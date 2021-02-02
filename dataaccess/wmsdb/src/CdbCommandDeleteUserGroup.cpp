#include "CdbCommandDeleteUserGroup.h"

CdbCommandDeleteUserGroup::CdbCommandDeleteUserGroup(long p_lgroupId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lGroupId(p_lgroupId)
{
}


CdbCommandDeleteUserGroup::~CdbCommandDeleteUserGroup()
{

}

int CdbCommandDeleteUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
     QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("delete from WMS_UM_ACCESSOR where AccessorId = %1")
                       .arg(m_lGroupId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      qstrQuery = QString("delete from WMS_UM_GROUP where GroupId = %1")
         .arg(m_lGroupId);

      if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidDeleteStatement);
      }
    }
    else
    {
      lRet = EC(eDmInvalidDeleteStatement);
    }

    return lRet;
}

bool CdbCommandDeleteUserGroup::CheckValid()
{
    return (m_lGroupId > 0);
}
