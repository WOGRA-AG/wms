/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsWorkflowStepEditorDlg.cpp
 ** Started Implementation: 2012/10/10
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QList>
#include <QStringList>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CdmValue.h"
#include "CdmValueListString.h"
#include "CdmValueListObjects.h"
#include "CdmValueDictStringString.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsObjectSelectionIf.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsListWidgetHelper.h"
#include "CwmsClassMemberSelection.h"
#include "CwmsWorkflowManager.h"
#include "CwmsWorkflowMemberValueEditor.h"
#include "CwmsWorkflowDefinition.h"
#include "CwmsWorkflowStepEditorDlg.h"

/** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::CwmsWorkflowStepEditorDlg   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:32:19 2012----------*/
CwmsWorkflowStepEditorDlg::CwmsWorkflowStepEditorDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCdmObjectSubWorkflow(nullptr),
  m_bNew(false)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::~CwmsWorkflowStepEditorDlg  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbgEscalationEditorDlg                                        *
 *----------------last changed: --------------------------------Mi 10. Okt 13:34:28 2012----------*/
CwmsWorkflowStepEditorDlg::~CwmsWorkflowStepEditorDlg()
{
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:00:18 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::FillDialog            // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowStepDefinition p_cStep         //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:00:18 2012----------*/
void CwmsWorkflowStepEditorDlg::FillDialog(CwmsWorkflowStepDefinition p_cStep, bool p_bNew)
{
   if (p_cStep.IsValid())
   {
      m_bNew = p_bNew;
      m_cStep = p_cStep;

      m_pCwmsTeam->SetContainerAndDisplayValue("Teams", "Name");
      m_pCwmsTeam->SetCurrentObject(m_cStep.GetResponsibility());
      m_pqcbState->setCurrentIndex(m_cStep.GetState());
      m_pqcbType->setCurrentIndex(m_cStep.GetType());
      m_pqleName->setText(m_cStep.GetName());
      m_pqlePosition->setText(QString::number(m_cStep.GetPosition()));
      m_pqteDescription->setPlainText(m_cStep.GetDescription());
      m_pqsbMaxDuration->setValue(m_cStep.GetMaxDuration());
      
      CdmObjectContainer* pEscalationList = m_cStep.GetEscalation();

      if (CHKPTR(pEscalationList))
      {
         QString qstrWql = "select Escalation_Step, Violation_Of_Limit from \"" + pEscalationList->GetKeyname() + "\"";
         m_pCwmsEscalation->SetQuery(qstrWql);
         m_pCwmsEscalation->FillDialog();
      }

      CdmObjectContainer* pSuccessorList = m_cStep.GetSuccessors();

      if (CHKPTR(pSuccessorList))
      {
         QString qstrWql = "select ID, Successor.Name from \"" + pSuccessorList->GetKeyname() + "\"";
         m_pCwmsSuccessors->SetQuery(qstrWql);
         m_pCwmsSuccessors->FillDialog();
      }

      m_rpCdmObjectSubWorkflow = m_cStep.GetSubWorkflow();

      if (CHKPTR(m_rpCdmObjectSubWorkflow))
      {
         CwmsWorkflowDefinition cDef(m_rpCdmObjectSubWorkflow);
         m_pqleSubWorkflow->setText(cDef.GetName());
      }

      FillHiddenValues();
      FillReadOnlyValues();
      FillChangingValues();
   }
}

/** +-=---------------------------------------------------------Fr 26. Okt 11:47:18 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::FillChangingValues    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 26. Okt 11:47:18 2012----------*/
void CwmsWorkflowStepEditorDlg::FillChangingValues()
{
   CdmValue* pCdmValue = nullptr;
   CdmObject* pCdmObject = m_cStep.GetObject();
   pCdmValue = pCdmObject->GetValue("Changing_Values");

   if (CHKPTR(pCdmValue))
   {
      CdmValueDictStringString* pDict = (CdmValueDictStringString*)pCdmValue;
      QMap<QString, QString> qmDict = pDict->GetDict();

      QMap<QString, QString>::iterator qmIt = qmDict.begin();
      QMap<QString, QString>::iterator qmItEnd = qmDict.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwValueChanges);
         pItem->setText(0, qmIt.key());
         pItem->setText(1, qmIt.value());
      }
   }
}

