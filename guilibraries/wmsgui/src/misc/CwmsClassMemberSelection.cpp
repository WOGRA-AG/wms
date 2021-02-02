/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsClassMemberSelection.cpp
 ** Started Implementation: 2012/09/10
 ** Description:
 **
 ** implements the selector for member vriables and functions
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsClassMemberSelection.h"

/** +-=---------------------------------------------------------Mo 10. Sep 13:43:45 2012----------*
 * @method  CwmsClassMemberSelection::CwmsClassMemberSelection // public                          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 13:43:45 2012----------*/
CwmsClassMemberSelection::CwmsClassMemberSelection(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 14. Dez 11:08:21 2012----------*
 * @method  CwmsClassMemberSelection::FillDialog             // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<QString, CdmClassMethod*>& p_rqmMethods     //                                   *
 * @param   bool p_bOnlyObjectMethods = false                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 11:08:21 2012----------*/
void CwmsClassMemberSelection::FillDialog(QMap<QString,
                                          CdmClassMethod*>& p_rqmMethods,
                                          bool p_bOnlyObjectMethods)
{
    Q_UNUSED(p_bOnlyObjectMethods);
   QMap<QString, CdmClassMethod*>::iterator qmIt = p_rqmMethods.begin();
   QMap<QString, CdmClassMethod*>::iterator qmItEnd = p_rqmMethods.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassMethod* pMethod = qmIt.value();

      if (CHKPTR(pMethod))
      {
        QListWidgetItem* pItem = new QListWidgetItem(m_pqlwMembers);
        pItem->setText(pMethod->GetMethodName());
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 13:48:51 2012----------*
 * @method  CwmsClassMemberSelection::FillDialog             // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long,CdmMember*>& p_rqmMembers              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 13:48:51 2012----------*/
void CwmsClassMemberSelection::FillDialog(QMap<long,CdmMember*>& p_rqmMembers)
{
   QMap<long,CdmMember*>::iterator qmIt = p_rqmMembers.begin();
   QMap<long,CdmMember*>::iterator qmItEnd = p_rqmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (CHKPTR(pCdmMember))
      {
         QListWidgetItem* pItem = new QListWidgetItem(m_pqlwMembers);
         pItem->setText(pCdmMember->GetKeyname());
      }
   }
}

/** +-=---------------------------------------------------------Mo 10. Sep 13:50:29 2012----------*
 * @method  CwmsClassMemberSelection::GetSelectedValues      // public                            *
 * @return  QStringList                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 13:50:29 2012----------*/
QStringList CwmsClassMemberSelection::GetSelectedValues()
{
   QStringList qstrlSelection;

   QList<QListWidgetItem*> qlSelection = m_pqlwMembers->selectedItems();

   for (int iCounter = 0; iCounter < qlSelection.count(); ++iCounter)
   {
      qstrlSelection.append(qlSelection[iCounter]->text());
   }

   return qstrlSelection;
}

void CwmsClassMemberSelection::MemberDoubleClickedSlot(QModelIndex p_qIndex)
{
   QListWidgetItem* pItem = m_pqlwMembers->item(p_qIndex.row());

   if (pItem)
   {
      pItem->setSelected(true);
      accept();
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 10:54:25 2013----------*
 * @method  CwmsClassMemberSelection::GetFunctionSelection   // public, static                    *
 * @return  QStringList                                      //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @param   bool p_bOnlyObjectMethods                        //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 10:54:25 2013----------*/
QStringList CwmsClassMemberSelection::GetFunctionSelection(const CdmClass* p_pCdmClass,
                                                           bool p_bOnlyObjectMethods,
                                                           QWidget* p_pqwParent)
{
   QStringList qstrlSelection;

   if (CHKPTR(p_pCdmClass))
   {
      CwmsClassMemberSelection* pSelector = new CwmsClassMemberSelection(p_pqwParent);

      QMap<QString, CdmClassMethod*> qmPublicInterface = (const_cast<CdmClass*>(p_pCdmClass))->GetAllMethods();
      pSelector->FillDialog(qmPublicInterface, p_bOnlyObjectMethods);
      pSelector->setWindowTitle(tr("Funktionen wählen"));

      if (pSelector->exec() == QDialog::Accepted)
      {
         qstrlSelection = pSelector->GetSelectedValues();
      }
   }

   return qstrlSelection;
}

/** +-=---------------------------------------------------------Mo 11. Feb 10:55:32 2013----------*
 * @method  CwmsClassMemberSelection::GetMemberSelection     // public, static                    *
 * @return  QStringList                                      //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 10:55:32 2013----------*/
QStringList CwmsClassMemberSelection::GetMemberSelection(const CdmClass* p_pCdmClass,
                                                         QWidget* p_pqwParent)
{
   QStringList qstrlSelection;

   if (CHKPTR(p_pCdmClass))
   {
      CwmsClassMemberSelection* pSelector = new CwmsClassMemberSelection(p_pqwParent);
      QMap<long,CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);
      pSelector->FillDialog(qmMembers);

      if (pSelector->exec() == QDialog::Accepted)
      {
         qstrlSelection = pSelector->GetSelectedValues();
      }
   }
   
   return qstrlSelection;
}
