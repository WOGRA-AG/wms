// WMS Includes
#include "CdmSessionManager.h"

#include "CftlCommandGetNewClassId.h"

#define INIT_CLASS_NAME "NewClass"

CftlCommandGetNewClassId::CftlCommandGetNewClassId(qint64 p_lSessionId,qint64 p_lSchemeId, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_lSessionId(p_lSessionId)
{

}

CftlCommandGetNewClassId::~CftlCommandGetNewClassId()
{
}

int CftlCommandGetNewClassId::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("insert into WMS_CLASS "
                        "(Keyname, LastChange, SchemeId, CreatorId, ModifierId, Caption, TempSessionId)"
                          "values(?, ?, ?, ?, ?, ?, ?)");
    cQSqlQuery.addBindValue(INIT_CLASS_NAME);
    cQSqlQuery.addBindValue(QDateTime::currentDateTime());
    cQSqlQuery.addBindValue(m_lSchemeId);
    cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    cQSqlQuery.addBindValue(CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    cQSqlQuery.addBindValue(INIT_CLASS_NAME);
    cQSqlQuery.addBindValue(m_lSessionId);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       // query for reading new id
       cQSqlQuery.prepare("select ClassId from WMS_CLASS where Keyname = ? and TempSessionId = ?");
       cQSqlQuery.addBindValue(INIT_CLASS_NAME);
       cQSqlQuery.addBindValue(m_lSessionId);

       if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
       {
          cQSqlQuery.first();
          if(cQSqlQuery.isValid())
          {
             // Value in col 0 is ClassId
             iRet = cQSqlQuery.value(0).toInt();
          }
          else
          {
             iRet = EC(eDmKeynameAlreadyExists);
             ERR("You can only create one class at one time if you need a new Id"
                 "you have first to commit the previous class creation!!!");
          }
       }
       else
       {
          ERR("Getting new Class Id failed (SELECT COMMAND).");
          iRet = EC(eDmInvalidSelectStatement);
       }
    }
    else
    {
       iRet = EC(eDmInvalidInsertStatement);
       ERR("Getting new Class Id failed (INSERT COMMAND).");
    }


    return iRet;
}

bool CftlCommandGetNewClassId::CheckValid()
{
    return (m_lSchemeId > 0 && m_lSessionId > 0);
}
