// System and QT Includes
#include <QCloseEvent>
#include <QCompleter>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QList>
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
#include <CwmsFormUserDefinedExecutor.h>

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
#include "CdmQuery.h"
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
#include "CwmsUIEditor.h"
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
#define CONTAINER_DISPLAY_LIMIT 100
CwmsErrorIf* CwmsAdminMainWindowIf::m_pCwmsErrorIf = nullptr;

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
    m_pqaNewWorkflow->setVisible(false);
    RestoreWindowsSlot();
    QSettings settings("WOGRA", "WMS");
    settings.beginGroup("wms_dp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    UpdateDockWidgetVisibility();
    CreateErrorDlg();
    FillDialog();
    AddContextMenus();
    DELPTR(m_pqdwWorkflows);
    CwmsServerSchemeManager cServerSchemeManager;
    cServerSchemeManager.CheckServerScheme();
    connect(CwmsContext::GetContext(), SIGNAL(ApplicationShutdownSignal()), this, SLOT(close()));
    connect(m_pqaLogoutExit, SIGNAL(triggered()), this, SLOT(LogoutAndExitSlot()));
}

CwmsAdminMainWindowIf::~CwmsAdminMainWindowIf()
{
    DELPTR(m_pCwmsUserManager)
            DELPTR(m_pRuntime)
            DELPTR(m_pScriptEnvironment)
}

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

//    connect(m_pqlvWorkflows, SIGNAL(customContextMenuRequested(const QPoint &)),
//            this, SLOT(CustomContextMenuSlot(const QPoint &)));

//    m_pqlvWorkflows->setContextMenuPolicy(Qt::CustomContextMenu);
}

void CwmsAdminMainWindowIf::ModelTreeWidgetExpandedSlot()
{
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvModel);
}

void CwmsAdminMainWindowIf::CreateErrorDlg()
{
    if (!m_pCwmsErrorIf)
    {
        m_pCwmsErrorIf = new CwmsErrorIf();
        CdmLogging::AddAdaptor(m_pCwmsErrorIf);
    }

    new CwmsMessenger(this, statusBar());
}

void CwmsAdminMainWindowIf::FillDialog()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        QList<QString> qvlDatabases;

        pCdmManager->GetSchemeList(qvlDatabases);

        if (qvlDatabases.count() > 1)
        {
            m_pqcbDatabases->addItem("");
        }

        QList<QString>::iterator qvlIt = qvlDatabases.begin();
        QList<QString>::iterator qvlItEnd = qvlDatabases.end();

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

void CwmsAdminMainWindowIf::DatabaseSelectedSlot()
{
    ClearEditor();
    QString qstrDbName = m_pqcbDatabases->currentText();

    if (!qstrDbName.isEmpty())
    {
        FillSchemeContent(qstrDbName);
    }
}

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
    //m_pqlvWorkflows->clear();
    m_pqlvViews->clear();
    m_pqcbLanguage->clear();
}

void CwmsAdminMainWindowIf::RefreshClickedSlot()
{
    DatabaseSelectedSlot();
}

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
            CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked(), CONTAINER_DISPLAY_LIMIT);
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

    }

    EnableActionOnContext();
    QApplication::restoreOverrideCursor();
    CdmMessageManager::CloseProgressBar("LoadScheme");
    CdmMessageManager::EndAndShowAsyncMessageCollection();
}


void CwmsAdminMainWindowIf::FillLanguages()
{
    CwmsMiscDataFiller::FillLanguages(m_pqcbLanguage);
}

void CwmsAdminMainWindowIf::FillApplications()
{
    CwmsMiscDataFiller::FillApplications(m_pqlvApplications);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvApplications);
}

void CwmsAdminMainWindowIf::FillForms()
{
    CwmsMiscDataFiller::FillForms(m_pqlvUis);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvUis);
}

void CwmsAdminMainWindowIf::FillReports()
{
    CwmsReportManager cReportManager; //will be done for creating the datastructure
    CwmsMiscDataFiller::FillReports(m_pqlvPrint);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvPrint);
}

