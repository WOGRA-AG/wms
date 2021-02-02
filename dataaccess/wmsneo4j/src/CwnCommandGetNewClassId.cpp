#include "CwnCommandGetNewClassId.h"
#include "CwnHelper.h"

#include <QDate>

#include "CwnCommandStdHeader.h"

CwnCommandGetNewClassId::CwnCommandGetNewClassId(long p_lSessionId, long p_lSchemeId, CwnDataAccess* p_pDataAccess):
    CwnCommandBase(p_pDataAccess),
    m_lSchemeId(p_lSchemeId),
    m_lSessionId(p_lSessionId)
{

}

CwnCommandGetNewClassId::~CwnCommandGetNewClassId()
{

}

QString CwnCommandGetNewClassId::createQuery()
{
    QString qstrQuery;
    // Query for creating new entry
    qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 CREATE (s)-[r:hasClass]->(c:Class {Keyname:\'%2\', LastChange:%3, Caption:\'%4\'}) RETURN id(c);")
                        .arg(m_lSchemeId)
                        .arg("NewClass")
                        .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()))
                        .arg("NewClass");
    return qstrQuery;
}

void CwnCommandGetNewClassId::interpretAnswer(QVariant &Ret)
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
            ERR("The Class could not be created.");
        }
    }
}

int CwnCommandGetNewClassId::Execute()
{
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    return Ret.toInt();
}

bool CwnCommandGetNewClassId::CheckValid()
{
    return (m_lSchemeId > 0 && m_lSessionId > 0);
}
