
// WMS Includes
#include "CumUserManager.h"
#include "CumUser.h"

// Own Includes
#include "CdbCommandCreateUser.h"
#include <CdmLogging.h>

CdbCommandCreateUser::CdbCommandCreateUser(CumUser* p_pUser,
                                           CdbDataAccess* p_ppDataAccess)
    : CdbAbstractCommandTransactional(p_ppDataAccess),
      m_rpUser(p_pUser)
{
}

CdbCommandCreateUser::~CdbCommandCreateUser()
{

}

int CdbCommandCreateUser::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    int iAccessorId = InsertInAccessorTable();

    if(SUCCESSFULL(iAccessorId))
    {
        iAccessorId = InsertInUserTable(iAccessorId);

        if (SUCCESSFULL(iAccessorId) && !m_rpUser->GetSchemeList().isEmpty())
        {
            InsertInAccessorSchemeTable(iAccessorId);
        }

        lRet = iAccessorId;
    }

    return lRet;
}

int CdbCommandCreateUser::InsertInUserTable(int p_iAccessorId)
{
    int iRet = 0;
    QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());

    if (!m_rpUser->IsEncrypted())
    {
        m_rpUser->SetPassword(CwmsUtilities::EncryptPassword(m_rpUser->GetPassword()));
    }


    cQSqlQuery.prepare("insert into WMS_UM_USER "
                       "(UserId, FirstName, LastName, Login, Pass, Email, Admin, IdentityKey, Active, SchemeIndependent, Encrypted) "
                       "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, true)");

    cQSqlQuery.addBindValue(p_iAccessorId);
    cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
    cQSqlQuery.addBindValue(m_rpUser->GetLastName());
    cQSqlQuery.addBindValue(m_rpUser->GetLogin());
    cQSqlQuery.addBindValue(m_rpUser->GetPassword());
    cQSqlQuery.addBindValue(m_rpUser->GetEmail());
    cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
    cQSqlQuery.addBindValue(m_rpUser->GetIdentitiyKey());
    cQSqlQuery.addBindValue(m_rpUser->GetIdentitiyKey().isEmpty()); // Active Flag
    cQSqlQuery.addBindValue(m_rpUser->IsSchemeIndependent());

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        iRet = p_iAccessorId;
        m_rpUser->SetEncrypted(true);
    }
    else
    {
        iRet = EC(CdmLogging::eDmInvalidInsertStatement);
        ERR("Insert user failed!!!");
    }

    return iRet;
}

int CdbCommandCreateUser::InsertInAccessorTable()
{
    int iAccessorId =  0;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    qstrQuery = QString("insert into WMS_UM_ACCESSOR(AccessorType, NewAccessor) values(%1, true)")
            .arg(eUmUserGroupTypeUser);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        qstrQuery = QString("select AccessorId from WMS_UM_ACCESSOR "
                            "where AccessorType = %1 and NewAccessor = true")
                .arg(eUmUserGroupTypeUser);

        if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
        {
            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
                iAccessorId = cQSqlQuery.value(0).toInt();
            }

            qstrQuery = QString("update WMS_UM_ACCESSOR set newaccessor = false "
                                "where AccessorId = %1")
                    .arg(iAccessorId);

            if(SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQuery)))
            {
                INFO("Accessor created")
            }
            else
            {
                iAccessorId = EC(eDmAccessorIdNotFoundInDb);
            }
        }
        else
        {
            iAccessorId = EC(eDmInvalidSelectStatement);
        }
    }
    else
    {
        iAccessorId = EC(eDmInvalidInsertStatement);
    }

    return iAccessorId;
}

void CdbCommandCreateUser::InsertInAccessorSchemeTable(int p_iAccessorId)
{
    QSqlQuery cQSqlQuery;
    QString qstrQuery = QString("delete from WMS_UM_ACCESSOR_SCHEME where accessorId = %1")
            .arg(p_iAccessorId);


    if (SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQuery)))
    {
        QStringList qstrlSchemes = m_rpUser->GetSchemeList();
        QString qstrValues;

        if (qstrlSchemes.count() > 0)
        {
            for (int pos = 0; pos < qstrlSchemes.count(); ++pos)
            {
                qstrValues += "(" + QString::number(p_iAccessorId) + ", '" + qstrlSchemes[pos] + "')";
            }

            QString qstrQuery = QString("insert into WMS_UM_ACCESSOR_SCHEME (accessorId, SchemeUri) values %1")
                    .arg(qstrValues);

            QSqlQuery cQSqlQueryInsert;
            if (!SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQueryInsert)))
            {
                ERR("Insert of Scheme failed");
            }
        }
    }
    else
    {
        ERR("WMS_ACCESSOR_SCHEME select failed");
    }
}

bool CdbCommandCreateUser::CheckValid()
{
    return (m_rpUser &&
            !m_rpUser->GetLogin().isEmpty() &&
            (!m_rpUser->GetPassword().isEmpty() || !m_rpUser->IsActive()));
}
