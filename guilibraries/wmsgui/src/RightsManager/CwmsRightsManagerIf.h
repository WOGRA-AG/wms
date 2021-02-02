/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang Graï¿½of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CwmsRightsManagerIf.h,v 1.4 2006/06/12 19:43:16 Entwicklung Exp $
 ******************************************************************************/


#ifndef CWMSRIGHTSMANAGERIF_H
#define CWMSRIGHTSMANAGERIF_H


// System and QT Includes
#include <QLinkedList>
#include <QDialog>

// WMS Includes
#include "CdmRights.h"

// own Includes
#include "wmsgui.h"
#include "ui_CwmsRightsManager.h"


// forwards
class CumAccessor;
class CumUser;
class CumUserGroup;
class CdmObjectContainer;
class CumAccessorRight;


class WMSGUI_API CwmsRightsManagerIf : public QDialog, public Ui::CwmsRightsManager
{

   Q_OBJECT
   /*
    * The objectlist which is needed to manages the rights.
    */
   private:
      CdmObjectContainer* m_rpContainer;
      QLinkedList<CumUser*> m_qvlUsers;
      QLinkedList<CumUserGroup*> m_qvlUserGroups;



   public:
   /** +-=---------------------------------------------------------Di 28. Sep 14:35:49 2010-------*
    * @method  CwmsRightsManagerIf::CwmsRightsManagerIf      // public                            *
    * @return                                                //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 14:35:49 2010----------*/
    CwmsRightsManagerIf( CdmObjectContainer* p_pContainer, QWidget* parent = NULL);

   /** +-=---------------------------------------------------------Wed Dec 21 11:35:36 2005-------*
    * @method  CwmsRightsManagerIf::~CwmsRightsManagerIf     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsRightsManagerIf                                        *
    *                                                                                             *
    *---------------------------------------------------------------Wed Dec 21 11:35:36 2005------*/
   public:
      virtual ~CwmsRightsManagerIf(  );
   protected:
   /** +-=---------------------------------------------------------So 3. Mai 13:03:32 2009--------*
    * @method  CwmsRightsManagerIf::FillDialog               // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:03:32 2009-----------*/
    virtual void FillDialog();
    protected slots:
   /** +-=---------------------------------------------------------Do 16. Aug 13:47:35 2012-------*
    * @method  CwmsRightsManagerIf::RemoveRightClickedSlot   // protected, slots                  *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 13:47:35 2012----------*/
void RemoveRightClickedSlot( );

   /** +-=---------------------------------------------------------Wed Dec 21 11:36:55 2005-------*
    * @method  CwmsRightsManagerIf::CloseClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Wed Dec 21 11:36:55 2005------*/
    private slots:
void CloseClickedSlot(  );
    protected slots:
   /** +-=---------------------------------------------------------So 3. Mai 13:01:43 2009--------*
    * @method  CwmsRightsManagerIf::AddGroupClickedSlot      // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:01:43 2009-----------*/
      virtual void AddGroupClickedSlot( );
    protected slots:
   /** +-=---------------------------------------------------------So 3. Mai 13:01:33 2009--------*
    * @method  CwmsRightsManagerIf::AddUserClickedSlot       // protected, virtual, slots         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:01:33 2009-----------*/
      virtual void AddUserClickedSlot( );


   /** +-=---------------------------------------------------------Wed Dec 21 16:12:14 2005-------*
    * @method  CwmsRightsManagerIf::FillUserGroupList        // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                               *
    * @comment                                                                                    *
    *---------------------------------------------------------------Wed Dec 21 16:12:14 2005------*/
   private:
	   void FillUserGroupList(QMap<int, EdmRight>& p_rqmAccessorRights);

   /** +-=---------------------------------------------------------Wed Dec 21 16:12:36 2005-------*
    * @method  CwmsRightsManagerIf::FillRights               // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                               *
    * @comment                                                                                    *
    *---------------------------------------------------------------Wed Dec 21 16:12:36 2005------*/
   private:
	   void FillRights(QMap<int, EdmRight>& p_rqmAccessorRights);
   protected:
   /** +-=---------------------------------------------------------So 3. Mai 13:02:33 2009--------*
    * @method  CwmsRightsManagerIf::FindUser                 // protected, virtual                *
    * @return  CumUser*                                      //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:02:33 2009-----------*/
    virtual CumUser* FindUser(long p_lUserId);
   protected:
   /** +-=---------------------------------------------------------So 3. Mai 13:02:19 2009--------*
    * @method  CwmsRightsManagerIf::FindUserGroup            // protected, virtual                *
    * @return  CumUserGroup*                                 //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:02:19 2009-----------*/
    virtual CumUserGroup* FindUserGroup(long p_lUserId);
   protected:
   /** +-=---------------------------------------------------------So 3. Mai 13:02:11 2009--------*
    * @method  CwmsRightsManagerIf::FindUserGroup            // protected, virtual                *
    * @return  CumUserGroup*                                 //                                   *
    * @param   QString p_qstrGroupName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:02:11 2009-----------*/
    virtual CumUserGroup* FindUserGroup(QString p_qstrGroupName);
   protected:
   /** +-=---------------------------------------------------------So 3. Mai 13:02:26 2009--------*
    * @method  CwmsRightsManagerIf::FindUser                 // protected, virtual                *
    * @return  CumUser*                                      //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 3. Mai 13:02:26 2009-----------*/
    virtual CumUser* FindUser(QString p_qstrLogin);

   /** +-=---------------------------------------------------------Wed Dec 21 16:11:51 2005-------*
    * @method  CwmsRightsManagerIf::FillUserList             // private                           *
    * @return  void                                          //                                   *
    * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                               *
    * @comment                                                                                    *
    *---------------------------------------------------------------Wed Dec 21 16:11:51 2005------*/
   private:
	   void FillUserList(QMap<int, EdmRight>& p_rqmAccessorRights);

   /** +-=---------------------------------------------------------Thu Dec 22 14:37:34 2005-------*
    * @method  CwmsRightsManagerIf::languageChange           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Thu Dec 22 14:37:34 2005------*/
   public:
      virtual void languageChange(  );

    protected slots:
   /** +-=---------------------------------------------------------So 3. Mai 13:01:56 2009--------*
    * @method  CwmsRightsManagerIf::RightsListViewDoubleClickedSlot // protected, virtual, slots  *
    * @return  void                                          //                                   *
    * @comment This slot changes the rights of the accessor.                                      *
    *----------------last changed: -----------------------------So 3. Mai 13:01:56 2009-----------*/
      virtual void RightsListViewDoubleClickedSlot( );

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 13:39:04 2012-------*
    * @method  CwmsRightsManagerIf::GetSelectedGroup         // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 13:39:04 2012----------*/
    QString GetSelectedGroup();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 13:38:38 2012-------*
    * @method  CwmsRightsManagerIf::GetSelectedListWidgetItem // public                           *
    * @return  QString                                       //                                   *
    * @param   QListWidget* p_pqwList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 13:38:38 2012----------*/
    QString GetSelectedListWidgetItem(QListWidget* p_pqwList);

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 13:39:46 2012-------*
    * @method  CwmsRightsManagerIf::GetSelectedUser          // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 13:39:46 2012----------*/
    QString GetSelectedUser();

   public:
   /** +-=---------------------------------------------------------Do 16. Aug 13:43:28 2012-------*
    * @method  CwmsRightsManagerIf::GetSelectedRight         // public                            *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 16. Aug 13:43:28 2012----------*/
    QTreeWidgetItem* GetSelectedRight();
};



#endif //
