
// System and Qt Includes
#include <qsqldatabase.h>
#include <qsqldriver.h>
#include <QSqlQuery>
#include <QTime>
#include <qsqlerror.h>

#ifdef WIN32
#include <qt_windows.h>
#else
#include <unistd.h>
#endif

// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CdbDataAccessConfigurator.h"
#include "CdbInterface.h"

#define KEEP_ALIVE_INTERVALL_MINUTES 5

CdbInterface::CdbInterface(QString p_qstrDId, QObject* p_pqobjParent) :
    QObject(p_pqobjParent),
    m_qstrDbId(p_qstrDId),
    m_iMsecsSum(0),
    m_qMutex(QMutex::Recursive),
    m_iTransactionCount(0),
    m_iQueryCount(0)
{
    BODY_TRY
    // init and start timer
    connect(&m_qKeepConnectionAlive, SIGNAL(timeout()), this, SLOT(KeepAlive()));
    m_qKeepConnectionAlive.start(KEEP_ALIVE_INTERVALL_MINUTES * 60 * 1000);
    BODY_CATCH
}


CdbInterface::~CdbInterface()
{
    BODY_TRY
    QSqlDatabase::removeDatabase(m_qstrDbName);
    BODY_CATCH
}

int CdbInterface::Init(CdbDataAccessConfigurator& p_pConfig)
{
   int iRet = CdmLogging::eDmUnknownSqlError;

   BODY_TRY
   m_qstrDbHostName = p_pConfig.getServer();
   m_qstrDbUserName = p_pConfig.getUser();
   m_qstrDbUserPassword = p_pConfig.getPassword();
   m_iDbPort = p_pConfig.getPort();
   m_qstrDbConnectionOption = p_pConfig.getConnectOptions();
   m_qstrDbDriver = p_pConfig.getDriver();
   m_qstrDbName = p_pConfig.getDatabase();
   iRet = EC(eDmOk);
   BODY_CATCH

   return iRet;
}

QSqlDatabase CdbInterface::GetSqlDatabase()
{
   QSqlDatabase db;

   BODY_TRY
   if (!QSqlDatabase::contains(m_qstrDbId))
   {
      db = QSqlDatabase::addDatabase(m_qstrDbDriver, m_qstrDbId);
      db.setDatabaseName(m_qstrDbName);
      db.setHostName(m_qstrDbHostName);
      db.setUserName(m_qstrDbUserName);
      db.setPassword(m_qstrDbUserPassword);

      if (m_iDbPort > 0)
      {
         db.setPort(m_iDbPort);
      }

      db.setConnectOptions(m_qstrDbConnectionOption);

      if (!db.open())
      {
         FATAL("Could not open Database connection")
         QString qstrErr = db.lastError().text();
         FATAL("DB Error Message: " + qstrErr)
         QSqlDatabase::removeDatabase(m_qstrDbId);
      }
   }
   else
   {
      db = QSqlDatabase::database(m_qstrDbId);
      if (db.isValid())
      {
          if (db.isOpen())
          {
              INFO("DB is open.")
          }
          else
          {
              INFO("Db is not open")

              if (!db.isOpenError())
              {
                  QSqlDatabase::removeDatabase(m_qstrDbName);
                  db = GetSqlDatabase();
              }
              else
              {
                  db.open();
              }
          }

          if (db.isOpenError())
          {
              ERR("DB isOpenError returned. Error" + db.lastError().text())
          }
      }
      else
      {
          ERR("Db is invalid")
      }
   }
   BODY_CATCH

   return db;
}

void CdbInterface::KeepAlive()
{
    BODY_TRY
    INFO("Keep alive for DB Connection called")
    QMutexLocker locker(&m_qMutex);
    QString qstrQuery = "select 1 from dual";
    QSqlDatabase db = QSqlDatabase::database(m_qstrDbId);
    QSqlQuery query(db);
    INFO("Query count: " + QString::number(++m_iQueryCount))
    query.exec(qstrQuery);
    BODY_CATCH
}

