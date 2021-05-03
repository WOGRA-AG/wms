/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <qsqldatabase.h>
#include <qsqldriver.h>
#include <QSqlQuery>
#include <QTime>
#include <qsqlerror.h>
#include <qdatetime.h>
#include <qfile.h>
#include <QVariant>
#include <QThread>
#include <qtextstream.h>
#include <QList>

#ifdef WIN32
#include <qt_windows.h>
#else
#include <unistd.h>
#endif //

#include "CwmsTimeMeassurement.h"

// WMS CORE Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmModelElement.h"
#include "CdmDataProvider.h"
#include "CdmSettings.h"
#include "CdmJournalItem.h"
#include "CdmSessionManager.h"

// own Includes
#include "CftlDbAccess.h"
#include "CftlUserManager.h"
#include "CftlLoginManager.h"
#include "CftlClassAccess.h"
#include "CftlObjectAccess.h"
#include "CftlInterface.h"
#include "CftlJournal.h"
#include "CftlDataAccess.h"

#define KEEP_ALIVE_INTERVALL_MINUTES 5



CftlDataAccess::CftlDataAccess(  )
    : QObject(nullptr),
      m_pCftlUserManager(nullptr),
      m_pCftlLoginManager(nullptr),
      m_pCftlDbAccess(nullptr),
      m_pCftlObjectAccess(nullptr),
      m_pCftlClassAccess(nullptr),
      m_pCftlJournal(nullptr),
      m_iInterfaceCallCounter(0),
      m_bServerMode(false)
{
}

CftlDataAccess::~CftlDataAccess(  )
{
    DELPTR(m_pCftlDbAccess);
    DELPTR(m_pCftlUserManager);
    DELPTR(m_pCftlLoginManager);
    DELPTR(m_pCftlObjectAccess);
    DELPTR(m_pCftlClassAccess);
    DELPTR(m_pCftlJournal);
}

int CftlDataAccess::Init(CftlDataAccessConfigurator* p_pConfig)
{
    int iRet = CdmLogging::eDmUnknownSqlError;
    m_rpConfig = p_pConfig;
    m_pCftlDbAccess     = new CftlSchemeAccess(this);
    m_pCftlUserManager  = new CftlUserManager(this);
    m_pCftlLoginManager = new CftlLoginManager(this, m_pCftlUserManager);
    m_pCftlObjectAccess = new CftlObjectAccess(this);
    m_pCftlClassAccess  = new CftlClassAccess(this);
    m_pCftlJournal = new CftlJournal(this);
    iRet = EC(eDmOk);
    return iRet;
}


void CftlDataAccess::KeepAlive()
{
    QString qstrQuery = "select 1 from dual";
    QStringList qstrlOpenConnections = QSqlDatabase::connectionNames();

    for (int iPos = 0; iPos < qstrlOpenConnections.count(); ++iPos)
    {
        QSqlDatabase db = QSqlDatabase::database(qstrlOpenConnections[iPos]);
        QSqlQuery query(db);
        query.exec(qstrQuery);
    }
}

int CftlDataAccess::GetInterfaceCallCounter() const
{
    return m_iInterfaceCallCounter;
}

void CftlDataAccess::SetServerMode(bool p_bServerMode)
{
    m_bServerMode = p_bServerMode;
}

bool CftlDataAccess::IsInServerMode() const
{
    return m_bServerMode;
}


CftlJournal* CftlDataAccess::GetJournal()
{
    return m_pCftlJournal;
}

long CftlDataAccess::ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CftlInterface* pInterface = GetFtlInterface();

    if (CHKPTR(pInterface))
    {
        lRet = pInterface->ExecuteQuery(p_qstrQuery, p_rqsqlQuery);
    }
    else
    {
        FATAL("DB connection not established. Execution of Query failed");
    }


    return lRet;
}

