#include "CumUser.h"

#include "CdbCommandUpdateUser.h"

CdbCommandUpdateUser::CdbCommandUpdateUser(CumUser* p_pUser,
                                           CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_rpUser(p_pUser)
{
}

CdbCommandUpdateUser::~CdbCommandUpdateUser()
{

}

int CdbCommandUpdateUser::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());
    QString qstrQuery;

    if (!m_rpUser->GetPassword().isEmpty())
    {
        if (!m_rpUser->IsEncrypted())
        {
            m_rpUser->SetPassword(CwmsUtilities::EncryptPassword(m_rpUser->GetPassword()));
        }

        cQSqlQuery.prepare("update WMS_UM_USER set Firstname = ?, Lastname = ?, Login = ?, Pass = ?, Admin = ?, Active = ?, Email = ?, SchemeIndependent = ?, Encrypted = 1 where UserId = ?");

        cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
        cQSqlQuery.addBindValue(m_rpUser->GetLastName());
        cQSqlQuery.addBindValue(m_rpUser->GetLogin());
        cQSqlQuery.addBindValue(m_rpUser->GetPassword());
        cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
        cQSqlQuery.addBindValue(m_rpUser->IsActive());
        cQSqlQuery.addBindValue(m_rpUser->GetEmail());
        cQSqlQuery.addBindValue(m_rpUser->IsSchemeIndependent());
        cQSqlQuery.addBindValue((int)m_rpUser->GetId());
    }
    else
    {
        cQSqlQuery.prepare("update WMS_UM_USER set Firstname = ?, Lastname = ?, Login = ?, Admin = ?, Active = ?, Email = ?, SchemeIndependent = ?, Encrypted = 1 where UserId = ?");
        cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
        cQSqlQuery.addBindValue(m_rpUser->GetLastName());
        cQSqlQuery.addBindValue(m_rpUser->GetLogin());
        cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
        cQSqlQuery.addBindValue(m_rpUser->IsActive());
        cQSqlQuery.addBindValue(m_rpUser->GetEmail());
        cQSqlQuery.addBindValue(m_rpUser->IsSchemeIndependent());
        cQSqlQuery.addBindValue((int)m_rpUser->GetId());
    }

    if(ExecuteQuery(cQSqlQuery) > 0)
    {
        UpdateSchemeUri();
        lRet = EC(eDmOk);
    }
    else
    {
        lRet = EC(eDmInvalidUpdateStatement);
    }

    return lRet;
}

void CdbCommandUpdateUser::UpdateSchemeUri()
{
    QSqlQuery cQSqlQuery;
    QString qstrQuery = QString("delete from WMS_UM_ACCESSOR_SCHEME where accessorId = %1")
            .arg(m_rpUser->GetId());


    if (SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQuery)))
    {
        QStringList qstrlSchemes = m_rpUser->GetSchemeList();
        QString qstrValues;

        if (qstrlSchemes.count() > 0)
        {
            for (int pos = 0; pos < qstrlSchemes.count(); ++pos)
            {
                qstrValues += "(" + QString::number(m_rpUser->GetId()) + ", '" + qstrlSchemes[pos] + "')";
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

bool CdbCommandUpdateUser::CheckValid()
{
    return (m_rpUser);
}
