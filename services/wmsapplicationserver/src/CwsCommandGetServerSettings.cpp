
// System and Qt Includes
#include <QVariant>

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmSettings.h"

// BASETOOLS Includes
#include "CwmsContext.h"

// own Includes
#include "CwsHttpServer.h"
#include "CwsServerStrings.h"
#include "CwsCommandGetServerSettings.h"

CwsCommandGetServerSettings::CwsCommandGetServerSettings(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandGetServerSettings::~CwsCommandGetServerSettings()
{
}


int CwsCommandGetServerSettings::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    Q_UNUSED(p_rRequest);

    CdmSettings cSettings(eDmSettingsModeServer);
    QVariantMap config = cSettings.getValueMap();
    p_rResponse.SetValue(CONFIGURATION, config);
    p_rResponse.SetValue(RESULT, true);
    p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    p_rResponse.SetMessage("Command executed. Configurations transmitted");
    return EC(eDmOk);
}
