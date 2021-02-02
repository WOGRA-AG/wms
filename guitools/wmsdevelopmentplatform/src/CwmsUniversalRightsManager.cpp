/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// SYstem and Qt Includes


// own Includes
#include "CdmRights.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CwmsUniversalRightsManager.h"

/** +-=---------------------------------------------------------Do 16. Aug 14:08:09 2012----------*
 * @method  CwmsUniversalRightsManagerIf::CwmsUniversalRightsManagerIf // public                  *
 * @return                                                   //                                   *
 * @param   CdmRights* p_pCdmRights                          //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:08:09 2012----------*/
CwmsUniversalRightsManagerIf::CwmsUniversalRightsManagerIf(CdmRights* p_pCdmRights,
                                                           QWidget* parent)
: QDialog(parent),
  m_rpCdmRights(p_pCdmRights)
{
   setupUi(this);

   if(CHKPTR(m_rpCdmRights))
   {
      FillDialog();
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:16:25 2012----------*
 * @method  CwmsUniversalRightsManagerIf::~CwmsUniversalRightsManagerIf // public, virtual        *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsRightsManagerIf                                           *
 *----------------last changed: --------------------------------Do 16. Aug 14:16:25 2012----------*/
CwmsUniversalRightsManagerIf::~CwmsUniversalRightsManagerIf()
{

}

/** +-=---------------------------------------------------------Do 16. Aug 15:00:06 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FillDialog         // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 15:00:06 2012----------*/
void CwmsUniversalRightsManagerIf::FillDialog()
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

         FillUserList();
         FillUserGroupList();
         FillRights();
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:16:38 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FillUserList       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:16:38 2012----------*/
void CwmsUniversalRightsManagerIf::FillUserList()
{
   m_pqlbUsers->clear();
   QLinkedList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QLinkedList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUser* pCumUser = (*qvlIt);

      if(CHKPTR(pCumUser))
      {
         if(!m_rpCdmRights->HasRightConfigured(pCumUser))
         {
            m_pqlbUsers->addItem(pCumUser->GetLogin());
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:16:43 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FillUserGroupList  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:16:43 2012----------*/
void CwmsUniversalRightsManagerIf::FillUserGroupList()
{

   m_pqlbGroups->clear();
   QLinkedList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QLinkedList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CumUserGroup* pCumUserGroup = (*qvlIt);

      if(pCumUserGroup)
      {
         if(!m_rpCdmRights->HasRightConfigured(pCumUserGroup))
         {
            m_pqlbGroups->addItem(pCumUserGroup->GetGroupName());
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:16:53 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FillRights         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:16:53 2012----------*/
void CwmsUniversalRightsManagerIf::FillRights()
{
   m_pqlvRights->clear();
  
   QMap<int, EdmRight> qmRights = m_rpCdmRights->GetRights();
   QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
   QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CumAccessor* pCumAccessor = FindUser(qmIt.key());

      if(!pCumAccessor)
      {
         pCumAccessor = FindUserGroup(qmIt.key());
      }

      if(pCumAccessor)
      {
         EdmRight eDmRight = qmIt.value();

         if(eDmRight != eDmRightNone)
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
            }

            if(eDmRight == eDmRightWrite)
            {
               pqlviItem->setText(3, tr("Schreiben"));
            }
            else if(eDmRight == eDmRightRead)
            {
               pqlviItem->setText(3, tr("Lesen"));
            }
            else
            {
               pqlviItem->setText(3, tr("Ungültig"));
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:17:02 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FindUser           // protected, virtual                *
 * @return  CumUser*                                         //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:02 2012----------*/
CumUser* CwmsUniversalRightsManagerIf::FindUser(long p_lUserId)
{
   CumUser* pRet = nullptr;
   QLinkedList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QLinkedList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

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

/** +-=---------------------------------------------------------Do 16. Aug 14:17:18 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FindUser           // protected, virtual                *
 * @return  CumUser*                                         //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:18 2012----------*/
CumUser* CwmsUniversalRightsManagerIf::FindUser(QString p_qstrLogin)
{
   CumUser* pRet = nullptr;
   QLinkedList<CumUser*>::iterator qvlIt = m_qvlUsers.begin();
   QLinkedList<CumUser*>::iterator qvlItEnd = m_qvlUsers.end();

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

/** +-=---------------------------------------------------------Do 16. Aug 14:17:24 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FindUserGroup      // protected, virtual                *
 * @return  CumUserGroup*                                    //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:24 2012----------*/
CumUserGroup* CwmsUniversalRightsManagerIf::FindUserGroup(long p_lUserId)
{
   CumUserGroup* pRet = nullptr;

   QLinkedList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QLinkedList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

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

/** +-=---------------------------------------------------------Do 16. Aug 14:17:30 2012----------*
 * @method  CwmsUniversalRightsManagerIf::FindUserGroup      // protected, virtual                *
 * @return  CumUserGroup*                                    //                                   *
 * @param   QString p_qstrGroupName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:30 2012----------*/
CumUserGroup* CwmsUniversalRightsManagerIf::FindUserGroup(QString p_qstrGroupName)
{

   CumUserGroup* pRet = nullptr;

   QLinkedList<CumUserGroup*>::iterator qvlIt = m_qvlUserGroups.begin();
   QLinkedList<CumUserGroup*>::iterator qvlItEnd = m_qvlUserGroups.end();

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

/** +-=---------------------------------------------------------Do 16. Aug 14:17:53 2012----------*
 * @method  CwmsUniversalRightsManagerIf::RemoveRightClickedSlot // protected, slots              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:53 2012----------*/
void CwmsUniversalRightsManagerIf::RemoveRightClickedSlot()
{
   QTreeWidgetItem* pqlviItem = GetSelectedRight();

   if(pqlviItem)
   {
      QString qstrId = pqlviItem->text(0);
      long lId = qstrId.toLong();
      m_rpCdmRights->DeleteRight(lId);
      FillDialog();
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:17:59 2012----------*
 * @method  CwmsUniversalRightsManagerIf::GetSelectedRight   // public                            *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:17:59 2012----------*/
QTreeWidgetItem* CwmsUniversalRightsManagerIf::GetSelectedRight()
{
   QTreeWidgetItem* pItem = nullptr;
   QList<QTreeWidgetItem*> qlItems = m_pqlvRights->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:10 2012----------*
 * @method  CwmsUniversalRightsManagerIf::GetSelectedGroup   // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:10 2012----------*/
QString CwmsUniversalRightsManagerIf::GetSelectedGroup()
{
   return GetSelectedListWidgetItem(m_pqlbGroups);
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:15 2012----------*
 * @method  CwmsUniversalRightsManagerIf::GetSelectedUser    // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:15 2012----------*/
QString CwmsUniversalRightsManagerIf::GetSelectedUser()
{
   return GetSelectedListWidgetItem(m_pqlbUsers);
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:20 2012----------*
 * @method  CwmsUniversalRightsManagerIf::GetSelectedListWidgetItem // public                     *
 * @return  QString                                          //                                   *
 * @param   QListWidget* p_pqwList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:20 2012----------*/
QString CwmsUniversalRightsManagerIf::GetSelectedListWidgetItem(QListWidget* p_pqwList)
{
   QString qstrValue;
   QList<QListWidgetItem *> qlItems = p_pqwList->selectedItems();

   if (qlItems.count() > 0)
   {
      qstrValue = qlItems[0]->text();
   }

   return qstrValue;
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:25 2012----------*
 * @method  CwmsUniversalRightsManagerIf::RightsListViewDoubleClickedSlot // protected, virtual, slots*
 * @return  void                                             //                                   *
 * @comment This slot changes the rights of the accessor.                                         *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:25 2012----------*/
void CwmsUniversalRightsManagerIf::RightsListViewDoubleClickedSlot()
{
   QTreeWidgetItem* pqlviItem = GetSelectedRight();

   if(pqlviItem)
   {
      QString qstrId = pqlviItem->text(0);
      long lId = qstrId.toLong();
      QMap<int, EdmRight> qmRights = m_rpCdmRights->GetRights();

      EdmRight eDmRight = qmRights[lId];
      if(eDmRight == eDmRightWrite)
      {
         m_rpCdmRights->AddRight(lId, eDmRightRead);
         pqlviItem->setText(3, tr("Lesen"));
      }
      else
      {
         m_rpCdmRights->AddRight(lId, eDmRightWrite);
         pqlviItem->setText(3, tr("Schreiben"));
      }
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:30 2012----------*
 * @method  CwmsUniversalRightsManagerIf::CloseClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:30 2012----------*/
void CwmsUniversalRightsManagerIf::CloseClickedSlot()
{
   accept();
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:35 2012----------*
 * @method  CwmsUniversalRightsManagerIf::AddGroupClickedSlot // protected, virtual, slots        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:35 2012----------*/
void CwmsUniversalRightsManagerIf::AddGroupClickedSlot()
{
   CumUserGroup* pCumUserGroup = FindUserGroup(GetSelectedGroup());

   if(CHKPTR(pCumUserGroup))
   {
      m_rpCdmRights->AddRight(pCumUserGroup->GetId(), eDmRightWrite);
      FillDialog();
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:18:40 2012----------*
 * @method  CwmsUniversalRightsManagerIf::AddUserClickedSlot // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:18:40 2012----------*/
void CwmsUniversalRightsManagerIf::AddUserClickedSlot()
{
   CumUser* pCumUser = FindUser(GetSelectedUser());
   
   if(CHKPTR(pCumUser))
   {
      m_rpCdmRights->AddRight(pCumUser->GetId(), eDmRightWrite);
      FillDialog();
   }
}