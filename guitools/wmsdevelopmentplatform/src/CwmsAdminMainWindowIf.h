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
    QMap<long, QString>  m_qmObjectLists;
    CwmsUserManagerIf* m_pCwmsUserManager;
    CwmsRuntime* m_pRuntime;
    QTreeWidget* m_rpqCurrentWidget;
    static CwmsErrorIf* m_pCwmsErrorIf;
    CwmsScriptingEnvironment* m_pScriptEnvironment;
    CwmsErrorMessenger* m_pLogger;
    QVariantList qvl_EventList;
    IdmEventStoreManager *m_pEventStoreManager;

public:
    /** +-=---------------------------------------------------------Mi 23. Nov 12:19:22 2011-------*
    * @method  CwmsAdminMainWindowIf::CwmsAdminMainWindowIf  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 12:19:22 2011----------*/
    CwmsAdminMainWindowIf( QWidget* parent = NULL);

public:
    /** +-=---------------------------------------------------------Mi 16. Mai 16:16:14 2007-------*
    * @method  CwmsAdminMainWindowIf::~CwmsAdminMainWindowIf // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsAdminMainWindowIf                                      *
    *----------------last changed: Wolfgang Graßhof-------------Mi 16. Mai 16:16:14 2007----------*/
    virtual ~CwmsAdminMainWindowIf( );

private:
    /** +-=---------------------------------------------------------Mi 16. Mai 16:16:43 2007-------*
    * @method  CwmsAdminMainWindowIf::FillDialog             // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog after application start                               *
    *----------------last changed: Wolfgang Graßhof-------------Mi 16. Mai 16:16:43 2007----------*/
    void FillDialog();

private slots:
    /** +-=---------------------------------------------------------Mi 16. Mai 16:49:11 2007-------*
    * @method  CwmsAdminMainWindowIf::DatabaseSelectedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user selected a new database. It fills the         *
    *          listview with the content of the database.                                         *
    *----------------last changed: Wolfgang Graßhof-------------Mi 16. Mai 16:49:11 2007----------*/
    void DatabaseSelectedSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 20. Sep 08:59:04 2013-------*
    * @method  CwmsAdminMainWindowIf::DbContentSelectedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the user collected database content. it opens the      *
    *          selected item in the edit frame.                                                   *
    *----------------last changed: -----------------------------Fr 20. Sep 08:59:04 2013----------*/
    void SchemeContentSelectedSlot( );

private:
    /** +-=---------------------------------------------------------Mi 16. Mai 16:51:36 2007-------*
    * @method  CwmsAdminMainWindowIf::FillDbContent          // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDbName                          //                                   *
    * @comment This method loads the selected db and fills the conntent to the listview.          *
    *----------------last changed: Wolfgang Graßhof-------------Mi 16. Mai 16:51:36 2007----------*/
    void FillSchemeContent(QString p_qstrDbName);

protected:
    /** +-=---------------------------------------------------------Do 17. Mai 00:17:31 2007-------*
    * @method  CwmsAdminMainWindowIf::closeEvent             // protected                         *
    * @return  void                                          //                                   *
    * @param   QCloseEvent* p_pqCloseEvent                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 00:17:31 2007----------*/
    void closeEvent(QCloseEvent* p_pqCloseEvent);



private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:14:03 2008-------*
    * @method  CwmsAdminMainWindowIf::CreateClassSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:14:03 2008----------*/
    void CreateClassSlot( );

private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:14:13 2008-------*
    * @method  CwmsAdminMainWindowIf::CreateDatabaseSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:14:13 2008----------*/
    void CreateDatabaseSlot( );

private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:14:24 2008-------*
    * @method  CwmsAdminMainWindowIf::CreateObjectListSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:14:24 2008----------*/
    void CreateObjectListSlot( );

private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:14:36 2008-------*
    * @method  CwmsAdminMainWindowIf::DeleteClassSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:14:36 2008----------*/
    void DeleteClassSlot( );

private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:14:48 2008-------*
    * @method  CwmsAdminMainWindowIf::DeleteDatabaseSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:14:48 2008----------*/
    void DeleteDatabaseSlot( );

