/******************************************************************************
 ** WOGRA Middleware Tools WMS Enterprise Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QCloseEvent>
#include <QCompleter>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QLinkedList>
#include <QMdiArea>
#include <QStandardItemModel>
#include <QMdiSubWindow>
#include <QMenu>
#include <QPluginLoader>
#include <QSettings>
#include <QTextBrowser>
#include <QVariant>
#include <qcombobox.h>
#include <qinputdialog.h>
#include <qlineedit.h>

// WMS Includes
#include "IwmsPluginInterface.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmMessageManager.h"
#include "CwmsJson.h"
#include "CdmPackage.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMember.h"
#include "CdmClassManager.h"
#include "CdmClassGroup.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmSettings.h"

// WMS Basetools Includes
#include "CwmsInitApplication.h"
#include "CwmsFunctionEditor.h"
#include "CwmsAddMemberIf.h"
#include "CwmsServerSchemeManager.h"
#include "CwmsApplicationServices.h"
#include "CwmsWorkflowManager.h"
#include "CwmsSmtpManager.h"
#include "CwmsContext.h"
#include "CwmsSmtpConfiguration.h"
#include "CwmsWorkflowDefinition.h"
#include "CwmsServiceManager.h"
#include "CwmsFormSearch.h"
#include "CwmsFormObject.h"
#include "CwmsFormUserDefined.h"
#include "CwmsFormObjectObjectList.h"
#include "CwmsFormView.h"
#include "CwmsFormStandardObjectList.h"
#include "CwmsFormManager.h"
#include "CwmsFormInteractiveComponent.h"
#include "CwmsApplication.h"
#include "CwmsView.h"
#include "CwmsExportSettings.h"
#include "CwmsImExportManager.h"
#include "CwmsApplicationManager.h"

// WMS GUI Includes
#include "CwmsguiObjectEditorIf.h"
#include "CwmsQmlLibraryEditor.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "CwmsPluginsDlg.h"
#include "CwmsFormInteractiveComponentEditor.h"
#include "CwmsDataAccessConfiguration.h"
#include "CwmsErrorMessenger.h"
#include "CwmsSearchWindow.h"
#include "CwmsEscalationEditorDlg.h"
#include "CwmsWorkflowStepExecutionEditorDlg.h"
#include "CwmsWorkflowStepEditorDlg.h"
#include "CwmsObjectListPropertiesDlg.h"
#include "CwmsMessenger.h"
#include "CwmsSmtpSettings.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsObjectListEditorIf.h"
#include "CwmsWorkflowDefitionEditor.h"
#include "CwmsFormSearchEditor.h"
#include "CwmsFormGenericObjectEditor.h"
#include "CwmsFormObjectObjectListEditor.h"
#include "CwmsFormViewEditor.h"
#include "CwmsFormStandardObjectListEditor.h"
#include "CwmsFunctionEditor.h"
#include "CwmsViewEditor.h"
#include "CwmsApplicationEditor.h"
#include "CwmsQueryResultViewer.h"
#include "CwmsPrintingTemplateProperties.h"
#include "CwmsReportManager.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsQueryEditor.h"
#include "CwmsExportSettingsIf.h"
#include "CwmsUserManagerIf.h"
#include "CwmsJournalViewer.h"
#include "CwmsRightsManagerIf.h"
#include "CwmsObjectListEditorWidgetIf.h"
#include "CwmsErrorIf.h"
#include "CwmsguiApplicationServices.h"
#include "CwmsGuiLdapAccessConfiguration.h"

// WMS QML Includes
#include "CwmsQmlEditor.h"
#include "CwmsQmlApplicationController.h"
#include "CwmsDataSearchDlg.h"

// Own Includes
#include "CwmsScriptingEnvironment.h"
#include "CwmsMiscDataFiller.h"
#include "CwmsRuntime.h"
#include "CwmsSymbolSearch.h"
#include "CwmsLanguagesEditorDlg.h"
#include "CwmsUniversalRightsManager.h"
#include "CwmsAdminMainWindowIf.h"
#include "CwmsClassEditorIf.h"
#include "CwmsAddNewClassIf.h"
#include "CwmsCreateobjectContainerDlg.h"
#include "CwmsGenerateCodeEditor.h"
#include "CwmsGenerateDatabaseCode.h"
#include "CwmsObjectContainerDataFiller.h"
#include "CwmsClassDataFiller.h"
#include "CwmsLogout.h"
#include "ui_cwmscreatobjectlistdlg.h"

#define WMS_DP "wms_dp"
CwmsErrorIf* CwmsAdminMainWindowIf::m_pCwmsErrorIf = nullptr;

/** +-=---------------------------------------------------------Mi 23. Nov 12:19:22 2011----------*
 * @method  CwmsAdminMainWindowIf::CwmsAdminMainWindowIf     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 12:19:22 2011----------*/
CwmsAdminMainWindowIf::CwmsAdminMainWindowIf(QWidget* parent)
   : QMainWindow(parent),
   m_pqlviClasses(nullptr),
   m_pqlviViews(nullptr),
   m_pqlviForms(nullptr),
   m_pqlviReports(nullptr),
   m_pqwEditor(nullptr),
   m_pCwmsUserManager(nullptr),
   m_pRuntime(nullptr),
   m_rpqCurrentWidget(nullptr),
   m_pScriptEnvironment(nullptr)
{
   CwmsApplicationServices::InstallTranslationFiles();
   setupUi(this);
   m_pqpbClearFilter->setVisible(false);
   m_pqaLicenceManager->setVisible(false);
   RestoreWindowsSlot();
   QSettings settings("WOGRA", "WMS");
   settings.beginGroup("wms_dp");
   restoreGeometry(settings.value("geometry").toByteArray());
   restoreState(settings.value("windowState").toByteArray());
   UpdateDockWidgetVisibility();
   CreateErrorDlg();
   FillDialog();
   AddContextMenus();
   CwmsServerSchemeManager cServerSchemeManager;
   cServerSchemeManager.CheckServerScheme();
   connect(CwmsContext::GetContext(), SIGNAL(ApplicationShutdownSignal()), this, SLOT(close()));
   connect(m_pqaLogoutExit, SIGNAL(triggered()), this, SLOT(LogoutAndExitSlot()));
   setEventStoreManager();
}

/** +-=---------------------------------------------------------Mi 16. Mai 16:16:14 2007----------*
 * @method  CwmsAdminMainWindowIf::~CwmsAdminMainWindowIf    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsAdminMainWindowIf                                         *
 *----------------last changed: Wolfgang GraÃŸhof----------------Mi 16. Mai 16:16:14 2007----------*/
CwmsAdminMainWindowIf::~CwmsAdminMainWindowIf()
{
   DELPTR(m_pCwmsUserManager)
   DELPTR(m_pRuntime)
   DELPTR(m_pScriptEnvironment)
}

/** +-=---------------------------------------------------------Mo 23. Sep 08:30:15 2013----------*
 * @method  CwmsAdminMainWindowIf::AddContextMenus           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 08:30:15 2013----------*/
