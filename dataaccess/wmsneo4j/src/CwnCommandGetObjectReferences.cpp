#include "CwnCommandGetObjectReferences.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetObjectReferences::CwnCommandGetObjectReferences(qint64 p_lContainerId,qint64 p_lObjectId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lContainerId(p_lContainerId),
  m_lObjectId(p_lObjectId)
{
}


CwnCommandGetObjectReferences::~CwnCommandGetObjectReferences()
{

}

bool CwnCommandGetObjectReferences::CheckValid()
{
    return (m_lContainerId > 0 && m_lObjectId > 0);
}

QString CwnCommandGetObjectReferences::createQuery()
{
    QString query = QString("MATCH(v:WMS_VALUE)-[:objectRefValue]->(o:WMS_DM_OBJECT)<-[:hasObjects]-(oc)) WHERE v.val=%1 RETURN DISTINCT id(o), id(oc);")
                 .arg(m_lObjectId);
    return query;
}

int CwnCommandGetObjectReferences::Execute()
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

void CwnCommandGetObjectReferences::interpretAnswer(QVariant &Ret)
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
           QList<QVariant>::ConstIterator it;
           for(it=dataListCon->begin();it!=dataListCon->end();it++) // loading each class
           {
               const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
               const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());


              qint64 lObjectListId = row->at(1).toInt();
              qint64 lObjectId = row->at(0).toInt();
               m_qmReferences.insert(lObjectId, lObjectListId);
            }
            Ret=1;
        }
        else
        {
            Ret = -1;
            ERR("The Value have no Objectreferences.");
        }
    }
}

QMap<qint64,qint64> CwnCommandGetObjectReferences::GetResult()
{
    return m_qmReferences;
}
