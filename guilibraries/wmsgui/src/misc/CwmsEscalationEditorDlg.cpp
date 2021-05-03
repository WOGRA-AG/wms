/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsEscalationEditorDlg.cpp
 ** Started Implementation: 2012/10/10
 ** Description:
 **
 ** implements the editor for escalations
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS INcludes
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmLogging.h"

// WMSGUI Includes
#include "CwmsTreeWidgetHelper.h"

// own Includes
#include "CwmsEscalationEditorDlg.h"

/** +-=---------------------------------------------------------Mi 10. Okt 13:32:19 2012----------*
 * @method  CwmsEscalationEditorDlg::CwmsEscalationEditorDlg   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:32:19 2012----------*/
CwmsEscalationEditorDlg::CwmsEscalationEditorDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:34:28 2012----------*
 * @method  CwmsEscalationEditorDlg::~CwmsEscalationEditorDlg  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsEscalationEditorDlg                                        *
 *----------------last changed: --------------------------------Mi 10. Okt 13:34:28 2012----------*/
CwmsEscalationEditorDlg::~CwmsEscalationEditorDlg()
{
}

/** +-=---------------------------------------------------------Mo 22. Okt 14:52:48 2012----------*
 * @method  CwmsEscalationEditorDlg::FillDialog              // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsEscalation p_cEscalation                     //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 14:52:48 2012----------*/
void CwmsEscalationEditorDlg::FillDialog(CwmsEscalation p_cEscalation, bool p_bNew)
{
   if (p_cEscalation.IsValid())
   {
      m_bNew = p_bNew;
      m_cEscalation = p_cEscalation;
      FillEmployees();
      m_pqsbLimit->setValue(m_cEscalation.GetViolationOfLimit());
      m_pqsbEscalationStep->setValue(m_cEscalation.GetEscalationStep());
   }
}

/** +-=---------------------------------------------------------Mi 10. Okt 18:07:02 2012----------*
 * @method  CwmsEscalationEditorDlg::FillEmployees            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 18:07:02 2012----------*/