void CwmsAdminMainWindowIf::AddContextMenus()
{
   connect(m_pqlvModel, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   connect(m_pqlvModel, SIGNAL(expanded(const QModelIndex&)),
           this, SLOT(ModelTreeWidgetExpandedSlot()));

   m_pqlvModel->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(m_pqlvUis, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   m_pqlvUis->setContextMenuPolicy(Qt::CustomContextMenu);

   if (m_pqdwPrint)
   {
       connect(m_pqlvPrint, SIGNAL(customContextMenuRequested(const QPoint &)),
               this, SLOT(CustomContextMenuSlot(const QPoint &)));

       m_pqlvPrint->setContextMenuPolicy(Qt::CustomContextMenu);
   }

   connect(m_pqlvApplications, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   m_pqlvApplications->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(m_pqlvViews, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   m_pqlvViews->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(m_pqlvData, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   m_pqlvData->setContextMenuPolicy(Qt::CustomContextMenu);

   connect(m_pqlvWorkflows, SIGNAL(customContextMenuRequested(const QPoint &)), 
           this, SLOT(CustomContextMenuSlot(const QPoint &)));

   m_pqlvWorkflows->setContextMenuPolicy(Qt::CustomContextMenu);
}

void CwmsAdminMainWindowIf::ModelTreeWidgetExpandedSlot()
{
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvModel);
}

/** +-=---------------------------------------------------------So 8. Sep 10:25:26 2013-----------*
 * @method  CwmsAdminMainWindowIf::CreateErrorDlg            // protected                         *
 * @return  void                                             //                                   *
 * @comment Creates the error dlg for displaying error messages in Debug Mode.                    *
 *----------------last changed: --------------------------------So 8. Sep 10:25:26 2013-----------*/
void CwmsAdminMainWindowIf::CreateErrorDlg()
{
   if (!m_pCwmsErrorIf)
   {
      m_pCwmsErrorIf = new CwmsErrorIf();
      CdmLogging::AddAdaptor(m_pCwmsErrorIf);
   }

   new CwmsMessenger(this, statusBar());
}

/** +-=---------------------------------------------------------Mi 16. Mai 16:16:43 2007----------*
 * @method  CwmsAdminMainWindowIf::FillDialog                // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog after application start                                  *
 *----------------last changed: Wolfgang GraÃŸhof----------------Mi 16. Mai 16:16:43 2007----------*/
void CwmsAdminMainWindowIf::FillDialog()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      QLinkedList<QString> qvlDatabases;
      
      pCdmManager->GetSchemeList(qvlDatabases);

      if (qvlDatabases.count() > 1)
      {
         m_pqcbDatabases->addItem("");
      }

      QLinkedList<QString>::iterator qvlIt = qvlDatabases.begin();
      QLinkedList<QString>::iterator qvlItEnd = qvlDatabases.end();

      for (; qvlIt != qvlItEnd; ++ qvlIt)
      {
         QString qstrDatabase = (*qvlIt);
         m_pqcbDatabases->addItem(qstrDatabase);
      }

      if (m_pqcbDatabases->count() == 1)
      {
         m_pqcbDatabases->setCurrentIndex(0);
         DatabaseSelectedSlot();
      }
   }

   UpdateActionState();
   InstallBaseFunctionsToExecutor();

   if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
   {
       m_pqdwPrint->setEnabled(false);
       m_pqaNewReport->setEnabled(false);
       m_pqaReportProperties->setEnabled(false);
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 09:53:48 2012----------*
 * @method  CwmsAdminMainWindowIf::UpdateActionState         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 09:53:48 2012----------*/
void CwmsAdminMainWindowIf::UpdateActionState()
{
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (!qstrDbName.isEmpty())
   {
      EnableActionOnContext();
   }
   else
   {
      DisableAllContentActions();
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 10:03:46 2012----------*
 * @method  CwmsAdminMainWindowIf::EnableActionOnContext     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 10:03:46 2012----------*/
void CwmsAdminMainWindowIf::EnableActionOnContext()
{
   DisableAllContentActions();
   m_pqaCreateClass->setEnabled(true);
   m_pqaNewPackage->setEnabled(true);
   m_pqaCreateObjectList->setEnabled(true);
   m_pqaCreateDbCode->setEnabled(true);
   m_pqaCreateDbQueries->setEnabled(true);
   m_pqaCreateDocumentation->setEnabled(true);
   m_pqaDatabaseJournal->setEnabled(true);
   m_pqaDbRights_2->setEnabled(true);
   m_pqaDeleteDatabase->setEnabled(true);
   m_pqaExportJson->setEnabled(true);
   m_pqaLanguages->setEnabled(true);
   m_pqaNewApplication->setEnabled(true);
   m_pqaNewGenericObjectForm->setEnabled(true);
   m_pqaNewObjectObjectListForm->setEnabled(true);
   m_pqaNewFormLibrary->setEnabled(true);
   m_pqaNewResource->setEnabled(true);
   m_pqaScriptEnvironment->setEnabled(true);


   if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
   {
        m_pqaNewReport->setEnabled(true);
        m_pqaReportProperties->setEnabled(true);
   }


   m_pqaNewStandardObjectListForm->setEnabled(true);
   m_pqaNewUserDefinedForm->setEnabled(true);
   m_pqaNewView->setEnabled(true);
   m_pqaNewViewObjectListForm->setEnabled(true);
   m_pqaNewFormSearch->setEnabled(true);
   m_pqaRefresh->setEnabled(true);
   m_pqaWorkflowTeams->setEnabled(true);
   m_pqaImportDeployment->setEnabled(true);
   
   QTreeWidgetItem* pqlviItem = GetSelectedItem();
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (pqlviItem && !qstrDbName.isEmpty())
   {
      EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());

      if (eType != eWmsTreeItemTypeNone)
      {
         m_pqaEdit_2->setEnabled(true);
         m_pqaDelete->setEnabled(true);
      }

      if (eType == eWmsTreeItemTypeClass)
      {
         m_pqaGenerateCode->setEnabled(true);
         m_pqaCreateObjectList->setEnabled(true);

      }
      else if (eType == eWmsTreeItemTypeContainer)
      {
         m_pqaExport->setEnabled(true);
         m_pqaDeleteAllObjects->setEnabled(true);
         m_pqaObjectListJournal->setEnabled(true);
         m_pqaObjectListProperties->setEnabled(true);
      }
      else if (eType == eWmsTreeItemTypeReport)
      {
         m_pqaReportProperties->setEnabled(true);
      }
      else if (eType == eWmsTreeItemTypeApplication)
      {
         m_pqaExecuteApplication->setEnabled(true);
      }
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 09:54:36 2012----------*
 * @method  CwmsAdminMainWindowIf::DisableAllContentActions  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 09:54:36 2012----------*/
void CwmsAdminMainWindowIf::DisableAllContentActions()
{
    if (!CwmsContext::GetContext()->IsTimedOut())
    {
       m_pqaCreateClass->setEnabled(false);
       m_pqaNewPackage->setEnabled(false);
       m_pqaCreateDbCode->setEnabled(false);
       m_pqaCreateDbQueries->setEnabled(false);
       m_pqaCreateDocumentation->setEnabled(false);
       m_pqaCreateObjectList->setEnabled(false);
       m_pqaDatabaseJournal->setEnabled(false);
       m_pqaDbRights_2->setEnabled(false);
       m_pqaDelete->setEnabled(false);
       m_pqaDeleteAllObjects->setEnabled(false);
       m_pqaDeleteDatabase->setEnabled(false);
       m_pqaEdit_2->setEnabled(false);
       m_pqaExecuteApplication->setEnabled(false);
       m_pqaExport->setEnabled(false);
       m_pqaExportJson->setEnabled(false);
       m_pqaGenerateCode->setEnabled(false);
       m_pqaLanguages->setEnabled(false);
       m_pqaNewApplication->setEnabled(false);
       m_pqaNewGenericObjectForm->setEnabled(false);
       m_pqaNewObjectObjectListForm->setEnabled(false);
       m_pqaNewFormLibrary->setEnabled(false);
       m_pqaNewResource->setEnabled(false);
       m_pqaScriptEnvironment->setEnabled(false);


       if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
       {
            m_pqaNewReport->setEnabled(false);
            m_pqaReportProperties->setEnabled(false);
       }

       m_pqaNewStandardObjectListForm->setEnabled(false);
       m_pqaNewUserDefinedForm->setEnabled(false);
       m_pqaNewView->setEnabled(false);
       m_pqaNewViewObjectListForm->setEnabled(false);
       m_pqaObjectListJournal->setEnabled(false);
       m_pqaRefresh->setEnabled(false);
       m_pqaReportProperties->setEnabled(false);
       m_pqaNewFormSearch->setEnabled(false);
       m_pqaWorkflowTeams->setEnabled(false);
       m_pqaObjectListProperties->setEnabled(false);
    }
}

/** +-=---------------------------------------------------------Mi 16. Mai 16:49:11 2007----------*
 * @method  CwmsAdminMainWindowIf::DatabaseSelectedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user selected a new database. It fills the            *
 *          listview with the content of the database.                                            *
 *----------------last changed: Wolfgang GraÃŸhof----------------Mi 16. Mai 16:49:11 2007----------*/
void CwmsAdminMainWindowIf::DatabaseSelectedSlot()
{
   ClearEditor();
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (!qstrDbName.isEmpty())
   {
      FillSchemeContent(qstrDbName);
   }
}

/** +-=---------------------------------------------------------So 8. Sep 20:53:19 2013-----------*
 * @method  CwmsAdminMainWindowIf::ClearEditor               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 8. Sep 20:53:19 2013-----------*/
void CwmsAdminMainWindowIf::ClearEditor()
{
   m_pqMdiArea->closeAllSubWindows();
   m_pqlvApplications->clear();
   m_pqlvModel->clear();
   m_pqlvData->clear();

   if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
   {
        m_pqlvPrint->clear();
   }

   m_pqlvUis->clear();
   m_pqlvWorkflows->clear();
   m_pqlvViews->clear();
   m_pqcbLanguage->clear();
}

/** +-=---------------------------------------------------------Di 14. Aug 14:21:08 2012----------*
 * @method  CwmsAdminMainWindowIf::RefreshClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 14:21:08 2012----------*/
void CwmsAdminMainWindowIf::RefreshClickedSlot()
{
   DatabaseSelectedSlot();
}

/** +-=---------------------------------------------------------Mi 16. Mai 16:51:36 2007----------*
 * @method  CwmsAdminMainWindowIf::FillSchemeContent             // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDbName                             //                                   *
 * @comment This method loads the selected db and fills the conntent to the listview.             *
 *----------------last changed: Wolfgang Graßhof----------------Mi 16. Mai 16:51:36 2007----------*/
void CwmsAdminMainWindowIf::FillSchemeContent(QString p_qstrDbName)
{
   CdmMessageManager::StartAsyncMessageCollection();
   int iSteps = 0;
   CdmMessageManager::StartProgressBar("LoadScheme", tr("Lade Schema"), tr("Beginne Schema zu laden"), 9);
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   m_pqcbLanguage->clear();
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      if (pCdmManager->GetCurrentScheme())
      {
        CwmsContext::GetContext()->GetServiceManager()->DeleteAllServices();
      }

      pCdmManager->RemoveAllLocalSchemes();
      pCdmManager->LoadScheme(p_qstrDbName);
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_qstrDbName);
      
      if (CHKPTR(pCdmClassManager))
      {
          CdmMessageManager::SetProgress("LoadScheme", tr("Lade Reports"), ++iSteps);
          FillReports();
          CdmMessageManager::SetProgress("LoadScheme", tr("Lade Sichten"), ++iSteps);
          FillViews();
          CwmsFormManager formManager;
          Q_UNUSED(formManager)
          CdmMessageManager::SetProgress("LoadScheme", tr("Aktualisiere Plugins"), ++iSteps);
         CwmsContext::GetContext()->GetPluginManager()->RefreshPlugins(this);

         if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
         {
             m_pqdwPrint->setEnabled(false);
             m_pqaNewReport->setEnabled(false);
             m_pqaReportProperties->setEnabled(false);
         }
         else
         {
             m_pqdwPrint->setEnabled(true);
             m_pqaNewReport->setEnabled(true);
             m_pqaReportProperties->setEnabled(true);
         }

         CwmsImExportManager cManager;
         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Klassen"), ++iSteps);
         FillClasses(pCdmClassManager);
         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Objectcontainer"), ++iSteps);
         CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked());
         CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvData);

         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Formulare"), ++iSteps);
         FillForms();
         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Applikationen"), ++iSteps);
         FillApplications();
         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Sprachen"), ++iSteps);
         FillLanguages();
         CdmMessageManager::SetProgress("LoadScheme", tr("Fülle Workflows"), ++iSteps);
         FillWorkflows();

         if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
         {
             m_pqdwPrint->setEnabled(false);
             m_pqaNewReport->setEnabled(false);
             m_pqaReportProperties->setEnabled(false);
         }
         else
         {
             m_pqdwPrint->setEnabled(true);
             m_pqaNewReport->setEnabled(true);
             m_pqaReportProperties->setEnabled(true);
         }
      }

      SubscribeEventMethods(pCdmClassManager);
   }

   EnableActionOnContext();
   QApplication::restoreOverrideCursor();
   CdmMessageManager::CloseProgressBar("LoadScheme");
   CdmMessageManager::EndAndShowAsyncMessageCollection();
}

void CwmsAdminMainWindowIf::SubscribeEventMethods(CdmClassManager *pCdmClassManager)
{
    QLinkedList<CdmClass*> qlClasses;
    pCdmClassManager->GetClassList(qlClasses);

    QLinkedList<CdmClass*>::iterator qlItStart = qlClasses.begin();
    QLinkedList<CdmClass*>::iterator qlItEnd = qlClasses.end();

    for(; qlItStart != qlItEnd; ++qlItStart)
    {
        CdmClass *pClass = (*qlItStart);
        CdmClassMethod *pClassMethod = pClass->GetMethod("onDomainEvent");
        if(pClassMethod)
        {
            if(pClassMethod->IsStatic())
            {
                if(!getEventStoreManager()->getSubscribers().contains(pClassMethod))
                {
                    getEventStoreManager()->subscribe(pClassMethod);
                }
            }
        }
        else
        {
            WARNING("ClassMethod is nullptr.")
        }
    }
}

/** +-=---------------------------------------------------------Mi 5. Sep 13:33:50 2012-----------*
 * @method  CwmsAdminMainWindowIf::FillLanguages             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 13:33:50 2012-----------*/
void CwmsAdminMainWindowIf::FillLanguages()
{
    CwmsMiscDataFiller::FillLanguages(m_pqcbLanguage);
}

/** +-=---------------------------------------------------------Do 30. Aug 14:42:31 2012----------*
 * @method  CwmsAdminMainWindowIf::FillApplications          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:42:31 2012----------*/
void CwmsAdminMainWindowIf::FillApplications()
{
   CwmsMiscDataFiller::FillApplications(m_pqlvApplications);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvApplications);
}

/** +-=---------------------------------------------------------Do 23. Aug 16:57:30 2012----------*
 * @method  CwmsAdminMainWindowIf::FillForms                 // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 16:57:30 2012----------*/
void CwmsAdminMainWindowIf::FillForms()
{
   CwmsMiscDataFiller::FillForms(m_pqlvUis);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvUis);
}

/** +-=---------------------------------------------------------Do 23. Aug 16:55:48 2012----------*
 * @method  CwmsAdminMainWindowIf::FillReports               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 16:55:48 2012----------*/
void CwmsAdminMainWindowIf::FillReports()
{
   CwmsReportManager cReportManager; //will be done for creating the datastructure
   CwmsMiscDataFiller::FillReports(m_pqlvPrint);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvPrint);
}

/** +-=---------------------------------------------------------Di 14. Aug 14:00:16 2012----------*
 * @method  CwmsAdminMainWindowIf::FillViews                 // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 14:00:16 2012----------*/
void CwmsAdminMainWindowIf::FillViews()
{
   CwmsMiscDataFiller::FillViews(m_pqlvViews);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvViews);
}


/** +-=---------------------------------------------------------Mi 24. Okt 15:29:28 2012----------*
 * @method  CwmsAdminMainWindowIf::FillWorkflows             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 15:29:28 2012----------*/
void CwmsAdminMainWindowIf::FillWorkflows()
{
   CwmsMiscDataFiller::FillWorkflows(m_pqlvWorkflows);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvWorkflows);
}


/** +-=---------------------------------------------------------Di 14. Aug 13:56:09 2012----------*
 * @method  CwmsAdminMainWindowIf::FillClasses               // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 13:56:09 2012----------*/
void CwmsAdminMainWindowIf::FillClasses(CdmClassManager* p_pCdmClassManager)
{
   if (CHKPTR(p_pCdmClassManager))
   {
      m_pqlvModel->clear();
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvModel);
      pItem->setText(0, tr("Klassen"));
      CwmsClassDataFiller::FillClasses(p_pCdmClassManager, pItem, false, m_pqchbShowTechnicalItems->isChecked());
      CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvModel);
      m_pqcbClassFilter->clear();
      disconnect(m_pqcbClassFilter, SIGNAL(currentTextChanged(QString)), this, SLOT(ClassFilterChangedSlot()));
      CwmsClassDataFiller::FillClassesToComboBox(m_pqcbClassFilter, false, true, m_pqchbShowTechnicalItems->isChecked());
      connect(m_pqcbClassFilter, SIGNAL(currentTextChanged(QString)), this, SLOT(ClassFilterChangedSlot()));
	  m_pqlvModel->sortItems(0, Qt::AscendingOrder);
	  
      QCompleter* pQCompleter = m_pqcbClassFilter->completer();

      if (pQCompleter)
      {
          pQCompleter->setCompletionMode(QCompleter::PopupCompletion);
          pQCompleter->setMaxVisibleItems(30);
          pQCompleter->setFilterMode(Qt::MatchContains);
      }
   }
}

/** +-=---------------------------------------------------------Di 14. Aug 13:51:16 2012----------*
 * @method  CwmsAdminMainWindowIf::FillObjectLists           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QTreeWidgetItem* p_pqtwClass                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 13:51:16 2012----------*/
void CwmsAdminMainWindowIf::FillObjectLists(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass)
{
   CwmsObjectContainerDataFiller::FillObjectContainersToClass(p_pCdmClass, p_pqtwClass);
}

/** +-=---------------------------------------------------------Fr 20. Sep 08:59:04 2013----------*
 * @method  CwmsAdminMainWindowIf::DbContentSelectedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user collected database content. it opens the         *
 *          selected item in the edit frame.                                                      *
 *----------------last changed: --------------------------------Fr 20. Sep 08:59:04 2013----------*/
