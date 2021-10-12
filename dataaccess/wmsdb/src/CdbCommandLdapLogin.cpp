#ifndef WMS_NO_LDAP
// WMS Includes
#include "CdmSettings.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CumUser.h"
#include "CumUserManager.h"

// Own Includes
#include "CdbUserManager.h"
#include "CdbCommandLdapLogin.h"
#include "CdbCommandLicenceCheck.h"
#include "CdbCommandGetNewSession.h"
#include "CwmsLdapUtilities.h"
#ifdef Q_OS_WIN32
#include "CwmsLdapFunctionalitiesWindows.h"
#elif defined Q_OS_LINUX
#include "CwmsLdapFunctionalitiesLinux.h"
#endif

CdbCommandLdapLogin::CdbCommandLdapLogin(QString p_qstrApplication,
                                         QString p_qstrVersion,
                                         QString p_qstrLogin,
                                         QString p_qstrPassword,
                                         CdbDataAccess* p_pDataAccess,
                                         CdbUserManager* p_pUserManager)
    : CdbAbstractCommand(p_pDataAccess),
      m_rpUserManager(p_pUserManager),
      m_qstrApplication(p_qstrApplication),
      m_qstrLogin(p_qstrLogin),
      m_qstrPassword(p_qstrPassword),
      m_qstrVersion(p_qstrVersion),
      m_pUser(nullptr)
{
}

CdbCommandLdapLogin::~CdbCommandLdapLogin()
{

}

int CdbCommandLdapLogin::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownLoginManagerError;
    CdbCommandLicenceCheck command(m_qstrApplication, m_qstrVersion, GetDataAccess());

    if(SUCCESSFULL(command.Run()))
    {
       #ifdef Q_OS_WIN32
            CwmsLdapFassade* func = CwmsLdapFunctionalitiesWindows::instance();
       #elif defined Q_OS_LINUX
            CwmsLdapFassade* func = CwmsLdapFunctionalitiesLinux::instance();
       #endif

       CdmSettings cSettings(eDmSettingsModeClient);

       QString rc = "false"; //pessimistic default
       QString rc2 = "false"; //pessimistic default

       QList<QString> UserInformationFromLdapQuestions;
       QList<QPair<QString,QString> > UserInformationFromLdapAnswers;

       QString host = cSettings.getLdapHost();
       QString port = cSettings.getLdapPort();
       QString dn = cSettings.getLdapBaseDN();
       QString adminDN = cSettings.getLdapAdmin();
       QString apasswd  = cSettings.getLdapPasswd();
       QString BenutzerGruppenName = cSettings.getLdapUserGroup();
       QString AdminGruppenName = cSettings.getLdapAdminGroup();
       bool adminflag = false;
       bool userflag = false;

       QString compMemberOf="memberOf", compEmail="mail", compGivenName="givenName", compSureName="sn";
       QString filter="(&(objectClass=person)(sAMAccountName="+m_qstrLogin+")(!(objectClass=Computer)))";

       //Reihenfolge ist wichtig
       UserInformationFromLdapQuestions.append(compMemberOf);
       UserInformationFromLdapQuestions.append(compGivenName);
       UserInformationFromLdapQuestions.append(compSureName);
       UserInformationFromLdapQuestions.append(compEmail);

       rc = func->checkPasswordwLdap(host,port,dn,adminDN,apasswd,0);

       if(rc != "Erfolg")
       {
           //CdmMessageManager::critical(tr("Fehler beim Verbindungsaufbau mit der Administratorkennung"),
           //tr("Es konnte keine Verbindung mit dem Server aufgebaut werden. Bitte überprüfen Sie die Ldap Verbindungseinstellungen."));
       }
       else
       {
           rc = func->checkPasswordwLdap(host, port, dn, m_qstrLogin ,m_qstrPassword, 0);

           if(rc == "Erfolg")
           {
               rc2 = func->ldap_lookup_with_filter(UserInformationFromLdapQuestions, UserInformationFromLdapAnswers, host, port, dn, adminDN, apasswd, filter);

               if(UserInformationFromLdapAnswers.size() != 0)
               {
                   CwmsLdapUtilities::IsUserInUserGroupOrAdminGroup(UserInformationFromLdapQuestions, UserInformationFromLdapAnswers, AdminGruppenName, BenutzerGruppenName, adminflag, userflag);

                   if(adminflag || userflag)
                   {
                       lRet = EC(eDmOk);
                   }
                   else
                   {
                       //CdmMessageManager::critical(tr("Anmeldung fehlgeschlagen."),
                       //tr("Der Benutzer ist nicht brechtigt sich am System anzumelden. Kontaktieren Sie einen Administrator."));
                   }
               }
               else
               {
                   //CdmMessageManager::critical(tr("Anmeldung fehlgeschlagen."),
                   //tr("Die Suche nach dem Benutzer ergab keinen Treffer oder ist fehlgeschlagen."));
               }
           }
       }

       if (lRet > 0)
       {
          m_pUser = m_rpUserManager->FindUserByLogin(m_qstrLogin, "");
          CumUserManager* pUserManager = CdmSessionManager::GetDataProvider()->GetUserManager();

          if(m_pUser && m_pUser->IsActive())
          {
             CwmsLdapUtilities::updateUserData(pUserManager,
                                              m_pUser,
                                              UserInformationFromLdapQuestions,
                                              UserInformationFromLdapAnswers,
                                              adminflag);

             lRet = GetNewSession();
          }
          else
          {
              CwmsLdapUtilities::createUserData(pUserManager,
                                               UserInformationFromLdapQuestions,
                                               UserInformationFromLdapAnswers,
                                               m_qstrLogin,
                                               m_qstrApplication,
                                               adminflag);

              m_pUser = m_rpUserManager->FindUserByLogin(m_qstrLogin, "");

              if (CHKPTR(m_pUser))
              {
                  lRet = GetNewSession();
              }
              else
              {
                  lRet = EC(eDmSessionCreationError);
              }
          }
       }
   }
   else
   {
      lRet = EC(eDmNoLicenceLeft);
   }


    #ifdef Q_OS_WIN32
         CwmsLdapFunctionalitiesWindows::drop();
    #elif defined Q_OS_LINUX
         CwmsLdapFunctionalitiesLinux::drop();
    #endif

    return static_cast<int>(lRet);

}

CumUser* CdbCommandLdapLogin::GetUser()
{
    return m_pUser;
}

qint64 CdbCommandLdapLogin::GetNewSession()
{
    CdbCommandGetNewSession commandNewSession(m_qstrApplication, m_pUser->GetId(), m_pUser->GetBaseAuth(), GetDataAccess());

   qint64 lRet = commandNewSession.Run();

    if (SUCCESSFULL(lRet))
    {
        lRet = commandNewSession.GetResult();
    }

    return lRet;
}

bool CdbCommandLdapLogin::CheckValid()
{
    return (CHKPTR(m_rpUserManager));
}
#endif
