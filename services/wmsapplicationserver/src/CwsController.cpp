/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CbmswsController.cpp
 ** Started Implementation: 2012/04/09
 ** Description:
 **
 ** Implements the user interface for the webserver
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <qdir.h>

// WMS Manager Include
#include "CdmError.h"
#include "CdmManager.h"
#include "CdmSessionManager.h"
#include "CdmErrorLogfileWriter.h"
#include "CdmMessageManager.h"
#include "CdmSettings.h"
#include "CdmJson.h"

// BASETOOLS Includes
#include "CwmsContext.h"


// WMS GUI Includes
#include "CwmsPluginsDlg.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "CwmsErrorIf.h"
#include "CwmsMessenger.h"

// BMSHANDLER Includes
#include "CwhWms.h"

// WMSCOM Includes
#include "CwmscomHandler.h"

// own Includes
#include "CwsRequest.h"
#include "CwsResponse.h"
#include "CwsServerCommandHandler.h"
#include "CwsController.h"

/** +-=---------------------------------------------------------Di 10. Apr 08:36:32 2012----------*
 * @method  CbmswsController::CbmswsController               // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pParent                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 10. Apr 08:36:32 2012----------*/
CwsController::CwsController(CwsServerCommandHandler* p_pCommandHandler, QWidget* p_pParent)
: QDialog(p_pParent),
  m_pTrayIconMenu(NULL),
  m_pTrayIcon(NULL),
  m_pCommandHandler(p_pCommandHandler)

{
   setupUi(this);

   m_pqaStart = new QAction(this);
   m_pqaStart->setText(tr("Start"));
   m_pqaStart->setIcon(m_pqpbStart->icon());
   connect(m_pqaStart, SIGNAL(triggered()), this, SLOT(StartClickedSlot()));

   m_pqaStop = new QAction(this);
   m_pqaStop->setText(tr("Stop"));
   m_pqaStop->setIcon(m_pqpbStop->icon());
   connect(m_pqaStop, SIGNAL(triggered()), this, SLOT(StopClickedSlot()));

   m_pqaConfiguration = new QAction(this);
   m_pqaConfiguration->setText(tr("Configuration"));
   m_pqaConfiguration->setIcon(m_pqpbConfiguration->icon());
   connect(m_pqaConfiguration, SIGNAL(triggered()), this, SLOT(ConfigurationClickedSlot()));

   m_pqaShowLogger = new QAction(this);
   m_pqaShowLogger->setText(tr("Configuration"));
   m_pqaShowLogger->setIcon(m_pqpbConfiguration->icon());
   connect(m_pqaShowLogger, SIGNAL(triggered()), this, SLOT(OpenLogFileClickedSlot()));

   m_pqaShowCommandWindow = new QAction(this);
   m_pqaShowCommandWindow->setText(tr("Show Command Window"));
   connect(m_pqaShowCommandWindow, SIGNAL(triggered()), this, SLOT(show()));

   m_pqaExit = new QAction(this);
   m_pqaExit->setText(tr("Quit"));
   m_pqaStart->setIcon(m_pqpbExit->icon());
   connect(m_pqaExit, SIGNAL(triggered()), this, SLOT(QuitClickedSlot()));

   m_pTrayIconMenu = new QMenu(this);
   m_pTrayIconMenu->addAction(m_pqaStart);
   m_pTrayIconMenu->addAction(m_pqaStop);
   m_pTrayIconMenu->addAction(m_pqaConfiguration);
   m_pTrayIconMenu->addSeparator();
   m_pTrayIconMenu->addAction(m_pqaShowCommandWindow);
   m_pTrayIconMenu->addSeparator();
   m_pTrayIconMenu->addAction(m_pqaExit);

   m_pTrayIcon = new QSystemTrayIcon(this);
   QIcon icon;
   icon.addFile(QStringLiteral(":/icons/wmsserver.png"), QSize(), QIcon::Normal, QIcon::Off);
   m_pTrayIcon->setIcon(icon);
   m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
   m_pTrayIcon->setToolTip(tr("The WMS Application Server"));
   m_pTrayIcon->show();
}

/** +-=---------------------------------------------------------Di 10. Apr 08:36:39 2012----------*
 * @method  CbmswsController::~CbmswsController              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbmswsController                                              *
 *----------------last changed: --------------------------------Di 10. Apr 08:36:39 2012----------*/
CwsController::~CwsController()
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:45:00 2012-----------*
 * @method  CbmswsController::StartClickedSlot               // public, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:45:00 2012-----------*/