/** +-=---------------------------------------------------------Fr 26. Okt 11:46:55 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::FillReadOnlyValues    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 26. Okt 11:46:55 2012----------*/
void CwmsWorkflowStepEditorDlg::FillReadOnlyValues()
{BODY_TRY
   CdmObject* pCdmObject = m_cStep.GetObject();

   if (CHKPTR(pCdmObject))
   {
       CdmValue*pCdmValue = pCdmObject->GetValue("ReadOnly_Members");

       if (CHKPTR(pCdmValue))
       {
          CdmValueListString* pList = dynamic_cast<CdmValueListString*>(pCdmValue);
          QList<QString> qllEntries = pList->GetList();

          QList<QString>::iterator qllIt    = qllEntries.begin();
          QList<QString>::iterator qllItEnd = qllEntries.end();

          for ( ; qllIt != qllItEnd; ++qllIt)
          {
             m_pqlwReadOnlyMembers->addItem(*qllIt);
          }
       }
   }
BODY_CATCH}

/** +-=---------------------------------------------------------Fr 26. Okt 11:45:59 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::FillHiddenValues      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 26. Okt 11:45:59 2012----------*/
void CwmsWorkflowStepEditorDlg::FillHiddenValues()
{BODY_TRY
    CdmObject* pCdmObject = m_cStep.GetObject();

    if (CHKPTR(pCdmObject))
    {
        CdmValue* pCdmValue = pCdmObject->GetValue("Hidden_Members");

        if (CHKPTR(pCdmValue))
        {
            CdmValueListString* pList = dynamic_cast<CdmValueListString*>(pCdmValue);

            if (CHKPTR(pList))
            {
                m_pqlwHiddenMembers->addItems(pList->GetStringList());
            }
        }
    }
BODY_CATCH}

/** +-=---------------------------------------------------------Do 20. Dez 15:17:39 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::GetClass              // private                           *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 15:17:39 2012----------*/
CdmClass* CwmsWorkflowStepEditorDlg::GetClass()
{
   CdmClass* pClass = nullptr;
   CdmObject* pObject = m_cStep.GetObject();

   if (CHKPTR(pObject))
   {
      CdmObject* pObjectOwner = pObject->GetOwner();

      if (CHKPTR(pObjectOwner))
      {
         CwmsWorkflowDefinition cDef(pObjectOwner);
         QString qstrClass = cDef.GetClass();

         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (CHKPTR(pManager))
         {
            CdmModelElement* pElement = (CdmModelElement*)pManager->GetUriObject(qstrClass);

            if (CHKPTR(pElement) && pElement->IsClass())
            {
               pClass = (CdmClass*)pElement;
            }
         }
      }
   }

   return pClass;
}

