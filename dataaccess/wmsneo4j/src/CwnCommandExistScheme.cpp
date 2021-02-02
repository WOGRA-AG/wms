#include "CwnCommandExistScheme.h"

#include "CwnCommandStdHeader.h"


CwnCommandExistScheme::CwnCommandExistScheme(CwnDataAccess *m_rpDataAccess, QString qstrKeyname)
: CwnCommandBase(m_rpDataAccess),
  m_qstrKeyname(qstrKeyname)

{

}

CwnCommandExistScheme::~CwnCommandExistScheme()
{

}

QString CwnCommandExistScheme::createQuery()
{
    QString query = QString("MATCH(n:Scheme {schemename:\'%1\'}) RETURN n;")
                 .arg(m_qstrKeyname);
    return query;
}

void CwnCommandExistScheme::interpretAnswer(QVariant &Ret)
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
        Ret=EC(eDmUnknownDBQueryError);
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            Ret = EC(eDmTrue);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No Schemes found.");

        }
    }
}

int CwnCommandExistScheme::Execute()
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

bool CwnCommandExistScheme::CheckValid()
{
    return (!m_qstrKeyname.isEmpty());
}
