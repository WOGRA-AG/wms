#ifndef CWSCOMMANDGETSERVERSETTINGS_H
#define CWSCOMMANDGETSERVERSETTINGS_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandGetServerSettings : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandGetServerSettings(CwsHttpServer* p_pServer);
    virtual ~CwsCommandGetServerSettings();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDGETSERVERSETTINGS_H
