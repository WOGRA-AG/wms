#include "CumUser.h"

#include "CftlCommandUpdateUser.h"

CftlCommandUpdateUser::CftlCommandUpdateUser(CumUser* p_pUser,
                                             CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_rpUser(p_pUser)
{
}

CftlCommandUpdateUser::~CftlCommandUpdateUser()
{

}

int CftlCommandUpdateUser::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    if (!m_rpUser->GetPassword().isEmpty())
    {
        if (!m_rpUser->IsEncrypted())
        {
            m_rpUser->SetPassword(CwmsUtilities::EncryptPassword(m_rpUser->GetPassword()));
        }

        cQSqlQuery.prepare("update WMS_UM_USER set Firstname = ?, Lastname = ?, Login = ?, Pass = ?, Admin = ?, Active = ?, Email = ?, Encrypted = 1 where UserId = ?");
        cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
        cQSqlQuery.addBindValue(m_rpUser->GetLastName());
        cQSqlQuery.addBindValue(m_rpUser->GetLogin());
        cQSqlQuery.addBindValue(m_rpUser->GetPassword());
        cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
        cQSqlQuery.addBindValue(m_rpUser->IsActive());
        cQSqlQuery.addBindValue(m_rpUser->GetEmail());
        cQSqlQuery.addBindValue(m_rpUser->GetId());
    }
    else // Don't aks me when this is possible??? I cann't remember WG 8.6.2017
    {
        cQSqlQuery.prepare("update WMS_UM_USER set Firstname = ?, Lastname = ?, Login = ?, Admin = ?, Active = ?, Email = ?, Encrypted = 1 where UserId = ?");
        cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
        cQSqlQuery.addBindValue(m_rpUser->GetLastName());
        cQSqlQuery.addBindValue(m_rpUser->GetLogin());
        cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
        cQSqlQuery.addBindValue(m_rpUser->IsActive());
        cQSqlQuery.addBindValue(m_rpUser->GetEmail());
        cQSqlQuery.addBindValue(m_rpUser->GetId());
    }

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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

void CftlCommandUpdateUser::UpdateSchemeUri()
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_UM_ACCESSOR_SCHEME where accessorId = ?");
    cQSqlQuery.addBindValue(m_rpUser->GetId());


    if (SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        QStringList qstrlSchemes = m_rpUser->GetSchemeList();
        if (qstrlSchemes.count() > 0)
        {
            QVariantList qvlUser;
            QVariantList qvlSchemes;

            for (int pos = 0; pos < qstrlSchemes.count(); ++pos)
            {
                qvlUser.append(m_rpUser->GetId());
                qvlSchemes.append(qstrlSchemes[pos]);
            }

            QSqlQuery cQSqlQueryInsert(GetSqlDatabase());
            cQSqlQueryInsert.prepare("insert into WMS_UM_ACCESSOR_SCHEME (accessorId, SchemeUri) values(?, ?)");
            cQSqlQueryInsert.addBindValue(qvlUser);
            cQSqlQueryInsert.addBindValue(qvlSchemes);

            if (!cQSqlQueryInsert.execBatch())
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

bool CftlCommandUpdateUser::CheckValid()
{
    return (m_rpUser &&
            !m_rpUser->GetLogin().isEmpty() &&
            (!m_rpUser->GetPassword().isEmpty() || m_rpUser->IsActive() == false));
}
