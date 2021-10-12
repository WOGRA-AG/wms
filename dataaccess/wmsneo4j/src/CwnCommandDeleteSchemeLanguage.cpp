#include "CwnCommandDeleteSchemeLanguage.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeleteSchemeLanguage::CwnCommandDeleteSchemeLanguage(qint64 p_lSchemeId, int p_lLanguage, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_lLanguage(p_lLanguage)
{
}


CwnCommandDeleteSchemeLanguage::~CwnCommandDeleteSchemeLanguage()
{
}

bool CwnCommandDeleteSchemeLanguage::CheckValid()
{
    return (m_lSchemeId > 0 && m_lLanguage > 0);
}

QString CwnCommandDeleteSchemeLanguage::createQuery()
{
    QString query = QString("MATCH (s:Scheme)-[g:languages]->(L:WMS_LANGUAGES) WHERE id(s)=%1 AND id(L)=%2 DELETE L RETURN 1;")
        .arg(m_lSchemeId )
        .arg(m_lLanguage);
    return query;
}

void CwnCommandDeleteSchemeLanguage::interpretAnswer(QVariant &Ret)
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
            INFO("Schemelanguage deleted.");
            Ret = 1;
        }
        else
        {
            Ret = -1;
            ERR("No Schemeslanguages found by id.");
        }
    }
}

int CwnCommandDeleteSchemeLanguage::Execute()
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
