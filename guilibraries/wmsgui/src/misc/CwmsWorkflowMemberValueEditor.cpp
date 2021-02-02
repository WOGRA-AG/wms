/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsWorkflowMemberValueEditor.cpp
 ** Started Implementation: 2012/12/19
 ** Description:
 **
 ** Implements the editor for changing values thru steps.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmClass.h"

// own Includes
#include "CwmsWorkflowMemberValueEditor.h"


/** +-=---------------------------------------------------------Mi 19. Dez 16:44:46 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::CwmsWorkflowMemberValueEditor // public                *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Dez 16:44:46 2012----------*/
CwmsWorkflowMemberValueEditor::CwmsWorkflowMemberValueEditor(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 19. Dez 16:44:52 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::~CwmsWorkflowMemberValueEditor // public, virtual      *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsWorkflowMemberValueEditor                                 *
 *----------------last changed: --------------------------------Mi 19. Dez 16:44:52 2012----------*/
CwmsWorkflowMemberValueEditor::~CwmsWorkflowMemberValueEditor()
{
}

/** +-=---------------------------------------------------------Do 20. Dez 15:37:24 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::FillDialog        // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 15:37:24 2012----------*/
void CwmsWorkflowMemberValueEditor::FillDialog(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);
      QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pMember = qmIt.value();

         if (CHKPTR(pMember))
         {
            m_pqcbMember->addItem(pMember->GetKeyname());
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Dez 10:07:10 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::Validate          // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 10:07:10 2012----------*/
bool CwmsWorkflowMemberValueEditor::Validate()
{
   return true;
}

/** +-=---------------------------------------------------------Do 20. Dez 10:07:36 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::GetMemberKeyname  // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 10:07:36 2012----------*/
QString CwmsWorkflowMemberValueEditor::GetMemberKeyname()
{
   return m_pqcbMember->currentText();
}

/** +-=---------------------------------------------------------Do 20. Dez 10:07:53 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::GetValue          // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 10:07:53 2012----------*/
QString CwmsWorkflowMemberValueEditor::GetValue()
{
   return m_pqleValue->text();
}

/** +-=---------------------------------------------------------Do 20. Dez 10:08:51 2012----------*
 * @method  CwmsWorkflowMemberValueEditor::OKClickedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Dez 10:08:51 2012----------*/
void CwmsWorkflowMemberValueEditor::OKClickedSlot()
{
   if (Validate())
   {
      accept();
   }
}