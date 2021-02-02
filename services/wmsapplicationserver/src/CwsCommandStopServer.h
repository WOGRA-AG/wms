#ifndef CWSCOMMANDSTOPSERVER_H
#define CWSCOMMANDSTOPSERVER_H

// Own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;


class CwsCommandStopServer : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandStopServer(CwsHttpServer* p_pServer);
    virtual ~CwsCommandStopServer();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDSTOPSERVER_H
