/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsGroupEditorDlg.cpp
 ** Started Implementation: 2012/08/17
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
#include "CdmClassGroup.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

// own Includes
#include "CwmsUniversalRightsManager.h"
#include "CwmsTranslationEditorDlg.h"
#include "CwmsGroupEditorDlg.h"


/** +-=---------------------------------------------------------Fr 17. Aug 14:09:25 2012----------*
 * @method  CwmsGroupEditorDlg::CwmsGroupEditorDlg           // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:09:25 2012----------*/
CwmsGroupEditorDlg::CwmsGroupEditorDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCdmGroup(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:10:01 2012----------*
 * @method  CwmsGroupEditorDlg::~CwmsGroupEditorDlg          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsGroupEditorDlg                                            *
 *----------------last changed: --------------------------------Fr 17. Aug 14:10:01 2012----------*/
CwmsGroupEditorDlg::~CwmsGroupEditorDlg()
{
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:36:16 2012----------*
 * @method  CwmsGroupEditorDlg::FillDialog                   // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClassGroup* p_pCdmGroup                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 15:36:16 2012----------*/
void CwmsGroupEditorDlg::FillDialog(CdmClassGroup* p_pCdmGroup)
{
   m_rpCdmGroup = p_pCdmGroup;

   if (CHKPTR(m_rpCdmGroup))
   {
      m_pqleName->setText(m_rpCdmGroup->GetName());
   }

   FillTranslations();
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:21:33 2012----------*
 * @method  CwmsGroupEditorDlg::Validate                     // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:21:33 2012----------*/
bool CwmsGroupEditorDlg::Validate()
{
   bool bRet = false;
   QString qstrName = m_pqleName->text();

   if (!qstrName.isEmpty())
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:22:04 2012----------*
 * @method  CwmsGroupEditorDlg::SaveData                     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:22:04 2012----------*/
void CwmsGroupEditorDlg::SaveData()
{
   m_rpCdmGroup->SetName(m_pqleName->text());
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:21:22 2012----------*
 * @method  CwmsGroupEditorDlg::OKClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:21:22 2012----------*/
void CwmsGroupEditorDlg::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:45:05 2012----------*
 * @method  CwmsGroupEditorDlg::AddTranslationClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:45:05 2012----------*/
void CwmsGroupEditorDlg::AddTranslationClickedSlot()
{
   CwmsTranslationEditorDlg* pEditor = new CwmsTranslationEditorDlg(this);
   pEditor->FillDialog("", "");

   if (pEditor->exec() == QDialog::Accepted)
   {
      m_rpCdmGroup->SetTranslation(pEditor->GetLanguage(),
         pEditor->GetTranslation());
   }

   DELPTR(pEditor);
   FillTranslations();
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:45:16 2012----------*
 * @method  CwmsGroupEditorDlg::EditTranslationClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:45:16 2012----------*/
void CwmsGroupEditorDlg::EditTranslationClickedSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedTranslationItem();

   if (pqItem)
   {
      QString iId = pqItem->data(0, Qt::UserRole).toString();

      CwmsTranslationEditorDlg* pEditor = new CwmsTranslationEditorDlg(this);
      pEditor->FillDialog(iId, pqItem->text(1));
      if (pEditor->exec() == QDialog::Accepted)
      {
         m_rpCdmGroup->SetTranslation(iId, pEditor->GetTranslation());
      }

      DELPTR(pEditor);
      FillTranslations();
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 14:45:26 2012----------*
 * @method  CwmsGroupEditorDlg::RemoveTranslationClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 14:45:26 2012----------*/
void CwmsGroupEditorDlg::RemoveTranslationClickedSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedTranslationItem();

   if (pqItem)
   {
      QString iId = pqItem->data(0, Qt::UserRole).toString();
      m_rpCdmGroup->DeleteTranslation(iId);
      DELPTR(pqItem);
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:35:12 2012----------*
 * @method  CwmsGroupEditorDlg::FillTranslations             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 15:35:12 2012----------*/
void CwmsGroupEditorDlg::FillTranslations()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if ( CHKPTR(pCdmDatabase) && m_rpCdmGroup)
      {
         m_pqtwTranslations->clear();
         QMap<QString, QString> qmTranslations = m_rpCdmGroup->GetTranslations();

         if (qmTranslations.count() > 0)
         {
            QMap<QString, QString>::iterator qmIt = qmTranslations.begin();
            QMap<QString, QString>::iterator qmItEnd = qmTranslations.end();


            for (; qmIt != qmItEnd; ++qmIt)
            {
               QString qstrValue = qmIt.value();

               QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwTranslations);
               pqItem->setText(0, qmIt.key());
               pqItem->setText(1, qstrValue);
               pqItem->setData(0, Qt::UserRole, QVariant(qmIt.key()));
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 15:21:47 2012----------*
 * @method  CwmsGroupEditorDlg::GetSelectedTranslationItem   // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 15:21:47 2012----------*/
QTreeWidgetItem* CwmsGroupEditorDlg::GetSelectedTranslationItem()
{
   QTreeWidgetItem* pItem = nullptr;
   QList<QTreeWidgetItem*> qlItems = m_pqtwTranslations->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Mi 22. Aug 16:46:28 2012----------*
 * @method  CwmsGroupEditorDlg::RightsClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 22. Aug 16:46:28 2012----------*/
void CwmsGroupEditorDlg::RightsClickedSlot()
{
   if (m_rpCdmGroup)
   {
      CdmRights* pCdmRights = &m_rpCdmGroup->GetRights();
      CwmsUniversalRightsManagerIf* pCwmsRighstManager = new CwmsUniversalRightsManagerIf(pCdmRights, this);
      pCwmsRighstManager->exec();
      DELPTR(pCwmsRighstManager);
   }
}