private slots:
    void DeleteObjectListSlot(QTreeWidgetItem* p_pItem);



private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:16:11 2008-------*
    * @method  CwmsAdminMainWindowIf::ObjectListRightsSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:16:11 2008----------*/
    void ObjectListRightsSlot( );

private slots:
    /** +-=---------------------------------------------------------So 18. Mai 13:18:01 2008-------*
    * @method  CwmsAdminMainWindowIf::DeleteAllObjectsSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 18. Mai 13:18:01 2008----------*/
    void DeleteAllObjectsSlot( );

public:
    /** +-=---------------------------------------------------------So 18. Mai 13:19:22 2008-------*
    * @method  CwmsAdminMainWindowIf::GetSelectedClass       // public                            *
    * @return  CdmClass*                                     //                                   *
    * @comment returns the selected class in listview. or null of no class is selected.           *
    *----------------last changed: -----------------------------So 18. Mai 13:19:22 2008----------*/
    CdmClass* GetSelectedClass();

public:
    /** +-=---------------------------------------------------------So 18. Mai 13:21:45 2008-------*
    * @method  CwmsAdminMainWindowIf::GetSelectedObjectList  // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment returns the selected Objectlist or NULL if no one is selected.                     *
    *----------------last changed: -----------------------------So 18. Mai 13:21:45 2008----------*/
    CdmObjectContainer* GetSelectedObjectList();

    CwmsScriptingEnvironment *GetScriptingEnvironment();
public slots:
    void AboutSlot();
    void DataSearchClickedSlot();
private slots:
    /** +-=---------------------------------------------------------Mo 19. Mai 19:20:12 2008-------*
    * @method  CwmsAdminMainWindowIf::DataExportSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This starts the export dlg for the selected objectlist.                            *
    *----------------last changed: -----------------------------Mo 19. Mai 19:20:12 2008----------*/
    void DataExportSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 19. Mai 19:20:33 2008-------*
    * @method  CwmsAdminMainWindowIf::CreateDocumentationSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment This method creates the DB Documentation as html file.                             *
    *----------------last changed: -----------------------------Mo 19. Mai 19:20:33 2008----------*/
    void CreateDocumentationSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 10. Nov 14:36:45 2011-------*
    * @method  CwmsAdminMainWindowIf::GenerateClassCodeSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 14:36:45 2011----------*/
    void GenerateClassCodeSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 11. Nov 18:27:58 2011-------*
    * @method  CwmsAdminMainWindowIf::GenerateDbCodeSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 11. Nov 18:27:58 2011----------*/
    void GenerateDbCodeSlot( );

private:
    /** +-=---------------------------------------------------------Di 14. Aug 11:30:27 2012-------*
    * @method  CwmsAdminMainWindowIf::GetSelectedItem        // private                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 11:30:27 2012----------*/
    QTreeWidgetItem* GetSelectedItem();


private:
    /** +-=---------------------------------------------------------Di 14. Aug 13:51:16 2012-------*
    * @method  CwmsAdminMainWindowIf::FillObjectLists        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QTreeWidgetItem* p_pqtwClass                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 13:51:16 2012----------*/
    void FillObjectLists(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);


private:
    /** +-=---------------------------------------------------------Di 14. Aug 13:56:09 2012-------*
    * @method  CwmsAdminMainWindowIf::FillClasses            // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 13:56:09 2012----------*/
    void FillClasses(CdmClassManager* p_pCdmClassManager);

private:
    /** +-=---------------------------------------------------------Di 14. Aug 14:00:16 2012-------*
    * @method  CwmsAdminMainWindowIf::FillViews              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 14:00:16 2012----------*/
    void FillViews();

private:
    /** +-=---------------------------------------------------------Do 23. Aug 16:55:48 2012-------*
    * @method  CwmsAdminMainWindowIf::FillReports            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 16:55:48 2012----------*/
    void FillReports();

