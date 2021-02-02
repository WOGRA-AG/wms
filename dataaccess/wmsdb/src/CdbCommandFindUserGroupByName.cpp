//WMS Includes
#include "CumUserGroup.h"

//Own Includes
#include "CdbCommandFindUserGroupByName.h"

CdbCommandFindUserGroupByName::CdbCommandFindUserGroupByName(QString p_qstrGroupName, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_qstrGroupName(p_qstrGroupName),
      m_pGroup(nullptr),
      m_qstrSchemeUri(p_qstrSchemeUri)
{

}

CdbCommandFindUserGroupByName::~CdbCommandFindUserGroupByName()
{

}

CumUserGroup* CdbCommandFindUserGroupByName::GetResult()
{
    return m_pGroup;
}

int CdbCommandFindUserGroupByName::Execute()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select GroupId, Name from WMS_UM_GROUP wmsgroup ");

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += "inner join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsgroup.GroupId = wmsscheme.AccessorId where "
                     "wmsscheme.SchmeUri = '" + m_qstrSchemeUri + "' and ";
    }
    else
    {
        qstrQuery += "where ";
    }

    qstrQuery += QString("wmsgroup.Name = '%1'")
            .arg(m_qstrGroupName);

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
            INFO("No usergroup found with Name " + m_qstrGroupName);
        }
    }
    return iRet;
}

bool CdbCommandFindUserGroupByName::CheckValid()
{
    return (!m_qstrGroupName.isEmpty());
}