void CwmsAdminMainWindowIf::SchemeContentSelectedSlot()
{
   BODY_TRY
   m_rpqCurrentWidget = static_cast<QTreeWidget*> (sender());
   QTreeWidgetItem* p_pItem = GetSelectedItem();
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (p_pItem && !qstrDbName.isEmpty())
   {
      EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(p_pItem->data(1, Qt::UserRole).toInt());

      if (eType == eWmsTreeItemTypeContainer) // a objectlist is marked
      {
         OpenContainerEditor(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeView) // a class is marked
      {
         OpenViewViewer(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeClass)
      {
         OpenClassEditor(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeApplication)
      {
         OpenApplicationEditor();
      }
   }

   if (!CwmsContext::GetContext()->IsTimedOut())
   {
        EnableActionOnContext();
   }
   BODY_CATCH
}

/** +-=---------------------------------------------------------Di 11. Sep 18:42:00 2012----------*
 * @method  CwmsAdminMainWindowIf::EditSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:42:00 2012----------*/
void CwmsAdminMainWindowIf::EditSlot()
{
   QObject* pObject = sender();
   QString qstrClassName = pObject->metaObject()->className();

   if (qstrClassName == "QTreeWidget")
   {
      m_rpqCurrentWidget = static_cast<QTreeWidget*> (sender());
   }

   QTreeWidgetItem* pItem = GetSelectedItem();
   EditSlot(pItem);
}

/** +-=---------------------------------------------------------Fr 20. Sep 08:08:12 2013----------*
 * @method  CwmsAdminMainWindowIf::EditSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 08:08:12 2013----------*/
void CwmsAdminMainWindowIf::EditSlot(QTreeWidgetItem* p_pItem)
{
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (p_pItem && !qstrDbName.isEmpty())
   {
      EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(p_pItem->data(1, Qt::UserRole).toInt());

      if (eType == eWmsTreeItemTypeContainer) // a objectlist is marked
      {
         OpenContainerEditor(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeView) // a class is marked
      {
         EditViewSlot();
      }
      else if (eType == eWmsTreeItemTypeClass)
      {
         OpenClassEditor(p_pItem);
      }
      else if (eType == eWmsTreeItemTypeApplication)
      {
         OpenApplicationEditor();
      }
      else if (eType == eWmsTreeItemTypeFormGenericObject)
      {
         EditGenericObjectFormSlot();            
      }
      else if (eType == eWmsTreeItemTypeFormObjectObjectList)
      {
         EditObjectObjectListFormSlot();
      }
      else if (eType == eWmsTreeItemTypeFormStandardObjectList)
      {
         EditStandardObjectListFormSlot();
      }
      else if (eType == eWmsTreeItemTypeFormUserDefined)
      {
         EditUserDefinedFormSlot();
      }
      else if (eType == eWmsTreeItemTypeFormViewObjectList)
      {
         EditViewObjectListFormSlot();
      }
      else if (eType == eWmsTreeItemTypeMember)
      {
         EditMemberSlot();
      }
      else if (eType == eWmsTreeItemTypeView)
      {
         EditViewSlot();
      }
      else if (eType == eWmsTreeItemTypeReport)
      {
         EditReportSlot();
      }
      else if (eType == eWmsTreeItemTypeFormSearch)
      {
         EditSearchFormSlot();
      }
      else if (eType == eWmsTreeItemTypeWorkflow)
      {
         EditWorkflowSlot();
      }
      else if (eType == eWmsTreeItemTypePackage)
      {
         EditPackageSlot();
      }
	  else if (eType == eWmsTreeItemTypeFunction)
	  {
		  EditFunctionSlot();
	  }
	  else if (eType == eWmsTreeItemTypeMember)
	  {
		  EditMemberSlot();
	  }
      else if (eType == eWmsTreeItemTypeFormLibrary)
      {
          EditLibrarySlot();
      }
      else if (eType == eWmsTreeItemTypeResource)
      {
          EditResourceSlot();
      }
      else if (eType == eWmsTreeItemTypeInteractiveComponentForm)
      {
          EditInteractiveComponentFormSlot();
      }
      else if (eType == eWmsTreeItemTypeSingletonClass)
      {
          EditSingleton();
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:42:10 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:42:10 2012----------*/
void CwmsAdminMainWindowIf::DeleteSlot()
{
   QList<QTreeWidgetItem*> qlItems = GetSelectedItems();
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (qlItems.count() > 0 && !qstrDbName.isEmpty())
   {
      if (CdmMessageManager::Ask(tr("Wirklich löschen?"),
         tr("Die gewählten Objekte werden unwiderruflich gelöscht."
         "Wollen Sie das wirklich?")))
      {
          for (int iPos = 0; iPos < qlItems.count(); ++iPos)
          {
         EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(qlItems[iPos]->data(1, Qt::UserRole).toInt());

         if (eType == eWmsTreeItemTypeContainer) // a objectlist is marked
         {
            DeleteObjectListSlot(qlItems[iPos]);
         }
         else if (eType == eWmsTreeItemTypeView) // a class is marked
         {
            DeleteViewSlot();
         }
         else if (eType == eWmsTreeItemTypeClass)
         {
            DeleteClassSlot();
         }
         else if (eType == eWmsTreeItemTypeApplication)
         {
            DeleteApplicationSlot();
         }
         else if (eType == eWmsTreeItemTypeFormGenericObject)
         {
            DeleteGenericObjectFormSlot();            
         }
         else if (eType == eWmsTreeItemTypeFormObjectObjectList)
         {
            DeleteObjectObjectListFormSlot();
         }
         else if (eType == eWmsTreeItemTypeFormStandardObjectList)
         {
            DeleteStandardObjectListFormSlot();
         }
         else if (eType == eWmsTreeItemTypeFormUserDefined)
         {
            DeleteUserDefinedFormSlot();
         }
         else if (eType == eWmsTreeItemTypeFormViewObjectList)
         {
            DeleteViewObjectListFormSlot();
         }
         else if (eType == eWmsTreeItemTypeMember)
         {
            DeleteMemberSlot();
         }
         else if (eType == eWmsTreeItemTypeFunction)
         {
            DeleteFunctionSlot();
         }
         else if (eType == eWmsTreeItemTypeView)
         {
            DeleteViewSlot();
         }
         else if (eType == eWmsTreeItemTypeReport)
         {
            DeleteReportSlot();
         }
         else if (eType == eWmsTreeItemTypeFormSearch)
         {
            DeleteSearchFormSlot();
         }
         else if (eType == eWmsTreeItemTypeWorkflow)
         {
            DeleteWorkflowSlot();
         }
         else if (eType == eWmsTreeItemTypePackage)
         {
            DeletePackageSlot();
         }
         else if (eType == eWmsTreeItemTypeFormLibrary)
         {
             DeleteLibrarySlot();
         }
         else if (eType == eWmsTreeItemTypeResource)
         {
             DeleteResourceSlot();
         }
         else if (eType == eWmsTreeItemTypeInteractiveComponentForm)
         {
             DeleteInteractiveComponentFormSlot();
         }
          }
      }
   }
}

/** +-=---------------------------------------------------------Fr 31. Aug 09:58:50 2012----------*
 * @method  CwmsAdminMainWindowIf::OpenClassEditor           // private                           *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Aug 09:58:50 2012----------*/
void CwmsAdminMainWindowIf::OpenClassEditor(QTreeWidgetItem* p_pItem)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager && p_pItem && pCdmManager->GetCurrentScheme())
   {
	  CdmClass* pCdmClass = GetSelectedClass();
      if (pCdmClass)
      {
        OpenClassEditor(pCdmClass);
      }
   }
}

/** +-=---------------------------------------------------------Mo 23. Sep 19:56:07 2013----------*
 * @method  CwmsAdminMainWindowIf::OpenClassEditor           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pClass                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 19:56:07 2013----------*/
void CwmsAdminMainWindowIf::OpenClassEditor(CdmClass* p_pClass)
{
  if (CHKPTR(p_pClass))
  {
     if (!FindAndSetSubWindow(p_pClass->GetUriInternal()))
     {
        m_pqtbInfo->setText(p_pClass->GetInfo());
        CwmsClassEditorIf* pEditor = new CwmsClassEditorIf(p_pClass, m_pqMdiArea);
        connect(pEditor, SIGNAL(ClassModifiedSignal()), this, SLOT(ClassModifiedSlot()));
        pEditor->SetMainWindow(this);
        QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

        if (CHKPTR(pSubWindow))
        {
           pSubWindow->setWindowTitle(tr("Klasse ") + p_pClass->GetKeyname());
           pSubWindow->setObjectName(p_pClass->GetUriInternal());
        }
     }
  }
}

/** +-=---------------------------------------------------------Di 17. Sep 18:58:19 2013----------*
 * @method  CwmsAdminMainWindowIf::FindAndSetSubWindow       // private                           *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrUri                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 17. Sep 18:58:19 2013----------*/
bool CwmsAdminMainWindowIf::FindAndSetSubWindow(QString p_qstrUri)
{
   bool bRet = false;
   QMdiSubWindow* pWindow = FindSubWindowByUri(p_qstrUri);

   if (pWindow)
   {
      bRet = true;
      m_pqMdiArea->setActiveSubWindow(pWindow);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Di 17. Sep 18:48:29 2013----------*
 * @method  CwmsAdminMainWindowIf::FindSubWindowByUri        // private                           *
 * @return  QMdiSubWindow*                                   //                                   *
 * @param   QString p_qstrUri                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 17. Sep 18:48:29 2013----------*/
QMdiSubWindow* CwmsAdminMainWindowIf::FindSubWindowByUri(QString p_qstrUri)
{
   QMdiSubWindow* pSubWindow = nullptr;

   if (!p_qstrUri.isEmpty())
   {
      QList<QMdiSubWindow*> qlSubWindows = m_pqMdiArea->subWindowList();

      for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
      {
         QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];

         if (pTempWindow->objectName() == p_qstrUri)
         {
            pSubWindow = pTempWindow;
            break;
         }
      }
   }
   
   return pSubWindow;
}


/** +-=---------------------------------------------------------Fr 13. Sep 15:19:15 2013----------*
 * @method  CwmsAdminMainWindowIf::AddMdiWindow              // private                           *
 * @return  QMdiSubWindow*                                   //                                   *
 * @param   QWidget* p_pWidget                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Sep 15:19:15 2013----------*/
QMdiSubWindow* CwmsAdminMainWindowIf::AddMdiWindow(QWidget* p_pWidget)
{
   QMdiSubWindow* pSubWindow = nullptr;
    
   if (CHKPTR(p_pWidget))
   {
      pSubWindow = m_pqMdiArea->addSubWindow(p_pWidget);

      if (CHKPTR(pSubWindow))
      {
         p_pWidget->show();
      }
   }

   return pSubWindow;
}

/** +-=---------------------------------------------------------Fr 31. Aug 09:57:00 2012----------*
 * @method  CwmsAdminMainWindowIf::OpenViewViewer            // private                           *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Aug 09:57:00 2012----------*/
void CwmsAdminMainWindowIf::OpenViewViewer(QTreeWidgetItem* p_pItem)
{
   if (p_pItem)
   {
      CwmsViewManager cCViewManager;
      CwmsView cView = cCViewManager.GetView(p_pItem->text(0));

      if (cView.IsValid())
      {
         if (!FindAndSetSubWindow(cView.GetUriInternal()))
         {
            m_pqtbInfo->setText(cView.GetComment());
            CwmsQueryResultViewer* pEditor = new CwmsQueryResultViewer(m_pqMdiArea);

            if (cView.IsWql())
            {
                pEditor->SetQuery(cView.GetViewCommand());
            }
            else if (cView.IsModel())
            {
                pEditor->SetModel(cView.GetModel());
            }

            QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);    

            if (CHKPTR(pSubWindow))
            {
               pSubWindow->setWindowTitle(tr("Sicht ") + cView.GetName());
               pSubWindow->setObjectName(cView.GetUriInternal());
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 31. Aug 09:52:38 2012----------*
 * @method  CwmsAdminMainWindowIf::OpenContainerEditor      // private                           *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Aug 09:52:38 2012----------*/
void CwmsAdminMainWindowIf::OpenContainerEditor(QTreeWidgetItem* p_pItem)
{
   if (CHKPTR(p_pItem))
   {
      QString qstrKeyname = p_pItem->text(0);
      CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainerEmpty(qstrKeyname);

      if (CHKPTR(pContainer))
      {
         OpenObjectContainerEditor(pContainer);
      }
   }
}

/** +-=---------------------------------------------------------Mo 23. Sep 19:57:59 2013----------*
 * @method  CwmsAdminMainWindowIf::OpenObjectContainerEditor // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 19:57:59 2013----------*/
void CwmsAdminMainWindowIf::OpenObjectContainerEditor(CdmObjectContainer* p_pContainer)
{
   if (CHKPTR(p_pContainer))
      {
         int iObjectCount = p_pContainer->CountObjectsOnDb();

         if (iObjectCount < 100)
         {
            OpenContainerEditor(p_pContainer);
         }
         else
         {
            OpenObjectListSearch(p_pContainer);
         }
   }
}

/** +-=---------------------------------------------------------Di 15. Jan 14:51:29 2013----------*
 * @method  CwmsAdminMainWindowIf::OpenObjectListSearch      // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 15. Jan 14:51:29 2013----------*/
void CwmsAdminMainWindowIf::OpenObjectListSearch(CdmObjectContainer* p_pList)
{
   if (CHKPTR(p_pList))
   {
      if (!FindAndSetSubWindow("Suche " + p_pList->GetUriInternal()))
      {
         CwmsSearchWindow* pSearch = new CwmsSearchWindow(m_pqMdiArea);
         m_pqtbInfo->setText(p_pList->GetInfo());
         pSearch->show();
         pSearch->FillDialog(p_pList);

         QMdiSubWindow* pSubWindow = AddMdiWindow(pSearch);    

         if (CHKPTR(pSubWindow))
         {
            pSubWindow->setWindowTitle(tr("Suche ") + p_pList->GetKeyname());
            pSubWindow->setObjectName("Suche " + p_pList->GetUriInternal());
         }
      }
   }
}

/** +-=---------------------------------------------------------Di 15. Jan 14:49:40 2013----------*
 * @method  CwmsAdminMainWindowIf::OpenContainerEditor      // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 15. Jan 14:49:40 2013----------*/
void CwmsAdminMainWindowIf::OpenContainerEditor(CdmObjectContainer* p_pList)
{
   if (CHKPTR(p_pList))
   {
      if (!FindAndSetSubWindow(p_pList->GetUriInternal()))
      {
         CwmsObjectListEditorWidgetIf* pEditor = new CwmsObjectListEditorWidgetIf(p_pList, m_pqMdiArea);
         m_pqtbInfo->setText(p_pList->GetInfo());
         pEditor->SetShowEditButton(true);
         pEditor->FillDialog();
         QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);    

         if (CHKPTR(pSubWindow))
         {
            pSubWindow->setWindowTitle(tr("Objektcontainer ") + p_pList->GetKeyname());
            pSubWindow->setObjectName(p_pList->GetUriInternal());
         }
      }
   }
}

/** +-=---------------------------------------------------------Di 14. Aug 11:30:27 2012----------*
 * @method  CwmsAdminMainWindowIf::GetSelectedItem           // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 11:30:27 2012----------*/
QTreeWidgetItem* CwmsAdminMainWindowIf::GetSelectedItem()
{
   QTreeWidgetItem* pItem = nullptr;

   if (m_rpqCurrentWidget)
   {
      pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_rpqCurrentWidget);
   }

   return pItem;
}

QList<QTreeWidgetItem*> CwmsAdminMainWindowIf::GetSelectedItems()
{
   QList<QTreeWidgetItem*> qlItems;

   if (m_rpqCurrentWidget)
   {
      qlItems = m_rpqCurrentWidget->selectedItems();
   }

   return qlItems;
}

/** +-=---------------------------------------------------------So 18. Mai 13:19:22 2008----------*
 * @method  CwmsAdminMainWindowIf::GetSelectedClass          // public                            *
 * @return  CdmClass*                                        //                                   *
 * @comment returns the selected class in listview. or nullptr of no class is selected.              *
 *----------------last changed: --------------------------------So 18. Mai 13:19:22 2008----------*/
CdmClass* CwmsAdminMainWindowIf::GetSelectedClass()
{
   CdmClass* pCdmClass = nullptr;
   CdmPackage* pPackage = nullptr;
   QTreeWidgetItem* pqlviItem = GetSelectedItem();
   QString qstrDbName = m_pqcbDatabases->currentText();
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
   
	   if (pqlviItem && !qstrDbName.isEmpty())
	   {
          EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());

		  if (eType == eWmsTreeItemTypeClass) 
		  {
              int iClassId = pqlviItem->data(0, Qt::UserRole).toInt();



			 CdmClassManager* pClassManager = pCdmManager->GetClassManager();

			 if (CHKPTR(pClassManager))
			 {
                 pCdmClass = pClassManager->FindClassById(iClassId);
			 }
         }
      }
   }
   
   return pCdmClass;
}

/** +-=---------------------------------------------------------So 18. Mai 13:21:45 2008----------*
 * @method  CwmsAdminMainWindowIf::GetSelectedObjectList     // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment returns the selected Objectlist or nullptr if no one is selected.                        *
 *----------------last changed: --------------------------------So 18. Mai 13:21:45 2008----------*/
CdmObjectContainer* CwmsAdminMainWindowIf::GetSelectedObjectList()
{
   QTreeWidgetItem* pqlviItem = GetSelectedItem();
   return GetContainerFromItem(pqlviItem);
}

CdmObjectContainer* CwmsAdminMainWindowIf::GetContainerFromItem(QTreeWidgetItem* p_pItem)
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
   QString qstrDbName = m_pqcbDatabases->currentText();

   if (p_pItem && !qstrDbName.isEmpty())
   {

      EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(p_pItem->data(1, Qt::UserRole).toInt());

      if (eType == eWmsTreeItemTypeContainer) // a objectlist is marked
      {
         QString qstrKeyname = p_pItem->text(0);

         if (CHKPTR(pCdmManager))
         {
            pContainer = pCdmManager->GetObjectContainer(qstrDbName, qstrKeyname);
         }
      }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Do 17. Mai 00:17:31 2007----------*
 * @method  CwmsAdminMainWindowIf::closeEvent                // protected                         *
 * @return  void                                             //                                   *
 * @param   QCloseEvent* p_pqCloseEvent                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang GraÃŸhof----------------Do 17. Mai 00:17:31 2007----------*/
void CwmsAdminMainWindowIf::closeEvent(QCloseEvent* p_pqCloseEvent)
{
    ClearEditor();

    if (!CwmsContext::GetContext()->IsTimedOut())
    {
        CdmSessionManager::Logout();
    }

   QSettings settings("WOGRA", "WMS");
   settings.beginGroup(WMS_DP);
   settings.setValue("geometry", saveGeometry());
   settings.setValue("windowState", saveState());

   QMainWindow::closeEvent(p_pqCloseEvent);
}

CdmClassManager* CwmsAdminMainWindowIf::GetCurrentClassManager()
{
    CdmClassManager* pCdmClassManager = nullptr;
    QString qstrDbName = m_pqcbDatabases->currentText();

    if (!qstrDbName.isEmpty())
    {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         pCdmClassManager = pCdmManager->GetClassManager(qstrDbName);
      }
    }

    return pCdmClassManager;
}

/** +-=---------------------------------------------------------So 18. Mai 13:14:03 2008----------*
 * @method  CwmsAdminMainWindowIf::CreateClassSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:14:03 2008----------*/
void CwmsAdminMainWindowIf::CreateClassSlot()
{
    CdmClassManager* pCdmClassManager = GetCurrentClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        CwmsAddNewClassIf* pCwmsAddNewClassIf = new CwmsAddNewClassIf(this);

        if (pCwmsAddNewClassIf->exec() == QDialog::Accepted)
        {
            QString qstrCaption = pCwmsAddNewClassIf->m_pqleCaption->text();
            QString qstrKeyname = pCwmsAddNewClassIf->m_pqleKeyname->text();
            QString qstrComment = pCwmsAddNewClassIf->m_pqteComment->toPlainText();

            if (!qstrCaption.isEmpty() && !qstrComment.isEmpty() && !qstrKeyname.isEmpty())
            {
               CdmClass* pCdmClass = pCdmClassManager->CreateClass(qstrKeyname);

               if (CHKPTR(pCdmClass))
               {
                  pCdmClass->SetCaption(qstrCaption);
                  pCdmClass->SetComment(qstrComment);
                  pCdmClass->Commit();

                  FillClasses(pCdmClassManager);
                  m_pqcbClassFilter->addItem(pCdmClass->GetKeyname(), pCdmClass->GetUriInternal());
                  OpenClassEditor(pCdmClass);
               }
            }
         }

        delete pCwmsAddNewClassIf;
    }
}

/** +-=---------------------------------------------------------So 18. Mai 13:14:13 2008----------*
 * @method  CwmsAdminMainWindowIf::CreateDatabaseSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:14:13 2008----------*/
void CwmsAdminMainWindowIf::CreateDatabaseSlot()
{
   QString qstrDbName = QInputDialog::getText(this, tr("Schema anlegen"), 
                                              tr("Bitte geben Sie den Namen des Schemas ein."), 
                                              QLineEdit::Normal);

   if (!qstrDbName.isEmpty())
   {
      CdmMessageManager::StartAsyncMessageCollection();
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
		  pCdmManager->RemoveAllLocalSchemes();
         if (pCdmManager->CreateScheme(qstrDbName) > 0)
         {
            CwmsApplicationServices::InitCurrentScheme();
            m_pqcbDatabases->addItem(qstrDbName);
            ClearEditor();
            m_pqcbDatabases->setCurrentText(qstrDbName);
            FillSchemeContent(qstrDbName);
         }
         else
         {
            CdmMessageManager::information(tr("Schema konnte nicht angelegt werden"), 
                                     tr("Das Schema konnte nicht angelegt werden. (Interner Fehler)"));
         }
      }

      CdmMessageManager::EndAndShowAsyncMessageCollection();
   }

}

/** +-=---------------------------------------------------------So 18. Mai 13:14:24 2008----------*
 * @method  CwmsAdminMainWindowIf::CreateObjectListSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:14:24 2008----------*/
void CwmsAdminMainWindowIf::CreateObjectListSlot()
{
   CdmObjectContainer* pContainer = CwmsCreateObjectContainerDlg::CreateObjectContainer(this);

   if (pContainer)
   {
      ClassFilterChangedSlot();
      OpenObjectContainerEditor(pContainer);
   }
}

/** +-=---------------------------------------------------------So 18. Mai 13:14:36 2008----------*
 * @method  CwmsAdminMainWindowIf::DeleteClassSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:14:36 2008----------*/
void CwmsAdminMainWindowIf::DeleteClassSlot()
{
   CdmClass* pCdmClass = GetSelectedClass();

   if (pCdmClass)
   {
      CdmClassManager* pCdmClassManager = pCdmClass->GetClassManager();

      if (CHKPTR(pCdmClassManager))
      {
         CloseClassRelatedUis(pCdmClass);

        if (pCdmClassManager->DeleteClass(pCdmClass) < 0)
        {
           CdmMessageManager::information(tr("Klasse konnte nicht gelöscht werden"),
                                    tr("Die Klasse konnte nicht gelöscht werden.\n "
                                       "Stellen Sie sicher dass diese Klasse keine Objektcontainer besitzt und\n"
                                       "nirgends als Basisklasse verwendet wurde."));

        }
        else
        {
           QTreeWidgetItem* pqlviItem = GetSelectedItem();
           delete pqlviItem;
           CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked());
        }

      }
   }
   else
   {
      CdmMessageManager::information(tr("Keine Klasse ausgewählt"), 
                               tr("Sie haben kein Schema ausgewählt. Löschung kann nicht durchgeführt werden."));
   }
}

void CwmsAdminMainWindowIf::CloseClassRelatedUis(CdmClass* p_pClass)
{
    QList<QMdiSubWindow*> qlSubWindows = m_pqMdiArea->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
       QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
       QString qstrUri = pTempWindow->objectName();
       CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

       if (pElement && pElement->IsContainer())
       {
           if (static_cast<CdmObjectContainer*>(pElement)->GetClass() == p_pClass)
           {
               DELPTR(pTempWindow)
           }
       }
       else if (pElement && pElement->IsClass())
       {
           if (static_cast<CdmClass*>(pElement) == p_pClass)
           {
               DELPTR(pTempWindow)
           }
       }
    }

    CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked());
}

void CwmsAdminMainWindowIf::CloseClassRelatedContainerUis(CdmClass* p_pClass)
{
    QList<QMdiSubWindow*> qlSubWindows = m_pqMdiArea->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
       QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
       QString qstrUri = pTempWindow->objectName();
       CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

       if (pElement && pElement->IsContainer())
       {
           if (static_cast<CdmObjectContainer*>(pElement)->GetClass() == p_pClass)
           {
               DELPTR(pTempWindow)
           }
       }
    }

    CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked());
}

