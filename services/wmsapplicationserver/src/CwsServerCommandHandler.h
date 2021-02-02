#ifndef CWSSERVERCOMMANDHANDLER_H
#define CWSSERVERCOMMANDHANDLER_H

// WMS Commons Includes
#include "IwmsHttpRequestHandler.h"
#include "CwsHttpServer.h"

// WMS Basetools Includes
#include "CwmsDataExchangeConfigurator.h"

// WMSQML Includes
#include "CwmsServerSettings.h"

// Own Includes

#include "CwsRequest.h"
#include "CwsResponse.h"


class CwsServerCommandHandler : public IwmsHttpRequestHandler
{
private:
    CwsHttpServer m_Server;
    CwmsDataExchangeConfigurator m_DataExchangeConfigurator;
    int ExtractSeverity(CwmsServerSettings &cSettings);
    int UpdateServerConfig(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int GetServerConfig(CwsRequest &p_rRequest, CwsResponse &p_rResponse);

    int Login(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int Logout(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int DeleteAppStoreScheme(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int AddAppStoreScheme(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
public:
    CwsServerCommandHandler();
    virtual ~CwsServerCommandHandler();
    int Start(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int Stop(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int IsRunning(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int InstallLogging(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int GetOpenSessions(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    int GetAppStoreData(CwsRequest &p_rRequest, CwsResponse &p_rResponse);
    virtual bool HandleRequest(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse);
};

#endif // CWSSERVERCOMMANDHANDLER_H
