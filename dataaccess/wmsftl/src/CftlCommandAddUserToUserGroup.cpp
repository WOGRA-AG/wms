#include "CftlCommandAddUserToUserGroup.h"

CftlCommandAddUserToUserGroup::CftlCommandAddUserToUserGroup(long p_lUser, long p_lGroup, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lGroupId(p_lGroup),
  m_lUserId(p_lUser)
{
}

CftlCommandAddUserToUserGroup::~CftlCommandAddUserToUserGroup()
{

}

int CftlCommandAddUserToUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;

    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("insert into WMS_UM_GROUPMEMBER (GroupId, UserId) values (?, ?)");
    cQSqlQuery.addBindValue((int)m_lGroupId);
    cQSqlQuery.addBindValue((int)m_lUserId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
      lRet = EC(eDmOk);
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
    }

    return lRet;
}

bool CftlCommandAddUserToUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && m_lUserId > 0);
}
