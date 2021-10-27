// System and Qt Includes
#include <QSettings>
#include <QFileDialog>

// WMS Commons Include
#include "CwmsSettingsStoreFactory.h"
#include "wmsdefines.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CwmsContext.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "CdmMessageManager.h"
#include "CwmsPluginsDlg.h"
#include "CwmsTreeWidgetHelper.h"
#include "CdmSessionManager.h"

// Basetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwsServerConfig.h"
#include "ui_CwsServerConfig.h"

CwsServerConfig::CwsServerConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwsServerConfig),
    m_pSettings(nullptr)
{
    m_pSettings = CwmsSettingsStoreFactory::GenerateServerSettings();
    ui->setupUi(this);
}

CwsServerConfig::~CwsServerConfig()
{
    CwmsContext::GetContext()->ServerLogout();
    delete ui;
    delete m_pSettings;
}


void CwsServerConfig::FillDialog()
{
    if (CwmsContext::GetContext()->ServerLogin())
    {
        FillPlugins();
    }

    // Daemon Configs
    ui->m_pqchbSimulateProcessManagement->setChecked(m_pSettings->value(SIMULATE_PROCESSMANAGEMENT, SIMULATE_PROCESSMANAGEMENT_VALUE).toBool());
    ui->m_pqsbBestSwitching->setValue(m_pSettings->value(BEST_SWITCHINGHOUR_START, DEFAULT_BEST_SWITCHINGHOUR_START).toInt());
    ui->m_pqsbBestSwitchingEnd->setValue(m_pSettings->value(BEST_SWITCHINGHOUR_END, DEFAULT_BEST_SWITCHINGHOUR_END).toInt());
    ui->m_pqsbMaxProcessMemoryUsage->setValue(m_pSettings->value(MAX_MEM_USAGE_MB, MAX_MEM_USAGE_MB_VALUE).toInt());
    ui->m_pqsbMaxServerAge->setValue(m_pSettings->value(DEFAULT_MAX_SERVER_AGE_HOURS, DEFAULT_MAX_SERVER_AGE_HOURS_VALUE).toInt());
    ui->m_pqsbProcessHealthCheckIntervall->setValue(m_pSettings->value(HEALTH_CHECK_INTERVALL, HEALTH_CHECK_INTERVALL_VALUE).toInt());
    ui->m_pqchbSchemeBasedUserManagement->setChecked(m_pSettings->value(SCHEME_BASED_USERMANAGEMENT, SCHEME_BASED_USERMANAGEMENT_VALUE).toBool());

    // Application Server Configs
    ui->m_pqchbZipCompression->setChecked(m_pSettings->value(ZIP_COMPRESSION, ZIP_COMPRESSION_VALUE).toBool());
    ui->m_pqleApplicationExecutablePath->setText(m_pSettings->value(SERVER_CONFIG_NAME, SERVER_APP_NAME_VALUE).toString());
    ui->m_pqsbMaxConnection->setValue(m_pSettings->value(MAX_CONNECTIONS, MAX_CONNECTIONS_VALUE).toInt());
    ui->m_pqsbThreads->setValue(m_pSettings->value(MAX_THREADS, MAX_THREADS_VALUE).toInt());
    ui->m_pqsbSessionTimeout->setValue(m_pSettings->value(SESSION_TIMEOUT, SESSION_TIMEOUT_VALUE).toInt());

    // Ports
    ui->m_pqsbSecondaryApplicationPort->setValue(m_pSettings->value(SECONDRAY_PORT, SECONDRAY_PORT_VALUE).toInt());
    ui->m_pqsbSecondaryMaintenancePort->setValue(m_pSettings->value(MAINTENANCE_SECONDARY_PORT, MAINTENANCE_SECONDARY_PORT_VALUE).toInt());
    ui->m_pqsbPrimaryApplicationPort->setValue(m_pSettings->value(PRIMARY_PORT, PRIMARY_PORT_VALUE).toInt());
    ui->m_pqsbPrimaryMaintenancePort->setValue(m_pSettings->value(MAINTENANCE_PRIMARY_PORT, MAINTENANCE_PRIMARY_PORT_VALUE).toInt());
    ui->m_pqsbDaemonPort->setValue(m_pSettings->value(DAEMON_SERVER_PORT, DAEMON_SERVER_PORT_VALUE).toInt());
    ui->m_pqsbMaintenancePort->setValue(m_pSettings->value(MAINTENANCE_PORT, DEFAULT_MAINTENANCE_SERVER_PORT).toInt());

    // User Data
    ui->m_pqleServerAdmin->setText(m_pSettings->value(SERVER_USER, ADMIN_STRING).toString());
    ui->m_pqleServerUser->setText(m_pSettings->value(SERVER_USER_PASSWORD, ADMIN_STRING).toString());

    //Logging
    ui->m_pqleApplicationLoggingPath->setText(m_pSettings->value(APPLICATION_LOGGING_PATH, "").toString());
    ui->m_pqleDaemonLogPath->setText(m_pSettings->value(DAEMON_LOGGING_PATH, DAEMON_LOGGING_PATH_VALUE).toString());
    ui->m_pqgbApplicationServerLogging->setChecked(m_pSettings->value(APPLICATION_LOGGING_ACTIVE, true).toBool());
    ui->m_pqgbDaemonServerLogging->setChecked(m_pSettings->value(DAEMON_LOGGING_ACTIVE, true).toBool());
    ui->m_pqchbApplicationSeverityError->setChecked(m_pSettings->value(APPLICATION_LOGGING_ERROR, true).toBool());
    ui->m_pqchbApplicationSeverityFatal->setChecked(m_pSettings->value(APPLICATION_LOGGING_FATAL, true).toBool());
    ui->m_pqchbApplicationSeverityInfo->setChecked(m_pSettings->value(APPLICATION_LOGGING_INFO, false).toBool());
    ui->m_pqchbApplicationSeverityWarning->setChecked(m_pSettings->value(APPLICATION_LOGGING_WARNING, false).toBool());
    ui->m_pqchbDaemonSeverityError->setChecked(m_pSettings->value(DAEMON_LOGGING_ERROR, true).toBool());
    ui->m_pqchbDaemonSeverityFatal->setChecked(m_pSettings->value(DAEMON_LOGGING_FATAL, true).toBool());
    ui->m_pqchbDaemonSeverityInfo->setChecked(m_pSettings->value(DAEMON_LOGGING_INFO, false).toBool());
    ui->m_pqchbDaemonSeverityWarning->setChecked(m_pSettings->value(DAEMON_LOGGING_WARNING, false).toBool());

    // URL Config
    QString qstrHost = m_pSettings->value(WMS_URL_SERVER_HOST, "").toString();
    ui->m_pqleServerHost->setText(qstrHost);
    ui->m_pqleServerPath->setText(m_pSettings->value(WMS_URL_SERVER_PATH, "").toString());
    ui->m_pqsbServerPort->setValue(m_pSettings->value(WMS_URL_SERVER_PORT, 0).toInt());
}


