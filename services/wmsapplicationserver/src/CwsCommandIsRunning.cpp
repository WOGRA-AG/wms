
// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CwsHttpServer.h"
#include "CwsServerStrings.h"
#include "CwsCommandIsRunning.h"

CwsCommandIsRunning::CwsCommandIsRunning(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandIsRunning::~CwsCommandIsRunning()
{
}


int CwsCommandIsRunning::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;
    Q_UNUSED(p_rRequest);

    if (m_rpCwsServer->isListening())
    {
        iRet = EC(eDmTrue);
        p_rResponse.SetMessage("Command executed: Server is running");
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetValue(ISRUNNING, true);
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }
    else
    {
        iRet = EC(eDmFalse);
        p_rResponse.SetMessage("Command executed: Server is not running");
        p_rResponse.SetValue(RESULT, true);
        p_rResponse.SetValue(ISRUNNING, false);
        p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
    }

    return iRet;
}