/** +-=---------------------------------------------------------So 18. Mai 13:14:48 2008----------*
 * @method  CwmsAdminMainWindowIf::DeleteDatabaseSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:14:48 2008----------*/
void CwmsAdminMainWindowIf::DeleteDatabaseSlot()
{
    BODY_TRY
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    QString qstrDb = m_pqcbDatabases->currentText();

    if (pCdmManager && !qstrDb.isEmpty())
    {
        if (CdmMessageManager::Ask(tr("Schema löschen"),
                                   tr("Das Schema wird unwiderruflich gelöscht."
                                      "Wollen Sie das wirklich?")))
        {
            ClearEditor();

            if (SUCCESSFULL(pCdmManager->RemoveScheme(qstrDb)))
            {
                m_pqcbDatabases->removeItem(m_pqcbDatabases->currentIndex());
                m_pqcbDatabases->setCurrentIndex(0);
                CdmMessageManager::information(tr("Schema erfoglreich gelöscht"), tr("Schema erfolgreich gelöscht."));
            }
        }
    }
    else
    {
        CdmMessageManager::information(tr("Kein Schema ausgewählt"),
                                       tr("Sie haben kein Schema ausgewählt. Löschung kann nicht durchgeführt werden."));
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------So 18. Mai 13:15:44 2008----------*
 * @method  CwmsAdminMainWindowIf::DeleteObjectListSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:15:44 2008----------*/
void CwmsAdminMainWindowIf::DeleteObjectListSlot(QTreeWidgetItem* p_pItem)
{
   CdmObjectContainer* pContainer = GetContainerFromItem(p_pItem);

   if (pContainer)
   {
      CdmContainerManager* pContainerManager = pContainer->GetContainerManager();

      if (CHKPTR(pContainerManager))
      {
         pContainerManager->DeleteContainer(pContainer);
         QTreeWidgetItem* pqlviItem = GetSelectedItem();
         DELPTR(pqlviItem)
      }
   }
   else
   {
      CdmMessageManager::information(tr("Keine ObjectList ausgewählt"), 
                                     tr("Sie haben keine ObjectList ausgewählt. Löschung kann nicht durchgeführt werden."));
   }
}

/** +-=---------------------------------------------------------So 18. Mai 13:16:11 2008----------*
 * @method  CwmsAdminMainWindowIf::ObjectListRightsSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:16:11 2008----------*/
void CwmsAdminMainWindowIf::ObjectListRightsSlot()
{
   CdmObjectContainer* pContainer = GetSelectedObjectList();
   
   if (pContainer)
   {
      CwmsRightsManagerIf* pCwmsRightsManagerIf = new CwmsRightsManagerIf(pContainer, this);
      pCwmsRightsManagerIf->exec();
      delete pCwmsRightsManagerIf;
   }
   else
   {
      CdmMessageManager::information(tr("Keine ObjectList ausgewählt"), 
         tr("Sie haben keine ObjectList ausgewählt. Berechtigungsfenster kann nicht aufgerufen werden."));
   }
}

/** +-=---------------------------------------------------------So 18. Mai 13:18:01 2008----------*
 * @method  CwmsAdminMainWindowIf::DeleteAllObjectsSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 18. Mai 13:18:01 2008----------*/
void CwmsAdminMainWindowIf::DeleteAllObjectsSlot()
{
   CdmObjectContainer* pContainer = GetSelectedObjectList();
   
   if (pContainer)
   {
      if (CdmMessageManager::Ask(tr("Objekte des Objectcontainers wirklich löschen"),
                                tr("Alle Objekte dieses Objectcontainers werden unwiderruflich gelöscht."
                                   "Wollen Sie das wirklich?")))
      {
         CdmContainerManager* pManager = pContainer->GetContainerManager();
         pManager->ReloadContainerComplete(pContainer);
         QLinkedList<CdmObject*> qvlObjects;
         pContainer->GetObjectList(qvlObjects);
         QLinkedList<CdmObject*>::iterator qvlIt    = qvlObjects.begin();
         QLinkedList<CdmObject*>::iterator qvlItEnd = qvlObjects.end();

         if (qvlObjects.isEmpty())
         {
            CdmMessageManager::information(tr("Keine Objekte gefunden"), 
               tr("Es wurden im Container keine Objekte zur Löschung gefunden."));
         }
         else
         {
            for (; qvlIt != qvlItEnd; ++qvlIt)
            {
               CdmObject* pCdmObject = (*qvlIt);

               if (CHKPTR(pCdmObject))
               {
                  pCdmObject->SetDeleted();
               }
            }
         
            pContainer->Commit();
            QMdiSubWindow* pSubWindow = FindSubWindowByUri(pContainer->GetUriInternal());

            if (pSubWindow)
            {
               CwmsObjectListEditorWidgetIf* pContainerEditor = 
                  dynamic_cast<CwmsObjectListEditorWidgetIf*>(pSubWindow->widget());

               if (pContainerEditor)
               {
                  pContainerEditor->Refresh();
               }
            }
         }
      }
   }
   else
   {
      CdmMessageManager::information(tr("Kein Objectcontainer ausgewählt"),
                               tr("Sie haben keinen Objectcontainer ausgewählt. Löschung kann nicht durchgeführt werden."));
   }
}

/** +-=---------------------------------------------------------Mo 19. Mai 19:20:12 2008----------*
 * @method  CwmsAdminMainWindowIf::DataExportSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This starts the export dlg for the selected objectlist.                               *
 *----------------last changed: --------------------------------Mo 19. Mai 19:20:12 2008----------*/
void CwmsAdminMainWindowIf::DataExportSlot()
{
    CdmMessageManager::StartAsyncMessageCollection();
   CdmObjectContainer* pContainer = GetSelectedObjectList();
   
   if (pContainer)
   {
      CwmsExportSettings cCwmsExportSettings;
      cCwmsExportSettings.SetContainerId(pContainer->GetId());
      cCwmsExportSettings.SetSchemeId(pContainer->GetSchemeId());
      
      CwmsExportSettingsIf* pCwmsExportSettingsIf = new CwmsExportSettingsIf(cCwmsExportSettings, this);
      pCwmsExportSettingsIf->FillDialog();
      pCwmsExportSettingsIf->exec();
      delete pCwmsExportSettingsIf;
   }
   else
   {
      CdmMessageManager::information(tr("Kein Objectcontainer ausgewählt"),
                               tr("Sie haben keinen Objectcontainer ausgewählt. Ein Datenexport kann nicht durchgeführt werden."));
   }

   CdmMessageManager::EndAndShowAsyncMessageCollection();

}

/** +-=---------------------------------------------------------Mo 19. Mai 19:20:33 2008----------*
 * @method  CwmsAdminMainWindowIf::CreateDocumentationSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method creates the DB Documentation as html file.                                *
 *----------------last changed: --------------------------------Mo 19. Mai 19:20:33 2008----------*/
void CwmsAdminMainWindowIf::CreateDocumentationSlot()
{
  CdmMessageManager::StartAsyncMessageCollection();
  CdmClassManager* pCdmClassManager = GetCurrentClassManager();

  if (CHKPTR(pCdmClassManager))
  {
    QString qstrFilename = QFileDialog::getSaveFileName(this, tr("Speicherort für Dokumentation auswählen"));

    if (!qstrFilename.isEmpty())
    {
        if (!qstrFilename.contains("."))
        {
           qstrFilename += ".html";
        }

        pCdmClassManager->GenerateClassDocumentation(pCdmClassManager->GetSchemeName(), qstrFilename);
    }
  }
  CdmMessageManager::EndAndShowAsyncMessageCollection();
}

/** +-=---------------------------------------------------------Do 10. Nov 14:36:45 2011----------*
 * @method  CwmsAdminMainWindowIf::GenerateClassCodeSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 14:36:45 2011----------*/
void CwmsAdminMainWindowIf::GenerateClassCodeSlot()
{
   CdmClass* pCdmClass = GetSelectedClass();

   if (pCdmClass)
   {
      CwmsGenerateCodeEditor::ShowCodeGenerator(this, pCdmClass);
   }
   else
   {
      CdmMessageManager::information(tr("Keine Klasse ausgewählt"), 
                               tr("Sie haben keine Klasse ausgewählt. Eine Codegenerierung kann nicht durchgeführt werden."));
   }
}

/** +-=---------------------------------------------------------Fr 11. Nov 18:27:58 2011----------*
 * @method  CwmsAdminMainWindowIf::GenerateDbCodeSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 11. Nov 18:27:58 2011----------*/
void CwmsAdminMainWindowIf::GenerateDbCodeSlot()
{
  CdmClassManager* pCdmClassManager = GetCurrentClassManager();

  if (CHKPTR(pCdmClassManager))
  {
     CwmsGenerateDatabaseCode cCwmsGenerator(pCdmClassManager);

     QString qstrDirectory = QFileDialog::getExistingDirectory(this, "Bitte wählen Sie das Verzeichnis zum speichern der Dateien aus.");

     if (!qstrDirectory.isEmpty())
     {
        cCwmsGenerator.GenerateDatabaseCode(qstrDirectory);
     }
  }
}

/** +-=---------------------------------------------------------Di 14. Aug 15:20:50 2012----------*
 * @method  CwmsAdminMainWindowIf::UserManagerSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 15:20:50 2012----------*/
void CwmsAdminMainWindowIf::UserManagerSlot()
{
   if (!m_pCwmsUserManager)
   {
      m_pCwmsUserManager = new CwmsUserManagerIf(this);
   }

   m_pCwmsUserManager->show();
}

/** +-=---------------------------------------------------------Di 14. Aug 15:45:30 2012----------*
 * @method  CwmsAdminMainWindowIf::OpenQueryEditorSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 14. Aug 15:45:30 2012----------*/
void CwmsAdminMainWindowIf::OpenQueryEditorSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      if (pCdmManager->GetCurrentScheme())
      {
         CwmsQueryEditor* pEditor = new CwmsQueryEditor(m_pqMdiArea);
         QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);    

         if (CHKPTR(pSubWindow))
         {
            QList<QMdiSubWindow*> qlSubWindows = m_pqMdiArea->subWindowList();
            int iQueryCounter = 0;

            for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
            {
                QMdiSubWindow* sub = qlSubWindows[iCounter];
               if (sub->windowTitle().startsWith(tr("Abfrage ")))
               {
                  ++iQueryCounter;
               }
            }

            pSubWindow->setWindowTitle(tr("Abfrage ") + QString::number(iQueryCounter+1));
         }
      }
      else
      {
         CdmMessageManager::information(tr("Kein Schema ausgewählt"), 
            tr("Sie können den Query Editor nur mit einem gewählten Schema öffnen"));
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 16:17:41 2012----------*
 * @method  CwmsAdminMainWindowIf::DbRightsSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 16:17:41 2012----------*/
void CwmsAdminMainWindowIf::SchemeRightsSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();
      if (pCdmDatabase)
      {
         CdmRights* pCdmRights = &pCdmDatabase->GetRights();

         if (pCdmRights)
         {
            CwmsUniversalRightsManagerIf* pCwmsRights = new CwmsUniversalRightsManagerIf(pCdmRights, this);
            pCwmsRights->exec();
            DELPTR(pCwmsRights)
         }

         pCdmDatabase->Commit();
      }
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:03:21 2012----------*
 * @method  CwmsAdminMainWindowIf::DbLanguagesSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:03:21 2012----------*/
void CwmsAdminMainWindowIf::SchemeLanguagesSlot()
{
   CwmsLanguagesEditorDlg* pCwmsDlg = new CwmsLanguagesEditorDlg(this);
   pCwmsDlg->FillDialog();
   pCwmsDlg->exec();
   DELPTR(pCwmsDlg)
   FillLanguages();
}

/** +-=---------------------------------------------------------Fr 24. Aug 15:46:36 2012----------*
 * @method  CwmsAdminMainWindowIf::NewViewSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 15:46:36 2012----------*/
void CwmsAdminMainWindowIf::NewViewSlot()
{
   CwmsView cView = CwmsView::Create();
   CwmsViewEditor::Edit(cView, true, this);
   RefreshClickedSlot();
}

/** +-=---------------------------------------------------------Fr 24. Aug 15:46:45 2012----------*
 * @method  CwmsAdminMainWindowIf::EditViewSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 15:46:45 2012----------*/
void CwmsAdminMainWindowIf::EditViewSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem)
   {
      CwmsViewManager cViewManager;
      CwmsView cView = cViewManager.GetView(pqItem->text(0));

      if (cView.IsValid())
      {
         CwmsViewEditor::Edit(cView, false, this);
         pqItem->setText(0, cView.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Fr 24. Aug 15:46:54 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteViewSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 15:46:54 2012----------*/
void CwmsAdminMainWindowIf::DeleteViewSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem && static_cast<EwmsTreeItemType>(pqItem->data(1, Qt::UserRole).toInt()) == eWmsTreeItemTypeView)
   {
      CwmsViewManager cViewManager;
      CwmsView cView = cViewManager.GetView(pqItem->text(0));

      if (cView.IsValid())
      {
         cView.SetDeleted();
         cView.CommitObject();
         DELPTR(pqItem)
      }
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:15:05 2012----------*
 * @method  CwmsAdminMainWindowIf::LanguageChangedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:15:05 2012----------*/
void CwmsAdminMainWindowIf::LanguageChangedSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
          QString qstrLanguage = m_pqcbLanguage->itemData(m_pqcbLanguage->currentIndex()).toString();
         pCdmDatabase->SetCurrentLanguage(qstrLanguage);
      }
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:15:26 2012----------*
 * @method  CwmsAdminMainWindowIf::NewReportSlot             // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:15:26 2012----------*/
void CwmsAdminMainWindowIf::NewReportSlot()
{
    if (CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
    {
       CwmsReportManager cManager;

       CdmObjectContainer* pContainer = cManager.GetObjectList();

       if (CHKPTR(pContainer))
       {
          CdmObject* pCdmObject = pContainer->CreateNewObject();

          if (CHKPTR(pCdmObject))
          {
             CwmsPrintingTemplateProperties::EditProperties(this, pCdmObject, true);
             RefreshClickedSlot();
          }
       }
    }
    else
    {
        CdmMessageManager::critical(tr("Kein Druckausgabe-Plugin Aktiv"),
                                    tr("Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden."));
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:15:35 2012----------*
 * @method  CwmsAdminMainWindowIf::EditReportSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:15:35 2012----------*/
void CwmsAdminMainWindowIf::EditReportSlot()
{
    if (CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
    {
       QTreeWidgetItem* pqItem = GetSelectedItem();

       if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeReport)
       {
          CwmsReportManager cManager;
          CwmsPrintingTemplate cTemplate = cManager.GetReport(pqItem->data(0, Qt::UserRole).toInt());

          if (cTemplate.IsValid())
          {
             CwmsReportManager::OpenReportEditor(cTemplate.GetObjectId(), this);
          }
       }
    }
    else
    {
        CdmMessageManager::critical(tr("Kein Druckausgabe-Plugin Aktiv"),
                                    tr("Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden."));
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:15:45 2012----------*
 * @method  CwmsAdminMainWindowIf::ReportPropertiesSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:15:45 2012----------*/
void CwmsAdminMainWindowIf::ReportPropertiesSlot()
{
    if (CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
    {
       QTreeWidgetItem* pqItem = GetSelectedItem();

       if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeReport)
       {
          CwmsReportManager cManager;
          CwmsPrintingTemplate cTemplate = cManager.GetReport(pqItem->data(0, Qt::UserRole).toInt());

          if (cTemplate.IsValid())
          {
             CwmsPrintingTemplateProperties::EditProperties(this, cTemplate.GetObject(), false);
             pqItem->setText(0, cTemplate.GetName());
          }
       }
    }
    else
    {
        CdmMessageManager::critical(tr("Kein Druckausgabe-Plugin Aktiv"),
                                    tr("Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden."));
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:16:03 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteReportSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:16:03 2012----------*/
void CwmsAdminMainWindowIf::DeleteReportSlot()
{
    if (CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
    {
       QTreeWidgetItem* pqItem = GetSelectedItem();

       if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeReport)
       {
          CwmsReportManager cManager;
          CwmsPrintingTemplate cTemplate = cManager.GetReport(pqItem->data(0, Qt::UserRole).toInt());

          if (cTemplate.IsValid())
          {
             cTemplate.SetDeleted();
             cTemplate.CommitObject();
             DELPTR(pqItem)
          }
       }
    }
    else
    {
        CdmMessageManager::critical(tr("Kein Druckausgabe-Plugin Aktiv"),
                                    tr("Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden."));
    }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:16:10 2012----------*
 * @method  CwmsAdminMainWindowIf::NewFormSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:16:10 2012----------*/
void CwmsAdminMainWindowIf::NewFormSlot()
{
   // TODO
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:16:21 2012----------*
 * @method  CwmsAdminMainWindowIf::EditFormSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:16:21 2012----------*/
void CwmsAdminMainWindowIf::EditFormSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeForm)
   {
      // TODO
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 15:16:29 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteFormSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 15:16:29 2012----------*/
void CwmsAdminMainWindowIf::DeleteFormSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeForm)
   {
      // TODO
   }
}

/** +-=---------------------------------------------------------Mi 29. Aug 19:13:42 2012----------*
 * @method  CwmsAdminMainWindowIf::DatabaseJournalSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 19:13:42 2012----------*/
void CwmsAdminMainWindowIf::DatabaseJournalSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();
      if (pCdmDatabase)
      {
         CwmsJournalViewer* pViewer = new CwmsJournalViewer(this);
         pViewer->FillDialog(pCdmDatabase);
         pViewer->exec();
         DELPTR(pViewer)
      }
   }
}

/** +-=---------------------------------------------------------Mi 29. Aug 19:13:54 2012----------*
 * @method  CwmsAdminMainWindowIf::ObjectListJournalSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 19:13:54 2012----------*/
void CwmsAdminMainWindowIf::ObjectListJournalSlot()
{
   CdmObjectContainer* pContainer = GetSelectedObjectList();

   if (pContainer)
   {
      CwmsJournalViewer* pViewer = new CwmsJournalViewer(this);
      pViewer->FillDialog(pContainer);
      pViewer->exec();
      DELPTR(pViewer)
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:27:31 2012----------*
 * @method  CwmsAdminMainWindowIf::OpenApplicationEditor     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:27:31 2012----------*/
void CwmsAdminMainWindowIf::OpenApplicationEditor()
{
   CwmsApplicationManager cAppManager;

   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem)
   {
      QString qstrName = pqItem->text(0);
      CdmMessageManager::StartAsyncMessageCollection();
      CwmsApplication cApp = cAppManager.FindApplication(qstrName);

      if (cApp.IsValid())
      {
         OpenApplicationEditor(cApp);
      }

      CdmMessageManager::EndAndShowAsyncMessageCollection();
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:37:43 2012----------*
 * @method  CwmsAdminMainWindowIf::NewApplicationSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:37:43 2012----------*/
void CwmsAdminMainWindowIf::NewApplicationSlot()
{
    // ToDo ask for Applicationname
   QString qstrApplicationName = CdmMessageManager::AskForInputText(tr("Neu Applikation anlegen"),
                                                                    tr("Bitte geben Sie den Namen der Applikation ein."));

   if (!qstrApplicationName.isEmpty())
   {
       CwmsApplication cApp = CwmsApplication::Create();
       cApp.SetName(qstrApplicationName);
       cApp.CommitObject();
       RefreshClickedSlot();
       OpenApplicationEditor(cApp);
   }
}

/** +-=---------------------------------------------------------Fr 13. Sep 14:47:11 2013----------*
 * @method  CwmsAdminMainWindowIf::OpenApplicationEditor     // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplication& p_rApp                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Sep 14:47:11 2013----------*/
void CwmsAdminMainWindowIf::OpenApplicationEditor(CwmsApplication& p_rApp)
{
    if (p_rApp.IsValid())
    {
      if (!FindAndSetSubWindow(p_rApp.GetUriInternal()))
      {
         CdmMessageManager::StartAsyncMessageCollection();
         CwmsApplicationEditor* pEditor = new CwmsApplicationEditor(m_pqMdiArea);
         pEditor->FillWidget(p_rApp);
         pEditor->show();
         QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);    

         if (CHKPTR(pSubWindow))
         {
            pSubWindow->setWindowTitle(tr("Applikation ") + p_rApp.GetName());
            pSubWindow->setObjectName(p_rApp.GetUriInternal());
         }

         CdmMessageManager::EndAndShowAsyncMessageCollection();
      }
    }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:37:54 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteApplicationSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:37:54 2012----------*/
void CwmsAdminMainWindowIf::DeleteApplicationSlot()
{
   CwmsApplicationManager cAppManager;
   QTreeWidgetItem* pqItem = GetSelectedItem();

   if (pqItem)
   {
      QString qstrName = pqItem->text(0);
      CwmsApplication cApp = cAppManager.FindApplication(qstrName);

      if (cApp.IsValid())
      {
         CdmMessageManager::StartAsyncMessageCollection();
         cApp.SetDeleted();
         cApp.CommitObject();
         DELPTR(pqItem)
         CdmMessageManager::EndAndShowAsyncMessageCollection();
      }
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:38:04 2012----------*
 * @method  CwmsAdminMainWindowIf::ExecuteApplicationSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:38:04 2012----------*/
void CwmsAdminMainWindowIf::ExecuteApplicationSlot()
{
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (pItem && pItem->data(1, Qt::UserRole) == eWmsTreeItemTypeApplication)
   {
      QString qstrApplication = pItem->text(0);

      if (!qstrApplication.isEmpty())
      {
         CwmsApplicationManager cAppManager;
         CwmsApplication cApp = cAppManager.FindApplication(qstrApplication);

         if (cApp.IsValid())
         {
             QString qstrMain = cApp.GetMain();

             if (!qstrMain.isEmpty())
             {
                 CwmsInitApplication::StartMainFunction(qstrMain);
             }


             CdmObject* pMainWindow = cApp.GetMainWindow();

             if (pMainWindow)
             {
                   CwmsQmlApplicationController::createController(QString("Dev Plattform"), nullptr);
                   CwmsFormUserDefined cForm(pMainWindow);
                   CwmsQmlApplicationController::getController()->createCustomMainWindow(cForm.GetName(), cForm.GetUICode());
             }
             else
             {
                if (m_pRuntime)
                {
                   DELPTR(m_pRuntime)
                }

                m_pRuntime = new CwmsRuntime(this);
                m_pRuntime->SetApplication(cApp);
                m_pRuntime->show();
                m_pRuntime->FillWidget();
                m_pRuntime->SetLogoutOnExit(false);
             }
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 6. Sep 15:48:17 2012-----------*
 * @method  CwmsAdminMainWindowIf::ExportJsonSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 6. Sep 15:48:17 2012-----------*/
void CwmsAdminMainWindowIf::ExportJsonSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         CdmMessageManager::StartAsyncMessageCollection();
         QVariant qvDb = pCdmDatabase->GetVariantCompleteDatabase();
         CwmsJson cJson;   
         bool bOk = false;
         QByteArray qbContent = cJson.serialize(qvDb, bOk);

         if (bOk)
         {
            QString qstrFilename = QFileDialog::getSaveFileName(this, tr("Speicherort für Json auswählen"));

            if (!qstrFilename.isEmpty())
            {


               if (!qstrFilename.contains("."))
               {
                  qstrFilename += ".json";
               }

               QFile qFile(qstrFilename);

               if (qFile.open(QIODevice::WriteOnly))
               {
                  qFile.write(qbContent);
                  qFile.close();
               }
            }
         }

         CdmMessageManager::EndAndShowAsyncMessageCollection();
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:37:03 2012----------*
 * @method  CwmsAdminMainWindowIf::NewGenericObjectFormSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:37:03 2012----------*/
void CwmsAdminMainWindowIf::NewGenericObjectFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetGenericFormContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormObject cForm(pCdmObject);
         CwmsFormGenericObjectEditor::EditForm(cForm, true, this);
         RefreshClickedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:55:37 2012----------*
 * @method  CwmsAdminMainWindowIf::EditGenericObjectFormSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:55:37 2012----------*/
void CwmsAdminMainWindowIf::EditGenericObjectFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetGenericFormContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsFormObject cForm(pCdmObject);
         CwmsFormGenericObjectEditor::EditForm(cForm, false, this);
         pItem->setText(0, cForm.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 19:01:02 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteGenericObjectFormSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 19:01:02 2012----------*/
void CwmsAdminMainWindowIf::DeleteGenericObjectFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetGenericFormContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:37:27 2012----------*
 * @method  CwmsAdminMainWindowIf::NewObjectObjectListFormSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:37:27 2012----------*/
void CwmsAdminMainWindowIf::NewObjectObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormObjectObjectContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormObjectContainer cForm(pCdmObject);
         CwmsFormObjectContainerEditor::EditForm(cForm, true, this);
         RefreshClickedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:52:16 2012----------*
 * @method  CwmsAdminMainWindowIf::EditObjectObjectListFormSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:52:16 2012----------*/
void CwmsAdminMainWindowIf::EditObjectObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormObjectObjectContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsFormObjectContainer cForm(pCdmObject);
         CwmsFormObjectContainerEditor::EditForm(cForm, false, this);
         pItem->setText(0, cForm.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 19:00:30 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteObjectObjectListFormSlot // private, slots               *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 19:00:30 2012----------*/
void CwmsAdminMainWindowIf::DeleteObjectObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormObjectObjectContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:38:00 2012----------*
 * @method  CwmsAdminMainWindowIf::NewStandardObjectListFormSlot // private, slots                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:38:00 2012----------*/
void CwmsAdminMainWindowIf::NewStandardObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetStandardFormContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormStandardContainer cForm(pCdmObject);
         CwmsFormStandardContainerEditor::EditForm(cForm, true, this);
         RefreshClickedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:51:21 2012----------*
 * @method  CwmsAdminMainWindowIf::EditStandardObjectListFormSlot // private, slots               *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:51:21 2012----------*/
void CwmsAdminMainWindowIf::EditStandardObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetStandardFormContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsFormStandardContainer cForm(pCdmObject);
         CwmsFormStandardContainerEditor::EditForm(cForm, false, this);
         pItem->setText(0, cForm.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 19:00:01 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteStandardObjectListFormSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 19:00:01 2012----------*/
void CwmsAdminMainWindowIf::DeleteStandardObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetStandardFormContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:38:20 2012----------*
 * @method  CwmsAdminMainWindowIf::NewUserDefinedFormSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:38:20 2012----------*/
void CwmsAdminMainWindowIf::NewUserDefinedFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
          CwmsFormUserDefined cForm(pCdmObject);
          cForm.SetName("New_Form");
          ScriptEnvironmentSlot();

          if (CHKPTR(m_pScriptEnvironment))
          {
              m_pScriptEnvironment->OpenObject(pCdmObject);
          }
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:49:47 2012----------*
 * @method  CwmsAdminMainWindowIf::EditUserDefinedFormSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:49:47 2012----------*/
void CwmsAdminMainWindowIf::EditUserDefinedFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
          ScriptEnvironmentSlot();

          if (CHKPTR(m_pScriptEnvironment))
          {
              m_pScriptEnvironment->OpenObject(pCdmObject);
          }
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:59:31 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteUserDefinedFormSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:59:31 2012----------*/
void CwmsAdminMainWindowIf::DeleteUserDefinedFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:24:59 2012----------*
 * @method  CwmsAdminMainWindowIf::NewViewObjectListFormSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:24:59 2012----------*/
void CwmsAdminMainWindowIf::NewViewObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormViewContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormView cForm(pCdmObject);
         CwmsFormViewEditor::EditForm(cForm, true, this);
		 CwmsMiscDataFiller::FillForms(m_pqlvUis);
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:47:17 2012----------*
 * @method  CwmsAdminMainWindowIf::EditViewObjectListFormSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:47:17 2012----------*/
void CwmsAdminMainWindowIf::EditViewObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormViewContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsFormView cForm(pCdmObject);
         CwmsFormViewEditor::EditForm(cForm, false, this);
         pItem->setText(0, cForm.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 18:58:44 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteViewObjectListFormSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:58:44 2012----------*/
void CwmsAdminMainWindowIf::DeleteViewObjectListFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormViewContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Di 18. Sep 09:21:50 2012----------*
 * @method  CwmsAdminMainWindowIf::NewSearchFormSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 09:21:50 2012----------*/
void CwmsAdminMainWindowIf::NewSearchFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormSearchContainer();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormSearch cForm(pCdmObject);
         CwmsFormSearchEditor::EditForm(cForm, true, this);
		 CwmsMiscDataFiller::FillForms(m_pqlvUis);
      }
   }
}

/** +-=---------------------------------------------------------Di 18. Sep 09:27:30 2012----------*
 * @method  CwmsAdminMainWindowIf::EditSearchFormSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 09:27:30 2012----------*/
void CwmsAdminMainWindowIf::EditSearchFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormSearchContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsFormSearch cForm(pCdmObject);
         CwmsFormSearchEditor::EditForm(cForm, false, this);
         pItem->setText(0, cForm.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Di 18. Sep 09:27:21 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteSearchFormSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 09:27:21 2012----------*/
void CwmsAdminMainWindowIf::DeleteSearchFormSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormSearchContainer();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}

/** +-=---------------------------------------------------------Mi 24. Okt 17:44:04 2012----------*
 * @method  CwmsAdminMainWindowIf::NewWorkflowSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 17:44:04 2012----------*/
void CwmsAdminMainWindowIf::NewWorkflowSlot()
{
   CwmsWorkflowManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetObjectList();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();

      if (CHKPTR(pCdmObject))
      {
         CwmsguiObjectEditorSelector::Create(pCdmObject, this);
         RefreshClickedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Mi 24. Okt 17:44:13 2012----------*
 * @method  CwmsAdminMainWindowIf::EditWorkflowSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 17:44:13 2012----------*/
void CwmsAdminMainWindowIf::EditWorkflowSlot()
{
   CwmsWorkflowManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetObjectList();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         CwmsguiObjectEditorSelector::Edit(pCdmObject, this);
      }
   }
}

/** +-=---------------------------------------------------------Mi 24. Okt 17:44:22 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteWorkflowSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 17:44:22 2012----------*/
void CwmsAdminMainWindowIf::DeleteWorkflowSlot()
{
   CwmsWorkflowManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetObjectList();
   QTreeWidgetItem* pItem = GetSelectedItem();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

      if (CHKPTR(pCdmObject))
      {
         pCdmObject->SetDeleted();
         pCdmObject->Commit();
         DELPTR(pItem)
      }
   }
}
/** +-=---------------------------------------------------------Di 11. Sep 18:46:36 2012----------*
 * @method  CwmsAdminMainWindowIf::EditFunctionSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:46:36 2012----------*/
void CwmsAdminMainWindowIf::EditFunctionSlot()
{
	CdmClassMethod* pMethod = nullptr;
	QTreeWidgetItem* pqtwMethod = GetSelectedItem();
	if (pqtwMethod)
	{
		QString qstrUri = pqtwMethod->data(0, Qt::UserRole).toString();
		CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

		if (CHKPTR(pElement) && pElement->IsMethod())
		{
			pMethod = static_cast<CdmClassMethod*>(pElement);
		}

		if (pMethod)
		{
            ScriptEnvironmentSlot();

            if (CHKPTR(m_pScriptEnvironment))
            {
                m_pScriptEnvironment->OpenObject(pMethod);
            }
		}
	}
}

/** +-=---------------------------------------------------------Di 11. Sep 18:58:25 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteFunctionSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:58:25 2012----------*/
void CwmsAdminMainWindowIf::DeleteFunctionSlot()
{
    BODY_TRY
    CdmClassMethod* pMethod = nullptr;
    QTreeWidgetItem* pqtwMethod = GetSelectedItem();

    if (pqtwMethod)
    {
        QString qstrUri = pqtwMethod->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMethod())
        {
            pMethod = static_cast<CdmClassMethod*>(pElement);
        }

        if (pMethod)
        {
            CdmClass* pClass = pMethod->GetClass();

            if (pClass)
            {
                pClass->DeleteMethod(pMethod->GetMethodName());
                pClass->Commit();
                DELPTR(pqtwMethod)
            }
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Di 11. Sep 18:46:46 2012----------*
 * @method  CwmsAdminMainWindowIf::EditMemberSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:46:46 2012----------*/
void CwmsAdminMainWindowIf::EditMemberSlot()
{
	CdmMember* pMember = nullptr;
	QTreeWidgetItem* pqItem = GetSelectedItem();
	QString qstrUri = pqItem->data(0, Qt::UserRole).toString();
	CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

	if (CHKPTR(pElement) && pElement->IsMember())
	{
		pMember = static_cast<CdmMember*>(pElement);
	}

	if (pMember)
	{
		CwmsAddMemberIf* pCwmsAddMemberIf = new CwmsAddMemberIf(pMember->GetClass(), this);
		pCwmsAddMemberIf->SetMember(pMember);

		if (pCwmsAddMemberIf->exec())
		{
			pMember->GetClass()->Commit();
		}

		delete pCwmsAddMemberIf;
	}

	
	
}

/** +-=---------------------------------------------------------Di 11. Sep 18:58:13 2012----------*
 * @method  CwmsAdminMainWindowIf::DeleteMemberSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:58:13 2012----------*/
void CwmsAdminMainWindowIf::DeleteMemberSlot()
{
    BODY_TRY
    CdmMember* pMember = nullptr;
    QTreeWidgetItem* pqtwMember = GetSelectedItem();

    if (pqtwMember)
    {
        QString qstrUri = pqtwMember->data(0, Qt::UserRole).toString();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (CHKPTR(pElement) && pElement->IsMember())
        {
            pMember = static_cast<CdmMember*>(pElement);
        }

        if (pMember)
        {
            CdmClass* pClass = pMember->GetClass();

            if (pClass)
            {
                pClass->DeleteMember(pMember->GetKeyname());
                pClass->Commit();
                DELPTR(pqtwMember)
            }
        }
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Di 11. Sep 18:46:59 2012----------*
 * @method  CwmsAdminMainWindowIf::EditObjectListSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 18:46:59 2012----------*/
void CwmsAdminMainWindowIf::EditObjectListSlot()
{
}

/** +-=---------------------------------------------------------Do 25. Okt 14:51:32 2012----------*
 * @method  CwmsAdminMainWindowIf::WorkflowTeamsSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 25. Okt 14:51:32 2012----------*/
void CwmsAdminMainWindowIf::WorkflowTeamsSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmObjectContainer* pContainer = pCdmManager->GetObjectContainer("Teams");   

      if(CHKPTR(pContainer))
      {
         CwmsObjectListEditorIf* pCwmsEditor = new CwmsObjectListEditorIf(pContainer, 
                                                                          this);
         pCwmsEditor->AddColumn("Name");
         pCwmsEditor->SetCaptionValue("Name");
         pCwmsEditor->FillDialog();
         pCwmsEditor->setWindowTitle(QObject::tr("Teams"));
         pCwmsEditor->exec();
         DELPTR(pCwmsEditor)
      }
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 09:52:01 2012----------*
 * @method  CwmsAdminMainWindowIf::CustomContextMenuSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @param   const QPoint & p_Pos                             //                                   *
 * @comment CustomContextMenuSlot(const QPoint &))                                                *
 *----------------last changed: --------------------------------Mi 12. Sep 09:52:01 2012----------*/
void CwmsAdminMainWindowIf::CustomContextMenuSlot(const QPoint & p_Pos)
{
   QObject* pObject = sender();
   QString qstrClassName = pObject->metaObject()->className();

   if (qstrClassName == "QTreeWidget")
   {
      m_rpqCurrentWidget = static_cast<QTreeWidget*> (sender());
   }

   if (m_rpqCurrentWidget)
   {
      QTreeWidgetItem* pItem = m_rpqCurrentWidget->itemAt(p_Pos);

      if(pItem)
      {
         QMenu qMenu(this);
         EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pItem->data(1, Qt::UserRole).toInt());

         qMenu.addAction(m_pqaCreateDbQueries);
         qMenu.addAction(m_pqaRefresh);
      

         if (eType != eWmsTreeItemTypeNone)
         {
            qMenu.addAction(m_pqaEdit_2);
            qMenu.addAction(m_pqaDelete);
            qMenu.addSeparator();
         }
      
         if (eType == eWmsTreeItemTypeApplication)
         {
            qMenu.addAction(m_pqaNewApplication);
            qMenu.addAction(m_pqaExecuteApplication);
         }
         else if (eType == eWmsTreeItemTypeContainer)
         {
            qMenu.addAction(m_pqaExport);
            qMenu.addAction(m_pqaObjectListJournal);
            qMenu.addAction(m_pqaObjectListProperties);
         }
         else if (eType == eWmsTreeItemTypeClass)
         {
            qMenu.addAction(m_pqaCreateClass);
            qMenu.addAction(m_pqaCreateObjectList);
            qMenu.addAction(m_pqaGenerateCode);
         }
         else if (eType == eWmsTreeItemTypeReport)
         {
             if (CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
             {
                qMenu.addAction(m_pqaNewReport);
                qMenu.addAction(m_pqaReportProperties);
             }
         }

         qMenu.exec(QCursor::pos());
      }
   }
}

/** +-=---------------------------------------------------------Mi 21. Nov 16:26:32 2012----------*
 * @method  CwmsAdminMainWindowIf::SmtpSlot                  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 16:26:32 2012----------*/
void CwmsAdminMainWindowIf::SmtpSlot()
{
   CwmsSmtpManager cManager;
   CwmsSmtpConfiguration* pConfig = cManager.GetSmtpConfiguration();

   if (CHKPTR(pConfig))
   {
      CwmsSmtpSettings::Edit(*pConfig, this);
      DELPTR(pConfig)
   }
}

/** +-=---------------------------------------------------------Di 13. Nov 13:24:30 2012----------*
 * @method  CwmsAdminMainWindowIf::InstallBaseFunctionsToExecutor // protected, virtual           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 13. Nov 13:24:30 2012----------*/
void CwmsAdminMainWindowIf::InstallBaseFunctionsToExecutor()
{
    CwmsApplicationServices::InstallFunctionsAndPlugins();
    CwmsguiApplicationServices::InstallUiEditors();
}

/** +-=---------------------------------------------------------Mo 3. Dez 10:37:19 2012-----------*
 * @method  CwmsAdminMainWindowIf::ExportDeploymentFileSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 10:37:19 2012-----------*/
void CwmsAdminMainWindowIf::ExportDeploymentFileSlot()
{
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmScheme* pScheme = pManager->GetCurrentScheme();

      if (pScheme)
      {
         CdmMessageManager::StartAsyncMessageCollection();
         QString qstrFilename = QFileDialog::getSaveFileName(this, tr("Bitte geben Sie den Dateiname an."), "", "*.wdf");

         if (!qstrFilename.isEmpty())
         {
            if (!qstrFilename.endsWith(".wdf"))
            {
               qstrFilename += ".wdf";
            }

            pScheme->GenerateDeploymentFile(qstrFilename);
            CdmMessageManager::information(tr("Datei wurde erstellt"), 
                                           tr("Die Deploymentdatei wurde erstellt."));
         }

         CdmMessageManager::EndAndShowAsyncMessageCollection();
      }
      else
      {
          CdmMessageManager::information(tr("Kein Schema gewählt"),
                                         tr("Für den Export einer Deplyomentdatei müssen Sie ein Schema auswählen."));
      }
   }
}

/** +-=---------------------------------------------------------Mo 3. Dez 10:37:32 2012-----------*
 * @method  CwmsAdminMainWindowIf::ImportDeploymentFileSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 10:37:32 2012-----------*/
void CwmsAdminMainWindowIf::ImportDeploymentFileSlot()
{
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmScheme* pDatabase = pManager->GetCurrentScheme();

      if (CHKPTR(pDatabase))
      {
         QString qstrFilename = QFileDialog::getOpenFileName(this, tr("Bitte wählen Sie die Deploymentdatei aus."), "", "*.wdf");

         if (!qstrFilename.isEmpty())
         {
            CdmMessageManager::StartAsyncMessageCollection();
            pDatabase->Deploy(qstrFilename);
            RefreshClickedSlot();
            CdmMessageManager::information(tr("Deploymentdatei importiert"),
                                           tr("Die Deploymentdatei wurde importiert"));
            CdmMessageManager::EndAndShowAsyncMessageCollection();
         }
      }
      else
      {
            CdmMessageManager::information(tr("Kein Schema gewählt"), 
                                           tr("Das Deployment muss auf einem ausgewählten Schema stattfinden."));
      }
   }
}

/** +-=---------------------------------------------------------Do 13. Dez 15:26:51 2012----------*
 * @method  CwmsAdminMainWindowIf::ObjectListPropertiesSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:26:51 2012----------*/
void CwmsAdminMainWindowIf::ObjectListPropertiesSlot()
{
   CdmObjectContainer* pContainer = GetSelectedObjectList();

   if (pContainer)
   {
      CwmsContainerPropertiesDlg cDlg(this);
      cDlg.FillDialog(pContainer);
      cDlg.exec();
   }
}


/** +-=---------------------------------------------------------Mi 4. Sep 19:58:50 2013-----------*
 * @method  CwmsAdminMainWindowIf::ClientSettingsSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 4. Sep 19:58:50 2013-----------*/
void CwmsAdminMainWindowIf::ClientSettingsSlot()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmSettings* pSettings = pManager->GetSettings();

        if (CHKPTR(pSettings))
        {
            CwmsGuiDataAccessConfiguration* pEditor = new CwmsGuiDataAccessConfiguration();
            pEditor->FillDialog();

            if (QDialog::Accepted == pEditor->exec())
            {
                CdmMessageManager::information(tr("Einstellungen übernommen"),
                    tr("Die Einstellungen wurden übernommen."));
            }

            DELPTR(pEditor)
        }
    }
}

/** +-=---------------------------------------------------------So 8. Sep 10:33:22 2013-----------*
 * @method  CwmsAdminMainWindowIf::LoggerClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 8. Sep 10:33:22 2013-----------*/
void CwmsAdminMainWindowIf::LoggerClickedSlot()
{
   if (CHKPTR(m_pCwmsErrorIf)) 
   {
      m_pCwmsErrorIf->show();
   }
}

/** +-=---------------------------------------------------------So 8. Sep 11:45:17 2013-----------*
 * @method  CwmsAdminMainWindowIf::RestoreWindowsSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 8. Sep 11:45:17 2013-----------*/
void CwmsAdminMainWindowIf::RestoreWindowsSlot()
{
   m_pqdwApplications->show();
   m_pqdwData->show();
   m_pqdwWorkflows->show();
   m_pqdwUi->show();
   m_pqdwPrint->show();
   m_pqdwModel->show();
   m_pqdwDatabase->show();
   m_pqdwInformation->show();

   addDockWidget(Qt::BottomDockWidgetArea, m_pqdwInformation);

   addDockWidget(Qt::RightDockWidgetArea, m_pqdwWorkflows);
   addDockWidget(Qt::RightDockWidgetArea, m_pqdwApplications);
   addDockWidget(Qt::RightDockWidgetArea, m_pqdwPrint);
   addDockWidget(Qt::RightDockWidgetArea, m_pqdwUi);

   tabifyDockWidget(m_pqdwApplications, m_pqdwWorkflows);
   tabifyDockWidget(m_pqdwWorkflows, m_pqdwPrint);
   tabifyDockWidget(m_pqdwPrint, m_pqdwUi);
   tabifyDockWidget(m_pqdwUi, m_pqdwModel);

   addDockWidget(Qt::LeftDockWidgetArea, m_pqdwModel);
   addDockWidget(Qt::LeftDockWidgetArea, m_pqdwData);
   addDockWidget(Qt::LeftDockWidgetArea, m_pqdwDatabase);

   tabifyDockWidget(m_pqdwData, m_pqdwModel);
}

/** +-=---------------------------------------------------------Sa 14. Sep 12:51:10 2013----------*
 * @method  CwmsAdminMainWindowIf::UpdateDockWidgetVisibility // private                          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 14. Sep 12:51:10 2013----------*/
void CwmsAdminMainWindowIf::UpdateDockWidgetVisibility()
{
   m_pqmViews->addAction(m_pqdwDatabase->toggleViewAction());
   m_pqmViews->addAction(m_pqdwModel->toggleViewAction());
   m_pqmViews->addAction(m_pqdwData->toggleViewAction());
   m_pqmViews->addAction(m_pqdwApplications->toggleViewAction());
   m_pqmViews->addAction(m_pqdwInformation->toggleViewAction());
   m_pqmViews->addAction(m_pqdwWorkflows->toggleViewAction());
   m_pqmViews->addAction(m_pqdwUi->toggleViewAction());
   m_pqmViews->addAction(m_pqdwPrint->toggleViewAction());
   m_pqmViews->addAction(m_pqdwSearch->toggleViewAction());
   m_pqmViews->addAction(m_pqdwViews->toggleViewAction());
}

/** +-=---------------------------------------------------------Mi 18. Sep 11:48:48 2013----------*
 * @method  CwmsAdminMainWindowIf::ClassFilterChangedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Sep 11:48:48 2013----------*/
void CwmsAdminMainWindowIf::ClassFilterChangedSlot()
{
    BODY_TRY
    if (m_pqcbDatabases->currentText().isEmpty()) return;

    QString qstrClass = m_pqcbClassFilter->currentText();
    QFont qfontFilter = m_pqlabClassFilter->font();
    qfontFilter.setBold(false);
    qfontFilter.setItalic(false);
    m_pqpbClearFilter->setVisible(false);

    if (qstrClass.isEmpty())
    {
        QSignalBlocker(this);
        qstrClass = tr("Objektcontainer aller Klassen");
    }

    if (qstrClass == tr("Objektcontainer aller Klassen"))
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked());
        QApplication::restoreOverrideCursor();
    }
    else
    {
        CdmClassManager* pClassManager = GetCurrentClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

            if (pClass)
            {
                m_pqpbClearFilter->setVisible(true);
                qfontFilter.setBold(true);
                CwmsObjectContainerDataFiller::FillObjectContainersToClass(pClass, m_pqlvData);
            }
            else
            {
                qfontFilter.setItalic(true);
                m_pqlvData->clear();
            }
        }
   }

   m_pqlabClassFilter->setFont(qfontFilter);
   BODY_CATCH
}

/** +-=---------------------------------------------------------Fr 20. Sep 08:57:46 2013----------*
 * @method  CwmsAdminMainWindowIf::CurrentTreeWidgetChangedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Sep 08:57:46 2013----------*/
void CwmsAdminMainWindowIf::CurrentTreeWidgetChangedSlot()
{
   m_rpqCurrentWidget = static_cast<QTreeWidget*> (sender());
}


void CwmsAdminMainWindowIf::SearchClickedSlot()
{
   QString qstrSearch = m_pqleSearch->text();

   bool bClassSearch = m_pqchbClasses->isChecked();
   bool bMemberSearch = m_pqchbMembers->isChecked();
   bool bMethodSearch = m_pqchbMethods->isChecked();

   if (!qstrSearch.isEmpty())
   {
      CwmsSymbolSearch cSearch(qstrSearch, bClassSearch, bMemberSearch, bMethodSearch);
      cSearch.Execute();
      QMap<CdmClass*,QTreeWidgetItem*> qmClassItems;
      int iCounter = 0;
      m_pqtwSearchResults->clear();

      if (bClassSearch)
      {
         QList<CdmClass*> qlClasses = cSearch.GetFoundClasses();

         for (iCounter = 0; iCounter < qlClasses.count(); ++iCounter)
         {
            CdmClass* pClass = qlClasses[iCounter];

            if (pClass && !qmClassItems.contains(pClass))
            {
               QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwSearchResults);
			   pItem->setText(0, pClass->GetCaption() + " - " + pClass->GetKeyname());
               pItem->setData(0, Qt::UserRole, static_cast<int>(pClass->GetId()));
			   pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeClass);
               qmClassItems.insert(pClass, pItem);
            }
         }
      }

      if (bMemberSearch)
      {
         QList<CdmMember*> qlMembers = cSearch.GetFoundMembers();

         for (iCounter = 0; iCounter < qlMembers.count(); ++iCounter)
         {
            CdmMember* pMember = qlMembers[iCounter];

            if (CHKPTR(pMember))
            {
               CdmClass* pClass = pMember->GetClass();
               QTreeWidgetItem* pParent = nullptr;

               if (!qmClassItems.contains(pClass))
               {
                  pParent = new QTreeWidgetItem(m_pqtwSearchResults);
				  pParent->setText(0, pClass->GetCaption() + " - " + pClass->GetKeyname());
                  pParent->setData(0, Qt::UserRole, static_cast<int>(pClass->GetId()));
				  pParent->setData(1, Qt::UserRole, eWmsTreeItemTypeClass);
                  qmClassItems.insert(pClass, pParent);
               }
               else
               {
                  pParent = qmClassItems[pClass];
               }

               if (pParent)
               {
                  QTreeWidgetItem* pItem = new QTreeWidgetItem(pParent);
                  pItem->setData(0, Qt::UserRole, pMember->GetUriInternal());
                  pItem->setText(0, pMember->GetKeyname());

				  pItem->setText(0, pMember->GetCaption() + " - " + pMember->GetKeyname() + " (" + pMember->GetValueTypeAsString() + ")");
                  pItem->setData(0, Qt::UserRole, pMember->GetUriInternal());
				  pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeMember);
               }
            }
         }
      }
      
      if (bMethodSearch)
      {
         QList<CdmClassMethod*> qlMethods = cSearch.GetFoundMethods();

         for (iCounter = 0; iCounter < qlMethods.count(); ++iCounter)
         {
            CdmClassMethod* pMethod = qlMethods[iCounter];

            if (CHKPTR(pMethod))
            {
               CdmClass* pClass = pMethod->GetClass();
               QTreeWidgetItem* pParent = nullptr;

               if (!qmClassItems.contains(pClass))
               {
                  pParent = new QTreeWidgetItem(m_pqtwSearchResults);
				  pParent->setText(0, pClass->GetCaption() + " - " + pClass->GetKeyname());
                  pParent->setData(0, Qt::UserRole, static_cast<int>(pClass->GetId()));
				  pParent->setData(1, Qt::UserRole, eWmsTreeItemTypeClass);
                  qmClassItems.insert(pClass, pParent);
               }
               else
               {
                  pParent = qmClassItems[pClass];
               }

               if (pParent)
               {
                  QTreeWidgetItem* pItem = new QTreeWidgetItem(pParent);
				  pItem->setText(0, pMethod->GetCallInterface());
                  pItem->setData(0, Qt::UserRole, pMethod->GetUriInternal());
				  pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFunction);
               }
            }
         }
      }
   }
}

void CwmsAdminMainWindowIf::ServerPluginsSlot()
{
    CdmObjectContainer* pContainer = 
      CwmsContext::GetContext()->GetPluginManager()->GetServerPluginContainer();

    if (CHKPTR(pContainer))
    {
        CwmsPluginsDlgIf cPlugins(this);
        cPlugins.FillDialogServer(pContainer);
        cPlugins.exec();
    }

}

void CwmsAdminMainWindowIf::AdminPluginsSlot()
{
    CdmObjectContainer* pContainer = CwmsContext::GetContext()->GetPluginManager()->GetPluginContainer();

    if (CHKPTR(pContainer))
    {
        CwmsPluginsDlgIf cPlugins(this);
        cPlugins.FillDialogAdmin(pContainer);
        cPlugins.exec();
    }

    if (!CwmsContext::GetContext()->GetPluginManager()->HasPrintingPlugin())
    {
        m_pqdwPrint->setEnabled(false);
        m_pqaNewReport->setEnabled(false);
        m_pqaReportProperties->setEnabled(false);
    }
    else
    {
        m_pqdwPrint->setEnabled(true);
        m_pqaNewReport->setEnabled(true);
        m_pqaReportProperties->setEnabled(true);
    }

}

void CwmsAdminMainWindowIf::NewPackageSlot()
{
    CdmPackage* pParent = GetSelectedPackage();
    CdmClassManager* pClassManager = GetCurrentClassManager();

    if (CHKPTR(pClassManager))
    {
        QString qstrName = QInputDialog::getText(this,
                                                 tr("Bitte Name des Pakets angegeben"),
                                                 tr("Butte geben Sie den Namen des neuen Pakets ein."));

        if (!qstrName.isEmpty())
        {
            pClassManager->CreatePackage(qstrName, pParent);
            FillClasses(GetCurrentClassManager());
        }
    }
}

void CwmsAdminMainWindowIf::EditPackageSlot()
{
    CdmPackage* pPackage = GetSelectedPackage();

    if (CHKPTR(pPackage))
    {
        QString qstrCaption = pPackage->GetCaption();

        QString qstrName = QInputDialog::getText(this,
                                                 tr("Bitte Name des Pakets angegeben"),
                                                 tr("Butte geben Sie den Namen des neuen Pakets ein."),
                                                 QLineEdit::Normal,
                                                 qstrCaption);

        if (!qstrName.isEmpty() && qstrName != qstrCaption)
        {
            pPackage->SetCaption(qstrName);
			pPackage->Rename(qstrName);
            FillClasses(GetCurrentClassManager());
        }
    }
}

CdmPackage* CwmsAdminMainWindowIf::GetSelectedPackage()
{
    CdmPackage* pPackage = nullptr;
    CdmClassManager* pClassManager = GetCurrentClassManager();

    if (CHKPTR(pClassManager))
    {
        QTreeWidgetItem* pCurrent =CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvModel);

        if (pCurrent)
        {
            EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pCurrent->data(1, Qt::UserRole).toInt());

            if (eType == eWmsTreeItemTypePackage)
            {
                QString qstrUri = pCurrent->data(0, Qt::UserRole).toString();
                pPackage = pClassManager->FindPackageByUri(qstrUri);
            }
        }
    }

    return pPackage;
}

void CwmsAdminMainWindowIf::DeletePackageSlot()
{
    CdmPackage* pPackage = GetSelectedPackage();

    if (CHKPTR(pPackage))
    {
        CdmClassManager* pClassManager = GetCurrentClassManager();

        if (CHKPTR(pClassManager))
        {
            pClassManager->DeletePackage(pPackage);
            FillClasses(pClassManager);
        }
    }
}

void CwmsAdminMainWindowIf::NewLibrarySlot()
{
    CwmsFormManager cFormManager;
    CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = pContainer->CreateNewObject();

        if (CHKPTR(pObject))
        {
            ScriptEnvironmentSlot();

            if (CHKPTR(m_pScriptEnvironment))
            {
                m_pScriptEnvironment->OpenObject(pObject);
            }
        }
    }
}

void CwmsAdminMainWindowIf::EditLibrarySlot()
{
    QTreeWidgetItem* pCurrent = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvUis);

    if (pCurrent)
    {
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pCurrent->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeFormLibrary)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    ScriptEnvironmentSlot();

                    if (CHKPTR(m_pScriptEnvironment))
                    {
                        m_pScriptEnvironment->OpenObject(pObject);
                    }
                }
            }
        }
    }
}

void CwmsAdminMainWindowIf::NewResourceSlot()
{
    CwmsFormManager cFormManager;
    CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

    if (CHKPTR(pContainer))
    {
        CdmObject* pObject = pContainer->CreateNewObject();
        if (CwmsguiObjectEditorSelector::Create(pObject, this))
        {
            CwmsMiscDataFiller::FillForms(m_pqlvUis);
        }
    }
}

void CwmsAdminMainWindowIf::EditResourceSlot()
{
    QTreeWidgetItem* pCurrent = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvUis);

    if (pCurrent)
    {
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pCurrent->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeResource)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    CwmsguiObjectEditorSelector::Edit(pObject, this);
                }
            }
        }
    }
}

