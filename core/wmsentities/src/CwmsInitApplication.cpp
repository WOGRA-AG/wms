
// System and QT Includes
#include <QCoreApplication>
#include <QDir>

// WMS Includes
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmEventLogger.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmLogfileWriter.h"

// Basetools Includes
#include "CwmsApplicationServices.h"
#include "CwmsContext.h"

// Own Includes
#include "CwmsInitApplication.h"

CwmsInitApplication::CwmsInitApplication(QString p_qstrApplicationName, QString p_qstrVersion)
    : m_eState(eInitStateLogin),
      m_qstrApplicationName(p_qstrApplicationName),
      m_qstrVersion(p_qstrVersion)
{
}

CwmsInitApplication::~CwmsInitApplication()
{
}

void CwmsInitApplication::InitApplication()
{
    BODY_TRY
    m_eState = eInitStateLogging;
    Continue();
    BODY_CATCH
}

void CwmsInitApplication::StateFinished(bool p_bSuccess)
{
    BODY_TRY
    if (p_bSuccess)
    {
        switch(m_eState)
        {
            case eInitStateLogging:
                m_eState = eInitStateLogin;
                break;
            case eInitStateLogin:
                m_eState = eInitStateDbSelection;
                break;
            case eInitStateDbSelection:
                m_eState = eInitStateApplicationSelection;
                break;
            case eInitStateApplicationSelection:
                m_eState = eInitStateApplicationStart;
                break;
            case eInitStateApplicationStart:
                m_eState = eInitStateFinished;
                break;
            default:
                m_eState = eInitStateCanceled;
                break;
        }
    }
    else
    {
        m_eState = eInitStateCanceled;
    }

    Continue();
    BODY_CATCH
}

void CwmsInitApplication::SetWmsStartApplication(const QString &qstrWmsStartApplication)
{
    BODY_TRY
    m_qstrWmsStartApplication = qstrWmsStartApplication;
    BODY_CATCH
}

void CwmsInitApplication::Continue()
{
    BODY_TRY
    switch(m_eState)
    {
    case eInitStateLogging:
        Logging();
        break;
    case eInitStateLogin:
        Login();
        break;
    case eInitStateDbSelection:
        DbSelection();
            break;
    case eInitStateApplicationSelection:
       ApplicationSelection();
       break;
    case eInitStateApplicationStart:
       ApplicationStart();
       break;
    case eInitStateFinished:
       Finished();
       break;
    case eInitStateCanceled:
       Canceled();
       break;
    default:
       ERR("Unknown state enum found")
       Canceled();
       break;
    }
    BODY_CATCH
}

void CwmsInitApplication::Logging()
{
    BODY_TRY
    INITERRORMANAGER()

    QString qstrFilename(m_qstrApplicationName);
    qstrFilename = qstrFilename.replace(QStringLiteral(" "), QStringLiteral("_")) + QStringLiteral(".log");
    QString qstrPath = QDir::homePath() + QStringLiteral("/Documents/") + qstrFilename;
    CdmLogfileWriter* pLogger = new CdmLogfileWriter(qstrPath, m_qstrApplicationName, m_qstrVersion);
    CdmLogging::AddAdaptor(pLogger);

    QString qstrFileNameEventLog = m_qstrApplicationName + QStringLiteral(" EventLog");
    qstrFileNameEventLog = qstrFileNameEventLog.replace(QStringLiteral(" "), QStringLiteral("_") + QStringLiteral(".log"));
    QString qstrEventLogPath = QDir::homePath() + QStringLiteral("/Documents/") + qstrFileNameEventLog;
    CdmEventLogger::CreateLoggingManager(qstrEventLogPath, m_qstrApplicationName, m_qstrVersion);

    StateFinished(true);
    BODY_CATCH
}

void CwmsInitApplication::Login()
{
}

void CwmsInitApplication::DbSelection()
{
}

void CwmsInitApplication::ApplicationSelection()
{
}

void CwmsInitApplication::ApplicationStart()
{
    BODY_TRY
    CdmObject* pCdmObject = CwmsApplication::GetApplication(m_qstrApplicationName);
    CwmsContext::CreateContext(pCdmObject);
    CwmsApplicationServices::InstallFunctionsAndPlugins();
    BODY_CATCH
}

void CwmsInitApplication::Finished()
{
    BODY_TRY
    deleteLater();
    BODY_CATCH
}

void CwmsInitApplication::Canceled()
{
    BODY_TRY
    CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

    if (pFactory)
    {
        pFactory->Logout();
    }

    qApp->quit();
    BODY_CATCH

    exit(0);
}

void CwmsInitApplication::StartMainFunction(QString p_qstrFunction)
{
    BODY_TRY
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        int pos = p_qstrFunction.lastIndexOf(QStringLiteral("."));

        QString qstrClass    = p_qstrFunction.left(pos);
        QString qstrFunction = p_qstrFunction.mid(pos + 1, p_qstrFunction.length() - pos - 1);

        CdmClassMethod* pMethod = nullptr;
        CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

            if (CHKPTR(pClass))
            {
                pMethod = pClass->FindMethod(qstrFunction);
            }
            else
            {
                ERR("Class " + qstrClass + " not found for calling static function " + qstrFunction + QStringLiteral("."))
            }
        }


        if (pMethod && pMethod->IsStatic())
        {
            QVariantList qlArguments;
            pExecutor->GetFunction()->ExecuteFunctionStatic(pMethod, qlArguments);
        }
        else
        {
            if (!pMethod)
            {
                ERR("Method " + qstrFunction + " not found in class " + qstrClass + QStringLiteral("."))
            }
            else
            {
                ERR("Main Function must be static method. The " + qstrFunction + " method in Class " + qstrClass + "  is not static!")
            }
        }
    }
    BODY_CATCH
}
