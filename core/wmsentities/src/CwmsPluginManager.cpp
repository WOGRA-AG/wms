// System and QT includes
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QPluginLoader>

// WMS Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmExecutor.h"
#include "CdmObject.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "IwmsPrintingPlugin.h"
#include "IwmsPluginInterface.h"

// own Includes
#include "CwmsServerSettings.h"
#include "CwmsTechnicalSchemeSwitch.h"
#include "CwmsContext.h"
#include "CwmsApplicationServices.h"
#include "CwmsPluginManager.h"

CwmsPluginManager::CwmsPluginManager()
{
    if (CwmsContext::GetContext()->GetContextType() != eWmsApplicationContextServer)
    {
        RefreshPlugins();
    }
}

CwmsPluginManager::~CwmsPluginManager()
{
}

void CwmsPluginManager::CreateDataStructure()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
        CdmClassManager* pClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            pClassManager->CreateClass("Technical_Plugins");
            CreatePluginsClass(pClassManager);
            CreateContainer();
        }
    }
}

void CwmsPluginManager::CreateContainer()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            QString qstrKeyname = "TechnicalAdminPlugins";
            pContainerManager->CreateContainer("Technical_Plugins",  qstrKeyname);
            CreateServerScheme();

        }
    }
}

bool CwmsPluginManager::CheckDataStructure()
{
    bool bRet = false;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager && pCdmManager->GetCurrentScheme())
    {
        CdmClassManager* pClassManager = pCdmManager->GetClassManager();

        if (pClassManager)
        {
            if (pClassManager->FindClassByKeyname("Technical_Plugins"))
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

void CwmsPluginManager::CreatePluginsClass(CdmClassManager* p_pClassManager)
{
    if (CHKPTR(p_pClassManager))
    {
        CdmClass* pCdmClass = p_pClassManager->FindClassByKeyname("Technical_Plugins");

        if (CHKPTR(pCdmClass))
        {
            pCdmClass->SetComment(QObject::tr("Plugin Einstellungen des Schemas"));
            pCdmClass->SetCaption(QObject::tr("Plugins Konfiguration"));
            pCdmClass->SetCaptionMember("");
            CdmMember* pCdmMember = nullptr;

            pCdmMember = pCdmClass->CreateMember("Name",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetComment(QObject::tr("Der Name des Plugins"));
                pCdmMember->SetCaption(QObject::tr("Pluginname"));
            }

            pCdmMember = pCdmClass->CreateMember("Active",
                                                 eDmValueBool,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetDefaultValue(true);
                pCdmMember->SetComment(QObject::tr("Aktiv Kennzeichen des Plugins"));
                pCdmMember->SetCaption(QObject::tr("Aktiv"));
            }

            pCdmMember = pCdmClass->CreateMember("Version",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetComment(QObject::tr("Die Versionsnummer des Plugins"));
                pCdmMember->SetCaption(QObject::tr("Version"));
            }

            pCdmMember = pCdmClass->CreateMember("Library",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetComment(QObject::tr("Der Dateiname des Plugins"));
                pCdmMember->SetCaption(QObject::tr("Dateiname"));
            }

            pCdmMember = pCdmClass->CreateMember("Plugin_Type",
                                                 eDmValueEnum,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetComment(QObject::tr("Die Art des Plugins"));
                pCdmMember->SetCaption(QObject::tr("Typ"));
                pCdmMember->SetValidationCode(QObject::tr("Funktion, Server Funktion, Print Output, User Interface"));
            }

            pCdmMember = pCdmClass->CreateMember("Required",
                                                 eDmValueBool,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
                pCdmMember->SetComment(QObject::tr("Pflichtplugin für Applikation"));
                pCdmMember->SetCaption(QObject::tr("Benötigt"));
            }

            pCdmClass->Commit();
        }
    }
}


void CwmsPluginManager::RefreshPlugins(QMainWindow* p_pMainWindow)
{
    if (!CheckDataStructure())
    {
        CreateDataStructure();
    }

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager) && pManager->GetCurrentScheme())
    {
        CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();
        pAddOnManager->ClearPlugins();
        LoadPrintingPlugin();
        InstallFunctionPlugins(p_pMainWindow);
    }
}

