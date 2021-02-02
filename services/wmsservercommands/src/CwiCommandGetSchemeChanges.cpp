#include "CwiCommandGetSchemeChanges.h"
#include "CdmDataProvider.h"
#include "CdmJournalItem.h"
#include "CdmScheme.h"


CwiCommandGetSchemeChanges::CwiCommandGetSchemeChanges(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetSchemeChanges::~CwiCommandGetSchemeChanges()
{

}

void CwiCommandGetSchemeChanges::Execute()
{
    CwmscomDataResult* pResult = nullptr;

  if (m_rpData)
  {
      int iDatabaseId = m_rpData->GetValue("DatabaseId").toInt();
      QDate qdFrom = m_rpData->GetValue("From").toDate();
      QDate qdTo = m_rpData->GetValue("To").toDate();

      if (!qdFrom.isValid() || !qdTo.isValid())
      {
          GetResultContainer(m_rpData,
                             -5000,
                             "Invalid from or to date.",
                             eWmscomMessageServerityError);
          return;
      }

       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (pCdmManager)
       {
           CdmScheme* pScheme = pCdmManager->FindSchemeById(iDatabaseId);

           if (pScheme)
           {
               QList<CdmJournalItem*> qlItems;
               pScheme->GetChanges(qdFrom, qdTo, qlItems);
               QVariantList qvResults;

               for (int iPos = 0; iPos < qlItems.count(); ++iPos)
               {
                   CdmJournalItem* pItem = qlItems[iPos];

                   if (pItem)
                   {
                       qvResults.append(pItem->GetVariant());
                       delete pItem;
                   }
               }

               pResult = GetResultContainer(m_rpData,
                                            1,
                                            "Database created!",
                                            eWmscomMessageServerityInfo);
               pResult->AddValue("Results", qvResults);
           }
           else
           {
               GetResultContainer(m_rpData,
                                  -5000,
                                  "Scheme not found",
                                  eWmscomMessageServerityError);
           }
       }
       else
       {
           GetResultContainer(m_rpData,
                              -5000,
                              "Invalid Session Manager bnot found",
                              eWmscomMessageServerityFatal);
       }
  }
  else
  {
     GetResultContainer(m_rpData,
                        -5000,
                        "Invalid call! Data pointer is nullptr.",
                        eWmscomMessageServerityFatal);
  }

}

