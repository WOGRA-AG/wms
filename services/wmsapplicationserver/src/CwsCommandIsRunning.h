#ifndef CWSCOMMANDISRUNNING_H
#define CWSCOMMANDISRUNNING_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandIsRunning : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandIsRunning(CwsHttpServer* p_pServer);
    virtual ~CwsCommandIsRunning();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDISRUNNING_H
