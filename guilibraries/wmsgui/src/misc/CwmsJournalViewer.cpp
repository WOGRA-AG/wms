/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsJournalViewer.cpp
 ** Started Implementation: 2012/08/29
 ** Description:
 **
 ** implements the viewer for journal data
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QClipboard>
#include <QDate>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmScheme.h"
#include "CdmJournalItem.h"

// own Includes
#include "CwmsJournalViewer.h"

/** +-=---------------------------------------------------------Mi 29. Aug 15:50:16 2012----------*
 * @method  CwmsJournalViewer::CwmsJournalViewer             // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 15:50:16 2012----------*/
CwmsJournalViewer::CwmsJournalViewer(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCdmDatabase(nullptr),
  m_rpContainer(nullptr),
  m_rpCdmObject(nullptr)
{
   setupUi(this);
   SetFromToDefaultData();
}

/** +-=---------------------------------------------------------Mi 29. Aug 15:53:03 2012----------*
 * @method  CwmsJournalViewer::~CwmsJournalViewer            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsJournalViewer                                             *
 *----------------last changed: --------------------------------Mi 29. Aug 15:53:03 2012----------*/
CwmsJournalViewer::~CwmsJournalViewer()
{
}

/** +-=---------------------------------------------------------Mi 29. Aug 19:17:26 2012----------*
 * @method  CwmsJournalViewer::FillDialog                    // public                            *
 * @return  void                                             //                                   *
 * @param   CdmDatabase* p_pCdmDtabase                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 19:17:26 2012----------*/
void CwmsJournalViewer::FillDialog(CdmScheme* p_pCdmDtabase)
{

   if (!m_rpCdmDatabase)
   {
      AddDbHeader();
   }

   m_rpCdmDatabase = p_pCdmDtabase;

   if (CHKPTR(m_rpCdmDatabase))
   {
      m_pqtwJournal->clear();
      QList<CdmJournalItem*> qlItems;
      QDate qdFrom = m_pqdeFrom->date();
      QDate qdTo = m_pqdeTo->date();
      m_rpCdmDatabase->GetChanges(qdFrom, qdTo, qlItems);

      for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
      {
         CdmJournalItem* pItem = qlItems[iCounter];

         if (CHKPTR(pItem))
         {
            QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
            pqItem->setText(0, pItem->GetUserString());
            pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
            pqItem->setText(2, pItem->GetChangeModeAsString());

            int iObjectListId = pItem->GetObjectListId();

            CdmObjectContainer* pContainer = m_rpCdmDatabase->GetContainerManager()->FindEmptyContainerById(iObjectListId);

            if (pContainer)
            {
               pqItem->setText(3, pContainer->GetCaption());
               int iObjectId = pItem->GetObjectId();

               if (iObjectId > 0)
               {
                  CdmObject* pCdmObject = pContainer->FindObjectById(iObjectId);

                  if (pCdmObject)
                  {
                     pqItem->setText(4, pCdmObject->GetCaption());
                     pqItem->setText(5, pItem->GetMemberAsString(pCdmObject));
                     pqItem->setText(6, pItem->GetDisplayString());
                  }
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 29. Aug 16:16:57 2012----------*
 * @method  CwmsJournalViewer::AddDbHeader                   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 16:16:57 2012----------*/
void CwmsJournalViewer::AddDbHeader()
{
   QStringList qstrlHeader;
   qstrlHeader.append(tr("Anwender"));
   qstrlHeader.append(tr("Zeitpunkt"));
   qstrlHeader.append(tr("Änderungsart"));
   qstrlHeader.append(tr("ObjektListe"));
   qstrlHeader.append(tr("Objekt"));
   qstrlHeader.append(tr("Variable"));
   qstrlHeader.append(tr("Wert"));
   m_pqtwJournal->setHeaderLabels(qstrlHeader);
}

/** +-=---------------------------------------------------------Mi 29. Aug 16:16:51 2012----------*
 * @method  CwmsJournalViewer::AddObjectListHeader           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 16:16:51 2012----------*/
void CwmsJournalViewer::AddObjectListHeader()
{
   QStringList qstrlHeader;
   qstrlHeader.append(tr("Anwender"));
   qstrlHeader.append(tr("Zeitpunkt"));
   qstrlHeader.append(tr("Änderungsart"));
   qstrlHeader.append(tr("Objekt"));
   qstrlHeader.append(tr("Variable"));
   qstrlHeader.append(tr("Wert"));
   m_pqtwJournal->setHeaderLabels(qstrlHeader);

}

/** +-=---------------------------------------------------------Mi 29. Aug 19:17:38 2012----------*
 * @method  CwmsJournalViewer::FillDialog                    // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 19:17:38 2012----------*/
void CwmsJournalViewer::FillDialog(CdmObjectContainer* p_pContainer)
{

   if (!m_rpContainer)
   {
      AddObjectListHeader();
   }

   m_rpContainer = p_pContainer;

   if (CHKPTR(m_rpContainer))
   {
      m_pqtwJournal->clear();
      QList<CdmJournalItem*> qlItems;
      m_rpContainer->GetChanges(m_pqdeFrom->date(), m_pqdeTo->date(), qlItems);

      for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
      {
         CdmJournalItem* pItem = qlItems[iCounter];

         if (CHKPTR(pItem))
         {
            QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
            pqItem->setText(0, pItem->GetUserString());
            pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
            pqItem->setText(2, pItem->GetChangeModeAsString());

            int iObjectId = pItem->GetObjectId();

            if (iObjectId > 0)
            {
               CdmObject* pCdmObject = m_rpContainer->FindObjectById(iObjectId);

               if (pCdmObject)
               {
                  pqItem->setText(3, pCdmObject->GetCaption());
                  pqItem->setText(4, pItem->GetMemberAsString(pCdmObject));
                  pqItem->setText(5, pItem->GetDisplayString());
               }
            }
         }
      }
      
   }
}

/** +-=---------------------------------------------------------Mi 29. Aug 19:17:44 2012----------*
 * @method  CwmsJournalViewer::FillDialog                    // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 19:17:44 2012----------*/
void CwmsJournalViewer::FillDialog(CdmObject* p_pCdmObject)
{

   if (!m_rpCdmObject)
   {
      AddObjectHeader();
   }

   m_rpCdmObject = p_pCdmObject;

   if (CHKPTR(m_rpCdmObject))
   {
      m_pqtwJournal->clear();
      QList<CdmJournalItem*> qlItems;
      m_rpCdmObject->GetChanges(m_pqdeFrom->date(), m_pqdeTo->date(), qlItems);

      for (int iCounter = 0; iCounter < qlItems.count(); ++iCounter)
      {
         CdmJournalItem* pItem = qlItems[iCounter];

         if (CHKPTR(pItem))
         {
            QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwJournal);
            pqItem->setText(0, pItem->GetUserString());
            pqItem->setText(1, pItem->GetModified().toString(Qt::SystemLocaleShortDate));
            pqItem->setText(2, pItem->GetChangeModeAsString());
            pqItem->setText(3, pItem->GetMemberAsString(m_rpCdmObject));
            pqItem->setText(4, pItem->GetDisplayString());
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 29. Aug 16:17:44 2012----------*
 * @method  CwmsJournalViewer::AddObjectHeader               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 16:17:44 2012----------*/
void CwmsJournalViewer::AddObjectHeader()
{
   QStringList qstrlHeader;
   qstrlHeader.append(tr("Anwender"));
   qstrlHeader.append(tr("Zeitpunkt"));
   qstrlHeader.append(tr("Änderungsart"));
   qstrlHeader.append(tr("Variable"));
   qstrlHeader.append(tr("Wert"));
   m_pqtwJournal->setHeaderLabels(qstrlHeader);

}

/** +-=---------------------------------------------------------Mi 29. Aug 16:06:13 2012----------*
 * @method  CwmsJournalViewer::SetFromToDefaultData          // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 16:06:13 2012----------*/
void CwmsJournalViewer::SetFromToDefaultData()
{
   m_pqdeTo->setDate(QDate::currentDate());
   m_pqdeFrom->setDate(QDate::currentDate().addDays(-30));
}

void CwmsJournalViewer::CopyToClipboardClickedSlot()
{
    QTreeWidgetItem* pItem = m_pqtwJournal->selectedItems().first();

    if (CHKPTR(pItem))
    {
        QString qstrText = QString("%s = %s").arg(pItem->text(3)).arg(pItem->text(4));

        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(qstrText);
    }
}

/** +-=---------------------------------------------------------Mi 29. Aug 16:04:19 2012----------*
 * @method  CwmsJournalViewer::RefreshClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Aug 16:04:19 2012----------*/
void CwmsJournalViewer::RefreshClickedSlot()
{
   if (m_rpCdmDatabase)
   {
      FillDialog(m_rpCdmDatabase);
   }
   else if (m_rpCdmObject)
   {
      FillDialog(m_rpCdmObject);
   }
   else if (m_rpContainer)
   {
      FillDialog(m_rpContainer);
   }
}
