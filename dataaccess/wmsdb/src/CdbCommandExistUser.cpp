#include "CdbCommandExistUser.h"

CdbCommandExistUser::CdbCommandExistUser(QString p_qstrLogin, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_qstrLogin(p_qstrLogin)
{
}

CdbCommandExistUser::~CdbCommandExistUser()
{
}

int CdbCommandExistUser::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    qstrQuery = QString("select UserId from WMS_UM_USER where Login = '%1'")
                       .arg(CwmsUtilities::MaskStringForChanges(m_qstrLogin));

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         lRet = cQSqlQuery.value(0).toInt();
      }
      else
      {
         lRet = EC(CdmLogging::eDmFalse);
         INFO("No User found on Db!!!");
      }
    }
    else
    {
      lRet = EC(eDmInvalidSelectStatement);
      INFO("the selection query is invalid. please check.");
    }

    return lRet;
}

bool CdbCommandExistUser::CheckValid()
{
    return (!m_qstrLogin.isEmpty());
}
