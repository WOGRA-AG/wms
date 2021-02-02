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
#include "CwmsContext.h"

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsArgumentParser.h"

#define CLASS_ARG "class"
#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define SCHEME_ARG "scheme"
#define FUNCTION_ARG "function"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_Exec";


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
    if (qmArgs.contains(CLASS_ARG) &&
        qmArgs.contains(LOGIN_ARG) &&
        qmArgs.contains(PASSWORD_ARG) &&
        qmArgs.contains(FUNCTION_ARG) &&
        qmArgs.contains(SCHEME_ARG))
    {
        QString qstrLogin    = CwmsArgumentParser::getArgValue(qmArgs, LOGIN_ARG);
        QString qstrPassword = CwmsArgumentParser::getArgValue(qmArgs, PASSWORD_ARG);
        QString qstrScheme   = CwmsArgumentParser::getArgValue(qmArgs, SCHEME_ARG);
        QString qstrClass    = CwmsArgumentParser::getArgValue(qmArgs, CLASS_ARG);
        QString qstrFunction = CwmsArgumentParser::getArgValue(qmArgs, FUNCTION_ARG);

        CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
        int iSessionId = 0;
        iSessionId = pFactory->CreateNewSession(qstrLogin, qstrPassword);

        if (SUCCESSFULL(iSessionId))
        {
            // First load scheme
            CdmDataProvider* pManager = pFactory->GetDataProvider();

            if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
            {
                INFO("Scheme loaded.");
                CdmClass* pClass = pManager->GetClass(qstrScheme, qstrClass);

                if (CHKPTR(pClass))
                {
                    INFO("Class found.");
                    CdmClassMethod* pMethod = pClass->FindMethod(qstrFunction);

                    if (CHKPTR(pMethod))
                    {
                        INFO("Method found.");
                        // third exec function
                        QVariantList qList;
                        CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, nullptr, qList);
                        INFO("Method executed.");
                    }
                    else
                    {
                        ERR("Method not found!");
                    }
                }
                else
                {
                    ERR("Class not found!");
                }
            }
            else
            {
                ERR("Scheme not found!");
            }

            if (CHKPTR(pFactory))
            {
                pFactory->Logout();
            }
        }
        else
        {
            ERR("Login failed!");
        }
    }
    else
    {
        ERR("Arguments are missing!");
    }
}