bool CwsServerConfig::Validate()
{
    return true;
}


bool CwsServerConfig::Save()
{
    m_pSettings->setValue(SIMULATE_PROCESSMANAGEMENT,ui->m_pqchbSimulateProcessManagement->isChecked());
    m_pSettings->setValue(ZIP_COMPRESSION,ui->m_pqchbZipCompression->isChecked());
    m_pSettings->setValue(SERVER_CONFIG_NAME,ui->m_pqleApplicationExecutablePath->text());
    m_pSettings->setValue(APPLICATION_LOGGING_PATH,ui->m_pqleApplicationLoggingPath->text());
    m_pSettings->setValue(DAEMON_LOGGING_PATH,ui->m_pqleDaemonLogPath->text());
    m_pSettings->setValue(SERVER_USER,ui->m_pqleServerAdmin->text());
    m_pSettings->setValue(SERVER_USER_PASSWORD,ui->m_pqleServerUser->text());
    m_pSettings->setValue(DAEMON_SERVER_PORT,ui->m_pqsbDaemonPort->value());
    m_pSettings->setValue(BEST_SWITCHINGHOUR_START,ui->m_pqsbBestSwitching->value());
    m_pSettings->setValue(BEST_SWITCHINGHOUR_END,ui->m_pqsbBestSwitchingEnd->value());
    m_pSettings->setValue(MAINTENANCE_PORT,ui->m_pqsbMaintenancePort->value());
    m_pSettings->setValue(MAX_CONNECTIONS,ui->m_pqsbMaxConnection->value());
    m_pSettings->setValue(MAX_MEM_USAGE_MB,ui->m_pqsbMaxProcessMemoryUsage->value());
    m_pSettings->setValue(DEFAULT_MAX_SERVER_AGE_HOURS,ui->m_pqsbMaxServerAge->value());
    m_pSettings->setValue(PRIMARY_PORT,ui->m_pqsbPrimaryApplicationPort->value());
    m_pSettings->setValue(MAINTENANCE_PRIMARY_PORT,ui->m_pqsbPrimaryMaintenancePort->value());
    m_pSettings->setValue(HEALTH_CHECK_INTERVALL,ui->m_pqsbProcessHealthCheckIntervall->value());
    m_pSettings->setValue(SECONDRAY_PORT,ui->m_pqsbSecondaryApplicationPort->value());
    m_pSettings->setValue(MAINTENANCE_SECONDARY_PORT,ui->m_pqsbSecondaryMaintenancePort->value());
    m_pSettings->setValue(MAX_THREADS,ui->m_pqsbThreads->value());
    m_pSettings->setValue(SESSION_TIMEOUT,ui->m_pqsbSessionTimeout->value());
    m_pSettings->setValue(APPLICATION_LOGGING_ACTIVE, ui->m_pqgbApplicationServerLogging->isChecked());
    m_pSettings->setValue(DAEMON_LOGGING_ACTIVE, ui->m_pqgbDaemonServerLogging->isChecked());
    m_pSettings->setValue(APPLICATION_LOGGING_ERROR, ui->m_pqchbApplicationSeverityError->isChecked());
    m_pSettings->setValue(APPLICATION_LOGGING_FATAL, ui->m_pqchbApplicationSeverityFatal->isChecked());
    m_pSettings->setValue(APPLICATION_LOGGING_INFO, ui->m_pqchbApplicationSeverityInfo->isChecked());
    m_pSettings->setValue(APPLICATION_LOGGING_WARNING, ui->m_pqchbApplicationSeverityWarning->isChecked());
    m_pSettings->setValue(DAEMON_LOGGING_ERROR, ui->m_pqchbDaemonSeverityError->isChecked());
    m_pSettings->setValue(DAEMON_LOGGING_FATAL, ui->m_pqchbDaemonSeverityFatal->isChecked());
    m_pSettings->setValue(DAEMON_LOGGING_INFO, ui->m_pqchbDaemonSeverityInfo->isChecked());
    m_pSettings->setValue(DAEMON_LOGGING_WARNING, ui->m_pqchbDaemonSeverityWarning->isChecked());
    m_pSettings->setValue(SCHEME_BASED_USERMANAGEMENT, ui->m_pqchbSchemeBasedUserManagement->isChecked());

    // URL Config
    QString qstrHost = ui->m_pqleServerHost->text();
    m_pSettings->setValue(WMS_URL_SERVER_HOST, qstrHost);
    m_pSettings->setValue(WMS_URL_SERVER_PATH, ui->m_pqleServerPath->text());
    m_pSettings->setValue(WMS_URL_SERVER_PORT, ui->m_pqsbServerPort->value());

    m_pSettings->sync();
    return true;
}

