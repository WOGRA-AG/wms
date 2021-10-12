#include <QDateTime>

#include "CwmsUtilities.h"
#include "CdbCommandUpdateSession.h"


CdbCommandUpdateSession::CdbCommandUpdateSession(qint64 p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lSessionId(p_lSessionId)
{
}
CdbCommandUpdateSession::CdbCommandUpdateSession(QString p_qstrBaseAuth, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lSessionId(0),
  m_qstrBaseAuth(p_qstrBaseAuth)
{
}


CdbCommandUpdateSession::~CdbCommandUpdateSession()
{
}

int CdbCommandUpdateSession::Execute()
{
    QString qstrUpdate;
    QSqlQuery cQuery;

    QDateTime qdtDateTime = QDateTime::currentDateTime();
    QString qstrDateTime = CwmsUtilities::ChangeDateToString(qdtDateTime);

    if (m_lSessionId > 0)
    {
        qstrUpdate = QString("update WMS_UM_SESSION set LAST_REQUEST = %1 where SessionId = %2")
                .arg(qstrDateTime)
                .arg(m_lSessionId);
    }
    else if (!m_qstrBaseAuth.isEmpty())
    {
        qstrUpdate = QString("update WMS_UM_SESSION set LAST_REQUEST = %1 where BaseAuth = '%2'")
                .arg(qstrDateTime)
                .arg(m_qstrBaseAuth);
    }



    return GetDataAccess()->ExecuteQuery(qstrUpdate, cQuery);
}




bool CdbCommandUpdateSession::CheckValid()
{
    return (m_lSessionId > 0 || !m_qstrBaseAuth.isEmpty());
}

bool CdbCommandUpdateSession::NeedsActiveSession()
{
    return false;
}

