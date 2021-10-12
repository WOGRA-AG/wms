#include "CftlCommandDeleteUserGroup.h"

CftlCommandDeleteUserGroup::CftlCommandDeleteUserGroup(qint64 p_lgroupId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lGroupId(p_lgroupId)
{
}


CftlCommandDeleteUserGroup::~CftlCommandDeleteUserGroup()
{

}

int CftlCommandDeleteUserGroup::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;

    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_UM_ACCESSOR where AccessorId = ?");
    cQSqlQuery.addBindValue(m_lGroupId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.prepare("delete from WMS_UM_GROUP where GroupId = ?");
        cQSqlQuery.addBindValue(m_lGroupId);

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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

bool CftlCommandDeleteUserGroup::CheckValid()
{
    return (m_lGroupId > 0);
}
