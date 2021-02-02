#include "CwnCommandExistClass.h"

#include "CwnCommandStdHeader.h"


CwnCommandExistClass::CwnCommandExistClass(long p_lSchemeId, QString p_qstrKeyname, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_qstrKeyname(p_qstrKeyname)
{

}

CwnCommandExistClass::~CwnCommandExistClass()
{

}

QString CwnCommandExistClass::createQuery()
{
    QString query = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class {Keyname:\'%1\'}) WHERE id(s)=%2 RETURN id(c);")
                .arg(m_qstrKeyname)
                .arg(m_lSchemeId);
    //qDebug() << query;
    return query;
}

void CwnCommandExistClass::interpretAnswer(QVariant &Ret)
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
            Ret = EC(eDmOk);
            m_bResult = true;
        }
        else
        {
            Ret = EC(eDmFalse);
            m_bResult = false;
            ERR("No class found.");
        }
    }
}

int CwnCommandExistClass::Execute()
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

bool CwnCommandExistClass::CheckValid()
{
    return (m_lSchemeId > 0 &&
            !m_qstrKeyname.isEmpty());
}

bool CwnCommandExistClass::GetResult()
{
    return m_bResult;
}
