
// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwsServerStrings.h"
#include "CwsHttpServer.h"
#include "CwsCommandLogin.h"



CwsCommandLogin::CwsCommandLogin(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandLogin::~CwsCommandLogin()
{
}


int CwsCommandLogin::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    QString qstrLogin = p_rRequest.GetValue(LOGIN).toString();
    QString qstrPassword = p_rRequest.GetValue(PASSWORD).toString();

    int iSession = CdmSessionManager::Login(qstrLogin,
                                            qstrPassword);

    if (iSession > 0)
    {
       p_rResponse.SetMessage("Login succeeded. New Session established!");
       p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
       p_rResponse.SetValue(RESULT, true);
       p_rResponse.SetValue(SESSION, iSession);
    }
    else
    {
       p_rResponse.SetMessage("Login failed!");
       p_rResponse.SetValue(RESULT, false);
       p_rResponse.SetStatusCode(eWmsHttpStatusCodeUnauthorized);
    }

    p_rResponse.SetValue("SessionId", iSession);
    return EC(eDmTrue);
}
