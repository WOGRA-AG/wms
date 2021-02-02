/******************************************************************************
 ** WOGRA Consulting GmbH Modul Information
 ** Modulename: <Dateiname>
 ** Started Implementation: <Datum>
 ** Description:
 **
 ** <Beschreibung>
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

// WMS Manager Includes
#include "CdmSessionManager.h"

// BAsetools Includes
#include "CwmsApplication.h"
#include "CwmsContext.h"

// own Includes
#include "CwmsQmlDatabaseSelection.h"
#include "CwmsQmlApplicationSelection.h"
#include "CwmsApplicationServices.h"
#include "CwmsQmlApplicationController.h"
#include "CwmsQmlInitApplication.h"

CwmsQmlInitApplication::CwmsQmlInitApplication(QString p_qstrApplicationName, QString p_qstrVersion)
: CwmsInitApplication(p_qstrApplicationName, p_qstrVersion)
{
    CwmsQmlApplicationController::createController(p_qstrApplicationName, this);
}

CwmsQmlInitApplication::~CwmsQmlInitApplication()
{

}

void CwmsQmlInitApplication::Login()
{
    CwmsQmlApplicationController::getController()->openWindow();
}

void CwmsQmlInitApplication::DbSelection()
{
    // Does nothing will be done by CwmsQmlApplicationController
}

void CwmsQmlInitApplication::ApplicationSelection()
{
    // Does nothing will be done by CwmsQmlApplicationController
}


void CwmsQmlInitApplication::ApplicationStart()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && !m_qstrApplicationName.isEmpty())
    {
        CwmsApplication cApp;

        CdmObject* pCdmObject = CwmsApplication::GetApplication(m_qstrApplicationName);
        cApp.SetObject(pCdmObject);
        CwmsContext::CreateContext(pCdmObject);
        CwmsApplicationServices::InstallFunctionsAndPlugins();
        QString qstrMain = cApp.GetMain();

        if (!qstrMain.isEmpty())
        {
            StartMainFunction(qstrMain);
        }
    }
    else
    {
        ERR("Unknown Application selected!");
    }
}
