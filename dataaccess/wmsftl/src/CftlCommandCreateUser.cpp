
// WMS Includes
#include "CumUserManager.h"
#include "CumUser.h"

// Own Includes
#include "CwmsUtilities.h"
#include "CftlCommandCreateUser.h"

CftlCommandCreateUser::CftlCommandCreateUser(CumUser* p_pUser,
                                             CftlDataAccess* p_ppDataAccess)
: CftlAbstractTransactionalCommand(p_ppDataAccess),
  m_rpUser(p_pUser)
{
}

CftlCommandCreateUser::~CftlCommandCreateUser()
{

}

int CftlCommandCreateUser::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    int iAccessorId = InsertInAccessorTable(eUmUserGroupTypeUser);

    if(SUCCESSFULL(iAccessorId))
    {
       iAccessorId = InsertInUserTable(iAccessorId);

       if (SUCCESSFULL(iAccessorId))
       {
           if (!m_rpUser->GetSchemeList().isEmpty())
           {
                InsertInAccessorSchemeTable(iAccessorId);
           }

           lRet = iAccessorId;
       }

    }

    return lRet;
}

bool CftlCommandCreateUser::NeedsSessionCheck()
{
    return false;
}

int CftlCommandCreateUser::InsertInUserTable(int p_iAccessorId)
{
    int iRet = 0;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("insert into WMS_UM_USER "
                        "(UserId, FirstName, LastName, Login, Pass, Email, Admin, IdentityKey, Active, Encrypted) "
                        "values(?, ?, ?, ?, ?, ?, ?, ?, ?, true)");
    cQSqlQuery.addBindValue(p_iAccessorId);
    cQSqlQuery.addBindValue(m_rpUser->GetFirstName());
    cQSqlQuery.addBindValue(m_rpUser->GetLastName());
    cQSqlQuery.addBindValue(m_rpUser->GetLogin());
    cQSqlQuery.addBindValue(m_rpUser->GetPassword());
    cQSqlQuery.addBindValue(m_rpUser->GetEmail());
    cQSqlQuery.addBindValue(m_rpUser->IsAdministrator());
    cQSqlQuery.addBindValue(m_rpUser->GetIdentitiyKey());
    cQSqlQuery.addBindValue(m_rpUser->GetIdentitiyKey().isEmpty()); // if identitykey is empty user is asap active

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        iRet = p_iAccessorId;
    }
    else
    {
        iRet = EC(CdmLogging::eDmInvalidInsertStatement);
        ERR("Insert user failed!!!");
    }

    return iRet;
}


void CftlCommandCreateUser::InsertInAccessorSchemeTable(int p_iAccessorId)
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("insert into WMS_UM_ACCESSOR_SCHEME (AccessorId, SchemeUri) values(:accessorId, :schemeUri)");
    cQSqlQuery.bindValue(":accessorId", p_iAccessorId);
    cQSqlQuery.bindValue(":schemeUri", m_rpUser->GetSchemeList()[0]); // An user can onbly be created with one scheme.

    if(!SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        ERR("Insert in WMS_UM_ACCESSOR_SCHEME failed!");
    }
}


bool CftlCommandCreateUser::CheckValid()
{
    return (m_rpUser &&
            !m_rpUser->GetLogin().isEmpty() &&
            (!m_rpUser->GetPassword().isEmpty() || m_rpUser->IsActive() == false));
}
