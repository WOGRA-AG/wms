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

#include "CwmsQmlStyleAndroid.h"

CwmsQmlStyleAndroid::CwmsQmlStyleAndroid(QObject *parent) :
    CwmsQmlStyle(parent)
{
}

CwmsQmlStyleAndroid::~CwmsQmlStyleAndroid()
{

}


QString CwmsQmlStyleAndroid::getBackgroundColor()
{
    return "#212126";
}

QString CwmsQmlStyleAndroid::getForegroundColor()
{
    return "white";
}

QString CwmsQmlStyleAndroid::getSeperatorColor()
{
    return "#424246";
}

QString CwmsQmlStyleAndroid::getSelectionColor()
{
    return  "#11ffffff";
}

QString CwmsQmlStyleAndroid::getButtonColor()
{
    return "gray";
}

QString CwmsQmlStyleAndroid::getNavigationBarColor()
{
    return "#c6c8ca";
}

QString CwmsQmlStyleAndroid::getScrollbarColor()
{
    return "#424246";
}