void CwmsAdminMainWindowIf::FillViews()
{
    CwmsMiscDataFiller::FillViews(m_pqlvViews);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvViews);
    ViewFilterEnterPressedSlot();
}

void CwmsAdminMainWindowIf::FillWorkflows()
{
//    CwmsMiscDataFiller::FillWorkflows(m_pqlvWorkflows);
//    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqlvWorkflows);
    DELPTR(m_pqdwWorkflows);
}

void CwmsAdminMainWindowIf::RefreshClasses()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pCdmClassManager))
        {
            FillClasses(pCdmClassManager);
        }
    }
}

void CwmsAdminMainWindowIf::CloseClassSubWindows()
{
    QList<QMdiSubWindow*> qlSubWindows = m_pqMdiArea->subWindowList();

    for (int iCounter = 0; iCounter < qlSubWindows.count(); ++iCounter)
    {
        QMdiSubWindow* pTempWindow = qlSubWindows[iCounter];
        QString qstrUri = pTempWindow->objectName();
        CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

        if (pElement && pElement->IsClass())
        {
            auto pClassEditor = dynamic_cast<CwmsClassEditorIf*> (pTempWindow->widget());

            if (CHKPTR(pClassEditor))
            {
                pClassEditor->FillFunctions();
                pClassEditor->FillMembers();
            }
        }
    }
}

void CwmsAdminMainWindowIf::FillClasses(CdmClassManager* p_pCdmClassManager)
{
    if (CHKPTR(p_pCdmClassManager))
    {
        m_pqlvModel->clear();
        QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqlvModel);
        pItem->setText(0, tr("Klassen"));
        CwmsClassDataFiller::FillClasses(p_pCdmClassManager, pItem, m_pqchbShowTechnicalItems->isChecked());
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

        ClassFilterEnterPressedSlot();
    }
}

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

void CwmsAdminMainWindowIf::OpenClassEditor(QTreeWidgetItem* p_pItem)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager && p_pItem && pCdmManager->GetCurrentScheme())
    {
        auto pCdmClass = GetSelectedClass();

        if (pCdmClass)
        {
            OpenClassEditor(pCdmClass);
        }
    }
}

void CwmsAdminMainWindowIf::OpenClassEditor(QString p_qstrKeyname)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pCdmClassManager))
        {
            auto pClass = pCdmClassManager->FindClassByKeyname(p_qstrKeyname);

            if (pClass)
            {
                OpenClassEditor(pClass);
            }
        }
    }
}

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

void CwmsAdminMainWindowIf::OpenViewViewer(QTreeWidgetItem* p_pItem)
{
    if (p_pItem)
    {
        CwmsViewManager cCViewManager;
        CwmsView cView = cCViewManager.GetViewByName(p_pItem->text(0));

        if (cView.IsValid())
        {
            if (!FindAndSetSubWindow(cView.GetUriInternal()))
            {
                m_pqtbInfo->setText(cView.GetComment());
                CwmsQueryResultViewer* pEditor = new CwmsQueryResultViewer(m_pqMdiArea);
                pEditor->SetView(cView);

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

void CwmsAdminMainWindowIf::OpenContainerEditor(QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pItem))
    {
        qint64 iContainerId = p_pItem->data(0, Qt::UserRole).toLongLong();
        CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainerEmpty(iContainerId);

        if (CHKPTR(pContainer))
        {
            OpenObjectContainerEditor(pContainer);
        }
    }
}

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

CdmClass* CwmsAdminMainWindowIf::GetSelectedClass()
{
    CdmClass* pCdmClass = nullptr;
    QTreeWidgetItem* pqlviItem = GetSelectedItem();
    QString qstrDbName = m_pqcbDatabases->currentText();
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {

        if (pqlviItem && !qstrDbName.isEmpty())
        {
            EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());

            if (eType == eWmsTreeItemTypeFunctionParent || eType == eWmsTreeItemTypeMemberParent)
            {
                pqlviItem = pqlviItem->parent();

                if (CHKPTR(pqlviItem))
                {
                    eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());
                }
            }
            else if (eType == eWmsTreeItemTypeFunction || eType == eWmsTreeItemTypeGroup)
            {
                pqlviItem = pqlviItem->parent();

                if (CHKPTR(pqlviItem))
                {
                    pqlviItem = pqlviItem->parent();
                }

                if (CHKPTR(pqlviItem))
                {
                    eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());
                }
            }
            else if (eType == eWmsTreeItemTypeMember)
            {
                pqlviItem = pqlviItem->parent();

                if (CHKPTR(pqlviItem))
                {
                    eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());

                    if (eType == eWmsTreeItemTypeGroup)
                    {
                        pqlviItem = pqlviItem->parent();

                        if (CHKPTR(pqlviItem))
                        {
                            pqlviItem = pqlviItem->parent();
                        }

                        if (CHKPTR(pqlviItem))
                        {
                            eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());
                        }
                    }
                    else if (eType == eWmsTreeItemTypeMemberParent)
                    {
                        pqlviItem = pqlviItem->parent();

                        if (CHKPTR(pqlviItem))
                        {
                            eType = static_cast<EwmsTreeItemType>(pqlviItem->data(1, Qt::UserRole).toInt());
                        }
                    }
                }
            }

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

