/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: main.cpp
 ** Started Implementation: 2012/04/02
 ** Description:
 **
 ** IMplements the main routine for starting the webserver.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QApplication>

#ifdef PRINTING_SUPPORT
#include <QPrinter>
#endif

#include <QSettings>

// WMS Commons Includes
#include "CwmsSettingsStoreFactory.h"
#include "CwsHttpServer.h"

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// Basetools Incldues
#include "CwmsContext.h"

// own Includes
#include "CwsService.h"

int main(int argc, char *argv[])
{
   CdmLogging::CreateLoggingManager();

#ifdef PRINTING_SUPPORT
   QApplication app(argc, argv); // for printing plugin it must be initialized after CwsServerCommandHandler
#else
   QCoreApplication app(argc, argv); // for printing plugin it must be initialized after CwsServerCommandHandler
#endif


   CdmSessionManager::CreateSessionManager(eDmSettingsModeServer);
   CwmsContext::CreateContext(eWmsApplicationContextServer);
   CwsServerCommandHandler commandHandler;



   CwsRequest cRequest;
   CwsResponse cResponse;
   commandHandler.InstallLogging(cRequest, cResponse);

   qInstallMessageHandler(wmsQtMessageHandler);

#ifdef PRINTING_SUPPORT
   //Added because of an strange runtime exception near ncreport
   //TODO Check what the hell is going on (Stefan Fenn)
   new QPrinter();
#endif

   CwsService serviceApp(argc, argv, &commandHandler);
   CwsHttpServer* pServerController = new CwsHttpServer(serviceApp.GetMaintenancePort(), 1, &commandHandler);
   serviceApp.start();
   pServerController->Start();
   return app.exec();
}
