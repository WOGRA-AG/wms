/******************************************************************************
 ** WOGRA Middleware Tools WMS Enterprise Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ******************************************************************************/

#ifndef CWMSCLASSEDITORIF_H
#define CWMSCLASSEDITORIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QStringList>

// own Includes
#include "ui_CwmsClassEditor.h"


// forwards
class CdmClassMethod;
class CdmClass;
class CwmsAdminMainWindowIf;
class QListWidgetItem;
class QTreeWidgetItem;
class CdmClassValidator;
class CdmPackage;


class CwmsClassEditorIf : public QWidget, public Ui::CwmsClassEditor
{
   Q_OBJECT

   private:
      CdmClass* m_rpCdmClass;
      CwmsAdminMainWindowIf* m_rpMainWindow;
      bool m_bEditMode;
      QList<CdmClass *> m_qlCreateEventClasses;
      QList<CdmClass *> m_qlDeleteEventClasses;
      QList<CdmClass *> m_qlUpdateEventClasses;

   public:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:36:48 2012-------*
    * @method  CwmsClassEditorIf::CwmsClassEditorIf          // public                            *
    * @return                                                //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment The constructor of the classeditor. it fills the classeditor with data.            *
    *----------------last changed: -----------------------------Mo 20. Aug 15:36:48 2012----------*/
    CwmsClassEditorIf( CdmClass* p_pCdmClass, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 17. Mai 09:55:49 2007-------*
    * @method  CwmsClassEditorIf::~CwmsClassEditorIf         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsClassEditorIf                                          *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 09:55:49 2007----------*/
    virtual ~CwmsClassEditorIf( );

   private:
   /** +-=---------------------------------------------------------Do 17. Mai 10:19:07 2007-------*
    * @method  CwmsClassEditorIf::FillDialog                 // private                           *
    * @return  void                                          //                                   *
    * @comment fills the widget with relevant data.                                               *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 10:19:07 2007----------*/
    void FillDialog();

   private:
   /** +-=---------------------------------------------------------Do 17. Mai 10:18:39 2007-------*
    * @method  CwmsClassEditorIf::FillBaseClasses            // private                           *
    * @return  void                                          //                                   *
    * @comment fills the baseclasses to the listbox                                               *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 10:18:39 2007----------*/
    void FillBaseClasses();

   private:
   /** +-=---------------------------------------------------------Do 17. Mai 10:18:54 2007-------*
    * @method  CwmsClassEditorIf::FillBaseData               // private                           *
    * @return  void                                          //                                   *
    * @comment fills the class basedata to the deitfields.                                        *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 10:18:54 2007----------*/
    void FillBaseData();

   private:
   /** +-=---------------------------------------------------------Do 17. Mai 10:18:24 2007-------*
    * @method  CwmsClassEditorIf::FillMembers                // private                           *
    * @return  void                                          //                                   *
    * @comment Fills the members to the listview                                                  *
    *----------------last changed: Wolfgang Graßhof-------------Do 17. Mai 10:18:24 2007----------*/
    void FillMembers();

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:12 2008-------*
    * @method  CwmsClassEditorIf::CancelClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:12 2008----------*/
void CancelClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:20 2008-------*
    * @method  CwmsClassEditorIf::EditClickedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:20 2008----------*/
void EditClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:28 2008-------*
    * @method  CwmsClassEditorIf::UpdateClickedSlot          // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:28 2008----------*/
void UpdateClickedSlot( );

void UpdatePackage();

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:36 2008-------*
    * @method  CwmsClassEditorIf::AddBaseClassClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:36 2008----------*/
void AddBaseClassClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:45 2008-------*
    * @method  CwmsClassEditorIf::RemoveBaseClassClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:45 2008----------*/
void RemoveBaseClassClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:45:54 2008-------*
    * @method  CwmsClassEditorIf::AddMemberClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:45:54 2008----------*/
void AddMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:46:04 2008-------*
    * @method  CwmsClassEditorIf::EditMemberClickedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:46:04 2008----------*/
void EditMemberClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 19. Mai 19:46:12 2008-------*
    * @method  CwmsClassEditorIf::DeleteMemberClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 19. Mai 19:46:12 2008----------*/
void DeleteMemberClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Di 14. Aug 14:58:29 2012-------*
    * @method  CwmsClassEditorIf::GetSelectedBaseClassItem   // private                           *
    * @return  QListWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 14:58:29 2012----------*/
    QListWidgetItem* GetSelectedBaseClassItem();

   private:
   /** +-=---------------------------------------------------------Di 14. Aug 14:59:59 2012-------*
    * @method  CwmsClassEditorIf::GetSelectedMemberItem      // private                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Aug 14:59:59 2012----------*/
    QTreeWidgetItem* GetSelectedMemberItem();

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 13:58:18 2012-------*
    * @method  CwmsClassEditorIf::NewGroupClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 13:58:18 2012----------*/
void NewGroupClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 13:58:29 2012-------*
    * @method  CwmsClassEditorIf::EditGroupClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 13:58:29 2012----------*/
void EditGroupClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 13:58:40 2012-------*
    * @method  CwmsClassEditorIf::DeleteGroupClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 13:58:40 2012----------*/
void DeleteGroupClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 13:58:52 2012-------*
    * @method  CwmsClassEditorIf::MoveGroupUpClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 13:58:52 2012----------*/
void MoveGroupUpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 17. Aug 13:59:07 2012-------*
    * @method  CwmsClassEditorIf::MoveGroupDownClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 17. Aug 13:59:07 2012----------*/
void MoveGroupDownClickedSlot( );

   private:
   /** +-=---------------------------------------------------------So 4. Nov 10:48:44 2012--------*
    * @method  CwmsClassEditorIf::FillGroups                 // private                           *
    * @return  void                                          //                                   *
    * @param   int p_iSelectedId = -1                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 10:48:44 2012-----------*/
    void FillGroups(int p_iSelectedId = -1);

   public:
   /** +-=---------------------------------------------------------Mo 20. Aug 15:45:48 2012-------*
    * @method  CwmsClassEditorIf::GetSelectedGroupItem       // public                            *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 20. Aug 15:45:48 2012----------*/
    QTreeWidgetItem* GetSelectedGroupItem();

    void SetMainWindow(CwmsAdminMainWindowIf *p_pMainWindow);
private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 09:45:12 2012-------*
    * @method  CwmsClassEditorIf::SequenceClickedSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 09:45:12 2012----------*/
void SequenceClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 23. Aug 13:50:57 2012-------*
    * @method  CwmsClassEditorIf::FillValidations            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:50:57 2012----------*/
    void FillValidations();

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:51:12 2012-------*
    * @method  CwmsClassEditorIf::NewValidationClickedSlot   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:51:12 2012----------*/
void NewValidationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:51:22 2012-------*
    * @method  CwmsClassEditorIf::EditValidationClickedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:51:22 2012----------*/
void EditValidationClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:51:34 2012-------*
    * @method  CwmsClassEditorIf::DeleteValidationClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:51:34 2012----------*/
void DeleteValidationClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 23. Aug 13:51:49 2012-------*
    * @method  CwmsClassEditorIf::FillFunctions              // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:51:49 2012----------*/
    void FillFunctions();

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:51:59 2012-------*
    * @method  CwmsClassEditorIf::NewFunctionClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:51:59 2012----------*/
void NewFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:52:09 2012-------*
    * @method  CwmsClassEditorIf::EditFunctionClickedSlot    // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:52:09 2012----------*/
void EditFunctionClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 23. Aug 13:52:20 2012-------*
    * @method  CwmsClassEditorIf::DeleteFunctionClickedSlot  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 13:52:20 2012----------*/
void DeleteFunctionClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Do 23. Aug 14:10:30 2012-------*
    * @method  CwmsClassEditorIf::GetSelectedFunction        // private                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 14:10:30 2012----------*/
    QTreeWidgetItem* GetSelectedFunction();

   private:
   /** +-=---------------------------------------------------------Do 23. Aug 14:10:52 2012-------*
    * @method  CwmsClassEditorIf::GetSelectedValidation      // private                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 14:10:52 2012----------*/
    QTreeWidgetItem* GetSelectedValidation();

    private slots:
   /** +-=---------------------------------------------------------Mo 12. Nov 14:21:37 2012-------*
    * @method  CwmsClassEditorIf::ExecuteFunctionClickedSlot // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 12. Nov 14:21:37 2012----------*/
void ExecuteFunctionClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Fr 23. Nov 11:46:09 2012-------*
    * @method  CwmsClassEditorIf::FillFunctionDataToItem     // private                           *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @param   CdmClassMethod* p_pMethod                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 23. Nov 11:46:09 2012----------*/
    void FillFunctionDataToItem(QTreeWidgetItem* p_pItem, CdmClassMethod* p_pMethod);

   private:
   /** +-=---------------------------------------------------------Mo 26. Nov 12:57:22 2012-------*
    * @method  CwmsClassEditorIf::FillValidationDataToTree   // private                           *
    * @return  void                                          //                                   *
    * @param   QTreeWidgetItem* p_pItem                      //                                   *
    * @param   CdmClassValidator* p_pValidation              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 26. Nov 12:57:22 2012----------*/
    void FillValidationDataToTree(QTreeWidgetItem* p_pItem, CdmClassValidator* p_pValidation);

    private slots:
   /** +-=---------------------------------------------------------Fr 30. Nov 15:05:52 2012-------*
    * @method  CwmsClassEditorIf::DebugClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 30. Nov 15:05:52 2012----------*/
void DebugClickedSlot( );

void CurrentTabChangedSlot(int p_iPos);
void CancelEventClickedSlot();
void UpdateEventClickedSlot();
void EditEventClickedSlot();

private:
   /** +-=---------------------------------------------------------So 2. Dez 11:52:22 2012--------*
    * @method  CwmsClassEditorIf::ExecuteFunction            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 2. Dez 11:52:22 2012-----------*/
void ExecuteFunction(bool p_bDebugger);
void FillPackageData();
void FillPackageComboBox(CdmPackage *p_pPackage);

void prepareEventClassLists();
void setEventClassLists();
void FillCUDEvents();
QList<CdmClass *> getEventClasses();

QList<CdmClass *> getCreateEventClasses();
QList<CdmClass *> getDeleteEventClasses();
QList<CdmClass *> getUpdateEventClasses();

void FillCreateEvent();
void FillDeleteEvent();
void FillUpdateEvent();

void extractAndSaveEventClassesFromTextEdits();
void copyCreateEventListToCB(QStringList qstrlCreateEvents);
void copyDeleteEventListToCB(QStringList qstrlDeleteEvents);
void copyUpdateEventListToCB(QStringList qstrlUpdateEvents);
void saveEventsInClass(QStringList qstrlCreateEvents, QStringList qstrlDeleteEvents, QStringList qstrlUpdateEvents);
QList<CdmClass*> findCreateEventClasses(QStringList qstrlCreateEvents, QList<CdmClass*> qlEventClasses);
QList<CdmClass*> findDeleteEventClasses(QStringList qstrlDeleteEvents, QList<CdmClass*> qlEventClasses);
QList<CdmClass *> findUpdateEventClasses(QStringList qstrlUpdateEvents, QList<CdmClass*> qlEventClasses);
void copyCreateEventToLE(QString qstrCreateEvent);
void copyDeleteEventToLE(QString qstrDeleteEvent);
void copyUpdateEventToLE(QString qstrUpdateEvent);
signals:
    void ClassModifiedSignal();
};

#endif //



