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

#define CONTAINER_ARG "container"
#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define FILENAME_ARG "filename"
#define CONFIG_ARG "config"
#define MODE_ARG "mode"
#define SCHEME_ARG "scheme"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_DataInterface";


int main(int argc, char *argv[])
{
    CdmLogging::CreateLoggingManager();
    qInstallMessageHandler(wmsQtMessageHandler);
    QCoreApplication a(argc, argv);
    CwmsContext::CreateContext(eWmsApplicationContextCommandLineInterface);
    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    a.setApplicationName("WMS Data Interface");
    a.setApplicationVersion(qstrVersion);
    a.setOrganizationDomain("www.wogra.com");
    a.setOrganizationName("WOGRA Consulting GmbH");
    CdmLogging::SetLoggingMode(eDmInfo | eDmWarning | eDmError | eDmFatal);
    CwmsLoggerConsole* pLogger = new CwmsLoggerConsole(a.applicationName(), a.applicationVersion());
    pLogger->AddLoggingRelevance(eDmInfo, "*main.cpp");
    CdmLogging::AddAdaptor(pLogger);

    QMap<QString,QString> qmArgs = CwmsArgumentParser::parseArgs(argc, argv);

    // check needed args
    if (qmArgs.contains(CONTAINER_ARG) &&
        qmArgs.contains(LOGIN_ARG) &&
        qmArgs.contains(PASSWORD_ARG) &&
        qmArgs.contains(CONFIG_ARG) &&
        qmArgs.contains(MODE_ARG) &&
        qmArgs.contains(SCHEME_ARG))
    {
        QString qstrLogin    = CwmsArgumentParser::getArgValue(qmArgs,LOGIN_ARG);
        QString qstrPassword = CwmsArgumentParser::getArgValue(qmArgs,PASSWORD_ARG);
        QString qstrFilename = CwmsArgumentParser::getArgValue(qmArgs,FILENAME_ARG);
        QString qstrConfig   = CwmsArgumentParser::getArgValue(qmArgs,CONFIG_ARG);
        QString qstrMode     = CwmsArgumentParser::getArgValue(qmArgs,MODE_ARG);
        QString qstrScheme   = CwmsArgumentParser::getArgValue(qmArgs,SCHEME_ARG);
        QString qstrContainer= CwmsArgumentParser::getArgValue(qmArgs,CONTAINER_ARG);


        CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
        int iSessionId = 0;
        iSessionId = pFactory->CreateNewSession(qstrLogin, qstrPassword);

        if (SUCCESSFULL(iSessionId))
        {
            INFO("Login successfull.")
            CdmDataProvider* pManager = pFactory->GetDataProvider();

            if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
            {
                INFO("Loading Scheme successfull.")
                CdmObjectContainer* pContainer = pManager->GetObjectContainerEmpty(qstrContainer);

                if (CHKPTR(pContainer))
                {
                    INFO("Container found.")
                    // third start import
                    CwmsImExportManager cManager;

                    if (qstrMode.toLower() == "import")
                    {
                        CwmsImportSettings cCwmsImportSettings;
                        cCwmsImportSettings.LoadSettings(qstrConfig, pContainer->GetClassId());

                        if (!qstrFilename.isEmpty()) {
                            cCwmsImportSettings.SetFilename(qstrFilename);
                        }

                        CwmsImport cImport;
                        cImport.StartImport(pContainer, cCwmsImportSettings);
                        INFO("Import finished.");
                    }
                    else if (qstrMode.toLower() == "export")
                    {
                        CwmsExportSettings cCwmsExportSettings;
                        cCwmsExportSettings.Load(qstrConfig, pContainer->GetClassId());
                        cCwmsExportSettings.SetContainerId(pContainer->GetId());
                        if (!qstrFilename.isEmpty()) {
                            cCwmsExportSettings.SetFilename(qstrFilename);
                        }

                        CwmsExportWriter cCwmsExportFileWriter(cCwmsExportSettings);
                        cCwmsExportFileWriter.Export();
                        INFO("Export finished.");
                    }
                }
                else
                {
                    ERR("Container not found!")
                }
            }
            else
            {
                ERR("Scheme not found!")
            }

            if (CHKPTR(pFactory))
            {
                pFactory->Logout();
            }
        }
        else
        {
            ERR("Login failed!")
        }
    }
    else
    {
        ERR("Arguments are missing!");
    }
}
