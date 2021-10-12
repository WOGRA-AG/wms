#include "CdbCommandRemoveUserFromUserGroup.h"

CdbCommandRemoveUserFromUserGroup::CdbCommandRemoveUserFromUserGroup(qint64 p_lUser,qint64 p_lGroup, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lGroupId(p_lGroup),
      m_lUserId(p_lUser)
{
}


CdbCommandRemoveUserFromUserGroup::~CdbCommandRemoveUserFromUserGroup()
{

}

int CdbCommandRemoveUserFromUserGroup::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("delete from  WMS_UM_GROUPMEMBER where GroupId = %1 and UserId = %2")
                       .arg(m_lGroupId)
                       .arg(m_lUserId);

    if(SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQuery)))
    {
      lRet = EC(eDmOk);
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
    }

    return lRet;
}

bool CdbCommandRemoveUserFromUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && m_lUserId > 0);
}
