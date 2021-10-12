
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

#include "CwmsTimeMeassurement.h"

// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CftlDialect.h"
#include "CftlInterface.h"

#define KEEP_ALIVE_INTERVALL_MINUTES 5

CftlInterface::CftlInterface(QString p_qstrDId, QObject *parent) :
    QObject(parent),
    m_qstrDbId(p_qstrDId),
    m_qMutex(QMutex::Recursive),
    m_iTransactionCount(0),
    m_iQueryCount(0),
    m_pDialect(nullptr)
{
    // init and start timer
    connect(&m_qKeepConnectionAlive, SIGNAL(timeout()), this, SLOT(KeepAlive()));
    m_qKeepConnectionAlive.start(KEEP_ALIVE_INTERVALL_MINUTES * 60 * 1000);
}


CftlInterface::~CftlInterface()
{
    QSqlDatabase::removeDatabase(m_qstrDbName);
    DELPTR(m_pDialect)
}

int CftlInterface::Init(CftlDataAccessConfigurator& p_pConfig)
{
   int iRet = CdmLogging::eDmUnknownSqlError;
   m_qstrDbHostName = p_pConfig.getServer();
   m_qstrDbUserName = p_pConfig.getUser();
   m_qstrDbUserPassword = p_pConfig.getPassword();
   m_iDbPort = p_pConfig.getPort();
   m_qstrDbConnectionOption = p_pConfig.getConnectOptions();
   m_qstrDbDriver = p_pConfig.getDriver();
   m_qstrDbName = p_pConfig.getDatabase();
   iRet = EC(eDmOk);

   m_pDialect = new CftlDialect();
   m_pDialect->Init(p_pConfig.getDialect());

   return iRet;
}

QSqlDatabase CftlInterface::GetSqlDatabase()
{
   QSqlDatabase db;

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
         FATAL("Could not open Database connection");
         QString qstrErr = db.lastError().text();
         FATAL("DB Error Message: " + qstrErr);
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
              INFO("DB is open.");
          }
          else
          {
              INFO("Db is not open");

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
              ERR("DB isOpenError returned. Error" + db.lastError().text());
          }
      }
      else
      {
          ERR("Db is invalid");
      }
   }

   return db;
}

CftlDialect *CftlInterface::GetDialect()
{
    return m_pDialect;
}

void CftlInterface::KeepAlive()
{
    INFO("Keep alive for DB Connection called")
    QMutexLocker locker(&m_qMutex);
    QString qstrQuery = "select 1 from dual";
    QSqlDatabase db = QSqlDatabase::database(m_qstrDbId);
    QSqlQuery query(db);
    INFO("Query count: " + QString::number(++m_iQueryCount));
    query.exec(qstrQuery);
}


QSqlDatabase CftlInterface::RefreshConnection()
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
            FATAL("Could not open Database connection");
            QString qstrErr = db.lastError().text();
            FATAL("DB Error Message: " + qstrErr);
        }
    }

    return db;
}

void CftlInterface::PrintLastErrorFromDb()
{
   QSqlDatabase db = GetSqlDatabase();
   QString qstrText = db.lastError().databaseText();
   ERR("Database Error: " + qstrText);
}

qint64 CftlInterface::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
   qint64 lRet = CdmLogging::eDmUnknownSqlError;
    QMutexLocker locker(&m_qMutex);

    if(!p_rqsqlQuery.exec())
    {
       QSqlError qError = p_rqsqlQuery.lastError();

       if (qError.isValid())
       {
           if (QSqlError::ConnectionError == qError.type())
           {
               ERR("Connection error. System refreshes the connection and tries it again.");
               QSqlDatabase db = RefreshConnection();
               p_rqsqlQuery = QSqlQuery(db);

               if(!p_rqsqlQuery.exec())
               {
                   qError = p_rqsqlQuery.lastError();
                   ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery());
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
               ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery() + "Error Text: "+ qstrText);
               lRet = EC(eDmSqlError);
           }
       }
       else
       {
           ERR("Error while executing query\nQuery: " + p_rqsqlQuery.executedQuery());
           lRet = EC(eDmSqlError);
       }
    }
    else
    {
       lRet = EC(eDmOk);
    }

    return lRet;
}

