// System and QT Includes
#include <qstring.h>
#include <qfile.h>
#include <qdatetime.h>

// own Includes
#include "CdmLoggingAdaptor.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmLogging.h"


CdmLogging* CdmLogging::ms_pCdmLogger = nullptr;

CdmLogging::CdmLogging()
: m_iCounter(0),
  m_iLoggingMode(eDmError | eDmFatal)
{
}

CdmLogging::~CdmLogging()
{
    QList<CdmLoggingAdaptor*>::iterator qllIt = m_qvlAdaptors.begin();
    QList<CdmLoggingAdaptor*>::iterator qllItEnd = m_qvlAdaptors.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        DELPTR(*qllIt);
    }

    m_qvlAdaptors.clear();
}

void CdmLogging::AddAdaptor(CdmLoggingAdaptor* p_pCdmAdaptor)
{
    if (ms_pCdmLogger)
    {
        ms_pCdmLogger->AddAdaptorP(p_pCdmAdaptor);
    }
}

void CdmLogging::RemoveAdaptor(CdmLoggingAdaptor *p_pCdmAdaptor)
{
    if (ms_pCdmLogger)
    {
        ms_pCdmLogger->RemoveAdaptorP(p_pCdmAdaptor);
    }
}

void CdmLogging::AddAdaptorP(CdmLoggingAdaptor *p_pCdmAdaptor)
{
    if (CHKPTR(p_pCdmAdaptor))
    {
       SYNCHRONIZED

       if (!m_qvlAdaptors.contains(p_pCdmAdaptor))
       {
          m_qvlAdaptors.append(p_pCdmAdaptor);
       }
    }
}

void CdmLogging::RemoveAdaptorP(CdmLoggingAdaptor *p_pCdmAdaptor)
{
    if (CHKPTR(p_pCdmAdaptor))
    {
       SYNCHRONIZED

       if (m_qvlAdaptors.contains(p_pCdmAdaptor))
       {
          m_qvlAdaptors.removeAll(p_pCdmAdaptor);
       }
    }
}

void CdmLogging::CreateLoggingManager()
{
   if(!ms_pCdmLogger)
   {
      ms_pCdmLogger = new CdmLogging();
   }
   else
   {
      ms_pCdmLogger->AddLog(eDmError, "CdmError", "Error Manager already created", __LINE__);
   }
}

void CdmLogging::DestroyLoggingManager()
{
   if (ms_pCdmLogger)
   {
      delete ms_pCdmLogger;
      ms_pCdmLogger = nullptr;
   }
}

void CdmLogging::AddLog(EdmErrorSeverity p_eDmErrorSeverity,
                        QString p_qstrErrorModule,
                        QString p_qstrEventText,
                        int p_iLine)
{
   m_iCounter++;

   if (m_iLoggingMode & p_eDmErrorSeverity)
   {
       long lSessionId = 0;

       if (CdmSessionManager::GetSessionManager())
       {
           lSessionId = CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
       }
      
       CdmLogEntry entry(lSessionId,
                         QDateTime::currentDateTime(),
                         p_eDmErrorSeverity,
                         p_qstrErrorModule,
                         p_qstrEventText,
                         p_iLine);
       SYNCHRONIZED
       QList<CdmLoggingAdaptor*>::iterator qvlIt = m_qvlAdaptors.begin();
       QList<CdmLoggingAdaptor*>::iterator qvlItEnd = m_qvlAdaptors.end();

       for (; qvlIt != qvlItEnd; ++qvlIt)
       {
          CdmLoggingAdaptor* pCdmErrorAdaptor = (*qvlIt);

          if (pCdmErrorAdaptor)
          {
             pCdmErrorAdaptor->AddEvent(entry);
          }
       }
   }
}

void CdmLogging::AddInfoLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine)
{
   if (ms_pCdmLogger)
   {
      ms_pCdmLogger->AddLog(eDmInfo, p_qstrErrorModule, p_qstrEvent, p_iLine );
   }
}

void CdmLogging::AddWarningLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine)
{
   if (ms_pCdmLogger)
   {
      ms_pCdmLogger->AddLog(eDmWarning, p_qstrErrorModule, p_qstrEvent, p_iLine);
   }
}

void CdmLogging::AddErrorLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine)
{
   if(ms_pCdmLogger)
   {
      ms_pCdmLogger->AddLog(eDmError, p_qstrErrorModule, p_qstrEvent, p_iLine);
   }
}

void CdmLogging::AddFatalLog(QString p_qstrErrorModule, QString p_qstrEvent, int p_iLine)
{
   if (ms_pCdmLogger)
   {
      ms_pCdmLogger->AddLog(eDmFatal, p_qstrErrorModule,p_qstrEvent, p_iLine);
   }
}

void CdmLogging::SetLoggingMode(int p_iMode)
{
   if (ms_pCdmLogger)
   {
      ms_pCdmLogger->m_iLoggingMode = p_iMode;
   }
}

bool CdmLogging::CheckPtr(const void* p_pPtr, QString p_qstrFile, int p_iLine)
{
   bool bRet = false;

   if(p_pPtr != nullptr)
   {
      bRet = true;
   }
   else
   {
      CdmLogging::AddErrorLog(p_qstrFile, "nullptr Pointer found\n", p_iLine);
   }

   return bRet;
}

bool CdmLogging::Deprecated(QString p_qstrFile, int p_iLine)
{
    CdmLogging::AddErrorLog(p_qstrFile, "Deprecated Function Call\n", p_iLine);
    return false;
}

int CdmLogging::AddErrorCode(EdmErrorCode p_eDmErrorCode)
{
   return p_eDmErrorCode;
}

bool CdmLogging::WasSuccessFull(long p_lReturnCode)
{
    return (p_lReturnCode > 0);
}

void wmsQtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        CdmLogging::AddInfoLog(context.file, localMsg.constData(), context.line);
        break;
    case QtWarningMsg: // will be movd to error because qt warnings are wms errors
        CdmLogging::AddWarningLog(context.file, localMsg.constData(), context.line);
        break;
    case QtCriticalMsg:
        CdmLogging::AddErrorLog(context.file, localMsg.constData(), context.line);
        break;
    case QtFatalMsg:
        CdmLogging::AddFatalLog(context.file, localMsg.constData(), context.line);
        break;
    default:
        CdmLogging::AddInfoLog(context.file, localMsg.constData(), context.line);
        break;
    }
}
