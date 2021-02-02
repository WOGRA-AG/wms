/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsClassValidationEditor.cpp
 ** Started Implementation: 2012/11/26
 ** Description:
 **
 ** implements the editor for class validations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmExecutor.h"
#include "CdmExecutorValidator.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmClassValidator.h"
#include "CdmClass.h"

// own Includes
#include "CwmsClassValidationEditor.h"

/** +-=---------------------------------------------------------Mo 26. Nov 11:40:21 2012----------*
 * @method  CwmsClassValidationEditor::CwmsClassValidationEditor // public                        *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:40:21 2012----------*/
CwmsClassValidationEditor::CwmsClassValidationEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:40:45 2012----------*
 * @method  CwmsClassValidationEditor::~CwmsClassValidationEditor // public, virtual              *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsClassValidationEditor                                     *
 *----------------last changed: --------------------------------Mo 26. Nov 11:40:45 2012----------*/
CwmsClassValidationEditor::~CwmsClassValidationEditor()
{
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:41:05 2012----------*
 * @method  CwmsClassValidationEditor::FillDialog            // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassValidator* p_pValidator                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:41:05 2012----------*/
void CwmsClassValidationEditor::FillDialog(CdmClassValidator* p_pValidator)
{
   if (CHKPTR(p_pValidator))
   {
      m_rpValidator = p_pValidator;
      m_pqleName->setText(p_pValidator->GetName());
      m_pqteErrorMessage->setPlainText(p_pValidator->GetErrorMessage());
      m_pCode->setPlainText(p_pValidator->GetCode());

      if (m_rpValidator->GetValidationType() == eDmValidationTypeObjectList)
      {
         m_pqrbObjectListValidation->setChecked(true);
      }
      else
      {
         m_pqrbObjectValidation->setChecked(true);
      }
   }
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:43:46 2012----------*
 * @method  CwmsClassValidationEditor::SyntaxCheckClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:43:46 2012----------*/
void CwmsClassValidationEditor::SyntaxCheckClickedSlot()
{
    CdmExecutor::GetExecutor()->GetValidator()->CreateEngine();

    if (CdmExecutor::GetExecutor()->GetValidator()->GetEngine()->SyntaxCheck(m_pCode->toPlainText()))
    {
       CdmMessageManager::information(tr("Syntax gültig"), tr("Die Syntax des Codes ist gültig."));
    }
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:44:56 2012----------*
 * @method  CwmsClassValidationEditor::Validate              // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:44:56 2012----------*/
bool CwmsClassValidationEditor::Validate()
{
   bool bRet = true;

   if (m_pqleName->text().isEmpty())
   {
      CdmMessageManager::critical(tr("Unvollständige Daten"), tr("Das Feld Name muss gefüllt werden."));
   }

   if (m_pqteErrorMessage->toPlainText().isEmpty())
   {
      CdmMessageManager::critical(tr("Unvollständige Daten"), tr("Das Feld Fehlermeldung muss gefüllt werden."));
   }

   if (m_pCode->toPlainText().isEmpty())
   {
      CdmMessageManager::critical(tr("Unvollständige Daten"), tr("Ein Validator ohne Validierungscode ist ungültig."));
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:45:05 2012----------*
 * @method  CwmsClassValidationEditor::SaveData              // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:45:05 2012----------*/
bool CwmsClassValidationEditor::SaveData()
{
   bool bRet = true;

   m_rpValidator->SetName(m_pqleName->text());
   m_rpValidator->SetMessage(m_pqteErrorMessage->toPlainText());
   m_rpValidator->SetCode(m_pCode->toPlainText());
   m_rpValidator->SetVersion(m_rpValidator->GetVersion() + 1);

   if (m_pqrbObjectValidation->isChecked())
   {
      m_rpValidator->SetValidationType(eDmValidationTypeObject);
   }
   else
   {
      m_rpValidator->SetValidationType(eDmValidationTypeObjectList);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 26. Nov 11:43:54 2012----------*
 * @method  CwmsClassValidationEditor::OKClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 11:43:54 2012----------*/
void CwmsClassValidationEditor::OKClickedSlot()
{
   if (Validate())
   {
      if (SaveData())
      {
         accept();
      }
   }
}

/** +-=---------------------------------------------------------Mo 26. Nov 12:34:54 2012----------*
 * @method  CwmsClassValidationEditor::EditValidation        // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   CdmClassValidator* p_pValidator                  //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 26. Nov 12:34:54 2012----------*/
bool CwmsClassValidationEditor::EditValidation(CdmClass* p_pCdmClass,
                                               CdmClassValidator* p_pValidator,
                                               bool p_bNew,
                                               QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsClassValidationEditor cEditor(p_pqwParent);
   cEditor.FillDialog(p_pValidator);

   if (cEditor.exec() == QDialog::Accepted)
   {
      p_pCdmClass->SetModified();
      p_pCdmClass->Commit();
      bRet = true;
   }
   else if (p_bNew)
   {
      p_pCdmClass->DeleteValidator(p_pValidator);
      p_pCdmClass->Commit();
   }

   return bRet;
}
