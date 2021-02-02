#include "CwiCommandUnlockObject.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "IdmDataAccess.h"



CwiCommandUnlockObject::CwiCommandUnlockObject(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandUnlockObject::~CwiCommandUnlockObject()
{

}

void CwiCommandUnlockObject::Execute()
{
    long lObjectId = m_rpData->GetValue("ObjectId").toInt();
    long lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
    long lDbId = m_rpData->GetValue("DatabaseId").toInt();

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
                pDataAccess->UnLockObject(pObject, bSuccess);

                if (bSuccess)
                {
                    GetResultContainer(m_rpData,
                                       1,
                                       "Object unlocked!",
                                       eWmscomMessageServerityInfo);
                }
                else
                {
                    GetResultContainer(m_rpData,
                                       -5000,
                                       "Could not unlock object on db!",
                                       eWmscomMessageServerityError);
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
}
