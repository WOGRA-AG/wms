// System or Qt Includes
#include <QSettings>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QTcpSocket>
#include <QCoreApplication>

// WMS Commons Include
#include "CwmsSettingsStoreFactory.h"
#include "CwsHttpClient.h"

// Own includes
#include "CwmsHttpRequestHandler.h"
#include "CwsServiceDeamon.h"
#include "wmsServerDefines.h"

QFile* CwsServiceDaemon::m_pFile = nullptr;
QMutex* CwsServiceDaemon::m_qLoggingMutex = nullptr;
EwmsDebugSeverity CwsServiceDaemon::m_sDebugSeverity = eWmsDebugSeverityError;

CwsServiceDaemon::CwsServiceDaemon(int argc, char** argv)
: QtService(argc, argv, "WMS Server Daemon"),
  m_pProcessActive(nullptr),
  m_pProcessBackup(nullptr),
  m_iCurrentServerPort(0),
  m_iCurrentMaintenanceServerPort(0),
  m_iListeningServerPort(DAEMON_SERVER_PORT_VALUE),
  m_iListeningMaintenanceServerPort(DEFAULT_MAINTENANCE_SERVER_PORT),
  m_iActivePort(PRIMARY_PORT_VALUE),
  m_iBackupPort(SECONDRAY_PORT_VALUE),
  m_iMaintenanceActivePort(MAINTENANCE_PRIMARY_PORT_VALUE),
  m_iMaintenanceBackupPort(MAINTENANCE_SECONDARY_PORT_VALUE),
  m_iMaxThreads(MAX_THREADS_VALUE),
  m_bSimulateProcessManagement(false),
  m_iMaxServerAge(DEFAULT_MAX_SERVER_AGE_HOURS_VALUE),
  m_iBestSwitchHourStart(DEFAULT_BEST_SWITCHINGHOUR_START),
  m_iBestSwitchHourEnd(DEFAULT_BEST_SWITCHINGHOUR_END),
  m_iProcessCheck(DEFAULT_PROCESS_CHECK_TIMEOUT),
  m_pApplicationServer(nullptr),
  m_pMaintenanceServer(nullptr),
  m_pServiceHandler(nullptr),
  m_iMaxMemUsage(MAX_MEM_USAGE_MB_VALUE)
{
   m_qstrServerName = SERVER_APP_NAME_VALUE;
   m_qstrDebugPath = DAEMON_LOGGING_PATH_VALUE;
   setServiceDescription("The REST WMS Server Daemon");
   setServiceFlags(QtServiceBase::CanBeSuspended);
}

CwsServiceDaemon::~CwsServiceDaemon()
{
    delete m_pApplicationServer;
    delete m_pMaintenanceServer;
    delete m_pServiceHandler;
    delete m_pMaintenaceHandler;

     KillProcess(m_pProcessActive);
     KillProcess(m_pProcessBackup);

    delete m_pFile;
}

void CwsServiceDaemon::start()
{
    ReadConfiguration();
    InitDebugger();
    qDebug() << "Configuration read. Logging initialized.";
    CreateProcesses();
    qDebug() << "All proccesses created.";
    m_pServiceHandler = new CwmsHttpRequestHandler(m_iActivePort);
    m_pMaintenaceHandler = new CwmsHttpRequestHandler(m_iMaintenanceActivePort);
    m_pApplicationServer = new CwsHttpServer(m_iListeningServerPort, m_iMaxThreads, m_pServiceHandler);
    qDebug() << "Application Server Connection object instantiated.";
    m_pMaintenanceServer = new CwsHttpServer(m_iListeningMaintenanceServerPort, m_iMaxThreads, m_pMaintenaceHandler);
    qDebug() << "Maintenance Server Connection object instantiated.";
    m_pApplicationServer->Start();
    qDebug() << "Application Server started. Listening on Port " << m_iListeningServerPort;
    m_qdtActiveProcessStart = QDateTime::currentDateTime();
    m_pMaintenanceServer->Start();
    qDebug() << "Maintenance Server started. Listening on Port " << m_iListeningMaintenanceServerPort;
    QTimer::singleShot(m_iProcessCheck, this, SLOT(ProcessCheckSlot()));
    qDebug() << "Processcheck starts in  " << m_iProcessCheck << " msecs.";
}

