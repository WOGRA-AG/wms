// System and Qt Includes
#include <QSqlQuery>

// WMS Core Includes
#include "CumUserGroup.h"

// Own Includes
#include "CftlCommandFindGroups.h"

CftlCommandFindGroups::CftlCommandFindGroups(QString p_qstrGroupName, QString p_qstrSchemeUri, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_qstrGroupName(p_qstrGroupName),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CftlCommandFindGroups::~CftlCommandFindGroups()
{
    // NOTHING To DO
}

QLinkedList<CumUserGroup *> CftlCommandFindGroups::GetResult()
{
    return m_qllGroups;
}

int CftlCommandFindGroups::Execute()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
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

    qstrQuery += QString("wmsgroup.Name like ?");
    cQSqlQuery.prepare(qstrQuery);
    cQSqlQuery.addBindValue("%" + m_qstrGroupName + "%");

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        while(cQSqlQuery.next())
        {
            CumUserGroup* pGroup = new CumUserGroup(cQSqlQuery.value(0).toInt(), nullptr);
            pGroup->SetGroupName(cQSqlQuery.value(1).toString());
            m_qllGroups.append(pGroup);
        }

        iRet = EC(eDmOk);
    }

    return iRet;
}

bool CftlCommandFindGroups::CheckValid()
{
    return !m_qstrGroupName.isEmpty();
}
