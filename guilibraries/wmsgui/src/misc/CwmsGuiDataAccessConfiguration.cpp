
// System and Qt Includes
#include <QMessageBox>

// WMS Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "IwmsDataAccessPlugin.h"

// Own Includes
#include "CwmsDataAccessConfigurator.h"
#include "CwmsTreeWidgetHelper.h"
#include "CwmsVariantMapEditor.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "ui_CwmsGuiDataAccessConfiguration.h"


CwmsGuiDataAccessConfiguration::CwmsGuiDataAccessConfiguration(QWidget* p_pqwParent)
    : WMS_BASE_QT_STANDARD_DIALOG,
      ui(new Ui::CwmsGuiDataAccessConfigurationUi)
{
    ui->setupUi(this);
}

CwmsGuiDataAccessConfiguration::~CwmsGuiDataAccessConfiguration()
{
    delete ui;
}

void CwmsGuiDataAccessConfiguration::FillDialog()
{
    m_Config.getDataAccessList();
    ui->m_pqcbConfig->clear();
    ui->m_pqtwConfigurations->clear();

    QStringList qstrlConfig = m_Config.getConfigurationList();

    for (int iCounter = 0; iCounter < qstrlConfig.size(); ++iCounter)
    {
        QTreeWidgetItem* pItem = new QTreeWidgetItem(ui->m_pqtwConfigurations);
        pItem->setText(0, qstrlConfig[iCounter]);
    }

    ui->m_pqcbConfig->addItems(qstrlConfig);
    ui->m_pqcbConfig->setCurrentIndex(ui->m_pqcbConfig->findText(m_Config.ReadConfigName()));
}

void CwmsGuiDataAccessConfiguration::NewClickedSlot()
{
    CwmsDataAccessConfigurator cConfigurator(this);
    cConfigurator.FillDialog(QString(), QString());

    if (cConfigurator.exec() == QDialog::Accepted)
    {
        FillDialog();
    }
}

void CwmsGuiDataAccessConfiguration::EditClickedSlot()
{
    QString qstrConfig = GetSelectedTreeConfig();

    if (!qstrConfig.isEmpty())
    {
        QString qstrPlugin = m_Config.getConfigurationPluginName(qstrConfig);
        CwmsDataAccessConfigurator cConfigurator(this);
        cConfigurator.FillDialog(qstrConfig, qstrPlugin);

        if (cConfigurator.exec() == QDialog::Accepted)
        {
            FillDialog();
        }

        //OpenPluginEditor(qstrConfig, qstrPlugin);
    }
}

void CwmsGuiDataAccessConfiguration::OpenPluginEditor(QString p_qstrConfig, QString p_qstrPlugin)
{
    IwmsDataAccessPlugin* pPlugin = m_Config.getDataAccessPlugin(p_qstrPlugin);

    if (pPlugin)
    {
        CwmsVariantMapEditor* pEditor = new CwmsVariantMapEditor(this);
        QVariantMap qMap = pPlugin->GetConfigurationMap(p_qstrConfig);
        pEditor->FillDialog(qMap);

        if (pEditor->exec() == QDialog::Accepted)
        {
            qMap = pEditor->GetVariantMap();
            pPlugin->SetConfigurationMap(p_qstrConfig, qMap);
            FillDialog();
        }

        DELPTR(pEditor)
    }
    else
    {
        ERR(tr("Plugin nicht gefunden."))
    }
}

void CwmsGuiDataAccessConfiguration::DeleteClickedSlot()
{
    QString qstrConfig = GetSelectedTreeConfig();

    if (!qstrConfig.isEmpty())
    {
        if (QMessageBox::question(this, tr("Wirklich löschen?"), tr("Wollen Sie die Konfiguraiton wirklich löschen?")) == QMessageBox::Yes)
        {
            m_Config.deleteConfiguration(qstrConfig);
        }
    }

    FillDialog();
}

QString CwmsGuiDataAccessConfiguration::GetSelectedTreeConfig()
{
    QString qstrConfig;
    QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(ui->m_pqtwConfigurations);

    if (pItem)
    {
        qstrConfig = pItem->text(0);
    }
    else
    {
        QMessageBox::critical(this, tr("Keine Auswahl vorhanden"), tr("Es wurde keine Auswahl getroffen.\nBearbeiten nicht möglich."));
    }

    return qstrConfig;
}

void CwmsGuiDataAccessConfiguration::TestClickedSlot()
{
    QString qstrConfig = ui->m_pqcbConfig->currentText();
    m_Config.testConfig(qstrConfig);
}

void CwmsGuiDataAccessConfiguration::OkClickedSlot()
{
    QString qstrConfig = ui->m_pqcbConfig->currentText();

    if (!qstrConfig.isEmpty())
    {
        m_Config.SetConfigName(qstrConfig);
        accept();
    }
    else
    {
        QMessageBox::critical(this, tr("Kein Datenzugriff gewählt"), tr("Es wurde keine aktuelle Konfiguration für das System gewählt."));
    }
}
