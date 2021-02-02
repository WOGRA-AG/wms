#include "CdbCommandCheckSessionTimeout.h"

CdbCommandCheckSessionTimeout::CdbCommandCheckSessionTimeout(int p_iTimeout, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_iTimeout(p_iTimeout) // Minutes
{
}


CdbCommandCheckSessionTimeout::~CdbCommandCheckSessionTimeout()
{

}

bool CdbCommandCheckSessionTimeout::CheckValid()
{
    return true;
}

int CdbCommandCheckSessionTimeout::Execute()
{
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    QDateTime qdtDateTime = QDateTime::currentDateTime();
    QString qstrLogoutDate = CwmsUtilities::ChangeDateToString(qdtDateTime);
    QString qstrMaxDate = CwmsUtilities::ChangeDateToString(qdtDateTime.addSecs(m_iTimeout * 60 * (-1)));

    qstrQuery =
            QString("update WMS_UM_SESSION set State = 0, LogoutDate = %1 where Last_Request <= %2 and State = 1")
            .arg(qstrLogoutDate)
            .arg(qstrMaxDate);

    return ExecuteQuery(qstrQuery, cQSqlQuery);
}