CdmObjectContainer* CwmsAdminMainWindowIf::GetSelectedObjectList()
{
    QTreeWidgetItem* pqlviItem = GetSelectedItem();
    return GetContainerFromItem(pqlviItem);
}

CdmObjectContainer* CwmsAdminMainWindowIf::GetContainerFromItem(QTreeWidgetItem* p_pItem)
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (p_pItem)
    {
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType>(p_pItem->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeContainer) // a objectlist is marked
        {
            qint64 qstrKeyname = p_pItem->data(0, Qt::UserRole).toLongLong();

            if (CHKPTR(pCdmManager))
            {
                pContainer = pCdmManager->GetObjectContainer(qstrKeyname);
            }
        }
    }

    return pContainer;
}

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
                MSG_INFO(("Schema konnte nicht angelegt werden"),
                         ("Das Schema konnte nicht angelegt werden. (Interner Fehler)"));
            }
        }

        CdmMessageManager::EndAndShowAsyncMessageCollection();
    }

}

void CwmsAdminMainWindowIf::CreateObjectListSlot()
{
    CdmObjectContainer* pContainer = CwmsCreateObjectContainerDlg::CreateObjectContainer(this);

    if (pContainer)
    {
        ClassFilterChangedSlot();
        OpenObjectContainerEditor(pContainer);
    }
}

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
                MSG_INFO(("Klasse konnte nicht gelöscht werden"),
                         ("Die Klasse konnte nicht gelöscht werden.\n "
                          "Stellen Sie sicher dass diese Klasse keine Objektcontainer besitzt und\n"
                          "nirgends als Basisklasse verwendet wurde."));

            }
            else
            {
                QTreeWidgetItem* pqlviItem = GetSelectedItem();
                delete pqlviItem;
                CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked(), CONTAINER_DISPLAY_LIMIT);
            }

        }
    }
    else
    {
        MSG_INFO(("Keine Klasse ausgewählt"),
                 ("Sie haben kein Schema ausgewählt. Löschung kann nicht durchgeführt werden."));
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

    CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked(), CONTAINER_DISPLAY_LIMIT);
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

    CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked(), CONTAINER_DISPLAY_LIMIT);
}

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
                MSG_INFO(("Schema erfoglreich gelöscht"), ("Schema erfolgreich gelöscht."));
            }
        }
    }
    else
    {
        MSG_INFO(("Kein Schema ausgewählt"),
                 ("Sie haben kein Schema ausgewählt. Löschung kann nicht durchgeführt werden."));
    }
    BODY_CATCH
}

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
        MSG_INFO(("Keinen Container ausgewählt"),
                 ("Sie haben keinen Container ausgewählt. Löschung kann nicht durchgeführt werden."));
    }
}

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
        MSG_INFO(("Keinen Container ausgewählt"),
                 ("Sie haben keinen Container ausgewählt. Berechtigungsfenster kann nicht aufgerufen werden."));
    }
}

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
            QList<CdmObject*> qvlObjects;
            pContainer->GetObjectList(qvlObjects);
            QList<CdmObject*>::iterator qvlIt    = qvlObjects.begin();
            QList<CdmObject*>::iterator qvlItEnd = qvlObjects.end();

            if (qvlObjects.isEmpty())
            {
                MSG_INFO(("Keine Objekte gefunden"),
                         ("Es wurden im Container keine Objekte zur Löschung gefunden."));
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
        MSG_INFO(("Kein Objectcontainer ausgewählt"),
                 ("Sie haben keinen Objectcontainer ausgewählt. Löschung kann nicht durchgeführt werden."));
    }
}

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
        MSG_INFO(("Kein Objectcontainer ausgewählt"),
                 ("Sie haben keinen Objectcontainer ausgewählt. Ein Datenexport kann nicht durchgeführt werden."));
    }

    CdmMessageManager::EndAndShowAsyncMessageCollection();

}

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

