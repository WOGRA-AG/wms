// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes
#include "CftlCommandGetOwner.h"

CftlCommandGetOwner::CftlCommandGetOwner(const CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer),
      m_lOwnerObjectId(-1),
      m_lOwnerContainerId(-1)
{
}

CftlCommandGetOwner::CftlCommandGetOwner(const CdmObject* p_pObject, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpObject(p_pObject),
      m_lOwnerObjectId(-1),
      m_lOwnerContainerId(-1)
{
}

CftlCommandGetOwner::~CftlCommandGetOwner()
{

}

bool CftlCommandGetOwner::CheckValid()
{
    return (m_rpObject != nullptr || m_rpContainer != nullptr);
}

int CftlCommandGetOwner::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (m_rpObject != nullptr)
    {
        lRet = FindObjectOwner();
    }
    else
    {
        lRet = FindContainerOwner();
    }

    return lRet;
}

qint64 CftlCommandGetOwner::GetOwnerObjectId()
{
    return m_lOwnerObjectId;
}

qint64 CftlCommandGetOwner::GetOwnerContainerId()
{
    return m_lOwnerContainerId;
}

qint64 CftlCommandGetOwner::FindObjectOwner()
{
   qint64 lRet = -1;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("select Ref_Container_ID, Ref_Object_ID from WMS_DM_OBJECT_REFERENCE where ObjectId = ? and ContainerId = ? and owner = ?");
    cQSqlQuery.addBindValue(m_rpObject->GetId());
    cQSqlQuery.addBindValue(m_rpObject->GetObjectContainerId());
    cQSqlQuery.addBindValue(true);

    lRet = ExecuteQuery(cQSqlQuery);

    if(SUCCESSFULL(lRet))
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          m_lOwnerContainerId = cQSqlQuery.value(0).toInt();
          m_lOwnerObjectId = cQSqlQuery.value(1).toInt();
       }
       else
       {
          lRet = EC(eDmInvalidSelectStatement);
       }
    }

    return lRet;
}

qint64 CftlCommandGetOwner::FindContainerOwner()
{
   qint64 lRet = -1;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("select Ref_Container_ID, Ref_Object_ID from WMS_DM_CONTAINER_REFERENCE where ContainerId = ? and owner = ?");
    cQSqlQuery.addBindValue(m_rpContainer->GetId());
    cQSqlQuery.addBindValue(true);

    lRet = ExecuteQuery(cQSqlQuery);

    if(SUCCESSFULL(lRet))
    {
       cQSqlQuery.first();

       if(cQSqlQuery.isValid())
       {
          m_lOwnerContainerId = cQSqlQuery.value(0).toInt();
          m_lOwnerObjectId = cQSqlQuery.value(1).toInt();
       }
       else
       {
          lRet = EC(eDmInvalidSelectStatement);
       }
    }

    return lRet;
}
