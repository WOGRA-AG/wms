/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSOBJECTEDITOR_H
#define CWMSOBJECTEDITOR_H

// System and QT Includes
#include <QWidget>
#include <QScrollArea>
#include <qstringlist.h>
#include <qpair.h>
#include <qmap.h>
#include <QList>

// WMS Includes
#include "CdmObjectAdaptor.h"

// own Includes
#include "CwmsApplicationModule.h"
#include "ui_CwmsObjectEditor.h"
#include "wmsgui.h"

// forwards
class CwmsRuntime;
class CdmObject;
class CdmClassGroup;
class CdmClass;
class CdmValue;
class CdmMember;
class CdmEnhancedQueryProxy;
class QVBoxLayout;
class QFrame;
class QPushButton;
class QFormLayout;
class CoeValueWidget;
class QToolBar;
class QMenu;

// Type definitions
typedef QPair<QString, QString> TStringPair;

// enumeration

// defines
#ifndef NEW
#define NEW "new"
#endif

#ifndef DELETE
#define DELETE "delete"
#endif

#ifndef UPDATE
#define UPDATE "update"
#endif

/*
 * This class is a gui interface for editing objects.
 */
class WMSGUI_API CwmsObjectEditor : public QWidget, public Ui::CwmsObjectEditorClass
{
   Q_OBJECT
   private:
      QWidget* m_pqwContainter;
      CdmObjectAdaptor m_cCdmObjectAdaptor;
      bool m_bReadOnly;
      bool m_bShowEditButton;
      bool m_bHideSystemMembers;
      QStringList m_qstrlHiddenValues;
      QStringList m_qstrlReadOnlyValues;
      QStringList m_qstrlSortedMembers;
      QMap<QString, TStringPair> m_qmObjectRefs;
      QMap<QString, EdmStringDisplayType> m_qmDisplayType;
      QMap<QString, CdmEnhancedQueryProxy*> m_qmProxies;
      QList<QString> m_qlAddedMembers;
      QStringList m_qstrlFunctions;
      QMap<QPushButton*, QString> m_qmFunctionMapping;
      QString m_qstrCaptionValue;
      CdmObject* m_rpCdmPrintingTemplate;
      bool m_bOwnerMode;
      QToolBar* m_pToolBar;
      QMenu* m_pMenu;
      bool m_bIsObjEventEditor;
      QStringList m_qstrlEventClassMembers;
      bool m_bCheckEventMode;
      CoeValueWidget *m_pCoeValueWidget;
      bool m_bIsUpdateEvent;

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:05:51 2012-------*
    * @method  CwmsObjectEditor::CwmsObjectEditor              // public                            *
    * @return                                                //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Object Editor constructor.                                                     *
    *----------------last changed: -----------------------------Mi 22. Aug 10:05:51 2012----------*/
    CwmsObjectEditor( CdmObject* p_pCdmObject, QWidget* p_pqwParent = nullptr);

   /** +-=---------------------------------------------------------Fri Dec 5 14:36:55 2003--------*
    * @method  CwmsObjectEditor::~CwmsObjectEditor             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectEditor                                            *
    *                                                                                             *
    *---------------------------------------------------------------Fri Dec 5 14:36:55 2003-------*/
   public:
      virtual ~CwmsObjectEditor(  );

   /** +-=---------------------------------------------------------Fri Dec 5 14:40:42 2003--------*
    * @method  CwmsObjectEditor::AddHiddenValue            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method adds an Value which should be hidden in this editor.                *
    *---------------------------------------------------------------Fri Dec 5 14:40:42 2003-------*/
   public:
      void AddHiddenValue(  QString p_qstrKeyname );

