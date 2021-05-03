// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CftlCommandFindUserGroup.h"
#include "CftlCommandGetGroupsOfUser.h"

CftlCommandGetGroupsOfUser::CftlCommandGetGroupsOfUser(long p_lUser, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lUserId(p_lUser)
{
}


CftlCommandGetGroupsOfUser::~CftlCommandGetGroupsOfUser()
{

}

QList<CumUserGroup *> CftlCommandGetGroupsOfUser::GetResult()
{
    return m_qllGroups;
}

int CftlCommandGetGroupsOfUser::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select GroupId from WMS_UM_GROUPMEMBER where UserId = ?");
    cQSqlQuery.addBindValue((int)m_lUserId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         cQSqlQuery.first();

         do // loading each bool
         {
            long lGroupId = cQSqlQuery.value(0).toInt();

            CftlCommandFindUserGroup command(lGroupId, GetDataAccess());
            if (SUCCESSFULL(command.Run()))
            {
                m_qllGroups.append(command.GetResult());
            }
         }
         while(cQSqlQuery.next());
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         INFO("no usergroup found on Db.");
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

bool CftlCommandGetGroupsOfUser::CheckValid()
{
    return (m_lUserId > 0);
}
