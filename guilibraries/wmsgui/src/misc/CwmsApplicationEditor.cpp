/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsApplicationEditor.cpp
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 ** implements the editor for applications
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMap>
#include <QFileDialog>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmQueryBuilder.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsFormManager.h"
#include "CwmsRightsManagerIf.h"
#include "CwmsTreeWidgetHelper.h"
#include "CoeTextEditIf.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsApplicationModule.h"
#include "CwmsApplicationModuleEditor.h"
#include "CwmsApplicationEditor.h"

/** +-=---------------------------------------------------------Do 30. Aug 16:34:55 2012----------*
 * @method  CwmsApplicationEditor::CwmsApplicationEditor     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:34:55 2012----------*/
CwmsApplicationEditor::CwmsApplicationEditor(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_rpCdmMainWindow(nullptr)
{
   setupUi(this);

   m_pqchbLicenceCheck->hide();
   m_pqpbCancelApplication->hide();
   m_pqpbUpdateApplication->hide();
   m_pqgbBaseData->setEnabled(false);
   m_pqgbDescription->setEnabled(false);
   m_pqgbVersion->setEnabled(false);
   m_pqgbApplicationType->setEnabled(false);
}

/** +-=---------------------------------------------------------Do 30. Aug 16:35:21 2012----------*
 * @method  CwmsApplicationEditor::~CwmsApplicationEditor    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsApplicationEditor                                         *
 *----------------last changed: --------------------------------Do 30. Aug 16:35:21 2012----------*/
CwmsApplicationEditor::~CwmsApplicationEditor()
{
}

/** +-=---------------------------------------------------------Do 30. Aug 16:42:29 2012----------*
 * @method  CwmsApplicationEditor::FillWidget                // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplication p_cApp                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:42:29 2012----------*/
void CwmsApplicationEditor::FillWidget(CwmsApplication p_cApp)
{
   if (p_cApp.IsValid())
   {
      m_cApp = p_cApp;

      m_pqleEmail->setText(m_cApp.GetEmail());
      m_pqleHotline->setText(m_cApp.GetHotline());
      m_pqleManufacturer->setText(m_cApp.GetManufacturer());
      m_pqleName->setText(m_cApp.GetName());
      m_pqleWeb->setText(m_cApp.GetWebaddress());
      m_pqchbLicenceCheck->setChecked(m_cApp.GetLicenceCheck());
      m_pqteDescription->setPlainText(m_cApp.GetDescription());
      m_pqchbDesktop->setChecked(m_cApp.GetDesktop());
      m_pqchbWeb->setChecked(m_cApp.GetWeb());
      m_pqchbMobile->setChecked(m_cApp.GetMobile());
      m_pqsbMajor->setValue(m_cApp.GetVersionMajor());
      m_pqsbMinor->setValue(m_cApp.GetVersionMinor());
      m_pqsbBugfix->setValue(m_cApp.GetVersionBugfix());
      m_pqteHelp->setHtml(m_cApp.GetHelp());
      m_pqteLicence->setHtml(m_cApp.GetLicence());
      m_pqchbActive->setChecked(m_cApp.GetActive());
      m_pqleMain->setText(m_cApp.GetMain());

      QPixmap qPixmap = m_cApp.GetIcon();

      if (!qPixmap.isNull())
      {
          QIcon qIcon(qPixmap);
          m_pqpbIcon->setIcon(qIcon);
      }

      m_rpCdmMainWindow = m_cApp.GetMainWindow();

      if (m_rpCdmMainWindow)
      {
         m_pqleMainWindow->setText(m_rpCdmMainWindow->GetDisplayString("Name"));
      }

      FillModules();
      FillTranslations();
      m_pCwmsPlugins->FillWidgetApplication(m_cApp);
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 18:22:04 2012----------*
 * @method  CwmsApplicationEditor::FillModules               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 18:22:04 2012----------*/
void CwmsApplicationEditor::FillModules()
{
   CdmObjectContainer* pContainer = m_cApp.GetModules();

   if (CHKPTR(pContainer))
   {
      QString qstrWql = "select Position, Name from \"" + pContainer->GetKeyname() + "\" order by Position";
      m_modelModules.Execute(qstrWql);
      m_pqtvModules->setModel(&m_modelModules);
      CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtvModules);
   }
}

/** +-=---------------------------------------------------------Fr 7. Sep 14:42:44 2012-----------*
 * @method  CwmsApplicationEditor::FillTranslations          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 14:42:44 2012-----------*/
void CwmsApplicationEditor::FillTranslations()
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
            m_pqcbLanguage->addItem(qmIt.value(), qmIt.value());
         }

         m_pqcbLanguage->setCurrentIndex(m_pqcbLanguage->findData(pCdmDatabase->GetCurrentLanguageName()));
         LanguageChangedSlot();
      }
   }
}

