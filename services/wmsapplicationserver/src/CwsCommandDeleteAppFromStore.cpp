
// WMS Includes
#include "CdmLogging.h"

// WMS Basetools Includes
#include "CwmsAppStoreData.h"

// Own Includes
#include "CwsServerStrings.h"
#include "CwsCommandDeleteAppFromStore.h"


CwsCommandDeleteAppFromStore::CwsCommandDeleteAppFromStore(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}


CwsCommandDeleteAppFromStore::~CwsCommandDeleteAppFromStore()
{

}

int CwsCommandDeleteAppFromStore::Execute(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
     int iRet = 0;
    CwmsAppStoreData cAppStore;
   qint64 lId = p_rRequest.GetValue(ID).toInt();

    if (cAppStore.DeleteAppScheme(lId))
    {
        iRet = EC(eDmOk);
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetMessage("Command executed. App Store Scheme Object deleted");
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }
    else
    {
        iRet = EC(eDmUnknownDbError);
        p_rResponse.SetValue(RESULT, false);
        p_rResponse.SetMessage("Command execution failed. AppStore Scheme not deleted with ID "
                               + QString::number(lId) + ".");

        p_rResponse.SetStatusCode(eWmsHttpStatusCodeInternalServerError);
    }

    return iRet;
}
