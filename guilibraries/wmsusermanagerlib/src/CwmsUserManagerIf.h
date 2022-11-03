// Header is missing impl started on 22.01.2005


#ifndef CWMSUSERMANAGERIF_H
#define CWMSUSERMANAGERIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT INcludes
#include <QMainWindow>
#include <QList>
#include <QCloseEvent>

// own Includes
#include "ui_CwmsUserManager.h"
#include "wmsusermanagerglobal.h"

// forwards
class CumUserManager;
class CumUserGroup;
class CumUser;
class QVBoxLayout;


class WMSUSERMANAGER_API CwmsUserManagerIf : public QMainWindow, public Ui::CwmsUserManager
{
   Q_OBJECT

   private:
      CumUserManager*           m_rpCumUserManager;
      QList<CumUserGroup*> m_qvlUserGroups; 
      QList<CumUser*>      m_qvlUsers;
      QList<CumUser*>     m_qlUsers;
      QList<CumUserGroup*> m_qlUsergroups;
      QVBoxLayout*              m_pqvbLayout;
      QWidget*                  m_pqwEditor;


   public:
   /** +-=---------------------------------------------------------Sa 22. Jan 15:38:31 2005*
    * @method  CwmsUserManagerIf::CwmsUserManagerIf          // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @param   const char* name = NULL                       //                                   *
    * @param   WFlags fl = 0                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 22. Jan 15:38:31 2005----------*/
CwmsUserManagerIf(QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Sa 22. Jan 15:38:42 2005*
    * @method  CwmsUserManagerIf::~CwmsUserManagerIf         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsUserManagerIf                                          *
    *                                                                                             *
    *----------------last changed: -----------------------------Sa 22. Jan 15:38:42 2005----------*/
virtual ~CwmsUserManagerIf(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:29:19 2005*
    * @method  CwmsUserManagerIf::AboutSlot                  // private, const, slots             *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:29:19 2005----------*/
void AboutSlot(  ) const;

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:29:31 2005*
    * @method  CwmsUserManagerIf::DeleteGroupSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:29:31 2005----------*/
void DeleteGroupSlot(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:29:45 2005*
    * @method  CwmsUserManagerIf::DeleteUserSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:29:45 2005----------*/
void DeleteUserSlot(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:29:56 2005*
    * @method  CwmsUserManagerIf::ExitSlot                   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:29:56 2005----------*/
void ExitSlot(  );


    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:30:22 2005*
    * @method  CwmsUserManagerIf::NewGroupSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:30:22 2005----------*/
void NewGroupSlot(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:30:33 2005*
    * @method  CwmsUserManagerIf::NewUserSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:30:33 2005----------*/
void NewUserSlot(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:30:43 2005*
    * @method  CwmsUserManagerIf::RenameGroupSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:30:43 2005----------*/
void RenameGroupSlot(  );


    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:31:04 2005*
    * @method  CwmsUserManagerIf::UpdateGroupListSlot        // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:31:04 2005----------*/
void UpdateGroupListSlot(  );

    private slots:
   /** +-=---------------------------------------------------------So 23. Jan 17:31:15 2005*
    * @method  CwmsUserManagerIf::UpdateUserListSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 23. Jan 17:31:15 2005----------*/
void UpdateUserListSlot(  );

   private:
   /** +-=---------------------------------------------------------Di 25. Jan 19:12:45 2005*
    * @method  CwmsUserManagerIf::ClearGroupList             // private                           *
    * @return  void                                          //                                   *
    * @comment This method clears the list of groups.                                             *
    *----------------last changed: -----------------------------Di 25. Jan 19:12:45 2005----------*/
void ClearGroupList(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 19:32:36 2005*
    * @method  CwmsUserManagerIf::UserGroupChangedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 25. Jan 19:32:36 2005----------*/
void UserGroupChangedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 19:32:45 2005*
    * @method  CwmsUserManagerIf::UserChangedSlot            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 25. Jan 19:32:45 2005----------*/
void UserChangedSlot(  );

   private:
   /** +-=---------------------------------------------------------Di 25. Jan 19:45:53 2005*
    * @method  CwmsUserManagerIf::ClearUserList              // private                           *
    * @return  void                                          //                                   *
    * @comment This method deletes the user pointers and clears the list.                         *
    *----------------last changed: -----------------------------Di 25. Jan 19:45:53 2005----------*/
void ClearUserList(  );

   protected:
   /** +-=---------------------------------------------------------Fr 30. Dez 15:58:25 2005*
    * @method  CwmsUserManagerIf::closeEvent                 // protected                         *
    * @return  void                                          //                                   *
    * @param   QCloseEvent* p_pqCloseEvent                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Fr 30. Dez 15:58:25 2005----------*/
void closeEvent(  QCloseEvent* p_pqCloseEvent );

   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 14:47:01 2012-------*
    * @method  CwmsUserManagerIf::GetSelectedItem            // public, static                    *
    * @return  QTreeWidgetItem*                              //                                   *
    * @param   QTreeWidget* p_pWidget                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 14:47:01 2012----------*/
    static QTreeWidgetItem* GetSelectedItem(QTreeWidget* p_pWidget);

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 14:49:50 2012-------*
    * @method  CwmsUserManagerIf::FindUserGroupById          // private                           *
    * @return  CumUserGroup*                                 //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 14:49:50 2012----------*/
    CumUserGroup* FindUserGroupById(int p_iId);

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 14:57:13 2012-------*
    * @method  CwmsUserManagerIf::FindUserById               // private                           *
    * @return  CumUser*                                      //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 14:57:13 2012----------*/
    CumUser* FindUserById(int p_iId);
    QList<CumUser*> FindUserByWildCard(QString qstrSearch);
    QList<CumUserGroup*> FindUserGroupByWildCard(QString qstrSearch);

    void ClearUsers();
private slots:
    void SearchForUserSlot();
    void SearchForUserGroupSlot();
public:
    void getSearchedUsersToList();
    void getSearchedUserGroupToList();
    CwmsUserManagerIf(CumUserManager *p_pCumUserManager, QWidget *parent);
};

#endif //
