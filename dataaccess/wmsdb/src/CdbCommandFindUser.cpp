
// System and Qt Includes
#include <qcryptographichash.h>

// WMS Commons Includes
#include "CwmsUtilities.h"

// WMS Includes
#include "CumUser.h"

// Own includes
#include "CdbCommandFindUser.h"

CdbCommandFindUser::CdbCommandFindUser(qint64 p_lUserId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lUserId(p_lUserId),
      m_rpUser(nullptr)
{
}

CdbCommandFindUser::CdbCommandFindUser(QString p_qstrValue, bool p_bEmail, QString p_qstrSchemeUri, CdbDataAccess *p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrSchemeUri(p_qstrSchemeUri),
      m_rpUser(nullptr)
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

CdbCommandFindUser::CdbCommandFindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri, CdbDataAccess *p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrLogin(p_qstrLogin),
      m_qstrPassword(p_qstrPassword),
      m_qstrSchemeUri(p_qstrSchemeUri),
      m_rpUser(nullptr)
{
}

CdbCommandFindUser::CdbCommandFindUser(QString p_qstrLoginEmailName, QString p_qstrSchemeUri, CdbDataAccess *p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lUserId(0),
      m_qstrIdentKey(p_qstrLoginEmailName),
      m_qstrSchemeUri(p_qstrSchemeUri),
      m_rpUser(nullptr)
{
}

CdbCommandFindUser::~CdbCommandFindUser()
{

}

int CdbCommandFindUser::Execute()
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

int CdbCommandFindUser::FindUserById()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = GetSelectPartOfQuery() + QString("where UserId = %1")
            .arg(m_lUserId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        iRet = SetResult(cQSqlQuery);
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
    }

    return iRet;
}

QString CdbCommandFindUser::GetSelectPartOfQuery()
{
    return QString("select UserId, FirstName, LastName, Email, Login, Pass, Admin, Active, Encrypted, SchemeIndependent from WMS_UM_USER wmsuser ");
}

int CdbCommandFindUser::SetResult(QSqlQuery& p_rQuery)
{
    int iRet = 0;
    p_rQuery.first();
    if(p_rQuery.isValid())
    {
        m_rpUser = new CumUser(p_rQuery.value(0).toInt(), nullptr);

        // the value at position 0 is the user id and not needed here
        m_rpUser->SetFirstName(p_rQuery.value(1).toString());
        m_rpUser->SetLastName(p_rQuery.value(2).toString());
        m_rpUser->SetEmail(p_rQuery.value(3).toString());
        m_rpUser->SetLogin(p_rQuery.value(4).toString());
        m_rpUser->SetPassword(p_rQuery.value(5).toString());
        m_rpUser->SetAdministrator(p_rQuery.value(6).toBool());
        m_rpUser->SetActive(p_rQuery.value(7).toBool());
        m_rpUser->SetEncrypted(p_rQuery.value(8).toBool());
        m_rpUser->SetSchemeIndependent(p_rQuery.value(9).toBool());

        iRet = EC(eDmOk);
    }
    else
    {
        iRet = EC(CdmLogging::eDmFalse);
        INFO("No user found with Login " + m_qstrLogin);
    }

    return iRet;
}

QString CdbCommandFindUser::GenerateJoin()
{
    return "left join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsuser.UserId = wmsscheme.AccessorId where ((wmsscheme.SchmeUri is nullptr and wmsuser.SchemeIndependent = 1) or "
           "wmsscheme.SchmeUri = '" + m_qstrSchemeUri + "') and ";
}

int CdbCommandFindUser::FindUserByLogin()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery = GetSelectPartOfQuery();


    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin();
    }
    else
    {
        qstrQuery += "where ";
    }

    qstrQuery += QString("Login = '%1'").arg(CwmsUtilities::MaskStringForChanges(m_qstrLogin));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        iRet = SetResult(cQSqlQuery);
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
    }

    return iRet;
}

