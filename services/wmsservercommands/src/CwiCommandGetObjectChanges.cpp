#include "CwiCommandGetObjectChanges.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmJournalItem.h"



CwiCommandGetObjectChanges::CwiCommandGetObjectChanges(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandGetObjectChanges::~CwiCommandGetObjectChanges()
{

}

void CwiCommandGetObjectChanges::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (m_rpData)
    {
        int iDatabaseId = m_rpData->GetValue("DatabaseId").toInt();
       qint64 lContainerId = m_rpData->GetValue("ObjectListId").toInt();
       qint64 lObjectId = m_rpData->GetValue("ObjectId").toInt();
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
                 CdmContainerManager* pContainerManager = pScheme->GetContainerManager();

                 if (pContainerManager)
                 {
                     CdmObjectContainer* pContainer = pContainerManager->FindContainerById(lContainerId);

                     if (pContainer)
                     {
                         CdmObject* pObject = pContainer->FindObjectById(lObjectId);

                         if (pObject)
                         {
                             QList<CdmJournalItem*> qlItems;
                             pObject->GetChanges(qdFrom, qdTo, qlItems);
                             QVariantList qvResults;

                             for (int iPos = 0; iPos < qlItems.count(); ++iPos)
                             {
                                 CdmJournalItem* pItem = qlItems[iPos];

                                 if (CHKPTR(pItem))
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
                                                "Object not found.",
                                                eWmscomMessageServerityError);
                         }
                     }
                     else
                     {
                         GetResultContainer(m_rpData,
                                            -5000,
                                            "Container not found.",
                                            eWmscomMessageServerityError);
                     }
                 }
                 else
                 {
                     GetResultContainer(m_rpData,
                                        -5000,
                                        "Container Manager not found.",
                                        eWmscomMessageServerityFatal);
                 }
             }
             else
             {
                 GetResultContainer(m_rpData,
                                    -5000,
                                    "Scheme not found.",
                                    eWmscomMessageServerityFatal);
             }
         }
         else
         {
             GetResultContainer(m_rpData,
                                -5000,
                                "Scheme not found.",
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