void CwsServiceDaemon::pause()
{
    m_pApplicationServer->Pause();
    m_pMaintenanceServer->Pause();
    qDebug() << "Daemon paused";
}

void CwsServiceDaemon::resume()
{
    m_pApplicationServer->Resume();
    m_pMaintenanceServer->Resume();
    qDebug() << "Daemon resumed";
}

void CwsServiceDaemon::stop()
{
    qDebug() << "Beginn stopping daemon.";
    KillProcess(m_pProcessActive);
    KillProcess(m_pProcessBackup);
    qDebug() << "Child processes killed.";
    m_pProcessActive = nullptr;
    m_pProcessBackup = nullptr;
    m_pApplicationServer->Stop();
    m_pMaintenanceServer->Stop();
    qDebug() << "Listening ports stopped";
    delete m_pApplicationServer;
    delete m_pMaintenanceServer;
    qDebug() << "Application Server object deleted.";
    qDebug() << "Maintenance Server object deleted.";
    m_pApplicationServer = nullptr;
    m_pMaintenanceServer = nullptr;
    qDebug() << "Daemon stopped, child processes killed.";
    qApp->quit();
}

void CwsServiceDaemon::ReadConfiguration()
{
    QSettings* pSettings = CwmsSettingsStoreFactory::GenerateServerSettings();

    if (pSettings)
    {
        m_iListeningServerPort = pSettings->value(DAEMON_SERVER_PORT, DAEMON_SERVER_PORT_VALUE).toInt();
        m_iListeningMaintenanceServerPort = pSettings->value(MAINTENANCE_PORT, DEFAULT_MAINTENANCE_SERVER_PORT).toInt();
        m_iActivePort = pSettings->value(PRIMARY_PORT, PRIMARY_PORT_VALUE).toInt();
        m_iBackupPort = pSettings->value(SECONDRAY_PORT, SECONDRAY_PORT_VALUE).toInt();
        m_iMaintenanceActivePort = pSettings->value(MAINTENANCE_PRIMARY_PORT, MAINTENANCE_PRIMARY_PORT_VALUE).toInt();
        m_iMaintenanceBackupPort = pSettings->value(MAINTENANCE_SECONDARY_PORT, MAINTENANCE_SECONDARY_PORT_VALUE).toInt();
        m_qstrServerName = pSettings->value(SERVER_CONFIG_NAME, SERVER_APP_NAME_VALUE).toString();
        m_bSimulateProcessManagement = pSettings->value(SIMULATE_PROCESSMANAGEMENT, false).toBool();
        m_iMaxServerAge = pSettings->value(MAX_SERVER_AGE, DEFAULT_MAX_SERVER_AGE_HOURS).toInt();
        m_iBestSwitchHourStart = pSettings->value(BEST_SWITCHINGHOUR_START, DEFAULT_BEST_SWITCHINGHOUR_START).toInt();
        m_iBestSwitchHourEnd = pSettings->value(BEST_SWITCHINGHOUR_END, DEFAULT_BEST_SWITCHINGHOUR_END).toInt();
        m_iMaxMemUsage = pSettings->value(MAX_MEM_USAGE_MB, MAX_MEM_USAGE_MB_VALUE).toInt();
        m_iMaxThreads = pSettings->value(MAX_THREADS, MAX_THREADS_VALUE).toInt();

        if (pSettings->value(DAEMON_LOGGING_INFO, false).toBool())
        {
            m_sDebugSeverity = eWmsDebugSeverityDebug;
        }
        else if (pSettings->value(DAEMON_LOGGING_WARNING, false).toBool())
        {
            m_sDebugSeverity = eWmsDebugSeverityWarning;
        }
        else if (pSettings->value(DAEMON_LOGGING_ERROR, true).toBool())
        {
            m_sDebugSeverity = eWmsDebugSeverityError;
        }
        else if (pSettings->value(DAEMON_LOGGING_FATAL, true).toBool())
        {
             m_sDebugSeverity = eWmsDebugSeverityFatal;
        }

        m_qstrDebugPath = pSettings->value(DAEMON_LOGGING_PATH, DAEMON_LOGGING_PATH_VALUE).toString();
        m_iProcessCheck = pSettings->value(HEALTH_CHECK_INTERVALL, HEALTH_CHECK_INTERVALL_VALUE).toInt() * 1000 * 60;
    }

    delete pSettings;
}

