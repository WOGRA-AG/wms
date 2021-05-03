// WMS Includes
#include "CumUserGroup.h"

// Own Includes
#include "CftlCommandGetUserGroupList.h"

CftlCommandGetUserGroupList::CftlCommandGetUserGroupList(CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess)
{
}

CftlCommandGetUserGroupList::~CftlCommandGetUserGroupList()
{

}

QList<CumUserGroup *> CftlCommandGetUserGroupList::GetResult()
{
    return m_qllUserGroups;
}

int CftlCommandGetUserGroupList::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select GroupId, Name from WMS_UM_GROUP");

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
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
         INFO("no groups found on Db.");
      }
    }
    else
    {
      lRet = EC(eDmInvalidInsertStatement);
    }

    return lRet;
}

bool CftlCommandGetUserGroupList::CheckValid()
{
    return true;
}
