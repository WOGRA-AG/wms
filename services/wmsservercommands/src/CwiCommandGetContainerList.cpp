#include "CwiCommandGetContainerList.h"
#include "CdmDataProvider.h"
#include "IdmDataAccess.h"



CwiCommandGetContainerList::CwiCommandGetContainerList(CwmscomData *p_pData,qint64 p_lDbId)
    :m_rpData(p_pData),
     m_rlDbId(p_lDbId)
{

}

CwiCommandGetContainerList::~CwiCommandGetContainerList()
{

}

void CwiCommandGetContainerList::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
      qint64 lClassId = m_rpData->GetValue("ClassId").toInt();

       CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pManager))
       {
          IdmDataAccess* pDataAccess = pManager->GetDataAccess();

          if (CHKPTR(pDataAccess))
          {
             QMap<qint64, QString> qmContainers;
             if (pDataAccess->GetContainerList(m_rlDbId,
                                               lClassId,
                                               qmContainers) > 0)
             {
                pResult = GetResultContainer(m_rpData,
                                             1,
                                             "Containerlist loaded",
                                             eWmscomMessageServerityInfo);

                QVariantMap qMap;

                QMap<qint64, QString>::iterator qmIt = qmContainers.begin();
                QMap<qint64, QString>::iterator qmItEnd = qmContainers.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                   qMap.insert(QString::number(qmIt.key()), qmIt.value());
                }

                pResult->AddValue("List", qMap);
             }
             else
             {
                ERR("Error in executing request GetContainerList");
                pResult = GetResultContainer(m_rpData,
                                             -5000,
                                             "Executing containerlist request failed on backendside",
                                             eWmscomMessageServerityError);
             }
          }
          else
          {
             pResult = GetResultContainer(m_rpData,
                                           -5000,
                                           "No dataaccess configured on backend side",
                                           eWmscomMessageServerityError);
          }
       }
       else
       {
          pResult = GetResultContainer(m_rpData,
                                       -5000,
                                       "Invalid session object creation not possible!",
                                       eWmscomMessageServerityFatal);
       }
    }
}

