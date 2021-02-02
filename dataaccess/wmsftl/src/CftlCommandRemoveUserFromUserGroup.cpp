#include "CftlCommandRemoveUserFromUserGroup.h"

CftlCommandRemoveUserFromUserGroup::CftlCommandRemoveUserFromUserGroup(long p_lUser, long p_lGroup, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lGroupId(p_lGroup),
      m_lUserId(p_lUser)
{
}


CftlCommandRemoveUserFromUserGroup::~CftlCommandRemoveUserFromUserGroup()
{

}

int CftlCommandRemoveUserFromUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    cQSqlQuery.prepare("delete from  WMS_UM_GROUPMEMBER where GroupId = ? and UserId = ?");
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

bool CftlCommandRemoveUserFromUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && m_lUserId > 0);
}