CftlInterface* CftlDataAccess::GetFtlInterface()
{
    CftlInterface* pInterface = nullptr;
    QThread* pThread = QThread::currentThread();

    if (pThread != nullptr)
    {
        qint64 lThreadPtr = (qint64)pThread;
        QMutexLocker locker(&m_qMutex);

        if (m_qmConnections.contains(lThreadPtr))
        {
            pInterface = m_qmConnections[lThreadPtr];
        }
        else
        {
            if (CHKPTR(m_rpConfig))
            {
                QString qstrThreadId = QString::number(lThreadPtr);
                INFO("Create new FtlInterface for Thread.");
                pInterface = new CftlInterface(qstrThreadId);
                pInterface->Init(*m_rpConfig);
                m_qmConnections.insert(lThreadPtr, pInterface);
            }
        }
    }

    return pInterface;
}

long CftlDataAccess::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
    long lRet = CdmLogging::eDmUnknownSqlError;

    QTime qtStart = QTime::currentTime();
    QTime qtEnd;
    CftlInterface* pInterface = GetFtlInterface();

    if (CHKPTR(pInterface))
    {
        lRet = pInterface->ExecuteQuery(p_rqsqlQuery);
    }
    else
    {
        FATAL("DB connection not established. Execution of Query failed");
    }

    qtEnd = QTime::currentTime();

    int msecs = qtStart.msecsTo(qtEnd);

    if (msecs > 500)
    {
        QString qstrMessage = "SLOW SQL Command took " + QString::number(msecs) + ".";
        qstrMessage += "\nQuery:\n";
        qstrMessage += p_rqsqlQuery.executedQuery();
        WARNING(qstrMessage);
    }

    return lRet;
}

int CftlDataAccess::LoadObjects(QList<long>& p_rqvlObjects, CdmObjectContainer*& p_pCdmObject)
{
    INFO("Data Access Call LoadObjects()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadObjects(p_pCdmObject, p_rqvlObjects);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjects() Finished");
    return lRet;
}


long CftlDataAccess::IsObjectUsed(const CdmObject* p_pObject)
{
    INFO("Data Access Call IsObjectUsed()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->IsObjectUsed(p_pObject);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call IsObjectUsed() Finished");
    return lRet;
}

int CftlDataAccess::LoadObject(const CdmObjectContainer* p_pContainer, long p_lObjectId, CdmObject*& p_pCdmObject)
{
    INFO("Data Access Call LoadObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadObject(p_pContainer, p_lObjectId, p_pCdmObject);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObject() Finished");
    return lRet;
}