QSqlDatabase CdbInterface::RefreshConnection()
{
    QMutexLocker locker(&m_qMutex);
    QSqlDatabase db;

    if (QSqlDatabase::contains(m_qstrDbId))
    {
        db = QSqlDatabase::database(m_qstrDbId);
        db.close();

        db = QSqlDatabase::addDatabase(m_qstrDbDriver, m_qstrDbId);
        db.setDatabaseName(m_qstrDbName);
        db.setHostName(m_qstrDbHostName);
        db.setUserName(m_qstrDbUserName);
        db.setPassword(m_qstrDbUserPassword);

        if (m_iDbPort > 0)
        {
            db.setPort(m_iDbPort);
        }

        db.setConnectOptions(m_qstrDbConnectionOption);

        if (!db.open())
        {
            FATAL("Could not open Database connection")
            QString qstrErr = db.lastError().text();
            FATAL("DB Error Message: " + qstrErr)
        }
    }

    return db;
}

void CdbInterface::PrintLastErrorFromDb()
{
   BODY_TRY
   QSqlDatabase db = GetSqlDatabase();
   QString qstrText = db.lastError().databaseText();
   ERR("Database Error: " + qstrText)
   BODY_CATCH
}

qint64 CdbInterface::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
   qint64 lRet = CdmLogging::eDmUnknownSqlError;
    QMutexLocker locker(&m_qMutex);

    if (!p_rqsqlQuery.exec())
    {
       INFO("Query count: " + QString::number(++m_iQueryCount))
       QSqlError qError = p_rqsqlQuery.lastError();

       if (qError.isValid())
       {
           if (QSqlError::ConnectionError == qError.type())
           {
               ERR("Connection error. System refreshes the connection and tries it again.")
               QSqlDatabase db = RefreshConnection();
               p_rqsqlQuery = QSqlQuery(db);

               if (!p_rqsqlQuery.exec())
               {
                   qError = p_rqsqlQuery.lastError();
                   ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery())
                   lRet = EC(eDmSqlError);
               }
               else
               {
                  lRet = EC(eDmOk);
               }
           }
           else
           {
               QString qstrText = qError.text();
               ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery() + "Error Text: "+ qstrText)
               lRet = EC(eDmSqlError);
           }
       }
       else
       {
           ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery())
           lRet = EC(eDmSqlError);
       }
    }
    else
    {

       INFO("SQL Command finished")
       lRet = EC(eDmOk);
    }

    return lRet;
}

qint64 CdbInterface::ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
    // #define LOG_SLOW_QUERIES
  qint64 lRet = CdmLogging::eDmUnknownSqlError;

   QMutexLocker locker(&m_qMutex);
#ifdef LOG_SLOW_QUERIES
   QTime qtStart;
#endif
   QSqlDatabase db = GetSqlDatabase();

   if (db.isOpen())
   {
      p_qstrQuery = p_qstrQuery.replace("% ", "%"); // is needed for masking % in search or in string because of QString::arg Problem
      INFO(p_qstrQuery)
      p_rqsqlQuery = QSqlQuery(db);
      INFO("QSqlQuery created!")

#ifdef LOG_SLOW_QUERIES
      qtStart = QTime::currentTime();
#endif

      if (!p_rqsqlQuery.exec(p_qstrQuery))
      {
         INFO("Query count: " + QString::number(++m_iQueryCount))
         QSqlError qError = p_rqsqlQuery.lastError();

         if (qError.isValid())
         {
             if (QSqlError::ConnectionError == qError.type())
             {
                 ERR("Connection error. System refreshes the connection and tries it again.")
                 QSqlDatabase db = RefreshConnection();
                 p_rqsqlQuery = QSqlQuery(db);

                 if (!p_rqsqlQuery.exec(p_qstrQuery))
                 {
                     qError = p_rqsqlQuery.lastError();
                     ERR("Error while executing query\nQuery: " + p_qstrQuery)
                     lRet = EC(eDmSqlError);
                 }
                 else
                 {
                     lRet = EC(eDmOk);
                 }
             }
             else
             {
                 QString qstrText = qError.text();
                 ERR("Error while executing query\nQuery: " + p_qstrQuery + "\nError Text: "+ qstrText)
                 lRet = EC(eDmSqlError);
             }
         }
         else
         {
             ERR("Error while executing query\nQuery: " + p_qstrQuery)
             lRet = EC(eDmSqlError);
         }
      }
      else
      {

         INFO("SQL Command finished")
         lRet = EC(eDmOk);
      }
   }
   else
   {
       FATAL("DB connection not established. Execution of Query failed")
   }

