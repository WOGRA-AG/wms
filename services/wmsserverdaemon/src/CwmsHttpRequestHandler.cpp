// WMS Commons Includes
#include "CwsHttpClient.h"

// Own Includes
#include "CwmsHttpRequestHandler.h"

CwmsHttpRequestHandler::CwmsHttpRequestHandler(int p_iPort)
: m_iPort(p_iPort)
{

}

CwmsHttpRequestHandler::~CwmsHttpRequestHandler()
{

}

bool CwmsHttpRequestHandler::HandleRequest(CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    CwsHttpClient client;
    client.SetParseResponse(false);
    client.SetPort(m_iPort);
    client.SetRequestTimeout(300000); // 5 minutes max
    return client.sendRequest(*p_pRequest, *p_pResponse);
}

void CwmsHttpRequestHandler::SetPort(int p_iPort)
{
    m_iPort = p_iPort;
}
