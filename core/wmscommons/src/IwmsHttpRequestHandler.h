#ifndef IWMSHTTPREQUESTHANDLER_H
#define IWMSHTTPREQUESTHANDLER_H


// Own Includes
#include "CwsHttpRequest.h"
#include "CwsHttpResponse.h"

class IwmsHttpRequestHandler
{
public:
    virtual ~IwmsHttpRequestHandler(){};

    virtual bool HandleRequest(CwsHttpRequest* p_pRequest, CwsHttpResponse* p_pResponse) = 0;
};

#endif // IWMSHTTPREQUESTHANDLER_H
