#ifndef CWSCOMMANDLOGIN_H
#define CWSCOMMANDLOGIN_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandLogin : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandLogin(CwsHttpServer* p_pServer);
    virtual ~CwsCommandLogin();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDLOGIN_H