void CwmsAdminMainWindowIf::DeleteLibrarySlot()
{
    QTreeWidgetItem* pCurrent = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvUis);

    if (pCurrent)
    {
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pCurrent->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeFormLibrary)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    pObject->SetDeleted();
                    pObject->Commit();
                    CwmsMiscDataFiller::FillForms(m_pqlvUis);
                }
            }
        }
    }
}

void CwmsAdminMainWindowIf::DeleteResourceSlot()
{
    QTreeWidgetItem* pCurrent = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvUis);

    if (pCurrent)
    {
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pCurrent->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeResource)
        {
            long lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    pObject->SetDeleted();
                    pObject->Commit();
                    CwmsMiscDataFiller::FillForms(m_pqlvUis);
                }
            }
        }
    }
}

void CwmsAdminMainWindowIf::ScriptEnvironmentSlot()
{
    if (!m_pScriptEnvironment)
    {
        m_pScriptEnvironment = new CwmsScriptingEnvironment(nullptr);
        m_pScriptEnvironment->SetAdminMainWindow(this);
    }

    m_pScriptEnvironment->FillContent();
    m_pScriptEnvironment->show();
    setEnabled(false);
}

CwmsScriptingEnvironment* CwmsAdminMainWindowIf::GetScriptingEnvironment()
{
    return m_pScriptEnvironment;
}

