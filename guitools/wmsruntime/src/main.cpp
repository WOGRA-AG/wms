// System and QT Includes
#include <QApplication>
#include <qdir.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"

// WMS Basetools Includes
#include "CwmsErrorMessenger.h"
#include "cwmsbtplattforminformation.h"
#include "CwmsContext.h"

// WMS Commons Includes
#include "CwmsArgumentParser.h"
#include "wmsdefines.h"

// own Incldudes
#include "CwmsNonGuiInitApplication.h"
#include "CwmsGuiInitApplication.h"
#include "CwmsMessenger.h"

#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define SCHEME_ARG "scheme"
#define APPLICATION_ARG "app"
#define SIM_MODE_ARG "simmode"

QString g_qstrMajor   = WMS_LIB_VERSION_MAJOR;
QString g_qstrMinor   = WMS_LIB_VERSION_MINOR;
QString g_qstrRelease = WMS_LIB_VERSION_BUGFIX;
QString g_qstrBuilt   = CdmDataProvider::GetBuild();
QString g_qstrInternalApplicationName = "WMS_Runtime";

void setApplicationData(QCoreApplication& p_rApp, QString qstrName, QString qstrVersion, QString qstrDomain, QString OrganizationName)
{
    p_rApp.setApplicationName(qstrName);
    p_rApp.setApplicationVersion(qstrVersion);
    p_rApp.setOrganizationDomain(qstrDomain);
    p_rApp.setOrganizationName(OrganizationName);
}


int main(int argc, char *argv[])
{
    QCoreApplication* pApp = nullptr;
    CwmsInitApplication* pInit = nullptr;
    CwmsbtPlattformInformation cInfo;
    QString qstrStartApplication;

    QString qstrVersion = g_qstrMajor + "." + g_qstrMinor + "." + g_qstrRelease;
    QMap<QString,QString> qmArgs = CwmsArgumentParser::parseArgs(argc, argv);
    CwmsbtPlattformInformation::SetSimulationMode(CwmsArgumentParser::getArgValue(qmArgs, SIM_MODE_ARG));

    if (cInfo.IsNonGuiApp())
    {
        pApp = new QCoreApplication(argc, argv);
        setApplicationData(*pApp,"WMS Runtime", qstrVersion, "www.wogra.com", "WOGRA Consulting GmbH");

        QString qstrLogin    = CwmsArgumentParser::getArgValue(qmArgs, LOGIN_ARG);
        QString qstrPassword = CwmsArgumentParser::getArgValue(qmArgs, PASSWORD_ARG);
        QString qstrScheme   = CwmsArgumentParser::getArgValue(qmArgs, SCHEME_ARG);
        QString qstrApp   = CwmsArgumentParser::getArgValue(qmArgs, APPLICATION_ARG);

        pInit = new CwmsNonGuiInitApplication(pApp->applicationName(),
                                              pApp->applicationVersion(),
                                              qstrLogin,
                                              qstrPassword,
                                              qstrScheme,
                                              qstrApp);
    }
    else
    {
        pApp = new QApplication(argc, argv);
        pApp->connect(pApp, SIGNAL(lastWindowClosed()), pApp, SLOT(quit()));
        setApplicationData(*pApp,"WMS Runtime", qstrVersion, "www.wogra.com", "WOGRA Consulting GmbH");

        pInit = new CwmsGuiInitApplication(pApp->applicationName(),
                                           pApp->applicationVersion());

        if (!qstrStartApplication.isEmpty())
        {
          pInit->SetWmsStartApplication(qstrStartApplication);
        }

        new CwmsMessenger(nullptr, nullptr);
    }

    pInit->InitApplication();
    return pApp->exec();
}
