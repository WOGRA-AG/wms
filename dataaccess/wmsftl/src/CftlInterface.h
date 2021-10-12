#ifndef CFTLINTERFACE_H
#define CFTLINTERFACE_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlQuery>

// own Inlcudes
#include "CftlDataAccessConfigurator.h"

class CftlDialect;

class CftlInterface : public QObject
{
    Q_OBJECT

private:
    QString m_qstrDbName;
    QString m_qstrDbId;
    QTimer m_qKeepConnectionAlive;
    int m_iMsecsSum;

    /*
     * The name of the odbc host
     */
    QString m_qstrDbHostName;

    /*
     * The db login name
     */
    QString m_qstrDbUserName;

    /*
     * The db login password
     */
    QString m_qstrDbUserPassword;
    QString m_qstrDbDriver;
    int m_iDbPort;
    QString m_qstrDbConnectionOption;
    QMutex m_qMutex;
    int m_iTransactionCount;
    int m_iQueryCount;
    CftlDialect* m_pDialect;

    void PrintLastErrorFromDb();
    QSqlDatabase RefreshConnection();

public:
    CftlInterface(QString p_qstrDId, QObject *parent = nullptr);
    ~CftlInterface();

    int Init(CftlDataAccessConfigurator &p_pConfig);
   qint64 ExecuteQuery(QString& p_qstrQuery, QSqlQuery &p_rqsqlQuery);
    QString GetConnectionDisplayString();
   qint64 BeginTransaction();
   qint64 Rollback();
   qint64 Commit();
   qint64 ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    QSqlDatabase GetSqlDatabase();
    CftlDialect* GetDialect();

    bool IsTransactionRunning();
private slots:
    void KeepAlive();
};

#endif // CDBINTERFACE_H
