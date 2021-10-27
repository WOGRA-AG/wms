/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsWorkflowDefinitionEditor.cpp
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
#include "CdmClass.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"

// own Includes
#include "CwmsClassSelectionIf.h"
#include "CwmsWorkflowDefitionEditor.h"

/** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::CwmsWorkflowDefinitionEditor   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:32:19 2012----------*/
CwmsWorkflowDefinitionEditor::CwmsWorkflowDefinitionEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCdmClass(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::~CwmsWorkflowDefinitionEditor  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbgEscalationEditorDlg                                        *
 *----------------last changed: --------------------------------Mi 10. Okt 13:34:28 2012----------*/
CwmsWorkflowDefinitionEditor::~CwmsWorkflowDefinitionEditor()
{
}

/** +-=---------------------------------------------------------Di 18. Dez 13:39:31 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::SelectClassClickedSlot // private, slots                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Dez 13:39:31 2012----------*/
void CwmsWorkflowDefinitionEditor::SelectClassClickedSlot()
{
   CdmClass* pClass = CwmsClassSelectionIf::GetClass(this);

   if (pClass)
   {
      m_rpCdmClass = pClass;
      m_pqleWorkflowClass->setText(pClass->GetKeyname());
   }
   
}

/** +-=---------------------------------------------------------Mi 24. Okt 14:55:28 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::FillDialog         // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsWorkflowDefinition p_cWorkflow                //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 14:55:28 2012----------*/
void CwmsWorkflowDefinitionEditor::FillDialog(CwmsWorkflowDefinition p_cWorkflow, bool p_bNew)
{
   if (p_cWorkflow.IsValid())
   {
      m_bNew = p_bNew;
      m_cWorkflow = p_cWorkflow;
      m_pqleName->setText(m_cWorkflow.GetName());
      m_pqteDescription->setPlainText(m_cWorkflow.GetDescription());
      m_pqcbWorkflowType->setCurrentIndex(m_cWorkflow.GetType());

      CdmObjectContainer* pWorkflowList = m_cWorkflow.GetWorkflow();

      if (CHKPTR(pWorkflowList))
      {
         QString qstrWql = "select Position, Name, Responsibility.Name from \"" + pWorkflowList->GetKeyname() + "\"";
         m_pCwmsWorkflowSteps->SetQuery(qstrWql);
         m_pCwmsWorkflowSteps->FillDialog();
      }

      QString qstrClassUri = p_cWorkflow.GetClass();

      if (!qstrClassUri.isEmpty())
      {  
         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (CHKPTR(pManager))
         {
            CdmModelElement* pElement = (CdmModelElement*)pManager->GetUriObject(qstrClassUri);

            if (pElement && pElement->IsClass())
            {
               m_rpCdmClass = (CdmClass*)pElement;
               m_pqleWorkflowClass->setText(m_rpCdmClass->GetKeyname());
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:35:26 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::Validate                 // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:35:26 2012----------*/
bool CwmsWorkflowDefinitionEditor::Validate()
{
   bool bRet = true;

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
      MSG_CRIT("Fehlende Angabe", "Das Feld Name muss gefüllt sein!");
   }

   if (!m_rpCdmClass)
   {
      bRet = false;
      MSG_CRIT("Fehlende Angabe", "Sie müssen eine Klasse gewählt haben!");
   }
   
   return bRet;
}

/** +-=---------------------------------------------------------Di 18. Dez 13:24:32 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::SaveData           // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Dez 13:24:32 2012----------*/
bool CwmsWorkflowDefinitionEditor::SaveData()
{
   m_cWorkflow.SetName(m_pqleName->text());
   m_cWorkflow.SetDescription(m_pqteDescription->toPlainText());
   m_cWorkflow.SetType(m_pqcbWorkflowType->currentIndex());

   if (m_rpCdmClass)
   {
      m_cWorkflow.SetClass(m_rpCdmClass->GetUriInternal());
   }
   else
   {
      m_cWorkflow.SetClass("");
   }

   return m_cWorkflow.CommitObject();
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:36:15 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::OKClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:36:15 2012----------*/
void CwmsWorkflowDefinitionEditor::OKClickedSlot()
{
   if (Validate() && SaveData())
   {
      accept();
   }
}

/** +-=---------------------------------------------------------Mi 24. Okt 14:55:10 2012----------*
 * @method  CwmsWorkflowDefinitionEditor::Edit               // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CwmsWorkflowDefinition p_cWorkflow                //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 24. Okt 14:55:10 2012----------*/
bool CwmsWorkflowDefinitionEditor::Edit(CwmsWorkflowDefinition p_cWorkflow,
                                        bool p_bNew,
                                        QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowDefinitionEditor cEditor(p_pqwParent);
   cEditor.FillDialog(p_cWorkflow, p_bNew);

   if (cEditor.exec() == QDialog::Accepted)
   {
      bRet = true;
   }
   else if (p_bNew)
   {
      p_cWorkflow.SetDeleted();
      p_cWorkflow.CommitObject();
   }

   return bRet;
}


/** +-=---------------------------------------------------------So 30. Dez 13:50:17 2012----------*
 * @method  CwmsWorkflowDefintionObjectEditorDescriptor::GetClassKeyname // public                *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 13:50:17 2012----------*/
QString CwmsWorkflowDefintionObjectEditorDescriptor::GetClassKeyname()
{
   return "Workflow_Definition";
}

/** +-=---------------------------------------------------------So 30. Dez 13:51:41 2012----------*
 * @method  CwmsWorkflowDefintionObjectEditorDescriptor::DisplayEditor // protected               *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 13:51:41 2012----------*/
bool CwmsWorkflowDefintionObjectEditorDescriptor::DisplayEditor(CdmObject* p_pCdmObject,
                                                                EwmsGuiDisplayMode p_eDisplayMode,
                                                                QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsWorkflowDefinition cWorkflow(p_pCdmObject);

   if (p_eDisplayMode == eWmsGuiDisplayModeNew)
   {
      bRet = CwmsWorkflowDefinitionEditor::Edit(cWorkflow, true, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeWrite)
   {
      bRet = CwmsWorkflowDefinitionEditor::Edit(cWorkflow, false, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeRead)
   {
      bRet = CwmsWorkflowDefinitionEditor::Edit(cWorkflow, false, p_pqwParent);
   }

   return bRet;
}
