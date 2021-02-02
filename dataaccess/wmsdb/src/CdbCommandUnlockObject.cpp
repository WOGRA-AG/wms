#include "CdbCommandUnlockObject.h"

CdbCommandUnlockObject::CdbCommandUnlockObject(long p_lSessionId, long p_lObjectId,CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lObjectId(p_lObjectId)
{
}

CdbCommandUnlockObject::~CdbCommandUnlockObject()
{

}

bool CdbCommandUnlockObject::CheckValid()
{
    return (m_lSessionId >0 && m_lObjectId > 0);
}

int CdbCommandUnlockObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // asking table if this object is inserted
    qstrQuery = QString("delete from WMS_DM_LOCKEDOBJECT where ObjectId = %1 and SessionId = %2")
                        .arg(m_lObjectId)
                        .arg(m_lSessionId);

    if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       lRet = EC(eDmOk);
    }
    else
    {
       lRet = EC(eDmInvalidDeleteStatement);
       INFO("It was not possible to unlock the object!!!");
    }

    return lRet;
}
