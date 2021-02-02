#include "CwiCommandObjectListQuery.h"
#include "CdmQuery.h"
#include "CdmQueryEnhanced.h"



CwiCommandObjectListQuery::CwiCommandObjectListQuery(CwmscomData *p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandObjectListQuery::~CwiCommandObjectListQuery()
{

}

void CwiCommandObjectListQuery::Execute()
{
    CwmscomDataResult* pResult = nullptr;

    if (CHKPTR(m_rpData))
    {
       QVariantMap qvHash = m_rpData->GetValue("Query").toMap();
       CdmQuery* pCdmQuery = nullptr;

       if (qvHash["EnhancedQuery"].toBool())
       {
          pCdmQuery = new CdmQueryEnhanced(qvHash);
       }
       else
       {
          pCdmQuery = new CdmQuery(qvHash);
       }

       if (pCdmQuery->Execute() > 0)
       {
          pResult = GetResultContainer(m_rpData,
                                       1,
                                       "Query executed!",
                                       eWmscomMessageServerityInfo);

          pResult->AddValue("Query", pCdmQuery->GetVariant());
       }
       else
       {
          pResult = GetResultContainer(m_rpData,
                                       -5000,
                                       "Query execution failed!",
                                       eWmscomMessageServerityError);
       }

       DELPTR(pCdmQuery);
    }
}