void CwmsPluginManager::LoadPrintingPlugin()
{
    INFO("Remove printing plugin");
    RemovePrintingPlugin();

    INFO("Loading Plugin Container");
    CdmObjectContainer* pContainer = GetPluginContainer();

    if (CHKPTR(pContainer))
    {
        QStringList qstrlFiles;
        QString qstrWql = QString("select Library from \"%1\" where and(Plugin_Type=%2, Active = true)")
                .arg(pContainer->GetKeyname())
                .arg(eWmsPluginTypePrinting);

        QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql, pContainer));

        if (CHKPTR(pQuery))
        {
            int iResults = pQuery->GetResultCount();

            if (iResults > 0)
            {
                INFO("Found " + QString::number(iResults) + " printing plugins. Loading the first");
                LoadPrintingPlugin(pQuery->GetResultAt(0,0).toString());

                if (iResults > 1)
                {
                    WARNING("More than one printing plugin active. Take first found.");
                }
            }
            else
            {
                WARNING("No active printing plugin found!");
            }
        }
    }
}

void CwmsPluginManager::RemovePrintingPlugin()
{
    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        pAddOnManager->ResetPrintingPlugin();
    }
}

IwmsPrintingPlugin *CwmsPluginManager::GetPrintingPlugin() // does the job of the addon manager TODO: Refactor
{
    IwmsPrintingPlugin* pPlugin = nullptr;
    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        pPlugin = pAddOnManager->GetPrintingPlugin();
    }

    return pPlugin;
}

void CwmsPluginManager::LoadPrintingPlugin(QString p_qstrFileName)
{
    RemovePrintingPlugin();
    QString qstrFileName = qApp->applicationDirPath() + PRINTINGPLUGINPATH + "/" + p_qstrFileName;
    QPluginLoader qLoader(qstrFileName);

    if (qLoader.load())
    {
        INFO("Plugin Loader loaded printingplugin successfully");
        QObject* pObject = qLoader.instance();
        IwmsPrintingPlugin* pPrintingPlugin = qobject_cast<IwmsPrintingPlugin*>(pObject);

        if (pPrintingPlugin)
        {
            INFO("Casted plugin successfully");
            CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

            if (CHKPTR(pAddOnManager))
            {
                INFO("Set it to add on manager successfully");
                pAddOnManager->SetPrintingPlugin(pPrintingPlugin);
            }
        }
    }
    else
    {
        QString qstrMessage = "File " + qstrFileName + " is not a valid printing plugin and will be ignored. Errormessage:\n" + qLoader.errorString();
        WARNING(qstrMessage);
        MSG_CRIT("Printing Plugin is not loaded", qstrMessage.toUtf8());
    }
}

bool CwmsPluginManager::HasPrintingPlugin()
{
    bool bRet = false;

    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        bRet = (pAddOnManager->GetPrintingPlugin() != nullptr);
    }

    return bRet;
}

