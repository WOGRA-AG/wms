/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportDlg.cpp
 ** Started Implementation: 2008/10/25
 ** Description:
 ** 
 ** Implements the Import Dialog for defining and executing the import.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QInputDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextCodec>

// WMS Manager
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsImExportManager.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportDlg.h"
#include "CwmsImportColumnDlg.h"
#include "CwmsImport.h"

/** +-=---------------------------------------------------------Mi 29. Okt 18:20:52 2008----------*
 * @method  CwmsImportDlg::CwmsImportDlg                     // public                            *
 * @return                                                   //                                   *
 * @param   CwmsImportSettings* p_pImportSettings            //                                   *
 * @param   CwmsImport* p_pCwmsImport                        //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mi 29. Okt 18:20:52 2008----------*/
CwmsImportDlg::CwmsImportDlg(CwmsImportSettings* p_pImportSettings,
                             CwmsImport* p_pCwmsImport,
                             QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCwmsImportSettings(p_pImportSettings),
  m_rpCwmsImport(p_pCwmsImport)
{
   setupUi(this);
   FilDialogWithSettings();
}

/** +-=---------------------------------------------------------Sa 25. Okt 11:53:02 2008----------*
 * @method  CwmsImportDlg::~CwmsImportDlg                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportDlg                                                 *
 *----------------last changed: --------------------------------Sa 25. Okt 11:53:02 2008----------*/
CwmsImportDlg::~CwmsImportDlg()
{
}

/** +-=---------------------------------------------------------So 26. Okt 11:18:31 2008----------*
 * @method  CwmsImportDlg::FillSettingsData                  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 11:18:31 2008----------*/
void CwmsImportDlg::FillSettingsData()
{
   if (CHKPTR(m_rpCwmsImportSettings))
   {
      m_rpCwmsImportSettings->SetFilename(m_pqleFilename->text());

      if (m_pqrbUpdate->isChecked())
      {
         m_rpCwmsImportSettings->SetImportMode(eWmsImportModeUpdate);
      }
      else if (m_pqrbAppend->isChecked())
      {
         m_rpCwmsImportSettings->SetImportMode(eWmsImportModeAppend);
      }
      else if (m_pqrbOverwrite->isChecked())
      {
         m_rpCwmsImportSettings->SetImportMode(eWmsImportModeOverwrite);
      }

      if (m_pqrbCsvFile->isChecked())
      {
         m_rpCwmsImportSettings->SetImportType(eWmsImportTypeCsv);
      }
      else if (m_pqrbTextFile->isChecked())
      {
         m_rpCwmsImportSettings->SetImportType(eWmsImportTypeText);
      }

      m_rpCwmsImportSettings->SetCsvSeperator(m_pqleCsvSeperator->text());
      m_rpCwmsImportSettings->SetStringEnclosing(m_pqleStringSeperator->text());
      m_rpCwmsImportSettings->SetIgnoreFirstLine(m_pqchbIgnoreFirstLine->isChecked());
      m_rpCwmsImportSettings->SetIgnoreLastLine(m_pqchbIgnoreLastLine->isChecked());
      m_rpCwmsImportSettings->SetEncoding(m_pqcbEncoding->currentText());
      m_rpCwmsImportSettings->SetPreprocessorCall(m_pqlePreProcessorFucntion->text());
      m_rpCwmsImportSettings->SetPostprocessorCall(m_pqlePostprocessorFunction->text());
   }
}

/** +-=---------------------------------------------------------So 26. Okt 11:44:07 2008----------*
 * @method  CwmsImportDlg::FilDialogWithSettings             // private                           *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog with the settings.                                       *
 *----------------last changed: --------------------------------So 26. Okt 11:44:07 2008----------*/
void CwmsImportDlg::FilDialogWithSettings()
{
   m_pqleFilename->setText(m_rpCwmsImportSettings->GetFilename());
   m_lClassId = m_rpCwmsImportSettings->GetClassId();

   if (!m_rpCwmsImportSettings->GetCsvSeperator().isEmpty())
   {
      m_pqleCsvSeperator->setText(m_rpCwmsImportSettings->GetCsvSeperator());
   }
   
   if (!m_rpCwmsImportSettings->GetStringEnclosing().isEmpty())
   {
      m_pqleStringSeperator->setText(m_rpCwmsImportSettings->GetStringEnclosing());

   }
   
   switch(m_rpCwmsImportSettings->GetImportType())
   {
   case eWmsImportTypeCsv:
      m_pqrbCsvFile->setChecked(true);
      break;
   case eWmsImportTypeText:
      m_pqrbTextFile->setChecked(true);
      break;
   }

   switch (m_rpCwmsImportSettings->GetImportMode())
   {
   case eWmsImportModeAppend:
      m_pqrbAppend->setChecked(true);
      break;
   case eWmsImportModeOverwrite:
      m_pqrbOverwrite->setChecked(true);
      break;
   case eWmsImportModeUpdate:
      m_pqrbUpdate->setChecked(true);
      break;
   }

   m_pqchbIgnoreFirstLine->setChecked(m_rpCwmsImportSettings->GetIgnoreFirstLine());
   m_pqchbIgnoreLastLine->setChecked(m_rpCwmsImportSettings->GetIgnoreLastLine());


   QList<QByteArray> qlCodecs = QTextCodec::availableCodecs();

   for (int i = 0; i < qlCodecs.count(); ++i)
   {
       m_pqcbEncoding->addItem(qlCodecs[i]);
   }

   if (m_rpCwmsImportSettings->GetEncoding().isEmpty())
   {
     QTextCodec* qtcDefault = QTextCodec::codecForLocale();
     if (CHKPTR(qtcDefault))
     {
         m_pqcbEncoding->setCurrentText(qtcDefault->name());
     }
   }
   else
   {
       m_pqcbEncoding->setCurrentText(m_rpCwmsImportSettings->GetEncoding());
   }

   m_pqlePreProcessorFucntion->setText(m_rpCwmsImportSettings->GetPreprocessorCall());
   m_pqlePostprocessorFunction->setText(m_rpCwmsImportSettings->GetPostprocessorCall());
}

/** +-=---------------------------------------------------------So 26. Okt 12:13:28 2008----------*
 * @method  CwmsImportDlg::FillListView                      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 12:13:28 2008----------*/
void CwmsImportDlg::FillListView()
{
   QList<CwmsImportSettingsColumn*> qlColumns;
   m_rpCwmsImportSettings->GetColumns(qlColumns);
   m_pqlvImportColumns->clear();

   for (int iPos = 0; iPos < qlColumns.count(); ++iPos)
   {
      CwmsImportSettingsColumn* pCwmsImportSettings = qlColumns[iPos];

      if (pCwmsImportSettings)
      {
         QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvImportColumns);
         QString qstrMember = pCwmsImportSettings->GetMember();

         if (qstrMember.isEmpty())
         {
            pqlviItem->setText(0, tr("Nicht relevant"));
            pqlviItem->setText(1, tr("Ja"));
         }
         else
         {
            pqlviItem->setText(0, pCwmsImportSettings->GetMember());
            pqlviItem->setText(1, tr("Nein"));
         }
         
         pqlviItem->setText(2, QString::number(pCwmsImportSettings->GetStartPos()));
         pqlviItem->setText(3, QString::number(pCwmsImportSettings->GetEndPos()));

         if (pCwmsImportSettings->IsUpdateCriteria())
         {
            pqlviItem->setText(4, tr("Ja"));
         }
         else
         {
            pqlviItem->setText(4, tr("Nein"));
         }
      }
   }
}

