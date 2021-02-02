#include <QCoreApplication>

#include "CwmsRestApiTestMultiThreaded.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CwmsRestApiTestMultiThreaded test;
    test.RunTest();

    return 0;
}