public slots:
    /** +-=---------------------------------------------------------Di 14. Aug 14:21:08 2012-------*
    * @method  CwmsAdminMainWindowIf::RefreshClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 14:21:08 2012----------*/
    void RefreshClickedSlot( );


private slots:
    /** +-=---------------------------------------------------------Di 14. Aug 15:20:50 2012-------*
    * @method  CwmsAdminMainWindowIf::UserManagerSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 15:20:50 2012----------*/
    void UserManagerSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 14. Aug 15:45:30 2012-------*
    * @method  CwmsAdminMainWindowIf::OpenQueryEditorSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 15:45:30 2012----------*/
    void OpenQueryEditorSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 16. Aug 16:17:41 2012-------*
    * @method  CwmsAdminMainWindowIf::DbRightsSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 16:17:41 2012----------*/
    void SchemeRightsSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 17. Aug 15:03:21 2012-------*
    * @method  CwmsAdminMainWindowIf::DbLanguagesSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 15:03:21 2012----------*/
    void SchemeLanguagesSlot( );

private:
    /** +-=---------------------------------------------------------Do 23. Aug 16:57:30 2012-------*
    * @method  CwmsAdminMainWindowIf::FillForms              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 16:57:30 2012----------*/
    void FillForms();



private slots:
    /** +-=---------------------------------------------------------Fr 24. Aug 15:46:36 2012-------*
    * @method  CwmsAdminMainWindowIf::NewViewSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 15:46:36 2012----------*/
    void NewViewSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 24. Aug 15:46:45 2012-------*
    * @method  CwmsAdminMainWindowIf::EditViewSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 15:46:45 2012----------*/
    void EditViewSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 24. Aug 15:46:54 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteViewSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 15:46:54 2012----------*/
    void DeleteViewSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:15:05 2012-------*
    * @method  CwmsAdminMainWindowIf::LanguageChangedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:15:05 2012----------*/
    void LanguageChangedSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:15:26 2012-------*
    * @method  CwmsAdminMainWindowIf::NewReportSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:15:26 2012----------*/
    void NewReportSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:15:35 2012-------*
    * @method  CwmsAdminMainWindowIf::EditReportSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:15:35 2012----------*/
    void EditReportSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:15:45 2012-------*
    * @method  CwmsAdminMainWindowIf::ReportPropertiesSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:15:45 2012----------*/
    void ReportPropertiesSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:16:03 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteReportSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:16:03 2012----------*/
    void DeleteReportSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:16:10 2012-------*
    * @method  CwmsAdminMainWindowIf::NewFormSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:16:10 2012----------*/
    void NewFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:16:21 2012-------*
    * @method  CwmsAdminMainWindowIf::EditFormSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:16:21 2012----------*/
    void EditFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 27. Aug 15:16:29 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteFormSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 27. Aug 15:16:29 2012----------*/
    void DeleteFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mi 29. Aug 19:13:42 2012-------*
    * @method  CwmsAdminMainWindowIf::DatabaseJournalSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 19:13:42 2012----------*/
    void DatabaseJournalSlot( );

private slots:
    /** +-=---------------------------------------------------------Mi 29. Aug 19:13:54 2012-------*
    * @method  CwmsAdminMainWindowIf::ObjectListJournalSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 29. Aug 19:13:54 2012----------*/
    void ObjectListJournalSlot( );

private:
    /** +-=---------------------------------------------------------Do 30. Aug 14:42:31 2012-------*
    * @method  CwmsAdminMainWindowIf::FillApplications       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 14:42:31 2012----------*/
    void FillApplications();

private:
    /** +-=---------------------------------------------------------Do 30. Aug 16:27:31 2012-------*
    * @method  CwmsAdminMainWindowIf::OpenApplicationEditor  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:27:31 2012----------*/
    void OpenApplicationEditor();

private slots:
    /** +-=---------------------------------------------------------Do 30. Aug 16:37:43 2012-------*
    * @method  CwmsAdminMainWindowIf::NewApplicationSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:37:43 2012----------*/
    void NewApplicationSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 30. Aug 16:37:54 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteApplicationSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:37:54 2012----------*/
    void DeleteApplicationSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 30. Aug 16:38:04 2012-------*
    * @method  CwmsAdminMainWindowIf::ExecuteApplicationSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 30. Aug 16:38:04 2012----------*/
    void ExecuteApplicationSlot( );