/** +-=---------------------------------------------------------So 26. Okt 10:49:09 2008----------*
 * @method  CwmsImportDlg::ChooseSourceFileClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:49:09 2008----------*/
void CwmsImportDlg::ChooseSourceFileClickedSlot()
{
   QString qstrFilter;

   if (m_pqrbCsvFile->isChecked())
   {
      qstrFilter = "*.csv";
   }
   else
   {
      qstrFilter = "*.txt";
   }

   QString qstrFilename = QFileDialog::getOpenFileName(this, tr("Bitte Quelldatei auswählen"), "", qstrFilter);

   QFileInfo qfInfo(qstrFilename);

   if (qfInfo.completeSuffix().isEmpty())
   {
      if (m_pqrbCsvFile->isChecked())
      {
         qstrFilename += ".csv";
      }
      else
      {
         qstrFilename += ".txt";
      }
   }

   m_pqleFilename->setText(qstrFilename);
}

/** +-=---------------------------------------------------------So 26. Okt 10:49:36 2008----------*
 * @method  CwmsImportDlg::AddColumnClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:49:36 2008----------*/
void CwmsImportDlg::AddColumnClickedSlot()
{
   if (m_rpCwmsImport)
   {
      CwmsImportColumnDlg* pCwmsImportColumnDlg = new CwmsImportColumnDlg(this);
      CdmObjectContainer* pContainer = m_rpCwmsImportSettings->GetContainer();

      if (CHKPTR(pContainer))
      {
         const CdmClass* pCdmClass = pContainer->GetClass();

         if (CHKPTR(pCdmClass))
         {
            pCwmsImportColumnDlg->FillMemberListView(pCdmClass, m_rpCwmsImport);
            
            if (pCwmsImportColumnDlg->exec() == QDialog::Accepted)
            {
               CwmsImportSettingsColumn* pCwmsColumn = new CwmsImportSettingsColumn("", 0, 0, false);
               pCwmsImportColumnDlg->GetColumnSetttings(pCwmsColumn);
               m_rpCwmsImportSettings->AddColumn(pCwmsColumn);
               FillListView();
            }

            DELPTR(pCwmsImportColumnDlg);
         }
      }
   }
}

