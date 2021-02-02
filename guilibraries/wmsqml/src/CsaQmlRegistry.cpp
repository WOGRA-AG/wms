/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QtQml>

// own Includes
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CsaValue.h"
#include "CsaQuery.h"
#include "CsaResultObject.h"
#include "CsaManager.h"
#include "CsaContainerManager.h"
#include "CsaClass.h"
#include "CsaClassManager.h"
#include "CsaUser.h"
#include "CsaUserGroup.h"
#include "CsaFactory.h"
#include "CsaMember.h"
#include "CsaQmlRegistry.h"

void CsaQmlRegistry::registerTypes()
{
    registerCreatableTypes();
    registerUncreatableTypes();
}


void CsaQmlRegistry::registerCreatableTypes()
{
    qmlRegisterType<CsaValue>("com.wogra.wmscore", 1, 0, "WmsValue");
}


void CsaQmlRegistry::registerUncreatableTypes()
{
    // These types will be always created by the factory and never by her own.
    qmlRegisterUncreatableType<CsaObject>          ("com.wogra.wmscore", 1, 0, "WmsObject",           "WmsObject will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaObjectContainer> ("com.wogra.wmscore", 1, 0, "WmsObjectContainer",  "WmsObjectContainer will only be created from wmsFactory");
    //qmlRegisterUncreatableType<CsaValue>           ("com.wogra.wmscore", 1, 0, "WmsValue",            "WmsValue will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaQuery>           ("com.wogra.wmscore", 1, 0, "WmsQuery",            "WmsQuery will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaManager>         ("com.wogra.wmscore", 1, 0, "WmsManager",          "WmsManager will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaContainerManager>("com.wogra.wmscore", 1, 0, "WmsContainerManager", "WmsContainerManager will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaClass>           ("com.wogra.wmscore", 1, 0, "WmsClass",            "WmsClass will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaClassManager>    ("com.wogra.wmscore", 1, 0, "WmsClassManager",     "WmsClassManager will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaMember>          ("com.wogra.wmscore", 1, 0, "WmsMember",           "WmsMember will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaUser>            ("com.wogra.wmscore", 1, 0, "WmsUser",             "WmsUser will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaUserGroup>       ("com.wogra.wmscore", 1, 0, "WmsUserGroup",        "WmsUserGroup will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaModelElement>    ("com.wogra.wmscore", 1, 0, "WmsModelElement",     "WmsModelElement will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaLocatedElement>  ("com.wogra.wmscore", 1, 0, "WmsLocatedElement",   "WmsLocatedElement will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaFactory>         ("com.wogra.wmscore", 1, 0, "WmsFactory",          "WmsFactory will only be created from wmsFactory");
    qmlRegisterUncreatableType<CsaResultObject>    ("com.wogra.wmscore", 1, 0, "WmsResultObject",     "WmsResultObjectwill only be created from class functions");
}
