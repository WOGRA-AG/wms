#include "CwnCommandCheckMethodLocked.h"
#include "CwnCommandLockMethod.h"

#include "CwnCommandStdHeader.h"

CwnCommandLockMethod::CwnCommandLockMethod(qint64 p_lSessionId,qint64 p_lMethodId,CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lMethodId(p_lMethodId)
{
}

CwnCommandLockMethod::~CwnCommandLockMethod()
{

}

bool CwnCommandLockMethod::CheckValid()
{
    return (m_lSessionId >0 && m_lMethodId > 0);
}


QString CwnCommandLockMethod::createQuery()
{
    QString query = QString("MATCH (s:Session),(o:WMS_CLASS_METHOD) WHERE id(o)=%1 AND id(s)=%2 CREATE (s)-[:SessionMethodLocked]->(w:WMS_DM_LOCKEDMETHOD)<-[:MethodLocked]-(o) RETURN id(s),id(w),id(o);")
                    .arg(m_lMethodId)
                    .arg(m_lSessionId);
    return query;
}

void CwnCommandLockMethod::interpretAnswer(QVariant &Ret)
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
            INFO("Could not lock Method!")
        }
    }
}

int CwnCommandLockMethod::Execute()
{
   qint64 lRet = 0;

    CwnCommandCheckMethodLocked command(m_lMethodId, m_lSessionId, GetDataAccess());
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
        INFO("Method is locked by another user or yourself");
        lRet = -1;
    }
    return static_cast<int>(lRet);
}
