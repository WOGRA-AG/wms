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
#include <QCoreApplication>
#include <qdir.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsLoggerConsole.h"
#include "CwmsImExportManager.h"
#include "CwmsImportSettings.h"
#include "CwmsImport.h"
#include "CwmsExportSettings.h"
#include "CwmsExportFileWriter.h"
#include "CwmsContext.h"

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsArgumentParser.h"


// own Incldudes
#include "CwmsUserHandler.h"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_UserManager_Console";



int main(int argc, char *argv[])
{
    CdmLogging::CreateLoggingManager();
    qInstallMessageHandler(wmsQtMessageHandler);
    QCoreApplication a(argc, argv);
    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    a.setApplicationName("WMS User Manager Console");
    a.setApplicationVersion(qstrVersion);
    a.setOrganizationDomain("www.wogra.com");
    a.setOrganizationName("WOGRA Consulting GmbH");
    CwmsContext::CreateContext(eWmsApplicationContextCommandLineInterface);
    CdmLogging::SetLoggingMode(eDmInfo | eDmWarning | eDmError | eDmFatal);
    CwmsLoggerConsole* pLogger = new CwmsLoggerConsole(a.applicationName(), a.applicationVersion());
    pLogger->AddLoggingRelevance(eDmInfo, "*CwmsUserCommand*");
    CdmLogging::AddAdaptor(pLogger);

    QMap<QString,QString> qmArgs = CwmsArgumentParser::parseArgs(argc, argv);

    CwmsUserHandler cHandler(qmArgs);
    return cHandler.Run();
}
