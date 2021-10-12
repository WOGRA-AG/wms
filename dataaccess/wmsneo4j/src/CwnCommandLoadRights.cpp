#include "CwnCommandLoadRights.h"

#include "CwnCommandStdHeader.h"


CwnCommandLoadRights::CwnCommandLoadRights(CdmRights& p_rCcdmRights,qint64 p_lObjectId, QString p_qstrTableName, CwnDataAccess* p_DataAccess)
: CwnCommandBase(p_DataAccess),
m_lObjectId(p_lObjectId),
m_prCcdmRights(p_rCcdmRights),
m_pqstrTableName(p_qstrTableName)
{

}

CwnCommandLoadRights::~CwnCommandLoadRights()
{

}

QString CwnCommandLoadRights::createQuery()
{
    QString query = QString("MATCH (var)-[r:rights]->(u) WHERE id(var)=%1 RETURN r.rightId,id(u);")
            .arg(m_lObjectId);
    return query;
}

void CwnCommandLoadRights::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());
    this->answer=nullptr;

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
            QList<QVariant>::ConstIterator it;
            for(it=dataList->begin();it!=dataList->end();it++) // loading each class
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
                const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                //qDebug() << rowList;
                m_prCcdmRights.AddRight(row->at(1).toInt(),static_cast<EdmRight>(row->at(0).toInt()));
            }
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmOk);
            INFO("There are no rights in the Database.");
        }
    }
}

int CwnCommandLoadRights::Execute()
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

bool CwnCommandLoadRights::CheckValid()
{
    bool bRet = true;

    if (/* DISABLES CODE */ (false))
    {
        bRet = false;
    }

    return bRet;
}


