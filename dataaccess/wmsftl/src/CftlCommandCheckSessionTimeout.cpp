#include "CftlCommandCheckSessionTimeout.h"

CftlCommandCheckSessionTimeout::CftlCommandCheckSessionTimeout(int p_iTimeout, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_iTimeout(p_iTimeout) // Minutes
{
}


CftlCommandCheckSessionTimeout::~CftlCommandCheckSessionTimeout()
{

}

bool CftlCommandCheckSessionTimeout::CheckValid()
{
    return true;
}

int CftlCommandCheckSessionTimeout::Execute()
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QDateTime qdtDateTime = QDateTime::currentDateTime();
    cQSqlQuery.prepare("update WMS_UM_SESSION set State = 0, LogoutDate = %1 where Last_Request <= %2");
    cQSqlQuery.addBindValue(qdtDateTime);
    cQSqlQuery.addBindValue(qdtDateTime.addSecs(m_iTimeout * 60 * (-1)));
    return ExecuteQuery(cQSqlQuery);
}