void CwmsAdminMainWindowIf::LdapSettingsSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        if (pCdmManager->IsLoggedInUserAdmin())
        {
            CwmsGuiLdapAccessConfiguration lEditor(pCdmManager->GetSettings(), nullptr);

            if (QDialog::Accepted == lEditor.exec())
            {
                CdmMessageManager::information(tr("Einstellungen übernommen"),
                    tr("Die Einstellungen wurden übernommen."));
            }
        }
    }
}

void CwmsAdminMainWindowIf::AboutSlot()
{
    // ToDo show own About Box
    QApplication::aboutQt();
}

void CwmsAdminMainWindowIf::ClassModifiedSlot()
{
    CdmClassManager* pCdmClassManager = GetCurrentClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        FillClasses(pCdmClassManager);
    }
}

void CwmsAdminMainWindowIf::NewInteractiveComponentFormSlot()
{
    CwmsFormManager cManager;
    CdmObjectContainer* pCdmList = cManager.GetInteractiveComponentContainer();

    if (CHKPTR(pCdmList))
    {
       CdmObject* pCdmObject = pCdmList->CreateNewObject();

       if (CHKPTR(pCdmObject))
       {
          CwmsFormInteractiveComponent cForm(pCdmObject);
          CwmsFormInteractiveComponentEditorIf::EditInteractiveComponent(this, cForm, true);
          CwmsMiscDataFiller::FillForms(m_pqlvUis);
       }
    }
}

