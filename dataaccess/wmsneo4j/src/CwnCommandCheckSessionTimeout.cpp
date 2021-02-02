#include "CwnCommandCheckSessionTimeout.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandCheckSessionTimeout::CwnCommandCheckSessionTimeout(int p_iTimeout, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_iTimeout(p_iTimeout) // Minutes
{
}


CwnCommandCheckSessionTimeout::~CwnCommandCheckSessionTimeout()
{

}

QString CwnCommandCheckSessionTimeout::createQuery()
{
   QDateTime qdtDateTime = QDateTime::currentDateTime();

   QString qstrQuery;

   qstrQuery =
            QString("MATCH(s:Session) WHERE s.Last_Request <= %2 and s.State = 1 SET s.State = 0, s.LogoutDate = %1;")
            .arg(qdtDateTime.toTime_t())
            .arg(qdtDateTime.addSecs(m_iTimeout * 60 * (-1)).toTime_t());
    return qstrQuery;
}

bool CwnCommandCheckSessionTimeout::CheckValid()
{
    return true;
}

int CwnCommandCheckSessionTimeout::Execute()
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

void CwnCommandCheckSessionTimeout::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=-1;
    }
}
