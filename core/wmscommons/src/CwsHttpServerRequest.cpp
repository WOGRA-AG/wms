

// own includes
#include "CwmsTimeMeassurement.h"
#include "CwsHttpServerRequest.h"
#include "IwmsHttpRequestHandler.h"

#define READ_TIMEOUT 5000
#define PROCESS_TIMEOUT 5000
#define READY_READ_TIMEOUT_APP_SERVER 30000
#define READY_READ_TIMEOUT 2
#define BYTES_WRITTEN_TIMEOUT 10
#define DISCONNECTED_TIMEOUT 10

#define HTTP_HEADER_CONTENT_LENGTH "Content-Length"


CwsHttpServerRequest::CwsHttpServerRequest(qintptr p_iSocketIdentifiyer,
                                           IwmsHttpRequestHandler* p_pHandler)
    : QRunnable(),
      m_iSocketDescriptor(p_iSocketIdentifiyer),
      m_iExpectedSize(0),
      m_bParseRequest(true),
      m_rpRequestHandler(p_pHandler),
      m_pClientSocket(nullptr)
{

}

CwsHttpServerRequest::~CwsHttpServerRequest()
{
    delete m_pClientSocket;
}

void CwsHttpServerRequest::Init()
{
    m_iExpectedSize = 0;
    m_bProcessReadFinished = false;
    m_bChildProcessFinished = false;
    m_rpRequestHandler = nullptr;
}

void CwsHttpServerRequest::SetRequestHandler(IwmsHttpRequestHandler* p_pHandler)
{
    m_rpRequestHandler = p_pHandler;
}

void CwsHttpServerRequest::SetParseRequest(bool p_bParse)
{
    m_bParseRequest = p_bParse;
}

void CwsHttpServerRequest::run()
{
    CwmsTimeMeassurement cTime(false, "Request");
    m_pClientSocket = new QTcpSocket();
    m_pClientSocket->setSocketDescriptor(m_iSocketDescriptor);
    cTime.finishedTask("Created Client Socket");

    try
    {
        if (ReadRequestFromClient())
        {
            cTime.finishedTask("Read Request");
            m_bProcessReadFinished = true;
            if (m_rpRequestHandler)
            {
                CwsHttpResponse response;
                m_rpRequestHandler->HandleRequest(this, &response);
                cTime.finishedTask("Handle Request");
                WriteResultToClient(response);
                cTime.finishedTask("Write Result to Client");
            }
            else
            {
                qCritical() << "Can not handle request. RequestHandler is missing";
            }
        }
    }
    catch (...)
    {
        // Thread aborted this catch block will be used to make sure,
        // that the server does not break down.
    }

    m_pClientSocket->close();
    cTime.finishedTask("Close Connection");
    cTime.finished();
}

bool CwsHttpServerRequest::WriteResultToClient(CwsHttpResponse& p_rResponse)
{
    bool bRet = false;
    QByteArray qbaResponse = p_rResponse.GenerateResponse();
    m_pClientSocket->write(qbaResponse);
    bRet = m_pClientSocket->waitForBytesWritten(BYTES_WRITTEN_TIMEOUT);
    m_pClientSocket->disconnectFromHost();

    if (m_pClientSocket->state() != QAbstractSocket::UnconnectedState)
    {
        m_pClientSocket->waitForDisconnected(DISCONNECTED_TIMEOUT);
    }

    return bRet;
}

bool CwsHttpServerRequest::ReadRequestFromClient()
{
    const QString endSymbol = "\r\n\r\n";
    QByteArray qbaRequest;
    int iHeaderEnd = 0;
    int iLastIndex = 0;
    bool bRet = false;

    while((iHeaderEnd = QString::fromUtf8(qbaRequest).indexOf(endSymbol, iLastIndex)) < 0)
    {
        iLastIndex = qbaRequest.size();

        if(!m_pClientSocket->waitForReadyRead(READY_READ_TIMEOUT))
        {
            break;
        }
        qbaRequest += m_pClientSocket->readAll();

    }

    CopyContent(qbaRequest);
    ParseContent();

    if(m_qmHeaderInformation.contains(HTTP_HEADER_CONTENT_LENGTH)) {
        int iLen = GetIntHeader(HTTP_HEADER_CONTENT_LENGTH);

        while(qbaRequest.size() < iHeaderEnd + 4 + iLen)
        {
            if(!m_pClientSocket->waitForReadyRead(READY_READ_TIMEOUT))
            {
                break;
            }
            qbaRequest += m_pClientSocket->readAll();

        }

        CopyContent(qbaRequest);
        SetBody(QString::fromUtf8(qbaRequest.mid(iHeaderEnd + 4)));
    }

    if (qbaRequest.size() >= GetDocumentLength())
    {
        bRet = true;
    }

    return bRet;
}



