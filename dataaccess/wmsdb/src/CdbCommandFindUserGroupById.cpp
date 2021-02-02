//WMS Includes
#include "CumUserGroup.h"

//Own Includes
#include "CdbCommandFindUserGroupById.h"

CdbCommandFindUserGroupById::CdbCommandFindUserGroupById(int p_iGroup, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_iGroupId(p_iGroup),
      m_pGroup(nullptr)
{

}

CdbCommandFindUserGroupById::~CdbCommandFindUserGroupById()
{

}

CumUserGroup* CdbCommandFindUserGroupById::GetResult()
{
    return m_pGroup;
}

int CdbCommandFindUserGroupById::Execute()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select GroupId, Name from WMS_UM_GROUP where GroupId = %1").
            arg(m_iGroupId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         m_pGroup = new CumUserGroup(cQSqlQuery.value(0).toInt(), nullptr);
         m_pGroup->SetGroupName(cQSqlQuery.value(1).toString());
         iRet = EC(eDmOk);
      }
      else
      {
         iRet = EC(CdmLogging::eDmFalse);
         INFO("No usergroup found with ID " +QString::number(m_iGroupId));
      }
    }

    return iRet;
}

bool CdbCommandFindUserGroupById::CheckValid()
{
    return (m_iGroupId > 0);
}
