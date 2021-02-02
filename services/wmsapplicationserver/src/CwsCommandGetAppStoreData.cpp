
#include <QVariant>

// Basteools Include
#include "CwmsAppStoreData.h"

#include "CwsCommandGetAppStoreData.h"
#include "CwsServerStrings.h"

CwsCommandGetAppStoreData::CwsCommandGetAppStoreData(CwsHttpServer* p_pServer)
: m_rpCwsServer(p_pServer)
{
}


CwsCommandGetAppStoreData::~CwsCommandGetAppStoreData()
{

}

int CwsCommandGetAppStoreData::Execute(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;
    Q_UNUSED(p_rRequest);

    QVariantList qvlResult;

    CwmsAppStoreData cAppStore;
    cAppStore.GetAppStoreData(qvlResult);

    p_rResponse.SetValue("Apps", qvlResult);
    p_rResponse.SetValue(RESULT, true);
    p_rResponse.SetMessage("Command executed. Appstore Data transmitted");
    p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);

    return iRet;
}


