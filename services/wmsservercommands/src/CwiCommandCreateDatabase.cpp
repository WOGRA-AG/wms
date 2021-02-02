#include "CwiCommandCreateDatabase.h"
#include "CdmDataProvider.h"

CwiCommandCreateDatabase::CwiCommandCreateDatabase(CwmscomData* p_pData)
    :m_rpData(p_pData)
{

}

CwiCommandCreateDatabase::~CwiCommandCreateDatabase()
{

}

void CwiCommandCreateDatabase::Execute()
{
    CwmscomDataResult* pResult = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    QString qstrScheme = m_rpData->GetValue("Name").toString();

    long lId = pCdmManager->CreateScheme(qstrScheme);

    if (lId >= 0)
    {
       pResult = GetResultContainer(m_rpData,
                                    1,
                                    "Scheme created!",
                                    eWmscomMessageServerityInfo);
    }
    else
    {
       pResult = GetResultContainer(m_rpData,
                                    -5000,
                                    "Scheme creation failed!",
                                    eWmscomMessageServerityError);
    }

    pResult->AddValue("Id", (int)lId);
}

