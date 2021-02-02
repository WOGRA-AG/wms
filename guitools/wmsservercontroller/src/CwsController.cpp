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
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <qdir.h>

#include "wmsServerDefines.h"

// own Includes
#include "CwsServerConfig.h"
#include "CwsController.h"



/** +-=---------------------------------------------------------Di 10. Apr 08:36:32 2012----------*
 * @method  CbmswsController::CbmswsController               // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pParent                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 10. Apr 08:36:32 2012----------*/
CwsController::CwsController(QWidget* p_pParent)
: QDialog(p_pParent),
  m_pTrayIconMenu(nullptr),
  m_pTrayIcon(nullptr),
  m_cController(SERVICENAME)
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

   UpdateUiState();

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
    QStringList args;

    if (m_cController.start(args))
    {
        QString qstrMessage = tr("Server is running");
        m_pqleState->setText(qstrMessage);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);

    }
    else
    {
        QString qstrError = "Could not start Service";
        m_pqleState->setText(qstrError);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrError, QSystemTrayIcon::Critical);
    }

    UpdateUiState();
}

void CwsController::UpdateUiState()
{
    if (m_cController.isInstalled())
    {
        if (m_cController.isRunning())
        {
            m_pqpbInstall->setEnabled(false);
            m_pqpbUninstall->setEnabled(false);
            m_pqpbOpenLogfile->setEnabled(true);
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
            m_pqpbInstall->setEnabled(false);
            m_pqpbUninstall->setEnabled(true);
            m_pqpbOpenLogfile->setEnabled(true);
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
    else
    {
        m_pqpbInstall->setEnabled(true);
        m_pqpbUninstall->setEnabled(false);
        m_pqpbOpenLogfile->setEnabled(true);
        m_pqpbStart->setEnabled(false);
        m_pqaStart->setEnabled(false);
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
    m_cController.stop();

    if (!m_cController.isRunning())
    {
        QString qstrMessage = tr("Server stopped");
        m_pqleState->setText(qstrMessage);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);
    }
    else
    {
        QString qstrMessage = tr("Server could not be stopped");
        m_pqleState->setText(qstrMessage);
        m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);
    }

    UpdateUiState();
}

void CwsController::PauseClickedSlot()
{
   m_cController.pause();
   UpdateUiState();
}

void CwsController::ResumeClickedSlot()
{
    m_cController.resume();
    UpdateUiState();
}

/** +-=---------------------------------------------------------Do 31. Mai 08:42:10 2012----------*
 * @method  CbmswsController::QuitClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 31. Mai 08:42:10 2012----------*/
void CwsController::QuitClickedSlot()
{
    qApp->quit();
}

void CwsController::ConfigurationClickedSlot() 
{
   CwsServerConfig config(this);
   config.FillDialog();
   config.exec();
   UpdateUiState();
}

void CwsController::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qApp->quit();
}

void CwsController::OpenLogFileClickedSlot() 
{
    CwmsServerSettings cSettings;

   if (cSettings.getLoggingActive())
   {
      QString qstrPath = cSettings.getLoggingPath();

      if (!qstrPath.isEmpty())
      {
         QDesktopServices services;
         services.openUrl(QUrl::fromLocalFile(qstrPath));
      }
   }

   UpdateUiState();
}


void CwsController::InstallClickedSlot()
{
    QString path = QDir::currentPath() + SERVICE_APPLICATION_NAME;
    QString account;
    QString password;
    QString qstrMessage;


    if (QtServiceController::install(path, account, password))
    {
        qstrMessage = tr("Service successfully installed");
    }
    else
    {
        qstrMessage = tr("Service installation failed");
    }

    m_pqleState->setText(qstrMessage);
    m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);
    UpdateUiState();
}

void CwsController::UninstallClickedSlot()
{
    QtServiceController controller(SERVICENAME);

    QString qstrMessage;
    if (controller.uninstall())
    {
        qstrMessage = tr("Service successfully uninstalled");
    }
    else
    {
        qstrMessage = tr("Uninstalling service failed");
    }

    m_pqleState->setText(qstrMessage);
    m_pTrayIcon->showMessage(tr("WMS Application Server Information"), qstrMessage);
    UpdateUiState();
}
