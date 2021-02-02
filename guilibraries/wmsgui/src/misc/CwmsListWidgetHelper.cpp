/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsListWidgetHelper.cpp
 ** Started Implementation: 2012/09/13
 ** Description:
 **
 ** implements helper functions for listwidget
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QListWidget>

//WMS Includes
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsListWidgetHelper.h"



/** +-=---------------------------------------------------------Do 13. Sep 11:10:37 2012----------*
 * @method  CwmsListWidgetHelper::GetSelectedItem            // public, static                    *
 * @return  QListWidgetItem*                                 //                                   *
 * @param   QListWidget* p_pWidget                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 11:10:37 2012----------*/
QListWidgetItem* CwmsListWidgetHelper::GetSelectedItem(QListWidget* p_pWidget)
{
   QListWidgetItem* pItem = nullptr;

   if (p_pWidget)
   {
      QList<QListWidgetItem*> qlItems = p_pWidget->selectedItems();

      if (qlItems.count() > 0)
      {
         pItem = qlItems[0];
      }
   }

   return pItem;
}

/** +-=---------------------------------------------------------Fr 15. Mrz 10:40:22 2013----------*
 * @method  CwmsListWidgetHelper::GetSelectedObject          // public, static                    *
 * @return  CdmObject*                                       //                                   *
 * @param   QListWidget* p_pWidget                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 15. Mrz 10:40:22 2013----------*/
CdmObject* CwmsListWidgetHelper::GetSelectedObject(QListWidget* p_pWidget)
{
   CdmObject* pObject = nullptr;
   QListWidgetItem* pItem = GetSelectedItem(p_pWidget);

   if (pItem)
   {
      pObject = GetItemObject(pItem);
   }

   return pObject;
}

/** +-=---------------------------------------------------------Fr 15. Mrz 10:39:58 2013----------*
 * @method  CwmsListWidgetHelper::GetItemObject              // public, static                    *
 * @return  CdmObject*                                       //                                   *
 * @param   QListWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 15. Mrz 10:39:58 2013----------*/
CdmObject* CwmsListWidgetHelper::GetItemObject(QListWidgetItem* p_pItem)
{
   CdmObject* pObject = nullptr;

   if (p_pItem)
   {
      QString qstrUri = p_pItem->data(Qt::UserRole).toString();
      CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pManager))
      {
         pObject = static_cast<CdmObject*>(pManager->GetUriObject(qstrUri));
      }
   }

   return pObject;
}

/** +-=---------------------------------------------------------Fr 15. Mrz 10:39:40 2013----------*
 * @method  CwmsListWidgetHelper::SetObjectToItem            // public, static                    *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pObject                             //                                   *
 * @param   QListWidgetItem* p_pItem                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 15. Mrz 10:39:40 2013----------*/
void CwmsListWidgetHelper::SetObjectToItem(CdmObject* p_pObject, QListWidgetItem* p_pItem)
{
   if (CHKPTR(p_pObject) && CHKPTR(p_pItem))
   {
      p_pItem->setData(Qt::UserRole, p_pObject->GetUriInternal());
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 11:12:11 2012----------*
 * @method  CwmsListWidgetHelper::MoveItemUp                 // public, static                    *
 * @return  void                                             //                                   *
 * @param   QListWidget* p_pWidget                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 11:12:11 2012----------*/
void CwmsListWidgetHelper::MoveItemUp(QListWidget* p_pWidget)
{
   QListWidgetItem* pItem = GetSelectedItem(p_pWidget);

   if (pItem)
   {
      int iCurrentRow = p_pWidget->row(pItem);

      if (iCurrentRow > 0)
      {
         QListWidgetItem* pItemAbove = p_pWidget->item(iCurrentRow - 1);

         if (pItemAbove)
         {
            QString qstrAbove = pItemAbove->text();
            QString qstrCurrent = pItem->text();
            pItemAbove->setText(qstrCurrent);
            pItem->setText(qstrAbove);
            pItemAbove->setSelected(true);
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 13. Sep 11:24:38 2012----------*
 * @method  CwmsListWidgetHelper::MoveItemDown               // public, static                    *
 * @return  void                                             //                                   *
 * @param   QListWidget* p_pWidget                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 11:24:38 2012----------*/
void CwmsListWidgetHelper::MoveItemDown(QListWidget* p_pWidget)
{
   QListWidgetItem* pItem = GetSelectedItem(p_pWidget);

   if (pItem)
   {
      int iCurrentRow = p_pWidget->row(pItem);

      if (iCurrentRow >= 0)
      {
         QListWidgetItem* pItemDown = p_pWidget->item(iCurrentRow + 1);

         if (pItemDown)
         {
            QString qstrDown = pItemDown->text();
            QString qstrCurrent = pItem->text();
            pItemDown->setText(qstrCurrent);
            pItem->setText(qstrDown);
            pItemDown->setSelected(true);
         }
      }
   }
}

void CwmsListWidgetHelper::SelectObject(QListWidget* p_pWidget, CdmObject* p_pObject)
{
    p_pWidget->clearSelection();

    if (p_pObject)
    {
        QString qstrUri = p_pObject->GetUriInternal();

        for (int pos = 0; pos < p_pWidget->count(); ++pos)
        {
            QListWidgetItem* pItem = p_pWidget->item(pos);

            if (CHKPTR(pItem))
            {
                if (qstrUri == pItem->data(Qt::UserRole).toString())
                {
                    SelectRow(p_pWidget, pos);
                    break;
                }
            }
        }
    }
}

void CwmsListWidgetHelper::SelectRow(QListWidget* p_pWidget, int p_iRow)
{
    QItemSelectionModel *selection = new QItemSelectionModel( p_pWidget->model() );
    QModelIndex index;

    for (int col=0; col< p_pWidget->model()->columnCount(); col++)
    {
       index = p_pWidget->model()->index(p_iRow,col, QModelIndex() );
       selection->select(index, QItemSelectionModel::Select);
    }

    p_pWidget->setSelectionModel( selection);
}
