#include <QDateTime>
#include "CwnHelper.h"
#include "CwnCommandUpdateSession.h"

#include "CwnCommandStdHeader.h"

CwnCommandUpdateSession::CwnCommandUpdateSession(long p_lSessionId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSessionId(p_lSessionId)
{
}
CwnCommandUpdateSession::CwnCommandUpdateSession(QString p_qstrBaseAuth, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSessionId(0),
  m_qstrBaseAuth(p_qstrBaseAuth)
{
}


CwnCommandUpdateSession::~CwnCommandUpdateSession()
{
}

QString CwnCommandUpdateSession::createQuery()
{
    QString qstrUpdate;

    QDateTime qdtDateTime = QDateTime::currentDateTime();

    if (m_lSessionId > 0)
    {
        qstrUpdate = QString("MATCH (s:Session) WHERE id(s)=%2 SET s.LAST_REQUEST=%1 RETURN 1")
                .arg(qdtDateTime.toTime_t())
                .arg(m_lSessionId);
    }
    else if (!m_qstrBaseAuth.isEmpty())
    {
        qstrUpdate = QString("MATCH (s:Session) WHERE s.BaseAuth=\'%2\' SET s.LAST_REQUEST=%1 RETURN 1")
                .arg(qdtDateTime.toTime_t())
                .arg(m_qstrBaseAuth);
    }

    return qstrUpdate;
}

int CwnCommandUpdateSession::Execute()
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

void CwnCommandUpdateSession::interpretAnswer(QVariant &Ret)
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
            //qDebug() << rowMap;
            Ret = 1;
        }
        else
        {
            Ret = -1;
            ERR("Could not find Session.");
        }
    }
}

bool CwnCommandUpdateSession::CheckValid()
{
    return (m_lSessionId > 0 || !m_qstrBaseAuth.isEmpty());
}

bool CwnCommandUpdateSession::NeedsActiveSession()
{
    return false;
}