void CwmsAdminMainWindowIf::GenerateClassCodeSlot()
{
    CdmClass* pCdmClass = GetSelectedClass();

    if (pCdmClass)
    {
        CwmsGenerateCodeEditor::ShowCodeGenerator(this, pCdmClass);
    }
    else
    {
        MSG_INFO(("Keine Klasse ausgewählt"),
                 ("Sie haben keine Klasse ausgewählt. Eine Codegenerierung kann nicht durchgeführt werden."));
    }
}

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

void CwmsAdminMainWindowIf::UserManagerSlot()
{
    if (!m_pCwmsUserManager)
    {
        m_pCwmsUserManager = new CwmsUserManagerIf(this);
    }

    m_pCwmsUserManager->show();
}

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
            MSG_INFO(("Kein Schema ausgewählt"),
                     ("Sie können den Query Editor nur mit einem gewählten Schema öffnen"));
        }
    }
}

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

void CwmsAdminMainWindowIf::SchemeLanguagesSlot()
{
    CwmsLanguagesEditorDlg* pCwmsDlg = new CwmsLanguagesEditorDlg(this);
    pCwmsDlg->FillDialog();
    pCwmsDlg->exec();
    DELPTR(pCwmsDlg)
            FillLanguages();
}

void CwmsAdminMainWindowIf::NewViewSlot()
{
    CwmsView cView = CwmsView::Create();
    CwmsViewEditor::Edit(cView, true, this);
    FillViews();
}

void CwmsAdminMainWindowIf::EditViewSlot()
{
    QTreeWidgetItem* pqItem = GetSelectedItem();

    if (pqItem)
    {
        CwmsViewManager cViewManager;
        CwmsView cView = cViewManager.GetViewByName(pqItem->text(0));

        if (cView.IsValid())
        {
            CwmsViewEditor::Edit(cView, false, this);
            pqItem->setText(0, cView.GetName());
        }
    }

    FillViews();
}

void CwmsAdminMainWindowIf::DeleteViewSlot()
{
    QTreeWidgetItem* pqItem = GetSelectedItem();

    if (pqItem && static_cast<EwmsTreeItemType>(pqItem->data(1, Qt::UserRole).toInt()) == eWmsTreeItemTypeView)
    {
        CwmsViewManager cViewManager;
        CwmsView cView = cViewManager.GetViewByName(pqItem->text(0));

        if (cView.IsValid())
        {
            cView.SetDeleted();
            cView.CommitObject();
            DELPTR(pqItem)
        }
    }
}

void CwmsAdminMainWindowIf::RefreshViewsClickedSlot()
{
    FillViews();
}

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
                FillReports();
            }
        }
    }
    else
    {
        MSG_CRIT("Kein Druckausgabe-Plugin Aktiv",
                 "Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden.");
    }
}

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
        MSG_CRIT("Kein Druckausgabe-Plugin Aktiv",
                 "Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden.");
    }
}

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
        MSG_CRIT("Kein Druckausgabe-Plugin Aktiv",
                 "Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden.");
    }
}

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
        MSG_CRIT("Kein Druckausgabe-Plugin Aktiv",
                 "Es ist kein Druckausgabe-Plugin aktiviert. Ein neuer Report kann nicht erstellt werden.");
    }
}

