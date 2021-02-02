#ifndef CWSHTTPSERVERREQUEST_H
#define CWSHTTPSERVERREQUEST_H

// System and Qt Includes
#include <QRunnable>
#include <QTcpSocket>
#include <QTimer>

// own includes
#include "CwsHttpRequest.h"
#include "wmscommons.h"

// forwards
class IwmsHttpRequestHandler;


class WMSCOMMONS_API CwsHttpServerRequest : public QRunnable, public CwsHttpRequest
{
private:
    int m_iSocketDescriptor;
    int m_iExpectedSize;
    bool m_bParseRequest;

    bool m_bProcessReadFinished;
    bool m_bChildProcessFinished;
    IwmsHttpRequestHandler* m_rpRequestHandler;
    QTcpSocket* m_pClientSocket;

public:
    CwsHttpServerRequest(qintptr p_iSocketIdentifiyer,
                         IwmsHttpRequestHandler* p_pHandler);
    virtual ~CwsHttpServerRequest();

    void SetSocketIdentifier(int val) { m_iSocketDescriptor = val; }
    void Init();
    void run();
    void SetRequestHandler(IwmsHttpRequestHandler *p_pHandler);
    void SetParseRequest(bool p_bParse);
private:

    bool ReadRequestFromClient();
    bool WriteResultToClient(CwsHttpResponse& p_rResponse);
};

#endif // CWSHTTPSERVERREQUEST_H
