#include "CwiCommandExecuteWQL.h"
#include "CdmDataProvider.h"
#include "CdmQueryBuilder.h"


CwiCommandExecuteWQL::CwiCommandExecuteWQL(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandExecuteWQL::~CwiCommandExecuteWQL()
{

}

void CwiCommandExecuteWQL::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
       QString qstrWql = m_rpData->GetValue("WQL").toString();

       if (pCdmManager)
       {
          IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();

          if (pIdmDataAccess)
          {
             CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

             if (pQuery)
             {
                pResult = GetResultContainer(m_rpData,
                                             1,
                                             "WQL successfull executed",
                                             eWmscomMessageServerityInfo);
                pResult->AddValue("Result", pQuery->GetVariant());
             }
             else
             {
                GetResultContainer(m_rpData,
                   -5000,
                   "WQL Error",
                   eWmscomMessageServerityError);
             }

             DELPTR(pQuery);
          }
          else
          {
             GetResultContainer(m_rpData,
                                           -5000,
                                           "No Data access here",
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
}

