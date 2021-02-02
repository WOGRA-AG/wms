#include <QUuid>
#include <QThread>

#include "CdbCommandGetNewSession.h"

CdbCommandGetNewSession::CdbCommandGetNewSession(QString p_qstrApplication,
                                                 long p_lUserId,
                                                 QString p_qstrBaseAuth,
                                                 CdbDataAccess* p_ppDataAccess)
    : CdbAbstractCommandTransactional(p_ppDataAccess),
      m_qstrApplication(p_qstrApplication),
      m_qstrBaseAuth(p_qstrBaseAuth),
      m_lUserId(p_lUserId),
      m_lSessionId(0)
{
}

CdbCommandGetNewSession::~CdbCommandGetNewSession()
{
}

int CdbCommandGetNewSession::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;

    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    QDateTime qdtLoginDate = QDateTime::currentDateTime();
    QString qstrLoginDate = CwmsUtilities::ChangeDateToString(qdtLoginDate);
    m_qstrApplication = QUuid::createUuid().toString();
    qstrQuery = QString("insert into WMS_UM_SESSION(UserId, State, LoginDate, Application, Last_Request, BaseAuth) "
                        "values(%1, %2, %3, '%4', %5, %6)")
                        .arg(m_lUserId)
                        .arg("true")
                        .arg(qstrLoginDate)
                        .arg(m_qstrApplication)
                        .arg(qstrLoginDate)
                        .arg(qstrLoginDate);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {

       qstrQuery = QString("select SessionId from WMS_UM_SESSION "
                           "where UserId = %1 and State = true and Application = '%2'")
                           .arg(m_lUserId)
                           .arg(m_qstrApplication);

       if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
       {
          cQSqlQuery.last();
          if(cQSqlQuery.isValid())
          {
             m_lSessionId = cQSqlQuery.value(0).toInt();
             INFO("New SessionId: " + QString::number(m_lSessionId) + " App ID: " + m_qstrApplication);
             iRet = EC(eDmOk);
          }
          else
          {
             iRet = EC(eDmSessionCreationError);
             ERR("The query execution returned no error but the insert failed!!!");
          }
       }
       else
       {
          iRet = EC(eDmInvalidSelectStatement);
          ERR("Error in executing query!!");
       }
    }
    else
    {
       iRet = EC(eDmInvalidInsertStatement);
       ERR("Error in executing query!!");
    }

    return iRet;
}

bool CdbCommandGetNewSession::CheckValid()
{
    return (!m_qstrApplication.isEmpty() && m_lUserId > 0);
}

int CdbCommandGetNewSession::GetResult()
{
    return m_lSessionId;
}

bool CdbCommandGetNewSession::NeedsActiveSession()
{
    return false;
}
