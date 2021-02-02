#ifndef CWSCOMMANDGETOPENSESSIONS_H
#define CWSCOMMANDGETOPENSESSIONS_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandGetOpenSessions : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandGetOpenSessions(CwsHttpServer* p_pServer);
    virtual ~CwsCommandGetOpenSessions();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDGETOPENSESSIONS_H
