#include "CwnCommandGetOwner.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetOwner::CwnCommandGetOwner(qint64 p_lContainerId,qint64 p_lObjectId, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_lObjectId(p_lObjectId),
      m_lOwnerContainerId(0),
      m_lOwnerObjectId(0)
{

}

CwnCommandGetOwner::~CwnCommandGetOwner()
{

}

QString CwnCommandGetOwner::createQueryForFindObjectOwner()
{
    return QString("MATCH (o:WMS_DM_OBJECT)<-[:objectRefValue]-(v:WMS_VALUE)<-[:member_to_value]-(m:WMS_CLASS_MEMBER)-[:member_to_value]->(:WMS_VALUE)<-[:Object_value]-(e:WMS_DM_OBJECT)<-[:hasObjects]-(i:WMS_DM_OBJECTLIST) WHERE m.Owner='true' AND id(o)=%1 RETURN id(e),id(i)").arg(m_lObjectId);
}

QString CwnCommandGetOwner::createQueryForFindContainerOwner()
{
    return QString("MATCH (o:WMS_DM_OBJECTLIST)<-[:objectListRefValue]-(v:WMS_VALUE)<-[:member_to_value]-(m:WMS_CLASS_MEMBER)-[:member_to_value]->(:WMS_VALUE)<-[:Object_value]-(e:WMS_DM_OBJECT)<-[:hasObjects]-(i:WMS_DM_OBJECTLIST) WHERE m.Owner='true' AND id(o)=%1 RETURN id(e),id(i)").arg(m_lContainerId);
}

qint64 CwnCommandGetOwner::GetOwnerObjectId()
{
    return m_lOwnerObjectId;
}

qint64 CwnCommandGetOwner::GetOwnerContainerId()
{
    return m_lOwnerContainerId;
}

bool CwnCommandGetOwner::CheckValid()
{
    return (m_lContainerId > 0);
}

int CwnCommandGetOwner::Execute()
{
    int iRet = EC(eDmUnknownSqlError);

    if (m_lObjectId > 0)
    {
        QString payload = createJson(createQueryForFindObjectOwner());
        queryCausedError = payload;
        ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
        QVariant Ret;
        interpretAnswer(Ret);
        iRet = Ret.toInt();
    }
    else
    {
        QString payload = createJson(createQueryForFindContainerOwner());
        queryCausedError = payload;
        ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
        QVariant Ret;
        interpretAnswer(Ret);
        iRet = Ret.toInt();
    }

    return iRet;
}

void CwnCommandGetOwner::interpretAnswer(QVariant &Ret)
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

            m_lOwnerObjectId = row->at(0).toInt();
            m_lOwnerContainerId = row->at(1).toInt();
            Ret=1;
        }
        else
        {
            INFO("Neither Object- nor ObjectList- Owner found, DB maybe corrupt.");
            Ret=1;
        }
    }
}
