#include "CwnCommandUnlockMethod.h"

#include "CwnCommandStdHeader.h"

CwnCommandUnlockMethod::CwnCommandUnlockMethod(long p_lSessionId, long p_lMethodId, CwnDataAccess *p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lMethodId(p_lMethodId)
{

}

CwnCommandUnlockMethod::~CwnCommandUnlockMethod()
{

}

bool CwnCommandUnlockMethod::CheckValid()
{
    return (m_lSessionId >0 && m_lMethodId > 0);
}

QString CwnCommandUnlockMethod::createQuery()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (s:Session)-[rs:SessionMethodLocked]->(w:WMS_DM_LOCKEDMETHOD)<-[ro:MethodLocked]-(o:WMS_CLASS_METHOD) WHERE id(o)=%1 DELETE rs,ro,w RETURN count(w)")
            .arg(m_lMethodId);

    return qstrQuery;
}

void CwnCommandUnlockMethod::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            if(!(list->at(0).toInt()>0))
            {
                Ret = 0;
                ERR("The MethodLock could not be deleted.");
            }
            else
            {
                Ret = 1;
            }
        }
        else
        {
            Ret = -1014;
            ERR("The User(SessionId) did not lock the Method.");
        }
    }
}

int CwnCommandUnlockMethod::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}
