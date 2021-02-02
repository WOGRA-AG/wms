
#include <QtScript>

// WMS Includes
#include "CdmLogging.h"

// WMS Commons Includes
#include "CwsHttpClient.h"
#include "CwsHttpRequest.h"

#include "CwmsScriptableHttpClient.h"

CwmsScriptableHttpClient::CwmsScriptableHttpClient()
{
}

CwmsScriptableHttpClient::~CwmsScriptableHttpClient()
{

}


QObject* CwmsScriptableHttpClient::createHttpClient()
{
    CwsHttpClient* pClient = new CwsHttpClient();
    addObjectForGarbageCollection(pClient);
    return pClient;
}


QObject* CwmsScriptableHttpClient::createHttpRequest()
{
    CwsHttpRequest* pRequest = new CwsHttpRequest();
    addObjectForGarbageCollection(pRequest);
    return pRequest;
}

QObject* CwmsScriptableHttpClient::sendRequest(QObject* p_pClient, QObject* p_pRequest)
{
    CwsHttpResponse* pResponse = nullptr;
    CwsHttpClient* pClient = dynamic_cast<CwsHttpClient*> (p_pClient);
    CwsHttpRequest* pRequest = dynamic_cast<CwsHttpRequest*> (p_pRequest);
    if (CHKPTR(pClient) && CHKPTR(pRequest))
    {
        pResponse = new CwsHttpResponse();
        addObjectForGarbageCollection(pResponse);
        pClient->sendRequest(*pRequest, *pResponse);
    }

    return pResponse;
}

