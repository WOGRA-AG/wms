/******************************************************************************
 ** WOGRA Middleware Server Licence Creator Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qapplication.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qdir.h>

// WMS Commons Includes
#include "wmsdefines.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmLogfileWriter.h"
#include "CdmDataProvider.h"

// WMS Basetools Includes
#include "CwmsMessenger.h"
#include "CwmsContext.h"

// own Includes
#include "CwmsInitAdmin.h"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();


int main(int argc, char ** argv)
{
   int iRet = 0;
   qInstallMessageHandler(wmsQtMessageHandler);
   QApplication qApplication(argc, argv);   
   // CwmsContext will be created after login
   new CwmsMessenger(nullptr, nullptr);
   QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
   qApplication.setApplicationName("WMS Development Platform");
   qApplication.setApplicationVersion(qstrVersion);
   qApplication.setOrganizationDomain("www.wogra.com");
   qApplication.setOrganizationName("WOGRA Consulting GmbH");

   CwmsInitAdmin* pInit = new CwmsInitAdmin("WMS Development Platform", qstrVersion);
   pInit->InitApplication();

   qApplication.connect(&qApplication, SIGNAL(lastWindowClosed()),
                        &qApplication, SLOT(quit()));

   iRet = qApplication.exec();
   return iRet;
}
