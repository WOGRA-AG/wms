/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsQueryEditor.cpp
 ** Started Implementation: 2012/07/26
 ** Description:
 **
 ** Implements the ui of the queryeditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QFileDialog>
#include <QTextStream>
#include <CwmsTimeMeassurement.h>
#include <CwmsQueryModelExportCsv.h>
//#include <QAbstractItemModel>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryBuilder.h"
#include "CdmQueryElement.h"
#include "CdmQueryEnhanced.h"

// Basetools includes
#include "CwmsErrorCollector.h"

// own Includes
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsTreeWidgetHelper.h"
#include "jshighlighter.h"
#include "CwmsView.h"
#include "CwmsViewEditor.h"
#include "CwmsQueryEditor.h"

/** +-=---------------------------------------------------------Do 26. Jul 11:26:32 2012----------*
 * @method  CwmsQueryEditor::CwmsQueryEditor                 // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:26:32 2012----------*/
CwmsQueryEditor::CwmsQueryEditor(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_pCdmQuery(nullptr)
{
   setupUi(this);

   m_pqtvResult->setSelectionBehavior(QAbstractItemView::SelectRows);
   m_pqtvResult->setSelectionMode(QAbstractItemView::ContiguousSelection);
   m_pqteEditor->setTextWrapEnabled(false);
   m_pqteEditor->setCodeFoldingEnabled(true);
   m_pqteEditor->setLineNumbersVisible(true);
   
}

/** +-=---------------------------------------------------------Do 26. Jul 11:27:00 2012----------*
 * @method  CwmsQueryEditor::~CwmsQueryEditor                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsQueryEditor                                               *
 *----------------last changed: --------------------------------Do 26. Jul 11:27:00 2012----------*/
CwmsQueryEditor::~CwmsQueryEditor()
{
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:27 2012----------*
 * @method  CwmsQueryEditor::ExecuteClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:27 2012----------*/
void CwmsQueryEditor::ExecuteClickedSlot()
{
   CdmMessageManager::StartAsyncMessageCollection();
   CwmsTimeMeassurement cTimeMeassure(false,"Wql");
   QString qstrQuery = m_pqteEditor->toPlainText();
   qstrQuery = qstrQuery.replace("\n", " ");
   CwmsErrorCollector cErrorCollector;
   CdmLogging::AddAdaptor(&cErrorCollector);
   m_cCdmModel.Execute(qstrQuery);
   CdmLogging::RemoveAdaptor(&cErrorCollector);

   if (cErrorCollector.HasEntries())
   {
      m_pqtwQueryAnalyzer->clear();
      m_pqtvResult->setModel(nullptr);
   }
   else
   {
      FillQueryAnalyzer(m_pqtwQueryAnalyzer, m_cCdmModel.GetQuery());
      m_pqtvResult->setModel(&m_cCdmModel);
   }

   QLocale loc;
   cTimeMeassure.finished();
   m_pqleDuration->setText(loc.toString(cTimeMeassure.GetCompleteDuration()) + " " + tr("msecs"));

   if (m_cCdmModel.GetQuery() && m_cCdmModel.GetQuery()->IsValid())
   {
       m_pqleState->setText(tr("OK"));
       m_pqleResultCount->setText(QString::number(m_cCdmModel.GetQuery()->GetResultCount()));
   }
   else
   {
       m_pqleState->setText(tr("Invalid Query"));
       m_pqleResultCount->setText("0");
   }

   CdmMessageManager::EndAndShowAsyncMessageCollection();
}

/** +-=---------------------------------------------------------Fr 24. Aug 13:29:13 2012----------*
 * @method  CwmsQueryEditor::FillQueryAnalyzer               // public, static                    *
 * @return  void                                             //                                   *
 * @param   QTreeWidget* p_pqTreeWidget                      //                                   *
 * @param   CdmQueryEnhanced* p_pQuery                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 13:29:13 2012----------*/
void CwmsQueryEditor::FillQueryAnalyzer(QTreeWidget* p_pqTreeWidget, CdmQuery* p_pQuery)
{
   p_pqTreeWidget->clear();

   if (CHKPTR(p_pQuery) && CHKPTR(p_pqTreeWidget))
   {
      QVector<QString> qvElements = p_pQuery->GetResultElements();

      QTreeWidgetItem* pqFields = new QTreeWidgetItem(p_pqTreeWidget);
      pqFields->setText(0, tr("Felder"));

      for (int iCounter = 0; iCounter < qvElements.count(); ++iCounter)
      {
         QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqFields);
         pqItem->setText(0, qvElements[iCounter]);
      }
      
      QTreeWidgetItem* pqConditions = new QTreeWidgetItem(p_pqTreeWidget);
      pqConditions->setText(0, tr("Bedingungen"));

      CdmQueryElement*  pCdmRoot = p_pQuery->GetQueryElement();

	  if (pCdmRoot)
	  {
		AddQueryElement(pCdmRoot, pqConditions);
	  }

      if (pqConditions->childCount() == 0)
      {
         DELPTR(pqConditions)
      }
      
      CdmObjectContainer* pContainer = p_pQuery->GetContainer();

      if (pContainer)
      {
         QTreeWidgetItem* pqObjectList = new QTreeWidgetItem(p_pqTreeWidget);
         pqObjectList->setText(0, tr("Objektcontainer"));

         QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqObjectList);
         pqItem->setText(0, pContainer->GetKeyname());
      }
      else if(p_pQuery->GetClass())
      {
          const CdmClass* pClass = p_pQuery->GetClass();
          QTreeWidgetItem* pqObjectList = new QTreeWidgetItem(p_pqTreeWidget);
          pqObjectList->setText(0, tr("Klasse"));

          QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqObjectList);
          pqItem->setText(0, pClass->GetKeyname());
      }

      QString qstrSorting = p_pQuery->GetOrderBy().join(", ");

      if (!qstrSorting.isEmpty())
      {
         QTreeWidgetItem* pqSorting = new QTreeWidgetItem(p_pqTreeWidget);
         pqSorting->setText(0, tr("Sortierung"));

         QTreeWidgetItem* pqItem = new QTreeWidgetItem(pqSorting);
         pqItem->setText(0, qstrSorting);
      }
   }
}