   /** +-=---------------------------------------------------------Fri Dec 5 14:41:38 2003--------*
    * @method  CwmsObjectEditor::AddReadOnlyValue          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method adds an read only Value to the editor. Which means the dataype will *
    *          be shown, but it will not be editable.                                             *
    *---------------------------------------------------------------Fri Dec 5 14:41:38 2003-------*/
   public:
      void AddReadOnlyValue(  QString p_qstrKeyname );
   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 14:08:54 2006*
    * @method  CwmsObjectEditor::FillObjectEditor             // public                            *
    * @return  void                                          //                                   *
    * @comment Overwritten virtual method which shows the dialog.                                 *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 14:08:54 2006-----------*/
void FillObjectEditor(  );
void FillObjectEventEditor(CdmClass *pEventClass, QString eventType);
   /** +-=---------------------------------------------------------Fri Dec 5 15:19:55 2003--------*
    * @method  CwmsObjectEditor::BuildWidget                  // private                           *
    * @return  void                                          //                                   *
    * @comment This method builds the widget for all Values.                                   *
    *---------------------------------------------------------------Fri Dec 5 15:19:55 2003-------*/
   private:
      void BuildWidget(CdmClass *pClass);
      void BuildWidget();

   /** +-=---------------------------------------------------------Thu Dec 11 16:42:02 2003-------*
    * @method  CwmsObjectEditor::FindInHiddenList             // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmValue* p_pCdmValue                   //                                   *
    * @comment This method checks if a Value is in Hidden list. If found true will be returned *
    *---------------------------------------------------------------Thu Dec 11 16:42:02 2003------*/
   private:
      bool FindInHiddenList(  CdmValue* p_pCdmValue );
   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:52:23 2013-------*
    * @method  CwmsObjectEditor::IsReadOnly                  // private                           *
    * @return  bool                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method checks if a Value is in Hidden list. If found true will be returned    *
    *----------------last changed: -----------------------------Mo 11. Feb 10:52:23 2013----------*/
    bool IsReadOnly(const CdmMember* p_pCdmMember);


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 10:06:04 2012-------*
    * @method  CwmsObjectEditor::CwmsObjectEditor              // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment The Object Editor constructor.                                                     *
    *----------------last changed: -----------------------------Mi 22. Aug 10:06:04 2012----------*/
    CwmsObjectEditor( QWidget* p_pqwParent = nullptr);


   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 14:07:53 2006*
    * @method  CwmsObjectEditor::SetReadOnly                  // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bReadOnly                              //                                   *
    * @comment This emthod sets the objecteditor in readonly mode or in edit mode.                *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 14:07:53 2006-----------*/
void SetReadOnly(  bool p_bReadOnly );

   private:
   /** +-=---------------------------------------------------------Fr 6. Jan 14:08:20 2006*
    * @method  CwmsObjectEditor::IsReadOnly                   // private                           *
    * @return  bool                                          //                                   *
    * @comment returns if the object editor is readonly or not.                                   *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 14:08:20 2006-----------*/
bool IsReadOnly(  );

   public:
   /** +-=---------------------------------------------------------Fr 6. Jan 18:17:58 2006*
    * @method  CwmsObjectEditor::GetSortMemberList            // public                            *
    * @return  QValueList<qint64>                              // the list of members               *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 18:17:58 2006-----------*/
QList<qint64> GetSortMemberList(  );
QList<qint64> getEventClassMemberList(CdmClass *pClass);
   private:
   /** +-=---------------------------------------------------------Fr 6. Jan 18:14:58 2006*
    * @method  CwmsObjectEditor::FindValueByMemberId          // private                           *
    * @return  CdmValue*                                     //                                   *
    * @param  qint64 p_lMemberId                              //                                   *
    * @comment This method finds a value by MemberId                                              *
    *----------------last changed: Wolfgang Graßhof-------------Fr 6. Jan 18:14:58 2006-----------*/
CdmValue* FindValueByMemberId( qint64 p_lMemberId );

