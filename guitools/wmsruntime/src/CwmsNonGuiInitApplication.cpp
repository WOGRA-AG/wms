
// System and QT Includes
#include <QCoreApplication>
#include <QDir>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmMessageManager.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmLogfileWriter.h"
#include "CdmLogging.h"

// Basetools Includes
#include "CwmsApplication.h"
#include "CwmsFormUserDefined.h"
#include "CwmsContext.h"

// Own Includes
#include "CwmsGuiLoginIf.h"
#include "CwmsGuiDatabaseSelection.h"
#include "CwmsGuiApplicationSelectionIf.h"
#include "CwmsApplicationServices.h"
#include "CwmsRuntime.h"
#include "CwmsNonGuiInitApplication.h"


CwmsNonGuiInitApplication::CwmsNonGuiInitApplication(QString p_qstrApplicationName, QString p_qstrVersion, QString p_qstrLogin, QString p_qstrPassword, QString p_qstrScheme, QString p_qstrApplication)
    : CwmsInitApplication(p_qstrApplicationName, p_qstrVersion),
      m_qstrLogin(p_qstrLogin),
      m_qstrPassword(p_qstrPassword),
      m_qstrScheme(p_qstrScheme),
      m_qstrApp(p_qstrApplication)
{
}

CwmsNonGuiInitApplication::~CwmsNonGuiInitApplication()
{
}

void CwmsNonGuiInitApplication::Logging()
{
    QString qstrFilename = m_qstrApplicationName;
    qstrFilename = qstrFilename.replace(" ", "_") + ".log";
    QString qstrPath = QDir::homePath() + "/Documents/" + qstrFilename;
    CdmLogfileWriter* pLogger
            = new CdmLogfileWriter(qstrPath, m_qstrApplicationName, m_qstrVersion);
    CdmLogging::AddAdaptor(pLogger);
    StateFinished(true);
}

void CwmsNonGuiInitApplication::Login()
{
    if (CwmsGuiLoginIf::TryLogin(m_qstrLogin, m_qstrPassword, m_qstrApplicationName, nullptr))
    {
        StateFinished(true);
    }
    else
    {
        StateFinished(false);
    }
}

void CwmsNonGuiInitApplication::DbSelection()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pCdmScheme = nullptr;
        if (pManager->LoadScheme(m_qstrScheme) > 0)
        {
            pCdmScheme = pManager->FindSchemeByName(m_qstrScheme);

            if (CHKPTR(pCdmScheme))
            {
                pManager->SetCurrentScheme(pCdmScheme);
                StateFinished(true);
            }
            else
            {
                MSG_CRIT("Fehler beim Laden des Schemas","Schema konnte nicht geladen werden!!!");
                StateFinished(false);
            }
        }
    }
}

void CwmsNonGuiInitApplication::ApplicationSelection()
{
    if (!m_qstrApp.isEmpty())
    {
        SetApplication(m_qstrApp);
        StateFinished(true);
    }
    else
    {
        StateFinished(false);
    }
}

void CwmsNonGuiInitApplication::ApplicationStart()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && !m_qstrApp.isEmpty())
    {
        CwmsApplication cApp;

        CdmObject* pCdmObject = CwmsApplication::GetApplication(m_qstrApp);
        cApp.SetObject(pCdmObject);
        CwmsContext::CreateContext(pCdmObject);
        CwmsApplicationServices::InstallFunctionsAndPlugins();
        QString qstrMain = cApp.GetMain();

        if (!qstrMain.isEmpty())
        {
            StartMainFunction(qstrMain);
        }
    }
}
