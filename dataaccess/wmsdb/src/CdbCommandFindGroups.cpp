// System and Qt Includes
#include <QSqlQuery>

// WMS Core Includes
#include "CumUserGroup.h"

// Own Includes
#include "CdbCommandFindGroups.h"

CdbCommandFindGroups::CdbCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_qstrGroupName(p_qstrGroupName),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CdbCommandFindGroups::~CdbCommandFindGroups()
{
    // NOTHING To DO
}

QLinkedList<CumUserGroup *> CdbCommandFindGroups::GetResult()
{
    return m_qllGroups;
}

int CdbCommandFindGroups::Execute()
{
    if(!m_qstrGroupName.isEmpty())
    {
        return FindUserGroupByGroupName();
    }
    else
    {
        return GetAllUserGroups();
    }
}

int CdbCommandFindGroups::FindUserGroupByGroupName()
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

    qstrQuery += QString("wmsgroup.Name like '%%1%'")
            .arg(m_qstrGroupName);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        FillGroupList(cQSqlQuery);
        iRet = EC(eDmOk);
    }

    return iRet;
}

int CdbCommandFindGroups::GetAllUserGroups()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery = "select GroupId, Name from WMS_UM_GROUP";

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        FillGroupList(cQSqlQuery);
        iRet = EC(eDmOk);
    }

    return iRet;
}

void CdbCommandFindGroups::FillGroupList(QSqlQuery &cQSqlQuery)
{
        while(cQSqlQuery.next())
        {
            CumUserGroup* pGroup = new CumUserGroup(cQSqlQuery.value(0).toInt(), nullptr);
            pGroup->SetGroupName(cQSqlQuery.value(1).toString());
            m_qllGroups.append(pGroup);
        }
    }

bool CdbCommandFindGroups::CheckValid()
{
    return true;
}
