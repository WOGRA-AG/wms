#ifndef CDBINTERFACE_H
#define CDBINTERFACE_H

// includes
#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QSqlDatabase>

// forwards
class CdbDataAccessConfigurator;
class QSqlQuery;

class CdbInterface : public QObject
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

    void PrintLastErrorFromDb();
    QSqlDatabase RefreshConnection();

public:
    CdbInterface(QString p_qstrDId, QObject* p_pqobjParent = nullptr);
    ~CdbInterface();

    int Init(CdbDataAccessConfigurator &p_pConfig);
    long ExecuteQuery(QString p_qstrQuery, QSqlQuery &p_rqsqlQuery);
    QString GetConnectionDisplayString();
    long BeginTransaction();
    long Rollback();
    long Commit();
    long ExecuteQuery(QSqlQuery &p_rqsqlQuery);
    QSqlDatabase GetSqlDatabase();
    bool IsTransactionRunning();

private slots:
    void KeepAlive();
};

#endif // CDBINTERFACE_H
