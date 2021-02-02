// System and Qt Includes
#include <QSettings>

// WMS Commons
#include "CwmsSettingsStoreFactory.h"

// WMS Manager
#include "CdmLogging.h"

// WMSCOM Includes
#include "CwmscomHandler.h"
#include "CwmscomController.h"

// Own Includes
#include "CsraRestRequestHandler.h"
#include "CsraPlugin.h"



CsraPlugin::CsraPlugin()
{

}


QString CsraPlugin::getVersion()
{
    return "0.1.0";
}

QString CsraPlugin::getName()
{
    return "WMS Simple Rest API";
}

void CsraPlugin::init()
{
    CwmscomHandler* pHandler = CwmscomHandler::CreateOrGetCommandHandler();
    AddWmsHandling(pHandler);
}

void CsraPlugin::AddWmsHandling(CwmscomHandler* p_pHandler)
{
    if (p_pHandler)
    {
        //Creating Controller
        CwmscomController* pController = new CwmscomController("Rest", p_pHandler);
        QScopedPointer<QSettings> pSettings(CwmsSettingsStoreFactory::GenerateServerSettings());

        if (CHKPTR(pSettings))
        {
            new CsraRestRequestHandler(pController);
        }
    }
}