private:
    /** +-=---------------------------------------------------------Fr 31. Aug 09:52:38 2012-------*
    * @method  CwmsAdminMainWindowIf::OpenContainerEditor   // private                           *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Aug 09:52:38 2012----------*/
    void OpenContainerEditor(QTreeWidgetItem* p_pItem);

private:
    /** +-=---------------------------------------------------------Fr 31. Aug 09:57:00 2012-------*
    * @method  CwmsAdminMainWindowIf::OpenViewViewer         // private                           *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Aug 09:57:00 2012----------*/
    void OpenViewViewer(QTreeWidgetItem* p_pItem);

private:
    /** +-=---------------------------------------------------------Fr 31. Aug 09:58:50 2012-------*
    * @method  CwmsAdminMainWindowIf::OpenClassEditor        // private                           *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Aug 09:58:50 2012----------*/
    void OpenClassEditor(QTreeWidgetItem* p_pItem);

private:
    /** +-=---------------------------------------------------------Mi 5. Sep 13:33:50 2012--------*
    * @method  CwmsAdminMainWindowIf::FillLanguages          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 5. Sep 13:33:50 2012-----------*/
    void FillLanguages();

private slots:
    /** +-=---------------------------------------------------------Do 6. Sep 15:48:17 2012--------*
    * @method  CwmsAdminMainWindowIf::ExportJsonSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 6. Sep 15:48:17 2012-----------*/
    void ExportJsonSlot( );


private slots:
    /** +-=---------------------------------------------------------Mo 10. Sep 16:37:03 2012-------*
    * @method  CwmsAdminMainWindowIf::NewGenericObjectFormSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:37:03 2012----------*/
    void NewGenericObjectFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 10. Sep 16:37:27 2012-------*
    * @method  CwmsAdminMainWindowIf::NewObjectObjectListFormSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:37:27 2012----------*/
    void NewObjectObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 10. Sep 16:38:00 2012-------*
    * @method  CwmsAdminMainWindowIf::NewStandardObjectListFormSlot // private, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:38:00 2012----------*/
    void NewStandardObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 10. Sep 16:38:20 2012-------*
    * @method  CwmsAdminMainWindowIf::NewUserDefinedFormSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:38:20 2012----------*/
    void NewUserDefinedFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 14:24:59 2012-------*
    * @method  CwmsAdminMainWindowIf::NewViewObjectListFormSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 14:24:59 2012----------*/
    void NewViewObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:42:00 2012-------*
    * @method  CwmsAdminMainWindowIf::EditSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:42:00 2012----------*/
    void EditSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:42:10 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:42:10 2012----------*/
    void DeleteSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:46:36 2012-------*
    * @method  CwmsAdminMainWindowIf::EditFunctionSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:46:36 2012----------*/
    void EditFunctionSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:46:46 2012-------*
    * @method  CwmsAdminMainWindowIf::EditMemberSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:46:46 2012----------*/
    void EditMemberSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:46:59 2012-------*
    * @method  CwmsAdminMainWindowIf::EditObjectListSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:46:59 2012----------*/
    void EditObjectListSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:47:17 2012-------*
    * @method  CwmsAdminMainWindowIf::EditViewObjectListFormSlot // private, slots                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:47:17 2012----------*/
    void EditViewObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:49:47 2012-------*
    * @method  CwmsAdminMainWindowIf::EditUserDefinedFormSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:49:47 2012----------*/
    void EditUserDefinedFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:51:21 2012-------*
    * @method  CwmsAdminMainWindowIf::EditStandardObjectListFormSlot // private, slots            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:51:21 2012----------*/
    void EditStandardObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:52:16 2012-------*
    * @method  CwmsAdminMainWindowIf::EditObjectObjectListFormSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:52:16 2012----------*/
    void EditObjectObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:55:37 2012-------*
    * @method  CwmsAdminMainWindowIf::EditGenericObjectFormSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:55:37 2012----------*/
    void EditGenericObjectFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:58:13 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteMemberSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:58:13 2012----------*/
    void DeleteMemberSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:58:25 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteFunctionSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:58:25 2012----------*/
    void DeleteFunctionSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:58:44 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteViewObjectListFormSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:58:44 2012----------*/
    void DeleteViewObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 18:59:31 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteUserDefinedFormSlot // private, slots                 *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 18:59:31 2012----------*/
    void DeleteUserDefinedFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 19:00:01 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteStandardObjectListFormSlot // private, slots          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 19:00:01 2012----------*/
    void DeleteStandardObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 19:00:30 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteObjectObjectListFormSlot // private, slots            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 19:00:30 2012----------*/
    void DeleteObjectObjectListFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 11. Sep 19:01:02 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteGenericObjectFormSlot // private, slots               *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 11. Sep 19:01:02 2012----------*/
    void DeleteGenericObjectFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Mi 12. Sep 09:52:01 2012-------*
    * @method  CwmsAdminMainWindowIf::CustomContextMenuSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QPoint & p_Pos                          //                                   *
    * @comment CustomContextMenuSlot(const QPoint &))                                             *
    *----------------last changed: -----------------------------Mi 12. Sep 09:52:01 2012----------*/
    void CustomContextMenuSlot( const QPoint & p_Pos);

