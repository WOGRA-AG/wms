#include "CftlCommandDeleteUser.h"

CftlCommandDeleteUser::CftlCommandDeleteUser(qint64 p_lUserId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_iUserId(p_lUserId)
{
}

CftlCommandDeleteUser::CftlCommandDeleteUser(QString p_qstrLogin, CftlDataAccess *p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_qstrLogin(p_qstrLogin),
      m_iUserId(0)
{

}

CftlCommandDeleteUser::~CftlCommandDeleteUser()
{

}

int CftlCommandDeleteUser::Execute()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;

    if (m_iUserId > 0)
    {
        iRet = DeleteUserById();
    }
    else if (!m_qstrLogin.isEmpty())
    {
        iRet = DeleteUserByLogin();
    }

    return iRet;
}

int CftlCommandDeleteUser::DeleteUserById()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_UM_ACCESSOR where AccessorId = ?");
    cQSqlQuery.addBindValue(m_iUserId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.prepare("delete from WMS_UM_USER where UserId = ?");
        cQSqlQuery.addBindValue(m_iUserId);

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
            lRet = EC(eDmOk);
        }
        else
        {
            lRet = EC(eDmInvalidDeleteStatement);
        }
    }
    else
    {
        lRet = EC(eDmInvalidDeleteStatement);
    }


    return lRet;

}

int CftlCommandDeleteUser::DeleteUserByLogin()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("select UserId from WMS_UM_USER where Login = ?");
    cQSqlQuery.addBindValue(m_qstrLogin);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            m_iUserId = cQSqlQuery.value(0).toInt();
            lRet = DeleteUserById();
        }
        else
        {
            lRet = EC(eDmUserNotFoundInDb);
        }
    }

    return lRet;
}

bool CftlCommandDeleteUser::CheckValid()
{
    return (m_iUserId > 0 || !m_qstrLogin.isEmpty());
}
