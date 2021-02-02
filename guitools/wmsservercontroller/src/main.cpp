#include <unistd.h>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QApplication>
#include "qtservice.h"

// WMS Commons Includes
#include "wmsServerDefines.h"

// WMS Includes
#include "CdmSessionManager.h"

// BAsetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwsController.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    CdmSessionManager::CreateSessionManager(eDmSettingsModeServer);
    CwmsContext::CreateContext(eWmsApplicationContextServer);
    CwsController* pGuiController = new CwsController(nullptr);
    pGuiController->show();
    return app.exec();
}