/** +-=---------------------------------------------------------Fr 24. Aug 13:53:43 2012----------*
 * @method  CwmsQueryEditor::AddQueryElement                 // private, static                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmElement                   //                                   *
 * @param   QTreeWidgetItem* p_pqParent                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 24. Aug 13:53:43 2012----------*/
void CwmsQueryEditor::AddQueryElement(CdmQueryElement* p_pCdmElement, QTreeWidgetItem* p_pqParent)
{
   if (CHKPTR(p_pCdmElement) && CHKPTR(p_pqParent))
   {
      QTreeWidgetItem* pqItem = new QTreeWidgetItem(p_pqParent);

      if (p_pCdmElement->GetQueryElementType() == eDmQueryElementTypeAnd)
      {
         pqItem->setText(0, tr("UND"));
      }
      else if (p_pCdmElement->GetQueryElementType() == eDmQueryElementTypeOr)
      {
         pqItem->setText(0, tr("ODER"));
      }
      else
      {
         pqItem->setText(0, p_pCdmElement->GetConditionAsString());
      }

      if (p_pCdmElement->GetQueryElementType() != eDmQueryElementTypeCompare)
      {
         QLinkedList<CdmQueryElement*> qlChilds;
         p_pCdmElement->GetChildList(qlChilds);

         QLinkedList<CdmQueryElement*>::iterator qllIt = qlChilds.begin();
         QLinkedList<CdmQueryElement*>::iterator qllItEnd = qlChilds.end();

         for (; qllIt != qllItEnd; ++qllIt)
         {
            AddQueryElement(*qllIt, pqItem); 
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:42 2012----------*
 * @method  CwmsQueryEditor::SaveClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:42 2012----------*/
void CwmsQueryEditor::SaveClickedSlot()
{
   QMenu* pqMenu = new QMenu(this);
   pqMenu->addAction(tr("Datei"));
   pqMenu->addAction(tr("Sicht"));
   QAction* pqAction = pqMenu->exec(QCursor::pos());

   if (pqAction)
   {
      if (pqAction->text() == tr("Datei"))
      {
         QString qstrFilename = CwmsQueryModelExportCsv::AskForFilename(".wql");

         if (!qstrFilename.isEmpty())
         {
            CwmsQueryModelExportCsv::SaveContent(qstrFilename, m_pqteEditor->toPlainText());
         }
      }
      else
      {
         CwmsView cView = CwmsView::Create();

         if (cView.IsValid())
         {
            cView.SetViewCommand(m_pqteEditor->toPlainText());
            CwmsViewEditor::Edit(cView, true, this);
         }
      }
   }
}

void CwmsQueryEditor::EditClickedSlot()
{
   CdmObject* pObject = m_cCdmModel.GetObject(m_pqtvResult);

   if (pObject)
   {
      CwmsguiObjectEditorSelector::Edit(pObject, this);
   }
}

/** +-=---------------------------------------------------------Do 26. Jul 11:39:53 2012----------*
 * @method  CwmsQueryEditor::SaveResultClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:39:53 2012----------*/
void CwmsQueryEditor::SaveResultClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(m_cCdmModel);
}

/** +-=---------------------------------------------------------Do 26. Jul 11:40:05 2012----------*
 * @method  CwmsQueryEditor::ClearResultClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Jul 11:40:05 2012----------*/
void CwmsQueryEditor::ClearResultClickedSlot()
{
   m_cCdmModel.Execute("");
}
