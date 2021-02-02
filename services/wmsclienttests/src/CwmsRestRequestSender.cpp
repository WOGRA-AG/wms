#include "CwsHttpClient.h"
#include "CwmsRestRequestSender.h"

CwmsRestRequestSender::CwmsRestRequestSender(QString p_qstrUrl, QString p_qstrServer, int p_iPort)
    : m_qstrUrl(p_qstrUrl),
      m_qstrServer(p_qstrServer),
      m_iPort(p_iPort)
{
}




void CwmsRestRequestSender::run()
{
    // ToDo make the rest call
    CwsHttpClient client;
    client.SetPort(m_iPort);
    client.SetHostAddress(m_qstrServer);

    CwsHttpRequest request;
    request.SetMethod(eWsGet);
    request.SetHttpVersion("1.0");
    request.SetUrl(m_qstrUrl);
    request.AddHeader("Authorization", "Basic YWRtaW46YWRtaW4=");
    //request.SetAuthType("Basic");
    //request.SetAuthValue("YWRtaW46YWRtaW4=");

    // TODO set Header

    CwsHttpResponse response;

    client.sendRequest(request, response);
}
