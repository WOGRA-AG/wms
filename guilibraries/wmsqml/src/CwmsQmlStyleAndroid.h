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

#ifndef CWMSQMLSTYLEANDROID_H
#define CWMSQMLSTYLEANDROID_H

// own Includes
#include "CwmsQmlStyle.h"

class CwmsQmlStyleAndroid : public CwmsQmlStyle
{
    Q_OBJECT
public:
    explicit CwmsQmlStyleAndroid(QObject *parent = 0);

    ~CwmsQmlStyleAndroid();
signals:

public slots:

    virtual QString getBackgroundColor();
    virtual QString getForegroundColor();
    virtual QString getSeperatorColor();
    virtual QString getButtonColor();
    virtual QString getNavigationBarColor();
    virtual QString getSelectionColor();
    virtual QString getScrollbarColor();
};

#endif // CWMSQMLSTYLEANDROID_H
