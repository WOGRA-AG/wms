#include "CwiCommandUpdateBinaryDocument.h"
#include "CdmDataProvider.h"
#include "CdmValueBinaryDocument.h"
#include "IdmDataAccess.h"



CwiCommandUpdateBinaryDocument::CwiCommandUpdateBinaryDocument(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandUpdateBinaryDocument::~CwiCommandUpdateBinaryDocument()
{

}

void CwiCommandUpdateBinaryDocument::Execute()
{
   int iDbId = m_rpData->GetValue("DatabaseId").toInt();
   QVariantMap qvBinDoc = m_rpData->GetValue("BinDoc").toMap();
   CdmValueBinaryDocument* pCdmBinDoc = new CdmValueBinaryDocument(qvBinDoc, nullptr);

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

      if (pIdmDataAccess)
      {
         if (pIdmDataAccess->UpdateBinaryDocument(iDbId, pCdmBinDoc) > 0)
         {
            GetResultContainer(m_rpData,
               1,
               "Binary Doc updated",
               eWmscomMessageServerityInfo);
         }
         else
         {
            GetResultContainer(m_rpData,
                                         -5000,
                                         "Error occured while saving binary document",
                                         eWmscomMessageServerityError);

         }
      }
      else
      {
         GetResultContainer(m_rpData,
                                       -5000,
                                       "Data access not found",
                                       eWmscomMessageServerityFatal);

      }
   }
   else
   {
      GetResultContainer(m_rpData,
                                    -5000,
                                    "Session not found",
                                    eWmscomMessageServerityFatal);

   }

   delete pCdmBinDoc;
}

