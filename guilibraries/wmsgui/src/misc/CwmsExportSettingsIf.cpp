/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsExportSettingsIf.cpp
 ** Started Implementation: 2008/04/13
 ** Description:
 ** 
 ** The Dialog for the export settings
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextCodec>
#include <QList>

// WMS Includes
#include "CdmMessageManager.h"
#include  "CdmLogging.h"
#include  "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include  "CdmObjectContainer.h"
#include  "CdmClass.h"
#include  "CdmMember.h"

// Own Includes
#include "CwmsSearchWidgetIf.h"
#include "CwmsImExportManager.h"
#include "CwmsSearchDlg.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsExportFileWriter.h"
#include "CwmsExportSettingsIf.h"


/** +-=---------------------------------------------------------Mi 5. Sep 10:05:11 2012-----------*
 * @method  CwmsExportSettingsIf::CwmsExportSettingsIf       // public                            *
 * @return                                                   //                                   *
 * @param   CwmsExportSettings& p_rCwmsExportSettings        //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 10:05:11 2012-----------*/
CwmsExportSettingsIf::CwmsExportSettingsIf(CwmsExportSettings& p_rCwmsExportSettings,
                                           QWidget* parent)
: QDialog(parent),
  m_rCwmsExportSettings(p_rCwmsExportSettings)

{
	setupUi(this);
}

/** +-=---------------------------------------------------------So 13. Apr 11:58:32 2008----------*
 * @method  CwmsExportSettingsIf::~CwmsExportSettingsIf      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsExportSettingsIf                                          *
 *----------------last changed: --------------------------------So 13. Apr 11:58:32 2008----------*/
CwmsExportSettingsIf::~CwmsExportSettingsIf()
{
}

/** +-=---------------------------------------------------------Mo 21. Apr 17:27:49 2008----------*
 * @method  CwmsExportSettingsIf::FillDialog                 // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 17:27:49 2008----------*/
void CwmsExportSettingsIf::FillDialog()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmObjectContainer* pContainerExport = pCdmManager->GetObjectContainer(m_rCwmsExportSettings.GetSchemeId(), 
                                                                       m_rCwmsExportSettings.GetContainerId());


      if (CHKPTR(pContainerExport))
      {
         const CdmClass* pCdmClass = pContainerExport->GetClass();

         if (CHKPTR(pCdmClass))
         {
            m_lClassId = pCdmClass->GetId();
            FillMemberListView(pCdmClass);
         }
      }

      QList<QByteArray> qlCodecs = QTextCodec::availableCodecs();

      for (int i = 0; i < qlCodecs.count(); ++i)
      {
          m_pqcbEncoding->addItem(qlCodecs[i]);
      }

      //m_pqcbEncoding->setCompleter(true);

      if (m_rCwmsExportSettings.GetEncoding().isEmpty())
      {
        QTextCodec* qtcDefault = QTextCodec::codecForLocale();
        if (CHKPTR(qtcDefault))
        {
            m_pqcbEncoding->setCurrentText(qtcDefault->name());
        }
      }
      else
      {
          m_pqcbEncoding->setCurrentText(m_rCwmsExportSettings.GetEncoding());
      }


   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:21:00 2013----------*
 * @method  CwmsExportSettingsIf::FillMemberListView         // private                           *
 * @return  void                                             //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:21:00 2013----------*/