void CwsServiceDaemon::InitDebugger()
{
    if (m_pFile)
    {
        m_pFile->close();
        delete m_pFile;
    }

    m_pFile = new QFile(m_qstrDebugPath);
    m_qLoggingMutex = new QMutex();

    if (m_pFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qInstallMessageHandler(CwsServiceDaemon::wmsQtMessageHandler);
    }
}

void CwsServiceDaemon::CreateProcesses()
{
    if (!m_bSimulateProcessManagement)
    {
        CreateActiveProcess();
        CreateBackupProcess();
    }
}

void CwsServiceDaemon::CreateActiveProcess()
{
    m_pProcessActive = new QProcess(this);
    m_pProcessActive->setProgram(m_qstrServerName);

    QStringList qstrlArgsActive;
    qstrlArgsActive.append(EXEC_ARG);
    qstrlArgsActive.append(PORT_ARG + QString::number(m_iActivePort));
    qstrlArgsActive.append(MAINTENANCE_PORT_ARG + QString::number(m_iMaintenanceActivePort));
    m_pProcessActive->setArguments(qstrlArgsActive);
    m_pProcessActive->start();
    qDebug() << "Active Process started with arguments " << qstrlArgsActive.join(" ");
    m_iCurrentServerPort = m_iActivePort;
    qDebug() << "Current Application Server port " << m_iCurrentServerPort;
    m_iCurrentMaintenanceServerPort = m_iMaintenanceActivePort;
    qDebug() << "Current Maintenance Server port " << m_iCurrentMaintenanceServerPort;
    AddActiveProcessEventHandling();
}


void CwsServiceDaemon::ProcessErrorSlot(QProcess::ProcessError)
{
    SwitchProcess();
}

void CwsServiceDaemon::ProcessFinishedSlot(int p_iExitCode, QProcess::ExitStatus p_eExitStatus)
{
    qWarning() << "Server Child Process finished. ExitCode" << p_iExitCode << "Exit Status " << p_eExitStatus;
    SwitchProcess();
}

void CwsServiceDaemon::BackupProcessFinishedSlot(int p_iExitCode, QProcess::ExitStatus p_eExitStatus)
{
    qWarning() << "Server Child Process finished. ExitCode" << p_iExitCode << "Exit Status " << p_eExitStatus;
    delete m_pProcessBackup;
    m_pProcessBackup = nullptr;
    CreateBackupProcess();
}

void CwsServiceDaemon::AddActiveProcessEventHandling()
{
    m_pProcessActive->disconnect();
    connect(m_pProcessActive, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(ProcessErrorSlot(QProcess::ProcessError)));

    connect(m_pProcessActive, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(ProcessFinishedSlot(int, QProcess::ExitStatus)));
}

void CwsServiceDaemon::SwitchProcess()
{
    m_qdtActiveProcessStart = QDateTime::currentDateTime();
    SwitchApplicationServerPort();
    SwitchMaintenanceServerPort();

    if (m_pProcessActive)
    {
        KillProcess(m_pProcessActive);
    }

    m_pProcessActive = m_pProcessBackup;
    AddActiveProcessEventHandling();
    CreateBackupProcess();
}

