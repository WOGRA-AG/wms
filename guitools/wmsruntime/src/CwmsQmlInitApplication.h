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

#ifndef CWMSQMLINITAPPLICATION_H
#define CWMSQMLINITAPPLICATION_H


// Basetools Includes
#include "CwmsInitApplication.h"


class CwmsQmlInitApplication : public CwmsInitApplication
{

public:
    CwmsQmlInitApplication(QString p_qstrApplicationName, QString p_qstrVersion);
    virtual ~CwmsQmlInitApplication();

    virtual void Login();
    virtual void DbSelection();
    virtual void ApplicationSelection();
    virtual void ApplicationStart();
};

#endif // CWMSQMLINITAPPLICATION_H