void CwsController::StartClickedSlot()
{
    CwsRequest request;
    CwsResponse response;

    if (m_pCommandHandler->Start(request, response) > 0)
    {
        QString qstrMessage = tr("Server is running");
        m_pqleState->setText(qstrMessage);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);
        INFO(qstrMessage);
        m_pqpbStart->setEnabled(false);
        m_pqaStart->setEnabled(false);
        m_pqpbStop->setEnabled(true);
        m_pqaStop->setEnabled(true);
        m_pqpbConfiguration->setEnabled(false);
        m_pqaConfiguration->setEnabled(false);
        m_pTrayIcon->setIcon(m_pqpbStart->icon());
    }
    else
    {
        QString qstrError = response.GetErrorString();
        m_pqleState->setText(qstrError);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrError, QSystemTrayIcon::Critical);
        m_pqpbStart->setEnabled(true);
        m_pqaStart->setEnabled(true);
        m_pqpbStop->setEnabled(false);
        m_pqaStop->setEnabled(false);
        m_pqpbConfiguration->setEnabled(true);
        m_pqaConfiguration->setEnabled(true);

        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/wmsserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pTrayIcon->setIcon(icon);
    }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:45:11 2012-----------*
 * @method  CbmswsController::StopClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:45:11 2012-----------*/
void CwsController::StopClickedSlot()
{
    CwsRequest request;
    CwsResponse response;

    if (m_pCommandHandler->Stop(request, response) > 0)
    {
        m_pqpbStart->setEnabled(true);
        m_pqaStart->setEnabled(true);
        m_pqpbStop->setEnabled(false);
        m_pqaStop->setEnabled(false);
        m_pqpbConfiguration->setEnabled(true);
        m_pqaConfiguration->setEnabled(true);
        QString qstrMessage = tr("Server stopped");
        m_pqleState->setText(qstrMessage);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);

        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/wmsserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pTrayIcon->setIcon(icon);
    }
}

void CwsController::PauseClickedSlot()
{
   StopClickedSlot();
}

void CwsController::ResumeClickedSlot()
{
   StartClickedSlot();
}

/** +-=---------------------------------------------------------Do 31. Mai 08:42:10 2012----------*
 * @method  CbmswsController::QuitClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Mai 08:42:10 2012----------*/
void CwsController::QuitClickedSlot()
{
    CwsRequest request;
    CwsResponse response;


   if (m_pCommandHandler->IsRunning(request, response) > 0 &&
       m_pCommandHandler->GetOpenSessions(request, response) > 0)
   {
      if (QMessageBox::question(this, 
                                tr("Really Quit?"),
                                tr("Do you really want to quit the server?\n"
                                "All open sessions and threads will be terminated."),
                                QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
      {
         qApp->quit();
      }
   }
   else
   {
      qApp->quit();
   }
}

void CwsController::ConfigurationClickedSlot() 
{
   CwmsQmlServerSettings* pSettings = new CwmsQmlServerSettings();
   pSettings->openSettings(NULL);
}

void CwsController::DataSourceClickedSlot()
{
   CwmsGuiDataAccessConfiguration* pEditor = new CwmsGuiDataAccessConfiguration("Webserver");
   pEditor->FillDialog();

   if (QDialog::Accepted == pEditor->exec())
   {
         CdmMessageManager::information(tr("Einstellungen übernommen"),
            tr("Die Einstellungen wurden übernommen."));
   }

   DELPTR(pEditor);
}

void CwsController::closeEvent(QCloseEvent *event)
{
   if (m_pTrayIcon->isVisible()) {
      QMessageBox::information(this, tr("WMS Application Server"),
         tr("The program will keep running in the "
         "system tray. To terminate the program, "
         "choose <b>Exit</b> in the context menu "
         "of the system tray entry."));
      hide();
      event->ignore();
   }
}

void CwsController::OpenLogFileClickedSlot() 
{
    CwmsQmlServerSettings cSettings;

   if (cSettings.getLoggingActive())
   {
      QString qstrPath = cSettings.getLoggingPath();

      if (!qstrPath.isEmpty())
      {
         QDesktopServices services;
         services.openUrl(QUrl::fromLocalFile(qstrPath));
      }
   }
}

void CwsController::ServerPluginsSlot()
{
    CdmObjectContainer* pContainer = NULL;
    CwsRequest request;
    CwsResponse response;

    if (m_pCommandHandler->ServerLogin(request, response))
    {
        CwmsContext* pContext = CwmsContext::GetContext();

        if (CHKPTR(pContext))
        {
            CwmsPluginManager* pPluginManager = pContext->GetPluginManager();

            if (CHKPTR(pPluginManager))
            {
                pContainer = pPluginManager->GetServerPluginContainer();

                if (CHKPTR(pContainer))
                {
                    CwmsPluginsDlgIf cPlugins(this);
                    cPlugins.FillDialogServer(pContainer);
                    cPlugins.exec();
                }
            }
        }

        m_pCommandHandler->ServerLogout(request, response);
    }
}
