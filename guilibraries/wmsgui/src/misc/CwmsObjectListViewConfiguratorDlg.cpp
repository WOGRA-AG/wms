/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsObjectListViewConfiguratorDlg.cpp
 ** Started Implementation: 2010/05/18
 ** Description:
 ** 
 ** Implements the configurator for the listview
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QInputDialog>

// WMS Includes
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmMember.h"
#include "CdmError.h"
#include "CdmObjectList.h"
#include "CdmObject.h"
#include "CdmManager.h"
 #include "CdmManagerFactory.h"

// Own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsObjectListListViewConfigurator.h"
#include "CwmsObjectListViewConfiguratorDlg.h"


/** +-=---------------------------------------------------------Fr 21. Mai 19:32:26 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::CwmsObjectListViewConfiguratorDlg // public        *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:32:26 2010----------*/
CwmsObjectListViewConfiguratorDlg::CwmsObjectListViewConfiguratorDlg(QWidget* p_pqwParent)
   : QDialog(p_pqwParent),
  m_rpCwmsConfig(NULL)
{

   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 21. Mai 17:36:55 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::~CwmsObjectListViewConfiguratorDlg // public, virtual*
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectListViewConfiguratorDlg                             *
 *----------------last changed: --------------------------------Fr 21. Mai 17:36:55 2010----------*/
CwmsObjectListViewConfiguratorDlg::~CwmsObjectListViewConfiguratorDlg()
{
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:46:36 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::FillDialog    // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsObjectListListViewConfigurator* p_pCwmsConfig//                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:46:36 2010----------*/
void CwmsObjectListViewConfiguratorDlg::FillDialog(CwmsObjectListListViewConfigurator* p_pCwmsConfig)
{
   if (CHKPTR(p_pCwmsConfig))
   {
      m_rpCwmsConfig = p_pCwmsConfig;
      CdmClass* pCdmClass = m_rpCwmsConfig->GetListViewClass();

      QTreeWidgetItem* pqtwHeader = m_pqlvColumnSource->headerItem();

      if (CHKPTR(pqtwHeader))
      {
         pqtwHeader->setText(0, tr("Name"));
         pqtwHeader->setText(1, tr("Schlüssel"));
         pqtwHeader->setText(2, tr("Schlüssel"));
         pqtwHeader->setText(3, tr("Dargestellte Bezeichnung"));
      }
      FillSourceListView(pCdmClass);
      FillTargetListView();
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 18:07:17 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::FillSourceListView // private                      *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 18:07:17 2010----------*/
void CwmsObjectListViewConfiguratorDlg::FillSourceListView(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QMap<long,CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);

      QMap<long, CdmMember*>::iterator qmIt    = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for(; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            if (pCdmMember->GetValue() == eDmValueObjectRef)
            {
               QTreeWidgetItem* pqchItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvColumnSource);
               
               pqchItem->setText(0, pCdmMember->GetCaption());
               pqchItem->setText(1, pCdmMember->GetKeyname());

               FillChildMembers(pCdmMember, pqchItem, 0, p_pCdmClass);
               pqchItem->setExpanded(TRUE);
            }
            else if (pCdmMember->GetValue() != eDmValueListDouble &&
                     pCdmMember->GetValue() != eDmValueListInt &&
                     pCdmMember->GetValue() != eDmValueListString &&
                     pCdmMember->GetValue() != eDmValueDictIntDouble &&
                     pCdmMember->GetValue() != eDmValueDictIntInt &&
                     pCdmMember->GetValue() != eDmValueDictIntString &&
                     pCdmMember->GetValue() != eDmValueDictStringDouble &&
                     pCdmMember->GetValue() != eDmValueDictStringInt &&
                     pCdmMember->GetValue() != eDmValueDictStringString &&
                     pCdmMember->GetValue() != eDmValueObjectListRef)
            {
               QTreeWidgetItem* pqchItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvColumnSource);

               pqchItem->setText(0, pCdmMember->GetCaption());
               pqchItem->setText(1, pCdmMember->GetKeyname());
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------So 28. Okt 11:05:24 2012----------*
 * @method  CwmsObjectListViewConfiguratorDlg::FillChildMembers // private                        *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QTreeWidgetItem* p_pqlvItem                      //                                   *
 * @param   int p_iDepth                                     //                                   *
 * @param   CdmClass* p_pCdmRequestClass                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 28. Okt 11:05:24 2012----------*/
void CwmsObjectListViewConfiguratorDlg::FillChildMembers(CdmMember* p_pCdmMember,
                                                         QTreeWidgetItem* p_pqlvItem,
                                                         int p_iDepth,
                                                         CdmClass* p_pCdmRequestClass)
{
   if (CHKPTR(p_pCdmMember) && CHKPTR(p_pqlvItem))
   {  
      int iClassId = p_pCdmMember->GetClassReference();
      CdmManager* pCdmManager = CdmManagerFactory::GetManager();

      if (CHKPTR(pCdmManager))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_pCdmMember->GetDatabaseId());

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(iClassId);

            if (pCdmClass)
            {
               QMap<long,CdmMember*> qmMembers;
               pCdmClass->GetMemberMap(qmMembers);
               QMap<long, CdmMember*>::iterator qmIt    = qmMembers.begin();
               QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();
               QTreeWidgetItem* pqchItem = NULL;

               for(; qmIt != qmItEnd; ++qmIt)
               {
                  CdmMember* pCdmMember = qmIt.value();

                  if (CHKPTR(pCdmMember))
                  {
                     if (pCdmMember->GetValue() == eDmValueObjectRef && 
                         p_iDepth < 2 &&
                         p_pCdmRequestClass->GetId() != pCdmMember->GetClassReference() &&
                         p_pCdmRequestClass->IsInherited(pCdmMember->GetClassReference()) < 1)
                     {
                        pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                        pqchItem->setText(0, pCdmMember->GetCaption());
                        pqchItem->setText(1, pCdmMember->GetKeyname());

                        ++p_iDepth;

                        FillChildMembers(pCdmMember, pqchItem, p_iDepth, p_pCdmRequestClass);
                        pqchItem->setExpanded(TRUE);
                     }
                     else if (pCdmMember->GetValue() != eDmValueListDouble &&
                              pCdmMember->GetValue() != eDmValueListInt &&
                              pCdmMember->GetValue() != eDmValueListString &&
                              pCdmMember->GetValue() != eDmValueDictIntDouble &&
                              pCdmMember->GetValue() != eDmValueDictIntInt &&
                              pCdmMember->GetValue() != eDmValueDictIntString &&
                              pCdmMember->GetValue() != eDmValueDictStringDouble &&
                              pCdmMember->GetValue() != eDmValueDictStringInt &&
                              pCdmMember->GetValue() != eDmValueDictStringString &&
                              pCdmMember->GetValue() != eDmValueObjectListRef)
                     {
                        pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                        pqchItem->setText(0, pCdmMember->GetCaption());
                        pqchItem->setText(1, pCdmMember->GetKeyname());
                     }
                  }
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 24. Mai 10:27:38 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::FillTargetListView // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 24. Mai 10:27:38 2010----------*/
void CwmsObjectListViewConfiguratorDlg::FillTargetListView()
{
   if (CHKPTR(m_rpCwmsConfig))
   {
      QMap<int, QString> qmDisplayColumns;
      m_rpCwmsConfig->GetDisplayColumns(qmDisplayColumns);
 
      QMap<int, QString>::iterator qmIt = qmDisplayColumns.begin();
      QMap<int, QString>::iterator qmItEnd = qmDisplayColumns.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QString qstrKeyname = qmIt.value();
         AddDisplayItem(qstrKeyname);
      }
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 18:47:18 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::AddDisplayItem // private                          *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 18:47:18 2010----------*/
void CwmsObjectListViewConfiguratorDlg::AddDisplayItem(QString p_qstrKeyname)
{
   QString qstrDisplayName = m_rpCwmsConfig->GetColumnNameByKeyname(p_qstrKeyname);

   if (!p_qstrKeyname.isEmpty())
   {
      QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvColumnTarget);
      pqlviItem->setText(0, p_qstrKeyname);
      pqlviItem->setText(1, qstrDisplayName);
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:11:31 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::SaveData      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:11:31 2010----------*/
void CwmsObjectListViewConfiguratorDlg::SaveData()
{
   if (CHKPTR(m_rpCwmsConfig))
   {
      m_rpCwmsConfig->ClearMaps();

      QTreeWidgetItemIterator it(m_pqlvColumnTarget);
      int iCounter = 0;
      
      while (*it) 
      {
         m_rpCwmsConfig->AddDisplayColumn(iCounter, (*it)->text(0));
         m_rpCwmsConfig->AddColumnName((*it)->text(0),  (*it)->text(1));
         ++it;
         ++iCounter;
      }
      
      m_rpCwmsConfig->Save();
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:09:45 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::AddColumnClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:09:45 2010----------*/
void CwmsObjectListViewConfiguratorDlg::AddColumnClickedSlot()
{
   QTreeWidgetItem* pqlviSelectedItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumnSource);
   
   if (pqlviSelectedItem)
   {
      QTreeWidgetItem* pqlviItem = pqlviSelectedItem;
      QString qstrMember = pqlviItem->text(0);

      while (pqlviItem->parent() != NULL)
      {
         pqlviItem = pqlviItem->parent();

         if (pqlviItem)
         {
            qstrMember = pqlviItem->text(1) + "." + qstrMember;
         }
      }

      pqlviItem = pqlviSelectedItem;
      QString qstrKeyname = pqlviItem->text(1);

      while (pqlviItem->parent() != NULL)
      {
         pqlviItem = pqlviItem->parent();

         if (pqlviItem)
         {
            qstrKeyname = pqlviItem->text(1) + "." + qstrKeyname;
         }
      }

      QTreeWidgetItem* pqlviItemNew = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvColumnTarget);
      pqlviItemNew->setText(0, qstrKeyname);
      pqlviItemNew->setText(1, qstrMember);
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:09:56 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::RemoveColumnClickedSlot // private, slots          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:09:56 2010----------*/
void CwmsObjectListViewConfiguratorDlg::RemoveColumnClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumnTarget);

   if (pqlviItem)
   {
      DELPTR(pqlviItem);
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:10:23 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::UpClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:10:23 2010----------*/
void CwmsObjectListViewConfiguratorDlg::UpClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumnTarget);

   if (pqlviItem)
   {
      QTreeWidgetItem* pqlviItemParent = CwmsTreeWidgetHelper::GetItemAbove(pqlviItem);
      if (pqlviItemParent)
      {
         QString qstrMember = pqlviItem->text(0);
         QString qstrKeyName = pqlviItem->text(1);
         DELPTR(pqlviItem);
         
         QTreeWidgetItem* pqlviItemGrandParent = CwmsTreeWidgetHelper::GetItemAbove(pqlviItemParent);

         if (pqlviItemGrandParent)
         {
            pqlviItem = new QTreeWidgetItem(m_pqlvColumnTarget, pqlviItemGrandParent);
            pqlviItem->setText(0, qstrMember);
            pqlviItem->setText(1, qstrKeyName);

         }
         else
         {
            pqlviItem = new QTreeWidgetItem(m_pqlvColumnTarget, NULL);
            pqlviItem->setText(0, qstrMember);
            pqlviItem->setText(1, qstrKeyName);
         }

         pqlviItem->setSelected(TRUE);
      }
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:10:37 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::DownClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:10:37 2010----------*/
void CwmsObjectListViewConfiguratorDlg::DownClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumnTarget);

   if (pqlviItem)
   {
      QTreeWidgetItem* pqlviSibling = CwmsTreeWidgetHelper::GetItemBelow(pqlviItem);

      if (pqlviSibling)
      {
         QString qstrMember = pqlviItem->text(0);
         QString qstrKeyName = pqlviItem->text(1);
         DELPTR(pqlviItem);

         pqlviItem = new QTreeWidgetItem(m_pqlvColumnTarget, pqlviSibling);
         pqlviItem->setText(0, qstrMember);
         pqlviItem->setText(1, qstrKeyName);
         pqlviItem->setSelected(TRUE);
      }
   }
}

/** +-=---------------------------------------------------------Fr 21. Mai 19:11:02 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::ChangeNameClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Mai 19:11:02 2010----------*/
void CwmsObjectListViewConfiguratorDlg::ChangeNameClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvColumnTarget);

   if (pqlviItem)
   {
      QString qstrName = QInputDialog::getText(this, tr("Spaltennamen ändern"), tr("Bitte geben Sie den neuen Spaltennamen ein"));

      if (!qstrName.isEmpty())
      {
         pqlviItem->setText(1, qstrName);
      }
   }
}

/** +-=---------------------------------------------------------So 23. Mai 09:54:35 2010----------*
 * @method  CwmsObjectListViewConfiguratorDlg::EditColumnConfiguration // public, static          *
 * @return  void                                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   CwmsObjectListListViewConfigurator* p_pCwmsConfig//                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 23. Mai 09:54:35 2010----------*/
void CwmsObjectListViewConfiguratorDlg::EditColumnConfiguration(QWidget* p_pqwParent,
                                                                CwmsObjectListListViewConfigurator* p_pCwmsConfig)
{
   if (CHKPTR(p_pCwmsConfig))
   {
      CwmsObjectListViewConfiguratorDlg* pCwmsDialog = new CwmsObjectListViewConfiguratorDlg(p_pqwParent);
      pCwmsDialog->FillDialog(p_pCwmsConfig);

      if (pCwmsDialog->exec() == QDialog::Accepted)
      {
         pCwmsDialog->SaveData();
      }

      DELPTR(pCwmsDialog);
   }
}