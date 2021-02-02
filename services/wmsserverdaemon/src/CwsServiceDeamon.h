
#ifndef CWSDEAMON_H
#define CWSDEAMON_H

// System and QT Includes
#include <QCoreApplication>
#include <QDateTime>
#include <QObject>

// Own Includes
#include "qtservice.h"
#include "CwsHttpServer.h"

// forwards
class QFile;
class QDebug;
class CwmsHttpRequestHandler;

enum EwmsDebugSeverity {
    eWmsDebugSeverityNone,
    eWmsDebugSeverityDebug,
    eWmsDebugSeverityWarning,
    eWmsDebugSeverityError,
    eWmsDebugSeverityFatal
};

class CwsServiceDaemon : public QObject, public QtService
{
    Q_OBJECT

   private:
      QProcess* m_pProcessActive;
      QProcess* m_pProcessBackup;
      QDateTime m_qdtActiveProcessStart;
      int m_iCurrentServerPort;
      int m_iCurrentMaintenanceServerPort;
      int m_iListeningServerPort;
      int m_iListeningMaintenanceServerPort;
      int m_iActivePort;
      int m_iBackupPort;
      int m_iMaintenanceActivePort;
      int m_iMaintenanceBackupPort;
      int m_iMaxThreads;
      QString m_qstrServerName;
      bool m_bSimulateProcessManagement;
      int m_iMaxServerAge;
      int m_iBestSwitchHourStart;
      int m_iBestSwitchHourEnd;
      int m_iProcessCheck;
      static EwmsDebugSeverity m_sDebugSeverity;
      static QFile* m_pFile;
      static QMutex* m_qLoggingMutex;
      CwsHttpServer* m_pApplicationServer;
      CwsHttpServer* m_pMaintenanceServer;
      CwmsHttpRequestHandler* m_pServiceHandler;
      CwmsHttpRequestHandler* m_pMaintenaceHandler;
      QString m_qstrDebugPath;
      int m_iMaxMemUsage;

      void CreateProcesses();
      void ReadConfiguration();
      int GetActiveProcessMemoryUsageInKByte();
      void SwitchProcess();
      void CreateBackupProcess();

      void SwitchMaintenanceServerPort();
      void SwitchApplicationServerPort();
      bool PingActiveProcess(int p_iPort);
      bool PingActiveProcess();
      void InitDebugger();
      void KillProcess(QProcess *p_pProcess);
      void CreateActiveProcess();
protected:
      void start();
      void pause();
      void resume();
      void stop();

private slots:
      void ProcessErrorSlot(QProcess::ProcessError);
      void ProcessCheckSlot();
      void ProcessFinishedSlot(int p_iExitCode, QProcess::ExitStatus p_eExitStatus);


      void BackupProcessFinishedSlot(int p_iExitCode, QProcess::ExitStatus p_eExitStatus);
public:
      CwsServiceDaemon(int argc, char** argv);
      ~CwsServiceDaemon();
      void AddActiveProcessEventHandling();
      static void wmsQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};


#endif //
