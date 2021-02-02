#include "CftlCommandExistUser.h"

CftlCommandExistUser::CftlCommandExistUser(QString p_qstrLogin, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_qstrLogin(p_qstrLogin)
{
}

CftlCommandExistUser::~CftlCommandExistUser()
{
}

int CftlCommandExistUser::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());


    cQSqlQuery.prepare("select UserId from WMS_UM_USER where Login = ?");
    cQSqlQuery.addBindValue(m_qstrLogin);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         lRet = cQSqlQuery.value(0).toInt();
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         ERR("No User found!!!");
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
    }

    return lRet;
}

bool CftlCommandExistUser::CheckValid()
{
    return (!m_qstrLogin.isEmpty());
}