   public:
   /** +-=---------------------------------------------------------Do 19. Jan 20:16:16 2006*
    * @method  CwmsObjectEditor::SetSortedList                // public                            *
    * @return  void                                          //                                   *
    * @param   QStringList p_qstrlistSortedMembers           //                                   *
    * @comment This method sets a sorted memberlist.                                              *
    *----------------last changed: Wolfgang Graßhof-------------Do 19. Jan 20:16:16 2006----------*/
void SetSortedList(  QStringList p_qstrlistSortedMembers );

   public:
   /** +-=---------------------------------------------------------Fr 20. Jan 23:32:41 2006*
    * @method  CwmsObjectEditor::AddObjectRefData             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrObjectListKeyname               //                                   *
    * @param   QString p_qstrObjectValue                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 20. Jan 23:32:41 2006----------*/
void AddObjectRefData(  QString p_qstrValue,
                       QString p_qstrObjectListKeyname,
                       QString p_qstrObjectValue );

   public:
   /** +-=---------------------------------------------------------Mo 3. Sep 15:43:51 2012--------*
    * @method  CwmsObjectEditor::SetDisplayType               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   EdmStringDisplayType p_EoeDisplayType         //                                   *
    * @comment This method sets the displaytype for a value.                                      *
    *----------------last changed: -----------------------------Mo 3. Sep 15:43:51 2012-----------*/
    void SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_EoeDisplayType);

   public:
   /** +-=---------------------------------------------------------Fr 20. Jan 22:43:03 2006*
    * @method  CwmsObjectEditor::GetSortedMemberListFromStringList // public                       *
    * @return  QValueList<qint64>                              //                                   *
    * @comment This method creates the sorted memberlist with the helb of the string list.        *
    *----------------last changed: Wolfgang Graßhof-------------Fr 20. Jan 22:43:03 2006----------*/
QList<qint64> GetSortedMemberListFromStringList(  );
QList<qint64> getEventClassMemberListFromStringList(CdmClass *pClass);

    private slots:
   /** +-=---------------------------------------------------------Di 24. Jan 22:49:24 2006*
    * @method  CwmsObjectEditor::CaptionChangedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @param   const QString & p_qstrCaption                 //                                   *
    * @comment This slot will be called if the user changes the caption.                          *
    *----------------last changed: Wolfgang Graßhof-------------Di 24. Jan 22:49:24 2006----------*/