#ifdef LOG_SLOW_QUERIES
   QTime qtEnd = QTime::currentTime();

   int msecs = qtStart.msecsTo(qtEnd);
   m_iMsecsSum += msecs;
   int iBound = 50000;

   if (msecs > iBound)
   {
      QString qstrMessage = "SLOW SQL Command took " + QString::number(msecs) + " ms. Sum of DB time: " + QString::number(m_iMsecsSum) + QString(" ms");
      qstrMessage += "\nQuery:\n";
      qstrMessage += p_qstrQuery;
      qstrMessage += QStringLiteral("\n");

      if (msecs > (2 * iBound))
      {
          ERR(qstrMessage)
      }
      else
      {
          WARNING(qstrMessage)
      }
   }
   else
   {
      INFO("SQL Command took " + QString::number(msecs) + ".")
   }
#endif

   return lRet;
}

QString CdbInterface::GetConnectionDisplayString()
{
   return "DB Host: " + m_qstrDbHostName + " User: " + m_qstrDbUserName + " Password: " + m_qstrDbUserPassword;
}

qint64 CdbInterface::BeginTransaction()
{
    QMutexLocker locker(&m_qMutex);
   qint64 lRet = CdmLogging::eDmOk;
    INFO("Beginn Transaction")

    if (m_iTransactionCount == 0)
    {
        QSqlDatabase db = GetSqlDatabase();
        QSqlDriver* pqDriver = db.driver();

        if(pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
        {
            db.transaction();
        }

        INFO("Start Transaction")
    }

    INFO("Transaction count: " + QString::number(++m_iTransactionCount))
    return lRet;
}

qint64 CdbInterface::Rollback()
{
    QMutexLocker locker(&m_qMutex);
   qint64 lRet = CdmLogging::eDmOk;
    INFO("Transaction count: " + QString::number(--m_iTransactionCount))
    INFO("In Rollback")

    if (m_iTransactionCount == 0)
    {
        QSqlDatabase db = GetSqlDatabase();
        QSqlDriver* pqDriver = db.driver();

        if (pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
        {
            db.rollback();

            INFO("Rollback successfull.")
        }
        else
        {
            INFO("No Rollback feature in DB")
        }
    }
    else
    {
        INFO("Transaction not finally finished Transaction depth: " + QString::number(m_iTransactionCount))
    }

    return lRet;
}

qint64 CdbInterface::Commit()
{
    QMutexLocker locker(&m_qMutex);
    INFO("Commiting changes")
   qint64 lRet = CdmLogging::eDmOk;
    INFO("Transaction count: " + QString::number(--m_iTransactionCount))

    if (m_iTransactionCount == 0)
    {
        QSqlDatabase db = GetSqlDatabase();
        QSqlDriver* pqDriver = db.driver();

        if(pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
        {
            db.commit();
            INFO("changes commited")
        }
        else
        {
            INFO("No commit feature in DB.")
        }
    }
    else
    {
        INFO("Transaction not finally finished Transaction depth: " + QString::number(m_iTransactionCount))
    }

    return lRet;
}

bool CdbInterface::IsTransactionRunning()
{
    return (m_iTransactionCount > 0);
}