void CwsServerConfig::OKClickedSlot()
{
    if (Validate() && Save())
    {
        accept();
    }
}

void CwsServerConfig::ServerExecutableClickedSlot()
{
    QString qstrFile = QFileDialog::getOpenFileName(this, "Please select server executable", "", "*");

    if (!qstrFile.isEmpty())
    {
       ui->m_pqleApplicationExecutablePath->setText(qstrFile);
    }

}

void CwsServerConfig::DataAccessClickedSlot()
{
    CwmsGuiDataAccessConfiguration* pEditor = new CwmsGuiDataAccessConfiguration();
    pEditor->FillDialog();

    if (QDialog::Accepted == pEditor->exec())
    {
        MSG_INFO(("Einstellungen geändert"),
            ("Die Einstellungen wurden geändert"));
    }

    delete pEditor;
}

void CwsServerConfig::ApplicationLogPathClickedSlot()
{
    QString qstrFile = QFileDialog::getSaveFileName(this, "Please select Application Server Logfile", "", "*.log");

    if (!qstrFile.isEmpty())
    {
       ui->m_pqleApplicationLoggingPath->setText(qstrFile);
    }
}

void CwsServerConfig::DaemonLogPathClickedSlot()
{
    QString qstrFile = QFileDialog::getSaveFileName(this, "Please select Daemon Server Logfile", "", "*.log");

    if (!qstrFile.isEmpty())
    {
       ui->m_pqleDaemonLogPath->setText(qstrFile);
    }
}

void CwsServerConfig::FillPlugins()
{
    CdmObjectContainer* pContainer = nullptr;
    CwmsContext* pContext = CwmsContext::GetContext();

    if (pContext)
    {
        CwmsPluginManager* pPluginManager = pContext->GetPluginManager();

        if (pPluginManager)
        {
            pContainer = pPluginManager->GetServerPluginContainer();

            if (pContainer)
            {
                ui->m_pCwmsPlugins->FillWidgetServer(pContainer);
            }
        }
    }
}

void CwsServerConfig::OptionSelectedSlot()
{
    QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(ui->m_pqtwOptions);

    if (pItem)
    {
        ui->m_pqWidgetStack->setCurrentIndex(ui->m_pqtwOptions->indexOfTopLevelItem(pItem));
    }
}
