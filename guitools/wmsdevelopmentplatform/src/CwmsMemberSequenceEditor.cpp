/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsMemberSequenceEditor.cpp
 ** Started Implementation: 2012/08/22
 ** Description:
 **
 ** implements the editor for the member sequence
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMap>

// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"

// own Includes
#include "CwmsMemberSequenceEditor.h"

/** +-=---------------------------------------------------------Mi 22. Aug 17:48:07 2012----------*
 * @method  CwmsMemberSequenceEditor::CwmsMemberSequenceEditor // public                          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:48:07 2012----------*/
CwmsMemberSequenceEditor::CwmsMemberSequenceEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
m_rpCdmClass(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:48:31 2012----------*
 * @method  CwmsMemberSequenceEditor::~CwmsMemberSequenceEditor // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsMemberSequenceEditor                                      *
 *----------------last changed: --------------------------------Mi 22. Aug 17:48:31 2012----------*/
CwmsMemberSequenceEditor::~CwmsMemberSequenceEditor()
{
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:48:49 2012----------*
 * @method  CwmsMemberSequenceEditor::FillDialog             // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:48:49 2012----------*/
void CwmsMemberSequenceEditor::FillDialog(CdmClass* p_pCdmClass)
{
   m_rpCdmClass = p_pCdmClass;

   if (CHKPTR(m_rpCdmClass))
   {
      QVector<QString> qvSequence = m_rpCdmClass->GetMemberSequence();

      if (qvSequence.count() > 0)
      {
         FillGroupsAndMembers(qvSequence);
      }
      else
      {
         FillGroupsAndMembers();
      }
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:58:41 2012----------*
 * @method  CwmsMemberSequenceEditor::FillGroupsAndMembers   // private                           *
 * @return  void                                             //                                   *
 * @param   QVector<QString>& p_rqvHash                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:58:41 2012----------*/
void CwmsMemberSequenceEditor::FillGroupsAndMembers(QVector<QString>& p_rqvHash)
{
   FillGroups(); 
   FillMembers(p_rqvHash);
   FillMembersNotInHash(p_rqvHash);

   QTreeWidgetItem* pqtItem = m_qmGroups[nullptr];

   if (pqtItem && pqtItem->childCount() == 0)
   {
      DELPTR(pqtItem);
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:51:52 2012----------*
 * @method  CwmsMemberSequenceEditor::FillGroupsAndMembers   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:51:52 2012----------*/
void CwmsMemberSequenceEditor::FillGroupsAndMembers()
{
   FillGroups();
   FillMembers();

   QTreeWidgetItem* pqtItem = m_qmGroups[nullptr];

   if (pqtItem && pqtItem->childCount() == 0)
   {
      DELPTR(pqtItem);
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:58:54 2012----------*
 * @method  CwmsMemberSequenceEditor::FillGroups             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:58:54 2012----------*/
void CwmsMemberSequenceEditor::FillGroups()
{
   QMap<int, CdmClassGroup*> qmGroups;
   m_rpCdmClass->GetGroups(qmGroups);

   QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
   QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassGroup* pCdmGroup = qmIt.value();

      if (CHKPTR(pCdmGroup))
      {
         QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwMembers);
         pqItem->setText(0, pCdmGroup->GetCaption());
         pqItem->setData(0, Qt::UserRole, QVariant(pCdmGroup->GetId()));
         pqItem->setData(1, Qt::UserRole, QVariant(true));
         m_qmGroups.insert(pCdmGroup, pqItem);
      }
   }

   QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwMembers);
   pqItem->setText(0, tr("Weitere Daten"));
   pqItem->setData(0, Qt::UserRole, QVariant(0));
   pqItem->setData(1, Qt::UserRole, QVariant(true));
   m_qmGroups.insert(nullptr, pqItem);
}

/** +-=---------------------------------------------------------Mi 22. Aug 18:13:31 2012----------*
 * @method  CwmsMemberSequenceEditor::FillMembers            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 18:13:31 2012----------*/
void CwmsMemberSequenceEditor::FillMembers()
{
   QMap<long, CdmMember*> qmMembers; 
   m_rpCdmClass->GetMemberMap(qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();
      AddMember(pCdmMember);
   }
}

/** +-=---------------------------------------------------------Di 6. Nov 16:11:14 2012-----------*
 * @method  CwmsMemberSequenceEditor::FillMembersNotInHash   // private                           *
 * @return  void                                             //                                   *
 * @param   QVector<QString>& p_rqvHash                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 6. Nov 16:11:14 2012-----------*/
void CwmsMemberSequenceEditor::FillMembersNotInHash(QVector<QString>& p_rqvHash)
{
   QMap<long, CdmMember*> qmMembers; 
   m_rpCdmClass->GetMemberMap(qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (!p_rqvHash.contains(pCdmMember->GetKeyname()))
      {
         AddMember(pCdmMember);
      }
   }
}


/** +-=---------------------------------------------------------Mo 11. Feb 11:10:50 2013----------*
 * @method  CwmsMemberSequenceEditor::AddMember              // private                           *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:10:50 2013----------*/
void CwmsMemberSequenceEditor::AddMember(const CdmMember* p_pCdmMember)
{
   if (p_pCdmMember && p_pCdmMember->GetAccessMode() != eDmMemberAccessPrivate)
   {
      const CdmClassGroup* pCdmGroup = p_pCdmMember->GetGroup();
      AddMemberToGroup(p_pCdmMember, pCdmGroup);
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:06:50 2013----------*
 * @method  CwmsMemberSequenceEditor::AddMemberToGroup       // private                           *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @param   const CdmClassGroup* p_pCdmGroup                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:06:50 2013----------*/
void CwmsMemberSequenceEditor::AddMemberToGroup(const CdmMember* p_pCdmMember,
                                                const CdmClassGroup* p_pCdmGroup)
{
   if (CHKPTR(p_pCdmMember))
   {
      if (m_qmGroups.contains((const_cast<CdmClassGroup*>(p_pCdmGroup))))
      {
         QTreeWidgetItem* pqtwGroup = m_qmGroups[(const_cast<CdmClassGroup*>(p_pCdmGroup))];
         QTreeWidgetItem* pqtwItem = nullptr;

         if (pqtwGroup)
         {
            pqtwItem = new QTreeWidgetItem(pqtwGroup);
         }
         else
         {
            pqtwItem = new QTreeWidgetItem(m_pqtwMembers);
         }
      
         SetMemberToTreeViewItem(p_pCdmMember, pqtwItem);
      }
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:07:15 2013----------*
 * @method  CwmsMemberSequenceEditor::SetMemberToTreeViewItem // public                           *
 * @return  void                                             //                                   *
 * @param   const CdmMember* p_pCdmMember                    //                                   *
 * @param   QTreeWidgetItem* p_pqItem                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:07:15 2013----------*/
void CwmsMemberSequenceEditor::SetMemberToTreeViewItem(const CdmMember* p_pCdmMember,
                                                       QTreeWidgetItem* p_pqItem)
{
   if (p_pCdmMember && p_pqItem)
   {
      p_pqItem->setText(0, p_pCdmMember->GetCaption());
      p_pqItem->setText(1, p_pCdmMember->GetKeyname());
      p_pqItem->setData(0, Qt::UserRole, QVariant((int)p_pCdmMember->GetId()));
      p_pqItem->setData(1, Qt::UserRole, QVariant(false));
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 18:13:56 2012----------*
 * @method  CwmsMemberSequenceEditor::FillMembers            // private                           *
 * @return  void                                             //                                   *
 * @param   QVector<QString>& p_rqvHash                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 18:13:56 2012----------*/
void CwmsMemberSequenceEditor::FillMembers(QVector<QString>& p_rqvHash)
{
   for (int iCounter = 0; iCounter < p_rqvHash.count(); ++iCounter)
   {
      QString qstrKeyname = p_rqvHash[iCounter];
      const CdmMember* pCdmMember = m_rpCdmClass->FindMember(qstrKeyname);
      AddMember(pCdmMember);
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:49:13 2012----------*
 * @method  CwmsMemberSequenceEditor::UpClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:49:13 2012----------*/
void CwmsMemberSequenceEditor::UpClickedSlot()
{
   QTreeWidgetItem* pqtItem = GetSelectedItem();

   if (pqtItem && pqtItem->data(1, Qt::UserRole).toBool() == false)
   {
      QTreeWidgetItem* pqtItemAbove = m_pqtwMembers->itemAbove(pqtItem);

      if (pqtItemAbove && pqtItemAbove->data(1, Qt::UserRole).toBool() == false)
      {
         const CdmMember* pCdmMemberOldPos = m_rpCdmClass->FindMember(pqtItem->text(1));
         const CdmMember* pCdmMemberNewPos = m_rpCdmClass->FindMember(pqtItemAbove->text(1));

         if (pCdmMemberNewPos && pCdmMemberOldPos)
         {
            SetMemberToTreeViewItem(pCdmMemberOldPos, pqtItemAbove);
            SetMemberToTreeViewItem(pCdmMemberNewPos, pqtItem);
         }            

         pqtItem->setSelected(false);
         pqtItemAbove->setSelected(true);
      }
   }
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:49:25 2012----------*
 * @method  CwmsMemberSequenceEditor::DownClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:49:25 2012----------*/
void CwmsMemberSequenceEditor::DownClickedSlot()
{
   QTreeWidgetItem* pqtItem = GetSelectedItem();

   if (pqtItem && pqtItem->data(1, Qt::UserRole).toBool() == false)
   {
      QTreeWidgetItem* pqtItemBelow = m_pqtwMembers->itemBelow(pqtItem);

      if (pqtItemBelow && pqtItemBelow->data(1, Qt::UserRole).toBool() == false)
      {
         const CdmMember* pCdmMemberOldPos = m_rpCdmClass->FindMember(pqtItem->text(1));
         const CdmMember* pCdmMemberNewPos = m_rpCdmClass->FindMember(pqtItemBelow->text(1));

         if (pCdmMemberNewPos && pCdmMemberOldPos)
         {
            SetMemberToTreeViewItem(pCdmMemberOldPos, pqtItemBelow);
            SetMemberToTreeViewItem(pCdmMemberNewPos, pqtItem);
         }

         pqtItem->setSelected(false);
         pqtItemBelow->setSelected(true);
      }
   }
}

/** +-=---------------------------------------------------------Do 23. Aug 10:48:36 2012----------*
* @method  CwmsMemberSequenceEditor::GetSelectedItem        // public                            *
* @return  QTreeWidgetItem*                                 //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------Do 23. Aug 10:48:36 2012----------*/
QTreeWidgetItem* CwmsMemberSequenceEditor::GetSelectedItem()
{
   QTreeWidgetItem* pItem = nullptr;
   QList<QTreeWidgetItem*> qlItems = m_pqtwMembers->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Do 23. Aug 11:10:32 2012----------*
 * @method  CwmsMemberSequenceEditor::GetSequence            // public                            *
 * @return  QVector<QString>                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 23. Aug 11:10:32 2012----------*/
QVector<QString> CwmsMemberSequenceEditor::GetSequence()
{
   QVector<QString> qvSequence;
   QTreeWidgetItemIterator it(m_pqtwMembers);

   while (*it) 
   {
      if((*it)->data(1, Qt::UserRole).toBool() == false)
      {
         qvSequence.append((*it)->text(1));
      }

      ++it;
   }

   return qvSequence;
}

/** +-=---------------------------------------------------------Mi 22. Aug 17:49:36 2012----------*
 * @method  CwmsMemberSequenceEditor::OKClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 17:49:36 2012----------*/
void CwmsMemberSequenceEditor::OKClickedSlot()
{
   accept();
}

