
// WMS Includes
#include "CdmLogging.h"

// WMS Basetools Includes
#include "CwmsAppStoreData.h"

// Own Includes
#include "CwsServerStrings.h"
#include "CwsCommandAddAppToStore.h"

CwsCommandAddAppToStore::CwsCommandAddAppToStore(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandAddAppToStore::~CwsCommandAddAppToStore()
{

}

int CwsCommandAddAppToStore::Execute(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;
    CwmsAppStoreData cAppStore;
    QVariantMap qmValues = p_rRequest.GetMembers();
    iRet = cAppStore.AddAppScheme(qmValues);

    if (SUCCESSFULL(iRet))
    {
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetValue(ID, iRet);
        p_rResponse.SetMessage("Command executed. App Store Scheme Object created.");
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }
    else
    {
        iRet = EC(eDmUnknownDbError);
        p_rResponse.SetValue(RESULT, false);
        p_rResponse.SetMessage("Command execution failed. AppStore Scheme not created.");
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }

    return iRet;
}
