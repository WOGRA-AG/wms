/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsTranslationEditorDlg.cpp
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
#include <QVariant>
#include <QMap>
#include <qmessagebox.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwmsTranslationEditorDlg.h"

/** +-=---------------------------------------------------------Fr 17. Aug 15:27:49 2012----------*
 * @method  CwmsTranslationEditorDlg::CwmsTranslationEditorDlg // public                          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:27:49 2012----------*/
CwmsTranslationEditorDlg::CwmsTranslationEditorDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:28:17 2012----------*
 * @method  CwmsTranslationEditorDlg::~CwmsTranslationEditorDlg // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsTranslationEditorDlg                                      *
 *----------------last changed: --------------------------------Fr 17. Aug 15:28:17 2012----------*/
CwmsTranslationEditorDlg::~CwmsTranslationEditorDlg()
{
}

/** +-=---------------------------------------------------------Mo 20. Aug 13:19:19 2012----------*
 * @method  CwmsTranslationEditorDlg::FillDialog             // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 13:19:19 2012----------*/
void CwmsTranslationEditorDlg::FillDialog()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         QMap<int, QString> qmLanguages = pCdmDatabase->GetLanguageMap();

         QMap<int, QString>::iterator qmIt = qmLanguages.begin();
         QMap<int, QString>::iterator qmItEnd = qmLanguages.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            m_pqcbLanguages->addItem(qmIt.value(), qmIt.value());
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:32:09 2012----------*
 * @method  CwmsTranslationEditorDlg::FillDialog             // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iLanguageId                                //                                   *
 * @param   QString p_qstrTranslation                        //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:32:09 2012----------*/
void CwmsTranslationEditorDlg::FillDialog(QString p_iLanguageId,
                                          QString p_qstrTranslation,
                                          QString p_qstrComment)
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      FillDialog();

      if (!p_iLanguageId.isEmpty())
      {
         m_pqcbLanguages->setCurrentIndex(m_pqcbLanguages->findData(p_iLanguageId));
      }

      m_pqleTranslation->setText(p_qstrTranslation);
      m_pqteComment->setPlainText(p_qstrComment);
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:32:04 2012----------*
 * @method  CwmsTranslationEditorDlg::FillDialog             // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iLanguageId                                //                                   *
 * @param   QString p_qstrTranslation                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:32:04 2012----------*/
void CwmsTranslationEditorDlg::FillDialog(QString p_iLanguageId, QString p_qstrTranslation)
{
   m_pqgbComment->hide();
   FillDialog(p_iLanguageId, p_qstrTranslation, "");
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:31:17 2012----------*
 * @method  CwmsTranslationEditorDlg::Validate               // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:31:17 2012----------*/
bool CwmsTranslationEditorDlg::Validate()
{
   bool bRet = false;

   if (!m_pqleTranslation->text().isEmpty())
   {
      if (m_pqgbComment->isVisible())
      {
         if (!m_pqteComment->toPlainText().isEmpty())
         {
            bRet = true;
         }
         else
         {
            QMessageBox::critical(this, tr("Pflichtfeld nicht gefÃ¼llt"),tr("Das Kommentar fehlt."));
         }
      }
      else
      {
         bRet = true;
      }
   }
   else
   {
      QMessageBox::critical(this, tr("Pflichtfeld nicht gefÃ¼llt"),tr("Die Ãœbersetzung fehlt"));
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:31:05 2012----------*
 * @method  CwmsTranslationEditorDlg::OKClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:31:05 2012----------*/
void CwmsTranslationEditorDlg::OKClickedSlot()
{
   if (Validate())
   {
      accept();
   }
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:56:51 2012----------*
 * @method  CwmsTranslationEditorDlg::GetLanguageId          // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:56:51 2012----------*/
QString CwmsTranslationEditorDlg::GetLanguage()
{
   return m_pqcbLanguages->itemData(m_pqcbLanguages->currentIndex()).toString();
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:57:01 2012----------*
 * @method  CwmsTranslationEditorDlg::GetComment             // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:57:01 2012----------*/
QString CwmsTranslationEditorDlg::GetComment()
{
   return m_pqteComment->toPlainText();
}

/** +-=---------------------------------------------------------Fr 17. Aug 15:57:11 2012----------*
 * @method  CwmsTranslationEditorDlg::GetTranslation         // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 17. Aug 15:57:11 2012----------*/
QString CwmsTranslationEditorDlg::GetTranslation()
{
   return m_pqleTranslation->text();
}
