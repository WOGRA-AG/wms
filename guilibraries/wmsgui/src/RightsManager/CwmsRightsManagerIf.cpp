/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and Qt Includes

// own Includes
#include "CumAccessorRight.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CwmsRightsManagerIf.h"

/** +-=---------------------------------------------------------Di 28. Sep 14:35:49 2010----------*
 * @method  CwmsRightsManagerIf::CwmsRightsManagerIf         // public                            *
 * @return                                                   //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 14:35:49 2010----------*/
CwmsRightsManagerIf::CwmsRightsManagerIf(CdmObjectContainer* p_pContainer,
                                         QWidget* parent)
   : QDialog(parent),
  m_rpContainer(p_pContainer)
{
   setupUi(this);

   if(CHKPTR(m_rpContainer))
   {
      FillDialog();
   }
}

/** +-=---------------------------------------------------------Wed Dec 21 11:35:36 2005----------*
 * @method  CwmsRightsManagerIf::~CwmsRightsManagerIf        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsRightsManagerIf                                           *
 *                                                                                                *
 *---------------------------------------------------------------Wed Dec 21 11:35:36 2005---------*/
CwmsRightsManagerIf::~CwmsRightsManagerIf(  )
{
}

/** +-=---------------------------------------------------------So 3. Mai 13:03:32 2009-----------*
 * @method  CwmsRightsManagerIf::FillDialog                  // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:03:32 2009-----------*/
void CwmsRightsManagerIf::FillDialog()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if(CHKPTR(pCumUserManager))
      {
         if(m_qvlUserGroups.isEmpty())
         {
            pCumUserManager->GetUserGroupList(m_qvlUserGroups);
         }

         if(m_qvlUsers.isEmpty())
         {
            pCumUserManager->GetUserListUnmanaged(m_qvlUsers);
         }

         QMap<int, EdmRight> qmRights = m_rpContainer->GetAccessorMap();

         FillUserList(qmRights);
         FillUserGroupList(qmRights);
         FillRights(qmRights);
      }
   }
}

/** +-=---------------------------------------------------------Wed Dec 21 16:11:51 2005----------*
 * @method  CwmsRightsManagerIf::FillUserList                // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                                  *
 * @comment                                                                                       *
 *---------------------------------------------------------------Wed Dec 21 16:11:51 2005---------*/
void CwmsRightsManagerIf::FillUserList(QMap<int, EdmRight>& p_rqmAccessorRights)
{
   m_pqlbUsers->clear();
   QList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUser* pCumUser = (*qvlIt);

      if(CHKPTR(pCumUser))
      {
         if(!p_rqmAccessorRights.contains(pCumUser->GetId()))
         {
            m_pqlbUsers->addItem(pCumUser->GetLogin());
         }
      }
   }
}

/** +-=---------------------------------------------------------Wed Dec 21 16:12:14 2005----------*
 * @method  CwmsRightsManagerIf::FillUserGroupList           // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                                  *
 * @comment                                                                                       *
 *---------------------------------------------------------------Wed Dec 21 16:12:14 2005---------*/
void CwmsRightsManagerIf::FillUserGroupList(QMap<int, EdmRight>& p_rqmAccessorRights)
{
   m_pqlbGroups->clear();
   QList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUserGroup* pCumUserGroup = (*qvlIt);

      if(pCumUserGroup)
      {
         if(!p_rqmAccessorRights.contains(pCumUserGroup->GetId()))
         {
            m_pqlbGroups->addItem(pCumUserGroup->GetGroupName());
         }
      }
   }
}

/** +-=---------------------------------------------------------Wed Dec 21 16:12:36 2005----------*
 * @method  CwmsRightsManagerIf::FillRights                  // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long, CumAccessorRight*>& p_rqmAccessorRights//                                  *
 * @comment                                                                                       *
 *---------------------------------------------------------------Wed Dec 21 16:12:36 2005---------*/
