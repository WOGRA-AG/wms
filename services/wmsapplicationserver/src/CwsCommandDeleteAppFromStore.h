#ifndef CWSCOMMANDDELETEAPPFROMSTORE_H
#define CWSCOMMANDDELETEAPPFROMSTORE_H

// System and Qt Includes

// own Includes
#include "IwsServerCommand.h"

// Forwards
class CwsHttpServer;

class CwsCommandDeleteAppFromStore : public IwsServerCommand
{

private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandDeleteAppFromStore(CwsHttpServer* p_pServer);
    ~CwsCommandDeleteAppFromStore();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDDELETEAPPFROMSTORE_H
