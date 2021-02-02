// System and Qt Includes

// WMS Commons Includes
#include "CwsHttpServer.h"

// WMS Includes
#include "CdmLogging.h"
#include "CwmsJson.h"
#include "CdmSessionManager.h"
// Basetools Includes
#include "CwmsContext.h"
#include "CwmsApplicationServices.h"

// WMS COM Includes
#include "CwmscomHandler.h"

// own Includes
#include "CwsServerStrings.h"
#include "CwsRequest.h"
#include "CwsResponse.h"
#include "CwmsServerSettings.h"
#include "CwsCommandStartServer.h"


#define DEFAULT_SESSION_TIMEOUT 30

CwsCommandStartServer::CwsCommandStartServer(CwsHttpServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{
}

CwsCommandStartServer::~CwsCommandStartServer()
{
}

void CwsCommandStartServer::LoadFunctionPlugins()
{
    CwmsContext::GetContext()->ServerLogin();
    CwmsPluginManager* pPluginManager = CwmsContext::GetContext()->GetPluginManager();
    pPluginManager->LoadServerPlugins();
    CwmsContext::GetContext()->ServerLogout();
}

int CwsCommandStartServer::Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;
    int iPort = p_rRequest.GetValue("port").toInt();
    LoadFunctionPlugins();
    CwmscomHandler* pHandler = CwmscomHandler::CreateOrGetCommandHandler();
    CwmsServerSettings cSettings;
    QString qstrUser = cSettings.getServerUser();
    QString qstrPasswort = cSettings.getServerUserPassword();
    IwmsParser* pParser = new CwmsJson();
    IwmsSerializer* pSerializer =  new CwmsJson();

    if (pHandler && pParser && pSerializer)
    {
        pHandler->Init();
        pHandler->SetSystemUserLogin(qstrUser);
        pHandler->SetSystemUserPassword(qstrPasswort);
        pHandler->SetParser(pParser); // change of ownership
        pHandler->SetSerializer(pSerializer); // change of ownership
        CdmSessionManager::GetSessionManager()->SetSessionTimeoutMinutes(DEFAULT_SESSION_TIMEOUT);
        m_rpCwsServer->SetPort(iPort);
        m_rpCwsServer->SetRequestHandler(pHandler);
        m_rpCwsServer->SetMaxThreadCount(4);
        m_rpCwsServer->Start();

        if (m_rpCwsServer->isListening())
        {
            iRet = EC(eDmOk);
            p_rResponse.SetMessage("Command successfully executed: Server started");
            p_rResponse.SetValue(RESULT, true);
            p_rResponse.SetStatusCode(eWmsHttpStatusCodeOk);
        }
        else
        {
            QString qstrMessage = QString("Listening on port %1 is not possible!\n").arg(cSettings.getPort());
            qstrMessage += m_rpCwsServer->errorString();
            p_rResponse.AddError(qstrMessage);
            p_rResponse.SetValue(RESULT, false);
            iRet = EC(eDmServerError);
            p_rResponse.SetStatusCode(eWmsHttpStatusCodeInternalServerError);
            p_rResponse.SetMessage("Server Start failed: " + qstrMessage);
            ERR(qstrMessage);
        }
    }

    return iRet;
}
