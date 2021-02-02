// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmSettings.h"

// own Includes
#include "CwsHttpServer.h"
#include "CwsServerStrings.h"
#include "CwsCommandUpdateServerSettings.h"


CwsCommandUpdateServerSettings::CwsCommandUpdateServerSettings(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandUpdateServerSettings::~CwsCommandUpdateServerSettings()
{
}


int CwsCommandUpdateServerSettings::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{

    CdmSettings cSettings(eDmSettingsModeServer);
    QVariantMap config = p_rRequest.GetValue(CONFIGURATION).toMap();
    cSettings.setValueMap(config);
    p_rResponse.SetValue(RESULT, true);
    p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    p_rResponse.SetMessage("Command executed. Server new Configurations commited");
    return EC(eDmOk);
}
