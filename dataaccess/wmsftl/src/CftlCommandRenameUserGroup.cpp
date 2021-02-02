#include "CftlCommandRenameUserGroup.h"

CftlCommandRenameUserGroup::CftlCommandRenameUserGroup(long p_lGroupId, QString p_qstrName, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lGroupId(p_lGroupId),
      m_qstrNewName(p_qstrName)
{
}


CftlCommandRenameUserGroup::~CftlCommandRenameUserGroup()
{

}

int CftlCommandRenameUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    cQSqlQuery.prepare("update WMS_UM_GROUP set Name = ? where GroupId = ?");
    cQSqlQuery.addBindValue(m_qstrNewName);
    cQSqlQuery.addBindValue((int)m_lGroupId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        INFO("Renaming group was succesfull");
        lRet = EC(eDmOk);
    }
    else
    {
        ERR("Renaming failed. Perhaps there is already a group with this name.")
        lRet = EC(eDmUserGroupNotUniqueInDb);
    }

    return lRet;
}

bool CftlCommandRenameUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && !m_qstrNewName.isEmpty());
}
