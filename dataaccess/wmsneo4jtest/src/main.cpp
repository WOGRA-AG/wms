#include <QtTest>
#include <QObject>
#include <QDateTime>
#include <qdir.h>

#include <QtTest>
#include <QObject>
#include <QDateTime>

#include "CdmLogging.h"

#include "Cwmsneo4jtestCwnQuery.h"
#include "CwnNeo4jFahrtenbuch.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(wmsQtMessageHandler);
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_Use96Dpi, true);
    QTEST_DISABLE_KEYPAD_NAVIGATION 
    INITERRORMANAGER();
    SETSEVERITY(eDmError);

    CwnNeo4jFahrtenBuch fahrtenbuch;
    int iRet=0;
    iRet = iRet | QTest::qExec(&fahrtenbuch, argc, argv);
    return iRet;

    //Cwmsneo4jtestCwnQuery queryTests;
    //int iRet = 0;
    //iRet = iRet | QTest::qExec(&queryTests, argc, argv);
    //return iRet;
}

