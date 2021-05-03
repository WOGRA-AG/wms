// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CdbCommandFindUserGroup.h"
#include "CdbCommandGetGroupsOfUser.h"

CdbCommandGetGroupsOfUser::CdbCommandGetGroupsOfUser(long p_lUser, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lUserId(p_lUser)
{
}


CdbCommandGetGroupsOfUser::~CdbCommandGetGroupsOfUser()
{

}

QList<CumUserGroup *> CdbCommandGetGroupsOfUser::GetResult()
{
    return m_qllGroups;
}

int CdbCommandGetGroupsOfUser::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    INFO("Looking for group memberships of user " + QString::number(m_lUserId));
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select GroupId from WMS_UM_GROUPMEMBER where UserId = %1")
      .arg(m_lUserId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         cQSqlQuery.first();

         do // loading each bool
         {
            long lGroupId = cQSqlQuery.value(0).toInt();

            CdbCommandFindUserGroup command(lGroupId, GetDataAccess());
            if (SUCCESSFULL(command.Run()))
            {
                m_qllGroups.append(command.GetResult());
            }
         }
         while(cQSqlQuery.next());

         INFO(QString::number(m_qllGroups.count()) + " groups found.");
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         INFO("No groups found");
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

bool CdbCommandGetGroupsOfUser::CheckValid()
{
    return (m_lUserId > 0);
}
