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

#ifndef CWMSQMLSTYLE_H
#define CWMSQMLSTYLE_H

#include <QObject>

class CwmsQmlStyle : public QObject
{
    Q_OBJECT
public:
    explicit CwmsQmlStyle(QObject *parent = 0);
    ~CwmsQmlStyle();
    static CwmsQmlStyle *createStyle(QObject *p_Parent);

public slots:

    virtual QString getBackgroundColor();
    virtual QString getForegroundColor();
    virtual int getRectangleRadius();
    virtual QString getSeperatorColor();
    virtual QString getButtonColor();
    virtual QString getScrollbarColor();
    virtual QString getNavigationBarColor();
    virtual QString getNavigationBarTextColor();
    virtual int getNavigationBarSize();
    virtual QString getTableviewHeader();
    virtual QString getComboboxArrow();
    virtual QString getSpinboxArrowDown();
    virtual QString getSpinboxArrowUp();
    virtual QString getCheckboxMarker();
    virtual QString getOkButton();
    virtual QString getCancelButton();
    virtual QString getConfigurationButton();
    virtual QString getIconsPath();
    virtual QString getSelectionColor();
    virtual int getToolButtonSize();
    virtual QString getFileSelectionButton();
    virtual QString getErrorTextColor();
    virtual int getContentHeight();
    virtual int getContentWidth();
    virtual double getHeaderScale();
    virtual double getTextScale();
    virtual double getSubtitleScale();
    virtual double getTableviewScale();

};

#endif // CWMSQMLSTYLE_H
