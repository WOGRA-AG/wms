#ifndef CWSHTTPCLIENT_H
#define CWSHTTPCLIENT_H

// System Qt Includes
#include <QTcpSocket>
#include <QObject>
#include <QNetworkProxy>
#include <QHostAddress>


// Own Incldues
#include "wmscommons.h"
#include "CwsHttpRequest.h"
#include "CwsHttpResponse.h"


class WMSCOMMONS_API CwsHttpClient : public QObject
{
    Q_OBJECT

private:
    bool m_bParseResponse;
    int m_iPort;
    int m_iTimeoutMSecs;
    QHostAddress m_qHostAddress;
    QString m_qstrHost;
    QAbstractSocket* m_pSocket;
    QNetworkProxy* m_pProxy;

    bool SendRequestToServer(QByteArray &p_Request);
    bool ReadResponseFromServer(QByteArray &p_Response);
    void createSocket(CwsHttpRequest &p_rRequest);

public:
    CwsHttpClient();
    virtual ~CwsHttpClient();

public slots:
    bool sendRequest(CwsHttpRequest& p_rRequest, CwsHttpResponse& p_rResponse);
    void SetParseResponse(bool p_bParse);
    void SetPort(int p_iPort);
    void SetProxy(QNetworkProxy* p_pProxy);
    void SetHostAddress(QString p_qstrAddress);
    void SetHostAddress(QHostAddress p_HostAddress);
    void SetRequestTimeout(int p_iMSecs);
};

#endif // CWSHTTPCLIENT_H
