#include "CwiCommandPrintContainer.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryEnhanced.h"
#include "CwmsReportManager.h"



CwiCommandPrintContainer::CwiCommandPrintContainer(CwmscomData *m_rpData)
    :m_rpData(m_rpData)
{

}

CwiCommandPrintContainer::~CwiCommandPrintContainer()
{

}

void CwiCommandPrintContainer::Execute()
{
   CwmscomDataResult* pResult = nullptr;
   long lObjectListId = m_rpData->GetValue("ObjectListId").toInt();
   long lObjectId = m_rpData->GetValue("ObjectId").toInt();

   CdmObjectContainer* pList = GetObjectList(lObjectListId);

   if (CHKPTR(pList))
   {
      CwmsReportManager cManager;
      const CdmClass* pClass = pList->GetClass();

      if (CHKPTR(pClass))
      {
         CdmQueryEnhanced* pQuery = nullptr;

         if (lObjectId <= 0)
         {
            pQuery = cManager.GetReportsByClassKeyname(pClass->GetKeyname(), eWmsTemplateTypeList);
         }
         else
         {
            pQuery = cManager.GetReportsByClassKeyname(pClass->GetKeyname(), eWmsTemplateTypeObject);
         }

         QVariantList qvlPrints;

         if (CHKPTR(pQuery))
         {
            if (pQuery->GetResultCount() > 0)
            {
               for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
               {
                  qvlPrints.append(pQuery->GetResultAt(0, iCounter));
               }
            }
         }

         if (qvlPrints.count() >= 0)
         {
            pResult = GetResultContainer(m_rpData,
                                         1,
                                         "printing templates found!",
                                         eWmscomMessageServerityInfo);

            pResult->AddValue("Templates", qvlPrints);
         }
      }
      else
      {
         pResult = GetResultContainer(m_rpData,
                                      -5000,
                                      "class not found!",
                                      eWmscomMessageServerityFatal);
      }
   }
   else
   {
      pResult = GetResultContainer(m_rpData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

CdmObjectContainer* CwiCommandPrintContainer::GetObjectList(long p_lObjectList)
{
   CdmObjectContainer* pList = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmContainerManager* pOLManager = pManager->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         pList = pOLManager->FindEmptyContainerById(p_lObjectList);
      }
   }

   return pList;
}
