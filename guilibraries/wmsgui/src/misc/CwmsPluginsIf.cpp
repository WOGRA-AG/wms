// QT Includes
#include <QPluginLoader>
#include <QFileInfo>
#include <QDir>
#include <QTreeWidget>
#include <QTreeWidgetItem>

// WMS Includes
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmQueryBuilder.h"
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "IwmsPluginInterface.h"

// Basetools Includes
#include "CwmsPluginManager.h"

#include "CwmsContext.h"
#include "CwmsApplication.h"
#include "CwmsApplicationManager.h"
#include "CwmsApplicationServices.h"
#include "IwmsPrintingPlugin.h"
#include "IwmsWebService.h"
#include "CwmsReportManager.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsPluginsIf.h"
#include "IwmsguiPlugin.h"



CwmsPluginsIf::CwmsPluginsIf(QWidget* parent)
    : QWidget(parent)
{
    setupUi(this);
}

CwmsPluginsIf::~CwmsPluginsIf()
{
    // nothing to do at the moment ;-)
}

void CwmsPluginsIf::AddConnections()
{
    connect(m_pqtwPlugins, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(ItemChangedSlot(QTreeWidgetItem *, int)));
}

void CwmsPluginsIf::FillWidgetApplication(CwmsApplication p_App)
{
    if (!p_App.GetObject()->GetClass()->FindMember("Plugins"))
    {
        CwmsPluginManager cPluginManager;
        Q_UNUSED(cPluginManager);
        CwmsApplicationManager cAppManager;
        cAppManager.AddPluginsMember(p_App.GetObject()->GetClass());
    }

    CdmObjectContainer* pContainer = p_App.GetPlugins();

    if (CHKPTR(pContainer))
    {
        p_App.CommitObject();
        FillCommonPlugins(pContainer);
        FillUserInterfacePlugins(pContainer);
        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwPlugins);
        AddConnections();
    }
}

void CwmsPluginsIf::FillWidgetServer(CdmObjectContainer* p_pContainer)
{
    if (CHKPTR(p_pContainer))
    {
        FillCommonPlugins(p_pContainer);
        FillServerPlugins(p_pContainer);
        CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwPlugins);
        AddConnections();
    }
}

void CwmsPluginsIf::FillWidgetAdmin(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))
   {
      FillCommonPlugins(p_pContainer);
      FillUserInterfacePlugins(p_pContainer);
      CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwPlugins);
      AddConnections();
   }
}


void CwmsPluginsIf::FillCommonPlugins(CdmObjectContainer* pContainer)
{
    FillFunctionsPlugins(pContainer);
    FillPrintingPlugins(pContainer);
}

void CwmsPluginsIf::SetConfigurationData(CdmObject* pConfiguration, QTreeWidgetItem* pItem)
{
    if (CHKPTR(pConfiguration))
    {
       pItem->setData(0, Qt::UserRole, pConfiguration->GetUriInternal());
       m_qstrlFoundUris.append(pConfiguration->GetUriInternal());
       bool bActive = false;
       bool bRequired = false;
       QString qstrFile;
       pConfiguration->GetValue("Active", bActive);
       pConfiguration->GetValue("Required", bRequired);
       pConfiguration->GetValue("Library", qstrFile);

       if (bActive)
       {
           pItem->setCheckState(2, Qt::Checked);
       }
       else
       {
           pItem->setCheckState(2, Qt::Unchecked);
       }

       if (bRequired)
       {
           pItem->setCheckState(3, Qt::Checked);
       }
       else
       {
           pItem->setCheckState(3, Qt::Unchecked);
       }

       pItem->setText(4, qstrFile);
    }
}

void CwmsPluginsIf::AddPlugintoView(CdmObject* pConfiguration, QStringList qstrlFunctions, QTreeWidgetItem* pFunctionRoot, bool p_bExists)
{
    if (CHKPTR(pConfiguration))
    {
        QTreeWidgetItem* pItem = new QTreeWidgetItem(pFunctionRoot);
        QString qstrName;
        QString qstrVersion;
        pConfiguration->GetValue("Version", qstrVersion);
        pConfiguration->GetValue("Name", qstrName);

        pItem->setText(0, qstrName);
        pItem->setText(1, qstrVersion);

        if (p_bExists)
        {
            pItem->setText(3, tr("installiert"));
        }
        else
        {
            pItem->setText(3, tr("nicht installiert"));
            pItem->setData(3, Qt::TextColorRole, QColor(Qt::red));
        }


        SetConfigurationData(pConfiguration, pItem);

        for (int iFuncCounter = 0; iFuncCounter < qstrlFunctions.count(); ++iFuncCounter)
        {
            QString qstrFunction = qstrlFunctions[iFuncCounter];
            QTreeWidgetItem* pSubItem = new QTreeWidgetItem(pItem);
            pSubItem->setText(0, qstrFunction);
        }
    }
}