void CwmsAdminMainWindowIf::NewFormSlot()
{
    // TODO
}

void CwmsAdminMainWindowIf::EditFormSlot()
{
    QTreeWidgetItem* pqItem = GetSelectedItem();

    if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeForm)
    {
        // TODO
    }
}

void CwmsAdminMainWindowIf::DeleteFormSlot()
{
    QTreeWidgetItem* pqItem = GetSelectedItem();

    if (pqItem->data(1, Qt::UserRole).toInt() == eWmsTreeItemTypeForm)
    {
        // TODO
    }
}

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

void CwmsAdminMainWindowIf::NewApplicationSlot()
{
    QString qstrApplicationName = CdmMessageManager::AskForInputText(tr("Neu Applikation anlegen"),
                                                                     tr("Bitte geben Sie den Namen der Applikation ein."));

    if (!qstrApplicationName.isEmpty())
    {
        CwmsApplication cApp = CwmsApplication::Create();
        cApp.SetName(qstrApplicationName);
        cApp.CommitObject();
        FillApplications();
        OpenApplicationEditor(cApp);
    }
}

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
                CwmsRuntime::Execute(cApp, this);
            }
        }
    }
}

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
            FillForms();
        }
    }
}

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
            FillForms();
        }
    }
}

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
            FillForms();
        }
    }
}

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
            QString qstrFormName = "New_Form";
            cForm.SetName(qstrFormName);
            cForm.CommitObject();
            FillForms();

            CwmsTreeWidgetHelper::SelectObject(m_pqlvUis, cForm.GetObject());
            auto pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvUis);

            EditFormSlot(pCdmObject, pItem);

        }
    }
}

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
            EditFormSlot(pCdmObject, pItem);
        }
    }
}

void CwmsAdminMainWindowIf::EditFormSlot(CdmObject* p_pObject, QTreeWidgetItem* p_pItem)
{
    if (CHKPTR(p_pObject))
    {
        if (!FindAndSetSubWindow(p_pObject->GetUriInternal()))
        {
           CwmsFormUserDefined cForm(p_pObject);
           CwmsUIEditor* pEditor = new CwmsUIEditor(m_pqMdiArea);
           pEditor->FillDialog(cForm);
           pEditor->SetItem(p_pItem);

           QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

           if (CHKPTR(pSubWindow))
           {
              pSubWindow->setWindowTitle(tr("Benutzeroberfläche ") + cForm.GetName());
              pSubWindow->setObjectName(p_pObject->GetUriInternal());
              pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
           }
       }
    }
}

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
            FillForms();
        }
    }
}

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
            FillForms();
        }
    }
}

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
            FillWorkflows();
        }
    }
}

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

void CwmsAdminMainWindowIf::NewFunction(CdmClass* pClass)
{
    if (CHKPTR(pClass))
    {
        auto pMethod = pClass->CreateMethod(tr("New_Function"));
        pClass->Commit();
        auto pItemParent = GetSelectedItem();
        EwmsTreeItemType eType = static_cast<EwmsTreeItemType> (pItemParent->data(1, Qt::UserRole).toInt());

        if (eType == eWmsTreeItemTypeFunction)
        {
            pItemParent = pItemParent->parent();
        }

        if (CHKPTR(pMethod) && CHKPTR(pItemParent))
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(pItemParent);
            pItem->setText(0, pMethod->GetMethodName());
            pItem->setData(0, Qt::UserRole, pMethod->GetUriInternal());
            pItem->setData(1, Qt::UserRole, eWmsTreeItemTypeFunction);

            CwmsFunctionEditor* pEditor = new CwmsFunctionEditor(m_pqMdiArea);
            pEditor->FillDialog(pMethod);
            pEditor->SetItem(pItem);

            QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

            if (CHKPTR(pSubWindow))
            {
               pSubWindow->setWindowTitle(tr("Funktion ") + pClass->GetKeyname() + "." + pMethod->GetMethodName());
               pSubWindow->setObjectName(pMethod->GetUriInternal());
               pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
            }
        }
    }
}

