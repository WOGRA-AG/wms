// System and Qt Includes
#include <QSqlQuery>
#include <QDateTime>

// Own Includes
#include "CwmsUtilities.h"
#include "CdbCommandGetNewContainerId.h"

CdbCommandGetNewContainerId::CdbCommandGetNewContainerId(qint64 p_lClassId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lClassId(p_lClassId),
  m_lSessionId(p_lSessionId)
{
}

CdbCommandGetNewContainerId::~CdbCommandGetNewContainerId()
{

}

bool CdbCommandGetNewContainerId::CheckValid()
{
    return (m_lClassId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

int CdbCommandGetNewContainerId::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   // Query for creating new entry
   qstrQuery = QString("insert into WMS_DM_OBJECTLIST "
                       "(ClassId, Keyname, LastChange, CreatorId, ModifierId, Caption, TempSessionId) "
                       "values(%1, '%2', %3, %4, %5, '%6', %7)")
                       .arg(m_lClassId)
                       .arg("New_Container")
                       .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                       .arg(0) // will be filled later
                       .arg(0) // will be filled later
                       .arg("New_Container")
                       .arg(m_lSessionId);

   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      // query for reading new id
      qstrQuery = QString("select ObjectListId from WMS_DM_OBJECTLIST "
                          "where ClassId = %1 AND TempSessionId = %2")
                          .arg(m_lClassId)
                          .arg(m_lSessionId);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
          if(cQSqlQuery.isValid())
          {

            // Value in col 0 is ObjectListId
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