void CwmsPluginsIf::AddFunctionPlugin(CdmObjectContainer* p_pContainer, QFileInfo& qfInfo, QList<QString>& qlLoadedPlugins, QTreeWidgetItem* pFunctionRoot)
{
    QString qstrFile = qfInfo.absoluteFilePath();
    QPluginLoader qLoader(qstrFile);

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
              CdmObject* pConfiguration = FindPluginConfiguration(p_pContainer, 
                                                                  qstrPluginName, 
                                                                  qstrVersion, 
                                                                  eWmsPluginTypeFunction, 
                                                                  qstrFile);

              AddPlugintoView(pConfiguration, 
                              qstrlFunctions, 
                              pFunctionRoot);
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

void CwmsPluginsIf::FillFunctionsPlugins(CdmObjectContainer* p_pContainer)
{
    QTreeWidgetItem* pFunctionRoot = new QTreeWidgetItem(m_pqtwPlugins);
    pFunctionRoot->setText(0,tr("Funktionserweiterungen"));
    QString qstrPluginsPath;

#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + FUNCTIONPLUGINPATH;
#endif


    QDir qPluginsDir(qstrPluginsPath);
    QList<QString> qlLoadedPlugins;
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);
    QList<QString> qlFoundPlugins;

    for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
    {
       QFileInfo qfInfo = qlEntries[iCounter];
       if (!qfInfo.isSymLink())
       {
           AddFunctionPlugin(p_pContainer, qfInfo, qlLoadedPlugins, pFunctionRoot);
           qlFoundPlugins.append(qfInfo.fileName());
       }
       else
       {
            WARNING("File " + qfInfo.fileName() + " is a symbolic link and will be ignored.");
       }
    }

    FillNotExistingPlugins(p_pContainer, eWmsPluginTypeFunction, pFunctionRoot);
    pFunctionRoot->setExpanded(true);
}

void CwmsPluginsIf::FillServerPlugins(CdmObjectContainer* p_pContainer)
{
    QTreeWidgetItem* pServerRoot = new QTreeWidgetItem(m_pqtwPlugins);
    pServerRoot->setText(0,tr("Servererweiterungen"));
    QString qstrPluginsPath;

#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + SERVERPLUGIN;
#endif


    QDir qPluginsDir(qstrPluginsPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);

    for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
    {
       QFileInfo qfInfo = qlEntries[iCounter];
       AddServerPlugin(p_pContainer, pServerRoot, qfInfo);
    }

    FillNotExistingPlugins(p_pContainer, eWmsPluginTypeServer, pServerRoot);
    pServerRoot->setExpanded(true);

}

void CwmsPluginsIf::AddServerPluginToView(QTreeWidgetItem* pServerRoot, QString qstrFile, IwmsWebService* pServerPlugin, CdmObjectContainer* p_pContainer)
{
    if (pServerPlugin)
    {
        CdmObject* pObject = FindPluginConfiguration(p_pContainer, pServerPlugin->getName(), pServerPlugin->getVersion(), eWmsPluginTypeServer, qstrFile);

        if (CHKPTR(pObject))
        {
            AddPlugintoView(pObject, QStringList(), pServerRoot);
        }
    }
    else
    {
       WARNING("File " + qstrFile + " is not a valid printing plugin and will be ignored.");
    }
}

void CwmsPluginsIf::AddServerPlugin(CdmObjectContainer* p_pContainer, QTreeWidgetItem* pServerRoot, QFileInfo qfInfo)
{
    if (!qfInfo.isSymLink())
    {
        QString qstrFile = qfInfo.absoluteFilePath();
        QPluginLoader qLoader(qstrFile);

        if (qLoader.load())
        {
           QObject* pObject = qLoader.instance();
           IwmsWebService* pServerPlugin = qobject_cast<IwmsWebService*>(pObject);
           AddServerPluginToView(pServerRoot, qstrFile, pServerPlugin, p_pContainer);
        }
        else
        {
           WARNING("File " + qstrFile + " is not a valid printing plugin and will be ignored.");
        }
    }
    else
    {
        WARNING("File " + qfInfo.fileName() + " is a symbolic link and will be ignored.");
    }
}