void CwmsRightsManagerIf::FillRights(QMap<int, EdmRight>& p_rqmAccessorRights)
{

   m_pqlvRights->clear();
   QMap<int, EdmRight>::iterator qmIt = p_rqmAccessorRights.begin();
   QMap<int, EdmRight>::iterator qmItEnd = p_rqmAccessorRights.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CumAccessor* pCumAccessor = FindUser(qmIt.key());

      if(!pCumAccessor)
      {
         pCumAccessor = FindUserGroup(qmIt.key());
      }

      if(pCumAccessor)
      {
		  EdmRight eRight = qmIt.value();

		  if (eRight)
         {
            QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvRights);

            if(pCumAccessor->IsUser())
            {
               CumUser* pCumUser = (CumUser*)pCumAccessor;
               // fill listview
               pqlviItem->setText(0, QString::number(pCumUser->GetId()));
               pqlviItem->setText(1, pCumUser->GetLogin());
               pqlviItem->setText(2, tr("Anwender"));
            }
            else if(pCumAccessor->IsGroup())
            {
               CumUserGroup* pCumUserGroup = (CumUserGroup*)pCumAccessor;
               // fill listview
               pqlviItem->setText(0, QString::number(pCumUserGroup->GetId()));
               pqlviItem->setText(1, pCumUserGroup->GetGroupName());
               pqlviItem->setText(2, tr("Gruppe"));
            }
            else
            {
               FATAL("Wrong Accessortype!!");
               DELPTR(pqlviItem);
            }

            if (pqlviItem)
            {
				if (eRight == eDmRightWrite)
               {
                  pqlviItem->setText(3, tr("Schreiben"));
               }
				else if (eRight == eDmRightRead)
               {
                  pqlviItem->setText(3, tr("Lesen"));
               }
               else
               {
                  pqlviItem->setText(3, tr("keine Berechtigung"));
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------So 3. Mai 13:02:33 2009-----------*
 * @method  CwmsRightsManagerIf::FindUser                    // protected, virtual                *
 * @return  CumUser*                                         //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:02:33 2009-----------*/
CumUser* CwmsRightsManagerIf::FindUser(long p_lUserId)
{
   CumUser* pRet = nullptr;
   QList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUser* pCumUser = (*qvlIt);

      if(CHKPTR(pCumUser) && pCumUser->GetId() == p_lUserId)
      {
         pRet = pCumUser;
         break;
      }
   }

   return pRet;
}

/** +-=---------------------------------------------------------So 3. Mai 13:02:26 2009-----------*
 * @method  CwmsRightsManagerIf::FindUser                    // protected, virtual                *
 * @return  CumUser*                                         //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:02:26 2009-----------*/
CumUser* CwmsRightsManagerIf::FindUser(QString p_qstrLogin)
{
   CumUser* pRet = nullptr;
   QList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUser* pCumUser = (*qvlIt);

      if(CHKPTR(pCumUser) && pCumUser->GetLogin() == p_qstrLogin)
      {
         pRet = pCumUser;
         break;
      }
   }

   return pRet;
}

/** +-=---------------------------------------------------------So 3. Mai 13:02:19 2009-----------*
 * @method  CwmsRightsManagerIf::FindUserGroup               // protected, virtual                *
 * @return  CumUserGroup*                                    //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:02:19 2009-----------*/
CumUserGroup* CwmsRightsManagerIf::FindUserGroup(long p_lUserId)
{

   CumUserGroup* pRet = nullptr;

   QList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUserGroup* pCumUserGroup = (*qvlIt);

      if(pCumUserGroup && pCumUserGroup->GetId() == p_lUserId)
      { 
         pRet = pCumUserGroup;
         break;
      }
   }

   return pRet;
}

/** +-=---------------------------------------------------------So 3. Mai 13:02:11 2009-----------*
 * @method  CwmsRightsManagerIf::FindUserGroup               // protected, virtual                *
 * @return  CumUserGroup*                                    //                                   *
 * @param   QString p_qstrGroupName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:02:11 2009-----------*/
CumUserGroup* CwmsRightsManagerIf::FindUserGroup(QString p_qstrGroupName)
{
   CumUserGroup* pRet = nullptr;

   QList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUserGroup* pCumUserGroup = (*qvlIt);

      if(pCumUserGroup && pCumUserGroup->GetGroupName() == p_qstrGroupName)
      { 
         pRet = pCumUserGroup;
         break;
      }
   }

   return pRet;
}

/** +-=---------------------------------------------------------Do 16. Aug 13:47:35 2012----------*
 * @method  CwmsRightsManagerIf::RemoveRightClickedSlot      // protected, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 13:47:35 2012----------*/
