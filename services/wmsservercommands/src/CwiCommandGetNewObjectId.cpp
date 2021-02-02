#include "CwiCommandGetNewObjectId.h"
#include "CdmContainerManager.h"
#include "CdmDataProvider.h"
#include "IdmDataAccess.h"


CwiCommandGetNewObjectId::CwiCommandGetNewObjectId(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetNewObjectId::~CwiCommandGetNewObjectId()
{

}

void CwiCommandGetNewObjectId::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    if (CHKPTR(m_rpData))
    {
        int iObjectListId = m_rpData->GetValue("ObjectListId").toInt();
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (pCdmManager)
        {
            IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

            if (pIdmDataAccess)
            {
                CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

                if (CHKPTR(pContainerManager))
                {
                    CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(iObjectListId);

                    if (CHKPTR(pContainer))
                    {

                        int iId = pIdmDataAccess->GetNewObjectId(pContainer);
                        pResult = GetResultContainer(m_rpData,
                                                     1,
                                                     "Object id created!",
                                                     eWmscomMessageServerityInfo);
                        pResult->AddValue("NewId", iId);
                    }
                    else
                    {
                        pResult = GetResultContainer(m_rpData,
                                                     -5000,
                                                     "No Data access configured!",
                                                     eWmscomMessageServerityFatal);
                    }
                }
            }
        }
        else
        {
            pResult = GetResultContainer(m_rpData,
                                         -5000,
                                         "Session not found!",
                                         eWmscomMessageServerityFatal);
        }
    }
}