private:
    /** +-=---------------------------------------------------------Mi 12. Sep 09:53:48 2012-------*
    * @method  CwmsAdminMainWindowIf::UpdateActionState      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 09:53:48 2012----------*/
    void UpdateActionState();

private:
    /** +-=---------------------------------------------------------Mi 12. Sep 09:54:36 2012-------*
    * @method  CwmsAdminMainWindowIf::DisableAllContentActions // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 09:54:36 2012----------*/
    void DisableAllContentActions();

private:
    /** +-=---------------------------------------------------------Mi 12. Sep 10:03:46 2012-------*
    * @method  CwmsAdminMainWindowIf::EnableActionOnContext  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 10:03:46 2012----------*/
    void EnableActionOnContext();

private slots:
    /** +-=---------------------------------------------------------Di 18. Sep 09:21:50 2012-------*
    * @method  CwmsAdminMainWindowIf::NewSearchFormSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 09:21:50 2012----------*/
    void NewSearchFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 18. Sep 09:27:21 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteSearchFormSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 09:27:21 2012----------*/
    void DeleteSearchFormSlot( );

private slots:
    /** +-=---------------------------------------------------------Di 18. Sep 09:27:30 2012-------*
    * @method  CwmsAdminMainWindowIf::EditSearchFormSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 18. Sep 09:27:30 2012----------*/
    void EditSearchFormSlot( );

private:
    /** +-=---------------------------------------------------------Mi 24. Okt 15:29:28 2012-------*
    * @method  CwmsAdminMainWindowIf::FillWorkflows          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 15:29:28 2012----------*/
    void FillWorkflows();

private slots:
    /** +-=---------------------------------------------------------Mi 24. Okt 17:44:04 2012-------*
    * @method  CwmsAdminMainWindowIf::NewWorkflowSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 17:44:04 2012----------*/
    void NewWorkflowSlot( );

private slots:
    /** +-=---------------------------------------------------------Mi 24. Okt 17:44:13 2012-------*
    * @method  CwmsAdminMainWindowIf::EditWorkflowSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 17:44:13 2012----------*/
    void EditWorkflowSlot( );

private slots:
    /** +-=---------------------------------------------------------Mi 24. Okt 17:44:22 2012-------*
    * @method  CwmsAdminMainWindowIf::DeleteWorkflowSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 24. Okt 17:44:22 2012----------*/
    void DeleteWorkflowSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 25. Okt 14:51:32 2012-------*
    * @method  CwmsAdminMainWindowIf::WorkflowTeamsSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 14:51:32 2012----------*/
    void WorkflowTeamsSlot( );


