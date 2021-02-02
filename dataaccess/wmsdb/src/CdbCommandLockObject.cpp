
#include "CdbCommandCheckObjectLocked.h"
#include "CdbCommandLockObject.h"

CdbCommandLockObject::CdbCommandLockObject(long p_lSessionId, long p_lObjectId,CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lObjectId(p_lObjectId)
{
}

CdbCommandLockObject::~CdbCommandLockObject()
{

}

bool CdbCommandLockObject::CheckValid()
{
    return (m_lSessionId >0 && m_lObjectId > 0);
}

int CdbCommandLockObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    CdbCommandCheckObjectLocked command(m_lObjectId, m_lSessionId, GetDataAccess());
    lRet = command.Run();

    if(!lRet)
    {
       QSqlQuery cQSqlQuery;
       QString qstrQuery;

       // asking table if this object is inserted
       qstrQuery = QString("insert into WMS_DM_LOCKEDOBJECT (ObjectId, SessionId) values(%1, %2)")
                           .arg(m_lObjectId)
                           .arg(m_lSessionId);

       if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
       {
          lRet = EC(eDmTrue);
       }
       else
       {
          lRet = EC(eDmInvalidInsertStatement);
       }
    }
    else
    {
       INFO("Object is locked by another user.");
       lRet = EC(eDmObjectDeathLock);
    }

    return lRet;
}
