#include "CwiCommandGetAppStoreData.h"

// Basteools Include
#include "CwmsAppStoreData.h"
#include "CwmscomDataResult.h"
#include "WmsInterfaceDefines.h"

CwiCommandGetAppStoreData::CwiCommandGetAppStoreData(CwmscomData* p_pData): m_rpData(p_pData)
{
}


CwiCommandGetAppStoreData::~CwiCommandGetAppStoreData()
{

}

void CwiCommandGetAppStoreData::Execute()
{
    CwmscomDataResult* pResult = new CwmscomDataResult(m_rpData);

    QVariantList qvlResult;

    CwmsAppStoreData cAppStore;
    cAppStore.GetAppStoreData(qvlResult);

    pResult->AddValue(APPS,qvlResult);
    pResult->AddValue(RESULT, true);
    pResult->SetMessageCode(eWmsHttpStatusCodeOk);
    pResult->SetMessage("Command executed. Appstore Data transmitted");
    pResult->SetSeverity(eWmscomMessageServerityInfo);
}
