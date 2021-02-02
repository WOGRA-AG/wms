#include "CdbCommandGetNewClassId.h"

CdbCommandGetNewClassId::CdbCommandGetNewClassId(long p_lSessionId, long p_lSchemeId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSchemeId(p_lSchemeId),
      m_lSessionId(p_lSessionId)
{

}

CdbCommandGetNewClassId::~CdbCommandGetNewClassId()
{
}

int CdbCommandGetNewClassId::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

    // Query for creating new entry
    qstrQuery = QString("insert into WMS_CLASS "
                        "(Keyname, LastChange, DataBaseId, CreatorId, ModifierId, Caption, TempSessionId)"
                        "values('%1', %2, %3, %4, %5, '%6', %7)")
                        .arg("New Class")
                        .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                        .arg(m_lSchemeId)
                        .arg(0) // will be filled later
                        .arg(0) // will be filled later
                        .arg("New Class")
                        .arg(m_lSessionId);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       // query for reading new id
       qstrQuery = QString("select ClassId from WMS_CLASS where Keyname = '%1' and TempSessionId = %2")
                           .arg("New Class")
                           .arg(m_lSessionId);

       if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
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

bool CdbCommandGetNewClassId::CheckValid()
{
    return (m_lSchemeId > 0 && m_lSessionId > 0);
}