CdmObjectContainer* CwmsPluginManager::GetPluginContainer()
{
    CdmObjectContainer* pContainer = nullptr;

    if (CHKPTR(CwmsContext::GetContext()))
    {
        if (CwmsContext::GetContext()->GetContextType() == eWmsApplicationContextApplication)
        {
            INFO("In Application Context Get App Plugins Config");
            CwmsApplication cApp = CwmsContext::GetContext()->GetApplication();
            pContainer = cApp.GetPlugins();
        }
        else if (CwmsContext::GetContext()->GetContextType() == eWmsApplicationContextServer)
        {
            INFO("In Server Context Get Server Plugins Config");
            pContainer = GetServerPluginContainer();
        }
        else if (CwmsContext::GetContext()->GetContextType() == eWmsApplicationContextAdmin)
        {
            CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
            CdmContainerManager* pContainerManager = pManager->GetContainerManager();

            if (CHKPTR(pContainerManager))
            {
                CdmScheme* pScheme = pManager->GetCurrentScheme();

                // if you opened the server scheme
                if (CHKPTR(pScheme) && pScheme->GetSchemeName() == WMS_TECHNICAL_SERVER)
                {
                    pContainer = GetServerPluginContainer();
                }
                else
                {
                    pContainer = pContainerManager->FindContainerByKeyname("TechnicalAdminPlugins");
                }
            }
        }
    }

    return pContainer;
}

CdmObjectContainer* CwmsPluginManager::GetServerPluginContainer()
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CwmsTechnicalSchemeSwitch themeSwitch;
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            INFO("Load TechnicalServerPlugins Container");
            pContainer = pContainerManager->FindContainerByKeyname("TechnicalServerPlugins");
        }
    }

    return pContainer;
}

void CwmsPluginManager::InstallFunctionPlugins(CdmObjectContainer* pContainer, QMainWindow* p_pMainWindow)
{
    if (CHKPTR(pContainer))
    {
        QStringList qstrlFiles;
        QString qstrWql = QString("select Library from \"%1\" where and(Plugin_Type=%2, Active = true)")
                .arg(pContainer->GetKeyname())
                .arg(eWmsPluginTypeFunction);

        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql, pContainer);

        if (CHKPTR(pQuery))
        {
            int iResults = pQuery->GetResultCount();

            for (int pos = 0; pos < iResults; ++pos)
            {
                qstrlFiles.append(pQuery->GetResultAt(0, pos).toString());
            }

            InstallFunctionPlugins(qstrlFiles, p_pMainWindow);
        }
    }
}

void CwmsPluginManager::InstallFunctionPlugins(QMainWindow* p_pMainWindow)
{
    CdmObjectContainer* pContainer = GetPluginContainer();
    InstallFunctionPlugins(pContainer, p_pMainWindow);
}

void CwmsPluginManager::InstallFunctionPlugins(QStringList& p_qstrlFunctions, QMainWindow* p_pMainWindow)
{
    for (int iCounter = 0; iCounter < p_qstrlFunctions.count(); ++iCounter)
    {
        QString qstrPlugin = p_qstrlFunctions[iCounter];
        LoadFunctionPlugin(qstrPlugin, p_pMainWindow);
    }
}

void CwmsPluginManager::LoadFunctionPlugin(QString qstrPluginFilename, QMainWindow* p_pMainWindow)
{
    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        QString qstrFilename = qApp->applicationDirPath() + FUNCTIONPLUGINPATH + "/" + qstrPluginFilename;
        QPluginLoader qLoader(qstrFilename);

        if (qLoader.load())
        {
            QObject* pObject = qLoader.instance();
            IwmsPluginInterface* pPlugin = qobject_cast<IwmsPluginInterface*>(pObject);

            if (CHKPTR(pPlugin))
            {
                pPlugin->init();
                QStringList qstrlFunctions = pPlugin->functionClasses();
                QString qstrPluginName = pPlugin->getName();

                for (int iFuncCounter = 0; iFuncCounter < qstrlFunctions.count(); ++iFuncCounter)
                {
                    QString qstrFunction = qstrlFunctions[iFuncCounter];
                    pAddOnManager->InstallPlugin(qstrPluginName + "." + qstrFunction, pPlugin);
                }

                if (p_pMainWindow && CwmsContext::GetContext())
                {
                    QList<QAction*> qlActions;
                    if (CwmsContext::GetContext()->GetContextType() == eWmsApplicationContextAdmin)
                    {
                        qlActions = pPlugin->getWmsDpActions();
                    }
                    else if (CwmsContext::GetContext()->GetContextType() == eWmsApplicationContextApplication)
                    {
                        qlActions = pPlugin->getWmsRuntimeActions();
                    }

                    if (qlActions.count() > 0)
                    {
                        QMenuBar* pMenuBar = p_pMainWindow->menuBar();
                        QMenu* pMenu = pMenuBar->findChild<QMenu*>(pPlugin->getName());
                        //pMenuBar->findChild<Qmenu*>(pPlugin->getName());

                        if (!pMenu)
                        {
                            pMenu = pMenuBar->addMenu(pPlugin->getName());

                            if (CHKPTR(pMenu))
                            {
                                pMenu->addActions(qlActions);
                            }
                        }
                    }
                }

                INFO("Plugin file " +  qstrFilename + " will be used");
            }
        }
        else
        {
            WARNING("File " + qstrFilename + " is not a valid plugin and will be ignored.");
        }
    }
}

