#include "CdmObjectContainer.h"

#include "CdbCommandCountObjectsOnDb.h"

CdbCommandCountObjectsOnDb::CdbCommandCountObjectsOnDb(CdmObjectContainer* p_pContainer, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer)
{
}

CdbCommandCountObjectsOnDb::~CdbCommandCountObjectsOnDb()
{

}

bool CdbCommandCountObjectsOnDb::CheckValid()
{
    return CHKPTR(m_rpContainer);
}

int CdbCommandCountObjectsOnDb::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(m_rpContainer))
    {
      qint64 lObjectListId = m_rpContainer->GetId();

       if (lObjectListId > 0)
       {
          QSqlQuery cQSqlQuery;
          QString qstrQuery;

          qstrQuery = QString("select COUNT(*) from "
                              "WMS_DM_OBJECT where ObjectListId = %1")
                             .arg(lObjectListId);

          lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

          if(lRet > 0)
          {
             cQSqlQuery.first();

             if(cQSqlQuery.isValid())
             {
                lRet = cQSqlQuery.value(0).toInt();
             }
             else
             {
                lRet = CdmLogging::eDmFalse;
             }
          }
       }
    }

    return lRet;
}
