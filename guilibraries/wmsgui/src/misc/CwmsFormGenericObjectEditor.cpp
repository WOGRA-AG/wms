/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormGenericObjectEditor.cpp
 ** Started Implementation: 2012/09/12
 ** Description:
 **
 ** implements the editor for generic forms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmModelElement.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsFormObjectRefAssignment.h"
#include "CwmsListWidgetHelper.h"
#include "CwmsObjectListSelectionIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsViewManager.h"
#include "CwmsReportManager.h"
#include "CwmsClassMemberSelection.h"
#include "CwmsClassSelectionIf.h"
#include "CwmsFormGenericObjectEditor.h"

/** +-=---------------------------------------------------------Mi 12. Sep 14:10:10 2012----------*
 * @method  CwmsFormGenericObjectEditor::CwmsFormGenericObjectEditor // public                    *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:10:10 2012----------*/
CwmsFormGenericObjectEditor::CwmsFormGenericObjectEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
m_rpCdmClass(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:11:22 2012----------*
 * @method  CwmsFormGenericObjectEditor::~CwmsFormGenericObjectEditor // public, virtual          *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormGenericObjectEditor                                   *
 *----------------last changed: --------------------------------Mi 12. Sep 14:11:22 2012----------*/
CwmsFormGenericObjectEditor::~CwmsFormGenericObjectEditor()
{
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:13:02 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillDialog          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsFormObject p_cForm                           //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:13:02 2012----------*/
void CwmsFormGenericObjectEditor::FillDialog(CwmsFormObject p_cForm, bool p_bNew)
{
   m_cForm.SetObject(p_cForm.GetObject());

   if (m_cForm.IsValid() && !p_bNew)
   {
      QString qstrClassUri = m_cForm.GetClassUri();
      SetClass(qstrClassUri);
      m_pqleName->setText(m_cForm.GetName());
      m_pqchbDefault->setChecked(m_cForm.GetDefault());
      m_pqchbJournal->setChecked(m_cForm.GetJournalEnabled());
      m_pqchbPrint->setChecked(m_cForm.GetPrintEnabled());
      m_pqchbReadOnly->setChecked(m_cForm.GetReadOnly());
      m_pqteWql->setPlainText(m_cForm.GetWql());
      FillReport(m_cForm.GetPrintingTemplate());
      FillDefaultValues();
      FillObjectReferences();
      FillDisplayTypes();
      FillVisibleMembers();
      FillFunctions();

      m_pqcbDisplayTypes->addItem(tr("Normal"));
      m_pqcbDisplayTypes->addItem(tr("Verzeichnis"));
      m_pqcbDisplayTypes->addItem(tr("Datei"));
      m_pqcbDisplayTypes->addItem(tr("Status"));
      m_pqcbDisplayTypes->addItem(tr("Verschlüsselt"));
      m_pqcbDisplayTypes->addItem(tr("Link"));
      m_pqcbDisplayTypes->addItem(tr("Json"));
      m_pqcbDisplayTypes->addItem(tr("Xml"));
      m_pqcbDisplayTypes->addItem(tr("Html"));
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:50:48 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillDisplayTypes    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:50:48 2012----------*/
void CwmsFormGenericObjectEditor::FillDisplayTypes()
{
   QMap<QString, int> qmDisplayTypes = m_cForm.GetDisplayTypes();

   QMap<QString, int>::iterator qmIt = qmDisplayTypes.begin();
   QMap<QString, int>::iterator qmItEnd = qmDisplayTypes.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwDisplayTypes);
      pItem->setText(0, qmIt.key());
      pItem->setText(1, CdmModelElement::GetDisplayTypeAsString((EdmStringDisplayType)qmIt.value()));
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:50:27 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillObjectReferences // private                          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:50:27 2012----------*/
void CwmsFormGenericObjectEditor::FillObjectReferences()
{
   QMap<QString, QString> qmObjectRefs = m_cForm.GetObjectRefAssignment();

   QMap<QString, QString>::iterator qmIt = qmObjectRefs.begin();
   QMap<QString, QString>::iterator qmItEnd = qmObjectRefs.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwObjectRefs);
      pItem->setText(0, qmIt.key());
      pItem->setText(1, qmIt.value());
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:50:08 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillDefaultValues   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:50:08 2012----------*/
void CwmsFormGenericObjectEditor::FillDefaultValues()
{
   QMap<QString, QString> qmDefaultValues = m_cForm.GetDefaultValues();

   QMap<QString, QString>::iterator qmIt = qmDefaultValues.begin();
   QMap<QString, QString>::iterator qmItEnd = qmDefaultValues.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwDefaultValues);
      pItem->setText(0, qmIt.key());
      pItem->setText(1, qmIt.value());
   }
}

/** +-=---------------------------------------------------------Fr 14. Dez 09:51:33 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillFunctions       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 09:51:33 2012----------*/
void CwmsFormGenericObjectEditor::FillFunctions()
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

/** +-=---------------------------------------------------------Mi 12. Sep 14:36:51 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillVisibleMembers  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:36:51 2012----------*/
void CwmsFormGenericObjectEditor::FillVisibleMembers()
{
   m_pqlwVisibleMembers->clear();
   QList<QString> qllVisibleMembers = m_cForm.GetVisibleMembers();
   QList<QString>::iterator qllIt = qllVisibleMembers.begin();
   QList<QString>::iterator qllItEnd = qllVisibleMembers.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QListWidgetItem* pItem = new QListWidgetItem(m_pqlwVisibleMembers);
      pItem->setText(*qllIt);
   }
}

/** +-=---------------------------------------------------------Fr 14. Dez 09:50:53 2012----------*
 * @method  CwmsFormGenericObjectEditor::AddFunctionClickedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 09:50:53 2012----------*/
void CwmsFormGenericObjectEditor::AddFunctionClickedSlot()
{
   QStringList qstrList = CwmsClassMemberSelection::GetFunctionSelection(m_rpCdmClass, true, this);

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


/** +-=---------------------------------------------------------Mi 12. Sep 14:37:46 2012----------*
 * @method  CwmsFormGenericObjectEditor::AddVisibleMemberClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:37:46 2012----------*/
void CwmsFormGenericObjectEditor::AddVisibleMemberClickedSlot()
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

/** +-=---------------------------------------------------------Fr 14. Dez 09:50:47 2012----------*
 * @method  CwmsFormGenericObjectEditor::RemoveFunctionClickedSlot // private, slots              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 09:50:47 2012----------*/
void CwmsFormGenericObjectEditor::RemoveFunctionClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwFunctions->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Fr 14. Dez 09:50:42 2012----------*
 * @method  CwmsFormGenericObjectEditor::FunctionUpClickedSlot // private, slots                  *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 09:50:42 2012----------*/
void CwmsFormGenericObjectEditor::FunctionUpClickedSlot()
{
   CwmsListWidgetHelper::MoveItemUp(m_pqlwFunctions);
}

/** +-=---------------------------------------------------------Fr 14. Dez 09:50:39 2012----------*
 * @method  CwmsFormGenericObjectEditor::FunctionDownClickedSlot // private, slots                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 09:50:39 2012----------*/
void CwmsFormGenericObjectEditor::FunctionDownClickedSlot()
{

   CwmsListWidgetHelper::MoveItemDown(m_pqlwFunctions);
}


/** +-=---------------------------------------------------------Mi 12. Sep 14:38:13 2012----------*
 * @method  CwmsFormGenericObjectEditor::RemoveVisibleMemberClickedSlot // private, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:38:13 2012----------*/
void CwmsFormGenericObjectEditor::RemoveVisibleMemberClickedSlot()
{
   QList<QListWidgetItem*> qlSelected = m_pqlwVisibleMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QListWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 15:29:46 2012----------*
 * @method  CwmsFormGenericObjectEditor::UpdateComboBoxes    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 15:29:46 2012----------*/
void CwmsFormGenericObjectEditor::UpdateComboBoxes()
{
   if (m_rpCdmClass)
   {
      QMap<qint64, CdmMember*> qmMembers;
      m_rpCdmClass->GetMemberMap(qmMembers);

      QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (pCdmMember)
         {
            if (m_pqtwDefaultValues->findItems(pCdmMember->GetKeyname(), Qt::MatchExactly).count() == 0)
            {
               m_pqcbDefaultMember->addItem(pCdmMember->GetKeyname());
            }

            if (pCdmMember->GetValueType() == eDmValueContainerRef ||
                pCdmMember->GetValueType() == eDmValueObjectRef)
            {
               if (m_pqtwObjectRefs->findItems(pCdmMember->GetKeyname(), Qt::MatchExactly).count() == 0)
               {
                  m_pqcbObjectRefMember->addItem(pCdmMember->GetKeyname());
               }
            }
            else if (pCdmMember->GetValueType() == eDmValueCharacterDocument ||
                     pCdmMember->GetValueType() == eDmValueString)
            {
               if (m_pqtwDisplayTypes->findItems(pCdmMember->GetKeyname(), Qt::MatchExactly).count() == 0)
               {
                  m_pqcbDisplayMembers->addItem(pCdmMember->GetKeyname());
               }
            }
         }
      }
   }
   else
   {
      m_pqcbDisplayMembers->clear();
      m_pqcbObjectRefMember->clear();
      m_pqcbDefaultMember->clear();
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:36:09 2012----------*
 * @method  CwmsFormGenericObjectEditor::GetSelectedMember   // public                            *
 * @return  QListWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:36:09 2012----------*/
QListWidgetItem* CwmsFormGenericObjectEditor::GetSelectedMember()
{
   QListWidgetItem* pItem = nullptr;
   QList<QListWidgetItem*> qlItems = m_pqlwVisibleMembers->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}


/** +-=---------------------------------------------------------Mi 12. Sep 14:38:41 2012----------*
 * @method  CwmsFormGenericObjectEditor::VisibleMemberUpClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:38:41 2012----------*/
void CwmsFormGenericObjectEditor::VisibleMemberUpClickedSlot()
{
   QListWidgetItem* pItem = GetSelectedMember();

   if (pItem)
   {
      int iCurrentRow = m_pqlwVisibleMembers->row(pItem);

      if (iCurrentRow > 0)
      {
         QListWidgetItem* pItemAbove = m_pqlwVisibleMembers->item(iCurrentRow - 1);

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

/** +-=---------------------------------------------------------Mi 12. Sep 14:38:47 2012----------*
 * @method  CwmsFormGenericObjectEditor::VisibleMemberDownClickedSlot // private, slots           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:38:47 2012----------*/
void CwmsFormGenericObjectEditor::VisibleMemberDownClickedSlot()
{
   QListWidgetItem* pItem = GetSelectedMember();

   if (pItem)
   {
      int iCurrentRow = m_pqlwVisibleMembers->row(pItem);

      if (iCurrentRow >= 0)
      {
         QListWidgetItem* pItemDown = m_pqlwVisibleMembers->item(iCurrentRow + 1);

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

/** +-=---------------------------------------------------------Fr 14. Dez 13:53:05 2012----------*
 * @method  CwmsFormGenericObjectEditor::SetClass            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrUri                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 13:53:05 2012----------*/
void CwmsFormGenericObjectEditor::SetClass(QString p_qstrUri)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmModelElement* pElement = (CdmModelElement*)pCdmManager->GetUriObject(p_qstrUri);

      if (CHKPTR(pElement) && pElement->IsClass())
      {
         SetClass((CdmClass*)pElement);
      }
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:34:30 2012----------*
 * @method  CwmsFormGenericObjectEditor::SetClass            // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:34:30 2012----------*/
void CwmsFormGenericObjectEditor::SetClass(CdmClass* p_pCdmClass)
{
   if (m_rpCdmClass != p_pCdmClass)
   {
      m_pqtwDefaultValues->clear();
      m_pqtwDisplayTypes->clear();
      m_pqtwObjectRefs->clear();
      m_rpCdmClass = p_pCdmClass;
   }

   if (m_rpCdmClass)
   {
      m_pqleClass->setText(m_rpCdmClass->GetCaption() + " (" + m_rpCdmClass->GetKeyname() + ")");
      m_pqwVisibleMembers->setEnabled(true);
      m_pqwDefaultsValues->setEnabled(true);
      m_pqwDisplayTypes->setEnabled(true);
      m_pqwObjectRefAssignment->setEnabled(true);
   }
   else
   {
      m_pqleClass->setText("");
      m_pqwVisibleMembers->setEnabled(false);
      m_pqwDefaultsValues->setEnabled(false);
      m_pqwDisplayTypes->setEnabled(false);
      m_pqwObjectRefAssignment->setEnabled(false);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:34:51 2012----------*
 * @method  CwmsFormGenericObjectEditor::SelectPrintingTemplateClickedSlot // private, slots      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:34:51 2012----------*/
void CwmsFormGenericObjectEditor::SelectPrintingTemplateClickedSlot()
{
   CwmsReportManager cManager;
   CdmObject* pCdmObject = CwmsObjectSelectionIf::GetObject(cManager.GetObjectList(), nullptr, this, "Name");
   FillReport(pCdmObject);
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:40:37 2012----------*
 * @method  CwmsFormGenericObjectEditor::SelectClassClickedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:40:37 2012----------*/
void CwmsFormGenericObjectEditor::SelectClassClickedSlot()
{
   CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);
   SetClass(pCdmClass);
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:35:28 2012----------*
 * @method  CwmsFormGenericObjectEditor::FillReport          // private                           *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:35:28 2012----------*/
void CwmsFormGenericObjectEditor::FillReport(CdmObject* p_pCdmObject)
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

/** +-=---------------------------------------------------------Mi 12. Sep 16:10:09 2012----------*
 * @method  CwmsFormGenericObjectEditor::AddDisplayTypeClickedSlot // private, slots              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:10:09 2012----------*/
void CwmsFormGenericObjectEditor::AddDisplayTypeClickedSlot()
{
   QString qstrMember = m_pqcbDisplayMembers->currentText();
   EdmStringDisplayType eType = (EdmStringDisplayType)m_pqcbDisplayTypes->currentIndex();

   if (m_pqtwDisplayTypes->findItems(qstrMember, Qt::MatchExactly).count() == 0)
   {
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwDisplayTypes);
      pItem->setText(0, qstrMember);
      pItem->setText(1, CdmModelElement::GetDisplayTypeAsString(eType));
      pItem->setData(0, Qt::UserRole, eType);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:09:39 2012----------*
 * @method  CwmsFormGenericObjectEditor::RemoveDisplayTypeClickedSlot // private, slots           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:09:39 2012----------*/
void CwmsFormGenericObjectEditor::RemoveDisplayTypeClickedSlot()
{
   QList<QTreeWidgetItem*> qlSelected = m_pqtwDisplayTypes->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QTreeWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:11:40 2012----------*
 * @method  CwmsFormGenericObjectEditor::AddObjectReferenceClickedSlot // private, slots          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:11:40 2012----------*/
void CwmsFormGenericObjectEditor::AddObjectReferenceClickedSlot()
{
   QString qstrMember = m_pqcbObjectRefMember->currentText();
   QString qstrKeyname;

   if (m_pqtwDisplayTypes->findItems(qstrMember, Qt::MatchExactly).count() == 0)
   {
      CdmClass* pCdmClass = nullptr;
      const CdmMember* pCdmMember = m_rpCdmClass->FindMember(qstrMember);

      if (pCdmMember)
      {
         int iId = pCdmMember->GetClassReference();

         CdmClassManager* pCdmManager = pCdmMember->GetClassManager();

         if (pCdmManager)
         {
            pCdmClass = pCdmManager->FindClassById(iId);
         }
      }

      qstrKeyname = CwmsFormObjectRefAssignment::GetObjectReferenceSelection(this, pCdmClass);

      if (!qstrKeyname.isEmpty())
      {
         QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwObjectRefs);
         pItem->setText(0, qstrMember);
         pItem->setText(1, qstrKeyname);
      }
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:11:30 2012----------*
 * @method  CwmsFormGenericObjectEditor::RemoveObjectReferenceClickedSlot // private, slots       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:11:30 2012----------*/
void CwmsFormGenericObjectEditor::RemoveObjectReferenceClickedSlot()
{
   QList<QTreeWidgetItem*> qlSelected = m_pqtwObjectRefs->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QTreeWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:12:25 2012----------*
 * @method  CwmsFormGenericObjectEditor::AddDefaultValuesClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:12:25 2012----------*/
void CwmsFormGenericObjectEditor::AddDefaultValuesClickedSlot()
{
   QString qstrMember = m_pqcbDisplayMembers->currentText();
   QString qstrValue = m_pqleDefaultValue->text();

   if (m_pqtwDefaultValues->findItems(qstrMember, Qt::MatchExactly).count() == 0)
   {
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwDefaultValues);
      pItem->setText(0, qstrMember);
      pItem->setText(1, qstrValue);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:12:38 2012----------*
 * @method  CwmsFormGenericObjectEditor::RemoveDefaultValuesClickedSlot // private, slots         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:12:38 2012----------*/
void CwmsFormGenericObjectEditor::RemoveDefaultValuesClickedSlot()
{
   QList<QTreeWidgetItem*> qlSelected = m_pqtwDefaultValues->selectedItems();

   for (int iCounter = 0; iCounter < qlSelected.count(); ++iCounter)
   {
      QTreeWidgetItem* pItem = qlSelected[iCounter];
      DELPTR(pItem);
   }

   UpdateComboBoxes();
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:26:29 2012----------*
 * @method  CwmsFormGenericObjectEditor::Validate            // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:26:29 2012----------*/
bool CwmsFormGenericObjectEditor::Validate()
{
   bool bRet = true;

   if (!m_rpCdmClass)
   {
      bRet = false;
      CdmMessageManager::critical(tr("Keine Klasse gewählt"), tr("Der Objekteditor benötigt die Klasse als Pflichtfeld"));
   }


   return bRet;
}

/** +-=---------------------------------------------------------Fr 14. Dez 13:56:12 2012----------*
 * @method  CwmsFormGenericObjectEditor::SaveData            // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 13:56:12 2012----------*/
bool CwmsFormGenericObjectEditor::SaveData()
{
   bool bRet = false;
   if (m_cForm.IsValid())
   {
      m_cForm.SetName(m_pqleName->text());
      m_cForm.SetPrintingTemplate(m_cTemplate.GetObject());

      if (m_rpCdmClass)
      {
         m_cForm.SetClassUri(m_rpCdmClass->GetUriInternal());
      }

      m_cForm.SetDefault(m_pqchbDefault->isChecked());
      m_cForm.SetJournalEnabled(m_pqchbJournal->isChecked());
      m_cForm.SetPrintEnabled(m_pqchbPrint->isChecked());
      m_cForm.SetReadOnly(m_pqchbReadOnly->isChecked());
      m_cForm.SetWql(m_pqteWql->toPlainText());

      QList<QString> qstrlVisibleMembers;

      for (int iCounter = 0; iCounter < m_pqlwVisibleMembers->count(); ++iCounter)
      {
         QListWidgetItem* pItem = m_pqlwVisibleMembers->item(iCounter);

         if (pItem)
         {
            qstrlVisibleMembers.append(pItem->text());
         }
      }

      m_cForm.SetVisibleMembers(qstrlVisibleMembers);

      QMap<QString, int> qmDisplayTypes;

      for (int iCounter = 0; iCounter < m_pqtwDisplayTypes->topLevelItemCount(); ++iCounter)
      {
         QTreeWidgetItem* pItem = m_pqtwDisplayTypes->topLevelItem(iCounter);

         if (pItem)
         {
            qmDisplayTypes.insert(pItem->text(0), pItem->data(0, Qt::UserRole).toInt());
         }
      }

      m_cForm.SetDisplayTypes(qmDisplayTypes);
      QMap<QString, QString> qmObjectRefs;

      for (int iCounter = 0; iCounter < m_pqtwObjectRefs->topLevelItemCount(); ++iCounter)
      {
         QTreeWidgetItem* pItem = m_pqtwObjectRefs->topLevelItem(iCounter);

         if (pItem)
         {
            qmObjectRefs.insert(pItem->text(0), pItem->text(1));
         }
      }

      m_cForm.SetObjectRefAssignment(qmObjectRefs);
      QMap<QString, QString> qmDefaultValues;

      for (int iCounter = 0; iCounter < m_pqtwDefaultValues->topLevelItemCount(); ++iCounter)
      {
         QTreeWidgetItem* pItem = m_pqtwDefaultValues->topLevelItem(iCounter);

         if (pItem)
         {
            qmDefaultValues.insert(pItem->text(0), pItem->text(1));
         }
      }

      m_cForm.SetDefaultValues(qmDefaultValues);

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
      bRet = m_cForm.CommitObject();
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 12. Sep 14:26:05 2012----------*
 * @method  CwmsFormGenericObjectEditor::OKClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 14:26:05 2012----------*/
void CwmsFormGenericObjectEditor::OKClickedSlot()
{
   if (Validate() && SaveData())
   {
      accept();
   }
}

/** +-=---------------------------------------------------------Mi 12. Sep 16:45:53 2012----------*
 * @method  CwmsFormGenericObjectEditor::EditForm            // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsFormObject p_cForm                           //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 12. Sep 16:45:53 2012----------*/
void CwmsFormGenericObjectEditor::EditForm(CwmsFormObject p_cForm,
                                           bool p_bNew,
                                           QWidget* p_pqwParent)
{
   if (p_cForm.IsValid())
   {
      CwmsFormGenericObjectEditor cEditor(p_pqwParent);
      cEditor.FillDialog(p_cForm, p_bNew);

      if (cEditor.exec() != QDialog::Accepted && p_bNew)
      {
         p_cForm.SetDeleted();
         p_cForm.CommitObject();
      }
   }
}
