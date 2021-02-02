#ifndef CWSCOMMANDLOGOUT_H
#define CWSCOMMANDLOGOUT_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandLogout : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandLogout(CwsHttpServer* p_pServer);
    virtual ~CwsCommandLogout();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDLOGOUT_H
