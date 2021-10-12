#include "CwiCommandGetContainerChanges.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmJournalItem.h"


CwiCommandGetContainerChanges::CwiCommandGetContainerChanges(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetContainerChanges::~CwiCommandGetContainerChanges()
{

}

void CwiCommandGetContainerChanges::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (m_rpData)
    {
        int iDatabaseId = m_rpData->GetValue("DatabaseId").toInt();
       qint64 lContainerId = m_rpData->GetValue("ObjectListId").toInt();
        QString qstrFrom = m_rpData->GetValue("From").toString();
        QString qstrTo = m_rpData->GetValue("To").toString();
        QDate qdFrom = m_rpData->GetValue("From").toDate();
        QDate qdTo = m_rpData->GetValue("To").toDate();

        if (!qdFrom.isValid() || !qdTo.isValid())
        {
           GetResultContainer(m_rpData,
                              -5000,
                              "Wrong Dateformat From: " + qdFrom.toString() + " To: " + qdTo.toString(),
                              eWmscomMessageServerityFatal);
           return;

        }

         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager)
         {
             CdmScheme* pScheme = nullptr;

             if (iDatabaseId == 0)
             {
                 pScheme = pCdmManager->GetCurrentScheme();
             }
             else
             {
                 pScheme = pCdmManager->FindSchemeById(iDatabaseId);
             }

             if (pScheme)
             {
                 CdmContainerManager* pContainerManager = pScheme->GetContainerManager();

                 if (pContainerManager)
                 {
                     CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lContainerId);

                     if (CHKPTR(pContainer))
                     {
                         QList<CdmJournalItem*> qlItems;
                         pContainer->GetChanges(qdFrom, qdTo, qlItems);
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
                                                      "Journal items loaded",
                                                      eWmscomMessageServerityInfo);
                         pResult->AddValue("Results", qvResults);
                     }
                 }
                 else
                 {
                    GetResultContainer(m_rpData,
                                       -5000,
                                       "Invalid call! Container pointer is nullptr.",
                                       eWmscomMessageServerityFatal);
                 }
             }
             else
             {
                GetResultContainer(m_rpData,
                                   -5000,
                                   "Invalid call! Database pointer is nullptr.",
                                   eWmscomMessageServerityFatal);
             }
         }
         else
         {
            GetResultContainer(m_rpData,
                               -5000,
                               "Invalid call! Session invalid!",
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