/** +-=---------------------------------------------------------Fr 7. Sep 14:53:58 2012-----------*
 * @method  CwmsApplicationEditor::LanguageChangedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 14:53:58 2012-----------*/
void CwmsApplicationEditor::LanguageChangedSlot()
{
   CdmObjectContainer* pCdmList = m_cApp.GetTranslations();

   if (CHKPTR(pCdmList))
   {
       QString iLanguageId = m_pqcbLanguage->itemData(m_pqcbLanguage->currentIndex()).toString();

	   if (iLanguageId > 0)
	   {
		   QString qstrWql = "select Original, Translation from \"" +
			   pCdmList->GetKeyname() + "\" where Language = \"" +
               iLanguageId + "\"";

		   m_pCwmsEditor->SetContainer(pCdmList);
		   m_pCwmsEditor->SetQuery(qstrWql);
		   m_pCwmsEditor->FillDialog();
	   }
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:51:43 2012----------*
 * @method  CwmsApplicationEditor::EditHelpClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:51:43 2012----------*/
void CwmsApplicationEditor::EditHelpClickedSlot()
{
   QString qstrHelp = m_cApp.GetHelp();
   CoeTextEditIf::EditText(this, qstrHelp);
   m_cApp.SetHelp(qstrHelp);
   m_pqteHelp->setHtml(qstrHelp);
   m_cApp.CommitObject();
}

/** +-=---------------------------------------------------------Mi 5. Sep 11:46:37 2012-----------*
 * @method  CwmsApplicationEditor::EditLicenceClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 11:46:37 2012-----------*/
void CwmsApplicationEditor::EditLicenceClickedSlot()
{
   QString qstrLicence = m_cApp.GetLicence();
   CoeTextEditIf::EditText(this, qstrLicence);
   m_cApp.SetLicence(qstrLicence);
   m_pqteLicence->setHtml(qstrLicence);
   m_cApp.CommitObject();
}

/** +-=---------------------------------------------------------Do 30. Aug 16:51:57 2012----------*
 * @method  CwmsApplicationEditor::AddModuleClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:51:57 2012----------*/
void CwmsApplicationEditor::AddModuleClickedSlot()
{
   CdmObjectContainer* pContainer = m_cApp.GetModules();

   if (CHKPTR(pContainer))
   {
      CwmsApplicationModule cModule = CwmsApplicationModule::Create(pContainer);

      if (cModule.IsValid())
      {
         CwmsApplicationModuleEditor::EditModule(cModule, true, this);
         FillModules();
      }
   }
}

/** +-=---------------------------------------------------------Di 4. Sep 10:27:49 2012-----------*
 * @method  CwmsApplicationEditor::EditModuleClickedSlot     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 10:27:49 2012-----------*/
void CwmsApplicationEditor::EditModuleClickedSlot()
{
   CdmObject* pCdmObject = m_modelModules.GetObject(m_pqtvModules->currentIndex());

   if (pCdmObject)
   {
      CwmsApplicationModuleEditor::EditModule(CwmsApplicationModule(pCdmObject), false, this);
      FillModules();
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:52:09 2012----------*
 * @method  CwmsApplicationEditor::DeleteModuleClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:52:09 2012----------*/
void CwmsApplicationEditor::DeleteModuleClickedSlot()
{
   CdmObject* pCdmObject = m_modelModules.GetObject(m_pqtvModules->currentIndex());

   if (pCdmObject)
   {
      pCdmObject->SetDeleted();
      pCdmObject->Commit();
      FillModules();
   }
}

void CwmsApplicationEditor::MoveModuleUpClickedSlot()
{
    CdmObject* pObject = m_modelModules.GetObject(m_pqtvModules->currentIndex());
    CdmObjectContainer* pContainer = m_cApp.GetModules();

    if (pObject && CHKPTR(pContainer))
    {
        CwmsApplicationModule cModule(pObject);

        if (cModule.GetPosition() > 0)
        {
            int iNewPosition = cModule.GetPosition() - 1;

            QString qstrWql = "select from \"" + pContainer->GetKeyname() + "\" where Position = " + QString::number(iNewPosition);
            CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

            if (pQuery->GetResultCount() > 0)
            {
                CdmObject* pObjectOld = pQuery->GetFirstResultObject();

                if (CHKPTR(pObjectOld))
                {
                    CwmsApplicationModule cModuleOld(pObjectOld);
                    cModuleOld.SetPosition(cModule.GetPosition());
                    cModule.SetPosition(iNewPosition);
                    cModuleOld.CommitObject();
                    cModule.CommitObject();
                    FillModules();

                    // Mark the right object
                    m_pqtvModules->setCurrentIndex(m_modelModules.index(iNewPosition-1,0)); // position count starts at 1 and index at 0
                }
            }
        }
    }
}

void CwmsApplicationEditor::MoveModuleDownClickedSlot()
{
    CdmObject* pObject = m_modelModules.GetObject(m_pqtvModules->currentIndex());
    CdmObjectContainer* pContainer = m_cApp.GetModules();

    if (pObject && CHKPTR(pContainer))
    {
        CwmsApplicationModule cModule(pObject);
        int iNewPosition = cModule.GetPosition() + 1;

        QString qstrWql = "select from \"" + pContainer->GetKeyname() + "\" where Position = " + QString::number(iNewPosition);
        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

        if (pQuery->GetResultCount() > 0) // else it is already the last one
        {
            CdmObject* pObjectOld = pQuery->GetFirstResultObject();

            if (CHKPTR(pObjectOld))
            {
                CwmsApplicationModule cModuleOld(pObjectOld);
                cModuleOld.SetPosition(cModule.GetPosition());
                cModule.SetPosition(iNewPosition);
                cModuleOld.CommitObject();
                cModule.CommitObject();
                FillModules();

                // Mark the right object
                m_pqtvModules->setCurrentIndex(m_modelModules.index(iNewPosition - 1,0));// position count starts at 1 and index at 0
            }
        }
    }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:52:27 2012----------*
 * @method  CwmsApplicationEditor::CancelChangesClickedSlot  // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:52:27 2012----------*/
void CwmsApplicationEditor::CancelChangesClickedSlot()
{
   m_pqpbCancelApplication->hide();
   m_pqpbUpdateApplication->hide();
   m_pqpbEditApplication->show();
   m_pqgbBaseData->setEnabled(false);
   m_pqgbDescription->setEnabled(false);
   m_pqgbVersion->setEnabled(false);
   m_pqgbApplicationType->setEnabled(false);
   
   FillWidget(m_cApp);
}

/** +-=---------------------------------------------------------Fr 31. Aug 15:37:26 2012----------*
 * @method  CwmsApplicationEditor::Validate                  // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Aug 15:37:26 2012----------*/
bool CwmsApplicationEditor::Validate()
{
   bool bRet = false;

   if (!m_pqleName->text().isEmpty())
   {
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 31. Aug 15:38:44 2012----------*
 * @method  CwmsApplicationEditor::SaveData                  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 31. Aug 15:38:44 2012----------*/
void CwmsApplicationEditor::SaveData()
{
   m_cApp.SetActive(m_pqchbActive->isChecked());
   m_cApp.SetDescription(m_pqteDescription->toPlainText());
   m_cApp.SetDesktop(m_pqchbDesktop->isChecked());
   m_cApp.SetEmail(m_pqleEmail->text());
   m_cApp.SetHotline(m_pqleHotline->text());
   m_cApp.SetLicenceCheck(m_pqchbLicenceCheck->isChecked());
   m_cApp.SetManufacturer(m_pqleManufacturer->text());
   m_cApp.SetMobile(m_pqchbMobile->isChecked());
   m_cApp.SetName(m_pqleName->text());
   m_cApp.SetVersionBugfix(m_pqsbBugfix->value());
   m_cApp.SetVersionMajor(m_pqsbMajor->value());
   m_cApp.SetVersionMinor(m_pqsbMinor->value());
   m_cApp.SetWeb(m_pqchbWeb->isChecked());
   m_cApp.SetWebaddress(m_pqleWeb->text());
   m_cApp.SetMainWindow(m_rpCdmMainWindow);
   m_cApp.SetMain(m_pqleMain->text());

   if (!m_qstrIconName.isEmpty())
   {
       m_cApp.SetIcon(m_qstrIconName);
   }

   m_cApp.CommitObject();
}

/** +-=---------------------------------------------------------Do 30. Aug 16:53:06 2012----------*
 * @method  CwmsApplicationEditor::UpdateApplicationClickedSlot // private, slots                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:53:06 2012----------*/
void CwmsApplicationEditor::UpdateApplicationClickedSlot()
{
   if (Validate())
   {
      SaveData();
      m_pqpbCancelApplication->hide();
      m_pqpbUpdateApplication->hide();
      m_pqpbEditApplication->show();
      m_pqgbBaseData->setEnabled(false);
      m_pqgbDescription->setEnabled(false);
      m_pqgbVersion->setEnabled(false);
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 16:53:25 2012----------*
 * @method  CwmsApplicationEditor::EditApplicationClickedSlot // private, slots                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:53:25 2012----------*/
void CwmsApplicationEditor::EditApplicationClickedSlot()
{
   m_pqpbCancelApplication->show();
   m_pqpbUpdateApplication->show();
   m_pqpbEditApplication->hide();
   m_pqgbBaseData->setEnabled(true);
   m_pqgbDescription->setEnabled(true);
   m_pqgbVersion->setEnabled(true);
   m_pqgbApplicationType->setEnabled(true);
}


/** +-=---------------------------------------------------------Fr 7. Sep 10:27:12 2012-----------*
 * @method  CwmsApplicationEditor::RightsClickedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 10:27:12 2012-----------*/
void CwmsApplicationEditor::RightsClickedSlot()
{
   CdmObjectContainer* pCdmList = m_cApp.GetModules();

   if (CHKPTR(pCdmList))
   {
      CwmsRightsManagerIf* pRights = new CwmsRightsManagerIf(pCdmList, this);
      pRights->exec();
      DELPTR(pRights);
   }
}

void CwmsApplicationEditor::SelectMainWindowClickedSlot()
{
   CwmsFormManager cManager;
   CdmObjectContainer* pCdmList = cManager.GetFormUserDefinedContainer();

   if (CHKPTR(pCdmList))
   {
      m_rpCdmMainWindow = CwmsObjectSelectionIf::GetObject(pCdmList, nullptr, this, "Name");

      if (m_rpCdmMainWindow)
      {
         m_pqleMainWindow->setText(m_rpCdmMainWindow->GetDisplayString("Name"));
      }
      else
      {
         m_pqleMainWindow->setText("");
      }
   }

}

void CwmsApplicationEditor::SelectIconSlot()
{
    m_qstrIconName = QFileDialog::getOpenFileName(this, tr("Bitte wählen Sie ein Icon aus dem Dateisystem aus"),
                                                  "", "*.png *.jpg *.gif *.ico");

    if (!m_qstrIconName.isEmpty())
    {
        QFile qFile(m_qstrIconName);

        if (qFile.open(QIODevice::ReadOnly))
        {
            m_qbaIcon = qFile.readAll();
            QPixmap qPixmap;
            qPixmap.loadFromData(m_qbaIcon);

            if (!qPixmap.isNull())
            {
                QIcon qIcon(qPixmap);
                m_pqpbIcon->setIcon(qIcon);
            }
        }
    }

}
