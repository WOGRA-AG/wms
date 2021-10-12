#include "CdmSessionManager.h"

#include "CftlCommandFindSession.h"

CftlCommandFindSession::CftlCommandFindSession(qint64 p_lSessionId,qint64 p_lUserId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(p_lUserId),
  m_pSession(nullptr)
{
}

CftlCommandFindSession::CftlCommandFindSession(qint64 p_lSessionId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(0),
  m_pSession(nullptr)
{
}

CftlCommandFindSession::CftlCommandFindSession(QString p_qstrBaseAuth, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSessionId(0),
  m_lUserId(0),
  m_qstrBaseAuth(p_qstrBaseAuth),
  m_pSession(nullptr)
{
}

CftlCommandFindSession::~CftlCommandFindSession()
{
}

int CftlCommandFindSession::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;

    if (m_lSessionId > 0 && m_lUserId > 0)
    {
        iRet = FindSessionBySessionIdAndUserId();
    }
    else if (m_lSessionId > 0)
    {
        iRet = FindSessionBySessionId();
    }
    else if (!m_qstrBaseAuth.isEmpty())
    {
        iRet = FindSessionByBaseAuth();
    }

    return iRet;
}

int CftlCommandFindSession::FindSessionBySessionIdAndUserId()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select State, SessionId, UserId from WMS_UM_SESSION where SessionId = ? and UserId = ?");
    cQSqlQuery.addBindValue(m_lSessionId);
    cQSqlQuery.addBindValue(m_lUserId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
           iRet = cQSqlQuery.value(0).toBool();
           if (SUCCESSFULL(iRet))
           {
               int iSessionId = cQSqlQuery.value(1).toInt();
               int iUserId = cQSqlQuery.value(2).toInt();
               m_pSession = CdmDataAccessHelper::CreateNewSession(iSessionId, iUserId, GetDataAccess());
           }
       }
       else
       {
          iRet = EC(eDmFalse);
          INFO("The session " + QString::number(m_lSessionId) + " of User "
               + QString::number(m_lUserId) + " does not exist.");
       }
    }
    else
    {
       iRet = EC(eDmSessionNotFound);
       ERR("Query Execution failed!!");
    }

    return iRet;
}

int CftlCommandFindSession::FindSessionBySessionId()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select State, SessionId, UserId from WMS_UM_SESSION where SessionId = ?");
    cQSqlQuery.addBindValue(m_lSessionId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
           iRet = cQSqlQuery.value(0).toBool();
           if (SUCCESSFULL(iRet))
           {
               int iSessionId = cQSqlQuery.value(1).toInt();
               int iUserId = cQSqlQuery.value(2).toInt();

               m_pSession = CdmDataAccessHelper::CreateNewSession(iSessionId, iUserId, GetDataAccess());
           }
       }
       else
       {
          iRet = EC(eDmFalse);
          INFO("The session " + QString::number(m_lSessionId) + " does not exist.");
       }
    }
    else
    {
       iRet = EC(eDmSessionNotFound);
       ERR("Query Execution failed!!");
    }

    return iRet;

}

int CftlCommandFindSession::FindSessionByBaseAuth()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery;
    cQSqlQuery.prepare("select State, SessionId, UserId from WMS_UM_SESSION where BaseAuth = ?");
    cQSqlQuery.addBindValue(m_qstrBaseAuth);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
           iRet = cQSqlQuery.value(0).toBool();
           if (SUCCESSFULL(iRet))
           {
               int iSessionId = cQSqlQuery.value(1).toInt();
               int iUserId = cQSqlQuery.value(2).toInt();

               m_pSession = CdmDataAccessHelper::CreateNewSession(iSessionId, iUserId, GetDataAccess());
           }
       }
       else
       {
          iRet = EC(eDmFalse);
          INFO("The session " + QString::number(m_lSessionId) + " of User "
               + QString::number(m_lUserId) + " does not exist.");
       }
    }
    else
    {
       iRet = EC(eDmSessionNotFound);
       ERR("Query Execution failed!!");
    }

    return iRet;
}

bool CftlCommandFindSession::CheckValid()
{
    return (m_lSessionId > 0);
}

CdmSession* CftlCommandFindSession::GetResult()
{
    return m_pSession;
}

bool CftlCommandFindSession::NeedsSessionCheck()
{
    return false;
}
