/******************************************************************************
 ** WOGRA Middleware Tools WMS Enterprise Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA Solutions All rights reserved
 ******************************************************************************/

#ifndef CWMSADMINMAINWINDOWIF_H
#define CWMSADMINMAINWINDOWIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <qstring.h>
#include <qlayout.h>
#include <qmap.h>
#include <QMainWindow>
#include <QCloseEvent>


// WMS Includes
#include "CdmSettings.h"
#include "IdmEventStoreManager.h"
#include "CdmSession.h"
#include "CdmSessionManager.h"
#include "CdmExecutorFunction.h"
#include "CdmExecutor.h"

// WMS Basetools Includes
#include "CwmsViewManager.h"
#include "CwmsApplication.h"



// own Includes 
#include "ui_CwmsAdminMainWindow.h"


// forwards
class CdmClass;
class CdmClassManager;
class QTreeWidgetItem;
class QMdiArea;
class QTreeWidget;
class QMdiSubWindow;
class CdmObjectContainer;
class QWidget;
class CwmsRuntime;
class CwmsUserManagerIf;
class NCRDMainWindow;
class CwmsErrorIf;
class QMdiSubWindow;
class CwmsScriptingEnvironment;
class CwmsErrorMessenger;
class IdmEventStoreManager;

// enums
enum EwmsTreeItemType
{
    eWmsTreeItemTypeNone,
    eWmsTreeItemTypeClass,
    eWmsTreeItemTypeContainer,
    eWmsTreeItemTypeMember,
    eWmsTreeItemTypeFunction,
    eWmsTreeItemTypeView,
    eWmsTreeItemTypeReport,
    eWmsTreeItemTypeForm,
    eWmsTreeItemTypeGroup,
    eWmsTreeItemTypeApplication,
    eWmsTreeItemTypeFormUserDefined,
    eWmsTreeItemTypeFormStandardObjectList,
    eWmsTreeItemTypeFormViewObjectList,
    eWmsTreeItemTypeFormObjectObjectList,
    eWmsTreeItemTypeFormGenericObject,
    eWmsTreeItemTypeFormSearch,
    eWmsTreeItemTypeFormLibrary,
    eWmsTreeItemTypeWorkflow,
    eWmsTreeItemTypePackage,
    eWmsTreeItemTypeResource,
    eWmsTreeItemTypeClassParent,
    eWmsTreeItemTypeResourceParent,
    eWmsTreeItemTypeFormLibraryParent,
    eWmsTreeItemTypeFormUserDefinedParent,
    eWmsTreeItemTypeMemberParent,
    eWmsTreeItemTypeFunctionParent,
    eWmsTreeItemTypeInteractiveComponentForm,
    eWmsTreeItemTypeSingletonClass
};

class CwmsAdminMainWindowIf : public QMainWindow, public Ui::CwmsAdminMainWindow
{
    Q_OBJECT

private:
    QTreeWidgetItem* m_pqlviClasses;
    QTreeWidgetItem* m_pqlviViews;
    QTreeWidgetItem* m_pqlviForms;
    QTreeWidgetItem* m_pqlviReports;
    QWidget* m_pqwEditor;
    QMap<qint64, QString>  m_qmObjectLists;
    CwmsUserManagerIf* m_pCwmsUserManager;
    CwmsRuntime* m_pRuntime;
    QTreeWidget* m_rpqCurrentWidget;
    static CwmsErrorIf* m_pCwmsErrorIf;
    CwmsScriptingEnvironment* m_pScriptEnvironment;
    CwmsErrorMessenger* m_pLogger;
    QVariantList qvl_EventList;
    IdmEventStoreManager *m_pEventStoreManager;

public:
    CwmsAdminMainWindowIf( QWidget* parent = NULL);
    virtual ~CwmsAdminMainWindowIf( );
    void CloseClassRelatedUis(CdmClass *p_pClass);
    CdmObjectContainer *GetContainerFromItem(QTreeWidgetItem *p_pItem);
    QList<QTreeWidgetItem *> GetSelectedItems();
    void CloseClassRelatedContainerUis(CdmClass *p_pClass);
    CdmClass* GetSelectedClass();
    CdmObjectContainer* GetSelectedObjectList();
    CwmsScriptingEnvironment *GetScriptingEnvironment();

    void RefreshClasses();
    void CloseClassSubWindows();
    void EditFunction(CdmClassMethod *pMethod, QTreeWidgetItem *pqtwMethod);

    void NewFunction(CdmClass *pClass);

    void OpenClassEditor(QString p_qstrKeyname);
public slots:
    void EditSingleton();
    void SearchClickedSlot();
    void NewPackageSlot();
    void EditPackageSlot();
    void DeletePackageSlot();
    void NewResourceSlot();
    void ScriptEnvironmentSlot();
    void ModelTreeWidgetExpandedSlot();
    void NewInteractiveComponentFormSlot();
    void EditInteractiveComponentFormSlot();
    void DeleteInteractiveComponentFormSlot();
    void ReplayEventsClickedSlot();
    void DeleteAllEventsClickedSlot();
    void LogoutAndExitSlot();
    void RefreshViewsClickedSlot();
    void ClassFilterEnterPressedSlot();
    void ViewFilterEnterPressedSlot();
    void AboutSlot();
    void DataSearchClickedSlot();
    void RefreshClickedSlot( );

