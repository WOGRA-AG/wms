// System and Qt Includes
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QPluginLoader>

// WMS Manager Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmExecutor.h"
#include "CdmLogging.h"
#include "CdmExecutorAddOnManager.h"

// own Includes
#include "IwmsPluginInterface.h"
#include "CwmsPluginManager.h"
#include "CwmsReportManager.h"
#include "CwmsTranslatorConfiguration.h"
#include "CwmsScriptableLogger.h"
#include "CwmsScriptableMailer.h"
#include "CwmsScriptableMessage.h"
#include "CwmsScriptablePrinter.h"
#include "CwmsScriptableUi.h"
#include "CwmsScriptableWorkflow.h"
#include "CwmsScriptablePlugin.h"
#include "CwmsScriptableStatic.h"
#include "CwmsScriptableWql.h"
#include "CwmsScriptableUtilities.h"
#include "CwmsScriptableGeoServices.h"
#include "CwmsScriptableHttpClient.h"
#include "CwmsScriptableFile.h"
#include "CwmsScriptableSql.h"
#include "CwmsScriptableTimer.h"
#include "CwmsSmtpManager.h"
#include "CwmsFormManager.h"
#include "CwmsImExportManager.h"
#include "CwmsApplicationManager.h"
#include "CwmsWorkflowManager.h"
#include "CwmsViewManager.h"
#include "CwmsApplicationServices.h"

void CwmsApplicationServices::InstallFunctionsAndPlugins()
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (pExecutor)
    {
        CdmExecutorAddOnManager* pAddOnManager = pExecutor->GetAddOnManager();

        if (pAddOnManager)
        {
            if (!pAddOnManager->ContainsFunctionality("message"))
            {
                pAddOnManager->InstallAdditionalFunctionality("message", new CwmsScriptableMessage());
            }

            if (!pAddOnManager->ContainsFunctionality("mail"))
            {
                pAddOnManager->InstallAdditionalFunctionality("mail", new CwmsScriptableMailer());
            }

            if (!pAddOnManager->ContainsFunctionality("printing"))
            {
                pAddOnManager->InstallAdditionalFunctionality("printing", new CwmsScriptablePrinter());
            }

            if (!pAddOnManager->ContainsFunctionality("wql"))
            {
                pAddOnManager->InstallAdditionalFunctionality("wql", new CwmsScriptableWql());
            }

            if (!pAddOnManager->ContainsFunctionality("ui"))
            {
                pAddOnManager->InstallAdditionalFunctionality("ui", new CwmsScriptableUi());
            }

            if (!pAddOnManager->ContainsFunctionality("workflow"))
            {
                pAddOnManager->InstallAdditionalFunctionality("workflow", new CwmsScriptableWorkflow());
            }

            if (!pAddOnManager->ContainsFunctionality("log"))
            {
                pAddOnManager->InstallAdditionalFunctionality("log", new CwmsScriptableLogger());
            }

            if (!pAddOnManager->ContainsFunctionality("plugin"))
            {
                pAddOnManager->InstallAdditionalFunctionality("plugin", new CwmsScriptablePlugin());
            }

            if (!pAddOnManager->ContainsFunctionality("staticExec"))
            {
                pAddOnManager->InstallAdditionalFunctionality("staticExec", new CwmsScriptableStatic());
            }

            if (!pAddOnManager->ContainsFunctionality("utilities"))
            {
                pAddOnManager->InstallAdditionalFunctionality("utilities", new CwmsScriptableUtilities());
            }

            if (!pAddOnManager->ContainsFunctionality("geo"))
            {
                pAddOnManager->InstallAdditionalFunctionality("geo", new CwmsScriptableGeoServices());
            }

            if (!pAddOnManager->ContainsFunctionality("httpClient"))
            {
                pAddOnManager->InstallAdditionalFunctionality("httpClient", new CwmsScriptableHttpClient());
            }

            if (!pAddOnManager->ContainsFunctionality("file"))
            {
                pAddOnManager->InstallAdditionalFunctionality("file", new CwmsScriptableFile());
            }

            if (!pAddOnManager->ContainsFunctionality("sql"))
            {
                pAddOnManager->InstallAdditionalFunctionality("sql", new CwmsScriptableSql());
            }

            if (!pAddOnManager->ContainsFunctionality("timer"))
            {
                pAddOnManager->InstallAdditionalFunctionality("timer", new CwmsScriptableTimer());
            }
        }
    }
}


void CwmsApplicationServices::InstallTranslationFiles()
{
    CwmsTranslatorConfiguration cTranslator("");
    cTranslator.InstallAllTranslationFiles();
}

void CwmsApplicationServices::InitCurrentScheme()
{
    CwmsReportManager cReportManager;
    CwmsViewManager cCwmsViewManager;
    CwmsFormManager formManager;
    CwmsImExportManager cManager;
    CwmsApplicationManager cAppManager;
    CwmsWorkflowManager cCwmsWorkflowManager;
    CwmsSmtpManager smtpManager;
    CwmsPluginManager pluginManager;

    InstallDeploymentFilesFromDirectory();
}

void CwmsApplicationServices::InstallDeploymentFilesFromDirectory()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pManager))
    {
        CdmScheme* pScheme = pManager->GetCurrentScheme();
        if (CHKPTR(pScheme))
        {
            QString qstrWdfPath = qApp->applicationDirPath() + WDFFILESPATH;
            QDir qWdfDir(qstrWdfPath);
            QStringList qstrlFilters;
            qstrlFilters.append("*.wdf");
            QFileInfoList qlEntries = qWdfDir.entryInfoList(qstrlFilters, QDir::Files);

            for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
            {
                QFileInfo qfInfo = qlEntries[iCounter];

                if (qfInfo.isFile())
                {
                    QString qstrFile = qfInfo.absoluteFilePath();
                    pScheme->Deploy(qstrFile);
                }
            }
        }
    }
}