/** +-=---------------------------------------------------------So 26. Okt 10:50:01 2008----------*
 * @method  CwmsImportDlg::RemoveColumnClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:50:01 2008----------*/
void CwmsImportDlg::RemoveColumnClickedSlot()
{
   int iPos = GetSelectedItemPos();

   if (iPos >= 0)
   {
      m_rpCwmsImportSettings->RemoveColumn(iPos);
      FillListView();
   }
   else
   {
      MSG_CRIT("Entfernung der Spalte nicht möglich",
               "Um eine Spalte zu entfernen muss diese markiert werden.");
   }
}

/** +-=---------------------------------------------------------So 26. Okt 12:37:42 2008----------*
 * @method  CwmsImportDlg::MoveUpClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 12:37:42 2008----------*/
void CwmsImportDlg::MoveUpClickedSlot()
{
   int iPos = GetSelectedItemPos();

   if (iPos >= 0)
   {
      m_rpCwmsImportSettings->MoveUp(iPos);
      FillListView();
   }
   else
   {
      MSG_CRIT("Verschieben der Spalte nicht möglich",
               "Um eine Spalte zu verschieben muss diese markiert werden.");
   }
}

/** +-=---------------------------------------------------------So 26. Okt 12:37:56 2008----------*
 * @method  CwmsImportDlg::MoveDownClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 12:37:56 2008----------*/
void CwmsImportDlg::MoveDownClickedSlot()
{
   int iPos = GetSelectedItemPos();

   if (iPos >= 0)
   {
      m_rpCwmsImportSettings->MoveDown(iPos);
      FillListView();
   }
   else
   {
       MSG_CRIT("Verschieben der Spalte nicht möglich",
                "Um eine Spalte zu verschieben muss diese markiert werden.");
   }
}

/** +-=---------------------------------------------------------Mi 29. Okt 19:53:44 2008----------*
 * @method  CwmsImportDlg::GetSelectedItemPos                // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 29. Okt 19:53:44 2008----------*/
int CwmsImportDlg::GetSelectedItemPos()
{
   int iRet = -1;
   int iRetTemp = 0;
   QTreeWidgetItemIterator it(m_pqlvImportColumns);
   
   while (*it) 
   {
      if ((*it)->isSelected())
      {
         iRet = iRetTemp;
         break;
      }
         
      ++iRetTemp;
      ++it;
   }

   return iRet;
}



/** +-=---------------------------------------------------------So 26. Okt 10:50:16 2008----------*
 * @method  CwmsImportDlg::SaveClickedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:50:16 2008----------*/