protected:
    /** +-=---------------------------------------------------------Di 13. Nov 13:24:30 2012-------*
    * @method  CwmsAdminMainWindowIf::InstallBaseFunctionsToExecutor // protected, virtual        *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 13:24:30 2012----------*/
    virtual void InstallBaseFunctionsToExecutor();

private slots:
    /** +-=---------------------------------------------------------Mi 21. Nov 16:26:32 2012-------*
    * @method  CwmsAdminMainWindowIf::SmtpSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 16:26:32 2012----------*/
    void SmtpSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 3. Dez 10:37:19 2012--------*
    * @method  CwmsAdminMainWindowIf::ExportDeploymentFileSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 10:37:19 2012-----------*/
    void ExportDeploymentFileSlot( );

private slots:
    /** +-=---------------------------------------------------------Mo 3. Dez 10:37:32 2012--------*
    * @method  CwmsAdminMainWindowIf::ImportDeploymentFileSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 10:37:32 2012-----------*/
    void ImportDeploymentFileSlot( );

private slots:
    /** +-=---------------------------------------------------------Do 13. Dez 15:26:51 2012-------*
    * @method  CwmsAdminMainWindowIf::ObjectListPropertiesSlot // private, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 15:26:51 2012----------*/
    void ObjectListPropertiesSlot( );

private:
    /** +-=---------------------------------------------------------So 30. Dez 13:52:52 2012-------*
    * @method  CwmsAdminMainWindowIf::InstallUiEditors       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 13:52:52 2012----------*/
    void InstallUiEditors();

private:
    /** +-=---------------------------------------------------------Di 15. Jan 14:49:40 2013-------*
    * @method  CwmsAdminMainWindowIf::OpenContainerEditor   // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 15. Jan 14:49:40 2013----------*/
    void OpenContainerEditor(CdmObjectContainer* p_pList);

private:
    /** +-=---------------------------------------------------------Di 15. Jan 14:51:29 2013-------*
    * @method  CwmsAdminMainWindowIf::OpenObjectListSearch   // private                           *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 15. Jan 14:51:29 2013----------*/
    void OpenObjectListSearch(CdmObjectContainer* p_pList);

private slots:
    /** +-=---------------------------------------------------------Mi 4. Sep 19:58:50 2013--------*
    * @method  CwmsAdminMainWindowIf::ClientSettingsSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 4. Sep 19:58:50 2013-----------*/
    void ClientSettingsSlot( );

protected:
    /** +-=---------------------------------------------------------So 8. Sep 10:25:26 2013--------*
    * @method  CwmsAdminMainWindowIf::CreateErrorDlg         // protected                         *
    * @return  void                                          //                                   *
    * @comment Creates the error dlg for displaying error messages in Debug Mode.                 *
    *----------------last changed: -----------------------------So 8. Sep 10:25:26 2013-----------*/
    void CreateErrorDlg();

private slots:
    /** +-=---------------------------------------------------------So 8. Sep 10:33:22 2013--------*
    * @method  CwmsAdminMainWindowIf::LoggerClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 8. Sep 10:33:22 2013-----------*/
    void LoggerClickedSlot( );

private slots:
    /** +-=---------------------------------------------------------So 8. Sep 11:45:17 2013--------*
    * @method  CwmsAdminMainWindowIf::RestoreWindowsSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 8. Sep 11:45:17 2013-----------*/
    void RestoreWindowsSlot( );







private:
    /** +-=---------------------------------------------------------So 8. Sep 20:53:19 2013--------*
    * @method  CwmsAdminMainWindowIf::ClearEditor            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 8. Sep 20:53:19 2013-----------*/
    void ClearEditor();

private:
    /** +-=---------------------------------------------------------Fr 13. Sep 14:47:11 2013-------*
    * @method  CwmsAdminMainWindowIf::OpenApplicationEditor  // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplication& p_rApp                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Sep 14:47:11 2013----------*/
    void OpenApplicationEditor(CwmsApplication& p_rApp);

