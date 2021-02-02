#include "CdmSessionManager.h"
#include "CdmSession.h"

#include "CdbCommandFindSession.h"

CdbCommandFindSession::CdbCommandFindSession(long p_lSessionId, long p_lUserId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(p_lUserId),
  m_pSession(nullptr)
{
}

CdbCommandFindSession::CdbCommandFindSession(long p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(0),
  m_pSession(nullptr)
{
}
CdbCommandFindSession::CdbCommandFindSession(QString p_qstrBaseAuth, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSessionId(0),
  m_lUserId(0),
  m_qstrBaseAuth(p_qstrBaseAuth),
  m_pSession(nullptr)
{
}


CdbCommandFindSession::~CdbCommandFindSession()
{
}

int CdbCommandFindSession::Execute()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;

    if (m_lSessionId > 0 && m_lUserId > 0)
    {
        m_pSession = CdmSessionManager::GetSessionManager()->FindSessionByIdLocal(m_lSessionId);

        if (!m_pSession)
        {
            iRet = FindSessionBySessionIdAndUserId();
        }
        else
        {
            iRet = CdmLogging::eDmOk;
        }
    }
    else if (m_lSessionId > 0)
    {
        m_pSession = CdmSessionManager::GetSessionManager()->FindSessionByIdLocal(m_lSessionId);

        if (!m_pSession)
        {
            iRet = FindSessionBySessionId();
        }
        else
        {
            iRet = CdmLogging::eDmOk;
        }
    }
    else if (!m_qstrBaseAuth.isEmpty())
    {
        iRet = FindSessionByBaseAuth();
    }

    return iRet;
}

int CdbCommandFindSession::FindSessionBySessionIdAndUserId()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    qstrQuery = QString("select State, SessionId, UserId from WMS_UM_SESSION where SessionId = %1 and UserId = %2")
                        .arg(m_lSessionId)
                        .arg(m_lUserId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

int CdbCommandFindSession::FindSessionBySessionId()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    qstrQuery = QString("select State, SessionId, UserId from WMS_UM_SESSION where SessionId = %1")
                        .arg(m_lSessionId);


    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

int CdbCommandFindSession::FindSessionByBaseAuth()
{
    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    qstrQuery = QString("select State, SessionId, UserId from WMS_UM_SESSION where BaseAuth = '%1'")
                        .arg(m_qstrBaseAuth);


    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

bool CdbCommandFindSession::CheckValid()
{
    return (m_lSessionId > 0 || !m_qstrBaseAuth.isEmpty());
}

CdmSession* CdbCommandFindSession::GetResult()
{
    return m_pSession;
}

bool CdbCommandFindSession::NeedsActiveSession()
{
    return false;
}
