/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormViewEditor.cpp
 ** Started Implementation: 2012/09/11
 ** Description:
 **
 ** implements the editor for view forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/


// System and QT Includes

// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsListWidgetHelper.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsViewManager.h"
#include "CwmsReportManager.h"
#include "CwmsFormViewEditor.h"

/** +-=---------------------------------------------------------Di 11. Sep 13:33:54 2012----------*
 * @method  CwmsFormViewEditor::CwmsFormViewEditor           // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:33:54 2012----------*/
CwmsFormViewEditor::CwmsFormViewEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Di 11. Sep 13:34:17 2012----------*
 * @method  CwmsFormViewEditor::~CwmsFormViewEditor          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormViewEditor                                            *
 *----------------last changed: --------------------------------Di 11. Sep 13:34:17 2012----------*/
CwmsFormViewEditor::~CwmsFormViewEditor()
{
}

/** +-=---------------------------------------------------------Di 11. Sep 14:44:21 2012----------*
 * @method  CwmsFormViewEditor::FillDialog                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsFormView p_cForm                             //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:44:21 2012----------*/
void CwmsFormViewEditor::FillDialog(CwmsFormView p_cForm, bool p_bNew)
{
   m_cForm.SetObject(p_cForm.GetObject());

   if (m_cForm.IsValid() && !p_bNew)
   {
      m_pqleName->setText(m_cForm.GetName());
      m_pqchbDefault->setChecked(m_cForm.GetDefault());
      m_pqchbSaveAsCsv->setChecked(m_cForm.GetSaveAsCsvEnabled());
      m_pqchbPrint->setChecked(m_cForm.GetPrintEnabled());
      m_pqchbReadOnly->setChecked(m_cForm.GetReadOnly());
      FillViews();
      FillReport(m_cForm.GetPrintingTemplate());
   }
}


/** +-=---------------------------------------------------------Di 11. Sep 13:37:26 2012----------*
 * @method  CwmsFormViewEditor::FillReport                   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:37:26 2012----------*/
void CwmsFormViewEditor::FillReport(CdmObject* p_pCdmObject)
{
   m_cTemplate.SetObject(p_pCdmObject);

   if (m_cTemplate.IsValid())
   {
      m_pqlePrintingTemplate->setText(m_cTemplate.GetName());
   }
   else
   {
      m_pqlePrintingTemplate->setText("");
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 13:37:05 2012----------*
 * @method  CwmsFormViewEditor::FillViews                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:37:05 2012----------*/
void CwmsFormViewEditor::FillViews()
{
   m_pqlwViews->clear();
   QLinkedList<QString> qllFunctions = m_cForm.GetViews();

   QLinkedList<QString>::iterator qllIt = qllFunctions.begin();
   QLinkedList<QString>::iterator qllItEnd = qllFunctions.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwViews);
      pItem->setText(*qllIt);
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:36:21 2012----------*
 * @method  CwmsFormViewEditor::SelectPrintingTemplateClickedSlot // private, slots               *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:36:21 2012----------*/
void CwmsFormViewEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

/** +-=---------------------------------------------------------Di 11. Sep 13:59:43 2012----------*
 * @method  CwmsFormViewEditor::AddViewClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:59:43 2012----------*/
void CwmsFormViewEditor::AddViewClickedSlot()
{
   CwmsViewManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetContainer(), nullptr, this, "Name");

   if (pCdmObject)
   {
      CwmsView cView(pCdmObject);
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwViews);
      pItem->setText(cView.GetName());
      pItem->setData(Qt::UserRole, cView.GetUri());
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:00:10 2012----------*
 * @method  CwmsFormViewEditor::RemoveViewClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:00:10 2012----------*/
void CwmsFormViewEditor::RemoveViewClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwViews->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:01:04 2012----------*
 * @method  CwmsFormViewEditor::ViewMemberUpClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:01:04 2012----------*/
void CwmsFormViewEditor::ViewUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwViews);
}

/** +-=---------------------------------------------------------Di 11. Sep 14:00:57 2012----------*
 * @method  CwmsFormViewEditor::ViewMemberDownClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:00:57 2012----------*/
void CwmsFormViewEditor::ViewDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwViews);
}

/** +-=---------------------------------------------------------Di 11. Sep 13:53:48 2012----------*
 * @method  CwmsFormViewEditor::Validate                     // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:53:48 2012----------*/
bool CwmsFormViewEditor::Validate()
{
   bool bRet = true;

   if (m_pqlwViews->count() == 0)
   {
      bRet = false;
   }

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
   }

   return bRet;
}


/** +-=---------------------------------------------------------Di 11. Sep 13:53:57 2012----------*
 * @method  CwmsFormViewEditor::SaveData                     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:53:57 2012----------*/
void CwmsFormViewEditor::SaveData()
{
   if (m_cForm.IsValid())
   {
      m_cForm.SetName(m_pqleName->text());
      m_cForm.SetPrintingTemplate(m_cTemplate.GetObject());
      m_cForm.SetDefault(m_pqchbDefault->isChecked());
      m_cForm.SetExportEnabled(false);
      m_cForm.SetImportEnabled(false);
      m_cForm.SetSearchEnabled(false);
      m_cForm.SetCopyEnabled(false);
      m_cForm.SetSaveAsCsvEnabled(m_pqchbSaveAsCsv->isChecked());
      m_cForm.SetJournalEnabled(false);
      m_cForm.SetPrintEnabled(m_pqchbPrint->isChecked());
      m_cForm.SetReadOnly(m_pqchbReadOnly->isChecked());

      QLinkedList<QString> qstrlViews;

      for (int iCounter = 0; iCounter < m_pqlwViews->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwViews->item(iCounter);

         if (pItem)
         {
            qstrlViews.append(pItem->text());
         }
      }

      m_cForm.SetViews(qstrlViews);
      m_cForm.CommitObject();
   }
}


/** +-=---------------------------------------------------------Di 11. Sep 13:54:07 2012----------*
 * @method  CwmsFormViewEditor::OKClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 13:54:07 2012----------*/
void CwmsFormViewEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:03:06 2012----------*
 * @method  CwmsFormViewEditor::EditForm                     // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsFormView p_cForm                             //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:03:06 2012----------*/
void CwmsFormViewEditor::EditForm(CwmsFormView p_cForm, bool p_bNew, QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormViewEditor cEditor(p_pqwParent);
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
