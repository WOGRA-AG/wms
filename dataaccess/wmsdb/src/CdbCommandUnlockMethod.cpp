#include "CdbCommandUnlockMethod.h"

CdbCommandUnlockMethod::CdbCommandUnlockMethod(qint64 p_lMethodId,qint64 p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lMethodId(p_lMethodId),
  m_bResult(true)
{
}

CdbCommandUnlockMethod::~CdbCommandUnlockMethod()
{

}

bool CdbCommandUnlockMethod::CheckValid()
{
    return (m_lSessionId > 0 && m_lMethodId > 0);
}

int CdbCommandUnlockMethod::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery;
    QString qstrSql = QString("delete from WMS_CLASS_LOCKEDMETHOD "
                              "where SessionId = %1 AND MethodId = %2")
                             .arg(m_lSessionId)
                             .arg(m_lMethodId);

    if (ExecuteQuery(qstrSql, cQuery) > 0)
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

bool CdbCommandUnlockMethod::GetResult()
{
    return m_bResult;
}