void CaptionChangedSlot(  const QString & p_qstrCaption );

   public:
   /** +-=---------------------------------------------------------Di 8. Mai 20:51:22 2007--------*
    * @method  CwmsObjectEditor::SetCaptionValue              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment Over this method you can set, from which value the objectcaption will be           *
    *          autmatically copied.                                                               *
    *----------------last changed: Wolfgang Graßhof-------------Di 8. Mai 20:51:22 2007-----------*/
    void SetCaptionValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 10. Jun 12:31:10 2008-------*
    * @method  CwmsObjectEditor::SetShowEditButton            // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bShow                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 10. Jun 12:31:10 2008----------*/
    void SetShowEditButton(bool p_bShow);

   public:
   /** +-=---------------------------------------------------------Di 10. Jun 16:46:58 2008-------*
    * @method  CwmsObjectEditor::ShowEditButton               // public                            *
    * @return  bool                                          //                                   *
    * @comment returns if the editbutton should be shown on objectreference.                      *
    *----------------last changed: -----------------------------Di 10. Jun 16:46:58 2008----------*/
    bool ShowEditButton();

   public:
   /** +-=---------------------------------------------------------So 10. Aug 21:44:51 2008-------*
    * @method  CwmsObjectEditor::SetSystemMembersHidden       // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bHidden                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Aug 21:44:51 2008----------*/
    void SetSystemMembersHidden(bool p_bHidden);

   private:
   /** +-=---------------------------------------------------------So 10. Aug 21:45:20 2008-------*
    * @method  CwmsObjectEditor::IsSystemMembersHidden        // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Aug 21:45:20 2008----------*/
    bool IsSystemMembersHidden();

   public:
   /** +-=---------------------------------------------------------Di 12. Aug 19:57:38 2008-------*
    * @method  CwmsObjectEditor::setObjectName                // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 12. Aug 19:57:38 2008----------*/
    void setObjectName(QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Di 12. Aug 20:11:42 2008-------*
    * @method  CwmsObjectEditor::SetObject                    // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment This method sets the object for this editor                                        *
    *----------------last changed: -----------------------------Di 12. Aug 20:11:42 2008----------*/
    void SetObject(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 12. Aug 20:12:29 2008-------*
    * @method  CwmsObjectEditor::GetObject                    // public                            *
    * @return  CdmObject*                                    //                                   *
    * @comment returns the object.                                                                *
    *----------------last changed: -----------------------------Di 12. Aug 20:12:29 2008----------*/
    CdmObject* GetObject();

   public:
   /** +-=---------------------------------------------------------Do 4. Okt 08:37:20 2012--------*
    * @method  CwmsObjectEditor::AddProxy                     // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmEnhancedQueryProxy* p_pCwmsProxy           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 4. Okt 08:37:20 2012-----------*/
    void AddProxy(QString p_qstrKeyname, CdmEnhancedQueryProxy* p_pCwmsProxy);

   private:
   /** +-=---------------------------------------------------------So 4. Nov 12:00:58 2012--------*
    * @method  CwmsObjectEditor::FillMembers                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 12:00:58 2012-----------*/
    void FillMembers();
    void FillMembers(CdmClass *pEventClass);
   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:09:07 2012--------*
    * @method  CwmsObjectEditor::AddMemberInFormLayout       // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QWidget* p_qwParent                           //                                   *
    * @param   QFormLayout* p_qLayout                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:09:07 2012-----------*/
    void AddMemberInFormLayout(QString p_qstrKeyname, QWidget* p_qwParent, QFormLayout* p_qLayout);
    void AddEventClassMemberInFormLayout(QString p_qstrKeyname, QWidget* p_qwParent, QFormLayout* p_qLayout, CdmObject *pCdmEventObject);

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 15:15:16 2012-------*
    * @method  CwmsObjectEditor::CreateMemberUi               // private                           *
    * @return  void                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqfParent                          //                                   *
    * @param   QFormLayout* p_qLayout                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 15:15:16 2012----------*/
    void CreateMemberUi(CdmValue* p_pCdmValue, QWidget* p_pqfParent, QFormLayout* p_qLayout);

   private:
   /** +-=---------------------------------------------------------So 4. Nov 11:20:29 2012--------*
    * @method  CwmsObjectEditor::FillGroups                  // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 11:20:29 2012-----------*/
    void FillGroups(CdmClass *pClass);
    void FillGroups();

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 16:12:36 2012-------*
    * @method  CwmsObjectEditor::Initialize                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 16:12:36 2012----------*/
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);

   private:
   /** +-=---------------------------------------------------------Mo 17. Sep 16:13:00 2012-------*
    * @method  CwmsObjectEditor::SetModule                    // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsApplicationModule p_cModule               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 16:13:00 2012----------*/
    void SetModule(CwmsApplicationModule p_cModule);

   private:
   /** +-=---------------------------------------------------------Di 23. Jul 12:37:05 2013-------*
    * @method  CwmsObjectEditor::ConnectRuntime              // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsRuntime* p_pRuntime                       //                                   *
    * @param   CwmsApplicationModule& p_cModule              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 23. Jul 12:37:05 2013----------*/
    void ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule& p_cModule);

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 16:21:08 2012-------*
    * @method  CwmsObjectEditor::JournalClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 16:21:08 2012----------*/
void JournalClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mo 17. Sep 16:21:38 2012-------*
    * @method  CwmsObjectEditor::PrintClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 16:21:38 2012----------*/
