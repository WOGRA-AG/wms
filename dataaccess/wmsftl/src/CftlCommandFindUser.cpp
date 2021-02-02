
// WMS Includes
#include "CumUser.h"

// Own includes
#include "CftlCommandFindUser.h"

CftlCommandFindUser::CftlCommandFindUser(long p_lUserId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lUserId(p_lUserId)
{
}

CftlCommandFindUser::CftlCommandFindUser(QString p_qstrValue, bool p_bEmail, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
    if (p_bEmail)
    {
        m_qstrEmail = p_qstrValue;
    }
    else
    {
        m_qstrLogin = p_qstrValue;
    }
}

CftlCommandFindUser::CftlCommandFindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrLogin(p_qstrLogin),
      m_qstrPassword(p_qstrPassword),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CftlCommandFindUser::CftlCommandFindUser(QString p_qstrIdentKey, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrIdentKey(p_qstrIdentKey),
      m_qstrSchemeUri(p_qstrSchemeUri)
{

}

CftlCommandFindUser::~CftlCommandFindUser()
{

}

int CftlCommandFindUser::Execute()
{
    int iRet = 0;
    EncryptAllPasswords();

    if (m_lUserId > 0)
    {
        iRet = FindUserById();
    }
    else if (!m_qstrEmail.isEmpty())
    {
        iRet = FindUserByEmail();
    }
    else if (!m_qstrLogin.isEmpty() && !m_qstrPassword.isEmpty())
    {
        iRet = FindUserByLoginAndPassword();
    }
    else if (!m_qstrLogin.isEmpty())
    {
        iRet = FindUserByLogin();
    }
    else if (!m_qstrIdentKey.isEmpty())
    {
        iRet = FindUserByIdentityKey();
    }

    return iRet;
}

bool CftlCommandFindUser::NeedsSessionCheck()
{
    return false;
}

QString CftlCommandFindUser::CreateSelectPart()
{
    return "select UserId, FirstName, LastName, Login, Email, Pass, Admin, Active, Encrypted from WMS_UM_USER ";
}

QString CftlCommandFindUser::GenerateJoin()
{
    return "left join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsuser.UserId = wmsscheme.AccessorId where ((wmsscheme.SchmeUri is null and wmsuser.SchemeIndependent = 1) or "
           "wmsscheme.SchmeUri = ?) and ";
}

int CftlCommandFindUser::FindUserById()
{
   int iRet = CdmLogging::eDmUnknownUserQueryError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   cQSqlQuery.prepare(CreateSelectPart() + " where UserId = ?");
   cQSqlQuery.addBindValue((int)m_lUserId);

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         CreateUserObjectFromQuery(cQSqlQuery);
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No user found with Id " + QString::number(m_lUserId));
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

    return iRet;
}

void CftlCommandFindUser::CreateUserObjectFromQuery(QSqlQuery& p_rQuery)
{
    m_rpUser = new CumUser(p_rQuery.value(0).toInt(), nullptr);

    // the value at position 0 is the user id and not needed here
    // Value in col 1 is SurName
    // Value in col 2 is Name
    // Value in col 3 is Login
    // Value in col 4 is Email
    // Value in col 5 is Password

    m_rpUser->SetFirstName(p_rQuery.value(1).toString());
    m_rpUser->SetLastName(p_rQuery.value(2).toString());
    m_rpUser->SetLogin(p_rQuery.value(3).toString());
    m_rpUser->SetEmail(p_rQuery.value(4).toString());
    m_rpUser->SetPassword(p_rQuery.value(5).toString());
    m_rpUser->SetAdministrator(p_rQuery.value(6).toBool());
    m_rpUser->SetActive(p_rQuery.value(7).toBool());
    m_rpUser->SetEncrypted(p_rQuery.value(8).toBool());
}

int CftlCommandFindUser::FindUserByLogin()
{
   int iRet = CdmLogging::eDmUnknownUserQueryError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());

   if (!m_qstrSchemeUri.isEmpty())
   {
       cQSqlQuery.prepare(CreateSelectPart() + GenerateJoin() + " Login = ?");
       cQSqlQuery.addBindValue(m_qstrSchemeUri);
   }
   else
   {
       cQSqlQuery.prepare(CreateSelectPart() + " where Login = ?");
   }

   cQSqlQuery.addBindValue(m_qstrLogin);

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         CreateUserObjectFromQuery(cQSqlQuery);
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No user found with Login " + m_qstrLogin);
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

    return iRet;
}

int CftlCommandFindUser::FindUserByLoginAndPassword()
{
   int iRet = CdmLogging::eDmUnknownUserQueryError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());

   if (!m_qstrSchemeUri.isEmpty())
   {
       cQSqlQuery.prepare(CreateSelectPart() + GenerateJoin() + " Login = ?");
       cQSqlQuery.addBindValue(m_qstrSchemeUri);
   }
   else
   {
       cQSqlQuery.prepare(CreateSelectPart() + " where Login = ?");
   }

   cQSqlQuery.addBindValue(m_qstrLogin);

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
         QString qstrPassword = cQSqlQuery.value(5).toString();
         QString qstrPasswordEntered;
         QString qstrTest;

         if(cQSqlQuery.value(8).toBool())
         {
            qstrPasswordEntered = CwmsUtilities::EncryptPassword(m_qstrPassword);
            qstrTest =  CwmsUtilities::EncryptPassword(m_qstrPassword);
         }

         if (qstrPassword == qstrPasswordEntered)
         {
             CreateUserObjectFromQuery(cQSqlQuery);
             iRet = EC(eDmOk);
         }
         else
         {
            iRet = EC(CdmLogging::eDmFalse);
            INFO("Invalid Password for user" +m_qstrLogin + " and Password " + m_qstrPassword);
         }
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No user found with login " +m_qstrLogin + " and Password " + m_qstrPassword);
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }


    return iRet;
}

