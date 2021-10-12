#include <QUuid>

#include "CftlCommandGetNewSession.h"

CftlCommandGetNewSession::CftlCommandGetNewSession(QString p_qstrApplication,
                                                qint64 p_lUserId,
                                                 CftlDataAccess* p_ppDataAccess)
    : CftlAbstractTransactionalCommand(p_ppDataAccess),
      m_qstrApplication(p_qstrApplication),
      m_lUserId(p_lUserId),
      m_lSessionId(0)
{
}

CftlCommandGetNewSession::~CftlCommandGetNewSession()
{
}

int CftlCommandGetNewSession::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QDateTime qdtLoginDate = QDateTime::currentDateTime();
    QSqlDatabase database = GetSqlDatabase();
    QSqlQuery cQSqlQuery(database);
    m_qstrApplication = QUuid::createUuid().toString();
    cQSqlQuery.prepare("insert into WMS_UM_SESSION(UserId, State, LoginDate, Application, LAST_REQUEST) "
                        "values(?, ?, ?, ?, ?)");
    cQSqlQuery.addBindValue(m_lUserId);
    cQSqlQuery.addBindValue(true);
    cQSqlQuery.addBindValue(qdtLoginDate);
    cQSqlQuery.addBindValue(m_qstrApplication);
    cQSqlQuery.addBindValue(qdtLoginDate);
    iRet = ExecuteQuery(cQSqlQuery);

    if(SUCCESSFULL(iRet))
    {
        QSqlQuery cQuerySelect(database);
        cQuerySelect.prepare("select SessionId, LoginDate from WMS_UM_SESSION "
                           "where UserId = ? and State = ? and Application = ?");
       cQuerySelect.addBindValue(m_lUserId);
       cQuerySelect.addBindValue(true);
       cQuerySelect.addBindValue(m_qstrApplication);


       if(SUCCESSFULL(ExecuteQuery(cQuerySelect)))
       {
          cQuerySelect.last();
          if(cQuerySelect.isValid())
          {
             m_lSessionId = cQuerySelect.value(0).toInt();
             iRet = EC(eDmOk);
          }
          else
          {
              QString qstrQuery = cQuerySelect.executedQuery();
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

bool CftlCommandGetNewSession::NeedsSessionCheck()
{
    return false;
}

bool CftlCommandGetNewSession::CheckValid()
{
    return (!m_qstrApplication.isEmpty() && m_lUserId > 0);
}

int CftlCommandGetNewSession::GetResult()
{
    return m_lSessionId;
}
