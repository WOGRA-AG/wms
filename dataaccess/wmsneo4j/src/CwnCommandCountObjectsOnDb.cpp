#include "CwnCommandCountObjectsOnDb.h"

#include "CwnCommandStdHeader.h"

CwnCommandCountObjectsOnDb::CwnCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CwnDataAccess* p_pDataAccess):CwnCommandBase(p_pDataAccess),
    m_rpContainer(p_pContainer)
{

}

CwnCommandCountObjectsOnDb::~CwnCommandCountObjectsOnDb(){

}

QString CwnCommandCountObjectsOnDb::createQuery()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (l:WMS_DM_OBJECTLIST)-[:hasObjects]->(o:WMS_DM_OBJECT) WHERE id(l)=%1 RETURN COUNT(o);")
                       .arg(m_rpContainer->GetId());

    return qstrQuery;
}

void CwnCommandCountObjectsOnDb::interpretAnswer(QVariant &Ret)
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
        Ret=-1;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());
            Ret = list->at(0).toLongLong();
        }
        else
        {
            Ret = CdmLogging::eDmFalse;
        }
    }
}

int CwnCommandCountObjectsOnDb::Execute()
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

bool CwnCommandCountObjectsOnDb::CheckValid()
{
    return CHKPTR(m_rpContainer);
}
