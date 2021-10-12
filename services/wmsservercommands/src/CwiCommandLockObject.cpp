#include "CwiCommandLockObject.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "IdmDataAccess.h"


CwiCommandLockObject::CwiCommandLockObject(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandLockObject::~CwiCommandLockObject()
{

}

void CwiCommandLockObject::Execute()
{
   qint64 lObjectId = m_rpData->GetValue("ObjectId").toInt();
   qint64 lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
   qint64 lDbId = m_rpData->GetValue("DatabaseId").toInt();

    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       IdmDataAccess* pDataAccess = pCdmManager->GetDataAccess();
       bool bSuccess = false;

       CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

       if (CHKPTR(pContainerManager))
       {
           CdmObject* pObject = pContainerManager->FindObject(lObjectListId, lObjectId);

           if (CHKPTR(pObject))
           {
               pDataAccess->LockObject(pObject, bSuccess);

               if (bSuccess)
               {
                  GetResultContainer(m_rpData,
                                               1,
                                               "Object locked!",
                                               eWmscomMessageServerityInfo);
               }
               else
               {
                  GetResultContainer(m_rpData,
                                               -5000,
                                               "Could not lock object on db!",
                                               eWmscomMessageServerityError);
               }
           }
       }
    }
    else
    {
       GetResultContainer(m_rpData,
                          -5000,
                          "Session not found",
                          eWmscomMessageServerityFatal);
    }
}

