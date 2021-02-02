// System and Qt Includes
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

// WMS Includes
#include "CdmLogging.h"

#include "CwmsScriptableSql.h"

CwmsScriptableSql::CwmsScriptableSql()
{

}

CwmsScriptableSql::~CwmsScriptableSql()
{

}

QStringList CwmsScriptableSql::getDriver()
{
    return QSqlDatabase::drivers();
}

bool CwmsScriptableSql::createDbConnection(QString p_qstrName, QString p_qstrDriver, QString p_qstrDbName, QString p_qstrServer, int p_iPort, QString p_qstrLogin, QString p_qstrPassword, QString p_qstrConnectinParams)
{
    bool bSuccess = false;
    if (!QSqlDatabase::contains(p_qstrName))
    {
       QSqlDatabase db = QSqlDatabase::addDatabase(p_qstrDriver, p_qstrName);
       db.setDatabaseName(p_qstrDbName);
       db.setHostName(p_qstrServer);
       db.setUserName(p_qstrLogin);
       db.setPassword(p_qstrPassword);

       if (p_iPort > 0)
       {
          db.setPort(p_iPort);
       }

       db.setConnectOptions(p_qstrConnectinParams);

       if (!db.open())
       {
          ERR("Could not open Database connection " + p_qstrName + ".");
          QString qstrErr = db.lastError().text();
          ERR("DB Error Message: " + qstrErr);
          QSqlDatabase::removeDatabase(p_qstrName);
       }
       else
       {
           bSuccess = true;
       }
    }
    else
    {
        ERR("DB connection with name " + p_qstrName + " already exists.");
    }

    return bSuccess;
}

QVariantList CwmsScriptableSql::executeSql(QString p_qstrName, QString p_qstrSql)
{
    QVariantList qvResult;
    QSqlDatabase db = QSqlDatabase::database(p_qstrName);
    QSqlQuery query(db);

    if (query.exec(p_qstrSql))
    {
        query.first();
        QSqlRecord record = query.record();
        int columns = record.count();

        while (query.isValid())
        {
            QVariantList qvRecordSet;

            for (int pos = 0; pos < columns; ++pos)
            {
                qvRecordSet.append(query.value(pos));
            }

            qvResult.append(qvRecordSet);
            query.next();
        }
    }
    else
    {
        ERR("Error in executing SQL command \"" + p_qstrSql + "\".");
        QString qstrErr = db.lastError().text();
        ERR("DB Error Message: " + qstrErr);
    }

    return qvResult;
}

void CwmsScriptableSql::closeDbConnection(QString p_qstrName)
{
    QSqlDatabase::removeDatabase(p_qstrName);
}