void CwmsPluginManager::RemoveFunctionPlugin(QString p_qstrPlugin)
{
    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        pAddOnManager->RemovePlugin(p_qstrPlugin);
    }
}

void CwmsPluginManager::InstallServerFunctionPlugins()
{
    InstallFunctionPlugins(nullptr);
}

void CwmsPluginManager::LoadServerPlugins()
{
    CdmExecutorAddOnManager* pAddOnManager = GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
        pAddOnManager->ClearPlugins();
    }


    InstallServerFunctionPlugins();
    LoadPrintingPlugin();
}

CdmExecutorAddOnManager* CwmsPluginManager::GetAddOnManager()
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (pExecutor)
    {
        return CdmExecutor::GetExecutor()->GetAddOnManager();
    }

    return nullptr;
}

void CwmsPluginManager::CreateServerScheme()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CwmsTechnicalSchemeSwitch schemeSwitch;

    CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();
    CdmClassManager* pClassManager = pCdmManager->GetClassManager();

    if (CHKPTR(pContainerManager) && CHKPTR(pClassManager))
    {
        if (!pClassManager->FindClassByKeyname("Technical_Plugins"))
        {
            pClassManager->CreateClass("Technical_Plugins");
            CreatePluginsClass(pClassManager);
            QString qstrKeyname = "TechnicalServerPlugins";
            pContainerManager->CreateContainer("Technical_Plugins",  qstrKeyname);
        }
    }
}

void CwmsPluginManager::LoadInstalledPrintingPlugins()
{
    QString qstrPluginsPath = qApp->applicationDirPath() + PRINTINGPLUGINPATH;
    QDir qPluginsDir(qstrPluginsPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);
    CdmObjectContainer* pContainer = GetPluginContainer();

    if (CHKPTR(pContainer))
    {
        for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
        {
            QFileInfo qfInfo = qlEntries[iCounter];
            AddPrintingPlugin(pContainer, qfInfo);
        }
    }
}

void CwmsPluginManager::AddPrintingPlugin(CdmObjectContainer* p_pContainer, QFileInfo qfInfo)
{
    QString qstrFile = qfInfo.absoluteFilePath();
    if (!qfInfo.isSymLink() && QLibrary::isLibrary(qstrFile))
    {
        QPluginLoader qLoader(qstrFile);

        if (qLoader.load())
        {
            QObject* pObject = qLoader.instance();
            IwmsPrintingPlugin* pPrintingPlugin = qobject_cast<IwmsPrintingPlugin*>(pObject);

            if (pPrintingPlugin)
            {
                FindPluginConfiguration(p_pContainer,
                                        pPrintingPlugin->getName(),
                                        pPrintingPlugin->getVersion(),
                                        eWmsPluginTypePrinting,
                                        qstrFile);
            }
            else
            {
                QString qstrError = qLoader.errorString();
                ERR("Error in loading Plugin.:" + qstrError);
            }
        }
    }
}

