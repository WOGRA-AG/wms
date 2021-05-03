/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang GraÃŸhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CWMSUNIVERSALRIGHTSMANAGERIF_H
#define CWMSUNIVERSALRIGHTSMANAGERIF_H


// System and QT Includes
#include <QList>
#include <QDialog>


// own Includes
#include "ui_CwmsRightsManager.h"


// forwards
class CumAccessor;
class CumUser;
class CumUserGroup;
class CdmObjectContainer;
class CdmRights;


class CwmsUniversalRightsManagerIf : public QDialog, public Ui::CwmsRightsManager
{

   Q_OBJECT

   private:
      CdmRights* m_rpCdmRights;
      QList<CumUser*> m_qvlUsers;
      QList<CumUserGroup*> m_qvlUserGroups;



   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:08:09 2012-------*
    * @method  CwmsUniversalRightsManagerIf::CwmsUniversalRightsManagerIf // public               *
    * @return                                                //                                   *
    * @param   CdmRights* p_pCdmRights                       //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:08:09 2012----------*/
    CwmsUniversalRightsManagerIf( CdmRights* p_pCdmRights,
                                  QWidget* parent = NULL);

   private:
   /** +-=---------------------------------------------------------Do 16. Aug 14:16:38 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FillUserList    // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:16:38 2012----------*/
    void FillUserList();

   private:
   /** +-=---------------------------------------------------------Do 16. Aug 14:16:43 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FillUserGroupList // private                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:16:43 2012----------*/
    void FillUserGroupList();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:16:25 2012-------*
    * @method  CwmsUniversalRightsManagerIf::~CwmsUniversalRightsManagerIf // public, virtual     *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsRightsManagerIf                                        *
    *----------------last changed: -----------------------------Do 16. Aug 14:16:25 2012----------*/
    virtual ~CwmsUniversalRightsManagerIf( );

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 15:00:06 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FillDialog      // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 15:00:06 2012----------*/
    virtual void FillDialog();

   private:
   /** +-=---------------------------------------------------------Do 16. Aug 14:16:53 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FillRights      // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:16:53 2012----------*/
    void FillRights();

   protected:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:02 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FindUser        // protected, virtual                *
    * @return  CumUser*                                      //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:02 2012----------*/
    virtual CumUser* FindUser(long p_lUserId);

   protected:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:18 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FindUser        // protected, virtual                *
    * @return  CumUser*                                      //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:18 2012----------*/
    virtual CumUser* FindUser(QString p_qstrLogin);

   protected:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:24 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FindUserGroup   // protected, virtual                *
    * @return  CumUserGroup*                                 //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:24 2012----------*/
    virtual CumUserGroup* FindUserGroup(long p_lUserId);

   protected:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:30 2012-------*
    * @method  CwmsUniversalRightsManagerIf::FindUserGroup   // protected, virtual                *
    * @return  CumUserGroup*                                 //                                   *
    * @param   QString p_qstrGroupName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:30 2012----------*/
    virtual CumUserGroup* FindUserGroup(QString p_qstrGroupName);

    protected slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:53 2012-------*
    * @method  CwmsUniversalRightsManagerIf::RemoveRightClickedSlot // protected, slots           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:53 2012----------*/
void RemoveRightClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:17:59 2012-------*
    * @method  CwmsUniversalRightsManagerIf::GetSelectedRight // public                           *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:17:59 2012----------*/
    QTreeWidgetItem* GetSelectedRight();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:10 2012-------*
    * @method  CwmsUniversalRightsManagerIf::GetSelectedGroup // public                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:10 2012----------*/
    QString GetSelectedGroup();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:15 2012-------*
    * @method  CwmsUniversalRightsManagerIf::GetSelectedUser // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:15 2012----------*/
    QString GetSelectedUser();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:20 2012-------*
    * @method  CwmsUniversalRightsManagerIf::GetSelectedListWidgetItem // public                  *
    * @return  QString                                       //                                   *
    * @param   QListWidget* p_pqwList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:20 2012----------*/
    QString GetSelectedListWidgetItem(QListWidget* p_pqwList);

    protected slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:25 2012-------*
    * @method  CwmsUniversalRightsManagerIf::RightsListViewDoubleClickedSlot // protected, virtual, slots*
    * @return  void                                          //                                   *
    * @comment This slot changes the rights of the accessor.                                      *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:25 2012----------*/
      virtual void RightsListViewDoubleClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:30 2012-------*
    * @method  CwmsUniversalRightsManagerIf::CloseClickedSlot // private, slots                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:30 2012----------*/
void CloseClickedSlot( );

    protected slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:35 2012-------*
    * @method  CwmsUniversalRightsManagerIf::AddGroupClickedSlot // protected, virtual, slots     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:35 2012----------*/
      virtual void AddGroupClickedSlot( );

    protected slots:
   /** +-=---------------------------------------------------------Do 16. Aug 14:18:40 2012-------*
    * @method  CwmsUniversalRightsManagerIf::AddUserClickedSlot // protected, virtual, slots      *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 14:18:40 2012----------*/
      virtual void AddUserClickedSlot( );
};

#endif //
