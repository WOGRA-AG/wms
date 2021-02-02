#include <QDateTime>

#include "CwmsUtilities.h"
#include "CftlCommandUpdateSession.h"


CftlCommandUpdateSession::CftlCommandUpdateSession(long p_lSessionId, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lSessionId(p_lSessionId)
{
}
CftlCommandUpdateSession::CftlCommandUpdateSession(QString p_qstrBaseAuth, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lSessionId(0),
  m_qstrBaseAuth(p_qstrBaseAuth)
{
}


CftlCommandUpdateSession::~CftlCommandUpdateSession()
{
}

int CftlCommandUpdateSession::Execute()
{
    QSqlQuery cQuery(GetSqlDatabase());
    QDateTime qdtDateTime = QDateTime::currentDateTime();

    if (m_lSessionId > 0)
    {
        cQuery.prepare("update WMS_UM_SESSION set LAST_REQUEST = ? where SessionId = ?");
        cQuery.addBindValue(qdtDateTime);
        cQuery.addBindValue((int)m_lSessionId);
    }
    else if (!m_qstrBaseAuth.isEmpty())
    {
        cQuery.prepare("update WMS_UM_SESSION set LAST_REQUEST = ? where BaseAuth = ?");
        cQuery.addBindValue(qdtDateTime);
        cQuery.addBindValue(m_qstrBaseAuth);
    }



    return ExecuteQuery(cQuery);
}




bool CftlCommandUpdateSession::CheckValid()
{
    return (m_lSessionId > 0 || !m_qstrBaseAuth.isEmpty());
}

bool CftlCommandUpdateSession::NeedsSessionCheck()
{
    return false;
}

