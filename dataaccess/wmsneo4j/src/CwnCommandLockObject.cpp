#include "CwnCommandCheckObjectLocked.h"
#include "CwnCommandLockObject.h"

#include "CwnCommandStdHeader.h"

CwnCommandLockObject::CwnCommandLockObject(long p_lSessionId, long p_lObjectId,CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lObjectId(p_lObjectId)
{
}

CwnCommandLockObject::~CwnCommandLockObject()
{

}

bool CwnCommandLockObject::CheckValid()
{
    return (m_lSessionId >0 && m_lObjectId > 0);
}


QString CwnCommandLockObject::createQuery()
{
    QString query = QString("MATCH (s:Session),(o:WMS_DM_OBJECT) WHERE id(o)=%1 AND id(s)=%2 CREATE (s)-[:SessionObjectLocked]->(w:WMS_DM_LOCKEDOBJECT)<-[:ObjectLocked]-(o) RETURN id(s),id(w),id(o);")
                    .arg(m_lObjectId)
                    .arg(m_lSessionId);
    return query;
}

void CwnCommandLockObject::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=EC(eDmInvalidSelectStatement);

    }
    else
    {
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {
            Ret=1;
        }
        else
        {
            Ret=0;
            INFO("Could not lock Object!")
        }
    }
}

int CwnCommandLockObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    CwnCommandCheckObjectLocked command(m_lObjectId, m_lSessionId, GetDataAccess());
    lRet = command.Run();

    if(!lRet)
    {
        QString payload = createJson(createQuery());
        queryCausedError = payload;
        ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
        QVariant Ret;
        interpretAnswer(Ret);
        lRet = Ret.toInt();
    }
    else
    {
        INFO("Object is locked by another user or yourself");
        lRet = EC(eDmObjectDeathLock);
    }
    return static_cast<int>(lRet);
}
