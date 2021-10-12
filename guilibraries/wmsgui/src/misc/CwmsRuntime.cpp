/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsRuntime.cpp
 ** Started Implementation: 2012/09/04
 ** Description:
 **
 ** implements the runtime for wms applications
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QInputDialog>
#include <QAction>
#include <QApplication>

// WMS Includes
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmMessageManager.h"
#include "CdmScheme.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmSettings.h"

// User Manager Includes
#include "CwmsUserManagerIf.h"
#include "CwmsPasswordIf.h"

// Basetools Includes
#include "CwmsContext.h"
#include "CwmsSmtpManager.h"

// own Includes
#include "CwmsGuiLdapAccessConfiguration.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "CwmsPluginsDlg.h"
#include "CwmsDataAccessConfiguration.h"
#include "CwmsSmtpConfiguration.h"
#include "CwmsSmtpSettings.h"
#include "CwmsSearchWindow.h"
#include "CwmsObjectObjectListEditorWidget.h"
#include "CwmsViewObjectListEditorWidget.h"
#include "CwmsHelp.h"
#include "CwmsAboutDlg.h"
#include "CwmsguiObjectEditorSelector.h"
#include "CwmsObjectListEditorWidgetIf.h"
#include "CwmsRuntime.h"

CwmsRuntime::CwmsRuntime(QWidget* p_pqwParent)
: QMainWindow(p_pqwParent),
  CwmsRuntimeBase(true),
  m_pCwmsUserManager(nullptr),
  m_bLogoffOnExit(true),
  m_pqCurrentModuleMenu(nullptr),
  m_pqCurrentModuleToolbar(nullptr)
{
   connect(CwmsContext::GetContext(), SIGNAL(ApplicationShutdownSignal()), this, SLOT(close()));
}

CwmsRuntime::~CwmsRuntime()
{
   DELPTR(m_pCwmsUserManager);
}

void CwmsRuntime::SetApplication(CwmsApplication p_cApp)
{
   m_cApp = p_cApp;
   InstallTranslator();
   setupUi(this);
   QString qstrTitle = m_cApp.GetName() + QStringLiteral(" V") + m_cApp.GetVersion();
   setWindowTitle(qstrTitle);
   move(200,200);
}

void CwmsRuntime::FillWidget()
{
   if (m_cApp.IsValid())
   {
       m_pqaLicenceManager->setVisible(false);
      CwmsguiObjectEditorSelector::Init();
      InstallBaseFunctionsToExecutor();
      FillModules();
      OpenDefaultModule();
   }
}

void CwmsRuntime::FillModules()
{
   CdmObjectContainer* pContainer = m_cApp.GetModules();

   if (CHKPTR(pContainer))
   {
      QString qstrWql = "select Name, Default, Position from \"" + pContainer->GetKeyname() + "\" where Active = true order by Position";
      CdmQueryEnhanced* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

      int iResultCount = pCdmQuery->GetResultCount();

      if (iResultCount == 1)
      {
         m_pqtbModules->hide();
      }

      for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
      {
         QString qstrName = pCdmQuery->GetResultAt(0, iCounter).toString();
        qint64 lObjectId = pCdmQuery->GetObjectIdAt(iCounter);
         CdmObject* pCdmObject = pCdmQuery->GetObjectAt(iCounter);
         CwmsApplicationModule cModule(pCdmObject);

         QAction* pAction = new QAction();
         pAction->setText(qstrName.toUtf8());
         pAction->setIcon(cModule.GetIcon());
         pAction->setData(lObjectId);
         m_pqtbModules->addAction(pAction);
         connect(pAction, SIGNAL(triggered(bool)), this, SLOT(EditActionTriggeredSlot()));

         if (pCdmQuery->GetResultAt(1, iCounter).toBool() || iResultCount == 1)
         {
            m_cDefaultModule = cModule;
         }
      }
   }
}

void CwmsRuntime::OpenDefaultModule()
{
   if (m_cDefaultModule.IsValid())
   {
      OpenModule(m_cDefaultModule);
   }
}

void CwmsRuntime::EditActionTriggeredSlot()
{
   QAction* pAction = dynamic_cast<QAction*> (sender());
   if (pAction)
   {
     qint64 lObjectId = pAction->data().toInt();

      if (lObjectId > 0)
      {
         OpenModule(lObjectId);
      }
   }
}

void CwmsRuntime::ClientSettingsSlot()
{
    BODY_TRY
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CwmsGuiDataAccessConfiguration* pEditor = new CwmsGuiDataAccessConfiguration();
        pEditor->FillDialog();

        if (QDialog::Accepted == pEditor->exec())
        {
            CdmMessageManager::information(tr("Einstellungen übernommen"), tr("Die Einstellungen wurden übernommen."));
        }

        DELPTR(pEditor)
    }
    BODY_CATCH
}

void CwmsRuntime::SetCurrentModuleMenu(QMenu *p_pMenu)
{
    m_pqCurrentModuleMenu = p_pMenu;
}

void CwmsRuntime::LdapSettingsSlot()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        if (pCdmManager->IsLoggedInUserAdmin())
        {
            CwmsGuiLdapAccessConfiguration lEditor(pCdmManager->GetSettings(),0);

            if (QDialog::Accepted == lEditor.exec())
            {
                CdmMessageManager::information(tr("Einstellungen übernommen"),
                    tr("Die Einstellungen wurden übernommen."));
            }
        }
    }
}

