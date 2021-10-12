#include "CdmObject.h"

#include "CftlCommandCheckObjectUsed.h"

CftlCommandCheckObjectUsed::CftlCommandCheckObjectUsed(const CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpObject(p_pObject)

{
}


CftlCommandCheckObjectUsed::~CftlCommandCheckObjectUsed()
{

}

bool CftlCommandCheckObjectUsed::CheckValid()
{
    return (m_rpObject != nullptr);
}

int CftlCommandCheckObjectUsed::Execute()
{
    int lRet = CdmLogging::eDmObjectAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("select COUNT(*) from "
                        "WMS_DM_OBJECT_REFERENCE where ObjectId = ? "
                        "and ContainerId = ?");
    cQSqlQuery.addBindValue(m_rpObject->GetId());
    cQSqlQuery.addBindValue(m_rpObject->GetObjectContainerId());

    lRet = ExecuteQuery(cQSqlQuery);

    if(SUCCESSFULL(lRet))
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
