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
#include "CdmQueryBuilder.h"
#include "CdmQueryEnhanced.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsLoggerConsole.h"
#include "CwmsContext.h"

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsArgumentParser.h"


#define WQL_ARG "wql"
#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define SCHEME_ARG "scheme"
#define FILE_ARG "file"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_WQL";


int main(int argc, char *argv[])
{
    CdmLogging::CreateLoggingManager();
    qInstallMessageHandler(wmsQtMessageHandler);
    QCoreApplication a(argc, argv);
    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    a.setApplicationName("WMS Wql");
    a.setApplicationVersion(qstrVersion);
    a.setOrganizationDomain("www.wogra.com");
    a.setOrganizationName("WOGRA Consulting GmbH");
    CwmsContext::CreateContext(eWmsApplicationContextCommandLineInterface);
    CdmLogging::SetLoggingMode(eDmInfo | eDmWarning | eDmError | eDmFatal);
    CwmsLoggerConsole* pLogger = new CwmsLoggerConsole(a.applicationName(), a.applicationVersion());
    pLogger->AddLoggingRelevance(eDmInfo, "*main.cpp");
    CdmLogging::AddAdaptor(pLogger);

    QMap<QString,QString> qmArgs = CwmsArgumentParser::parseArgs(argc, argv);

    // check needed args
    if (qmArgs.contains(WQL_ARG) &&
        qmArgs.contains(LOGIN_ARG) &&
        qmArgs.contains(PASSWORD_ARG) &&
        qmArgs.contains(FILE_ARG) &&
        qmArgs.contains(SCHEME_ARG))
    {
        QString qstrLogin    = CwmsArgumentParser::getArgValue(qmArgs, LOGIN_ARG);
        QString qstrPassword = CwmsArgumentParser::getArgValue(qmArgs, PASSWORD_ARG);
        QString qstrScheme   = CwmsArgumentParser::getArgValue(qmArgs, SCHEME_ARG);
        QString qstrFile     = CwmsArgumentParser::getArgValue(qmArgs, FILE_ARG);
        QString qstrWql      = CwmsArgumentParser::getArgValue(qmArgs, WQL_ARG);


        CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
        int iSessionId = 0;
        iSessionId = pFactory->CreateNewSession(qstrLogin, qstrPassword);

        if (SUCCESSFULL(iSessionId))
        {
            INFO("Login successfull");
            // First load scheme
            CdmDataProvider* pManager = pFactory->GetDataProvider();
            QFile* pFile = nullptr;

            if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
            {
                INFO("Loading Scheme successfull!");
                CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

                if (CHKPTR(pQuery))
                {
                    QString qstrResult = pQuery->GetResultAsString();
                    QTextStream stream(stdout);

                    if (!qstrFile.isEmpty())
                    {
                        pFile = new QFile(qstrFile);

                        if (pFile->open(QIODevice::WriteOnly))
                        {
                            stream.setDevice(pFile);
                        }
                        else
                        {
                            ERR("File not writable. Writing to stdout.");
                        }
                    }
                    else
                    {
                        ERR("Filename not found. Can not write result to file.")
                    }


                    stream << qstrResult;
                    stream.flush();

                    if (pFile)
                    {
                        pFile->close();
                        DELPTR(pFile);
                    }

                    INFO("WQL File written");
                }
            }

            if (CHKPTR(pFactory))
            {
                pFactory->Logout();
            }
        }
        else
        {
            ERR("Login failed.")
        }
    }
    else
    {
        ERR("Arguments missing.");
    }
}