void CwmsExportSettingsIf::FillMemberListView(const CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QMap<qint64,CdmMember*> qmMembers;
      p_pCdmClass->GetMemberMap(qmMembers);

	  QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
	  QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for(; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            if (pCdmMember->GetValueType() == eDmValueObjectRef)
            {
               
               if (m_qstrlHiddenMembers.contains(pCdmMember->GetKeyname()) == 0)
               {
                  QTreeWidgetItem* pqchItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvMembers);
                  pqchItem->setText(0, pCdmMember->GetCaption());
                  pqchItem->setText(1, pCdmMember->GetKeyname());

                  FillChildMembers(pCdmMember, pqchItem, 0, p_pCdmClass);
                  pqchItem->setExpanded(true);
               }
            }
            else if (CdmMember::IsExportType(pCdmMember->GetValueType()))
            {
               if (m_qstrlHiddenMembers.contains(pCdmMember->GetKeyname()) == 0)
               {
                  QTreeWidgetItem* pqchItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvMembers);
                  pqchItem->setText(0, pCdmMember->GetCaption());
                  pqchItem->setText(1, pCdmMember->GetKeyname());
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:31:51 2013----------*
 * @method  CwmsExportSettingsIf::FillChildMembers           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QTreeWidgetItem* p_pqlvItem                      //                                   *
 * @param   int p_iDepth                                     //                                   *
 * @param   const CdmClass* p_pCdmRequestClass               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:31:51 2013----------*/
void CwmsExportSettingsIf::FillChildMembers(CdmMember* p_pCdmMember,
                                            QTreeWidgetItem* p_pqlvItem,
                                            int p_iDepth,
                                            const CdmClass* p_pCdmRequestClass)
{
   if (CHKPTR(p_pCdmMember) && CHKPTR(p_pqlvItem))
   {  
      int iClassId = p_pCdmMember->GetClassReference();

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(p_pCdmMember->GetSchemeId());

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(iClassId);
         
            if (pCdmClass)
            {
               QMap<qint64,CdmMember*> qmMembers;
               pCdmClass->GetMemberMap(qmMembers);
               
			   QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
			   QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();
            QTreeWidgetItem* pqchItem = nullptr;
               
               for(; qmIt != qmItEnd; ++qmIt)
               {
                  CdmMember* pCdmMember = qmIt.value();
                  
                  if (CHKPTR(pCdmMember))
                  {
                     if (pCdmMember->GetValueType() == eDmValueObjectRef && 
                         p_iDepth < 2 &&
                         p_pCdmRequestClass->GetId() != pCdmMember->GetClassReference() &&
                         p_pCdmRequestClass->IsInherited(pCdmMember->GetClassReference()) < 1)
                     {
                        if (m_qstrlHiddenMembers.contains(pCdmMember->GetKeyname()) == 0)
                        {
                           pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                           pqchItem->setText(0, pCdmMember->GetCaption());
                           pqchItem->setText(1, pCdmMember->GetKeyname());

                           ++p_iDepth;
                           
                           FillChildMembers(pCdmMember, pqchItem, p_iDepth, p_pCdmRequestClass);
                           pqchItem->setExpanded(true);
                        }
                     }
                     else if (CdmMember::IsExportType(pCdmMember->GetValueType()))
                     {
                        if (m_qstrlHiddenMembers.contains(pCdmMember->GetKeyname()) == 0)
                        {
                           pqchItem = new QTreeWidgetItem(p_pqlvItem, pqchItem);
                           pqchItem->setText(0, pCdmMember->GetCaption());
                           pqchItem->setText(1, pCdmMember->GetKeyname());
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------So 13. Apr 12:00:04 2008----------*
 * @method  CwmsExportSettingsIf::DataFormatChangedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 13. Apr 12:00:04 2008----------*/
void CwmsExportSettingsIf::DataFormatChangedSlot()
{
   if (m_pqrbCsv->isChecked())
   {
      m_pqgbCsvSettings->setEnabled(true);
   }
   else
   {
      m_pqgbCsvSettings->setEnabled(false);
   }
}

/** +-=---------------------------------------------------------So 13. Apr 12:00:16 2008----------*
 * @method  CwmsExportSettingsIf::SearchClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 13. Apr 12:00:16 2008----------*/
void CwmsExportSettingsIf::SearchClickedSlot()
{
   QString qstrFileEnding;

   if (m_pqrbCsv->isChecked())
   {
      qstrFileEnding = "*.csv";
   }
   else if (m_pqrbHtml->isChecked())
   {
      qstrFileEnding = "*.html";
   }
   else if (m_pqrbXml->isChecked())
   {
      qstrFileEnding = "*.xml";
   }

   QString qstrFilename = QFileDialog::getSaveFileName(this, tr("Bitte Datei auswählen"), qstrFileEnding);

   QFileInfo qfInfo(qstrFilename);

   if (qfInfo.completeSuffix().isEmpty())
   {
      if (m_pqrbCsv->isChecked())
      {
         qstrFilename += ".csv";
      }
      else if (m_pqrbHtml->isChecked())
      {
         qstrFilename += ".html";
      }
      else if (m_pqrbXml->isChecked())
      {
         qstrFilename += ".xml";
      }
   }

   m_pqleFilename->setText(qstrFilename);
}

/** +-=---------------------------------------------------------So 13. Apr 12:00:31 2008----------*
 * @method  CwmsExportSettingsIf::CancelClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 13. Apr 12:00:31 2008----------*/
void CwmsExportSettingsIf::CancelClickedSlot()
{
   reject();
}

/** +-=---------------------------------------------------------So 13. Apr 12:00:42 2008----------*
 * @method  CwmsExportSettingsIf::OKClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 13. Apr 12:00:42 2008----------*/
void CwmsExportSettingsIf::OKClickedSlot()
{
   bool bExecute = true;
   bExecute = FillExportSettings();


   if (bExecute)
   {
         CdmMessageManager::StartAsyncMessageCollection();
         CwmsExportWriter cCwmsExportFileWriter(m_rCwmsExportSettings);
         cCwmsExportFileWriter.Export();
         CdmMessageManager::information(tr("Export beendet"), 
                                  tr("Der Export wurde abgeschlossen."));
         CdmMessageManager::EndAndShowAsyncMessageCollection();
         accept();
   }
   else
   {
      // Error Messages will be sent in FillExportSettings()
   }
}

/** +-=---------------------------------------------------------So 4. Nov 09:22:32 2012-----------*
 * @method  CwmsExportSettingsIf::FillMembers                // private                           *
 * @return  bool                                             // Successflag                       *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 09:22:32 2012-----------*/
bool CwmsExportSettingsIf::FillMembers()
{
   bool bRet = false;
   QTreeWidgetItemIterator it(m_pqlvSelected);
   m_rCwmsExportSettings.ClearMembers();

   while (*it) 
   {
      m_rCwmsExportSettings.AddMember((*it)->text(1));
      bRet = true;
      ++it;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 21. Apr 16:49:23 2008----------*
 * @method  CwmsExportSettingsIf::AddHiddenMember            // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrHiddenMember                       //                                   *
 * @comment This method adds hidden members to the list. this members won't be displayed for      *
 *----------------last changed: --------------------------------Mo 21. Apr 16:49:23 2008----------*/
void CwmsExportSettingsIf::AddHiddenMember(QString p_qstrHiddenMember)
{
   m_qstrlHiddenMembers.append(p_qstrHiddenMember);
}

/** +-=---------------------------------------------------------Mo 21. Apr 17:28:49 2008----------*
 * @method  CwmsExportSettingsIf::SetHiddenList              // public                            *
 * @return  void                                             //                                   *
 * @param   QValueList<QString> p_qvlHiddenMembers           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 17:28:49 2008----------*/
void CwmsExportSettingsIf::SetHiddenList(QList<QString> p_qvlHiddenMembers)
{
   m_qstrlHiddenMembers = p_qvlHiddenMembers;
}

/** +-=---------------------------------------------------------Do 17. Apr 23:36:23 2008----------*
 * @method  CwmsExportSettingsIf::SelectClickedSlot          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 17. Apr 23:36:23 2008----------*/
void CwmsExportSettingsIf::SelectClickedSlot()
{
   QTreeWidgetItem* pqlviSelectedItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvMembers);
   
   if (pqlviSelectedItem)
   {
      QTreeWidgetItem* pqlviItem = pqlviSelectedItem;
      QString qstrMember = pqlviItem->text(1);

      while (pqlviItem->parent() != nullptr)
      {
         pqlviItem = pqlviItem->parent();

         if (pqlviItem)
         {
            qstrMember = pqlviItem->text(1) + "." + qstrMember;
         }
      }

      pqlviItem = pqlviSelectedItem;
      QString qstrKeyname = pqlviItem->text(1);
      
      while (pqlviItem->parent() != nullptr)
      {
         pqlviItem = pqlviItem->parent();
         
         if (pqlviItem)
         {
            qstrKeyname = pqlviItem->text(1) + "." + qstrKeyname;
         }
      }

      QTreeWidgetItem* pqlviItemNew = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvSelected);
      pqlviItemNew->setText(0, qstrMember);
      pqlviItemNew->setText(1, qstrKeyname);
   }
}

/** +-=---------------------------------------------------------Do 17. Apr 23:36:36 2008----------*
 * @method  CwmsExportSettingsIf::DeselectClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 17. Apr 23:36:36 2008----------*/
void CwmsExportSettingsIf::DeselectClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvSelected);

   if (pqlviItem)
   {
      DELPTR(pqlviItem);
   }
}

/** +-=---------------------------------------------------------Mo 21. Apr 17:08:44 2008----------*
 * @method  CwmsExportSettingsIf::UpClickedSlot              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 17:08:44 2008----------*/
void CwmsExportSettingsIf::UpClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvSelected);
   
   if (pqlviItem)
   {
      QTreeWidgetItem* pqlviItemParent = CwmsTreeWidgetHelper::GetItemAbove(pqlviItem);

      if (pqlviItemParent)
      {
         QString qstrMember = pqlviItem->text(0);
         QString qstrKeyName = pqlviItem->text(1);
         DELPTR(pqlviItem);
         QTreeWidgetItem* pqlviItemGrandParent = CwmsTreeWidgetHelper::GetItemAbove(pqlviItemParent);

         if (pqlviItemGrandParent)
         {
            
            pqlviItem = new QTreeWidgetItem(m_pqlvSelected, pqlviItemGrandParent);
            pqlviItem->setText(0, qstrMember);
            pqlviItem->setText(1, qstrKeyName);
       
         }
         else
         {
            pqlviItem = new QTreeWidgetItem(m_pqlvSelected);
            pqlviItem->setText(0, qstrMember);
            pqlviItem->setText(1, qstrKeyName);
         }

         pqlviItem->setSelected(true);
      }
   }
}


/** +-=---------------------------------------------------------Mo 21. Apr 17:08:36 2008----------*
 * @method  CwmsExportSettingsIf::DownClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 17:08:36 2008----------*/
void CwmsExportSettingsIf::DownClickedSlot()
{
   QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvSelected);
   
   if (pqlviItem)
   {
      QTreeWidgetItem* pqlviSibling = CwmsTreeWidgetHelper::GetItemBelow(pqlviItem);

      if (pqlviSibling)
      {
         QString qstrMember = pqlviItem->text(0);
         QString qstrKeyName = pqlviItem->text(1);
         DELPTR(pqlviItem);

         pqlviItem = new QTreeWidgetItem(m_pqlvSelected, pqlviSibling);
         pqlviItem->setText(0, qstrMember);
         pqlviItem->setText(1, qstrKeyName);
         pqlviItem->setSelected(true);
      }

   }
}

/** +-=---------------------------------------------------------Mo 21. Apr 18:05:29 2008----------*
 * @method  CwmsExportSettingsIf::SaveClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment saves the export settings.                                                            *
 *----------------last changed: --------------------------------Mo 21. Apr 18:05:29 2008----------*/
void CwmsExportSettingsIf::SaveClickedSlot()
{
   QString qstrName = m_rCwmsExportSettings.GetSettingsName();
   qstrName = QInputDialog::getText(this, 
                                    tr("Bitte Namen eingeben"), 
                                    tr("Bitte geben Sie den Namen zum speichern ein."), 
                                    QLineEdit::Normal, 
                                    qstrName);

   if (!qstrName.isEmpty())
   {
      if (FillExportSettings())
      {
         m_rCwmsExportSettings.Save(qstrName);
         CdmMessageManager::information(tr("Speichern erfolgreich"), 
                                        tr("Die Konfiguration wurde erfolgreich gespeichert."));
      }
   }
}

/** +-=---------------------------------------------------------Mo 21. Apr 18:05:46 2008----------*
 * @method  CwmsExportSettingsIf::LoadClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment loads the export settings from file.                                                  *
 *----------------last changed: --------------------------------Mo 21. Apr 18:05:46 2008----------*/
void CwmsExportSettingsIf::LoadClickedSlot()
{
   CwmsImExportManager cManager;
   QMap<QString, QString> qmConfigs = cManager.GetExportConfiguration(m_lClassId);
   QStringList qstrlKeys = qmConfigs.keys();

   if (qstrlKeys.count() > 0)
   {
      bool bOk = false;
      QString qstrKey = QInputDialog::getItem(this, tr("Bitte wählen Sie die zuladenden Konfiguration aus."),
                                                    tr("Konfiguration:"), qstrlKeys, 0, false, &bOk);

      if (bOk && !qstrKey.isEmpty())
      {
         m_rCwmsExportSettings.Load(qstrKey, m_lClassId);
         m_pqlvMembers->clear();
         m_pqlvSelected->clear();

         FillDialog();

         m_pqleStringEncloser->setText(m_rCwmsExportSettings.GetCsvStringEnclosing());
         m_pqleSeperator->setText(m_rCwmsExportSettings.GetCsvSeperator());
         m_pqchbShowHeadline->setChecked(m_rCwmsExportSettings.GetExportHeader());
         m_pqleFilename->setText(m_rCwmsExportSettings.GetFilename());
         
         switch (m_rCwmsExportSettings.GetExportType())
         {
         case eWmsExportTypeCsv:
            m_pqrbCsv->setChecked(true);
            break;
         case eWmsExportTypeHtml:
            m_pqrbHtml->setChecked(true);
            break;
         case eWmsExportTypeXml:
            m_pqrbXml->setChecked(true);
            break;
         default:
            m_pqrbCsv->setChecked(true);
         }

         if (m_rCwmsExportSettings.GetEncoding().isEmpty())
         {
           QTextCodec* qtcDefault = QTextCodec::codecForLocale();
           if (CHKPTR(qtcDefault))
           {
               m_pqcbEncoding->setCurrentText(qtcDefault->name());
           }
         }
         else
         {
             m_pqcbEncoding->setCurrentText(m_rCwmsExportSettings.GetEncoding());
         }
         
         QList<QString> qvlMembers = m_rCwmsExportSettings.GetMemberList();
         QList<QString>::iterator qvlIt = qvlMembers.begin();
         QList<QString>::iterator qvlItEnd = qvlMembers.end();

         for (; qvlIt != qvlItEnd; ++qvlIt)
         {
            QTreeWidgetItem* pqlviItem = CwmsTreeWidgetHelper::CreateItemAtEnd(m_pqlvSelected);
            pqlviItem->setText(0, (*qvlIt));
            pqlviItem->setText(1, (*qvlIt));
         }
      }
   }
   else
   {
      CdmMessageManager::critical(tr("Keine Konfigurationen gefunden"), tr("Zu diesen Datenstrukturen wurden keine Konfigurationen gefunden.\n Laden daher nicht möglich."));
   }
}

/** +-=---------------------------------------------------------Mo 21. Apr 18:44:13 2008----------*
 * @method  CwmsExportSettingsIf::FillExportSettings         // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Apr 18:44:13 2008----------*/
bool CwmsExportSettingsIf::FillExportSettings()
{
    bool bExecute = true;
    m_rCwmsExportSettings.SetFilename(m_pqleFilename->text());

    if (m_pqrbCsv->isChecked())
    {
        m_rCwmsExportSettings.SetExportType(eWmsExportTypeCsv);
        m_rCwmsExportSettings.SetExportHeader(m_pqchbShowHeadline->isChecked());

        if (m_pqleSeperator->text().length() > 0)
        {
            m_rCwmsExportSettings.SetCsvSeperator(m_pqleSeperator->text());

            if (m_pqleSeperator->text().length() > 0)
            {
                m_rCwmsExportSettings.SetCsvStringEnclosing(m_pqleStringEncloser->text());
            }
            else
            {
                bExecute = false;
                CdmMessageManager::critical(tr("Fehler"), tr("Es wurde kein Feldtrennzeichen angegeben"));
            }
        }
        else
        {
            bExecute = false;
            CdmMessageManager::critical(tr("Fehler"), tr("Es wurde kein Texttrennzeichen angegeben."));
        }
    }
    else if (m_pqrbHtml->isChecked())
    {
        m_rCwmsExportSettings.SetExportType(eWmsExportTypeHtml);
    }
    else if (m_pqrbXml->isChecked())
    {
        m_rCwmsExportSettings.SetExportType(eWmsExportTypeXml);
    }

    m_rCwmsExportSettings.SetEncoding(m_pqcbEncoding->currentText());

    if (bExecute)
    {
        if (FillMembers())
        {
            bExecute = true;
        }
        else
        {
            CdmMessageManager::critical(tr("Fehler"), tr("Es wurden keine Ausgabedaten gewählt."));
        }
    }

    return bExecute;
}

/** +-=---------------------------------------------------------Mi 9. Sep 18:20:53 2009-----------*
 * @method  CwmsExportSettingsIf::ReduceExportSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This method opens the searchdlg to reduce the export result.                          *
 *----------------last changed: --------------------------------Mi 9. Sep 18:20:53 2009-----------*/
void CwmsExportSettingsIf::ReduceExportSlot()
{
   CwmsSearchDlg* pCwmsSearchDlg = new CwmsSearchDlg(this);
   CwmsSearchWidgetIf* pCwmsSearchWidget = pCwmsSearchDlg->GetSearchWidget();

   if (CHKPTR(pCwmsSearchWidget))
   {
      ConfigureSearchWidget(pCwmsSearchWidget);

      if (pCwmsSearchDlg->exec() == QDialog::Accepted)
      {
         QList<qint64> qllObjects;
         pCwmsSearchWidget->GetDisplayList(qllObjects);

         int iCount = qllObjects.count();

         if (iCount > 0)
         {
            CdmMessageManager::information(tr("Datenobjekte wurden für den Export ausgewählt"), 
                                     tr("Es wurden ") + QString::number(iCount) + 
                                        tr(" Datenobjekte für den Export ausgewählt."));
            m_rCwmsExportSettings.SetExportList(qllObjects);
         }
         else
         {
            CdmMessageManager::warning(tr("Keine Datenobjekte für den Export ausgewählt"), 
                                 tr("Die Einschränkung lieferte kein Ergebnis. \n"
                                    "Aus diesem Grund wird der Export nicht eingeschränkt."));
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 9. Sep 18:29:21 2009-----------*
 * @method  CwmsExportSettingsIf::ConfigureSearchWidget      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsSearchWidgetIf* p_pCwmsSearchWidget          //                                   *
 * @comment This method configures the searchwidget.                                              *
 *----------------last changed: --------------------------------Mi 9. Sep 18:29:21 2009-----------*/
void CwmsExportSettingsIf::ConfigureSearchWidget(CwmsSearchWidgetIf* p_pCwmsSearchWidget)
{
   if (CHKPTR(p_pCwmsSearchWidget))
   {
      p_pCwmsSearchWidget->SetSearchButtonVisibility(false);

      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmObjectContainer* pContainer = 
            pCdmManager->GetObjectContainer(m_rCwmsExportSettings.GetSchemeId(),
                                       m_rCwmsExportSettings.GetContainerId());

         if (CHKPTR(pContainer))
         {
            p_pCwmsSearchWidget->SetObjectList(pContainer);
            p_pCwmsSearchWidget->FillWidget();
         }
      }
   }
}



