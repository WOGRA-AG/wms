// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CdbCommandGetUserGroupList.h"

CdbCommandGetUserGroupList::CdbCommandGetUserGroupList(CdbDataAccess* p_pDataAccess, QString p_qstrSchemeUri)
    : CdbAbstractCommand(p_pDataAccess),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
}

CdbCommandGetUserGroupList::~CdbCommandGetUserGroupList()
{

}

QList<CumUserGroup *> CdbCommandGetUserGroupList::GetResult()
{
    return m_qllUserGroups;
}

int CdbCommandGetUserGroupList::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select GroupId, Name from WMS_UM_GROUP wmsgroup");

    if (!m_qstrSchemeUri.isEmpty())
    {
        qstrQuery += "inner join WMS_UM_ACCESSOR_SCHEME wmsscheme on wmsgroup.GroupId = wmsscheme.AccessorId where "
                     "wmsscheme.SchmeUri = '" + m_qstrSchemeUri + "'";
    }

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         do // loading each bool
         {
            long     lId                = cQSqlQuery.value(0).toInt();
            QString qstrName            = cQSqlQuery.value(1).toString();

            CumUserGroup* pCumUserGroup = new CumUserGroup(lId, nullptr);
            pCumUserGroup->SetGroupName(qstrName);
            m_qllUserGroups.append(pCumUserGroup);
         }
         while(cQSqlQuery.next());

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
      }
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
    }

    return lRet;
}

bool CdbCommandGetUserGroupList::CheckValid()
{
    return true;
}

