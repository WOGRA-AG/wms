#include "CwnCommandAddSchemeLanguage.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandAddSchemeLanguage::CwnCommandAddSchemeLanguage(long p_lSchemeId, QString p_qstrLanguage, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_qstrLanguage(p_qstrLanguage)
{
}

CwnCommandAddSchemeLanguage::~CwnCommandAddSchemeLanguage()
{

}

QString CwnCommandAddSchemeLanguage::createQuery()
{
    QString qstrQuery;

    qstrQuery = QString("MATCH (s:Scheme) WHERE id(s)=%1 MERGE (s)-[r:languages]->(n:WMS_LANGUAGES {language:\'%2\'}) RETURN id(n);")
                .arg(m_lSchemeId)
                .arg(CwnHelper::MaskStringForChanges(m_qstrLanguage));

    return qstrQuery;
}

void CwnCommandAddSchemeLanguage::interpretAnswer(QVariant &Ret)
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
        Ret = -1060;
        ERR("The language could not be created.");
    }
    else
    {
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();

        if(dataListCon->count()>0)
        {
            const QVariantMap* row = static_cast<const QVariantMap*>(dataListCon->at(0).data());
            const QVariantList* rowList = static_cast<const QVariantList*>(row->find("row")->data());
            //qDebug() << rowList[1].toBool();
            if(rowList->at(0).toInt()>0)
            {
                Ret = rowList->at(0);
                //qDebug() << rowList[0].toInt();
            }
        }
    }
}

int CwnCommandAddSchemeLanguage::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug() << payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;

}

bool CwnCommandAddSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && !m_qstrLanguage.isEmpty());
}
