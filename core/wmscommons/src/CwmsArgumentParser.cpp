// System and Qt Includes
#include <QMap>
#include <QString>
#include <QStringList>

#include "CwmsArgumentParser.h"

QMap<QString,QString> CwmsArgumentParser::parseArgs(int argc, char **argv)
{
    QMap<QString,QString> qmValues;

    for (int counter = 1; counter < argc; ++counter)
    {
        QString qstrArg = argv[counter];

        if (qstrArg.contains("=")) {
            QStringList qstrlArgs = qstrArg.split("=");
            QString qstrKey = qstrlArgs[0].remove("-");
            QString qstrValue = qstrlArgs[1].remove("\"");
            qmValues.insert(qstrKey, qstrValue);
        }
    }

    return qmValues;
}

QString CwmsArgumentParser::getArgValue(QMap<QString,QString>& p_rqmArgs, QString p_qstrValue)
{
    QString qstrRet;

    if (p_rqmArgs.contains(p_qstrValue))
    {
        qstrRet = p_rqmArgs[p_qstrValue];
    }

    return qstrRet;
}