/** +-=---------------------------------------------------------Do 20. Dez 11:45:02 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::AddValueChangeMemberClickedSlot // private, slots          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:45:02 2012----------*/
void CwmsWorkflowStepEditorDlg::AddValueChangeMemberClickedSlot()
{
   CdmClass* pClass = GetClass();

   if (CHKPTR(pClass))
   {
      CwmsWorkflowMemberValueEditor cEditor(this);
      cEditor.FillDialog(pClass);
      if (cEditor.exec() == QDialog::Accepted)
      {
         QString qstrMember = cEditor.GetMemberKeyname();
         QString qstrValue = cEditor.GetValue();

         QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwValueChanges);
         pItem->setText(0, qstrMember);
         pItem->setText(1, qstrValue);
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 11:45:14 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::RemoveValueChangeMemberClickedSlot // private, slots       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:45:14 2012----------*/
void CwmsWorkflowStepEditorDlg::RemoveValueChangeMemberClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwValueChanges);

   if (pItem)
   {
      DELPTR(pItem);
   }
   else
   {
      CdmMessageManager::critical(tr("Kein Wert gewÃ¤hlt"), tr("Um einen Wert lÃ¶schen zu kÃ¶nnen mÃ¼ssen Sie diesen markieren."));
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 11:45:26 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::AddSubProcessClickedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:45:26 2012----------*/
void CwmsWorkflowStepEditorDlg::AddSubProcessClickedSlot()
{
   CdmClass* pClass = GetClass();
   CwmsWorkflowManager cManager;
   CdmObjectContainer* pList = cManager.GetObjectList();

   if (CHKPTR(pClass) && CHKPTR(pList))
   {
      QString qstrUri = pClass->GetUriInternal();
      QString qstrWql = "select Name from \"" + pList->GetKeyname() + "\" where AND(Type = 1, Class = " + qstrUri + ")";
      m_rpCdmObjectSubWorkflow = CwmsObjectSelectionIf::GetObject(qstrWql, this);

      if (m_rpCdmObjectSubWorkflow)
      {
         CwmsWorkflowDefinition cDef(m_rpCdmObjectSubWorkflow);
         m_pqleSubWorkflow->setText(cDef.GetName());
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 11:45:51 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::RemoveSubProcessClickedSlot // private, slots              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:45:51 2012----------*/
void CwmsWorkflowStepEditorDlg::RemoveSubProcessClickedSlot()
{
   m_rpCdmObjectSubWorkflow = nullptr;
   m_pqleSubWorkflow->setText("");
}

/** +-=---------------------------------------------------------Do 20. Dez 16:07:38 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::AddHiddenMemberClickedSlot // private, slots               *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:07:38 2012----------*/
void CwmsWorkflowStepEditorDlg::AddHiddenMemberClickedSlot()
{
   CdmClass* pClass = GetClass();

   if (CHKPTR(pClass))
   {
      QStringList qstrlSelection = CwmsClassMemberSelection::GetMemberSelection(pClass, this);

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqlwHiddenMembers->addItem(qstrlSelection[iCounter]);
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 16:07:48 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::RemoveHiddenMemberClickedSlot // private, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:07:48 2012----------*/
void CwmsWorkflowStepEditorDlg::RemoveHiddenMemberClickedSlot()
{
   QListWidgetItem* pItem = CwmsListWidgetHelper::GetSelectedItem(m_pqlwHiddenMembers);

   if (pItem)
   {
      DELPTR(pItem);
   }
   else
   {
      CdmMessageManager::critical(tr("Kein Wert gewÃ¤hlt"), tr("Um einen Wert lÃ¶schen zu kÃ¶nnen mÃ¼ssen Sie diesen markieren."));
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 16:07:59 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::AddReadOnlyMemberClickedSlot // private, slots             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:07:59 2012----------*/
void CwmsWorkflowStepEditorDlg::AddReadOnlyMemberClickedSlot()
{
   CdmClass* pClass = GetClass();

   if (CHKPTR(pClass))
   {
      QStringList qstrlSelection = CwmsClassMemberSelection::GetMemberSelection(pClass, this);

      for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
      {
         m_pqlwReadOnlyMembers->addItem(qstrlSelection[iCounter]);
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 16:08:09 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::RemoveReadOnlyMemberClickedSlot // private, slots          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:08:09 2012----------*/
void CwmsWorkflowStepEditorDlg::RemoveReadOnlyMemberClickedSlot()
{
   QListWidgetItem* pItem = CwmsListWidgetHelper::GetSelectedItem(m_pqlwReadOnlyMembers);

   if (pItem)
   {
      DELPTR(pItem);
   }
   else
   {
      CdmMessageManager::critical(tr("Kein Wert gewÃ¤hlt"), tr("Um einen Wert lÃ¶schen zu kÃ¶nnen mÃ¼ssen Sie diesen markieren."));
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 11:47:27 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::Validate              // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:47:27 2012----------*/
bool CwmsWorkflowStepEditorDlg::Validate()
{
   bool bRet = true;

   if (m_pqleName->text().isEmpty())
   {
      CdmMessageManager::critical(tr("Pflichtfeld nicht gefÃ¼llt"), tr("Das Feld Name muss gefÃ¼llt sein."));
      bRet = false;
   }
   
   if (!m_pCwmsTeam->GetSelectedObject())
   {
      CdmMessageManager::critical(tr("Pflichtfeld nicht gefÃ¼llt"), tr("Das Bearbeitungsteam muss gefÃ¼llt sein."));
      bRet = false;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 28. Dez 15:28:11 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::SaveData              // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 28. Dez 15:28:11 2012----------*/
bool CwmsWorkflowStepEditorDlg::SaveData()
{
   m_cStep.SetDescription(m_pqteDescription->toPlainText());
   m_cStep.SetMaxDuration(m_pqsbMaxDuration->value());
   m_cStep.SetName(m_pqleName->text());
   m_cStep.SetResponsibility(m_pCwmsTeam->GetSelectedObject());
   m_cStep.SetState(m_pqcbState->currentIndex());
   m_cStep.SetSubWorkflow(m_rpCdmObjectSubWorkflow);
   m_cStep.SetType(m_pqcbType->currentIndex());
   SaveChangeValues();
   SaveHiddenMembers();
   SaveReadOnlyMembers();
   return m_cStep.CommitObject();
}


/** +-=---------------------------------------------------------Do 20. Dez 16:39:59 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::SaveHiddenMembers     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:39:59 2012----------*/
void CwmsWorkflowStepEditorDlg::SaveHiddenMembers()
{
   QList<QString> qllValues;

   for (int iCounter = 0; iCounter < m_pqlwHiddenMembers->count(); ++iCounter)
   {
      QListWidgetItem* pItem = m_pqlwHiddenMembers->item(iCounter);

      if (CHKPTR(pItem))
      {
         qllValues.append(pItem->text());
      }
   }

   CdmValue* pCdmValue = nullptr;
   CdmObject* pCdmObject = m_cStep.GetObject();
   pCdmValue = pCdmObject->GetValue("Hidden_Members");

   if (CHKPTR(pCdmValue))
   {
      CdmValueListString* pDict = (CdmValueListString*)pCdmValue;
      pDict->SetList(qllValues);
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 16:40:09 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::SaveReadOnlyMembers   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:40:09 2012----------*/
void CwmsWorkflowStepEditorDlg::SaveReadOnlyMembers()
{
   QList<QString> qllValues;

   for (int iCounter = 0; iCounter < m_pqlwReadOnlyMembers->count(); ++iCounter)
   {
      QListWidgetItem* pItem = m_pqlwReadOnlyMembers->item(iCounter);

      if (CHKPTR(pItem))
      {
         qllValues.append(pItem->text());
      }
   }

   CdmValue* pCdmValue = nullptr;
   CdmObject* pCdmObject = m_cStep.GetObject();
   pCdmValue = pCdmObject->GetValue("ReadOnly_Members");

   if (CHKPTR(pCdmValue))
   {
      CdmValueListString* pDict = (CdmValueListString*)pCdmValue;
      pDict->SetList(qllValues);
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 16:35:33 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::SaveChangeValues      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 16:35:33 2012----------*/
void CwmsWorkflowStepEditorDlg::SaveChangeValues()
{
   QMap<QString, QString> qmChangeValues;

   for (int iCounter = 0; iCounter < m_pqtwValueChanges->topLevelItemCount(); ++iCounter)
   {
      QTreeWidgetItem* pItem = m_pqtwValueChanges->topLevelItem(iCounter);

      if (CHKPTR(pItem))
      {
         qmChangeValues.insert(pItem->text(0), pItem->text(1));
      }
   }

   CdmValue* pCdmValue = nullptr;
   CdmObject* pCdmObject = m_cStep.GetObject();
   pCdmValue = pCdmObject->GetValue("Changing_Values");

   if (CHKPTR(pCdmValue))
   {
      CdmValueDictStringString* pDict = (CdmValueDictStringString*)pCdmValue;
      pDict->SetValue(qmChangeValues);
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 11:47:48 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::OKClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 11:47:48 2012----------*/
void CwmsWorkflowStepEditorDlg::OKClickedSlot()
{
   if (Validate() && SaveData())
   {
      accept();
   }
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:00:39 2012----------*
 * @method  CwmsWorkflowStepEditorDlg::Edit                  // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CwmsWorkflowStepDefinition p_cStep         //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:00:39 2012----------*/
bool CwmsWorkflowStepEditorDlg::Edit(CwmsWorkflowStepDefinition p_cStep,
                                     bool p_bNew,
                                     QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowStepEditorDlg cEditor(p_pqwParent);
   cEditor.FillDialog(p_cStep, p_bNew);

   if (cEditor.exec() == QDialog::Accepted)
   {
      bRet = true;
   }
   else if (p_bNew)
   {
      p_cStep.SetDeleted();
      p_cStep.CommitObject();
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 30. Dez 14:01:08 2012----------*
 * @method  CwmsWorkflowStepObjectEditorDescriptor::GetClassKeyname // public                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:01:08 2012----------*/
QString CwmsWorkflowStepObjectEditorDescriptor::GetClassKeyname()
{
   return "Workflow_Step_Definition";
}

/** +-=---------------------------------------------------------So 30. Dez 14:01:16 2012----------*
 * @method  CwmsWorkflowStepObjectEditorDescriptor::DisplayEditor // protected                    *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:01:16 2012----------*/
bool CwmsWorkflowStepObjectEditorDescriptor::DisplayEditor(CdmObject* p_pCdmObject,
                                                           EwmsGuiDisplayMode p_eDisplayMode,
                                                           QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowStepDefinition cStep(p_pCdmObject);

   if (p_eDisplayMode == eWmsGuiDisplayModeNew)
   {
      bRet = CwmsWorkflowStepEditorDlg::Edit(cStep, true, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeWrite)
   {
      bRet = CwmsWorkflowStepEditorDlg::Edit(cStep, false, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeRead)
   {
      bRet = CwmsWorkflowStepEditorDlg::Edit(cStep, false, p_pqwParent);
   }

   return bRet;
}
