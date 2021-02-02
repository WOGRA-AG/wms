#ifndef CWMSHTTPREQUESTHANDLER_H
#define CWMSHTTPREQUESTHANDLER_H

#include "IwmsHttpRequestHandler.h"


class CwmsHttpRequestHandler : public IwmsHttpRequestHandler
{
private:
    int m_iPort;

public:
    CwmsHttpRequestHandler(int p_iPort);
    virtual ~CwmsHttpRequestHandler();
    virtual bool HandleRequest(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse);
    void SetPort(int p_iPort);
};

#endif // CWMSHTTPREQUESTHANDLER_H
