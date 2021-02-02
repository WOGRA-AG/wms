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
#include "CdmError.h"
#include "CdmManager.h"
#include "CdmMessageManager.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsLoggerConsole.h"
#include "CwmsContext.h"
#include "CwmsErrorMessenger.h"
#include "CwmsImExportManager.h"
#include "CwmsImportSettings.h"
#include "CwmsImport.h"
#include "CwmsExportSettings.h"
#include "CwmsExportFileWriter.h"


// own Incldudes
#include "CwmsMessenger.h"


#define OBJECT_ARG    "-object"
#define CONTAINER_ARG "-container"
#define LOGIN_ARG     "-login"
#define PASSWORD_ARG  "-password"
#define SCHEME_ARG    "-scheme"
#define TEMPLATE_ARG  "-template"
#define FILE_ARG      "-file"
#define ALIAS_APP     "WMS_Runtime"



QString g_qstrMajor = "0";
QString g_qstrMinor = "1";
QString g_qstrRelease = "0";
QString g_qstrBuilt = "1";
QString g_qstrInternalApplicationName = "WMS_Pdf";

QMap<QString,QString> processArgs(int argc, char **argv)
{
    QMap<QString,QString> qmValues;

    for (int counter = 1; counter < argc; ++counter)
    {
        QString qstrArg = argv[counter];

        if (qstrArg.contains("=")) {
            QStringList qstrlArgs = qstrArg.split("=");
            qmValues.insert(qstrlArgs[0], qstrlArgs[1]);
        }
    }

    return qmValues;
}

QString getArgValue(QMap<QString,QString>& p_rqmArgs, QString p_qstrValue)
{
    QString qstrRet;

    if (p_rqmArgs.contains(p_qstrValue))
    {
        qstrRet = p_rqmArgs[p_qstrValue];
    }

    return qstrRet.remove("\"");
}

int main(int argc, char *argv[])
{
    CdmError::CreateErrorManager();
    qInstallMessageHandler(wmsQtMessageHandler);
    QCoreApplication a(argc, argv);
    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    a.setApplicationName("WMS Pdf");
    a.setApplicationVersion(qstrVersion);
    a.setOrganizationDomain("www.wogra.com");
    a.setOrganizationName("WOGRA Consulting GmbH");
    CdmError::SetErrorMode(eDmInfo | eDmWarning | eDmError | eDmFatal);
    CwmsLoggerConsole* pLogger = new CwmsLoggerConsole(a.applicationName(), a.applicationVersion());
    pLogger->AddLoggingRelevance(eDmInfo, "*main.cpp");
    CdmError::AddErrorAdaptor(pLogger);

    QMap<QString,QString> qmArgs = processArgs(argc, argv);

    // check needed args
    if (qmArgs.contains(LOGIN_ARG) &&
        qmArgs.contains(PASSWORD_ARG) &&
        qmArgs.contains(SCHEME_ARG))
    {
        QString qstrLogin     = getArgValue(qmArgs, LOGIN_ARG);
        QString qstrPassword  = getArgValue(qmArgs, PASSWORD_ARG);
        QString qstrScheme    = getArgValue(qmArgs, SCHEME_ARG);
        QString qstrClass     = getArgValue(qmArgs, OBJECT_ARG);
        QString qstrContainer = getArgValue(qmArgs, CONTAINER_ARG);
        QString qstrTemplate  = getArgValue(qmArgs, TEMPLATE_ARG);
        QString qstrFunction  = getArgValue(qmArgs, FILE_ARG);

        CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
        int iSessionId = 0;
        iSessionId = pFactory->CreateNewSession(ALIAS_APP, qstrLogin, qstrPassword);

        if (SUCCESSFULL(iSessionId))
        {
            // First load scheme
            INFO("Login successfull");
            CdmManager* pManager = pFactory->GetManager();

            if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
            {
                INFO("Scheme loaded");

                // TODO
            }

            if (CHKPTR(pFactory))
            {
                pFactory->Logout();
            }
       }
    }
    else
    {
        QString qstrMessage("Arguments missing. You need " LOGIN_ARG ", " PASSWORD_ARG " and " SCHEME_ARG ".\n");
        ERR(qstrMessage);
    }

}
