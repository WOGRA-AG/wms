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
#include "CwiPing.h"
#include "CwiLogin.h"
#include "CwiLoginInt.h"
#include "CwiLogout.h"
#include "CwiUser.h"
#include "CwiUserList.h"
#include "CwiUserGroupList.h"
#include "CwiClassManager.h"
#include "CwiObject.h"
#include "CwiObjectList.h"
#include "CwiDatabase.h"
#include "CwiRuntime.h"
#include "CwiServerFunctions.h"
#include "CwiServerPlugin.h"
#include "WmsInterfaceDefines.h"


CwiServerPlugin::CwiServerPlugin()
{

}


QString CwiServerPlugin::getVersion()
{
    return "1.0.0";
}

QString CwiServerPlugin::getName()
{
    return "WMS Server Commands";
}

void CwiServerPlugin::init()
{
    CwmscomHandler* pHandler = CwmscomHandler::CreateOrGetCommandHandler();
    AddWmsHandling(pHandler);
}

void CwiServerPlugin::AddWmsHandling(CwmscomHandler* p_pHandler)
{
    if (p_pHandler)
    {
        //Creating Controller
        CwmscomController* pController = new CwmscomController("Wms", p_pHandler);
        QScopedPointer<QSettings> pSettings(CwmsSettingsStoreFactory::GenerateServerSettings());

        if (CHKPTR(pSettings))
        {
            // Creating Functions
            // will be handled and destroyed by the pController

            if (pSettings->value(SERVICE_LOGIN, true).toBool() == true)
            {
                new CwiLogin(pController);
                if (!pSettings->contains(SERVICE_LOGIN))
                {
                    pSettings->setValue(SERVICE_LOGIN, true);
                }
            }

            if (pSettings->value(SERVICE_LOGIN_INT, true).toBool() == true)
            {
                new CwiLoginInt(pController);
                if (!pSettings->contains(SERVICE_LOGIN_INT))
                {
                    pSettings->setValue(SERVICE_LOGIN_INT, true);
                }
            }

            if (pSettings->value(SERVICE_LOGOUT, true).toBool() == true)
            {
                new CwiLogout(pController);
                if (!pSettings->contains(SERVICE_LOGOUT))
                {
                    pSettings->setValue(SERVICE_LOGOUT, true);
                }
            }

            if (pSettings->value(SERVICE_USER, true).toBool() == true)
            {
                new CwiUser(pController);
                if (!pSettings->contains(SERVICE_USER))
                {
                    pSettings->setValue(SERVICE_USER, true);
                }
            }

            if (pSettings->value(SERVICE_USER_LIST, true).toBool() == true)
            {
                new CwiUserList(pController);
                if (!pSettings->contains(SERVICE_USER_LIST))
                {
                    pSettings->setValue(SERVICE_USER_LIST, true);
                }
            }

            if (pSettings->value(SERVICE_USER_GROUP_LIST, true).toBool() == true)
            {
                new CwiUserGroupList(pController);
                if (!pSettings->contains(SERVICE_USER_GROUP_LIST))
                {
                    pSettings->setValue(SERVICE_USER_GROUP_LIST, true);
                }
            }

            if (pSettings->value(SERVICE_CLASS_MANAGER, true).toBool() == true)
            {
                new CwiClassManager(pController);
                if (!pSettings->contains(SERVICE_CLASS_MANAGER))
                {
                    pSettings->setValue(SERVICE_CLASS_MANAGER, true);
                }
            }

            if (pSettings->value(SERVICE_SCHEME, true).toBool() == true)
            {
                new CwiDatabase(pController);

                if (!pSettings->contains(SERVICE_SCHEME))
                {
                    pSettings->setValue(SERVICE_SCHEME, true);
                }
            }

            if (pSettings->value(SERVICE_OBJECT, true).toBool() == true)
            {
                new CwiObject(pController);
                if (!pSettings->contains(SERVICE_OBJECT))
                {
                    pSettings->setValue(SERVICE_OBJECT, true);
                }
            }

            if (pSettings->value(SERVICE_OBJECT_CONTAINER, true).toBool() == true)
            {
                new CwiObjectContainer(pController);
                if (!pSettings->contains(SERVICE_OBJECT_CONTAINER))
                {
                    pSettings->setValue(SERVICE_OBJECT_CONTAINER, true);
                }
            }

            if (pSettings->value(SERVICE_RUNTIME, true).toBool() == true)
            {
                new CwiRuntime(pController);
                if (!pSettings->contains(SERVICE_RUNTIME))
                {
                    pSettings->setValue(SERVICE_RUNTIME, true);
                }
            }

            if (pSettings->value(SERVICE_SERVER_FUNCTIONS, true).toBool() == true)
            {
                new CwiServerFunctions(pController);
                if (!pSettings->contains(SERVICE_SERVER_FUNCTIONS))
                {
                    pSettings->setValue(SERVICE_SERVER_FUNCTIONS, true);
                }
            }

            if (pSettings->value(SERVICE_PING, true).toBool() == true)
            {
                new CwiPing(pController);
                if (!pSettings->contains(SERVICE_PING))
                {
                    pSettings->setValue(SERVICE_PING, true);
                }
            }
        }
        // Insert here: further functions
    }
}