void CwsServiceDaemon::KillProcess(QProcess* p_pProcess)
{
    if (p_pProcess)
    {
        p_pProcess->disconnect();
        p_pProcess->kill();
        p_pProcess->waitForFinished(10);
        delete p_pProcess;
    }
}

void CwsServiceDaemon::SwitchApplicationServerPort()
{
    if (m_iCurrentServerPort == m_iActivePort)
    {
        m_iCurrentServerPort = m_iBackupPort;
    }
    else
    {
        m_iCurrentServerPort = m_iActivePort;
    }
}

void CwsServiceDaemon::SwitchMaintenanceServerPort()
{
    if (m_iCurrentMaintenanceServerPort == m_iMaintenanceActivePort)
    {
        m_iCurrentMaintenanceServerPort = m_iBackupPort;
    }
    else
    {
        m_iCurrentMaintenanceServerPort = m_iMaintenanceActivePort;
    }
}
void CwsServiceDaemon::CreateBackupProcess()
{
    m_pProcessBackup = new QProcess(this);
    m_pProcessBackup->setProgram(m_qstrServerName);
    QStringList qstrlArgsBackup;
    qstrlArgsBackup.append(EXEC_ARG);

    if (m_iCurrentServerPort == m_iActivePort)
    {
        qstrlArgsBackup.append(PORT_ARG + QString::number(m_iBackupPort));
    }
    else
    {
        qstrlArgsBackup.append(PORT_ARG + QString::number(m_iActivePort));
    }

    if (m_iCurrentMaintenanceServerPort == m_iMaintenanceActivePort)
    {
        qstrlArgsBackup.append(MAINTENANCE_PORT_ARG + QString::number(m_iMaintenanceBackupPort));
    }
    else
    {
        qstrlArgsBackup.append(MAINTENANCE_PORT_ARG + QString::number(m_iMaintenanceActivePort));
    }

    m_pProcessBackup->setArguments(qstrlArgsBackup);
    m_pProcessBackup->start();
    qDebug() << "Backup Process started with arguments " << qstrlArgsBackup.join(" ");

    connect(m_pProcessBackup, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(BackupProcessFinishedSlot(int, QProcess::ExitStatus)));

}

void CwsServiceDaemon::ProcessCheckSlot()
{
    bool bSwitchProcess = false;
    qDebug() << "Health check started.";
    if(PingActiveProcess())
    {
        int memUsage = GetActiveProcessMemoryUsageInKByte();
        if (m_iMaxMemUsage < memUsage/1024)
        {
            bSwitchProcess = true;
            qWarning() << "Memory usage exceeded defined border of " << m_iMaxMemUsage << " MB. Usage: " <<memUsage << " switching process";
        }
    }
    else
    {
        bSwitchProcess = true;
        qWarning() << "Server does not answer. Switching process";
    }

    if (!bSwitchProcess)
    {
        QDateTime current = QDateTime::currentDateTime();
        int iRunningHours = current.secsTo(m_qdtActiveProcessStart) / 60 / 60;

        if (iRunningHours > m_iMaxServerAge)
        {
            int iCurrentHour = current.time().hour();

            if (iCurrentHour >= m_iBestSwitchHourStart && iCurrentHour <= m_iBestSwitchHourEnd)
            {
                qDebug() << "Server exceeded max uptime. Switching process";
                bSwitchProcess = true;
            }
        }
    }


    if (bSwitchProcess)
    {
        SwitchProcess();
    }
    else
    {
        qDebug() << "Health check successfully finished";
    }

    QTimer::singleShot(m_iProcessCheck, this, SLOT(ProcessCheckSlot()));
}