qint64 CftlInterface::ExecuteQuery(QString& p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
  qint64 lRet = CdmLogging::eDmUnknownSqlError;
   CwmsTimeMeassurement cTime(false, "ExecuteQuery");
   QMutexLocker locker(&m_qMutex);
   cTime.finishedTask("Mutex access granted");
   QSqlDatabase db = GetSqlDatabase();


   if (db.isOpen())
   {
      cTime.finishedTask("DB access granted");
      p_qstrQuery = p_qstrQuery.replace("% ", "%"); // is needed for masking % in search or in string because of QString::arg Problem
      p_rqsqlQuery = QSqlQuery(db);


      if(!p_rqsqlQuery.exec(p_qstrQuery))
      {
         QSqlError qError = db.lastError();

         if (qError.isValid())
         {
             if (QSqlError::ConnectionError == qError.type() || QSqlError::StatementError == qError.type())
             {
                 ERR("Connection error. System refreshes the connection and tries it again.");
                 QSqlDatabase db = RefreshConnection();
                 p_rqsqlQuery = QSqlQuery(db);

                 if(!p_rqsqlQuery.exec(p_qstrQuery))
                 {
                     qError = db.lastError();
                     QString qstrText = qError.text();
                     ERR("Error while executing query\nQuery: " + p_qstrQuery + "Error Text: " + qstrText);
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
                 ERR("Error while executing query\nQuery: " + p_qstrQuery + "Error Text: " + qstrText);
                 lRet = EC(eDmSqlError);
             }
         }
         else
         {
             ERR("Error while executing query\nQuery: " + p_qstrQuery);
             lRet = EC(eDmSqlError);
         }
      }
      else
      {
         lRet = EC(eDmOk);
      }

      cTime.finishedTask("ExecuteQuery: " + p_qstrQuery);
   }
   else
   {
       FATAL("DB connection not established. Execution of Query failed");
   }

   m_iMsecsSum += cTime.GetCompleteDuration();

   if (cTime.GetCompleteDuration() > 500)
   {
      QString qstrMessage = "SLOW SQL Command took " + QString::number(cTime.GetCompleteDuration()) + ". Sum of DB time: " + QString::number(m_iMsecsSum);
      qstrMessage += "\nQuery:\n";
      qstrMessage += p_qstrQuery + "\n";
      qstrMessage += cTime.getTimeRecorderResult();
      WARNING(qstrMessage);
   }

   return lRet;
}

QString CftlInterface::GetConnectionDisplayString()
{
   return "DB Host: " + m_qstrDbHostName + " User: " + m_qstrDbUserName + " Password: " + m_qstrDbUserPassword;
}

qint64 CftlInterface::BeginTransaction()
{
    QMutexLocker locker(&m_qMutex);
  qint64 lRet = CdmLogging::eDmOk;
   INFO("Beginn Transaction");

   if(m_iTransactionCount == 0)
   {
      QSqlDatabase db = GetSqlDatabase();
      QSqlDriver* pqDriver = db.driver();

      if(pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
      {
         db.transaction();
      }

      INFO("Start Transaction");
   }

   INFO("Transaction count: " + QString::number(++m_iTransactionCount));
   return lRet;
}

qint64 CftlInterface::Rollback()
{
    QMutexLocker locker(&m_qMutex);
  qint64 lRet = CdmLogging::eDmOk;
   INFO("Transaction count: " + QString::number(--m_iTransactionCount));
   INFO("In Rollback");

   if (m_iTransactionCount == 0)
   {
      QSqlDatabase db = GetSqlDatabase();
      QSqlDriver* pqDriver = db.driver();

      if(pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
      {
         db.rollback();

         INFO("Rollback successfull.");
      }
      else
      {
          INFO("No Rollback feature in DB")
      }
   }
   else
   {
      INFO("Transaction not finally finished Transaction depth: " + QString::number(m_iTransactionCount));
   }

   return lRet;
}

qint64 CftlInterface::Commit()
{
    QMutexLocker locker(&m_qMutex);
    INFO("Commiting changes");
  qint64 lRet = CdmLogging::eDmOk;
   INFO("Transaction count: " + QString::number(--m_iTransactionCount));

   if (m_iTransactionCount == 0)
   {
      QSqlDatabase db = GetSqlDatabase();
      QSqlDriver* pqDriver = db.driver();

      if(pqDriver && pqDriver->hasFeature(QSqlDriver::Transactions))
      {
         db.commit();
         INFO("changes commited");
      }
      else
      {
          INFO("No commit feature in DB.")
      }
   }
   else
   {
      INFO("Transaction not finally finished Transaction depth: " + QString::number(m_iTransactionCount));
   }

   return lRet;
}

bool CftlInterface::IsTransactionRunning()
{
    return (m_iTransactionCount > 0);
}
