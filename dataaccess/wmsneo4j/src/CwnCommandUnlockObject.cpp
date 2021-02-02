#include "CwnCommandUnlockObject.h"

#include "CwnCommandStdHeader.h"

CwnCommandUnlockObject::CwnCommandUnlockObject(long p_lSessionId, long p_lObjectId, CwnDataAccess *p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_lObjectId(p_lObjectId)
{

}

CwnCommandUnlockObject::~CwnCommandUnlockObject()
{

}

bool CwnCommandUnlockObject::CheckValid()
{
    return (m_lSessionId >0 && m_lObjectId > 0);
}

QString CwnCommandUnlockObject::createQuery()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (s:Session)-[rs:SessionObjectLocked]->(w:WMS_DM_LOCKEDOBJECT)<-[ro:ObjectLocked]-(o:WMS_DM_OBJECT) WHERE id(o)=%1 DELETE rs,ro,w RETURN count(w)")
            .arg(m_lObjectId);

    return qstrQuery;
}

void CwnCommandUnlockObject::interpretAnswer(QVariant &Ret)
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
                Ret = EC(eDmTrue);
                INFO("The ObjectLock could not be deleted, because there is no lock.");
            }
            else
            {
                Ret = EC(eDmTrue);
                INFO("The ObjectLock could be deleted. Either old session Lock or same user lock.");
            }
        }
        else
        {
            Ret = -1014;
            ERR("The User(SessionId) did not lock the Object.");
        }
    }
}

int CwnCommandUnlockObject::Execute()
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