void CwmsEscalationEditorDlg::FillEmployees()
{
   QList<int> qlEmployees = m_cEscalation.GetEmployees();
   QList<int>::iterator qllIt = qlEmployees.begin();
   QList<int>::iterator qllItEnd = qlEmployees.end();
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

      if (CHKPTR(pCumUserManager))
      {
         for (; qllIt != qllItEnd; ++qllIt)
         {
            int iUserId = *qllIt;
            CumUser* pCumUser = pCumUserManager->FindUserById(iUserId);

            if (CHKPTR(pCumUser))
            {
               AddUserToTree(pCumUser);
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 10. Okt 18:21:02 2012----------*
 * @method  CwmsEscalationEditorDlg::AddUserToTree            // private                           *
 * @return  void                                             //                                   *
 * @param   CumUser* p_pCumUser                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 18:21:02 2012----------*/
void CwmsEscalationEditorDlg::AddUserToTree(CumUser* p_pCumUser)
{
   if (CHKPTR(p_pCumUser))
   {
      int iUserId = p_pCumUser->GetId();
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwEmployees);
      pItem->setText(0, p_pCumUser->GetFirstName());
      pItem->setText(1, p_pCumUser->GetLastName());
      pItem->setData(0, Qt::UserRole, iUserId);
   }
}

/** +-=---------------------------------------------------------Do 11. Okt 09:43:56 2012----------*
 * @method  CwmsEscalationEditorDlg::AddEmployeeClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Okt 09:43:56 2012----------*/
void CwmsEscalationEditorDlg::AddEmployeeClickedSlot()
{
   AddUserToTree(m_pUsers->GetSelectedUser());
}


/** +-=---------------------------------------------------------Do 11. Okt 09:44:06 2012----------*
 * @method  CwmsEscalationEditorDlg::RemoveEmployeeClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Okt 09:44:06 2012----------*/
void CwmsEscalationEditorDlg::RemoveEmployeeClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwEmployees);

   if (pItem)
   {
      DELPTR(pItem);
   }
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:35:26 2012----------*
 * @method  CwmsEscalationEditorDlg::Validate                 // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:35:26 2012----------*/
bool CwmsEscalationEditorDlg::Validate()
{
   bool bRet = true;

   if (m_pqtwEmployees->topLevelItemCount() == 0)
   {
      bRet = false;
      CdmMessageManager::critical(tr("Fehlende Angabe"), 
                                  tr("Mindestens ein Mitarbeiter muss dem Eskalationsschritt hinzguefügt werden!"));
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:36:01 2012----------*
 * @method  CwmsEscalationEditorDlg::SaveData                 // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:36:01 2012----------*/
void CwmsEscalationEditorDlg::SaveData()
{
   for (int iCounter = 0 ; iCounter < m_pqtwEmployees->topLevelItemCount(); ++iCounter)
   {
      QTreeWidgetItem* pItem = m_pqtwEmployees->topLevelItem(iCounter);

      if (pItem)
      {
         m_cEscalation.AddEmployee(pItem->data(0, Qt::UserRole).toInt());
      }
   }

   m_cEscalation.SetEscalationStep(m_pqsbEscalationStep->value());
   m_cEscalation.SetViolationOfLimit(m_pqsbLimit->value());
   m_cEscalation.CommitObject();
}

/** +-=---------------------------------------------------------Mi 10. Okt 13:36:15 2012----------*
 * @method  CwmsEscalationEditorDlg::OKClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Okt 13:36:15 2012----------*/
void CwmsEscalationEditorDlg::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Mo 22. Okt 14:52:25 2012----------*
 * @method  CwmsEscalationEditorDlg::Edit                    // public, static                    *
 * @return  bool                                             //                                   *
 * @param   CwmsEscalation p_cEscalation                     //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 22. Okt 14:52:25 2012----------*/
bool CwmsEscalationEditorDlg::Edit(CwmsEscalation p_cEscalation, bool p_bNew, QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsEscalationEditorDlg cEditor(p_pqwParent);
   cEditor.FillDialog(p_cEscalation, p_bNew);

   if (cEditor.exec() == QDialog::Accepted)
   {
      bRet = true;
   }
   else if (p_bNew)
   {
      p_cEscalation.SetDeleted();
      p_cEscalation.CommitObject();
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 30. Dez 14:24:35 2012----------*
 * @method  CwmsEscalationObjectEditorDescriptor::GetClassKeyname // public                       *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:24:35 2012----------*/
QString CwmsEscalationObjectEditorDescriptor::GetClassKeyname()
{

   return "Workflow_Escalation";
}

/** +-=---------------------------------------------------------So 30. Dez 14:24:40 2012----------*
 * @method  CwmsEscalationObjectEditorDescriptor::DisplayEditor // protected                      *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   EwmsGuiDisplayMode p_eDisplayMode                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 30. Dez 14:24:40 2012----------*/
bool CwmsEscalationObjectEditorDescriptor::DisplayEditor(CdmObject* p_pCdmObject,
                                                         EwmsGuiDisplayMode p_eDisplayMode,
                                                         QWidget* p_pqwParent)
{
   bool bRet = false;
   CwmsEscalation cEscalation(p_pCdmObject);

   if (p_eDisplayMode == eWmsGuiDisplayModeNew)
   {
      bRet = CwmsEscalationEditorDlg::Edit(cEscalation, true, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeWrite)
   {
      bRet = CwmsEscalationEditorDlg::Edit(cEscalation, false, p_pqwParent);
   }
   else if (p_eDisplayMode == eWmsGuiDisplayModeRead)
   {
      bRet = CwmsEscalationEditorDlg::Edit(cEscalation, false, p_pqwParent);
   }

   return bRet;
}