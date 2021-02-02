#include "CwiCommandCounterValue.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "IdmDataAccess.h"


CwiCommandCounterValue::CwiCommandCounterValue(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandCounterValue::~CwiCommandCounterValue()
{

}

void CwiCommandCounterValue::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
        long lDbId = m_rpData->GetValue("DatabaseId").toInt();
        long lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
        long lValueId = m_rpData->GetValue("ValueId").toInt();
        QString qstrKeyname = m_rpData->GetValue("Keyname").toString();

        if (pCdmManager)
        {
            IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

            if (pIdmDataAccess)
            {
                CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager();

                if (CHKPTR(pContainerManager))
                {
                    CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(lObjectListId);

                    if (CHKPTR(pContainer))
                    {
                        // TODO Check if this method will be really called!
                        int iValue = -1;//pIdmDataAccess->GetCounterValue(pContainer, lValueId, qstrKeyname);

                        if (iValue > 0)
                        {
                            pResult = GetResultContainer(m_rpData,
                                                         1,
                                                         "Value reserved",
                                                         eWmscomMessageServerityInfo);
                            pResult->AddValue("Result", iValue);
                        }
                        else
                        {
                            GetResultContainer(m_rpData,
                                               -5000,
                                               "Error occured while reading counter value",
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

