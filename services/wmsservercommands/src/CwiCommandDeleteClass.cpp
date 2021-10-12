#include "CwiCommandDeleteClass.h"
#include "CdmDataProvider.h"
#include "IdmDataAccess.h"


CwiCommandDeleteClass::CwiCommandDeleteClass(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandDeleteClass::~CwiCommandDeleteClass()
{

}

void CwiCommandDeleteClass::Execute()
{
   qint64 iClassId = m_rpData->GetValue("ClassId").toInt();
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (pCdmManager)
    {
       IdmDataAccess* pDataAccess = pCdmManager->GetDataAccess();

       if (pDataAccess)
       {
          int iSuccess = pDataAccess->DeleteClass(iClassId);

          if (iSuccess > 0)
          {
             GetResultContainer(m_rpData,
                               1,
                               "Class deleted",
                               eWmscomMessageServerityInfo);
          }
          else
          {
             GetResultContainer(m_rpData,
                               -5000,
                               "Error occured while deleting class",
                               eWmscomMessageServerityError);
          }
       }
       else
       {
          GetResultContainer(m_rpData,
                            -5000,
                            "No Data Access configured",
                            eWmscomMessageServerityFatal);
       }
    }
    else
    {
       GetResultContainer(m_rpData,
                         -5000,
                         "No session found",
                         eWmscomMessageServerityFatal);
    }
}

