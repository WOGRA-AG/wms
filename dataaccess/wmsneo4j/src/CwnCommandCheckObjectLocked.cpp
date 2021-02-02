#include "CwnCommandStdHeader.h"

#include "CwnCommandCheckObjectLocked.h"
#include "CwnCommandUnlockObject.h"

CwnCommandCheckObjectLocked::CwnCommandCheckObjectLocked(long p_lObjectId, long p_lSessionId, CwnDataAccess* p_pDataAccess): CwnCommandBase(p_pDataAccess),
      m_lObjectId(p_lObjectId),
      m_lSessionId(p_lSessionId)
{

}

CwnCommandCheckObjectLocked::~CwnCommandCheckObjectLocked()
{

}

bool CwnCommandCheckObjectLocked::CheckValid()
{
    return (m_lObjectId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

QString CwnCommandCheckObjectLocked::createQuery()
{
    QString query = QString("MATCH (s:Session)-[:SessionObjectLocked]->(w:WMS_DM_LOCKEDOBJECT)<-[r:ObjectLocked]-(o:WMS_DM_OBJECT) WHERE id(o)=%1 RETURN id(s),s.State;")
                    .arg(m_lObjectId);

    return query;
}

int CwnCommandCheckObjectLocked::Execute()
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

void CwnCommandCheckObjectLocked::interpretAnswer(QVariant &Ret)
{
    Ret = CdmLogging::eDmObjectAccessError;
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
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            //Object is locked

            long lSessionId = list->at(0).toLongLong();
            INFO("Object with ID" + QString::number(m_lObjectId) +
                 " is locked by session " + QString::number(m_lSessionId));

            if(lSessionId == m_lSessionId)
            {
                CwnCommandUnlockObject command(m_lObjectId, lSessionId, GetDataAccess());
                command.Run();
                Ret = EC(eDmFalse);
                INFO("Object is locked by the same session(user), so it plays no role if this object is locked or not, he has all rights, deleted lock.");
            }
            else
            {
                //IF STATE=1 OBJECT IS LOCKED IF STATE=0 OBJECT IS NOT LOCKED, BUT AN OLD LOCK STILL EXIST
                if(!list->at(1).toBool())
                {
                    CwnCommandUnlockObject command(m_lObjectId, lSessionId, GetDataAccess());
                    command.Run();
                    Ret=EC(eDmFalse);
                    INFO("Objectlock deleted from an old Lock.")
                }
                else
                    Ret = EC(eDmTrue);
            }
        }
        else
        {
            Ret=EC(eDmFalse);
            INFO("Object is not locked.")
        }
    }
}

