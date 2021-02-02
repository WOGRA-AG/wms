#include "CdmSessionManager.h"

#include "CftlCommandLogout.h"

CftlCommandLogout::CftlCommandLogout(CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess)
{
}

CftlCommandLogout::~CftlCommandLogout()
{

}

int CftlCommandLogout::Execute()
{
   long lRet = CdmLogging::eDmUnknownLoginManagerError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   QString qstrQuery;
   cQSqlQuery.prepare("update WMS_UM_SESSION set State = ?, LogOutDate = ? where SessionId = ?");
   cQSqlQuery.addBindValue(false);
   cQSqlQuery.addBindValue(QDateTime::currentDateTime());
   cQSqlQuery.addBindValue((int)CdmSessionManager::GetSessionManager()->GetCurrentSessionId());

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      lRet = EC(eDmOk);
   }
   else
   {
      lRet = EC(eDmInvalidUpdateStatement);
      ERR("Logout was not successfull!!");
   }


    return lRet;
}

bool CftlCommandLogout::CheckValid()
{
    return (CdmSessionManager::GetSessionManager()->GetCurrentSessionId() > 0);
}

bool CftlCommandLogout::NeedsActiveSession()
{
    return false;
}
