#ifndef CWSCOMMANDGETAPPSTOREDATA_H
#define CWSCOMMANDGETAPPSTOREDATA_H


// own include
#include "IwsServerCommand.h"
#include "CwsHttpServer.h"



class CwsCommandGetAppStoreData : public IwsServerCommand
{
private:
    CwsHttpServer* m_rpCwsServer;

public:
    CwsCommandGetAppStoreData(CwsHttpServer* p_pServer);
    virtual ~CwsCommandGetAppStoreData();
    virtual int Execute(CwsRequest& p_rRequest, CwsResponse& p_rResponse);
};

#endif // CWSCOMMANDGETAPPSTOREDATA_H