    void NewFunctionSlot();
protected:
    void closeEvent(QCloseEvent* p_pqCloseEvent);
    virtual void InstallBaseFunctionsToExecutor();
    void CreateErrorDlg();

private slots:
    void CreateClassSlot( );
    void CreateDatabaseSlot( );
    void CreateObjectListSlot( );
    void DeleteClassSlot( );
    void DeleteDatabaseSlot( );
    void DeleteObjectListSlot(QTreeWidgetItem* p_pItem);
    void ObjectListRightsSlot( );
    void DeleteAllObjectsSlot( );
    void DataExportSlot( );
    void CreateDocumentationSlot( );
    void GenerateClassCodeSlot( );
    void GenerateDbCodeSlot( );
    void UserManagerSlot( );
    void OpenQueryEditorSlot( );
    void SchemeRightsSlot( );
    void SchemeLanguagesSlot( );
    void NewViewSlot( );
    void EditViewSlot( );
    void DeleteViewSlot( );
    void LanguageChangedSlot( );
    void NewReportSlot( );
    void EditReportSlot( );
    void ReportPropertiesSlot( );
    void DeleteReportSlot( );
    void NewFormSlot( );
    void EditFormSlot( );
    void DeleteFormSlot( );
    void DatabaseJournalSlot( );
    void ObjectListJournalSlot( );
    void NewApplicationSlot( );
    void DeleteApplicationSlot( );
    void ExecuteApplicationSlot( );
    void LoggerClickedSlot( );
    void RestoreWindowsSlot( );
    void ClientSettingsSlot( );
    void ClassFilterChangedSlot( );
    void EditSlot( QTreeWidgetItem* p_pItem);
    void CurrentTreeWidgetChangedSlot( );
    void ServerPluginsSlot();
    void AdminPluginsSlot();
    void NewLibrarySlot();
    void EditLibrarySlot();
    void EditResourceSlot();
    void DeleteResourceSlot();
    void DeleteLibrarySlot();
    void LdapSettingsSlot();
    void ClassModifiedSlot();
    void SmtpSlot( );
    void ExportDeploymentFileSlot( );
    void ImportDeploymentFileSlot( );
    void ObjectListPropertiesSlot( );
    void NewWorkflowSlot( );
    void EditWorkflowSlot( );
    void DeleteWorkflowSlot( );
    void WorkflowTeamsSlot( );
    void NewSearchFormSlot( );
    void DeleteSearchFormSlot( );
    void EditSearchFormSlot( );
    void ExportJsonSlot( );
    void NewGenericObjectFormSlot( );
    void NewObjectObjectListFormSlot( );
    void NewStandardObjectListFormSlot( );
    void NewUserDefinedFormSlot( );
    void NewViewObjectListFormSlot( );
    void EditSlot( );
    void DeleteSlot( );
    void EditFunctionSlot( );
    void EditMemberSlot( );
    void EditObjectListSlot( );
    void EditViewObjectListFormSlot( );
    void EditUserDefinedFormSlot( );
    void EditStandardObjectListFormSlot( );
    void EditObjectObjectListFormSlot( );
    void EditGenericObjectFormSlot( );
    void DeleteMemberSlot( );
    void DeleteFunctionSlot( );
    void DeleteViewObjectListFormSlot( );
    void DeleteUserDefinedFormSlot( );
    void DeleteStandardObjectListFormSlot( );
    void DeleteObjectObjectListFormSlot( );
    void DeleteGenericObjectFormSlot( );
    void CustomContextMenuSlot( const QPoint & p_Pos);
    void DatabaseSelectedSlot( );
    void SchemeContentSelectedSlot( );

private:
    void FillDialog();
    void FillSchemeContent(QString p_qstrDbName);
    void FillApplications();
    void OpenApplicationEditor();
    void OpenContainerEditor(QTreeWidgetItem* p_pItem);
    void OpenViewViewer(QTreeWidgetItem* p_pItem);
    void OpenClassEditor(QTreeWidgetItem* p_pItem);
    void FillLanguages();
    void UpdateActionState();
    void DisableAllContentActions();
    void EnableActionOnContext();
    void FillWorkflows();
    void InstallUiEditors();
    void OpenContainerEditor(CdmObjectContainer* p_pList);
    void OpenObjectListSearch(CdmObjectContainer* p_pList);
    void AddContextMenus();
    void OpenClassEditor(CdmClass* p_pClass);
    void OpenObjectContainerEditor(CdmObjectContainer* p_pContainer);
    CdmClassManager *GetCurrentClassManager();
    CdmPackage *GetSelectedPackage();
    void SubscribeEventMethods(CdmClassManager *pCdmClassManager);
    void setEventStoreManager();
    IdmEventStoreManager *getEventStoreManager();
    void ClearEditor();
    void OpenApplicationEditor(CwmsApplication& p_rApp);
    QMdiSubWindow* AddMdiWindow(QWidget* p_pWidget);
    void UpdateDockWidgetVisibility();
    QMdiSubWindow* FindSubWindowByUri(QString p_qstrUri);
    bool FindAndSetSubWindow(QString p_qstrUri);
    QTreeWidgetItem* GetSelectedItem();
    void FillObjectLists(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);
    void FillClasses(CdmClassManager* p_pCdmClassManager);
    void FillViews();
    void FillReports();
    void FillForms();
};

#endif //
