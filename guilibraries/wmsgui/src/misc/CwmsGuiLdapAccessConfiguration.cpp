
#include "CwmsGuiLdapAccessConfiguration.h"
#include "ui_CwmsGuiLdapAccessConfiguration.h"

CwmsGuiLdapAccessConfiguration::CwmsGuiLdapAccessConfiguration(CdmSettings *m_cCdmSettings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsGuiLdapAccessConfigurationClass)
{
    this->m_cCdmSettings = m_cCdmSettings;
    ui->setupUi(this);

    if(m_cCdmSettings->getIsLdapActive())
    {
        ui->lActive->setChecked(true);
    }
    else
    {
        ui->lActive->setChecked(false);
    }

    if(m_cCdmSettings->getIsLdapConfigured())
    {
        this->loadSettings();
    }

}

CwmsGuiLdapAccessConfiguration::~CwmsGuiLdapAccessConfiguration()
{
    delete ui;
    this->m_cCdmSettings = nullptr;

}

void CwmsGuiLdapAccessConfiguration::doTest(){

    QString host = ui->InputHost->text();
    QString port = ui->InputPort->text();
    QString dn = ui->InputBaseDN->text();
    QString adminDN = ui->InputAdminDN->text();
    QString passwd  = ui->InputPasswd->text();

    //TEST FUNCTION NOT IMPLEMENTED
    //QString rc = func->checkPasswordwLdap(host,port,dn,adminDN,passwd,0);
    //ui->Status->setText("Status: "+rc);

}

void CwmsGuiLdapAccessConfiguration::doSave(){

    this->saveSettings();
    accept();
}

void CwmsGuiLdapAccessConfiguration::doCancel(){

    reject();
}

void CwmsGuiLdapAccessConfiguration::loadSettings()
{
    bool sIsLdapActive = m_cCdmSettings->getIsLdapActive();
    ui->lActive->setChecked(sIsLdapActive);

    QString sInputHost = m_cCdmSettings->getLdapHost();
    ui->InputHost->setText(sInputHost);

    QString sInputPort = m_cCdmSettings->getLdapPort();
    ui->InputPort->setText(sInputPort);

    QString sInputBaseDN = m_cCdmSettings->getLdapBaseDN();
    ui->InputBaseDN->setText(sInputBaseDN);

    QString sInputAdminDN = m_cCdmSettings->getLdapAdmin();
    ui->InputAdminDN->setText(sInputAdminDN);

    QString sInputPasswd = m_cCdmSettings->getLdapPasswd();
    ui->InputPasswd->setText(sInputPasswd);

    QString sInputAdminGroup =  m_cCdmSettings->getLdapAdminGroup();
    ui->inputAdminGroup->setText(sInputAdminGroup);

    QString sInputUserGroup =  m_cCdmSettings->getLdapUserGroup();
    ui->inputUserGroup->setText(sInputUserGroup);
}

void CwmsGuiLdapAccessConfiguration::saveSettings()
{
    bool sIsLdapActive = ui->lActive->isChecked();
    m_cCdmSettings->setIsLdapActive(sIsLdapActive);

    QString sInputHost = (ui->InputHost) ? ui->InputHost->text() : "";
    m_cCdmSettings->setLdapHost(sInputHost);

    QString sInputPort = (ui->InputPort) ? ui->InputPort->text() : "";
    m_cCdmSettings->setLdapPort(sInputPort);

    QString sInputBaseDN = (ui->InputBaseDN) ? ui->InputBaseDN->text() : "";
    m_cCdmSettings->setLdapBaseDN(sInputBaseDN);

    QString sInputAdminDN = (ui->InputAdminDN) ? ui->InputAdminDN->text() : "";
    m_cCdmSettings->setLdapAdmin(sInputAdminDN);

    QString sInputPasswd = (ui->InputPasswd) ? ui->InputPasswd->text() : "";
    m_cCdmSettings->setLdapPasswd(sInputPasswd);

    QString sInputAdminGroup = (ui->inputAdminGroup) ? ui->inputAdminGroup->text() : "";
    m_cCdmSettings->setLdapAdminGroup(sInputAdminGroup);

    QString sInputUserGroup = (ui->inputUserGroup) ? ui->inputUserGroup->text() : "";
    m_cCdmSettings->setLdapUserGroup(sInputUserGroup);

    bool sIsLdapConfigured = true;
    m_cCdmSettings->setIsLdapConfigured(sIsLdapConfigured);

}

