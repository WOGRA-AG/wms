#ifndef CWMSARGUMENTPARSER_H
#define CWMSARGUMENTPARSER_H

#include "wmscommons.h"

class WMSCOMMONS_API CwmsArgumentParser
{
public:
    static QMap<QString, QString> parseArgs(int argc, char **argv);
    static QString getArgValue(QMap<QString, QString> &p_rqmArgs, QString p_qstrValue);
};

#endif // CWMSARGUMENTPARSER_H
