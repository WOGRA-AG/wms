
// System and Qt Incldues

// WMS Includes
#include "IwmsDataAccessPlugin.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsDataAccessConfigurator.h"
#include "CwmsVariantMapEditorWidget.h"
#include "ui_CwmsDataAccessConfigurator.h"

CwmsDataAccessConfigurator::CwmsDataAccessConfigurator(QWidget* p_pqwParent)
    : WMS_BASE_QT_STANDARD_DIALOG,
    ui(new Ui::CwmsDataAccessConfigurator)
{
    ui->setupUi(this);
}

CwmsDataAccessConfigurator::~CwmsDataAccessConfigurator()
{
    delete ui;
}

void CwmsDataAccessConfigurator::FillDialog(QString p_qstrConfigName, QString p_qstrPluginName)
{
    ui->m_pqleDatasourceName->setText(p_qstrConfigName);
    QStringList qstrlPlugins = m_Config.getDataAccessList();
    ui->m_pqcbDatasourceType->addItems(qstrlPlugins);
    ui->m_pqcbDatasourceType->setCurrentText(p_qstrPluginName);
}

void CwmsDataAccessConfigurator::FillConfigData()
{
    IwmsDataAccessPlugin* pPlugin = m_Config.getDataAccessPlugin(ui->m_pqcbDatasourceType->currentText());

    if (pPlugin)
    {
        CwmsVariantMapEditorWidget* pVariantEditor = static_cast<CwmsVariantMapEditorWidget*>(ui->m_pqWidgetStack->currentWidget());

        if (CHKPTR(pVariantEditor))
        {
            QVariantMap qMap = pPlugin->GetConfigurationMap(ui->m_pqleDatasourceName->text());
            pVariantEditor->FillDialog(qMap);
        }
    }
}

void CwmsDataAccessConfigurator::DatasourceTypeChangedSlot()
{
    CwmsVariantMapEditorWidget* pVariantEditor = new CwmsVariantMapEditorWidget(this);
    ui->m_pqWidgetStack->addWidget(pVariantEditor);
    ui->m_pqWidgetStack->setCurrentWidget(pVariantEditor);
    FillConfigData();
}

bool CwmsDataAccessConfigurator::Save()
{
    bool bRet = false;

    CwmsVariantMapEditorWidget* pVariantEditor = static_cast<CwmsVariantMapEditorWidget*>(ui->m_pqWidgetStack->currentWidget());

    if (CHKPTR(pVariantEditor))
    {
        IwmsDataAccessPlugin* pPlugin = m_Config.getDataAccessPlugin(ui->m_pqcbDatasourceType->currentText());

        if (pPlugin)
        {
            QVariantMap qmMap = pVariantEditor->GetVariantMap();
            m_Config.setConfigurationPluginName(ui->m_pqleDatasourceName->text(), ui->m_pqcbDatasourceType->currentText());
            pPlugin->SetConfigurationMap(ui->m_pqleDatasourceName->text(), qmMap);
            bRet = true;
        }
    }

    return bRet;
}

bool CwmsDataAccessConfigurator::Validate()
{
    bool bRet = true;

    if (ui->m_pqleDatasourceName->text().isEmpty())
    {
        bRet = false;
        CdmMessageManager::critical(tr("Validation failed"), tr("Please enter a datasource name."));
    }

    if (ui->m_pqcbDatasourceType->currentText().isEmpty())
    {
        bRet = false;
        CdmMessageManager::critical(tr("Validation failed"), tr("Please select a datasource type."));
    }

    return bRet;
}

void CwmsDataAccessConfigurator::OKClickedSlot()
{
    if (Validate() && Save())
    {
        accept();
    }
}
