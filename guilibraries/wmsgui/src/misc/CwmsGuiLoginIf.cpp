/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

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

/** +-=---------------------------------------------------------Thu Dec 18 13:37:17 2003----------*
 * @method  CwmsLoginIf::~CwmsLoginIf                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsLoginIf                                                   *
 *---------------------------------------------------------------Thu Dec 18 13:37:17 2003---------*/
CwmsGuiLoginIf::~CwmsGuiLoginIf(  )
{
   // nothing to be done here
}

/** +-=---------------------------------------------------------Thu Dec 18 15:22:42 2003----------*
 * @method  CwmsLoginIf::CancelClickedSlot                   // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to cancel the login.                       *
 *---------------------------------------------------------------Thu Dec 18 15:22:42 2003---------*/
void CwmsGuiLoginIf::CancelClickedSlot(  )
{
   reject();
   exit(0);
}

/** +-=---------------------------------------------------------Thu Dec 18 15:23:11 2003----------*
 * @method  CwmsLoginIf::OKClickedSlot                       // protected, virtual, slots         *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to login to the system.                    *
 *---------------------------------------------------------------Thu Dec 18 15:23:11 2003---------*/
void CwmsGuiLoginIf::OKClickedSlot(  )
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

/** +-=---------------------------------------------------------Sa 22. Jan 13:14:52 2005----------*
 * @method  CwmsLoginIf::SetCaption                          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment Sets the Caption of the Login Dialog.                                                 *
 *----------------last changed: --------------------------------Sa 22. Jan 13:14:52 2005----------*/
void CwmsGuiLoginIf::SetCaption(  QString p_qstrCaption )
{
   setWindowTitle(p_qstrCaption);
}

/** +-=---------------------------------------------------------Sa 22. Jan 13:16:36 2005----------*
 * @method  CwmsLoginIf::SetApplicationInfoText              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrLoginLabel                         //                                   *
 * @comment Sets the Text of the Login Label.                                                     *
 *----------------last changed: --------------------------------Sa 22. Jan 13:16:36 2005----------*/
void CwmsGuiLoginIf::SetApplicationInfoText(  QString p_qstrLoginLabel )
{
   m_pqlApplicationInfo->setText(p_qstrLoginLabel);
}

/** +-=---------------------------------------------------------Do 29. Dez 13:57:34 2005----------*
 * @method  CwmsLoginIf::Login                               // public, static                    *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrApplicationName                    //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @param   QString p_qstrApplicationInfoText                //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment This static memeber function starts the login screen waits for user input and will    *
 *          do all the stuff for creating a workable WMS, inlcusive communication settings and    *
 *          so on.                                                                                *
 *----------------last changed: Wolfgang Graßhof----------------Do 29. Dez 13:57:34 2005----------*/
bool CwmsGuiLoginIf::Login(QString p_qstrApplicationName,
                           QWidget* p_pqwParent )
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

/** +-=---------------------------------------------------------Fr 9. Mai 19:13:41 2008-----------*
 * @method  CwmsLoginIf::ClientSettingsClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user clicks on the clientsettings button. it          *
 *          opens the clientsettings app.                                                         *
 *----------------last changed: --------------------------------Fr 9. Mai 19:13:41 2008-----------*/
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

/** +-=---------------------------------------------------------Fr 9. Mai 19:13:41 2008-----------*
 * @method  CwmsLoginIf::LdapSettingsClickedSlot           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user clicks on the ldapsettings button. it          *
 *          opens the ldapsettings app.                                                         *
 *----------------last changed: --------------------------------Fr 9. Mai 19:13:41 2008-----------*/
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
