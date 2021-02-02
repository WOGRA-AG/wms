#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CwmscomDataResult.h"

#include "CwiCommandGetSchemeList.h"

CwiCommandGetSchemeList::CwiCommandGetSchemeList(CwmscomData* p_pData)
: m_rpData(p_pData)
{
}

CwiCommandGetSchemeList::~CwiCommandGetSchemeList()
{

}

void CwiCommandGetSchemeList::Execute()
{
    if (m_rpData)
    {
       CwmscomDataResult* pResult = nullptr;
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (pCdmManager)
       {
          QLinkedList<QString> qllDbs;
          pCdmManager->GetSchemeList(qllDbs);

          pResult = GetResultContainer(m_rpData,
                                        1,
                                        "Databases returned!",
                                        eWmscomMessageServerityInfo);


          QList<QVariant> qllResults;

          QLinkedList<QString>::iterator qllIt = qllDbs.begin();
          QLinkedList<QString>::iterator qllItEnd = qllDbs.end();

          for (; qllIt != qllItEnd; ++qllIt)
          {
             qllResults.append(*qllIt);
          }

          pResult->AddValue("List", qllResults);
       }
    }
}