int CftlDataAccess::LoadObjectContainer(long p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadObjectList(p_lObjectListId, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObject() finished");
    return lRet;
}

int CftlDataAccess::LoadObjectContainer(long p_lDatabaseId,
                                        QString p_qstrKeyname,
                                        CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadObjectList(p_lDatabaseId, p_qstrKeyname, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CftlDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadEmptyObjectList(p_lDataBaseId, p_qstrKeyname, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CftlDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId, long p_lId, CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadEmptyObjectList(p_lDataBaseId, p_lId, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CftlDataAccess::GetNewContainerId(long p_lClassId)
{
    INFO("Data Access Call GetNewObjectListId()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->GetNewContainerId(p_lClassId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CftlDataAccess::GetNewClassId(long p_lDbId)
{
    INFO("Data Access Call GetNewClassId()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->GetNewClassId(p_lDbId, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CftlDataAccess::GetNewObjectId(const CdmObjectContainer* p_pContainer)
{
    INFO("Data Access Call GetNewObjectId()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->GetNewObjectId(p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CftlDataAccess::UpdateObject(CdmObject*& p_pCdmObject)
{
    INFO("Data Access Call UpdateObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;


    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->UpdateObject(p_pCdmObject);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CftlDataAccess::UpdateObjectContainer(CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call UpdateObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;


    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->UpdateContainer(p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call UpdateObjectList() finished");
    return lRet;
}

int CftlDataAccess::CreateScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager)
{
    INFO("Data Access Call CreateDb()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlDbAccess))
    {
        lRet = m_pCftlDbAccess->CreateDb(p_qstrKeyname, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateDb() finished");
    return lRet;
}

int CftlDataAccess::LoadSchemeBaseData(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager)
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlDbAccess))
    {
        lRet = m_pCftlDbAccess->FindDatabase(p_qstrKeyname, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return lRet;
}

int CftlDataAccess::LoadSchemeBaseData(long p_lDb, CdmScheme *&p_pCdmDatabaseManager)
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlDbAccess))
    {
        lRet = m_pCftlDbAccess->FindDatabase(p_lDb, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return lRet;
}

int CftlDataAccess::IsDemo(QString p_qstrApplication, QString p_qstrVersion)
{
    int iRet = 0;
    bool bDemo = false;
    int p_iModules = 0;
    QString qstrVersion;
    m_pCftlLoginManager->LicenceCheck(p_qstrApplication, bDemo, p_iModules, qstrVersion);

    if (bDemo)
    {
        iRet = EC(eDmTrue);
    }
    else
    {
        iRet = EC(eDmFalse);

        if (qstrVersion != p_qstrVersion)
        {
            iRet = EC(eDmTrue);
        }
    }

    return iRet;
}

bool CftlDataAccess::LicenceCheck(QString p_qstrApplication,
                                  bool& p_bDemo,
                                  int& p_iModules,
                                  QString p_qstrVersion)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    bool bRet = false;

    if(CHKPTR(m_pCftlLoginManager))
    {
        bRet = m_pCftlLoginManager->LicenceCheck(p_qstrApplication, p_bDemo, p_iModules, p_qstrVersion);
    }

    return bRet;
}

int CftlDataAccess::Login(QString p_qstrApplication,
                          QString p_qstrLogin,
                          QString p_qstrPassword,
                          bool& p_bDemo,
                          int& p_iModules,
                          QString p_qstrVersion,
                          long& p_lSessionId,
                          CumUser*& p_rpCumUser)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlLoginManager))
    {
        p_lSessionId = m_pCftlLoginManager->Login(p_qstrApplication,
                                                  p_qstrLogin,
                                                  p_qstrPassword,
                                                  p_rpCumUser,
                                                  p_bDemo,
                                                  p_iModules,
                                                  p_qstrVersion);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    lRet = p_lSessionId;


    INFO("Data Access Call LogIn() finished. SessionId: " + QString::number(lRet));
    return lRet;
}

int CftlDataAccess::Logout()
{
    INFO("Data Access Call LogOut()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlLoginManager))
    {
        lRet = m_pCftlLoginManager->Logout();
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call LogOut() finished. SessionId");
    return lRet;
}

int CftlDataAccess::CreateUser(CumUser* p_pUser)
{
    INFO("Data Access Call CreateUser()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (m_pCftlUserManager)
    {
        lRet = m_pCftlUserManager->CreateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call CreateUser() finished");
    return lRet;
}

int CftlDataAccess::RegisterUser(CumUser* p_pUser)
{
    INFO("Data Access Call RegisterUser()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (m_pCftlUserManager)
    {
        lRet = m_pCftlUserManager->CreateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call RegisterUser() finished");
    return lRet;
}

int CftlDataAccess::DeleteUser(QString p_qstrLogin)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->DeleteUser(p_qstrLogin);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call DeleteUser() finished");
    return lRet;
}

int CftlDataAccess::DeleteUser(long p_lUserToDeleteId)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->DeleteUser(p_lUserToDeleteId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteUser() finished");
    return lRet;
}

int CftlDataAccess::LoadClassManager(long p_lSchemeId, CdmClassManager*& p_pCdmClassManager)
{
    INFO("Data Access Call LoadClassManager()");

    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->LoadClassManager(p_lSchemeId, p_pCdmClassManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadClassManager() finsihed");
    return lRet;
}

int CftlDataAccess::UpdateClass(CdmClass*& p_pCdmClass)
{
    INFO("Data Access Call UpdateClass()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->UpdateClass(p_pCdmClass);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateClass() finished");
    return lRet;
}

int CftlDataAccess::DeleteClass(long p_lClassId)
{
    INFO("Data Access Call DeleteClass()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->DeleteClass(p_lClassId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call DeleteClass() finished");
    return lRet;
}

int CftlDataAccess::DeleteScheme(QString p_qstrKeyname)
{
    INFO("Data Access Call DeleteDb()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlDbAccess))
    {
        lRet = m_pCftlDbAccess->DeleteDb(p_qstrKeyname);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteDb() finished");
    return lRet;
}

int CftlDataAccess::DeleteObjectContainer(long p_lObjectListId)
{
    INFO("Data Access Call DeleteObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlObjectAccess))
    {
         lRet = m_pCftlObjectAccess->DeleteObjectList(p_lObjectListId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteObjectList() finished");
    return lRet;
}

int CftlDataAccess::GetUserList(QList<CumUser*>& p_rqvlUser)
{
    INFO("Data Access Call GetUserList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(m_pCftlUserManager)
    {
        m_pCftlUserManager->GetUserList(p_rqvlUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetUserList() finished");
    return lRet;
}

int CftlDataAccess::UpdateUser(CumUser* p_pUser)
{

    INFO("Data Access Call UpdateUser()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(m_pCftlUserManager)
    {
        lRet = m_pCftlUserManager->UpdateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateUser() finished");
    return lRet;
}

int CftlDataAccess::GetContainerList(long p_lDbId, long p_lClassId, QMap<long, QString>& p_rqmObjectListsLList)
{
    INFO("Data Access Call GetObjectListsList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->GetObjectListsList(p_lDbId, p_lClassId, p_rqmObjectListsLList);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetObjectListsList() finished");
    return lRet;
}

int CftlDataAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
    INFO("Data Access Call ExecuteQuery()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->ExecuteQuery(p_pCdmQuery);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExecuteQuery() finished");
    return lRet;
}

int CftlDataAccess::ExistScheme(QString p_qstrKeyname, bool& p_bResult)
{
    INFO("Data Access Call ExistDb()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlDbAccess))
    {
        lRet = m_pCftlDbAccess->ExistDb(p_qstrKeyname, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistDb() finished");
    return lRet;
}

int CftlDataAccess::ExistClass(long p_lDbId, QString p_qstrClassKeyname, bool & p_bResult)
{
    INFO("Data Access Call ExistClass()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->ExistClass(p_lDbId, p_qstrClassKeyname, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistClass() finished");
    return lRet;
}

int CftlDataAccess::ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname)
{
    INFO("Data Access Call ExistObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlObjectAccess))
    {
        m_pCftlObjectAccess->ExistObjectList(p_lDbId, p_qstrObjectListKeyname);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistObjectList() finished");
    return lRet;
}

int CftlDataAccess::LockObject(CdmObject* p_pObject, bool & p_bResult)
{
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LockObject(p_pObject, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LockObject() finished");
    return lRet;
}

int CftlDataAccess::UnLockObject(CdmObject* p_pObject, bool & p_bResult )
{
    INFO("Data Access Call UnLockObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->UnLockObject(p_pObject, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UnLockObject() finished");
    return lRet;
}

QByteArray CftlDataAccess::ReadBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    INFO("Data Access Call ReadBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lDbId)
    QByteArray qByteArray;
    if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCftlObjectAccess))
    {
        qByteArray = m_pCftlObjectAccess->ReadBinaryDocument(p_pCdmBinaryDocument);
    }

    INFO("Data Access Call ReadBinaryDocument() finished");
    return qByteArray;
}

int CftlDataAccess::UpdateBinaryDocument(long p_lDbId, CdmValueBinaryDocument* p_pCdmBinaryDocument )
{
    INFO("Data Access Call UpdateBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lDbId)
    long lRet = 0;

    if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->UpdateBinaryDocument(p_pCdmBinaryDocument);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateBinaryDocument() finished");
    return lRet;
}

long CftlDataAccess::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    INFO("Data Access Call RenameUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->RenameUserGroup(p_lGroupId, p_qstrNewName);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call RenameUserGroup() finished");
    return lRet;
}

long CftlDataAccess::CreateUserGroup(QString p_qstrGroupName)
{
    INFO("Data Access Call CreateUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->CreateUserGroup(p_qstrGroupName);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateUserGroup() finished");
    return lRet;
}

long CftlDataAccess::DeleteUserGroup(long p_llGroupId)
{
    INFO("Data Access Call DeleteUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->DeleteUserGroup(p_llGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteUserGroup() finished");
    return lRet;
}

long CftlDataAccess::AddUserToUserGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call AddUserToUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->AddUserToUserGroup(p_lChangeUserId, p_lUserGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call AddUserToUserGroup() finished");
    return lRet;
}

long CftlDataAccess::RemoveUserFromGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call RemoveUserFromGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->RemoveUserFromGroup(p_lChangeUserId, p_lUserGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call RemoveUserFromGroup() finished");
    return lRet;
}


long CftlDataAccess::GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    INFO("Data Access Call GetUserGroupList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->GetUserGroupList(p_rqvlUserGroups);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call GetUserGroupList() finished");
    return lRet;
}

long CftlDataAccess::GetListOfUsersInList(long p_lUserGroupId, QList<CumUser*>& p_rqvlUserList)
{
    INFO("Data Access Call GetListOfUsersInList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->GetListOfUsersInList(p_lUserGroupId, p_rqvlUserList);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetListOfUsersInList() finished");
    return lRet;
}

long CftlDataAccess::GetUserGroupMemberList(long p_lChangeUserId, QList<CumUserGroup*>& p_qvlUserGroups)
{
    INFO("Data Access Call GetUserGroupMemberList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlUserManager))
    {
        lRet = m_pCftlUserManager->GetUserGroupMemberList(p_lChangeUserId, p_qvlUserGroups);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }


    INFO("Data Access Call GetUserGroupMemberList() finished");
    return lRet;
}

long CftlDataAccess::AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey)
{
    // ToDo Impl
    Q_UNUSED(p_qstrApplication);
    Q_UNUSED(p_qstrLicensee);
    Q_UNUSED(p_qstrLicensekey);
    return -1;
}

long CftlDataAccess::FreeLicense()
{
    // ToDo Impl
    NOTIMPLEMENTED;
    return -1;
}

long CftlDataAccess::GetSchemeList(QList<QString>& p_qvlDatabases)
{
    INFO("Data Access Call GetDatbaseList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlDbAccess))
    {
        m_pCftlDbAccess->GetDatabaseList(p_qvlDatabases);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetDatbaseList() finished");
    return lRet;
}

long CftlDataAccess::UpdateScheme(CdmScheme* p_pCdmDatabase)
{
    INFO("Data Access Call UpdateDatabase()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCftlDbAccess) && CHKPTR(p_pCdmDatabase))
    {
        lRet = m_pCftlDbAccess->UpdateDatabase(p_pCdmDatabase);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateDatabase() finished");
    return lRet;
}


long CftlDataAccess::GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue)
{
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->GetCounterValue(p_pContainer, p_pValue);
    }

    INFO("Data Access Call GetCounterValue() finished");
    return lRet;
}

QString CftlDataAccess::GetConnectionDisplayString()
{
    QString qstrConnection;
    CftlInterface* pInterface = GetFtlInterface();

    if (pInterface)
    {
        qstrConnection = pInterface->GetConnectionDisplayString();
    }

    return qstrConnection;
}


bool CftlDataAccess::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->CheckAuthorisationAdmin(p_qstrLogin, p_qstrPassword);
}

bool CftlDataAccess::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->CheckAuthorisation(p_qstrLogin, p_qstrPassword);
}

CumUser* CftlDataAccess::FindUserById(int p_iId)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUser(p_iId);
}

CumUser* CftlDataAccess::FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserByEmail(p_qstrEmail, p_qstrSchemeUri);
}

CumUser* CftlDataAccess::FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserByLogin(p_qstrLogin, p_qstrSchemeUri);
}

CumUser* CftlDataAccess::FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUser(p_qstrLogin, p_qstrPassword, p_qstrSchemeUri);
}

CumUserGroup* CftlDataAccess::FindUserGroupById(int p_iId)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserGroupById(p_iId);
}

CumUserGroup* CftlDataAccess::FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserGroupByName(p_qstrName, p_qstrSchemeUri);
}

int CftlDataAccess::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, long& p_lSessionId, CumUser*& p_rUser)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlLoginManager))
    {
        p_lSessionId = m_pCftlLoginManager->LoginLdap(p_qstrApplication,
                                                      p_qstrLogin,
                                                      p_qstrPassword,
                                                      p_rUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    lRet = p_lSessionId;

    INFO("Data Access Call LogIn() finished. SessionId: " + QString::number(lRet));
    return lRet;
}

int CftlDataAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
{
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCftlClassAccess))
    {
        lRet = m_pCftlClassAccess->UpdatePackage(p_pCdmPackage);
    }

    return lRet;
}

long CftlDataAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    long lRet = 0;
    ++m_iInterfaceCallCounter;
    INFO("RefreshObject Call");

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->RefreshObject(p_pCdmObject);
    }

    INFO("RefreshObject Call finished");
    return lRet;
}

long CftlDataAccess::RefreshObjectContainer(CdmObjectContainer* p_pCdmObject)
{
    long lRet = 0;
    INFO("RefreshObjectList Call");
    ++m_iInterfaceCallCounter;


    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->RefreshObjectList(p_pCdmObject);
    }


    INFO("RefreshObjectList Call finished");
    return lRet;
}

long CftlDataAccess::CountObjectsOnDb(CdmObjectContainer* p_pCdmObject)
{
    long lRet = 0;
    ++m_iInterfaceCallCounter;
    INFO("CountObjectOnDb Call");

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->CountObjectsOnDb(p_pCdmObject);
    }

    return lRet;
}

int CftlDataAccess::DeleteRights(long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName)
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    GetFtlInterface()->BeginTransaction();
    QSqlQuery cQuery;
    QString qstrSQLDeleteOldRights;

    qstrSQLDeleteOldRights = "delete from " + p_qstrTableName + " where " + p_qstrIdFieldName + " = " + QString::number(p_lObjectId);

    if (ExecuteQuery(qstrSQLDeleteOldRights, cQuery) > 0)
    {
        iRet = EC(eDmOk);
    }
    else
    {
        iRet = EC(eDmInvalidDeleteStatement);
    }

    if (iRet > 0)
    {
        GetFtlInterface()->Commit();
    }
    else
    {
        GetFtlInterface()->Rollback();
    }

    return iRet;
}

int CftlDataAccess::SaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName)
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    GetFtlInterface()->BeginTransaction();

    if (DeleteRights(p_lObjectId, p_qstrTableName, p_qstrIdFieldName) == CdmLogging::eDmOk)
    {
        QVariantMap qvHash = p_rCcdmRights.GetVariant().toMap();
        QVariantMap::Iterator qvIt = qvHash.begin();
        QVariantMap::Iterator qvItEnd = qvHash.end();

        if (qvHash.count() == 0)
        {
            iRet = EC(eDmOk);
        }
        else
        {
            for (; qvIt != qvItEnd; ++qvIt)
            {
                QString qstrInsert;
                QSqlQuery cQuery;
                qstrInsert = QString("insert into %1 (%2, UserBaseId, RightId) values (%3, %4, %5)")
                        .arg(p_qstrTableName)
                        .arg(p_qstrIdFieldName)
                        .arg(p_lObjectId)
                        .arg(qvIt.key().toInt())
                        .arg(qvIt.value().toInt());

                if (ExecuteQuery(qstrInsert, cQuery))
                {
                    iRet = EC(eDmOk);
                }
            }
        }
    }
    else
    {
        iRet = EC(eDmInvalidDeleteStatement);
    }

    if (iRet > 0)
    {
        GetFtlInterface()->Commit();
    }
    else
    {
        GetFtlInterface()->Rollback();
    }

    return iRet;
}

int CftlDataAccess::LoadRights(CdmRights& p_rCcdmRights,  long p_lObjectId,  QString p_qstrTableName, QString p_qstrIdFieldName)
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQuery;
    QString qstrSQL;

    qstrSQL = QString("select UserBaseId, RightId from %1 where %2 = %3")
            .arg(p_qstrTableName)
            .arg(p_qstrIdFieldName)
            .arg(p_lObjectId);

    if (ExecuteQuery(qstrSQL, cQuery) > 0)
    {
        iRet = EC(eDmOk);
        cQuery.first();

        if(cQuery.isValid())
        {
            do
            {
                int iUserBaseId = cQuery.value(0).toInt();
                EdmRight eDmRight = static_cast<EdmRight>(cQuery.value(1).toInt());
                p_rCcdmRights.AddRight(iUserBaseId, eDmRight);
            }
            while(cQuery.next());
        }
    }

    return iRet;
}

int CftlDataAccess::DeleteLanguage(long p_lDatabaseId, int p_iLanguageId)
{
    long lRet = 0;
    ++m_iInterfaceCallCounter;
    INFO("Delete Language Call");

    lRet = m_pCftlDbAccess->DeleteLanguage(p_lDatabaseId, p_iLanguageId);

    return lRet;
}

int CftlDataAccess::AddLanguage(long p_lDatabaseId, QString p_qstrLanguage)
{
    ++m_iInterfaceCallCounter;
    INFO("AddLanguage Call");
    return m_pCftlDbAccess->AddLanguage(p_lDatabaseId, p_qstrLanguage);
}


int CftlDataAccess::GetSchemeModifications(long p_lSchemeId,
                                           QDate p_qdFrom,
                                           QDate p_qdTo,
                                           QList<CdmJournalItem*>& p_qlItems)
{
    ++m_iInterfaceCallCounter;
    INFO("GetDatabaseModifications Call");
    return m_pCftlJournal->GetDatabaseModifications(p_lSchemeId, p_qdFrom, p_qdTo, p_qlItems);
}


int CftlDataAccess::GetObjectContainerModifications(const CdmObjectContainer* p_pContainer,
                                                    QDate p_qdFrom,
                                                    QDate p_qdTo,
                                                    QList<CdmJournalItem*>& p_qlItems)
{
    ++m_iInterfaceCallCounter;
    INFO("GetObjectListModifications Call");
    return m_pCftlJournal->GetObjectListModifications(p_pContainer->GetId(), p_qdFrom, p_qdTo, p_qlItems);
}


int CftlDataAccess::GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_qlItems)
{
    ++m_iInterfaceCallCounter;
    INFO("GetObjectModifications Call");
    return m_pCftlJournal->GetObjectModifications(p_pObject, p_qdFrom, p_qdTo, p_qlItems);
}

bool CftlDataAccess::GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject)
{
    return m_pCftlObjectAccess->GetOwner(p_pObject, p_pOwnerObject);
}

bool CftlDataAccess::GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject)
{
    return m_pCftlObjectAccess->GetOwner(p_pContainer, p_pOwnerObject);
}

bool CftlDataAccess::GetReferences(const CdmObject* p_pObject, QList<CdmObject*>& p_rqmReferences)
{
    Q_UNUSED(p_rqmReferences);
    Q_UNUSED(p_pObject);
    bool bRet = false;
    NOTIMPLEMENTED;
    return bRet;
}

CdmObject* CftlDataAccess::CreateObject(CdmObjectContainer* p_pContainer)
{
    Q_UNUSED(p_pContainer);
    // only implemented for webclient
    NOTIMPLEMENTED;
    return nullptr;
}

int CftlDataAccess::Init(QString p_qstrApplicationName, QString p_qstrVersion)
{
    int iRet = 0;
    Q_UNUSED(p_qstrApplicationName);
    Q_UNUSED(p_qstrVersion);
    return iRet;
}

void CftlDataAccess::CreateDatabase(EftlSupportedDatabase database)
{
    QString qstrSQLFile = ":/sql/";

    switch (database)
    {
    case eSupportedDatabaseMySQL:
        qstrSQLFile += "mysql";
        break;
    case eSupportedDatabasePostgreSQL:
        qstrSQLFile += "postgresql";
        break;
    case eSupportedDatabaseOracle:
        qstrSQLFile += "oracle";
        break;
    case eSupportedDatabaseMSSQL:
        qstrSQLFile += "mssql";
        break;
    }

    qstrSQLFile += "-create-script.sql";
    CreateDatabase(qstrSQLFile);
}

void CftlDataAccess::CreateDatabase(QString p_qstrFilename)
{
    QFile qFile(p_qstrFilename);

    if(qFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream qTextStream(&qFile);
        QString line;
        QString qstrSql = "";
        while (!qTextStream.atEnd()){
            line = qTextStream.readLine();
            if(line.startsWith('#') || line.isEmpty())
                continue;
            qstrSql += line;
            if(qstrSql.trimmed().endsWith(";")){
                QSqlQuery query;
                ExecuteQuery(qstrSql, query);
                qstrSql = "";
            }
        }
    }
    else
    {
        ERR("Could not open SQL File for creating database");
    }
}


bool CftlDataAccess::LockClassMethod(long p_lMethodId)
{
    bool bSuccess = false;
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;

    if(CHKPTR(m_pCftlClassAccess))
    {
        bSuccess = m_pCftlClassAccess->LockMethod(p_lMethodId);
    }

    return bSuccess;
}

bool CftlDataAccess::UnlockClassMethod(long p_lMethodId)
{
    bool bSuccess = false;
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    if(CHKPTR(m_pCftlClassAccess))
    {
        bSuccess = m_pCftlClassAccess->UnlockMethod(p_lMethodId);
    }

    return bSuccess;
}

QVariant CftlDataAccess::ExecuteFunction(CdmObject* p_PObject,
                                         QString p_qstrFunctionName,
                                         QVariantList p_qvlParameters)
{
    Q_UNUSED(p_PObject);
    Q_UNUSED(p_qstrFunctionName);
    Q_UNUSED(p_qvlParameters);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
    return QVariant();
}

QVariant CftlDataAccess::EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula )
{
    Q_UNUSED(p_pObject);
    Q_UNUSED(p_qstrFormula);
    NOTIMPLEMENTED;
    return QVariant();
}

void CftlDataAccess::PrintObject(QString p_qstrTemplateName, CdmObject* p_pObject)
{
    Q_UNUSED(p_pObject);
    Q_UNUSED(p_qstrTemplateName);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
}

void CftlDataAccess::PrintContainer(QString p_qstrTemplateName, CdmObjectContainer* p_pContainer)
{
    Q_UNUSED(p_pContainer);
    Q_UNUSED(p_qstrTemplateName);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
}

CdmSession *CftlDataAccess::FindSession(int p_iSessionId)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlLoginManager->FindSession(p_iSessionId);
}

CdmSession *CftlDataAccess::FindSession(QString p_qstrBaseAuth)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlLoginManager->FindSession(p_qstrBaseAuth);
}

void CftlDataAccess::UpdateSession(int p_iSessionId)
{
    ++m_iInterfaceCallCounter;
    m_pCftlLoginManager->UpdateSession(p_iSessionId);
}

void CftlDataAccess::UpdateSession(QString p_qstrBaseAuth)
{
    ++m_iInterfaceCallCounter;
    m_pCftlLoginManager->UpdateSession(p_qstrBaseAuth);
}

void CftlDataAccess::SessionTimeoutCheck(int p_iTimeoutMin)
{
    ++m_iInterfaceCallCounter;
    m_pCftlLoginManager->SessionTimeoutCheck(p_iTimeoutMin);
}

CumUser *CftlDataAccess::FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserByIdentKey(p_qstridentKey, p_qstrSchemeUri);
}

QList<CumUser*> CftlDataAccess::FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUser(p_qstrUserLoginNameEmail, p_qstrSchemeUri);
}

QList<CumUserGroup *> CftlDataAccess::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCftlUserManager->FindUserGroups(p_qstrName, p_qstrSchemeUri);
}

int CftlDataAccess::LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject)
{
    long lRet = CdmLogging::eDmUnknownSqlError;

    if(CHKPTR(m_pCftlObjectAccess))
    {
        lRet = m_pCftlObjectAccess->LoadObject(p_pContainer, p_qstrKeyname, p_pCdmObject);
    }

    return lRet;
}
