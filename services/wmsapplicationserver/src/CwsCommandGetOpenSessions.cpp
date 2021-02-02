// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
// own Includes
#include "CwsHttpServer.h"
#include "CwsServerStrings.h"
#include "CwsCommandGetOpenSessions.h"

CwsCommandGetOpenSessions::CwsCommandGetOpenSessions(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandGetOpenSessions::~CwsCommandGetOpenSessions()
{
}


int CwsCommandGetOpenSessions::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;
    Q_UNUSED(p_rRequest);

    if (m_rpCwsServer->isListening())
    {
        iRet = CdmSessionManager::GetOpenSessions();
        p_rResponse.SetValue(OPEN_SESSIONS, iRet);
        p_rResponse.SetValue(OPEN_THREADS, CdmSessionManager::GetOpenThreads());
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetMessage("Command executed. Session Information transmitted");
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }
    else
    {
        iRet = EC(eDmFalse);
        p_rResponse.SetValue(OPEN_SESSIONS, CdmSessionManager::GetOpenSessions());
        p_rResponse.SetValue(OPEN_THREADS, CdmSessionManager::GetOpenThreads());
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetMessage("Command executed. Server does not run.");
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }

    return iRet;
}
