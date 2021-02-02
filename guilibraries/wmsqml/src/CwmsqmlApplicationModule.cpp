// System and Qt Includes
#include <QtQml>

// WMS Includes
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"

// Own Includes
#include "CwmsQmlApplicationController.h"
#include "CwmsqmlApplicationModule.h"

CwmsQmlApplicationModule::CwmsQmlApplicationModule()
{
}

CwmsQmlApplicationModule::~CwmsQmlApplicationModule()
{
}

void CwmsQmlApplicationModule::setObject(CsaObject *p_pObject)
{
    if (p_pObject)
    {
        m_Module.SetObject(p_pObject->getInternals());
    }
    else
    {

        m_Module.SetObject(nullptr);
    }
}

CsaObject *CwmsQmlApplicationModule::getUserInterface()
{
    return CwmsQmlApplicationController::getController()->convertObject(m_Module.GetUserInterface());
}

CsaObject *CwmsQmlApplicationModule::getObjectModule()
{
    return CwmsQmlApplicationController::getController()->convertObject(m_Module.GetObjectModule());
}

CsaObjectContainer *CwmsQmlApplicationModule::getContainerModule()
{
    return CwmsQmlApplicationController::getController()->convertContainer(m_Module.GetContainerModule());
}

QString CwmsQmlApplicationModule::getName()
{
    return m_Module.GetName();
}

long CwmsQmlApplicationModule::getId()
{
    return m_Module.GetObjectId();
}


void CwmsQmlApplicationModule::registerToQml()
{
    qmlRegisterType<CwmsQmlApplicationModule>("com.wogra.wmsqml", 1, 0, "WmsApplicationModule");
}
