#ifndef CWSCOMMANDADDAPPTOSTORE_H
#define CWSCOMMANDADDAPPTOSTORE_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandAddAppToStore : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandAddAppToStore(CwsHttpServer* p_pServer);
    ~CwsCommandAddAppToStore();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDADDAPPTOSTORE_H
