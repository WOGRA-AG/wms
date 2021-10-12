#include "CwnCommandLogout.h"

// System and QT Includes
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandLogout::CwnCommandLogout(qint64 p_lSessionId,CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId)
{
}

CwnCommandLogout::~CwnCommandLogout()
{

}

QString CwnCommandLogout::createQuery()
{

    QString query = QString("MATCH (s:Session) WHERE id(s) = %1 SET s+={State: %2, LogoutDate: %3} RETURN s;")
            .arg(m_lSessionId)
            .arg(false)
            .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()));

    return query;
}

void CwnCommandLogout::interpretAnswer(QVariant &Ret)
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
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {
            Ret = 1;
        }
        else
        {
            Ret = -1;
            ERR("No Session found by id.");
        }
   }
}

int CwnCommandLogout::Execute()
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

bool CwnCommandLogout::CheckValid()
{
    return (m_lSessionId >= 0);
}
