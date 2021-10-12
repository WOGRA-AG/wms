#include "CwiCommandIsObjectUsed.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "IdmDataAccess.h"



CwiCommandIsObjectUsed::CwiCommandIsObjectUsed(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandIsObjectUsed::~CwiCommandIsObjectUsed()
{

}

void CwiCommandIsObjectUsed::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
       qint64 lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
       qint64 lObjectId = m_rpData->GetValue("ObjectId").toInt();

        if (pCdmManager)
        {
            IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

            if (pIdmDataAccess)
            {
                CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

                if (CHKPTR(pContainerManager))
                {
                    CdmObject* pObject = pContainerManager->FindObject(lObjectListId, lObjectId);

                    if (CHKPTR(pObject))
                    {
                        int iResult = pIdmDataAccess->IsObjectUsed(pObject);

                        if (iResult >= 0)
                        {
                            pResult = GetResultContainer(m_rpData,
                                                         1,
                                                         "Request successfull finished",
                                                         eWmscomMessageServerityInfo);
                            pResult->AddValue("Result", iResult);
                        }
                        else
                        {
                            GetResultContainer(m_rpData,
                                               -5000,
                                               "Request error",
                                               eWmscomMessageServerityError);
                        }
                    }
                    else
                    {
                        GetResultContainer(m_rpData,
                                           -5000,
                                           "No Data access here",
                                           eWmscomMessageServerityFatal);
                    }
                }
                else
                {
                    GetResultContainer(m_rpData,
                                       -5000,
                                       "No Session found!",
                                       eWmscomMessageServerityFatal);
                }
            }
        }
    }
}

