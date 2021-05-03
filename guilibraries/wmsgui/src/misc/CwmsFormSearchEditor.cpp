/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormStandardObjectListEditor.cpp
 ** Started Implementation: 2012/09/10
 ** Description:
 **
 ** implements the editor for searchform configuration
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsListWidgetHelper.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsViewManager.h"
#include "CwmsReportManager.h"
#include "CwmsClassMemberSelection.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsFormSearchEditor.h"


/** +-=---------------------------------------------------------Mo 17. Sep 18:39:00 2012----------*
 * @method  CwmsFormSearchEditor::CwmsFormSearchEditor       // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:39:00 2012----------*/
CwmsFormSearchEditor::CwmsFormSearchEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpContainer(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:39:13 2012----------*
 * @method  CwmsFormSearchEditor::~CwmsFormSearchEditor      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormStandardObjectListEditor                              *
 *----------------last changed: --------------------------------Mo 17. Sep 18:39:13 2012----------*/
CwmsFormSearchEditor::~CwmsFormSearchEditor()
{

}

/** +-=---------------------------------------------------------Mo 17. Sep 18:39:59 2012----------*
 * @method  CwmsFormSearchEditor::FillDialog                 // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CwmsFormSearch p_cForm                           //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:39:59 2012----------*/
void CwmsFormSearchEditor::FillDialog(CwmsFormSearch p_cForm, bool p_bNew)
{
   m_cForm.SetObject(p_cForm.GetObject());

   if (m_cForm.IsValid() && !p_bNew)
   {
      CdmObjectContainer* pCdmList = m_cForm.GetSearchList();
      SetObjectList(pCdmList);
      m_pqleName->setText(m_cForm.GetName());
      m_pqchbExport->setChecked(m_cForm.GetExportEnabled());
      m_pqchbImport->setChecked(m_cForm.GetImportEnabled());
      m_pqchbPrint->setChecked(m_cForm.GetPrintEnabled());
      m_pqchbReadOnly->setChecked(m_cForm.GetReadOnly());
      m_pqchbNewObject->setChecked(m_cForm.GetNewEnabled());
      m_pqchbCopy->setChecked(m_cForm.GetCopyEnabled());
      m_pqchbSaveAsCsv->setChecked(m_cForm.GetSaveAsCsvEnabled());
      FillReport(m_cForm.GetPrintingTemplate());
      FillFunctions();
      FillSearchMembers();
      FillVisibleMembers();
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:49:08 2012----------*
 * @method  CwmsFormSearchEditor::FillReport                 // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:49:08 2012----------*/
void CwmsFormSearchEditor::FillReport(CdmObject* p_pCdmObject)
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

/** +-=---------------------------------------------------------Mo 17. Sep 18:49:21 2012----------*
 * @method  CwmsFormSearchEditor::FillFunctions              // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:49:21 2012----------*/
void CwmsFormSearchEditor::FillFunctions()
{
   m_pqlwFunctions->clear();
   QList<QString> qllFunctions = m_cForm.GetFunctions();

   QList<QString>::iterator qllIt = qllFunctions.begin();
   QList<QString>::iterator qllItEnd = qllFunctions.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwFunctions);
      pItem->setText(*qllIt);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:49:30 2012----------*
 * @method  CwmsFormSearchEditor::FillSearchMembers          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:49:30 2012----------*/
void CwmsFormSearchEditor::FillSearchMembers()
{
   m_pqlwSearchMembers->clear();
   QList<QString> qllSearchMembers = m_cForm.GetSearchMembers();
   QList<QString>::iterator qllIt = qllSearchMembers.begin();
   QList<QString>::iterator qllItEnd = qllSearchMembers.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSearchMembers);
      pItem->setText(*qllIt);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:49:41 2012----------*
 * @method  CwmsFormSearchEditor::FillVisibleMembers         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:49:41 2012----------*/
void CwmsFormSearchEditor::FillVisibleMembers()
{
   m_pqlwVisibleMembers->clear();
   QList<QString> qllVisibleMembers = m_cForm.GetDisplayMembers();
   QList<QString>::iterator qllIt = qllVisibleMembers.begin();
   QList<QString>::iterator qllItEnd = qllVisibleMembers.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwVisibleMembers);
      pItem->setText(*qllIt);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:50:39 2012----------*
 * @method  CwmsFormSearchEditor::SetObjectList              // public                            *
 * @return  void                                             //                                   *
 * @param   int p_lObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:50:39 2012----------*/
void CwmsFormSearchEditor::SetObjectList(int p_lObjectListId)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pCdmOLManager = pCdmManager->GetContainerManager();

      if (CHKPTR(pCdmOLManager))
      {
         SetObjectList(pCdmOLManager->FindContainerById(p_lObjectListId));
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:51:52 2012----------*
 * @method  CwmsFormSearchEditor::SetObjectList              // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:51:52 2012----------*/
void CwmsFormSearchEditor::SetObjectList(CdmObjectContainer* p_pContainer)
{
   m_rpContainer = p_pContainer;

   if (m_rpContainer)
   {
      m_pqleObjectList->setText(m_rpContainer->GetCaption() + " (" + m_rpContainer->GetKeyname() + ")");
      m_pqwFunctions->setEnabled(true);
      m_pqwSearchMembers->setEnabled(true);
      m_pqwVisibleMembers->setEnabled(true);
   }
   else
   {
      m_pqleObjectList->setText("");
      m_pqwFunctions->setEnabled(false);
      m_pqwSearchMembers->setEnabled(false);
      m_pqwVisibleMembers->setEnabled(false);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:52:33 2012----------*
 * @method  CwmsFormSearchEditor::SelectPrintingTemplateClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:52:33 2012----------*/
void CwmsFormSearchEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:52:49 2012----------*
 * @method  CwmsFormSearchEditor::SelectObjectListClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:52:49 2012----------*/
void CwmsFormSearchEditor::SelectObjectListClickedSlot()
{
   CdmObjectContainer* pCdmList = nullptr;
   CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);

   if (pCdmClass)
   {
      pCdmList = CwmsContainerSelectionIf::GetObjectContainer(pCdmClass->GetSchemeId(), pCdmClass->GetId(), this);
   }

   SetObjectList(pCdmList);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:54:14 2012----------*
 * @method  CwmsFormSearchEditor::AddFunctionClickedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:54:14 2012----------*/
void CwmsFormSearchEditor::AddFunctionClickedSlot()
{
   if (m_rpContainer)
   {
      QStringList qstrList = CwmsClassMemberSelection::GetFunctionSelection(m_rpContainer->GetClass(), false, this);

      for (int iCounter = 0; iCounter < qstrList.count(); ++iCounter)
      {
         QString qstrName = qstrList[iCounter];

         if (m_pqlwFunctions->findItems(qstrName, Qt::MatchExactly).count() == 0)
         {
            QListWidgetItem* pItem = new QListWidgetItem(m_pqlwFunctions);
            pItem->setText(qstrName);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:54:19 2012----------*
 * @method  CwmsFormSearchEditor::AddVisibleMemberClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:54:19 2012----------*/
void CwmsFormSearchEditor::AddVisibleMemberClickedSlot()
{
   if (m_rpContainer)
   {
      QStringList qstrList = CwmsClassMemberSelection::GetMemberSelection(m_rpContainer->GetClass(), this);

      for (int iCounter = 0; iCounter < qstrList.count(); ++iCounter)
      {
         QString qstrName = qstrList[iCounter];

         if (m_pqlwVisibleMembers->findItems(qstrName, Qt::MatchExactly).count() == 0)
         {
            QListWidgetItem* pItem = new QListWidgetItem(m_pqlwVisibleMembers);
            pItem->setText(qstrName);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:54:24 2012----------*
 * @method  CwmsFormSearchEditor::AddSearchMemberClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:54:24 2012----------*/
void CwmsFormSearchEditor::AddSearchMemberClickedSlot()
{
   if (m_rpContainer)
   {
      QStringList qstrList = CwmsClassMemberSelection::GetMemberSelection(m_rpContainer->GetClass(), this);

      for (int iCounter = 0; iCounter < qstrList.count(); ++iCounter)
      {
         QString qstrName = qstrList[iCounter];

         if (m_pqlwSearchMembers->findItems(qstrName, Qt::MatchExactly).count() == 0)
         {
            QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSearchMembers);
            pItem->setText(qstrName);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:54:29 2012----------*
 * @method  CwmsFormSearchEditor::RemoveFunctionClickedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:54:29 2012----------*/
void CwmsFormSearchEditor::RemoveFunctionClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwFunctions->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:54:36 2012----------*
 * @method  CwmsFormSearchEditor::RemoveVisibleMemberClickedSlot // private, slots                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:54:36 2012----------*/
void CwmsFormSearchEditor::RemoveVisibleMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwVisibleMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:07 2012----------*
 * @method  CwmsFormSearchEditor::RemoveSearchMemberClickedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:07 2012----------*/
void CwmsFormSearchEditor::RemoveSearchMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwSearchMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:17 2012----------*
 * @method  CwmsFormSearchEditor::VisibleMemberUpClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:17 2012----------*/
void CwmsFormSearchEditor::VisibleMemberUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwVisibleMembers);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:22 2012----------*
 * @method  CwmsFormSearchEditor::VisibleMemberDownClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:22 2012----------*/
void CwmsFormSearchEditor::VisibleMemberDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwVisibleMembers);
}



/** +-=---------------------------------------------------------Mo 17. Sep 18:56:31 2012----------*
 * @method  CwmsFormSearchEditor::FunctionUpClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:31 2012----------*/
void CwmsFormSearchEditor::FunctionUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwFunctions);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:41 2012----------*
 * @method  CwmsFormSearchEditor::FunctionDownClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:41 2012----------*/
void CwmsFormSearchEditor::FunctionDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwFunctions);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:49 2012----------*
 * @method  CwmsFormSearchEditor::SearchMemberUpClickedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:49 2012----------*/
void CwmsFormSearchEditor::SearchMemberUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwSearchMembers);
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:56:57 2012----------*
 * @method  CwmsFormSearchEditor::SearchMemberDownClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:56:57 2012----------*/
void CwmsFormSearchEditor::SearchMemberDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwSearchMembers);
}


/** +-=---------------------------------------------------------Mo 17. Sep 18:57:32 2012----------*
 * @method  CwmsFormSearchEditor::Validate                   // protected, virtual                *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:57:32 2012----------*/
bool CwmsFormSearchEditor::Validate()
{
   bool bRet = true;

   if (!m_rpContainer)
   {
      bRet = false;
   }

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:58:03 2012----------*
 * @method  CwmsFormSearchEditor::SaveData                   // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:58:03 2012----------*/
void CwmsFormSearchEditor::SaveData()
{
   if (m_cForm.IsValid())
   {
      m_cForm.SetName(m_pqleName->text());
      m_cForm.SetPrintingTemplate(m_cTemplate.GetObject());

      if (m_rpContainer)
      {
         m_cForm.SetSearchList(m_rpContainer);
      }
      
      m_cForm.SetExportEnabled(m_pqchbExport->isChecked());
      m_cForm.SetImportEnabled(m_pqchbImport->isChecked());
      m_cForm.SetPrintEnabled(m_pqchbPrint->isChecked());
      m_cForm.SetReadOnly(m_pqchbReadOnly->isChecked());
      m_cForm.SetSaveAsCsvEnabled(m_pqchbSaveAsCsv->isChecked());
      m_cForm.SetCopyEnabled(m_pqchbCopy->isChecked());
      m_cForm.SetNewEnabled(m_pqchbNewObject->isChecked());
      QList<QString> qstrlFunctions;

      for (int iCounter = 0; iCounter < m_pqlwFunctions->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwFunctions->item(iCounter);

         if (pItem)
         {
            qstrlFunctions.append(pItem->text());
         }
      }

      m_cForm.SetFunctions(qstrlFunctions);
      QList<QString> qstrlVisibleMembers;

      for (int iCounter = 0; iCounter < m_pqlwVisibleMembers->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwVisibleMembers->item(iCounter);

         if (pItem)
         {
            qstrlVisibleMembers.append(pItem->text());
         }
      }

      m_cForm.SetDisplayMembers(qstrlVisibleMembers);
      QList<QString> qstrlSearchMembers;

      for (int iCounter = 0; iCounter < m_pqlwSearchMembers->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwSearchMembers->item(iCounter);

         if (pItem)
         {
            qstrlSearchMembers.append(pItem->text());
         }
      }

      m_cForm.SetSearchMembers(qstrlSearchMembers);
      m_cForm.CommitObject();
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:58:14 2012----------*
 * @method  CwmsFormSearchEditor::OKClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:58:14 2012----------*/
void CwmsFormSearchEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}


/** +-=---------------------------------------------------------Mo 17. Sep 18:58:32 2012----------*
 * @method  CwmsFormSearchEditor::EditForm                   // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsFormSearch p_cForm                           //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:58:32 2012----------*/
void CwmsFormSearchEditor::EditForm(CwmsFormSearch p_cForm, bool p_bNew, QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormSearchEditor cEditor(p_pqwParent);
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