bool CdbCommandFindUser::CheckPassword(QSqlQuery& cQSqlQuery)
{
    bool bValidPassword = false;
    cQSqlQuery.first();
    if(cQSqlQuery.isValid())
    {
       QString qstrStoredPassword = cQSqlQuery.value(5).toString();
       QString qstrGivenPassword;

       if (cQSqlQuery.value(8).toBool())
       {
            qstrGivenPassword = CwmsUtilities::EncryptPassword(m_qstrPassword);
       }
       else
       {
           qstrGivenPassword = m_qstrPassword;
       }

       if (qstrStoredPassword == qstrGivenPassword)
       {
           bValidPassword = true;
       }
    }

    return bValidPassword;
}

int CdbCommandFindUser::FindUserByLoginAndPassword()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery = GetSelectPartOfQuery();

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin();
    }
    else
    {
        qstrQuery += "where ";
    }

    qstrQuery += QString("Login = '%1'").arg(CwmsUtilities::MaskStringForChanges(m_qstrLogin));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        bool bValidPassword = CheckPassword(cQSqlQuery);

        if (bValidPassword)
        {
            iRet = SetResult(cQSqlQuery);
        }
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
    }


    return iRet;
}

int CdbCommandFindUser::FindUserByEmail()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = GetSelectPartOfQuery();

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin();
    }
    else
    {
        qstrQuery += "where ";
    }


    qstrQuery += QString("wmsuser.Email = '%1'")
            .arg(CwmsUtilities::MaskStringForChanges(m_qstrEmail));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        iRet = SetResult(cQSqlQuery);
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
    }

    return iRet;
}

CumUser *CdbCommandFindUser::GetResult()
{
    return m_rpUser;
}

bool CdbCommandFindUser::CheckValid()
{
    return (m_lUserId > 0 || !m_qstrEmail.isEmpty() || !m_qstrLogin.isEmpty() || !m_qstrIdentKey.isEmpty());
}


void CdbCommandFindUser::EncryptAllPasswords()
{
    QSqlQuery cQSqlQuery;
    QString qstrSelect = "select UserId, Pass from WMS_UM_USER where encrypted = 0 or encrypted is null";

    if(ExecuteQuery(qstrSelect, cQSqlQuery) > 0)
    {
        cQSqlQuery.first();
        QMap<qint64, QString> qmEncryptedPasswords;
        if(cQSqlQuery.isValid())
        {
            do // loading each password and converting it
            {
               qint64     lId                = cQSqlQuery.value(0).toInt();
                QString qstrPassword        = cQSqlQuery.value(1).toString();
                qmEncryptedPasswords.insert(lId, CwmsUtilities::EncryptPassword(qstrPassword));
            }
            while(cQSqlQuery.next());

            QMap<qint64, QString>::iterator qmIt = qmEncryptedPasswords.begin();
            QMap<qint64, QString>::iterator qmItEnd = qmEncryptedPasswords.end();

            for (; qmIt != qmItEnd; ++qmIt) // update passwords in db
            {
                QSqlQuery cQSqlQueryTemp;
                QString qstrUpdate = QString("update WMS_UM_USER set pass = '%1', encrypted = 1 where userid = '%2'")
                        .arg(CwmsUtilities::MaskStringForChanges(qmIt.value()))
                        .arg(qmIt.key());


                if(ExecuteQuery(qstrUpdate, cQSqlQueryTemp) <= 0)
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

int CdbCommandFindUser::FindUserByIdentityKey()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    // won't be used as return parameter but good for debugging
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = GetSelectPartOfQuery();


    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += GenerateJoin();
    }
    else
    {
        qstrQuery += "where ";
    }

    qstrQuery += QString("wmsuser.IdentityKey = '%1'")
            .arg(CwmsUtilities::MaskStringForChanges(m_qstrIdentKey));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        iRet = SetResult(cQSqlQuery);
    }
    else
    {
        iRet = EC(eDmInvalidSelectStatement);
    }

    return iRet;
}

bool CdbCommandFindUser::NeedsActiveSession()
{
    return false;
}

