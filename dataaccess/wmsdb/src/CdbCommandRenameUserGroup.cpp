#include "CdbCommandRenameUserGroup.h"

CdbCommandRenameUserGroup::CdbCommandRenameUserGroup(long p_lGroupId, QString p_qstrName, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lGroupId(p_lGroupId),
      m_qstrNewName(p_qstrName)
{
}


CdbCommandRenameUserGroup::~CdbCommandRenameUserGroup()
{

}

int CdbCommandRenameUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("update WMS_UM_GROUP set Name = '%1' where GroupId = %2")
                      .arg(CwmsUtilities::MaskStringForChanges(m_qstrNewName))
                      .arg(m_lGroupId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        INFO("Renaming group was succesfull");
        lRet = EC(eDmOk);
    }
    else
    {
        INFO("Renaming failed. Perhaps there is already a group with this name.")
        lRet = EC(CdmLogging::eDmFalse);
    }

    return lRet;
}

bool CdbCommandRenameUserGroup::CheckValid()
{
    return (m_lGroupId > 0 && !m_qstrNewName.isEmpty());
}