void CwmsAdminMainWindowIf::EditInteractiveComponentFormSlot()
{
    CwmsFormManager cManager;
    CdmObjectContainer* pCdmList = cManager.GetInteractiveComponentContainer();
    QTreeWidgetItem* pItem = GetSelectedItem();

    if (CHKPTR(pCdmList))
    {
       CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

       if (CHKPTR(pCdmObject))
       {
          CwmsFormInteractiveComponent cForm(pCdmObject);
          CwmsFormInteractiveComponentEditorIf::EditInteractiveComponent(this, cForm, false);
          pItem->setText(0, cForm.GetName());
       }
    }
}

void CwmsAdminMainWindowIf::DeleteInteractiveComponentFormSlot()
{
    CwmsFormManager cManager;
    CdmObjectContainer* pCdmList = cManager.GetInteractiveComponentContainer();
    QTreeWidgetItem* pItem = GetSelectedItem();

    if (CHKPTR(pCdmList))
    {
       CdmObject* pCdmObject = pCdmList->FindObjectById(pItem->data(0, Qt::UserRole).toInt());

       if (CHKPTR(pCdmObject))
       {
          pCdmObject->SetDeleted();
          pCdmObject->Commit();
          DELPTR(pItem)
       }
    }
}

void CwmsAdminMainWindowIf::EditSingleton()
{
    QTreeWidgetItem* pItem = GetSelectedItem();

    if (CHKPTR(pItem))
    {
        QString qstrKeyname = pItem->data(0, Qt::UserRole).toString();
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager))
        {
            CdmClassManager* pClassManager = pCdmManager->GetClassManager();

            if (CHKPTR(pClassManager))
            {
                CdmClass* pClass = pClassManager->FindClassByKeyname(qstrKeyname);

                if (CHKPTR(pClass))
                {
                    CdmObject* pObject = pClass->GetSingletonObject();

                    if (CHKPTR(pObject))
                    {
                        CwmsguiObjectEditorIf editor(pObject, this);
                        editor.FillDialog();
                        editor.exec();
                    }
                }
            }
        }
    }

}

