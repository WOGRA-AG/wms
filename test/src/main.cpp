#include <QtTest>
#include <QObject>
#include <QDateTime>
#include <qdir.h>

#include <QtTest>
#include <QObject>
#include <QDateTime>

#include "CdmLogging.h"

#include "CwmsLoggerConsole.h"

#include "CwtClass.h"
#include "CwtMassTest.h"
#include "CwtUser.h"
#include "CwtQuery.h"
#include "CwtObject.h"
#include "CwtObjectContainer.h"
#include "CwtMassLoginLogout.h"
#include "CwtScheme.h"
#include "CwtServiceTest.h"

#define IGNORE_CONTAINERMANAGERSYNC_TESTS true
#define IGNORE_LOGINLOGOUT_TESTS true
#define IGNORE_USER_TESTS true
#define IGNORE_SCHEME_TESTS true
#define IGNORE_CLASS_TESTS true
#define IGNORE_CONTAINER_TESTS true
#define IGNORE_OBJECT_TEST true
#define IGNORE_QUERY_TEST true
#define IGNORE_SERVICE_TEST false


int runTest(QObject *test, QStringList arguments);
QStringList getArgumentsWithTestName(QStringList arguments, QObject* testClass);
QStringList cleanArguments(int argc, char** argv);

int main(int argc, char *argv[])
{
    qInstallMessageHandler(wmsQtMessageHandler);
    QApplication app(argc, argv); 
    app.setAttribute(Qt::AA_Use96Dpi, true); 
    QTEST_DISABLE_KEYPAD_NAVIGATION 
    INITERRORMANAGER();
    CdmLogging::SetLoggingMode(eDmError | eDmFatal);
    CdmLogging::AddAdaptor(new CwmsLoggerConsole(app.applicationName(), app.applicationVersion()));

    //CwtMassTest cMassTest;
    CwtLoginLogout cLoginLogout;
    CwtScheme cScheme;
    CwtUser cUser;
    CwtClass cClass;
    CwtObjectContainer cContainer;
    CwtObject cObject;
    CwtQuery cQuery;
    CwtServiceTest cServiceTest;
    int iRet = 0;

    QStringList cleanedArguments = cleanArguments(argc, argv);

    if (!IGNORE_LOGINLOGOUT_TESTS)
    {
        iRet = iRet | runTest(&cLoginLogout, cleanedArguments);
    }

    if (!IGNORE_USER_TESTS)
    {
        iRet = iRet | runTest(&cUser, cleanedArguments);
    }

    if (!IGNORE_SCHEME_TESTS)
    {
        iRet = iRet | runTest(&cScheme, cleanedArguments);
    }

    if (!IGNORE_CLASS_TESTS)
    {
        iRet = iRet | runTest(&cClass, cleanedArguments);
    }

    if (!IGNORE_CONTAINER_TESTS)
    {
        iRet = iRet | runTest(&cContainer, cleanedArguments);
    }

    if (!IGNORE_OBJECT_TEST)
    {
        iRet = iRet | runTest(&cObject, cleanedArguments);
    }

    if (!IGNORE_QUERY_TEST)
    {
        iRet = iRet | runTest(&cQuery, cleanedArguments);
    }

    if (!IGNORE_SERVICE_TEST)
    {
        iRet = iRet | runTest(&cServiceTest, cleanedArguments);
    }

    return iRet;
}

int runTest(QObject *test, QStringList arguments)
{
    QStringList targs = getArgumentsWithTestName(arguments, test);
    return QTest::qExec(test, targs);
}

QStringList getArgumentsWithTestName(QStringList arguments, QObject* testClass)
{
    QStringList newArgs = QStringList(arguments);

    if(newArgs.contains("-xml"))
    {
        newArgs.removeAll("-xml");

        newArgs.append("-o");
        newArgs.append(QString("xml-result-%1.xml,xml").arg(testClass->metaObject()->className()));
        newArgs.append("-o"); // also output to stdout in text format
        newArgs.append("-,txt");
    }

    return newArgs;
}

QStringList cleanArguments(int argc, char** argv)
{
    QStringList cleanArgs;

    for(int i = 0; i < argc; i++)
    {
        QString arg(argv[i]);
        QString prev = (i > 0) ? QString(argv[i-1]) : QString();

        if(prev == "-o"  || arg == "-o")
        {
            // don't add argument to clean arguments
        }
        else
        {
            // append to new cmd line
            cleanArgs.append(arg);
        }
    }
    return cleanArgs;
}