void PrintClickedSlot( );


   private:
   /** +-=---------------------------------------------------------So 4. Nov 11:34:58 2012--------*
    * @method  CwmsObjectEditor::HasMembersWithoutGroup      // private                           *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 11:34:58 2012-----------*/
    bool HasMembersWithoutGroup();

    private slots:
   /** +-=---------------------------------------------------------So 4. Nov 11:40:11 2012--------*
    * @method  CwmsObjectEditor::GroupChangedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 11:40:11 2012-----------*/
void GroupChangedSlot();
void GroupChangedSlot(CdmClass* pClass);
   private:
   /** +-=---------------------------------------------------------So 4. Nov 11:44:23 2012--------*
    * @method  CwmsObjectEditor::AddGroupsToListWidget       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 11:44:23 2012-----------*/
    void AddGroupsToListWidget();

   private:
   /** +-=---------------------------------------------------------So 4. Nov 11:58:51 2012--------*
    * @method  CwmsObjectEditor::BuildContainerWidget        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 11:58:51 2012-----------*/
    void BuildContainerWidget();

   private:
   /** +-=---------------------------------------------------------So 4. Nov 12:02:39 2012--------*
    * @method  CwmsObjectEditor::CountAdditionalTabs         // private                           *
    * @return  int                                           //                                   *
    * @param   CdmClassGroup* p_pCdmGroup                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 12:02:39 2012-----------*/
    int CountAdditionalTabs(CdmClassGroup* p_pCdmGroup);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:12:33 2012--------*
    * @method  CwmsObjectEditor::CountAditionalTabsforNoneGroupMembers // private                 *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:12:33 2012-----------*/
    int CountAditionalTabsforNoneGroupMembers();

   private:
   /** +-=---------------------------------------------------------So 4. Nov 12:04:13 2012--------*
    * @method  CwmsObjectEditor::NeedsMemberTab              // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 4. Nov 12:04:13 2012-----------*/
    bool NeedsMemberTab(CdmMember* p_pCdmMember);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 09:19:48 2012--------*
    * @method  CwmsObjectEditor::GetClassMembers             // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<qint64, CdmMember*>& p_rqmMembers          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 09:19:48 2012-----------*/
    void GetClassMembers(QMap<qint64, CdmMember*>& p_rqmMembers);
    void GetClassMembers(QMap<qint64, CdmMember *> &p_rqmMembers, CdmClass *pClass);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 09:19:39 2012--------*
    * @method  CwmsObjectEditor::GetMemberById               // private                           *
    * @return  CdmMember*                                    //                                   *
    * @param  qint64 p_lId                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 09:19:39 2012-----------*/
    CdmMember* GetMemberById(qint64 p_lId);
    CdmMember* GetMemberById(qint64 p_lId, CdmClass *pClass);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:16:02 2012--------*
    * @method  CwmsObjectEditor::AddMemberInTab              // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QTabWidget* p_qwParent                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:16:02 2012-----------*/
    void AddMemberInTab(QString p_qstrKeyname, QTabWidget* p_qwParent);
    void AddEventClassMemberInTab(QString p_qstrKeyname, QTabWidget* p_qwParent, CdmObject *pCdmEventObject);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 11:28:07 2012--------*
    * @method  CwmsObjectEditor::CreateTabMemberUi           // private                           *
    * @return  bool                                          //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   QWidget* p_pqfParent                          //                                   *
    * @param   QVBoxLayout* p_qLayout                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 11:28:07 2012-----------*/
    bool CreateTabMemberUi(CdmValue* p_pCdmValue, QWidget* p_pqfParent, QVBoxLayout* p_qLayout);

   private:
    void FillMembers(QList<CdmClassGroup *> &p_qlGroups);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 14:31:46 2012--------*
    * @method  CwmsObjectEditor::GetParentWidgetAndLayout    // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClassGroup* p_pGroup                       //                                   *
    * @param   QWidget*& p_rpWidget                          //                                   *
    * @param   QFormLayout*& p_rpLayout                      //                                   *
    * @param   QTabWidget*& p_rpTab                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 14:31:46 2012-----------*/
    void GetParentWidgetAndLayout(CdmClassGroup* p_pGroup,
                                  QWidget*& p_rpWidget,
                                  QFormLayout*& p_rpLayout,
                                  QTabWidget*& p_rpTab);

   private:
   /** +-=---------------------------------------------------------Mo 5. Nov 14:26:45 2012--------*
    * @method  CwmsObjectEditor::AddMember                   // private                           *
    * @return  void                                          //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   QWidget* p_pqMain                             //                                   *
    * @param   QFormLayout* p_pLayout                        //                                   *
    * @param   QTabWidget* p_pqTab                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Nov 14:26:45 2012-----------*/
    void AddMember(CdmMember* p_pCdmMember,
                   QWidget* p_pqMain,
                   QFormLayout* p_pLayout,
                   QTabWidget* p_pqTab);

    void AddEventClassMember(CdmMember* p_pCdmMember,
                             QWidget* p_pqMain,
                             QFormLayout* p_pLayout,
                             QTabWidget* p_pqTab, CdmObject *pCdmEventObject);
   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:25:00 2013-------*
    * @method  CwmsObjectEditor::CheckReadOnly               // private                           *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMeber                  //                                   *
    * @param   CoeValueWidget* p_pWidget                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 10:25:00 2013----------*/
    void CheckReadOnly(const CdmMember* p_pCdmMeber, CoeValueWidget* p_pWidget);

   public:
   /** +-=---------------------------------------------------------Mo 5. Nov 15:07:10 2012--------*
    * @method  CwmsObjectEditor::DeactivateOwnerMode         // public                            *
    * @return  void                                          //                                   *
    * @comment The owner mode is used to display in an objecteditor an objecteditor of an owned   *
    *          object. if you deactivate this mode, objectreferences which are owned will only    *
    *          be displayed as an edit button and not as a child tab.                             *
    *----------------last changed: -----------------------------Mo 5. Nov 15:07:10 2012-----------*/
    void DeactivateOwnerMode();

   private:
   /** +-=---------------------------------------------------------Fr 14. Dez 10:42:24 2012-------*
    * @method  CwmsObjectEditor::AddFunctions                // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 14. Dez 10:42:24 2012----------*/
    void AddFunctions();

    void CreateEventMemberUi(CdmValue *p_pCdmValue, QWidget *p_pqfParent, QFormLayout *p_qLayout, CdmObject *pEventObject);
    bool CreateEventTabMemberUi(CdmValue *p_pCdmValue, QWidget *p_pqfParent, QVBoxLayout *p_qLayout, CdmObject *pEventObject);
    void CheckEditable(const CdmMember *p_pCdmMeber, CoeValueWidget *p_pWidget);
    bool checkForEventMode(QString qstr_checkEventMode);

    int CountAditionalTabsforNoneGroupMembers(CdmClass *pEventClass);
    void GetGroupList(QListWidgetItem *pItem, QList<CdmClassGroup *> &p_rqlGroups);
private slots:
void FunctionClickedSlot( );

   public:

    void SetFormConfiguration(CdmObject* p_pObject);

    void setIsObjectEventEditor(bool bIsObjEEditor);
    bool getIsObjectEventEditor();
    QList<CdmValue *> getEventClassMemberValues() const;
    bool checkEventMode(QString qstr_checkEventMode);
    void GetParentWidgetAndEventLayout(CdmClassGroup *p_pGroup, QWidget *&p_rpWidget, QFormLayout *&p_rpLayout, QTabWidget *&p_rpTab, CdmClass *pEventClass);
public slots:
    void SaveClickedSlot();
    void ResetClickedSlot();
    void MetaDataClickedSlot();
};

#endif //

