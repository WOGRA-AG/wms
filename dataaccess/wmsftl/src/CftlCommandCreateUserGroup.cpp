
// WMSCORE Includes
#include "CumAccessor.h"

// Own Includes
#include "CftlCommandCreateUserGroup.h"

CftlCommandCreateUserGroup::CftlCommandCreateUserGroup(QString p_qstrGroupName, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_qstrNewName(p_qstrGroupName)
{
}

CftlCommandCreateUserGroup::~CftlCommandCreateUserGroup()
{
}

int CftlCommandCreateUserGroup::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    int iAccessorId = InsertInAccessorTable(eUmUserGroupTypeUser);

    if(SUCCESSFULL(iAccessorId))
    {
        lRet = InsertInGroupTable(iAccessorId);
    }

    return lRet;
}

int CftlCommandCreateUserGroup::InsertInGroupTable(int p_iAccessorId)
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("insert into WMS_UM_GROUP (GroupId, Name) values(?, ?)");
    cQSqlQuery.addBindValue(p_iAccessorId);
    cQSqlQuery.addBindValue(m_qstrNewName);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        lRet = p_iAccessorId;
    }
    else
    {
        lRet = EC(eDmInvalidInsertStatement);
        ERR("Insert Usergroup failed!!!");
    }

    return lRet;
}



bool CftlCommandCreateUserGroup::CheckValid()
{
    return !m_qstrNewName.isEmpty();
}
