/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CbgWorkflowStepEditorDlg.cpp
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

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// BMS Data Includes
#include "CwmsWorkflowObject.h"
#include "CwmsEscalation.h"

// own Includes
#include "CwmsWorkflowStepExecutionEditorDlg.h"

/** +-=---------------------------------------------------------Mi 17. Okt 17:23:01 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::CwmsWorkflowStepExecutionEditorDlg // public        *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 17:23:01 2012----------*/
CwmsWorkflowStepExecutionEditorDlg::CwmsWorkflowStepExecutionEditorDlg(QWidget* p_pqwParent)
   : QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 17. Okt 17:23:10 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::~CwmsWorkflowStepExecutionEditorDlg // public, virtual*
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbgEscalationEditorDlg                                        *
 *----------------last changed: --------------------------------Mi 17. Okt 17:23:10 2012----------*/
CwmsWorkflowStepExecutionEditorDlg::~CwmsWorkflowStepExecutionEditorDlg()
{

}

/** +-=---------------------------------------------------------Mo 22. Okt 15:14:34 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::FillDialog   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowStepExecution p_cStep          //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:14:34 2012----------*/
void CwmsWorkflowStepExecutionEditorDlg::FillDialog(CwmsWorkflowStepExecution p_cStep,
                                                    bool p_bNew)
{
   if (p_cStep.IsValid())
   {
      m_bNew = p_bNew;
      m_cStep = p_cStep;

      CdmObject* pCdmObject = m_cStep.GetResponsibility();

      if (pCdmObject)
      {
         QString qstrName = pCdmObject->GetVariant("Name").toString();
         m_pqleTeam->setText(qstrName);
      }
      
      m_pqleName->setText(m_cStep.GetName());
      m_pqlePos->setText(QString::number(m_cStep.GetPosition()));
      m_pqteDescription->setPlainText(m_cStep.GetDescription());
      m_pqleTargetDate->setText(m_cStep.GetNextEscalation().toString(Qt::LocalDate));
      m_pqcbState->setCurrentIndex(m_cStep.GetCurrentState());

      CdmObject* pCdmEscalation = m_cStep.GetCurrentEscalationStep();

      if (pCdmEscalation)
      {
         CwmsEscalation cEscalation(pCdmEscalation);
         m_pqleEscalationStep->setText(QString::number(cEscalation.GetEscalationStep()));
      }
      else
      {
         m_pqleEscalationStep->setText("Termin nicht überschritten!");
      }

      CdmObject* pCdmWorkflowObject = m_cStep.GetWorkflowObject();

      if (CHKPTR(pCdmWorkflowObject))
      {
         CwmsWorkflowObject cWorkflowObject(pCdmWorkflowObject);
         m_pqleProcessObjectName->setText(cWorkflowObject.GetName());
         m_pqteProzessObjectDescrpiption->setPlainText(cWorkflowObject.GetDescription());
      }

      m_pCwmsEditor->SetCurrentUser(m_cStep.GetEditor());
   }
}

/** +-=---------------------------------------------------------Mi 17. Okt 17:23:33 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::Validate      // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 17:23:33 2012----------*/
bool CwmsWorkflowStepExecutionEditorDlg::Validate()
{
   bool bRet = true;

   // TODO

   return bRet;
}

/** +-=---------------------------------------------------------Mi 17. Okt 17:23:44 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::SaveData      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 17:23:44 2012----------*/
void CwmsWorkflowStepExecutionEditorDlg::SaveData()
{
   m_cStep.SetEditor(m_pCwmsEditor->GetSelectedUser());
   m_cStep.SetCurrentState(m_pqcbState->currentIndex());
   m_cStep.CommitObject();
}

/** +-=---------------------------------------------------------Mi 17. Okt 17:23:54 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::OKClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 17. Okt 17:23:54 2012----------*/
void CwmsWorkflowStepExecutionEditorDlg::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Mo 22. Okt 15:15:05 2012----------*
 * @method  CwmsWorkflowStepExecutionEditorDlg::Edit         // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CwmsWorkflowStepExecution p_cStep          //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 15:15:05 2012----------*/
bool CwmsWorkflowStepExecutionEditorDlg::Edit(CwmsWorkflowStepExecution p_cStep,
                                              bool p_bNew,
                                              QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowStepExecutionEditorDlg cEditor(p_pqwParent);
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

/** +-=---------------------------------------------------------So 30. Dez 14:21:53 2012----------*
 * @method  CwmsWorkflowStepExecutionObjectEditorDescriptor::GetClassKeyname // public            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:21:53 2012----------*/
QString CwmsWorkflowStepExecutionObjectEditorDescriptor::GetClassKeyname()
{
   return "Workflow_Step_Execution";
}

/** +-=---------------------------------------------------------So 30. Dez 14:21:47 2012----------*
 * @method  CwmsWorkflowStepExecutionObjectEditorDescriptor::DisplayEditor // public              *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:21:47 2012----------*/
bool CwmsWorkflowStepExecutionObjectEditorDescriptor::DisplayEditor(CdmObject* p_pCdmObject,
                                                                    EwmsGuiDisplayMode p_eDisplayMode,
                                                                    QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowStepExecution cStep(p_pCdmObject);

   if (p_eDisplayMode == eWmsGuiDisplayModeNew)
   {
      bRet = CwmsWorkflowStepExecutionEditorDlg::Edit(cStep, true, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeWrite)
   {
      bRet = CwmsWorkflowStepExecutionEditorDlg::Edit(cStep, false, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeRead)
   {
      bRet = CwmsWorkflowStepExecutionEditorDlg::Edit(cStep, false, p_pqwParent);
   }

   return bRet;
}