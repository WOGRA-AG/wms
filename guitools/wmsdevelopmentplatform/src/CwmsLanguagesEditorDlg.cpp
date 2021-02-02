/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsLanguagesEditorDlg.cpp
 ** Started Implementation: 2012/08/18
 ** Description:
 **
 ** This class implements the editor for languages at the db
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMap>
#include <QInputDialog>
#include <QList>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmScheme.h"

// own Includes
#include "CwmsLanguagesEditorDlg.h"

/** +-=---------------------------------------------------------Sa 18. Aug 11:11:59 2012----------*
 * @method  CwmsLanguagesEditorDlg::CwmsLanguagesEditorDlg   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 18. Aug 11:11:59 2012----------*/
CwmsLanguagesEditorDlg::CwmsLanguagesEditorDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      m_rpCdmDatabase = pCdmManager->GetCurrentScheme();
   }
}

/** +-=---------------------------------------------------------Sa 18. Aug 11:12:14 2012----------*
 * @method  CwmsLanguagesEditorDlg::~CwmsLanguagesEditorDlg  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsLanguagesEditorDlg                                        *
 *----------------last changed: --------------------------------Sa 18. Aug 11:12:14 2012----------*/
CwmsLanguagesEditorDlg::~CwmsLanguagesEditorDlg()
{
}

/** +-=---------------------------------------------------------Sa 18. Aug 11:12:27 2012----------*
 * @method  CwmsLanguagesEditorDlg::FillDialog               // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 18. Aug 11:12:27 2012----------*/
void CwmsLanguagesEditorDlg::FillDialog()
{
   if (CHKPTR(m_rpCdmDatabase))
   {
      m_pqlwLanguages->clear();
      QMap<int, QString> qmLanguages = m_rpCdmDatabase->GetLanguageMap();

      QMap<int, QString>::iterator qmIt = qmLanguages.begin();
      QMap<int, QString>::iterator qmItEnd = qmLanguages.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         QListWidgetItem* pqlwiItem = new QListWidgetItem(m_pqlwLanguages);
         pqlwiItem->setText(qmIt.value());
         pqlwiItem->setData(Qt::UserRole, QVariant(qmIt.key()));
      }
   }
}

/** +-=---------------------------------------------------------Sa 18. Aug 11:45:32 2012----------*
 * @method  CwmsLanguagesEditorDlg::AddClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 18. Aug 11:45:32 2012----------*/
void CwmsLanguagesEditorDlg::AddClickedSlot()
{
   if (CHKPTR(m_rpCdmDatabase))
   {
      QString qstrLanguage = QInputDialog::getText(this, "Neue Sprache anlegen", "Bitte geben Sie den Namen der Sprache ein.");

      if (!qstrLanguage.isEmpty())
      {
         m_rpCdmDatabase->AddLanguage(qstrLanguage);
         FillDialog();
      }
   }
}

/** +-=---------------------------------------------------------Sa 18. Aug 11:45:49 2012----------*
 * @method  CwmsLanguagesEditorDlg::RemoveClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 18. Aug 11:45:49 2012----------*/
void CwmsLanguagesEditorDlg::RemoveClickedSlot()
{
   if (CHKPTR(m_rpCdmDatabase))
   {
      QList<QListWidgetItem*> qlSelectedItems = m_pqlwLanguages->selectedItems();

      if (qlSelectedItems.count() > 0)
      {
         if (CdmMessageManager::Ask(tr("Sprache wirklich löschen"), tr("Wollen Sie die Sprache wirklich löschen?\nAlle Übersetzungen gehen verloren.")))
         {
            for (int iCounter = 0; iCounter < qlSelectedItems.count(); ++iCounter)
            {
               int iId = qlSelectedItems[iCounter]->data(Qt::UserRole).toInt();
               m_rpCdmDatabase->RemoveLanguage(iId);
               FillDialog();
            }
         }
      }
   }
}
