#include "CwiCommandObjectListGetNewId.h"
#include "CdmDataProvider.h"
#include "IdmDataAccess.h"



CwiCommandObjectListGetNewId::CwiCommandObjectListGetNewId(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandObjectListGetNewId::~CwiCommandObjectListGetNewId()
{

}

void CwiCommandObjectListGetNewId::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    if (CHKPTR(m_rpData))
    {
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
       int iClassId = m_rpData->GetValue("ClassId").toInt();

       if (pCdmManager)
       {
          IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

          if (pIdmDataAccess)
          {
             int iOLId = pIdmDataAccess->GetNewContainerId(iClassId);

             pResult = GetResultContainer(m_rpData,
                                          1,
                                          "New ID created",
                                          eWmscomMessageServerityInfo);
             pResult->AddValue("NewId", iOLId);
          }
          else
          {
             pResult = GetResultContainer(m_rpData,
                                           -5000,
                                           "No Data access configured!",
                                           eWmscomMessageServerityFatal);
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

