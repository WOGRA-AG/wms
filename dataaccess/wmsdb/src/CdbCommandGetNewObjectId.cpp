// System and Qt Includes
#include <QSqlQuery>
#include <QDateTime>

// Own Includes
#include "CwmsUtilities.h"
#include "CdbCommandGetNewObjectId.h"

CdbCommandGetNewObjectId::CdbCommandGetNewObjectId(long p_lContainerId, long p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lContainerId(p_lContainerId),
  m_lSessionId(p_lSessionId)
{
}

CdbCommandGetNewObjectId::~CdbCommandGetNewObjectId()
{

}

bool CdbCommandGetNewObjectId::CheckValid()
{
    return (m_lContainerId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

int CdbCommandGetNewObjectId::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(GetDataAccess()))
    {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;
      QString qstrObjKeyname = "NewObject";

      // Query for creating new entry
      qstrQuery = QString("insert into WMS_DM_OBJECT "
                          "(ObjectListId, Keyname,  LastChange, CreatorId, ModifierId, Caption, TempSessionId)"
                          "values(%1, '%2', %3, %4, %5, '%6', %7)")
                          .arg(m_lContainerId)
                          .arg(qstrObjKeyname)
                          .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                          .arg(0) // will be filled later
                          .arg(0) // will be filled later
                          .arg(qstrObjKeyname)
                          .arg(m_lSessionId);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         // query for reading new id the keyname is needed because the id value could be doubled in table.
         qstrQuery = QString("select ObjectId from WMS_DM_OBJECT "
                             "where ObjectListId = %1 and Keyname = '%2' "
                             "and TempSessionId = %3")
                             .arg(m_lContainerId)
                             .arg(qstrObjKeyname)
                             .arg(m_lSessionId);

         if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
         {
            cQSqlQuery.first();
            if(cQSqlQuery.isValid())
            {
               // Value in col 0 is ObjectId
               lRet = cQSqlQuery.value(0).toInt();
            }
            else
            {
               lRet = EC(eDmNoUniqueId);
               ERR("Impossible Error occurred (BaseId more the once)!!!");
            }
         }
         else
         {
            lRet = EC(eDmInvalidSelectStatement);
            ERR("Getting new Object Id failed (SELECT COMMAND).");
         }
      }
      else
      {
         lRet = EC(eDmInvalidInsertStatement);
         ERR("Getting new Object Id failed (INSERT COMMAND).");
      }
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}