void CwmsImportDlg::SaveClickedSlot()
{
   FillSettingsData();
   QString qstrName = m_rpCwmsImportSettings->GetSettingsName();
   qstrName = QInputDialog::getText(this, 
                                    tr("Bitte Namen eingeben"), 
                                    tr("Bitte geben Sie den Namen zum speichern ein."), 
                                    QLineEdit::Normal, 
                                    qstrName);

   if (!qstrName.isEmpty())
   {
      m_rpCwmsImportSettings->SaveSettings(qstrName);
      MSG_INFO(("Speichern erfolgreich"), ("Die Konfiguration wurde erfolgreich gespeichert."));
   }
}

/** +-=---------------------------------------------------------So 26. Okt 10:50:36 2008----------*
 * @method  CwmsImportDlg::LoadClickedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:50:36 2008----------*/
void CwmsImportDlg::LoadClickedSlot()
{
   CwmsImExportManager cManager;
   QMap<QString, QString> qmConfigs = cManager.GetImportConfiguration(m_lClassId);
   QStringList qstrlKeys = qmConfigs.keys();
   bool bOk;

   QString qstrKey = QInputDialog::getItem(this, 
                                           tr("Bitte wählen Sie die zuladenden Konfiguration aus."),
                                           tr("Konfiguration:"), 
                                           qstrlKeys, 
                                           0, 
                                           false, 
                                           &bOk);

   if (!qstrKey.isEmpty() && bOk)
   {
      m_rpCwmsImportSettings->LoadSettings(qstrKey, qmConfigs[qstrKey]);
      FilDialogWithSettings();
      FillListView();
   }
}

/** +-=---------------------------------------------------------So 26. Okt 10:51:11 2008----------*
 * @method  CwmsImportDlg::CancelClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:51:11 2008----------*/
void CwmsImportDlg::CancelClickedSlot()
{
   reject();
}

/** +-=---------------------------------------------------------So 26. Okt 10:51:23 2008----------*
 * @method  CwmsImportDlg::OKClickedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 10:51:23 2008----------*/
void CwmsImportDlg::OKClickedSlot()
{
   if (ValidateSettings())
   {
      FillSettingsData();
      accept();
   }
}

/** +-=---------------------------------------------------------Di 4. Nov 18:00:42 2008-----------*
 * @method  CwmsImportDlg::ValidateSettings                  // private                           *
 * @return  bool                                             //                                   *
 * @comment This method validates the methods.                                                    *
 *----------------last changed: --------------------------------Di 4. Nov 18:00:42 2008-----------*/
bool CwmsImportDlg::ValidateSettings()
{
   bool bRet = true;

   if (m_pqrbCsvFile->isChecked())
   {
      if (m_pqleCsvSeperator->text().isEmpty() || m_pqleStringSeperator->text().isEmpty())
      {
         bRet = false;
         MSG_CRIT("CSV Zeicheneinstellungen nicht vollständig",
                  "Der CSV Trenner oder das Zeichenkettentrennzeichen ist nicht festgelegt.");
      }
   }
   else
   {
      if (!m_rpCwmsImportSettings->ColumnsValidForTextImport())
      {
         bRet = false;
         MSG_CRIT("Spaltendefinition nicht vollständig",
                  "Es muss für jede Spalte eine Start und eine Endposition angegeben werden.");
      }
   }

   if (m_pqrbUpdate->isChecked())
   {
      if (!m_rpCwmsImportSettings->HasNonUpdateRelevantColumn() || 
          !m_rpCwmsImportSettings->HasUpdateRelevantColumn())
      {
         bRet = false;
         MSG_CRIT("Aktualisierungsimport mit diesen Spalteneinstellungen nicht möglich",
                  "Es muss mindestens eine Spalte Aktualisierungsrelevant sein und\n mindestens eine Spalte nicht Aktualisierungsrelevant.");
      }
   }

   QList<CwmsImportSettingsColumn*> qlColumns;
   m_rpCwmsImportSettings->GetColumns(qlColumns);
   
   if (qlColumns.count() == 0)
   {
      bRet = false;
      MSG_CRIT("Spaltenpflege unvollständig",
               "Es muss mindestens eine Spalte importiert werden.");
   }

   if (m_pqleFilename->text().isEmpty())
   {
      MSG_CRIT("Dateiname für Import fehlt",
               "Es muss der Quelldateiname angegeben werden.");
   }

   return bRet;
}