void CwmsAdminMainWindowIf::NewFunctionSlot()
{
    auto pClass = GetSelectedClass();

    if (CHKPTR(pClass))
    {
        NewFunction(pClass);
    }
}

void CwmsAdminMainWindowIf::EditFunction(CdmClassMethod* pMethod, QTreeWidgetItem* pqtwMethod)
{


    if (pMethod)
    {
        if (!pqtwMethod)
        {
            //pqtwMethod = FindClassViewItemByUri(pMethod->GetUri());
        }

        if (!FindAndSetSubWindow(pMethod->GetUriInternal()))
        {
            CdmMessageManager::StartAsyncMessageCollection();
            CwmsFunctionEditor* pEditor = new CwmsFunctionEditor(m_pqMdiArea);
            pEditor->FillDialog(pMethod);
            pEditor->SetItem(pqtwMethod);
            pEditor->show();
            QMdiSubWindow* pSubWindow = AddMdiWindow(pEditor);

            if (CHKPTR(pSubWindow))
            {
                auto pClass = pMethod->GetClass();
                pSubWindow->setWindowTitle(tr("Funktion ") + pClass->GetKeyname() + "." + pMethod->GetMethodName());
                pSubWindow->setObjectName(pMethod->GetUriInternal());
                pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
            }

            CdmMessageManager::EndAndShowAsyncMessageCollection();
        }
    }
}

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
            pMethod = dynamic_cast<CdmClassMethod*>(pElement);
        }

        if (pMethod)
        {
            EditFunction(pMethod, pqtwMethod);
        }
    }
}

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
            pMethod = dynamic_cast<CdmClassMethod*>(pElement);
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

void CwmsAdminMainWindowIf::EditMemberSlot()
{
    CdmMember* pMember = nullptr;
    QTreeWidgetItem* pqItem = GetSelectedItem();
    QString qstrUri = pqItem->data(0, Qt::UserRole).toString();
    CdmLocatedElement* pElement = CdmSessionManager::GetDataProvider()->GetUriObject(qstrUri);

    if (CHKPTR(pElement) && pElement->IsMember())
    {
        pMember = dynamic_cast<CdmMember*>(pElement);
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

void CwmsAdminMainWindowIf::EditObjectListSlot()
{
}

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
            else if (eType == eWmsTreeItemTypeFunctionParent ||
                     eType == eWmsTreeItemTypeFunction)
            {
                qMenu.addAction(m_pqaNewFunction);

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

void CwmsAdminMainWindowIf::InstallBaseFunctionsToExecutor()
{
    CwmsguiApplicationServices::InstallFunctionsAndPlugins();
    CwmsguiApplicationServices::InstallUiEditors();
}

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
                MSG_INFO(("Datei wurde erstellt"),
                         ("Die Deploymentdatei wurde erstellt."));
            }

            CdmMessageManager::EndAndShowAsyncMessageCollection();
        }
        else
        {
            MSG_INFO(("Kein Schema gewählt"),
                     ("Für den Export einer Deplyomentdatei müssen Sie ein Schema auswählen."));
        }
    }
}

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
                MSG_INFO(("Deploymentdatei importiert"),
                         ("Die Deploymentdatei wurde importiert"));
                CdmMessageManager::EndAndShowAsyncMessageCollection();
            }
        }
        else
        {
            MSG_INFO(("Kein Schema gewählt"),
                     ("Das Deployment muss auf einem ausgewählten Schema stattfinden."));
        }
    }
}

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
                MSG_INFO(("Einstellungen übernommen"),
                         ("Die Einstellungen wurden übernommen."));
            }

            DELPTR(pEditor)
        }
    }
}

