// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CftlCommandFindUserGroup.h"


CftlCommandFindUserGroup::CftlCommandFindUserGroup(qint64 p_lGroupId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lGroupId(p_lGroupId),
  m_pGroup(nullptr)
{

}

CftlCommandFindUserGroup::CftlCommandFindUserGroup(QString p_qstrName, QString p_qstrSchemeUri, CftlDataAccess *p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lGroupId(0),
      m_pGroup(nullptr),
      m_qstrGroupName(p_qstrName),
      m_qstrSchemeUri(p_qstrSchemeUri)
{

}

CftlCommandFindUserGroup::~CftlCommandFindUserGroup()
{

}

CumUserGroup* CftlCommandFindUserGroup::GetResult()
{
    return m_pGroup;
}

int CftlCommandFindUserGroup::Execute()
{
    if (m_lGroupId > 0)
    {
        return FindUserGroupById();
    }
    else
    {
        return FindUserGroupByName();
    }
}

int CftlCommandFindUserGroup::FindUserGroupById()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    cQSqlQuery.prepare("select GroupId, Name from WMS_UM_GROUP where GroupId = ?");
    cQSqlQuery.addBindValue(m_lGroupId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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
         INFO("No usergroup found with ID " +QString::number(m_lGroupId));
      }
    }
    return iRet;
}

int CftlCommandFindUserGroup::FindUserGroupByName()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    if (!m_qstrSchemeUri.isEmpty())
    {
        cQSqlQuery.prepare("select GroupId, Name from WMS_UM_GROUP wmsgroup "
                           "inner join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsgroup.GroupId = wmsscheme.AccessorId where "
                           "wmsscheme.SchmeUri = ? and wmsgroup.Name = ?");
        cQSqlQuery.addBindValue(m_qstrSchemeUri);
    }
    else
    {
        cQSqlQuery.prepare("select GroupId, Name from WMS_UM_GROUP wmsgroup where wmsgroup.Name = ?");
    }

    cQSqlQuery.addBindValue(m_qstrGroupName);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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
         INFO("No usergroup found with Name " + m_qstrGroupName);
      }
    }
    return iRet;
}

bool CftlCommandFindUserGroup::CheckValid()
{
    return (m_lGroupId > 0 || !m_qstrGroupName.isEmpty());
}
