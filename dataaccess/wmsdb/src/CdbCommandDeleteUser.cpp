#include "CdbCommandDeleteUser.h"

CdbCommandDeleteUser::CdbCommandDeleteUser(long p_lUserId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_iUserId(p_lUserId)
{
}

CdbCommandDeleteUser::CdbCommandDeleteUser(QString p_qstrLogin, CdbDataAccess *p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_qstrLogin(p_qstrLogin),
      m_iUserId(0)
{

}

CdbCommandDeleteUser::~CdbCommandDeleteUser()
{

}

int CdbCommandDeleteUser::Execute()
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

int CdbCommandDeleteUser::DeleteUserById()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;

       QSqlQuery cQSqlQuery;
       QString qstrQuery;

     qstrQuery = QString("delete from WMS_UM_ACCESSOR where AccessorId = %1")
                    .arg(m_iUserId);

     if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
     {
        cQSqlQuery.first();
        qstrQuery = QString("delete from WMS_UM_USER where UserId = %1")
                    .arg(m_iUserId);

        if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

int CdbCommandDeleteUser::DeleteUserByLogin()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;


   qstrQuery = QString("select UserId from WMS_UM_USER where Login = '%1'")
                .arg(CwmsUtilities::MaskStringForChanges(m_qstrLogin));

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

bool CdbCommandDeleteUser::CheckValid()
{
    return (m_iUserId > 0 || !m_qstrLogin.isEmpty());
}
