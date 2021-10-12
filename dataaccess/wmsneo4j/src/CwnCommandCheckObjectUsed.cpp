#include "CwnCommandCheckObjectUsed.h"

#include "CwnCommandStdHeader.h"

CwnCommandCheckObjectUsed::CwnCommandCheckObjectUsed(qint64 p_lObjectId,qint64 p_lContainerId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lObjectId(p_lObjectId),
  m_lContainerId(p_lContainerId)
{
}


CwnCommandCheckObjectUsed::~CwnCommandCheckObjectUsed()
{

}

bool CwnCommandCheckObjectUsed::CheckValid()
{
    return (m_lContainerId > 0 && m_lObjectId > 0);
}

QString CwnCommandCheckObjectUsed::createQuery()
{
    QString query = QString("MATCH (o:WMS_DM_OBJECT)<-[r:objectRefValue]-() WHERE id(o)=%1 RETURN count(r);")
                    .arg(m_lObjectId);

    return query;
}

int CwnCommandCheckObjectUsed::Execute()
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

void CwnCommandCheckObjectUsed::interpretAnswer(QVariant &Ret)
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

            int lValue = 0;
            lValue = list->at(0).toInt();

            if (lValue > 0)
            {
               Ret = CdmLogging::eDmTrue;
            }
            else
            {
               Ret = CdmLogging::eDmFalse;
            }
        }
    }
}
