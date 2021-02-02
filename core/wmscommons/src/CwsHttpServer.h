/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbmsWebServer.h
 ** Started Implementation: 2012/04/02
 ** Description:
 ** 
 ** IMplements the webserver class for incoming requests
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWSSERVER_H
#define CWSSERVER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>
#include <QMutex>
#include <QTcpServer>
#include <QProcess>
#include <QThreadPool>

// Own Includes
#include "IwmsHttpRequestHandler.h"
#include "wmscommons.h"

// Forwards
class CwsRequestSocket;


// TypeDefs


/* 
 * This class implements the webserver class for incoming requests
 */
class WMSCOMMONS_API CwsHttpServer : public QTcpServer
{
    Q_OBJECT

    private:
       int m_iListeningPort;
       int m_iMaxThreads;
       bool m_bMultiThreading;
       int m_iRequestCount;
       bool m_bParseRequest;
       IwmsHttpRequestHandler* m_rpRequestHandler;
       QList<CwsRequestSocket*> m_qThreadList;
       QList<CwsRequestSocket*> m_qReleasedThreads;

public:
     CwsHttpServer(int p_iListeningPort, int p_iMaxThreads,  IwmsHttpRequestHandler* p_pRequestHandler, QObject* pqObject = NULL);
     virtual ~CwsHttpServer();
     virtual void incomingConnection(qintptr p_iSocketIdentitfyer);
     void Pause();
     void Resume();
     void Start();
     void Stop();
     void SetPort(int p_iPort);
     void SetRequestHandler(IwmsHttpRequestHandler *p_pRequestHandler);
     void SetMaxThreadCount(int p_iThreads);
     void SetParseRequest(bool p_bParse);
};

#endif // CBMSWEBSERVER_H
