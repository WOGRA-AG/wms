// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CdbCommandFindUserGroup.h"


CdbCommandFindUserGroup::CdbCommandFindUserGroup(long p_lGroup, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lGroupId(p_lGroup),
  m_pGroup(nullptr)
{

}

CdbCommandFindUserGroup::CdbCommandFindUserGroup(QString p_lGroup,CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lGroupId(0),
      m_pGroup(NULL),
      m_qstrGroupName(p_lGroup)
{

}

CdbCommandFindUserGroup::~CdbCommandFindUserGroup()
{

}

CumUserGroup* CdbCommandFindUserGroup::GetResult()
{
    return m_pGroup;
}

int CdbCommandFindUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select GroupId, Name from WMS_UM_GROUP where GroupId = %1")
                       .arg(m_lGroupId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         m_pGroup = new CumUserGroup(cQSqlQuery.value(0).toInt(), nullptr);
         m_pGroup->SetGroupName(cQSqlQuery.value(1).toString());
         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         INFO("No usergroup found with ID " +QString::number(m_lGroupId));
      }
    }

    return lRet;
}

bool CdbCommandFindUserGroup::CheckValid()
{
    return (m_lGroupId > 0);
}
