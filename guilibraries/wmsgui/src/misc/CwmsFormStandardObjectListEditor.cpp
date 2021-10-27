/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormStandardContainerEditor.cpp
 ** Started Implementation: 2012/09/10
 ** Description:
 **
 ** implements the editor for standardobjectlistform configuration
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
#include "CwmsFormStandardObjectListEditor.h"


/** +-=---------------------------------------------------------Mo 10. Sep 14:02:33 2012----------*
 * @method  CwmsFormStandardContainerEditor::CwmsFormStandardContainerEditor // public          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:02:33 2012----------*/
CwmsFormStandardContainerEditor::CwmsFormStandardContainerEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
m_rpCdmClass(nullptr),
m_rpCdmSelectionList(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:02:58 2012----------*
 * @method  CwmsFormStandardContainerEditor::~CwmsFormStandardContainerEditor // public, virtual*
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormStandardContainerEditor                              *
 *----------------last changed: --------------------------------Mo 10. Sep 14:02:58 2012----------*/
CwmsFormStandardContainerEditor::~CwmsFormStandardContainerEditor()
{
}

/** +-=---------------------------------------------------------Di 11. Sep 15:44:27 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillDialog     // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CwmsFormStandardObjectList p_cForm               //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 15:44:27 2012----------*/
void CwmsFormStandardContainerEditor::FillDialog(CwmsFormStandardContainer p_cForm, bool p_bNew)
{
   m_cForm.SetObject(p_cForm.GetObject());

   if (m_cForm.IsValid() && !p_bNew)
   {
      QString qstrClassUri = m_cForm.GetClassUri();
      SetClass(qstrClassUri);
      m_pqleName->setText(m_cForm.GetName());
      m_pqchbDefault->setChecked(m_cForm.GetDefault());
      m_pqchbExport->setChecked(m_cForm.GetExportEnabled());
      m_pqchbImport->setChecked(m_cForm.GetImportEnabled());
      m_pqchbJournal->setChecked(m_cForm.GetJournalEnabled());
      m_pqchbPrint->setChecked(m_cForm.GetPrintEnabled());
      m_pqchbReadOnly->setChecked(m_cForm.GetReadOnly());
      m_pqchbSearch->setChecked(m_cForm.GetSearchEnabled());
      m_pqchbSaveAsCsv->setChecked(m_cForm.GetSaveAsCsvEnabled());
      m_pqchbCopy->setChecked(m_cForm.GetCopyEnabled());
      FillView(m_cForm.GetView());
      FillReport(m_cForm.GetPrintingTemplate());
      FillFunctions();
      FillSearchMembers();
      FillVisibleMembers();
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 15:48:03 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillReport     // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 15:48:03 2012----------*/
void CwmsFormStandardContainerEditor::FillReport(CdmObject* p_pCdmObject)
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

/** +-=---------------------------------------------------------Mo 10. Sep 15:35:45 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillView       // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 15:35:45 2012----------*/
void CwmsFormStandardContainerEditor::FillView(CdmObject* p_pCdmObject)
{
   m_cView.SetObject(p_pCdmObject);

   if (m_cView.IsValid())
   {
      m_pqleView->setText(m_cView.GetName());
      int iObjectListRef = m_cView.GetReference();

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmContainerManager* pCdmOLManager = pCdmManager->GetContainerManager();

         if (CHKPTR(pCdmOLManager))
         {
            CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerById(iObjectListRef);

            if (CHKPTR(pContainer))
            {
               const CdmClass* pCdmClass = pContainer->GetClass();
               SetClass(pCdmClass);
            }
         }
      }
   }
   else
   {
      m_pqleView->setText("");
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:38:13 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillFunctions  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:38:13 2012----------*/
void CwmsFormStandardContainerEditor::FillFunctions()
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

/** +-=---------------------------------------------------------Mo 10. Sep 14:38:25 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillSearchMembers // private                        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:38:25 2012----------*/
void CwmsFormStandardContainerEditor::FillSearchMembers()
{
	if (m_pqwSearchMembers)
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
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:38:36 2012----------*
 * @method  CwmsFormStandardContainerEditor::FillVisibleMembers // private                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:38:36 2012----------*/
void CwmsFormStandardContainerEditor::FillVisibleMembers()
{
	if (m_pqwVisibleMembers)
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
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:14:48 2012----------*
 * @method  CwmsFormStandardContainerEditor::SetClass       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrUri                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:14:48 2012----------*/
void CwmsFormStandardContainerEditor::SetClass(QString p_qstrUri)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager();

      if (CHKPTR(pCdmClassManager))
      {
         SetClass((CdmClass*)pCdmManager->GetUriObject(p_qstrUri));
      }
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:05:01 2013----------*
 * @method  CwmsFormStandardContainerEditor::SetClass       // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:05:01 2013----------*/
void CwmsFormStandardContainerEditor::SetClass(const CdmClass* p_pCdmClass)
{
   m_rpCdmClass = p_pCdmClass;

   if (m_rpCdmClass)
   {
      m_pqleClass->setText(m_rpCdmClass->GetCaption() + " (" + m_rpCdmClass->GetKeyname() + ")");
      m_pqwFunctions->setEnabled(true);

	  if (m_pqwSearchMembers)
	  {
		m_pqwSearchMembers->setEnabled(true);
	  }

	  if (m_pqwVisibleMembers)
	  {
		m_pqwVisibleMembers->setEnabled(true);
	  }
   }
   else
   {
      m_pqleClass->setText("");
      m_pqwFunctions->setEnabled(false);
      if (m_pqwSearchMembers)
      {
         m_pqwSearchMembers->setEnabled(false);
      }

      if (m_pqwVisibleMembers)
      {
         m_pqwVisibleMembers->setEnabled(false);
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 15:33:13 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectViewClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 15:33:13 2012----------*/
void CwmsFormStandardContainerEditor::SelectViewClickedSlot()
{
   CwmsViewManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetContainer(), nullptr, this, "Name");
   FillView(pCdmObject);
}

/** +-=---------------------------------------------------------Mo 10. Sep 15:33:28 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectPrintingTemplateClickedSlot // private, slots *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 15:33:28 2012----------*/
void CwmsFormStandardContainerEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:18:33 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectClassClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:18:33 2012----------*/
void CwmsFormStandardContainerEditor::SelectClassClickedSlot()
{
   CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);
   SetClass(pCdmClass);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:04:22 2012----------*
 * @method  CwmsFormStandardContainerEditor::AddFunctionClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:04:22 2012----------*/
void CwmsFormStandardContainerEditor::AddFunctionClickedSlot()
{
   QStringList qstrList = CwmsClassMemberSelection::GetFunctionSelection(m_rpCdmClass, false, this);

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

/** +-=---------------------------------------------------------Mo 10. Sep 14:08:54 2012----------*
 * @method  CwmsFormStandardContainerEditor::AddVisibleMemberClickedSlot // private, slots       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:08:54 2012----------*/
void CwmsFormStandardContainerEditor::AddVisibleMemberClickedSlot()
{
   QStringList qstrList = CwmsClassMemberSelection::GetMemberSelection(m_rpCdmClass, this);

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

/** +-=---------------------------------------------------------Mo 10. Sep 14:10:09 2012----------*
 * @method  CwmsFormStandardContainerEditor::AddSearchMemberClickedSlot // private, slots        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:10:09 2012----------*/
void CwmsFormStandardContainerEditor::AddSearchMemberClickedSlot()
{
   QStringList qstrList = CwmsClassMemberSelection::GetMemberSelection(m_rpCdmClass, this);

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

/** +-=---------------------------------------------------------Mo 10. Sep 14:11:02 2012----------*
 * @method  CwmsFormStandardContainerEditor::RemoveFunctionClickedSlot // private, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:11:02 2012----------*/
void CwmsFormStandardContainerEditor::RemoveFunctionClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwFunctions->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:11:15 2012----------*
 * @method  CwmsFormStandardContainerEditor::RemoveVisibleMemberClickedSlot // private, slots    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:11:15 2012----------*/
void CwmsFormStandardContainerEditor::RemoveVisibleMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwVisibleMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:11:26 2012----------*
 * @method  CwmsFormStandardContainerEditor::RemoveSearchMemberClickedSlot // private, slots     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:11:26 2012----------*/
void CwmsFormStandardContainerEditor::RemoveSearchMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwSearchMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:11:42 2012----------*
 * @method  CwmsFormStandardContainerEditor::VisibleMemberUpClickedSlot // private, slots        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:11:42 2012----------*/
void CwmsFormStandardContainerEditor::VisibleMemberUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwVisibleMembers);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:12:04 2012----------*
 * @method  CwmsFormStandardContainerEditor::VisibleMemberDownClickedSlot // private, slots      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:12:04 2012----------*/
void CwmsFormStandardContainerEditor::VisibleMemberDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwVisibleMembers);
}



/** +-=---------------------------------------------------------Mo 10. Sep 14:12:16 2012----------*
 * @method  CwmsFormStandardContainerEditor::FunctionUpClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:12:16 2012----------*/
void CwmsFormStandardContainerEditor::FunctionUpClickedSlot()
{
CwmsListWidgetHelper::MoveItemUp(m_pqlwFunctions);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:12:30 2012----------*
 * @method  CwmsFormStandardContainerEditor::FunctionDownClickedSlot // private, slots           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:12:30 2012----------*/
void CwmsFormStandardContainerEditor::FunctionDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwFunctions);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:12:42 2012----------*
 * @method  CwmsFormStandardContainerEditor::SearchMemberUpClickedSlot // private, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:12:42 2012----------*/
void CwmsFormStandardContainerEditor::SearchMemberUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwSearchMembers);
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:13:04 2012----------*
 * @method  CwmsFormStandardContainerEditor::SearchMemberDownClickedSlot // private, slots       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:13:04 2012----------*/
void CwmsFormStandardContainerEditor::SearchMemberDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwSearchMembers);
}

/** +-=---------------------------------------------------------Di 11. Sep 17:40:13 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectSelectionViewClickedSlot // private, slots    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:40:13 2012----------*/
void CwmsFormStandardContainerEditor::SelectSelectionViewClickedSlot()
{
   CwmsViewManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetContainer(), nullptr, this, "Name");

   if (pCdmObject)
   {
      m_cSelectionView.SetObject(pCdmObject);
      m_pqleSelectionView->setText(m_cSelectionView.GetName());

      if (m_cSelectionView.IsWql())
      {
          QString qstrWql = m_cSelectionView.GetViewCommand();
          CdmQuery* pCdmQuery = CdmQueryBuilder::BuildQuery(qstrWql);

          if (pCdmQuery)
          {
             m_rpCdmSelectionList = pCdmQuery->GetContainer();
             m_pqleSelectionObjectList->setText(m_rpCdmSelectionList->GetKeyname());
          }
          else
          {
             MSG_CRIT("Sicht ungültig",
                "Bei der Überprüfung der Sicht ist ein Fehler aufgetreten.\n Bitte überprüfen Sie die Sicht.");
          }
      }
   }
   else
   {
      m_cSelectionView.SetObject(nullptr);
      m_pqleSelectionView->setText("");
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 17:40:05 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectSelectionObjectListClickedSlot // private, slots*
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:40:05 2012----------*/
void CwmsFormStandardContainerEditor::SelectSelectionObjectListClickedSlot()
{
   CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);

   if (pCdmClass)
   {
      m_rpCdmSelectionList = CwmsContainerSelectionIf::GetObjectContainer(pCdmClass->GetSchemeId(), 
         pCdmClass->GetId(), 
         this);
   }

   if (m_rpCdmSelectionList)
   {
      m_pqleSelectionObjectList->setText(m_rpCdmSelectionList->GetKeyname());
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 17:39:59 2012----------*
 * @method  CwmsFormStandardContainerEditor::AddSelectionMemberClickedSlot // private, slots     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:39:59 2012----------*/
void CwmsFormStandardContainerEditor::AddSelectionMemberClickedSlot()
{

   if (m_rpCdmSelectionList)
   {
      const CdmClass* pCdmClass = m_rpCdmSelectionList->GetClass();

      if (pCdmClass)
      {
         QStringList qstrList = CwmsClassMemberSelection::GetMemberSelection(pCdmClass, this);

         for (int iCounter = 0; iCounter < qstrList.count(); ++iCounter)
         {
            QString qstrName = qstrList[iCounter];

            if (m_pqlwSelectionMembers->findItems(qstrName, Qt::MatchExactly).count() == 0)
            {
               QListWidgetItem* pItem = new QListWidgetItem(m_pqlwSelectionMembers);
               pItem->setText(qstrName);
            }
         }
      }
   }
   else
   {
      MSG_CRIT("Kein View oder Objektliste gewählt",
         "Um die Darstellung zu konfigurieren müssen Sie einen View oder eine Objektliste wählen.");
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 17:39:51 2012----------*
 * @method  CwmsFormStandardContainerEditor::RemoveSelectionMemberClickedSlot // private, slots  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:39:51 2012----------*/
void CwmsFormStandardContainerEditor::RemoveSelectionMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwSelectionMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 17:39:45 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectionMemberUpClickedSlot // private, slots      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:39:45 2012----------*/
void CwmsFormStandardContainerEditor::SelectionMemberUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwSelectionMembers);
}

/** +-=---------------------------------------------------------Di 11. Sep 17:39:39 2012----------*
 * @method  CwmsFormStandardContainerEditor::SelectionMemberDownClickedSlot // private, slots    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 17:39:39 2012----------*/
void CwmsFormStandardContainerEditor::SelectionMemberDownClickedSlot()
{
   CwmsListWidgetHelper::MoveItemDown(m_pqlwSelectionMembers);
}

/** +-=---------------------------------------------------------Di 11. Sep 15:44:43 2012----------*
 * @method  CwmsFormStandardContainerEditor::Validate       // protected, virtual                *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 15:44:43 2012----------*/
bool CwmsFormStandardContainerEditor::Validate()
{
   bool bRet = true;

   if (!m_cView.IsValid() && !m_rpCdmClass)
   {
      bRet = false;
   }

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Di 11. Sep 15:44:52 2012----------*
 * @method  CwmsFormStandardContainerEditor::SaveData       // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 15:44:52 2012----------*/
void CwmsFormStandardContainerEditor::SaveData()
{
   if (m_cForm.IsValid())
   {
      m_cForm.SetName(m_pqleName->text());
      m_cForm.SetView(m_cView.GetObject());
      m_cForm.SetPrintingTemplate(m_cTemplate.GetObject());

      if (m_rpCdmClass)
      {
         m_cForm.SetClassUri(m_rpCdmClass->GetUriInternal());
      }
      
      m_cForm.SetDefault(m_pqchbDefault->isChecked());
      m_cForm.SetExportEnabled(m_pqchbExport->isChecked());
      m_cForm.SetImportEnabled(m_pqchbImport->isChecked());
      m_cForm.SetJournalEnabled(m_pqchbJournal->isChecked());
      m_cForm.SetPrintEnabled(m_pqchbPrint->isChecked());
      m_cForm.SetReadOnly(m_pqchbReadOnly->isChecked());
      m_cForm.SetSearchEnabled(m_pqchbSearch->isChecked());
      m_cForm.SetSaveAsCsvEnabled(m_pqchbSaveAsCsv->isChecked());
      m_cForm.SetCopyEnabled(m_pqchbCopy->isChecked());
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

	  if (m_pqwVisibleMembers)
	  {
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
	  }

      

	  if (m_pqwSearchMembers)
	  {
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
	  }

      m_cForm.CommitObject();
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 14:22:42 2012----------*
 * @method  CwmsFormStandardContainerEditor::OKClickedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 14:22:42 2012----------*/
void CwmsFormStandardContainerEditor::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Di 11. Sep 14:46:54 2012----------*
 * @method  CwmsFormStandardContainerEditor::HideSelectionWidgets // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 11. Sep 14:46:54 2012----------*/
void CwmsFormStandardContainerEditor::HideSelectionWidgets()
{
   DELPTR(m_pqwSelection);
   DELPTR(m_pqwSelectionConfiguration);
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:22:06 2012----------*
 * @method  CwmsFormStandardContainerEditor::EditForm       // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsFormStandardObjectList p_cForm               //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:22:06 2012----------*/
void CwmsFormStandardContainerEditor::EditForm(CwmsFormStandardContainer p_cForm,
                                                bool p_bNew,
                                                QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormStandardContainerEditor cEditor(p_pqwParent);
      cEditor.HideSelectionWidgets();
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
