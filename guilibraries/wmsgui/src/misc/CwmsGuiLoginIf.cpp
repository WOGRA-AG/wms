// WMS Includes
#include "wmsdefines.h"
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// WMS QML Includes
#include "CwmsQmlLogin.h"

// own Includes
#include "CwmsGuiLdapAccessConfiguration.h"
#include "CwmsGuiDataAccessConfiguration.h"
#include "CwmsGuiLoginIf.h"

// defines
#define SINGLE_SIGN_ON 1

CwmsGuiLoginIf::CwmsGuiLoginIf(QString p_qstrAppliactionName, QWidget* p_pqwParent)
    : WMS_BASE_QT_STANDARD_DIALOG,
      m_cCdmSettings(eDmSettingsModeClient),
      m_qSettings(QSettings::UserScope, QStringLiteral("WOGRA"), QStringLiteral("WMS")),
      m_qstrApplicationName(p_qstrAppliactionName)
{
   setupUi(this);

   if (SINGLE_SIGN_ON == 0)
   {
       m_pqchbStoreLogin->setChecked(false);
       m_pqchbStoreLogin->hide();
   }
   else
   {
       m_pqchbStoreLogin->setChecked(m_qSettings.value(STORE_WMS_LOGIN).toBool());
   }

   p_qstrAppliactionName = p_qstrAppliactionName.replace(QStringLiteral("_"), QStringLiteral(" "));
   m_pqlApplicationInfo->setText(p_qstrAppliactionName);
   setWindowTitle(p_qstrAppliactionName + " Anmeldung");

   if (m_pqchbStoreLogin->isChecked())
   {
      m_pqleLogin->setText(m_qSettings.value(WMS_LOGIN).toString());
      m_pqlePassword->setText(m_qSettings.value(PASSWORD).toString());
      m_pqlePassword->setFocus();
   }
}

CwmsGuiLoginIf::~CwmsGuiLoginIf()
{
   // nothing to be done here
}

void CwmsGuiLoginIf::CancelClickedSlot()
{
   reject();
   exit(0);
}

void CwmsGuiLoginIf::OKClickedSlot()
{
   if (m_pqchbStoreLogin->isChecked())
   {
       m_qSettings.setValue(STORE_WMS_LOGIN, m_pqchbStoreLogin->isChecked());
       m_qSettings.setValue(WMS_LOGIN, m_pqleLogin->text());
       m_qSettings.setValue(PASSWORD, m_pqlePassword->text());
   }
   else
   {
       m_qSettings.setValue(STORE_WMS_LOGIN, false);
       m_qSettings.setValue(WMS_LOGIN, "");
       m_qSettings.setValue(PASSWORD, "");
   }

   accept();
}

void CwmsGuiLoginIf::SetCaption(QString p_qstrCaption)
{
   setWindowTitle(p_qstrCaption);
}

void CwmsGuiLoginIf::SetApplicationInfoText(QString p_qstrLoginLabel)
{
   m_pqlApplicationInfo->setText(p_qstrLoginLabel);
}

bool CwmsGuiLoginIf::Login(QString p_qstrApplicationName,
                           QWidget* p_pqwParent)
{
    bool bRet = false;
    bool bAccepted = true;
    CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    CwmsGuiLoginIf* pCwmsLoginIf = new CwmsGuiLoginIf(p_qstrApplicationName, p_pqwParent);
    bRet = TryLogin(pCwmsLoginIf->m_pqleLogin->text(), pCwmsLoginIf->m_pqlePassword->text(), p_qstrApplicationName, pCwmsLoginIf);

    int iTrials = 0;
    int iMaxTrials = 2;

    while (bAccepted && !bRet)
    {
        if (pCwmsLoginIf->exec() == QDialog::Accepted)
        {
            bAccepted = true;

            bRet = TryLogin(pCwmsLoginIf->m_pqleLogin->text(), pCwmsLoginIf->m_pqlePassword->text(), p_qstrApplicationName, pCwmsLoginIf);
            ++iTrials;

            if (!bRet)
            {
                if (iTrials > iMaxTrials)
                {
                    CdmMessageManager::information(tr("Login fehlgeschlagen"), tr("Login fehlgeschlagen. Zu viele Fehlversuche die Anwendung wird beendet."));
                    break;
                }
                else
                {
                    CdmMessageManager::information(tr("Fehler bei der Authentifizierung"), tr("Ungültiger Benutzername oder falsches Passwort"));
                }
            }
        }
        else
        {
            bAccepted = false;
        }
    }

    DELPTR(pCwmsLoginIf)
    return bRet;
}

bool CwmsGuiLoginIf::TryLogin(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrApplicationName, CwmsGuiLoginIf* pCwmsLoginIf)
{
    bool bRet = false;

    if (pCwmsLoginIf && pCwmsLoginIf->m_cCdmSettings.getIsLdapActive() && pCwmsLoginIf->m_cCdmSettings.getIsLdapConfigured())
    {
        bRet = pCwmsLoginIf->LdapLogin(p_qstrLogin,
                                       p_qstrPassword);

    }
    else
    {
        bRet = CwmsQmlLogin::loginP(p_qstrApplicationName,
                                    p_qstrLogin,
                                    p_qstrPassword);
    }

    return bRet;
}

void CwmsGuiLoginIf::ClientSettingsClickedSlot()
{
    CwmsGuiDataAccessConfiguration* pEditor = new CwmsGuiDataAccessConfiguration();
    pEditor->FillDialog();

    if (QDialog::Accepted == pEditor->exec())
    {
        CdmMessageManager::information(tr("Einstellungen übernommen"), tr("Die Einstellungen wurden übernommen."));
    }

    DELPTR(pEditor)
}

void CwmsGuiLoginIf::LdapSettingsClickedSlot()
{
    CwmsGuiLdapAccessConfiguration* lEditor = new CwmsGuiLdapAccessConfiguration(&m_cCdmSettings, nullptr);
    //lEditor->FillDialog();

    if (QDialog::Accepted == lEditor->exec())
    {
        CdmMessageManager::information(tr("Einstellungen übernommen"), tr("Die Einstellungen wurden übernommen."));
    }

    DELPTR(lEditor)
}

bool CwmsGuiLoginIf::LdapLogin(QString username, QString passwd)
{
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR((pSessionManager)))
    {
        int iRet = pSessionManager->CreateNewSessionLdap(username, passwd);
        return (iRet > 0);
    }
    else
    {
        return false;
    }
}
