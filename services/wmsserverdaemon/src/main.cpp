/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: main.cpp
 ** Started Implementation: 2012/04/02
 ** Description:
 **
 ** IMplements the main routine for starting the webserver.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QDebug>
#include <QCoreApplication>

// QT Service Includes
#include "qtservice.h"

// own Includes
#include "CwsServiceDeamon.h"



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    CwsServiceDaemon serviceApp(argc, argv);
    return serviceApp.exec();
}
