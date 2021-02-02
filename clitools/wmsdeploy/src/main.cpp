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
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsLoggerConsole.h"
#include "CwmsImExportManager.h"
#include "CwmsImportSettings.h"
#include "CwmsApplicationServices.h"
#include "CwmsImport.h"
#include "CwmsExportSettings.h"
#include "CwmsContext.h"
#include "CwmsExportFileWriter.h"

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsArgumentParser.h"

#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define SCHEME_ARG "scheme"
#define FILE_ARG "file"
#define MODE_ARG "mode"
#define MODE_INSTALL "install"
#define MODE_GENERATE "generate"
#define DELETE_BEFORE_DEPLOY "deleteScheme"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_Deploy";


int main(int argc, char *argv[])
{
    CdmLogging::CreateLoggingManager();
    CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    CwmsContext::CreateContext(eWmsApplicationContextCommandLineInterface);
    qInstallMessageHandler(wmsQtMessageHandler);
    QCoreApplication a(argc, argv);

    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    a.setApplicationName("WMS Deploy");
    a.setApplicationVersion(qstrVersion);
    a.setOrganizationDomain("www.wogra.com");
    a.setOrganizationName("WOGRA Consulting GmbH");
    CdmLogging::SetLoggingMode(eDmInfo | eDmWarning | eDmError | eDmFatal);
    CwmsLoggerConsole* pLogger = new CwmsLoggerConsole(a.applicationName(), a.applicationVersion());
    pLogger->AddLoggingRelevance(eDmInfo, "*main.cpp");
    CdmLogging::AddAdaptor(pLogger);

    QMap<QString,QString> qmArgs = CwmsArgumentParser::parseArgs(argc, argv);
    INFO("Checking Arguments");

    // check needed args
    if (qmArgs.contains(FILE_ARG) &&
        qmArgs.contains(LOGIN_ARG) &&
        qmArgs.contains(PASSWORD_ARG) &&
        qmArgs.contains(MODE_ARG) &&
        qmArgs.contains(SCHEME_ARG))
    {
        QString qstrLogin    = CwmsArgumentParser::getArgValue(qmArgs, LOGIN_ARG);
        QString qstrPassword = CwmsArgumentParser::getArgValue(qmArgs, PASSWORD_ARG);
        QString qstrScheme   = CwmsArgumentParser::getArgValue(qmArgs, SCHEME_ARG);
        QString qstrFile    = CwmsArgumentParser::getArgValue(qmArgs, FILE_ARG);
        QString qstrMode = CwmsArgumentParser::getArgValue(qmArgs, MODE_ARG);
        QString qstrDelete = CwmsArgumentParser::getArgValue(qmArgs, DELETE_BEFORE_DEPLOY);

        INFO("Creating Session");
        int iSessionId = 0;
        iSessionId = pFactory->CreateNewSession(qstrLogin, qstrPassword);

        if (SUCCESSFULL(iSessionId))
        {
            // First load scheme
            INFO("Session created.");
            CdmDataProvider* pManager = pFactory->GetDataProvider();

            if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
            {
                if (qstrDelete == "true")
                {
                    INFO("Deleting existing scheme");
                    pManager->RemoveScheme(qstrScheme);
                    INFO("Creating new Scheme");
                    pManager->CreateScheme(qstrScheme);
                }

                INFO("Scheme loaded.");
                CdmScheme* pScheme = pManager->FindSchemeByName(qstrScheme);

                if (qstrMode.toLower() == MODE_INSTALL)
                {
                    INFO("Deploying file to WMS");
                    if (pScheme->Deploy(qstrFile))
                    {
                        INFO("Successfully deployt File.")
                    }
                    else
                    {
                        ERR("Deployment failed.");
                    }
                }
                else if (qstrMode.toLower() == MODE_GENERATE)
                {
                    INFO("Generating Deployment file.");
                    if (pScheme->GenerateDeploymentFile(qstrFile))
                    {
                        INFO("Generating Deployment file was successfull.");
                    }
                    else
                    {
                        ERR("Generating Deployment file failed.");
                    }
                }
            }
            else
            {
                if (qstrMode.toLower() == MODE_INSTALL)
                {
                    pManager->CreateScheme(qstrScheme);
                    CwmsApplicationServices::InitCurrentScheme();
                    CdmScheme* pScheme = pManager->FindSchemeByName(qstrScheme);
                    if (pScheme->Deploy(qstrFile))
                    {
                        INFO("Successfully deployt File.")
                    }
                    else
                    {
                        ERR("Deployment failed.");
                    }
                }
                else
                {
                    ERR("Scheme not found. Generating Deployment file failed.");
                }
            }

            if (CHKPTR(pFactory))
            {
                pFactory->Logout();
            }
        }
        else
        {
            ERR("Login failed.");
        }
    }
    else
    {
        QString qstrMessage = "Arguments are missing. WMSDEPLOY needs " FILE_ARG " " LOGIN_ARG " " PASSWORD_ARG " and " MODE_ARG ".\n";
        qstrMessage += "Example:\n";
        qstrMessage += "wmsdeploy -file=c:/test/test.wdf -login=admin -password=admin -scheme=testScheme -mode=install/generate -deleteScheme=true";


        ERR(qstrMessage);
    }

}
