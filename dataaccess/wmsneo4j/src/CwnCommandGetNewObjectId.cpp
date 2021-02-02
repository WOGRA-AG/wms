#include "CwnCommandGetNewObjectId.h"
#include "CwnHelper.h"

#include <QDate>

#include "CwnCommandStdHeader.h"

CwnCommandGetNewObjectId::CwnCommandGetNewObjectId(long p_lContainerId, long p_lSessionId, CwnDataAccess* p_pDataAccess):CwnCommandBase(p_pDataAccess),
m_lContainerId(p_lContainerId),m_lSessionId(p_lSessionId)
{

}

CwnCommandGetNewObjectId::~CwnCommandGetNewObjectId()
{

}

bool CwnCommandGetNewObjectId::CheckValid()
{
    return (m_lContainerId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

QString CwnCommandGetNewObjectId::createQuery()
{

    QString qstrQuery;
    QString qstrObjKeyname = "NewObject";

    // Query for creating new entry
    qstrQuery = QString("MATCH (c:WMS_DM_OBJECTLIST) WHERE id(c)=%1 CREATE(o:WMS_DM_OBJECT{Keyname:\'%2\', LastChange:%3, Caption:\'%4\'})<-[:hasObjects]-(c) RETURN id(o)")
                        .arg(m_lContainerId)
                        .arg(qstrObjKeyname)
                        .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()))
                        .arg(qstrObjKeyname);
    //qDebug() << qstrQuery;
    return qstrQuery;
}

void CwnCommandGetNewObjectId::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();
        if(dataListCon->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataListCon->at(0).data());
            const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            Ret = row->at(0).toInt();
        }
        else
        {
            Ret = -1;
            ERR("The Object could not be created.");
        }
    }
}

int CwnCommandGetNewObjectId::Execute()
{
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    return Ret.toInt();
}