void CwmsAdminMainWindowIf::DataSearchClickedSlot()
{
    CwmsDataSearchDlg cDlg(this);
    cDlg.exec();
}

void CwmsAdminMainWindowIf::ReplayEventsClickedSlot()
{
    BODY_TRY
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();
    QList<CdmClassMethod*> qlSubscribers = getEventStoreManager()->getSubscribers();

    if (!qlSubscribers.isEmpty())
    {
        IdmEventIterator* pEventIterator = getEventStoreManager()->getEventIterator();

        if (CHKPTR(pEventIterator))
        {
            QList<CdmClassMethod*>::iterator ql_ItStart = qlSubscribers.begin();
            QList<CdmClassMethod*>::iterator ql_ItEnd = qlSubscribers.end();
            QVariantList qvlParameters;

            for ( ; ql_ItStart != ql_ItEnd; ++ql_ItStart)
            {
                while (pEventIterator->hasNext())
                {
                    CdmClassMethod *pClassMethod = (*ql_ItStart);
                    QObject *pEventDtoObject = pEventIterator->next();
                    QVariant qvEventDto = QVariant::fromValue<QObject*>(pEventDtoObject);
                    qvlParameters.append(qvEventDto);
                    QVariant qvFunction = pExecutor->GetFunction()->ExecuteFunctionStatic(pClassMethod, qvlParameters);
                    qvlParameters.clear();
                }

                if (!pEventIterator->hasNext())
                {
                    QObject *pEventDtoObject = pEventIterator->next();
                    QVariant qvEventDto = QVariant::fromValue<QObject*>(pEventDtoObject);
                    qvlParameters.append(qvEventDto);
                    QVariant qvFunction = pExecutor->GetFunction()->ExecuteFunctionStatic((*ql_ItStart), qvlParameters);
                    qvlParameters.clear();
                    pEventIterator->setBacktoFirstElement();
                }
            }
        }

        CdmMessageManager::information("Replay beendet", "Alle Events wurden erfolgreich erneut abgespielt.");
    }
    else
    {
        ERR("No Subscribers found. Replaying Events is not available!")
    }
    BODY_CATCH
}

void CwmsAdminMainWindowIf::DeleteAllEventsClickedSlot()
{
    BODY_TRY
    CdmSessionManager *pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        CdmSession* pSession = pSessionManager->FindSession();

        if (CHKPTR(pSession)                    &&
            CHKPTR(pSession->GetDataProvider()) &&
            CHKPTR(pSession->GetDataProvider()->GetCurrentScheme()))
        {
            int iDBId = pSession->GetDataProvider()->GetCurrentScheme()->GetId();

            if (CdmMessageManager::Ask(tr("Wollen Sie alle bisherigen Events wirklich löschen?"),
                                       tr("Sie können dann nicht mehr auf alte Events zugreifen.")))
            {
                int iRet = getEventStoreManager()->deleteAllExistingEventsByDatabaseId(iDBId);

                if (iRet > 0)
                {
                    CdmMessageManager::information("Events gelöscht", "Die Events wurden erfolgreich gelöscht.");
                }
            }
            else
            {
                CdmMessageManager::information("Löschen abgelehnt", "Die Events wurden nicht gelöscht.");
            }
        }
    }
    BODY_CATCH
}

void CwmsAdminMainWindowIf::setEventStoreManager()
{
    BODY_TRY
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (pSessionManager)
    {
        CdmSession* pSession = pSessionManager->FindSession();

        if (pSession)
        {
            m_pEventStoreManager = pSession->getEventStoreManager();
        }
    }
    BODY_CATCH
}

IdmEventStoreManager *CwmsAdminMainWindowIf::getEventStoreManager()
{
    return m_pEventStoreManager;
}

void CwmsAdminMainWindowIf::LogoutAndExitSlot()
{
    BODY_TRY
    CwmsLogout* pLogout = new CwmsLogout();

    if (pLogout->Logout())
    {
        INFO("Logout successfull!")
        close();
    }
    else
    {
        INFO("Logout unsuccessfull!!!")
    }
    BODY_CATCH
}
