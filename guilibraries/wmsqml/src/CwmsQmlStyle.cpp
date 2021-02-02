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

// System and Qt Includes

// Basetools includes
#include "cwmsbtplattforminformation.h"

// own Includes
#include "CwmsQmlStyleAndroid.h"
#include "CwmsQmlStyleIOS.h"
#include "CwmsQmlStyle.h"

CwmsQmlStyle::CwmsQmlStyle(QObject *parent) :
    QObject(parent)
{
}

CwmsQmlStyle::~CwmsQmlStyle()
{

}


QString CwmsQmlStyle::getBackgroundColor()
{
    return "white";
}

QString CwmsQmlStyle::getForegroundColor()
{
    return "black";
}

QString CwmsQmlStyle::getSeperatorColor()
{
    return "white";
}

QString CwmsQmlStyle::getButtonColor()
{
    return "gray";
}

QString CwmsQmlStyle::getScrollbarColor()
{
    return "gray";
}

QString CwmsQmlStyle::getSelectionColor()
{
    return "silver";
}

QString CwmsQmlStyle::getErrorTextColor()
{
    return "red";
}

QString CwmsQmlStyle::getNavigationBarColor()
{
    return "gray";
}

QString CwmsQmlStyle::getNavigationBarTextColor()
{
    return "white";
}

int CwmsQmlStyle::getContentHeight()
{
    return 400;
}

int CwmsQmlStyle::getContentWidth()
{
    return 360;
}

double CwmsQmlStyle::getHeaderScale(){
    return 0.06;
}

double CwmsQmlStyle::getTextScale(){
    return 0.04;
}

double CwmsQmlStyle::getSubtitleScale(){
    return 0.025;
}

double CwmsQmlStyle::getTableviewScale(){
    return 0.012;
}

int CwmsQmlStyle::getNavigationBarSize()
{
    return getToolButtonSize() + 8;
}

int CwmsQmlStyle::getToolButtonSize()
{
    return 32;
}

int CwmsQmlStyle::getRectangleRadius()
{
    return 0;
}

QString CwmsQmlStyle::getTableviewHeader()
{
    return getIconsPath() + "header.png";
}

QString CwmsQmlStyle::getComboboxArrow()
{
    return getIconsPath() + "spinBoxArrowDown.svg";
}

QString CwmsQmlStyle::getSpinboxArrowDown()
{
    return getIconsPath() + "spinBoxArrowDown.svg";
}

QString CwmsQmlStyle::getSpinboxArrowUp()
{
    return getIconsPath() + "spinBoxArrowUp.svg";
}

QString CwmsQmlStyle::getCheckboxMarker()
{
    return getIconsPath() + "checkmark.svg";
}

QString CwmsQmlStyle::getFileSelectionButton()
{
    return getIconsPath() + "ok32.png";
}

QString CwmsQmlStyle::getOkButton()
{
    return getIconsPath() + "ok32.png";
}

QString CwmsQmlStyle::getCancelButton()
{
    return getIconsPath() + "cancel32.png";
}

QString CwmsQmlStyle::getConfigurationButton()
{
    return getIconsPath() + "clientsettings32.png";
}

QString CwmsQmlStyle::getIconsPath()
{
    return "../icons/";
}

CwmsQmlStyle* CwmsQmlStyle::createStyle(QObject* p_Parent)
{
    CwmsbtPlattformInformation cInfo;
    CwmsQmlStyle* pStyle = nullptr;

    if (cInfo.isDesktop())
    {
        // TODO change to a desktop specific style
        pStyle = new CwmsQmlStyleAndroid(p_Parent);
    }
    else if (cInfo.isAndroid())
    {
        pStyle = new CwmsQmlStyleAndroid(p_Parent);
    }
    else if (cInfo.isIOS())
    {
        pStyle = new CwmsQmlStyleIOS(p_Parent);
    }

    // ToDo further frontend systems

    return pStyle;
}
