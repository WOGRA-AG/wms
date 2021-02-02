

// System and Qt Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"

// WMS COM Includes
#include "CwmscomHandler.h"

// own Includes
#include "CwsServerStrings.h"
#include "CwsRequest.h"
#include "CwsResponse.h"
#include "CwmsServerSettings.h"
#include "CwsCommandStopServer.h"
#include "CwsHttpServer.h"

CwsCommandStopServer::CwsCommandStopServer(CwsHttpServer* p_pServer)
: m_rpCwsServer(p_pServer)
{
}

CwsCommandStopServer::~CwsCommandStopServer()
{
}

int CwsCommandStopServer::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
   int iRet = 0;
   Q_UNUSED(p_rRequest);

   // Stop the server
   m_rpCwsServer->Stop();

   if (!m_rpCwsServer->isListening())
   {
       iRet = EC(eDmOk);
       p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
       p_rResponse.SetMessage("Command executed. Server stoped");
       p_rResponse.SetValue(RESULT, true);
   }
   else
   {
       QString qstrMessage = "Stopping Server not possible";
       ERR(qstrMessage);
       p_rResponse.AddError(qstrMessage);
       iRet = EC(eDmServerError);
       p_rResponse.SetValue(RESULT, false);
       p_rResponse.SetStatusCode(eWmsHttpStatusCodeInternalServerError);
   }

    return iRet;
}
