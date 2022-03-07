
// System and QT Includes
#include <CwmsFormUserDefinedExecutor.h>
#include <QCoreApplication>
#include <QDir>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmMessageManager.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "CdmLogfileWriter.h"

// Basetools Includes
#include "CwmsApplication.h"
#include "CwmsFormUserDefined.h"
#include "CwmsContext.h"

// Own Includes
#include "CwmsErrorMessenger.h"
#include "CwmsGuiLoginIf.h"
#include "CwmsGuiDatabaseSelection.h"
#include "CwmsGuiApplicationSelectionIf.h"
#include "CwmsguiApplicationServices.h"
#include "CwmsRuntime.h"
#include "CwmsGuiInitApplication.h"


CwmsGuiInitApplication::CwmsGuiInitApplication(QString p_qstrApplicationName, QString p_qstrVersion)
    : CwmsInitApplication(p_qstrApplicationName, p_qstrVersion)
{
}

CwmsGuiInitApplication::~CwmsGuiInitApplication()
{
}

void CwmsGuiInitApplication::Logging()
{
    INITERRORMANAGER();

    QString qstrFilename = m_qstrApplicationName;
    qstrFilename = qstrFilename.replace(" ", "_") + ".log";
    QString qstrPath = QDir::homePath() + "/Documents/" + qstrFilename;
    CdmLogfileWriter* pLogger
            = new CdmLogfileWriter(qstrPath, m_qstrApplicationName, m_qstrVersion);
    CdmLogging::AddAdaptor(pLogger);

    CwmsErrorMessenger* pLoggerMessenger = new CwmsErrorMessenger();
    CdmLogging::AddAdaptor(pLoggerMessenger);

    StateFinished(true);
}

void CwmsGuiInitApplication::SetStyleSheet()
{
    QString qstrStylesheetPath = qApp->applicationDirPath() + "/manjaro.qss";
    QFile qFile(qstrStylesheetPath);

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream qts(&qFile);
        QString qstrStyleSheetDefinition = qts.readAll();

        if (!qstrStyleSheetDefinition.isEmpty())
        {
            qApp->setStyleSheet(qstrStyleSheetDefinition);
        }
    }
}

void CwmsGuiInitApplication::Login()
{
    //    SetStyleSheet();

    if (CwmsGuiLoginIf::Login(m_qstrApplicationName, nullptr))
    {
        StateFinished(true);
    }
    else
    {
        StateFinished(false);
    }
}

void CwmsGuiInitApplication::DbSelection()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        QList<QString> qllSchemes;
        pManager->GetSchemeList(qllSchemes);
        QList<QString> qlSchemes;

        QList<QString>::iterator qIt = qllSchemes.begin();
        QList<QString>::iterator qItEnd = qllSchemes.end();

        for (; qIt != qItEnd; ++qIt)
        {
            QString qstrSchemeName = *qIt;
            if (!qstrSchemeName.startsWith("Technical"))
            {
                qlSchemes.append(qstrSchemeName);
            }
        }

        if (qlSchemes.count() == 1)
        {
            QString qstrScheme = qlSchemes[0];
            CdmScheme* pCdmScheme = nullptr;
            if (pManager->LoadScheme(qstrScheme) > 0)
            {
                pCdmScheme = pManager->FindSchemeByName(qstrScheme);

                if (CHKPTR(pCdmScheme))
                {
                    pManager->SetCurrentScheme(pCdmScheme);
                    StateFinished(true);
                }
                else
                {
                    MSG_CRIT("Fehler beim Laden des Schemas", "Schema konnte nicht geladen werden!!!");
                    StateFinished(false);
                }
            }
        }
        else
        {
            CwmsGuiDatabaseSelection cDbSelect;
            cDbSelect.FillDialog(qllSchemes);

            if (cDbSelect.exec() == QDialog::Accepted)
            {
                StateFinished(true);
            }
            else
            {
                StateFinished(false);
            }
        }
    }
}

void CwmsGuiInitApplication::ApplicationSelection()
{
    CwmsGuiApplicationSelectionIf cAppSelection;
    QString qstrApplication = CwmsGuiApplicationSelectionIf::GetApplicationString();

    if (!qstrApplication.isEmpty())
    {
        SetApplication(qstrApplication);
        StateFinished(true);
    }
    else
    {
        StateFinished(false);
    }
}

void CwmsGuiInitApplication::ApplicationStart()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && !m_qstrApplicationName.isEmpty())
    {
        CwmsApplication cApp;

        CdmObject* pCdmObject = CwmsApplication::GetApplication(m_qstrApplicationName);

        if (CHKPTR(pCdmObject))
        {
            cApp.SetObject(pCdmObject);
            CwmsContext::CreateContext(pCdmObject);
            CwmsguiApplicationServices::InstallFunctionsAndPlugins();
            CwmsRuntime::Execute(cApp, nullptr);
        }
    }
}