void CwmsPluginsIf::AddPrintingPluginToView(QTreeWidgetItem* pPrintingRoot, QString qstrFile, IwmsPrintingPlugin* pPrintingPlugin, CdmObjectContainer* p_pContainer)
{
    if (pPrintingPlugin)
    {
        CdmObject* pObject = FindPluginConfiguration(p_pContainer, 
                                                     pPrintingPlugin->getName(), 
                                                     pPrintingPlugin->getVersion(), 
                                                     eWmsPluginTypePrinting, 
                                                     qstrFile);

        if (CHKPTR(pObject))
        {
            AddPlugintoView(pObject, 
                            QStringList(), 
                            pPrintingRoot);
        }
    }
    else
    {
       WARNING("File " + qstrFile + " is not a valid printing plugin and will be ignored.");
    }
}

void CwmsPluginsIf::AddPrintingPlugin(CdmObjectContainer* p_pContainer, QTreeWidgetItem* pPrintingRoot, QFileInfo qfInfo)
{
    QString qstrFile = qfInfo.absoluteFilePath();
    if (!qfInfo.isSymLink() && QLibrary::isLibrary(qstrFile))
    {
        QPluginLoader qLoader(qstrFile);

        if (qLoader.load())
        {
           QObject* pObject = qLoader.instance();
           IwmsPrintingPlugin* pPrintingPlugin = qobject_cast<IwmsPrintingPlugin*>(pObject);
           AddPrintingPluginToView(pPrintingRoot, qstrFile, pPrintingPlugin, p_pContainer);
        }
        else
        {
           QString qstrError = qLoader.errorString();
        }
    }
    else
    {
        WARNING("File " + qfInfo.fileName() + " is a symbolic link and will be ignored.");
    }
}

void CwmsPluginsIf::FillPrintingPlugins(CdmObjectContainer* p_pContainer)
{
    QTreeWidgetItem* pPrintingRoot = new QTreeWidgetItem(m_pqtwPlugins);
    pPrintingRoot->setText(0,tr("Druckausgabeerweiterungen"));

    QString qstrPluginsPath = qApp->applicationDirPath() + PRINTINGPLUGINPATH;
    QDir qPluginsDir(qstrPluginsPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);

    for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
    {
       QFileInfo qfInfo = qlEntries[iCounter];
       AddPrintingPlugin(p_pContainer, pPrintingRoot, qfInfo);
    }

    FillNotExistingPlugins(p_pContainer, eWmsPluginTypePrinting, pPrintingRoot);
    pPrintingRoot->setExpanded(true);
}

void CwmsPluginsIf::FillUserInterfacePlugins(CdmObjectContainer* p_pContainer)
{
    QTreeWidgetItem* pUIRoot = new QTreeWidgetItem(m_pqtwPlugins);
    pUIRoot->setText(0,tr("Benutzeroberflächen"));
    QString qstrPluginsPath;

#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + UIPLUGINPATH;
#endif


    QDir qPluginsDir(qstrPluginsPath);
    QList<QString> qlLoadedPlugins;
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);

    for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
    {
       QFileInfo qfInfo = qlEntries[iCounter];
       if (!qfInfo.isSymLink())
       {
           AddUiPlugin(p_pContainer, qfInfo, qlLoadedPlugins, pUIRoot);
       }
       else
       {
            WARNING("File " + qfInfo.fileName() + " is a symbolic link and will be ignored.");
       }
    }

    FillNotExistingPlugins(p_pContainer, eWmsPluginTypeUserInterface, pUIRoot);
    pUIRoot->setExpanded(true);
}

