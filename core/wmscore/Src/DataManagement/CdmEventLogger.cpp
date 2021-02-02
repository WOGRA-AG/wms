// System and QT Includes
#include <qstring.h>
#include <qfile.h>
#include <qdatetime.h>
#include <QThread>
#include <QDir>

// own Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

#include "CumUser.h"

#include "CdmEventLogger.h"

CdmEventLogger* CdmEventLogger::ms_pCdmEventLogger = nullptr;
QString CdmEventLogger::m_qstrOutputFormat = "%1;%2;%3;%4\n";

CdmEventLogger::CdmEventLogger(QString qstrFileName,
                               QString p_qstrApplicationName,
                               QString p_qstrVersion)
{
    if (qstrFileName.isEmpty())
    {
        qstrFileName = QDir::tempPath() + "/wms.log";
    }

    if (p_qstrApplicationName.isEmpty())
    {
        p_qstrApplicationName = "WMS Client Or Server";
    }

    if (p_qstrVersion.isEmpty())
    {
        p_qstrVersion = "Unknown Version";
    }

    m_logFile.setFileName(qstrFileName);

    if (m_logFile.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        QTextStream qtsStream(&m_logFile);
        QDateTime qdCurrent = QDateTime::currentDateTime();
        QString qstrStartText = p_qstrApplicationName + " Logging of Version " + p_qstrVersion +"\n";
        qstrStartText += "on " + qdCurrent.toString() + "\n";
        qtsStream << qstrStartText;
    }
}

CdmEventLogger::~CdmEventLogger()
{
}

void CdmEventLogger::CreateLoggingManager(QString qstrFileName,
                                          QString p_qstrApplicationName,
                                          QString p_qstrVersion)
{
    if(!ms_pCdmEventLogger)
    {
        ms_pCdmEventLogger = new CdmEventLogger(qstrFileName,
                                                p_qstrApplicationName,
                                                p_qstrVersion);
    }
}

void CdmEventLogger::DestroyLoggingManager()
{
    if (ms_pCdmEventLogger)
    {
        QDateTime qdCurrent = QDateTime::currentDateTime();
        QString qstrEndText = "Logging ended \n";
        qstrEndText += "on " + qdCurrent.toString();
        if (ms_pCdmEventLogger->m_logFile.isOpen())
        {
            QTextStream qtsStream(&ms_pCdmEventLogger->m_logFile);
            qtsStream << qstrEndText;
            ms_pCdmEventLogger->m_logFile.close();
        }
        delete ms_pCdmEventLogger;
        ms_pCdmEventLogger = nullptr;
    }
}

CdmEventLogger* CdmEventLogger::getEventLogger()
{
    return ms_pCdmEventLogger;
}

void CdmEventLogger::AddLog(QString p_qstrEventTextFirstPart,
                            QString p_qstrEventTextSecondPart)
{
    QString qstrUserName = "User: ";
    CumUser *pCurrentUser = const_cast<CumUser*>(CdmSessionManager::GetSessionManager()->GetCurrentUser());
    if(pCurrentUser)
    {
        qstrUserName += pCurrentUser->GetCompleteName();
    }

    QString qstrMessage = QString(m_qstrOutputFormat)
            .arg(QDateTime::currentDateTime().toString())
            .arg(qstrUserName)
            .arg(p_qstrEventTextFirstPart)
            .arg(p_qstrEventTextSecondPart);

    if (getEventLogger() != nullptr)
    {
        getEventLogger()->WriteToLogFile(qstrMessage);
    }
}

void CdmEventLogger::WriteToLogFile(QString qstrMessage)
{
    SYNCHRONIZED;
    if (m_logFile.isOpen() ||
        m_logFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream qtsStream(&m_logFile);
        qtsStream << qstrMessage;
        qtsStream.flush();
    }
}
