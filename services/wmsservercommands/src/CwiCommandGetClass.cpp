#include "CwiCommandGetClass.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"


CwiCommandGetClass::CwiCommandGetClass(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetClass::~CwiCommandGetClass()
{

}

void CwiCommandGetClass::Execute()
{
   qint64 iDbId = m_rpData->GetValue("DatabaseId").toInt();
    CwmscomDataResult* pResult = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (pManager)
    {
       CdmClassManager* pCdmClassManager = pManager->GetClassManager(iDbId);

       if (!pCdmClassManager)
       {
          pManager->LoadClassManager(iDbId);
          pCdmClassManager = pManager->GetClassManager(iDbId);
       }

       if (pCdmClassManager)
       {
          QVariant qvCM = pCdmClassManager->GetVariant();
          pResult = GetResultContainer(m_rpData,
                                        1,
                                        "Classes added",
                                        eWmscomMessageServerityInfo);
          pResult->AddValue("ClassManager", qvCM);

       }
       else
       {
          pResult = GetResultContainer(m_rpData,
                                        -5000,
                                        "Class Manager does not exist on Server",
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

