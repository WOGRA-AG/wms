#include "CwnCommandGetNewSession.h"
#include "CwnHelper.h"

#include <QDate>
#include <QUuid>
#include <QThread>

#include "CumUser.h"

#include "CwnCommandStdHeader.h"

CwnCommandGetNewSession::CwnCommandGetNewSession(QString p_qstrApplication,qint64 p_lUserId, CwnDataAccess *m_rpDataAccess)
    : CwnCommandBase(m_rpDataAccess),
    m_qstrApplication(p_qstrApplication),
    m_lUserId(p_lUserId),
    m_lSessionId(0)
{
}

CwnCommandGetNewSession::~CwnCommandGetNewSession()
{

}

QString CwnCommandGetNewSession::createQueryForSessionInsert()
{
    m_qdtLoginDate = QDateTime::currentDateTime();
    m_qstrApplication = QString::number((size_t)QThread::currentThread()) + QString::number(m_qdtLoginDate.toMSecsSinceEpoch());
    QString query = QString("MATCH (a:User) WHERE id(a) = %1 CREATE(s:Session{State: '%2', LoginDate: %3, LogoutDate: 0, Application: '%4', Last_Request: %5})-[r:SessionConnectionToUser]->(a) RETURN id(s);")
                 .arg(m_lUserId)
                 .arg(true)
                 .arg(CwnHelper::ChangeDateToString(m_qdtLoginDate))
                 .arg(m_qstrApplication)
                 .arg(m_qdtLoginDate.toTime_t());
    return query;
}

void CwnCommandGetNewSession::interpretAnswer(QVariant &Ret)
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

            m_lSessionId = row->at(0).toInt();

            INFO("New SessionId: " + QString::number(m_lSessionId) + " App ID: " + m_qstrApplication);
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = -1;
            ERR("The Session could not be created.");
        }
    }
}

int CwnCommandGetNewSession::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQueryForSessionInsert());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandGetNewSession::CheckValid()
{
    return (!m_qstrApplication.isEmpty() && m_lUserId >= 0);
}

int CwnCommandGetNewSession::GetResult()
{
    return static_cast<int>(m_lSessionId);
}


