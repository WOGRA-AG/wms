#include "CwiCommandObjectListExist.h"
#include "CdmDataProvider.h"
#include "IdmDataAccess.h"



CwiCommandObjectListExist::CwiCommandObjectListExist(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandObjectListExist::~CwiCommandObjectListExist()
{

}

void CwiCommandObjectListExist::Execute()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
   int iDbId = m_rpData->GetValue("DatabaseId").toInt();
   QString qstrKeyname = m_rpData->GetValue("Keyname").toString();

   if (pCdmManager)
   {
      IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

      if (pIdmDataAccess)
      {
         if (pIdmDataAccess->ExistObjectContainer(iDbId, qstrKeyname) > 0)
         {
            GetResultContainer(m_rpData,
                             1,
                             "Objectlist exists",
                             eWmscomMessageServerityInfo);
         }
         else
         {
            GetResultContainer(m_rpData,
                             0,
                             "Objectlist does not exist",
                             eWmscomMessageServerityInfo);
         }
      }
      else
      {
         GetResultContainer(m_rpData,
                          -5000,
                          "No Data access configured",
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

