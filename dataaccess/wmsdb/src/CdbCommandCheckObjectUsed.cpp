#include "CdbCommandCheckObjectUsed.h"

CdbCommandCheckObjectUsed::CdbCommandCheckObjectUsed(long p_lObjectId, long p_lContainerId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lObjectId(p_lObjectId),
  m_lContainerId(p_lContainerId)
{
}


CdbCommandCheckObjectUsed::~CdbCommandCheckObjectUsed()
{

}

bool CdbCommandCheckObjectUsed::CheckValid()
{
    return (m_lContainerId > 0 && m_lObjectId > 0);
}

int CdbCommandCheckObjectUsed::Execute()
{
    int lRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;


    qstrQuery = QString("select COUNT(*) from "
                        "WMS_VALUE_OBJECTREFERENCE where ObjectId = %1 "
                        "and ObjectListId = %2")
                        .arg(m_lObjectId)
                        .arg(m_lContainerId);

    lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

    if(lRet > 0)
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          int lValue = 0;
          lValue = cQSqlQuery.value(0).toInt();

          if (lValue > 0)
          {
             lRet = CdmLogging::eDmTrue;
          }
          else
          {
             lRet = CdmLogging::eDmFalse;
          }
       }
       else
       {
          lRet = CdmLogging::eDmFalse;
       }
    }

    return lRet;
}