int CwsServiceDaemon::GetActiveProcessMemoryUsageInKByte()
{
    int iLength = 0;
    QString qstrCommand = "{\"Command\": \"GetOpenSessions\"}";
    QByteArray qbaResult;
    QTcpSocket socket;
    CwsHttpClient client;
    client.SetPort(m_iMaintenanceActivePort);
    CwsHttpRequest request;
    request.SetBody(qstrCommand);
    CwsHttpResponse response;

    if (client.sendRequest(request, response))
    {
       QString qstrContent = response.GetBody();
       QString qstrMemUsage = "MemoryUsage";
       int iPos = qstrContent.indexOf(qstrMemUsage);

       if (iPos >= 0)
       {
           iPos += qstrMemUsage.length();
           iPos = qstrContent.indexOf(":", iPos);
           int iEndPos = qstrContent.indexOf(",", iPos);
           QString qstrMemContent = qstrContent.mid(iPos+1, iEndPos - iPos - 1);
           qstrMemContent = qstrMemContent.remove("\"");
           qstrMemContent = qstrMemContent.simplified();
           iLength = qstrMemContent.toInt();
       }
    }

    return iLength;
}

bool CwsServiceDaemon::PingActiveProcess()
{
   bool bSuccess = true;

   bSuccess = PingActiveProcess(m_iCurrentServerPort);

   if (bSuccess)
   {
       bSuccess = PingActiveProcess(m_iCurrentMaintenanceServerPort);
   }

   return bSuccess;
}

bool CwsServiceDaemon::PingActiveProcess(int p_iPort)
{
    bool bSuccess = false;
    CwsHttpClient client;
    client.SetPort(p_iPort);
    CwsHttpRequest request;
    request.SetBody("{\"Command\" : \"Ping\"}");
    CwsHttpResponse response;

    if (client.sendRequest(request, response))
    {
        if (!response.GetBody().isEmpty())
        {
            bSuccess = true;
        }
        else
        {
            qWarning() << "Service does not answer to ping request. Port: " << p_iPort;
        }
    }

   return bSuccess;
}

void CwsServiceDaemon::wmsQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QTextStream stdoutStream(stdout);
    stdoutStream << context.function << " "  << context.line << " " << msg << endl;

    switch (type) {
    case QtDebugMsg:
        if (m_sDebugSeverity >= eWmsDebugSeverityDebug)
        {
            QMutexLocker lock(m_qLoggingMutex);
            QTextStream stream(m_pFile);
            stream << QDateTime::currentDateTime().toString() << " " << context.file << " " << context.function << " "  << context.line << " " << msg<< endl;
        }
        break;
    case QtWarningMsg:
        if (m_sDebugSeverity >= eWmsDebugSeverityWarning)
        {
            QMutexLocker lock(m_qLoggingMutex);
            QTextStream stream(m_pFile);
            stream << QDateTime::currentDateTime().toString() << " " << context.file << " " << context.function << " "  << context.line << " " << msg<< endl;
        }
        break;
    case QtCriticalMsg:
        if (m_sDebugSeverity >= eWmsDebugSeverityError)
        {
            QMutexLocker lock(m_qLoggingMutex);
            QTextStream stream(m_pFile);
            stream << QDateTime::currentDateTime().toString() << " " << context.file << " " << context.function << " "  << context.line << " " << msg<< endl;
        }
        break;
    case QtFatalMsg:
        if (m_sDebugSeverity >= eWmsDebugSeverityFatal)
        {
            QMutexLocker lock(m_qLoggingMutex);
            QTextStream stream(m_pFile);
            stream << QDateTime::currentDateTime().toString() << " " << context.file << " " << context.function << " "  << context.line << " " << msg<< endl;
        }
        break;
    default:
        if (m_sDebugSeverity >= eWmsDebugSeverityDebug)
        {
            QMutexLocker lock(m_qLoggingMutex);
            QTextStream stream(m_pFile);
            stream << QDateTime::currentDateTime().toString() << " " << context.file << " " << context.function << " "  << context.line << " " << msg<< endl;
        }
        break;
    }
}
