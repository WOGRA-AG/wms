// System and Qt Includes
#include <QSqlQuery>
#include <QDateTime>

#include "CdmSessionManager.h"

// Own Includes
#include "CwmsUtilities.h"
#include "CftlCommandGetNewContainerId.h"

#define INIT_CONTAINER_NAME "New_Container"

CftlCommandGetNewContainerId::CftlCommandGetNewContainerId(qint64 p_lClassId, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lClassId(p_lClassId)
{
}

CftlCommandGetNewContainerId::~CftlCommandGetNewContainerId()
{

}

bool CftlCommandGetNewContainerId::CheckValid()
{
    return (m_lClassId > 0 && CHKPTR(GetDataAccess()));
}

int CftlCommandGetNewContainerId::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());


   // Query for creating new entry
   cQSqlQuery.prepare("insert into WMS_DM_CONTAINER "
                       "(ClassId, Keyname, LastChange, CreatorId, ModifierId, Caption, TempSessionId)"
                       "values(?, ?, ?, ?, ?, ?, ?)");

   cQSqlQuery.addBindValue(m_lClassId);
   cQSqlQuery.addBindValue(INIT_CONTAINER_NAME);
   cQSqlQuery.addBindValue(QDateTime::currentDateTime());
   cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
   cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
   cQSqlQuery.addBindValue(INIT_CONTAINER_NAME);
   cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());


   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      // query for reading new id
      cQSqlQuery.prepare("select ContainerId from WMS_DM_CONTAINER where ClassId = ? AND TempSessionId = ?");
      cQSqlQuery.addBindValue(m_lClassId);
      cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());

      if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
      {
         cQSqlQuery.first();
          if(cQSqlQuery.isValid())
          {
            lRet = cQSqlQuery.value(0).toInt();
         }
         else
         {
            lRet = EC(eDmNoNewIdCreated);
            ERR("The query reported no errors but dataset was not found!!!");
         }
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
         ERR("Getting new Class Id failed (SELECT COMMAND).");
      }
   }
   else
   {
      lRet = EC(eDmLockingError);
      ERR("Getting new Class Id failed (INSERT COMMAND).");
   }

   return lRet;
}