void CwmsPluginsIf::AddUiPlugin(CdmObjectContainer* p_pContainer, QFileInfo& qfInfo, QList<QString>& qlLoadedPlugins, QTreeWidgetItem* pFunctionRoot)
{
    QString qstrFile = qfInfo.absoluteFilePath();
    QPluginLoader qLoader(qstrFile);

    if (qLoader.load())
    {
       QObject* pObject = qLoader.instance();
       IwmsGuiPlugin* pPlugin = qobject_cast<IwmsGuiPlugin*>(pObject);

       if (CHKPTR(pPlugin))
       {
          QString qstrPluginName = pPlugin->getName();
          int iVersion = pPlugin->getVersion();
          QString qstrLoadedPlugin = qstrPluginName+"-"+ QString::number(iVersion);
          if (!qlLoadedPlugins.contains(qstrLoadedPlugin))
          {
              qlLoadedPlugins.append(qstrLoadedPlugin);
              CdmObject* pConfiguration = FindPluginConfiguration(p_pContainer, 
                                                                  qstrPluginName, 
                                                                  QString::number(iVersion), 
                                                                  eWmsPluginTypeUserInterface, 
                                                                  qstrFile);

              AddPlugintoView(pConfiguration, QStringList(), pFunctionRoot);
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


CdmObject* CwmsPluginsIf::FindPluginConfiguration(CdmObjectContainer* p_pContainer, QString p_qstrPluginName, QString p_qstrVersion, EwmsPluginType p_Type, QString p_qstrFilename)
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

void CwmsPluginsIf::FillNotExistingPlugins(CdmObjectContainer* p_pContainer, EwmsPluginType p_Type, QTreeWidgetItem* p_pParent)
{
   QString qstrWql = QString("select from \"%1\" where Plugin_Type = %2")
      .arg(p_pContainer->GetKeyname())
      .arg(p_Type);

   CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql, p_pContainer);

   if (CHKPTR(pQuery))
   {
      QList<long> qllResults = pQuery->GetResultList();
      QList<long>::iterator qllIt = qllResults.begin();
      QList<long>::iterator qllItEnd = qllResults.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         long lObjectId = (*qllIt);
         CdmObject* pObject = p_pContainer->FindObjectById(lObjectId);

         if (CHKPTR(pObject) && !m_qstrlFoundUris.contains(pObject->GetUriInternal()))
         {
            AddPlugintoView(pObject, QStringList(), p_pParent, false);
         }
      }
   }
}


void CwmsPluginsIf::ItemChangedSlot(QTreeWidgetItem * p_pItem, int p_iColumn)
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager) && CHKPTR(p_pItem))
    {
        QString qstrUri = p_pItem->data(0, Qt::UserRole).toString();
        CdmObject* pObject = static_cast<CdmObject*>(pManager->GetUriObject(qstrUri));

        if (CHKPTR(pObject))
        {
            if (p_iColumn == 2)
            {
                if (p_pItem->checkState(2) == Qt::Checked)
                {
                    pObject->SetValue("Active", true);

                }
                else
                {
                    pObject->SetValue("Active", false);
                }

                UpdatePluginState(pObject);
            }
            else if (p_iColumn == 3)
            {
                if (p_pItem->checkState(3) == Qt::Checked)
                {
                    pObject->SetValue("Required", true);
                }
                else
                {
                    pObject->SetValue("Required", false);
                }
            }

            pObject->Commit();

        }
    }
}

void CwmsPluginsIf::UpdatePluginState(CdmObject* p_pObject)
{
    bool bActive = false;
    p_pObject->GetValue("Active", bActive);

    if (bActive)
    {
        ActivatePlugin(p_pObject);
    }
    else
    {
        DeactivatePlugin(p_pObject);
    }
}

void CwmsPluginsIf::ActivatePlugin(CdmObject* p_pObject)
{
    int iType = 0;
    QString qstrName;
    QString qstrFilename;
    p_pObject->GetValue("Plugin_Type", iType);
    p_pObject->GetValue("Name", qstrName);
    p_pObject->GetValue("Library", qstrFilename);


    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();

    if (CHKPTR(pPluginManager))
    {
        if (iType == eWmsPluginTypeFunction)
        {
            pPluginManager->LoadFunctionPlugin(qstrFilename, nullptr);
        }
        else if (iType == eWmsPluginTypePrinting)
        {
            pPluginManager->LoadPrintingPlugin(qstrFilename);
        }
        else if (iType == eWmsPluginTypeServer)
        {

        }
        else if (iType == eWmsPluginTypeUserInterface)
        {

        }
        else
        {
            ERR("Unknown Plugin type");
        }
    }
}

void CwmsPluginsIf::DeactivatePlugin(CdmObject* p_pObject)
{
    int iType = 0;
    QString qstrName;
    p_pObject->GetValue("Plugin_Type", iType);
    p_pObject->GetValue("Name", qstrName);
    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();

    if (CHKPTR(pPluginManager))
    {
        if (iType == eWmsPluginTypeFunction)
        {
            pPluginManager->RemoveFunctionPlugin(qstrName);
        }
        else if (iType == eWmsPluginTypePrinting)
        {
             pPluginManager->RemovePrintingPlugin();
        }
        else if (iType == eWmsPluginTypeServer)
        {

        }
        else if (iType == eWmsPluginTypeUserInterface)
        {

        }
        else
        {
            ERR("Unknown Plugin type");
        }
    }
}
