#include "CwnCommandStdHeader.h"

#include "CwnCommandCheckMethodLocked.h"
#include "CwnCommandUnlockMethod.h"

CwnCommandCheckMethodLocked::CwnCommandCheckMethodLocked(qint64 p_lMethodId,qint64 p_lSessionId, CwnDataAccess* p_pDataAccess): CwnCommandBase(p_pDataAccess),
      m_lMethodId(p_lMethodId),
      m_lSessionId(p_lSessionId)
{

}

CwnCommandCheckMethodLocked::~CwnCommandCheckMethodLocked()
{

}

bool CwnCommandCheckMethodLocked::CheckValid()
{
    return (m_lMethodId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

QString CwnCommandCheckMethodLocked::createQuery()
{
    QString query = QString("MATCH (u:User)-[sctu:SessionConnectionToUser]->(s:Session)-[:SessionMethodLocked]->(w:WMS_DM_METHODLOCKED)<-[r:MethodLocked]-(o:WMS_CLASS_METHOD) WHERE id(o)=%1 RETURN id(s),s.State,u.login;")
                    .arg(m_lMethodId);

    return query;
}

int CwnCommandCheckMethodLocked::Execute()
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

void CwnCommandCheckMethodLocked::interpretAnswer(QVariant &Ret)
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
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            //Method is locked

           qint64 lSessionId = list->at(0).toLongLong();
            QString qstrLogin = list->at(2).toString();

            ERR("The method is under examination by User " + qstrLogin + ". SessionId: "
                + QString::number(lSessionId));

            if(lSessionId == m_lSessionId)
            {
                Ret = 1;
                INFO("Method is locked by the same session(user), so it plays no role if this Method is locked or not, he has all rigths.");
            }
            else
            {
                //IF STATE=1 METHOD IS LOCKED IF STATE=0 METHOD IS NOT LOCKED, BUT AN OLD LOCK STILL EXIST
                if(!list->at(1).toBool())
                {
                    CwnCommandUnlockMethod command(m_lMethodId, lSessionId, GetDataAccess());
                    command.Run();
                    Ret=0;
                }
                else
                    Ret = list->at(1).toBool();
            }
        }
        else
        {
            Ret=EC(eDmFalse);
            INFO("Method is not locked.")
        }
    }
}