void CwmsRuntime::LanguageSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         QMap<int, QString> qmLanguages = pCdmDatabase->GetLanguageMap();
         QStringList qstrlLanguages;
         QMap<int, QString>::iterator qmIt = qmLanguages.begin();
         QMap<int, QString>::iterator qmItEnd = qmLanguages.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            qstrlLanguages.append(qmIt.value());

         }

         QString qstrLanguage = QInputDialog::getItem(this, 
                                                      tr("Sprachauswahl"), 
                                                      tr("Bitte Sprache wählen"), 
                                                      qstrlLanguages, 
                                                      0,
                                                      false);

         if (!qstrLanguage.isEmpty())
         {
            pCdmManager->SetCurrentLanguage(qstrLanguage);
            m_cApp.SetCurrentUserLanguage(qstrLanguage);
            CdmMessageManager::information(tr("Sprache geändert Programm neu starten"), 
                                     tr("Die Spracheinstellung wurde geändert. Um diese vollständig zu aktivieren müssen Sie das Programm neu starten!"));
         }
      }
      
   }
}

void CwmsRuntime::HelpSlot()
{
   CwmsHelp::ShowHtmlHelp(m_cApp.GetHelp(), this);
}

void CwmsRuntime::InfoSlot()
{
   CwmsAboutDlg::ShowAboutDialog(m_cApp, this, this);
}

void CwmsRuntime::UserManagerSlot()
{
   if (!m_pCwmsUserManager)
   {
      m_pCwmsUserManager = new CwmsUserManagerIf(this);
   }

   m_pCwmsUserManager->show();
}

void CwmsRuntime::ChangePasswordSlot()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CwmsPasswordIf::ChangePassword(const_cast<CumUser*>(pCdmManager->GetUser()), this);
   }
}

QString CwmsRuntime::GetBuild()
{
   QString qstrDate = __DATE__;
   QString qstrBuild = qstrDate;

   // a small hack for generating a nice date format
   const char mydate[] = 
   {
      __DATE__[4] == ' ' ? '0' : __DATE__[4], __DATE__[5], '.',

      __DATE__[0] == 'O' ||
      __DATE__[0] == 'N' ||
      __DATE__[0] == 'D' ? '1' : '0',

      __DATE__[0] == 'J' && __DATE__[0] == 'a' ? '1' :
      __DATE__[0] == 'F' ? '2' :
      __DATE__[0] == 'M' && __DATE__[2] == 'r' ? '3' :
      __DATE__[0] == 'A' && __DATE__[1] == 'p' ? '4' :
      __DATE__[0] == 'M' ? '5' :
      __DATE__[0] == 'J' && __DATE__[2] == 'n' ? '6' :
      __DATE__[0] == 'J' ? '7' :
      __DATE__[0] == 'A' ? '8' :
      __DATE__[0] == 'S' ? '9' :
      __DATE__[0] == 'O' ? '0' :
      __DATE__[0] == 'N' ? '1' :
      __DATE__[0] == 'D' ? '2' : 'X',

      '.',
      __DATE__[7], __DATE__[8], __DATE__[9], __DATE__[10], '\0'

   };


   QDate qdDate = QDate::fromString(mydate, "dd.MM.yyyy");

   if (qdDate.isValid())
   {
      int iDays = qdDate.daysTo(QDate(2000,4,1)) * (-1);
      qstrBuild = QString::number(iDays);
   }

   return qstrBuild;
}

void CwmsRuntime::closeEvent(QCloseEvent* p_pqCloseEvent)
{
   QWidget* pWidget = QMainWindow::centralWidget();
   DELPTR(pWidget);
   QMainWindow::setCentralWidget(nullptr);

   if (m_bLogoffOnExit)
   {
       if (!CwmsContext::GetContext()->IsTimedOut())
       {
            CdmSessionManager::Logout();
       }
   }

   RemoveTranslator();
   QWidget::closeEvent(p_pqCloseEvent);
}

void CwmsRuntime::SetLogoutOnExit(bool p_bLogout)
{
   m_bLogoffOnExit = p_bLogout;
}

QWidget* CwmsRuntime::GetMainWidget()
{
   return this;
}

CwmsApplication CwmsRuntime::GetApplication()
{
   return m_cApp;
}

void CwmsRuntime::SmtpSlot()
{
   CwmsSmtpManager cManager;
   CwmsSmtpConfiguration* pConfig = cManager.GetSmtpConfiguration();

   if (CHKPTR(pConfig))
   {
      CwmsSmtpSettings::Edit(*pConfig, this);
      DELPTR(pConfig);
   }
}

void CwmsRuntime::AddToolBar(QToolBar* p_pToolBar)
{
   if (CHKPTR(p_pToolBar))
   {
      m_qlToolbars.append(p_pToolBar);
      addToolBar(p_pToolBar);
      m_pqCurrentModuleToolbar = p_pToolBar;
   }
}

void CwmsRuntime::PluginsSlot()
{
    CwmsPluginsDlgIf* pDlg = new CwmsPluginsDlgIf(this);
    pDlg->FillDialog(m_cApp);
    pDlg->exec();
    DELPTR(pDlg);
}
