#ifndef CWSCOMMANDUPDATESERVERSETTINGS_H
#define CWSCOMMANDUPDATESERVERSETTINGS_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandUpdateServerSettings : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandUpdateServerSettings(CwsHttpServer* p_pServer);
    virtual ~CwsCommandUpdateServerSettings();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDUPDATESERVERSETTINGS_H
