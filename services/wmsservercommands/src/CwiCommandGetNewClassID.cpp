#include "CwiCommandGetNewClassID.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"


CwiCommandGetNewClassID::CwiCommandGetNewClassID(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetNewClassID::~CwiCommandGetNewClassID()
{

}

void CwiCommandGetNewClassID::Execute()
{
    if (m_rpData->HasValue("DatabaseId"))
    {
       long iDbId = m_rpData->GetValue("DatabaseId").toInt();

       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (pCdmManager)
       {
          CdmClassManager* pCdmCM = pCdmManager->GetClassManager(iDbId);

          if (pCdmCM)
          {
             CdmClass* pCdmClass = pCdmCM->CreateClass("Temp");

             if (pCdmClass)
             {
                int iClassId = pCdmClass->GetId();
                CwmscomDataResult* pResult = GetResultContainer(m_rpData,
                                             1,
                                             "New class id returned",
                                             eWmscomMessageServerityInfo);
                pResult->AddValue("ClassId", iClassId);
             }
             else
             {
                GetResultContainer(m_rpData,
                                  -5000,
                                  "Error in getting new class id!",
                                  eWmscomMessageServerityError);
             }
          }
          else
          {
             GetResultContainer(m_rpData,
                               -5000,
                               "No Dataaccess found!",
                               eWmscomMessageServerityFatal);
          }
       }
       else
       {
          GetResultContainer(m_rpData,
                            -5000,
                            "Session not found!",
                            eWmscomMessageServerityFatal);
       }
    }
    else
    {
       GetResultContainer(m_rpData,
                         -5000,
                         "No DB Id delivered!",
                         eWmscomMessageServerityError);
    }
}