void CwmsRightsManagerIf::RemoveRightClickedSlot()
{
   QTreeWidgetItem* pqlviItem = GetSelectedRight();

   if(pqlviItem)
   {
      QString qstrId = pqlviItem->text(0);
      long lId = qstrId.toLong();
      m_rpContainer->RemoveAccessorRight(lId);
      FillDialog();
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 13:43:28 2012----------*
 * @method  CwmsRightsManagerIf::GetSelectedRight            // public                            *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 13:43:28 2012----------*/
QTreeWidgetItem* CwmsRightsManagerIf::GetSelectedRight()
{
   QTreeWidgetItem* pItem = nullptr;
   QList<QTreeWidgetItem*> qlItems = m_pqlvRights->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Do 16. Aug 13:39:04 2012----------*
 * @method  CwmsRightsManagerIf::GetSelectedGroup            // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 13:39:04 2012----------*/
QString CwmsRightsManagerIf::GetSelectedGroup()
{
   return GetSelectedListWidgetItem(m_pqlbGroups);
}

/** +-=---------------------------------------------------------Do 16. Aug 13:39:46 2012----------*
 * @method  CwmsRightsManagerIf::GetSelectedUser             // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 13:39:46 2012----------*/
QString CwmsRightsManagerIf::GetSelectedUser()
{
   return GetSelectedListWidgetItem(m_pqlbUsers);
}

/** +-=---------------------------------------------------------Do 16. Aug 13:38:38 2012----------*
 * @method  CwmsRightsManagerIf::GetSelectedListWidgetItem   // public                            *
 * @return  QString                                          //                                   *
 * @param   QListWidget* p_pqwList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 13:38:38 2012----------*/
QString CwmsRightsManagerIf::GetSelectedListWidgetItem(QListWidget* p_pqwList)
{
   QString qstrValue;
   QList<QListWidgetItem *> qlItems = p_pqwList->selectedItems();

   if (qlItems.count() > 0)
   {
      qstrValue = qlItems[0]->text();
   }

   return qstrValue;
}

/** +-=---------------------------------------------------------So 3. Mai 13:01:56 2009-----------*
 * @method  CwmsRightsManagerIf::RightsListViewDoubleClickedSlot // protected, virtual, slots     *
 * @return  void                                             //                                   *
 * @comment This slot changes the rights of the accessor.                                         *
 *----------------last changed: --------------------------------So 3. Mai 13:01:56 2009-----------*/
void CwmsRightsManagerIf::RightsListViewDoubleClickedSlot()
{
   QTreeWidgetItem* pqlviItem = GetSelectedRight();

   if(pqlviItem)
   {
      QString qstrId = pqlviItem->text(0);
      long lId = qstrId.toLong();
      const CdmRights& cRights = m_rpContainer->GetRights();

	  if (cRights.HasWriteAccess(lId))
      {
		 m_rpContainer->UpdateAccessorRight(lId, eDmRightRead);
         pqlviItem->setText(3, tr("Lesen"));
      }
      else
      {
		  m_rpContainer->UpdateAccessorRight(lId, eDmRightWrite);
		  pqlviItem->setText(3, tr("Schreiben"));
      }
   }
}

/** +-=---------------------------------------------------------Wed Dec 21 11:36:55 2005----------*
 * @method  CwmsRightsManagerIf::CloseClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Wed Dec 21 11:36:55 2005---------*/
void CwmsRightsManagerIf::CloseClickedSlot(  )
{
   m_rpContainer->Commit();
   accept();
}

/** +-=---------------------------------------------------------So 3. Mai 13:01:43 2009-----------*
 * @method  CwmsRightsManagerIf::AddGroupClickedSlot         // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:01:43 2009-----------*/
void CwmsRightsManagerIf::AddGroupClickedSlot()
{
   CumUserGroup* pCumUserGroup = FindUserGroup(GetSelectedGroup());

   if(CHKPTR(pCumUserGroup))
   {
      m_rpContainer->AddAccessorRight(pCumUserGroup->GetId(), eDmRightWrite);
      FillDialog();
   }
}

/** +-=---------------------------------------------------------So 3. Mai 13:01:33 2009-----------*
 * @method  CwmsRightsManagerIf::AddUserClickedSlot          // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 3. Mai 13:01:33 2009-----------*/
void CwmsRightsManagerIf::AddUserClickedSlot()
{
   CumUser* pCumUser = FindUser(GetSelectedUser());
   
   if(CHKPTR(pCumUser))
   {
      m_rpContainer->AddAccessorRight(pCumUser->GetId(), eDmRightWrite);
      FillDialog();
   }
}


/** +-=---------------------------------------------------------Thu Dec 22 14:37:34 2005----------*
 * @method  CwmsRightsManagerIf::languageChange              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Thu Dec 22 14:37:34 2005---------*/
void CwmsRightsManagerIf::languageChange(  )
{
}
