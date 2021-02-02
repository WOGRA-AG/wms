#ifndef CWMSSCRIPTABLESQL_H
#define CWMSSCRIPTABLESQL_H

// System and Qt Includes
#include <QVariant>

// own Includes
#include "basetools.h"
#include "CwmsScriptableBase.h"


class BASETOOLS_API CwmsScriptableSql : public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptableSql();
    virtual ~CwmsScriptableSql();

public slots:
    QStringList getDriver();
    bool createDbConnection(QString p_qstrName,  QString p_qstrDriver, QString p_qstrDbName, QString p_qstrServer, int p_iPort, QString p_qstrLogin, QString p_qstrPassword, QString p_qstrConnectinParams);
    QVariantList executeSql(QString p_qstrName, QString p_qstrSql);
    void closeDbConnection(QString p_qstrName);
};

#endif // CWMSSCRIPTABLESQL_H
