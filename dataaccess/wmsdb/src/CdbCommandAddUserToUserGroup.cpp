#include "CdbCommandAddUserToUserGroup.h"

CdbCommandAddUserToUserGroup::CdbCommandAddUserToUserGroup(qint64 p_lUser,qint64 p_lGroup, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lGroupId(p_lGroup),
  m_lUserId(p_lUser)
{
}

CdbCommandAddUserToUserGroup::~CdbCommandAddUserToUserGroup()
{

}

int CdbCommandAddUserToUserGroup::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;

    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("insert into WMS_UM_GROUPMEMBER (GroupId, UserId) values (%1, %2)")
                       .arg(m_lGroupId)
                       .arg(m_lUserId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      lRet = EC(eDmOk);
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
    }

    return lRet;
}

bool CdbCommandAddUserToUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && m_lUserId > 0);
}
