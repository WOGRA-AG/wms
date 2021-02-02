#ifndef CWSCOMMANDSTARTSERVER_H
#define CWSCOMMANDSTARTSERVER_H

// Own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandStartServer : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

    void LoadFunctionPlugins();
public:
    CwsCommandStartServer(CwsHttpServer* p_pServer);
    virtual ~CwsCommandStartServer();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDSTARTSERVER_H
