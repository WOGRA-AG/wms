/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwsHttpServer.cpp
 ** Started Implementation: 2012/04/02
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QSslSocket>
#include <QSettings>
#include <QThread>
#include <QTimer>
#include <QCoreApplication>

// own Includes
#include "CwmsTimeMeassurement.h"
#include "CwsHttpServer.h"
#include "CwsHttpServerRequest.h"

#define MAX_THREADS 4
#define SERVER_APP_NAME "serverdaemon"
#define SERVERNAME "wmsserver.exe"
#define EXEC_ARG "-exec"
#define PORT_ARG "-port="
#define MAINTENANCE_PORT_ARG "-maintananceport="
#define PROCESS_MEM_CHECK_TIMEOUT 1000*60*60
#define MAX_MEM_USAGE_KB 200*1000*1000
#define DEFAULT_ACTIVE_PORT 8585
#define DEFAULT_BACKUP_PORT 8586
#define DEFAULT_ACTIVE_MAINTENANCE_PORT 8182
#define DEFAULT_BACKUP_MAINTENANCE_PORT 8183
#define DEFAULT_SERVER_PORT 8383
#define DEFAULT_MAINTENANCE_SERVER_PORT 8181
#define MAX_SLEEP_COUNT 5
#define SLEEP_MSECS 100


CwsHttpServer::CwsHttpServer(int p_iListeningPort, int p_iMaxThreads, IwmsHttpRequestHandler* p_pRequestHandler, QObject* pqObject)
    : QTcpServer(pqObject),
      m_iListeningPort(p_iListeningPort),
      m_iMaxThreads(p_iMaxThreads),
      m_bMultiThreading(p_iMaxThreads > 1),
      m_iRequestCount(0),
      m_bParseRequest(true),
      m_rpRequestHandler(p_pRequestHandler)
{
    QThreadPool::globalInstance()->setMaxThreadCount(m_iMaxThreads);
    QThreadPool::globalInstance()->setExpiryTimeout(30000);
}

CwsHttpServer::~CwsHttpServer()
{
}

void CwsHttpServer::SetRequestHandler(IwmsHttpRequestHandler* p_pRequestHandler)
{
    m_rpRequestHandler = p_pRequestHandler;
}

void CwsHttpServer::SetParseRequest(bool p_bParse)
{
    m_bParseRequest = p_bParse;
}

void CwsHttpServer::SetMaxThreadCount(int p_iThreads)
{
    m_iMaxThreads = p_iThreads;
    m_bMultiThreading = (m_iMaxThreads > 1);
    QThreadPool::globalInstance()->setMaxThreadCount(m_iMaxThreads);
}

void CwsHttpServer::Start()
{
    if (m_rpRequestHandler)
    {
        listen(QHostAddress::Any, m_iListeningPort);
    }
    else
    {
        qCritical() << "Can not start Http Server. RequestHandler is missing";
    }
}

void CwsHttpServer::Stop()
{
    close();
}

void CwsHttpServer::SetPort(int p_iPort)
{
    m_iListeningPort = p_iPort;
}

void CwsHttpServer::incomingConnection(qintptr p_iSocketIdentitfyer)
{
   ++m_iRequestCount;

    try
    {
        CwsHttpServerRequest* pRequest = new CwsHttpServerRequest(p_iSocketIdentitfyer, m_rpRequestHandler);
        pRequest->SetParseRequest(m_bParseRequest);

        if (m_bMultiThreading)
        {
            QThreadPool::globalInstance()->start(pRequest);
        }
        else
        {
            pRequest->run();
            delete pRequest;
        }
    }
    catch (...)
    {
    }

}

void CwsHttpServer::Pause()
{
    pauseAccepting();
}

void CwsHttpServer::Resume()
{
    resumeAccepting();
}

