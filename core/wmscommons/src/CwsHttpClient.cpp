
// System and Qt Includes
#include <QSslSocket>

// Own Incldues
#include "CwsHttpClient.h"

// Defines
#define READY_READ_TIMEOUT_APP_SERVER 50

CwsHttpClient::CwsHttpClient()
: m_bParseResponse(true),
  m_iPort(80),
  m_iTimeoutMSecs(READY_READ_TIMEOUT_APP_SERVER),
  m_qHostAddress(QHostAddress::LocalHost),
  m_pSocket(nullptr),
  m_pProxy(nullptr)
{
}

CwsHttpClient::~CwsHttpClient()
{
    delete m_pSocket;
}

void CwsHttpClient::SetParseResponse(bool p_bParse)
{
    m_bParseResponse = p_bParse;
}

void CwsHttpClient::SetPort(int p_iPort)
{
    m_iPort = p_iPort;
}

void CwsHttpClient::SetProxy(QNetworkProxy* p_pProxy)
{
    m_pProxy = p_pProxy;
}

void CwsHttpClient::SetRequestTimeout(int p_iMSecs)
{
    m_iTimeoutMSecs = p_iMSecs;
}

void CwsHttpClient::SetHostAddress(QString p_qstrAddress)
{
    m_qstrHost = p_qstrAddress;
}

void CwsHttpClient::SetHostAddress(QHostAddress p_HostAddress)
{
    m_qHostAddress = p_HostAddress;
}

void CwsHttpClient::createSocket(CwsHttpRequest &p_rRequest)
{
    if (m_pSocket) // for reuse
    {
        delete m_pSocket;
    }

    if (p_rRequest.IsSSLRequest())
    {
        m_pSocket = new QSslSocket();
    }
    else
    {
        m_pSocket = new QTcpSocket();
    }

    if (m_pProxy)
    {
        m_pSocket->setProxy(*m_pProxy);
    }
}

bool CwsHttpClient::sendRequest(CwsHttpRequest &p_rRequest, CwsHttpResponse &p_rResponse)
{
    bool bSuccess = false;
    createSocket(p_rRequest);
    QByteArray qbaRequest;
    QByteArray qbaResponse;
    qbaRequest.append(p_rRequest.GenerateRequestString().toUtf8());

    if (SendRequestToServer(qbaRequest))
    {
        bSuccess = ReadResponseFromServer(qbaResponse);
        p_rResponse.CopyContent(qbaResponse);

        if (m_bParseResponse)
        {
            p_rResponse.ParseContent();
        }
    }

    return bSuccess;
}


bool CwsHttpClient::SendRequestToServer(QByteArray& p_Request)
{
    bool bRet = false;
    if (m_qstrHost.isEmpty())
    {
        m_pSocket->connectToHost(m_qHostAddress, m_iPort);
    }
    else
    {
        QString qstrHost = m_qstrHost;
        int iPos = qstrHost.indexOf("://");

        if (iPos > 0)
        {
            qstrHost = qstrHost.mid(iPos + 3);
        }

        m_pSocket->connectToHost(qstrHost, m_iPort);
    }

   if (m_pSocket->waitForConnected())
   {
       m_pSocket->write(p_Request);
       bRet = m_pSocket->waitForBytesWritten(m_iTimeoutMSecs);
   }
   else
   {
       QString qstrError = m_pSocket->errorString();
       qWarning() << qstrError;
   }

   return bRet;
}

bool CwsHttpClient::ReadResponseFromServer(QByteArray& p_Response)
{
    bool bRet = false;

    if (m_pSocket->waitForReadyRead(m_iTimeoutMSecs))
    {
        quint64 bytes = m_pSocket->bytesAvailable();
        while (bytes > sizeof(quint64))
        {
            p_Response += m_pSocket->readAll();
            bRet = true;
            if (!m_pSocket->waitForReadyRead(m_iTimeoutMSecs))
            {
                break;
            }
        }
    }
    else
    {
        QString qstrError = m_pSocket->errorString();
        qstrError = "Not ready to read from application server!\n" + qstrError;
        p_Response += qstrError.toUtf8();
        qWarning() << qstrError;
    }

    return bRet;
}
