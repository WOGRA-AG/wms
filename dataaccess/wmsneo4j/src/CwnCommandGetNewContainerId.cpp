#include "CwnCommandGetNewContainerId.h"
#include "CwnHelper.h"

#include <QDate>

#include "CwnCommandStdHeader.h"

CwnCommandGetNewContainerId::CwnCommandGetNewContainerId(long p_lClassId, long p_lSessionId, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lClassId(p_lClassId),
      m_lSessionId(p_lSessionId)
{
}

CwnCommandGetNewContainerId::~CwnCommandGetNewContainerId()
{

}

bool CwnCommandGetNewContainerId::CheckValid()
{
    return (m_lClassId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

QString CwnCommandGetNewContainerId::createQuery()
{
    QString qstrQuery;
    // Query for creating new entry
    qstrQuery = QString("MATCH (c:Class) WHERE id(c)=%1 CREATE (o:WMS_DM_OBJECTLIST{Keyname:\'%2\', LastChange:%3, Caption:\'%4\'})<-[h:hasObjectContainer]-(c) RETURN id(o);")
                .arg(m_lClassId)
                .arg("New Container")
                .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()))
                .arg("New ObjectList");
    //qDebug() << qstrQuery;
    return qstrQuery;
}

void CwnCommandGetNewContainerId::interpretAnswer(QVariant &Ret)
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
            ERR("The ObjectContainer could not be created.");
        }
    }
}

int CwnCommandGetNewContainerId::Execute()
{
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    return Ret.toInt();
}

