#include "CdmSessionManager.h"

#include "CftlCommandUnlockMethod.h"

CftlCommandUnlockMethod::CftlCommandUnlockMethod(qint64 p_lMethodId, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lMethodId(p_lMethodId),
  m_bResult(true)
{
}

CftlCommandUnlockMethod::~CftlCommandUnlockMethod()
{

}

bool CftlCommandUnlockMethod::CheckValid()
{
    return (m_lMethodId > 0);
}

int CftlCommandUnlockMethod::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_LOCKEDMETHOD where SessionId = ? AND MethodId = ?");
    cQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    cQuery.addBindValue(m_lMethodId);

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
       INFO("Method unlocked. ID: " + QString::number(m_lMethodId));
       m_bResult = true;
    }
    else
    {
       ERR("Could not unlock method. perhaps it is not locked.");
    }


    return iRet;
}

bool CftlCommandUnlockMethod::GetResult()
{
    return m_bResult;
}