void CwmsAdminMainWindowIf::LoggerClickedSlot()
{
    if (CHKPTR(m_pCwmsErrorIf))
    {
        m_pCwmsErrorIf->show();
    }
}

void CwmsAdminMainWindowIf::RestoreWindowsSlot()
{
    m_pqdwApplications->show();
    m_pqdwData->show();
    //m_pqdwWorkflows->show();
    m_pqdwUi->show();
    m_pqdwPrint->show();
    m_pqdwModel->show();
    m_pqdwDatabase->show();
    m_pqdwInformation->show();

    addDockWidget(Qt::BottomDockWidgetArea, m_pqdwInformation);

    //addDockWidget(Qt::RightDockWidgetArea, m_pqdwWorkflows);
    addDockWidget(Qt::RightDockWidgetArea, m_pqdwApplications);
    addDockWidget(Qt::RightDockWidgetArea, m_pqdwPrint);
    addDockWidget(Qt::RightDockWidgetArea, m_pqdwUi);

    //tabifyDockWidget(m_pqdwApplications, m_pqdwWorkflows);
    tabifyDockWidget(m_pqdwApplications, m_pqdwPrint);
    tabifyDockWidget(m_pqdwPrint, m_pqdwUi);
    tabifyDockWidget(m_pqdwUi, m_pqdwModel);

    addDockWidget(Qt::LeftDockWidgetArea, m_pqdwModel);
    addDockWidget(Qt::LeftDockWidgetArea, m_pqdwData);
    addDockWidget(Qt::LeftDockWidgetArea, m_pqdwDatabase);

    tabifyDockWidget(m_pqdwData, m_pqdwModel);
}

void CwmsAdminMainWindowIf::UpdateDockWidgetVisibility()
{
    m_pqmViews->addAction(m_pqdwDatabase->toggleViewAction());
    m_pqmViews->addAction(m_pqdwModel->toggleViewAction());
    m_pqmViews->addAction(m_pqdwData->toggleViewAction());
    m_pqmViews->addAction(m_pqdwApplications->toggleViewAction());
    m_pqmViews->addAction(m_pqdwInformation->toggleViewAction());
    //m_pqmViews->addAction(m_pqdwWorkflows->toggleViewAction());
    m_pqmViews->addAction(m_pqdwUi->toggleViewAction());
    m_pqmViews->addAction(m_pqdwPrint->toggleViewAction());
    m_pqmViews->addAction(m_pqdwSearch->toggleViewAction());
    m_pqmViews->addAction(m_pqdwViews->toggleViewAction());
}

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
        CwmsObjectContainerDataFiller::FillAllObjectContainersToView(m_pqlvData, m_pqchbShowTechnicalItems->isChecked(), CONTAINER_DISPLAY_LIMIT);
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
            qint64 lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
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
            FillForms();
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
            qint64 lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
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
            qint64 lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetFormLibrary();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    pObject->SetDeleted();
                    pObject->Commit();
                    FillForms();
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
            qint64 lObjectId = pCurrent->data(0, Qt::UserRole).toInt();
            CwmsFormManager cFormManager;
            CdmObjectContainer* pContainer = cFormManager.GetResourceContainer();

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                if (CHKPTR(pObject))
                {
                    pObject->SetDeleted();
                    pObject->Commit();
                    FillForms();
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
                MSG_INFO(("Einstellungen übernommen"),
                         ("Die Einstellungen wurden übernommen."));
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
            FillForms();
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
                        if (editor.exec() == QDialog::Accepted)
                        {
                            pObject->Commit();
                        }

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

void CwmsAdminMainWindowIf::ClassFilterEnterPressedSlot()
{
    CwmsMiscDataFiller::FilterTreeWidgetsUnderRootElement(m_pqleClassFilter->text(), m_pqlvModel);
}


void CwmsAdminMainWindowIf::ViewFilterEnterPressedSlot()
{
    CwmsMiscDataFiller::FilterTreeWidgetsUnderRootElement(m_pqleViewFilter->text(), m_pqlvViews);
}