CdmObject* CwmsPluginManager::FindPluginConfiguration(CdmObjectContainer* p_pContainer, QString p_qstrPluginName, QString p_qstrVersion, EwmsPluginType p_Type, QString p_qstrFilename)
{
    CdmObject* pObject = nullptr;

    QString qstrWql = QString("select from \"%1\" where and(Name = \"%2\", Version = \"%3\",Plugin_Type = %4)")
            .arg(p_pContainer->GetKeyname())
            .arg(p_qstrPluginName)
            .arg(p_qstrVersion)
            .arg(p_Type);

    CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql, p_pContainer);

    if (CHKPTR(pQuery))
    {
        if (pQuery->GetResultCount() > 0)
        {
            pObject = pQuery->GetFirstResultObject();

            if (pQuery->GetResultCount() > 1)
            {
                WARNING("More than one result found. Taking first");
            }
        }
        else
        {
            INFO("Plugin not yet found in DB can be added now.");

            QFileInfo qfInfo(p_qstrFilename);

            pObject = p_pContainer->CreateNewObject();
            pObject->SetValue("Name", p_qstrPluginName);
            pObject->SetValue("Version", p_qstrVersion);
            pObject->SetValue("Plugin_Type", p_Type);
            pObject->SetValue("Required", false);
            pObject->SetValue("Active", false);
            pObject->SetValue("Library", qfInfo.fileName());
            pObject->Commit();
        }
    }

    return pObject;
}

void CwmsPluginManager::LoadInstalledFunctionsPlugins()
{
    QString qstrPluginsPath;

#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + FUNCTIONPLUGINPATH;
#endif


    QDir qPluginsDir(qstrPluginsPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);
    CdmObjectContainer* pContainer = GetPluginContainer();

    if (CHKPTR(pContainer))
    {
        for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
        {
            QFileInfo qfInfo = qlEntries[iCounter];
            QString qstrFile = qfInfo.absoluteFilePath();
            if (!qfInfo.isSymLink() && QLibrary::isLibrary(qstrFile))
            {
                AddFunctionPlugin(pContainer, qfInfo);
            }
        }
    }
}

void CwmsPluginManager::AddFunctionPlugin(CdmObjectContainer* p_pContainer, QFileInfo& qfInfo)
{
    QString qstrFile = qfInfo.absoluteFilePath();
    QPluginLoader qLoader(qstrFile);
    QStringList qlLoadedPlugins;

    if (qLoader.load())
    {
        QObject* pObject = qLoader.instance();
        IwmsPluginInterface* pPlugin = qobject_cast<IwmsPluginInterface*>(pObject);

        if (CHKPTR(pPlugin))
        {
            pPlugin->init();
            QStringList qstrlFunctions = pPlugin->functionClasses();
            QString qstrPluginName = pPlugin->getName();
            QString qstrVersion = pPlugin->getVersion();
            QString qstrLoadedPlugin = qstrPluginName+"-"+ qstrVersion;

            if (!qlLoadedPlugins.contains(qstrLoadedPlugin))
            {
                qlLoadedPlugins.append(qstrLoadedPlugin);
                FindPluginConfiguration(p_pContainer,
                                        qstrPluginName,
                                        qstrVersion,
                                        eWmsPluginTypeFunction,
                                        qstrFile);
            }
            else
            {
                WARNING("File " + qstrFile + " has the same plugin and version like another file and will be ignored.");
            }
        }
    }
    else
    {
        WARNING("File " + qstrFile + " is not a valid plugin and will be ignored.");
    }
}

CdmPackage* CwmsPluginManager::FindOrCreatePluginPackage()
{
    CdmPackage* pPackage = nullptr;

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

       if (CHKPTR(pCdmClassManager))
       {
           pPackage = pCdmClassManager->FindPackageByName(PLUGIN_PACKAGE);

           if (!pPackage)
           {
               pPackage = pCdmClassManager->CreatePackage(PLUGIN_PACKAGE, nullptr);
           }
       }
    }

    return pPackage;
}