int CftlCommandFindUser::FindUserByEmail()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    if (!m_qstrSchemeUri.isEmpty())
    {
        cQSqlQuery.prepare(CreateSelectPart() + GenerateJoin() + " Email = ?");
        cQSqlQuery.addBindValue(m_qstrSchemeUri);
    }
    else
    {
        cQSqlQuery.prepare(CreateSelectPart() + " where Email = ?");
    }

    cQSqlQuery.addBindValue(m_qstrEmail);

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         CreateUserObjectFromQuery(cQSqlQuery);
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No user found with Email " + m_qstrEmail);
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

   return iRet;
}

CumUser *CftlCommandFindUser::GetResult()
{
    return m_rpUser;
}

bool CftlCommandFindUser::CheckValid()
{
    return (m_lUserId > 0 || !m_qstrEmail.isEmpty() || !m_qstrLogin.isEmpty() || !m_qstrIdentKey.isEmpty());
}


void CftlCommandFindUser::EncryptAllPasswords()
{
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   cQSqlQuery.prepare("select UserId, Pass from WMS_UM_USER where encrypted = 0 or encrypted is null");

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      QMap<long, QString> qmEncryptedPasswords;
      if(cQSqlQuery.isValid())
      {
         do // loading each password and converting it
         {
            long     lId                = cQSqlQuery.value(0).toInt();
            QString qstrPassword        = cQSqlQuery.value(1).toString();
            qmEncryptedPasswords.insert(lId, CwmsUtilities::EncryptPassword(qstrPassword));
         }
         while(cQSqlQuery.next());

         QMap<long, QString>::iterator qmIt = qmEncryptedPasswords.begin();
         QMap<long, QString>::iterator qmItEnd = qmEncryptedPasswords.end();

         for (; qmIt != qmItEnd; ++qmIt) // update passwords in db
         {
            QSqlQuery cQSqlQueryTemp(GetSqlDatabase());
            cQSqlQueryTemp.prepare("update WMS_UM_USER set pass = ?, encrypted = 1 where userid = ?");
            cQSqlQueryTemp.addBindValue(qmIt.value());
            cQSqlQueryTemp.addBindValue((int)qmIt.key());

            if(!SUCCESSFULL(ExecuteQuery(cQSqlQueryTemp)))
            {
               ERR("Error while updating password.");
            }
         }
      }
   }
   else
   {
      ERR("Old Databaseversion this version will not work with this version of WMS.");
   }
}

int CftlCommandFindUser::FindUserByIdentityKey()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    if (!m_qstrSchemeUri.isEmpty())
    {
        cQSqlQuery.prepare(CreateSelectPart() + GenerateJoin() + " IdentityKey = ?");
        cQSqlQuery.addBindValue(m_qstrSchemeUri);
    }
    else
    {
        cQSqlQuery.prepare(CreateSelectPart() + " where IdentityKey = ?");
    }

    cQSqlQuery.addBindValue(m_qstrIdentKey);

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
          CreateUserObjectFromQuery(cQSqlQuery);
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No user found with Email " + m_qstrEmail);
      }
   }
   else
   {
      iRet = EC(eDmInvalidSelectStatement);
   }

   return iRet;
}
