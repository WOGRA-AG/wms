// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwsServerStrings.h"
#include "CwsHttpServer.h"
#include "CwsCommandLogout.h"


CwsCommandLogout::CwsCommandLogout(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandLogout::~CwsCommandLogout()
{
}


int CwsCommandLogout::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    Q_UNUSED(p_rRequest);
    CdmSessionManager::Logout();
    p_rResponse.SetValue(RESULT, true);
    p_rResponse.SetMessage("Logout succeeded. Session destroyed!");
    return EC(eDmTrue);
}