private:
    /** +-=---------------------------------------------------------Fr 13. Sep 15:19:15 2013-------*
    * @method  CwmsAdminMainWindowIf::AddMdiWindow           // private                           *
    * @return  QMdiSubWindow*                                //                                   *
    * @param   QWidget* p_pWidget                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Sep 15:19:15 2013----------*/
    QMdiSubWindow* AddMdiWindow(QWidget* p_pWidget);

private:
    /** +-=---------------------------------------------------------Sa 14. Sep 12:51:10 2013-------*
    * @method  CwmsAdminMainWindowIf::UpdateDockWidgetVisibility // private                       *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Sep 12:51:10 2013----------*/
    void UpdateDockWidgetVisibility();

private:
    /** +-=---------------------------------------------------------Di 17. Sep 18:41:26 2013-------*
    * @method  CwmsAdminMainWindowIf::FindSubWindowByUri     // private                           *
    * @return  QMdiSubWindow*                                //                                   *
    * @param   QString p_qstrUri                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 17. Sep 18:41:26 2013----------*/
    QMdiSubWindow* FindSubWindowByUri(QString p_qstrUri);

private:
    /** +-=---------------------------------------------------------Di 17. Sep 18:58:19 2013-------*
    * @method  CwmsAdminMainWindowIf::FindAndSetSubWindow    // private                           *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrUri                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 17. Sep 18:58:19 2013----------*/
    bool FindAndSetSubWindow(QString p_qstrUri);

private slots:
    /** +-=---------------------------------------------------------Mi 18. Sep 11:48:48 2013-------*
    * @method  CwmsAdminMainWindowIf::ClassFilterChangedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Sep 11:48:48 2013----------*/
    void ClassFilterChangedSlot( );

private slots:
    /** +-=---------------------------------------------------------Fr 20. Sep 08:08:12 2013-------*
    * @method  CwmsAdminMainWindowIf::EditSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 08:08:12 2013----------*/
    void EditSlot( QTreeWidgetItem* p_pItem);

private slots:
    /** +-=---------------------------------------------------------Fr 20. Sep 08:57:46 2013-------*
    * @method  CwmsAdminMainWindowIf::CurrentTreeWidgetChangedSlot // private, slots              *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Sep 08:57:46 2013----------*/
    void CurrentTreeWidgetChangedSlot( );

private slots:
    void ServerPluginsSlot();
    void AdminPluginsSlot();
    void NewLibrarySlot();
    void EditLibrarySlot();
    void EditResourceSlot();
    void DeleteResourceSlot();
    void DeleteLibrarySlot();
    void LdapSettingsSlot();
    void ClassModifiedSlot();
private:
    /** +-=---------------------------------------------------------Mo 23. Sep 08:30:15 2013-------*
    * @method  CwmsAdminMainWindowIf::AddContextMenus        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 08:30:15 2013----------*/
    void AddContextMenus();

private:
    /** +-=---------------------------------------------------------Mo 23. Sep 19:56:07 2013-------*
    * @method  CwmsAdminMainWindowIf::OpenClassEditor        // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pClass                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 19:56:07 2013----------*/
    void OpenClassEditor(CdmClass* p_pClass);

private:
    /** +-=---------------------------------------------------------Mo 23. Sep 19:57:59 2013-------*
    * @method  CwmsAdminMainWindowIf::OpenObjectContainerEditor // private                        *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Sep 19:57:59 2013----------*/
    void OpenObjectContainerEditor(CdmObjectContainer* p_pContainer);

    CdmClassManager *GetCurrentClassManager();
    CdmPackage *GetSelectedPackage();
    void SubscribeEventMethods(CdmClassManager *pCdmClassManager);
    void setEventStoreManager();
    IdmEventStoreManager *getEventStoreManager();
public:
    void CloseClassRelatedUis(CdmClass *p_pClass);
    CdmObjectContainer *GetContainerFromItem(QTreeWidgetItem *p_pItem);
    QList<QTreeWidgetItem *> GetSelectedItems();
    void CloseClassRelatedContainerUis(CdmClass *p_pClass);

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
};

#endif //
