#include "CdmSessionManager.h"

#include "CdbAbstractCommand.h"
#include "CdbCommandFindSession.h"
#include "CdbCommandUpdateSession.h"


CdbAbstractCommand::CdbAbstractCommand(CdbDataAccess* p_pDataAccess)
    : m_rpDataAccess(p_pDataAccess),
      m_qMutex(QMutex::Recursive)
{
}

CdbAbstractCommand::~CdbAbstractCommand()
{

}

int CdbAbstractCommand::Run()
{
    int iRet = Validate();

    if (SUCCESSFULL(iRet))
    {
        if (NeedsActiveSession())
        {
            iRet = SessionCheck();
        }

        if (SUCCESSFULL(iRet))
        {
            iRet = Execute();
        }
    }

    return iRet;
}

long CdbAbstractCommand::ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
    return m_rpDataAccess->ExecuteQuery(p_qstrQuery,p_rqsqlQuery);
}

long CdbAbstractCommand::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
    return m_rpDataAccess->ExecuteQuery(p_rqsqlQuery);
}

QSqlDatabase CdbAbstractCommand::GetSqlDatabase()
{
    return m_rpDataAccess->GetDbInterface()->GetSqlDatabase();
}

bool CdbAbstractCommand::Validate()
{
    return (CHKPTR(m_rpDataAccess) && CheckValid());
}


CdbDataAccess* CdbAbstractCommand::GetDataAccess()
{
    return m_rpDataAccess;
}

bool CdbAbstractCommand::NeedsActiveSession()
{
    return true;
}

void CdbAbstractCommand::UpdateSession()
{
    long lSessionId = CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
    CdbCommandUpdateSession command(lSessionId, GetDataAccess());
    command.Run();
}

int CdbAbstractCommand::SessionCheck()
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CdbInterface* pInterface = GetInterface();

    if (CHKPTR(pInterface))
    {
        if (!pInterface->IsTransactionRunning())
        {
            CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

            if (CHKPTR(pSessionManager))
            {
                long iSessionId = pSessionManager->GetCurrentSessionId();
                long iUserId = pSessionManager->GetCurrentUserId();
                CdbCommandFindSession command(iSessionId, iUserId, m_rpDataAccess);
                lRet = command.Run();

                if (SUCCESSFULL(lRet))
                {
                    UpdateSession();
                }
            }
        }
        else
        {
            lRet = EC(eDmOk);
        }
    }

    return lRet;
}

CdbInterface* CdbAbstractCommand::GetInterface()
{
    return m_rpDataAccess->GetDbInterface();
}
