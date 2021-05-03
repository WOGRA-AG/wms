
// System and QT Includes

#include <QTime>
#include <qdatetime.h>
#include <qfile.h>
#include <QVariant>
#include <QThread>
#include <qtextstream.h>
#include <QList>
#include <QDebug>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"

// own Includes
#include "CwnDataAccessConfigurator.h"
#include "CwnUserManager.h"
#include "CwnLoginManager.h"
#include "CwnDataAccess.h"
#include "CwnClassAccess.h"
#include "CwnObjectAccess.h"
#include "CwnDbAccess.h"
#include "CwnJournal.h"
#include "CwnQuery.h"
#include "CwnCommandCreateScheme.h"
#include "CwnCommandLoadRights.h"
#include "CwnCommandSaveRights.h"
#include "CwnCommandCreateUser.h"


CwnDataAccess::CwnDataAccess()
: QObject(nullptr),
  m_pCwnUserManager(nullptr),
  m_pCwnLoginManager(nullptr),
  m_iQueryCountGlobal(0),
  m_iQueryCountSuccess(0),
  m_qstrDbName("wms"),
  m_bServerMode(false),
  m_iInterfaceCallCounter(0),
  m_iTransactionCount(0),
  m_iMsecsSum(0)
{

}

CwnDataAccess::~CwnDataAccess()
{
    DELPTR(m_pCwnDbAccess);
    DELPTR(m_pCwnUserManager);
    DELPTR(m_pCwnLoginManager);
    DELPTR(m_pCwnObjectAccess);
    DELPTR(m_pCwnClassAccess);
    DELPTR(m_pCwnJournal);
}

int CwnDataAccess::Init(CwnDataAccessConfigurator *p_pConfig)
{
    int iRet = CdmLogging::eDmUnknownSqlError;

    m_rpConfig = p_pConfig;
    m_pCwnUserManager = new CwnUserManager(this);
    m_pCwnLoginManager = new CwnLoginManager(this,m_pCwnUserManager);
    m_pCwnClassAccess = new CwnClassAccess(this);
    m_pCwnDbAccess =  new CwnSchemeAccess(this);
    m_pCwnObjectAccess = new CwnObjectAccess(this);
    m_pCwnJournal = new CwnJournal(this);

    iRet = EC(eDmOk);

    CwnCommandCreateUser create(this,"");
    create.setActive(true);
    create.setAdmin(true);
    create.setFirstname("admin");
    create.setLastname("admin");
    create.setLogin("admin");
    create.setPass("admin");
    create.Run();

    return iRet;
}

CwnDataAccessConfigurator *CwnDataAccess::GetConfig()
{
    return m_rpConfig;
}

int CwnDataAccess::SessionCheck()
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        long iSessionId = pSessionManager->GetCurrentSessionId();
        long iUserId = pSessionManager->GetCurrentUserId();
        lRet = m_pCwnLoginManager->FindSession(iSessionId, iUserId);
    }

    return lRet;
}

int CwnDataAccess::LoadObject(const CdmObjectContainer* p_pContainer, long p_lObjectId, CdmObject *&p_pCdmObject)
{
    INFO("Data Access Call LoadObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->LoadObject(p_pContainer->GetId(), p_lObjectId, p_pCdmObject);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadObject() Finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadObjectContainer(long p_lObjectListId, CdmObjectContainer *&p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->LoadContainer(p_lObjectListId, p_pContainer);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadObject() finished");
    return static_cast<int>(lRet);
}

long CwnDataAccess::GetNewClassId(long p_lDbId)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
        return m_pCwnClassAccess->GetNewClassId(p_lDbId, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }

    return static_cast<int>(lRet);
}

long CwnDataAccess::GetNewObjectId(const CdmObjectContainer* p_pContainer)
{
    INFO("Data Access Call GetNewObjectId()");
    ++m_iInterfaceCallCounter;
    long lRet=1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->GetNewObjectId(p_pContainer->GetId(), CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CwnDataAccess::UpdateObject(CdmObject *&p_pCdmObject)
{
    INFO("Data Access Call UpdateObject()");
    ++m_iInterfaceCallCounter;
    //long lRet = BeginTransaction();
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->UpdateObject(p_pCdmObject, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call LoadObjectList() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::UpdateObjectContainer(CdmObjectContainer *&p_pContainer)
{
    INFO("Data Access Call UpdateObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->UpdateContainer(p_pContainer, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call UpdateObjectList() finished");
    return static_cast<int>(lRet);
}


int CwnDataAccess::CreateScheme(QString p_qstrKeyname, CdmScheme *&p_pScheme)
{
    INFO("Data Access Call CreateScheme()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;
    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnDbAccess))
        {
            lRet = m_pCwnDbAccess->CreateDb(p_qstrKeyname, p_pScheme);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call CreateScheme() finished.");
    return static_cast<int>(lRet);
}


int CwnDataAccess::LoadSchemeBaseData(QString p_qstrKeyname, CdmScheme *&p_pScheme)
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;

    long lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnDbAccess))
       {
          lRet = m_pCwnDbAccess->FindDatabase(p_qstrKeyname, p_pScheme);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadSchemeBaseData(long p_lSchemeId, CdmScheme *&p_pScheme)
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;
    long lRet;
    //long lRet = BeginTransaction();

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnDbAccess))
       {
          lRet = m_pCwnDbAccess->FindDatabase(p_lSchemeId, p_pScheme);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return static_cast<int>(lRet);

}

int CwnDataAccess::Login(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, bool &p_bDemo, int &p_iModules, QString p_qstrVersion, long &p_lSessionId, CumUser *&p_rpCumUser)
{
    INFO("Data Access Call LogIn()");
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    if(CHKPTR(m_pCwnLoginManager))
    {
        p_lSessionId = m_pCwnLoginManager->Login(p_qstrApplication,
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
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, long &p_lSessionId, CumUser *&p_rUser)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    if(CHKPTR(m_pCwnLoginManager))
    {
        p_lSessionId = m_pCwnLoginManager->LoginLdap(p_qstrApplication,
                                                          p_qstrLogin,
                                                          p_qstrPassword,
                                                          p_rUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LogIn() finished. SessionId: " + QString::number(lRet));
    return static_cast<int>(lRet);
}

int CwnDataAccess::Logout()
{
    INFO("Data Access Call LogOut()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    if(CHKPTR(m_pCwnLoginManager))
    {
       lRet = m_pCwnLoginManager->Logout(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LogOut() finished. SessionId");
    return static_cast<int>(lRet);

}

int CwnDataAccess::CreateUser(CumUser* p_pUser)
{
    INFO("Data Access Call CreateUser()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if (m_pCwnUserManager)
        {
            lRet = m_pCwnUserManager->CreateUser(p_pUser);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call CreateUser() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::RegisterUser(CumUser* p_pUser)
{
    INFO("Data Access Call RegisterUser()");
    ++m_iInterfaceCallCounter;
    long lRet=1;
    if(lRet > 0)
    {
       if (m_pCwnUserManager)
       {
           lRet = m_pCwnUserManager->CreateUser(p_pUser);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call RegisterUser() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::DeleteUser(QString p_qstrLogin)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnUserManager))
        {
            lRet = m_pCwnUserManager->DeleteUser(p_qstrLogin);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call DeleteUser() finished");
    return static_cast<int>(lRet);

}

int CwnDataAccess::DeleteUser(long p_lUserToDeleteId)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet =1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnUserManager))
          {
             lRet = m_pCwnUserManager->DeleteUser(p_lUserToDeleteId);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call DeleteUser() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::DeleteClass(long p_lClassId)
{
    INFO("Data Access Call DeleteClass()");
    ++m_iInterfaceCallCounter;
    long lRet =1;
    //BeginTransaction();

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnClassAccess))
          {
             m_pCwnClassAccess->DeleteClass(p_lClassId);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call DeleteClass() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadClassManager(long p_lDatabaseId, CdmClassManager *&p_pCdmClassManager)
{
    INFO("Data Access Call LoadClassManager()");

    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnClassAccess))
       {
          m_pCwnClassAccess->LoadClassManager(p_lDatabaseId, p_pCdmClassManager);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadClassManager() finsihed");
    return static_cast<int>(lRet);
}

int CwnDataAccess::DeleteScheme(QString p_qstrKeyname)
{
    INFO("Data Access Call DeleteDb()");
    ++m_iInterfaceCallCounter;
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnDbAccess))
          {
             lRet = m_pCwnDbAccess->DeleteScheme(p_qstrKeyname);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }
    return static_cast<int>(lRet);
}

int CwnDataAccess::DeleteObjectContainer(long p_lObjectListId)
{
    INFO("Data Access Call DeleteObjectList()");
     ++m_iInterfaceCallCounter;
     long lRet =1;

     if(lRet > 0)
     {
        lRet = SessionCheck();

        if(lRet > 0)
        {
           if(CHKPTR(m_pCwnObjectAccess))
           {
              m_pCwnObjectAccess->DeleteContainer(p_lObjectListId);
           }
           else
           {
              lRet = EC(eDmInvalidPtr);
           }
        }
     }

     INFO("Data Access Call DeleteObjectList() finished");
     return static_cast<int>(lRet);
}

int CwnDataAccess::GetUserList(QList<CumUser *> &p_rqvlUser)
{
    INFO("Data Access Call GetUserList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(m_pCwnUserManager)
       {
          m_pCwnUserManager->GetUserList(p_rqvlUser);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetUserList() finished");
    return static_cast<int>(lRet);

}

int CwnDataAccess::GetContainerList(long p_lDbId, long p_lClassId, QMap<long, QString> &p_rqmObjectListsLList)
{
    INFO("Data Access Call GetObjectListsList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->GetObjectListsList(p_lDbId, p_lClassId, p_rqmObjectListsLList);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetObjectListsList() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::ExecuteQuery(CdmQuery *p_pCdmQuery)
{
    INFO("Data Access Call ExecuteQuery()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->ExecuteQuery(p_pCdmQuery);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }
    INFO("Data Access Call ExecuteQuery() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::ExistScheme(QString p_qstrKeyname, bool &p_bResult)
{
    INFO("Data Access Call ExistDb()");
    ++m_iInterfaceCallCounter;
    //BeginTransaction();
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnDbAccess))
       {
          lRet = m_pCwnDbAccess->ExistDb(p_qstrKeyname, p_bResult);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call ExistDb() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::ExistClass(long p_lDbId, QString p_qstrClassKeyname, bool &p_bResult)
{
    INFO("Data Access Call ExistClass()");
    //BeginTransaction();
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnClassAccess))
       {
          lRet = m_pCwnClassAccess->ExistClass(p_lDbId, p_qstrClassKeyname, p_bResult);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call ExistClass() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname)
{
    INFO("Data Access Call ExistObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          m_pCwnObjectAccess->ExistObjectList(p_lDbId, p_qstrObjectListKeyname);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call ExistObjectList() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LockObject(CdmObject* p_pObject, bool &p_bResult)
{
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             m_pCwnObjectAccess->LockObject(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(),
                                            p_pObject->GetId(),
                                            p_bResult);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call LockObject() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::UnLockObject(CdmObject* p_pObject, bool &p_bResult)
{
    INFO("Data Access Call UnLockObject()");
    ++m_iInterfaceCallCounter;
    long lRet=1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->UnLockObject(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(),
                                                     p_pObject->GetId(),
                                                     p_bResult);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call UnLockObject() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadObjectContainer(long p_lDatabaseId, QString p_qstrKeyname, CdmObjectContainer *&p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->LoadContainer(p_lDatabaseId, p_qstrKeyname, p_pContainer);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadObjectList() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId, QString p_qstrKeyname, CdmObjectContainer *&p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
     ++m_iInterfaceCallCounter;

     long lRet = 0;
     lRet = SessionCheck();

     if(lRet > 0)
     {
        if(CHKPTR(m_pCwnObjectAccess))
        {
           lRet = m_pCwnObjectAccess->LoadEmptyContainer(p_lDataBaseId, p_qstrKeyname, p_pContainer);
        }
        else
        {
           lRet = EC(eDmInvalidPtr);
        }
     }

     INFO("Data Access Call LoadObjectList() finished");
     return static_cast<int>(lRet);
}

QByteArray CwnDataAccess::ReadBinaryDocument(long p_lDbId, CdmValueBinaryDocument *p_pCdmBinaryDocument)
{
    INFO("Data Access Call ReadBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lDbId)

    long lRet = 0;
    lRet = SessionCheck();
    QByteArray qbaResult;

    if(lRet > 0)
    {
       if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCwnObjectAccess))
       {
          qbaResult = m_pCwnObjectAccess->ReadBinaryDocument(p_pCdmBinaryDocument);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call ReadBinaryDocument() finished");
    return qbaResult;
}

int CwnDataAccess::UpdateBinaryDocument(long p_lDbId, CdmValueBinaryDocument *p_pCdmBinaryDocument)
{
    INFO("Data Access Call UpdateBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lDbId)
    long lRet=1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->UpdateBinaryDocument(p_pCdmBinaryDocument);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call UpdateBinaryDocument() finished");
    return static_cast<int>(lRet);
}

long CwnDataAccess::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    INFO("Data Access Call RenameUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnUserManager))
        {
            lRet = m_pCwnUserManager->RenameUserGroup(p_lGroupId, p_qstrNewName);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call RenameUserGroup() finished");
    return lRet;
}

long CwnDataAccess::CreateUserGroup(QString p_qstrGroupName)
{
    INFO("Data Access Call CreateUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnUserManager))
        {
            lRet = m_pCwnUserManager->CreateUserGroup(p_qstrGroupName);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call CreateUserGroup() finished");
    return lRet;
}

long CwnDataAccess::DeleteUserGroup(long p_llGroupId)
{
    INFO("Data Access Call DeleteUserGroup()");
     ++m_iInterfaceCallCounter;
     long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnUserManager))
       {
          lRet = m_pCwnUserManager->DeleteUserGroup(p_llGroupId);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call DeleteUserGroup() finished");
    return lRet;
}

long CwnDataAccess::AddUserToUserGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call AddUserToUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnUserManager))
        {
            lRet = m_pCwnUserManager->AddUserToUserGroup(p_lChangeUserId, p_lUserGroupId);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call AddUserToUserGroup() finished");
    return lRet;
}

long CwnDataAccess::RemoveUserFromGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call RemoveUserFromGroup()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnUserManager))
        {
            lRet = m_pCwnUserManager->RemoveUserFromGroup(p_lChangeUserId, p_lUserGroupId);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call RemoveUserFromGroup() finished");
    return lRet;
}

long CwnDataAccess::GetUserGroupList(QList<CumUserGroup *> &p_rqvlUserGroups, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    INFO("Data Access Call GetUserGroupList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnUserManager))
       {
          lRet = m_pCwnUserManager->GetUserGroupList(p_rqvlUserGroups);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetUserGroupList() finished");
    return lRet;
}

long CwnDataAccess::GetListOfUsersInList(long p_lUserGroupId, QList<CumUser *> &p_rqvlUserList)
{
    INFO("Data Access Call GetListOfUsersInList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnUserManager))
       {
          lRet = m_pCwnUserManager->GetListOfUsersInList(p_lUserGroupId, p_rqvlUserList);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetListOfUsersInList() finished");
    return lRet;
}

long CwnDataAccess::GetUserGroupMemberList(long p_lChangeUserId, QList<CumUserGroup *> &p_qvlUserGroups)
{
    INFO("Data Access Call GetUserGroupMemberList()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnUserManager))
       {
          lRet = m_pCwnUserManager->GetUserGroupMemberList(p_lChangeUserId, p_qvlUserGroups);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetUserGroupMemberList() finished");
    return lRet;
}

long CwnDataAccess::AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey)
{
    // ToDo Impl
    Q_UNUSED(p_qstrApplication);
    Q_UNUSED(p_qstrLicensee);
    Q_UNUSED(p_qstrLicensekey);
    return -1;
}

long CwnDataAccess::FreeLicense()
{
    // ToDo Impl
    NOTIMPLEMENTED;
    return -1;
}

long CwnDataAccess::GetSchemeList(QList<QString> &p_qvlDatabases)
{
    INFO("Data Access Call GetDatbaseList()");
    //BeginTransaction();
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnDbAccess))
       {
          m_pCwnDbAccess->GetDatabaseList(p_qvlDatabases);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call GetDatbaseList() finished");
    //Commit();
    return lRet;
}

long CwnDataAccess::UpdateScheme(CdmScheme *p_pCdmDatabase)
{
    INFO("Data Access Call UpdateDatabase()");
    ++m_iInterfaceCallCounter;
    long lRet =1;
    //BeginTransaction();

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnDbAccess) && CHKPTR(p_pCdmDatabase))
          {
             lRet = m_pCwnDbAccess->UpdateDatabase(p_pCdmDatabase);
          }
          else
          {
             lRet = EC(eDmInvalidPtr);
          }
       }
    }

    INFO("Data Access Call UpdateDatabase() finished");
    return lRet;
}

long CwnDataAccess::GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue)
{
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnObjectAccess))
          {
             lRet = m_pCwnObjectAccess->GetCounterValue(p_pContainer->GetSchemeId(),
                                                        p_pContainer->GetId(),
                                                        p_pValue->GetId(),
                                                        p_pValue->GetKeyname());
          }
       }
    }

    INFO("Data Access Call GetCounterValue() finished");
    return lRet;
}

long CwnDataAccess::GetNewContainerId(long p_lClassId)
{
    INFO("Data Access Call GetNewObjectListId()");

    ++m_iInterfaceCallCounter;

    long lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->GetNewObjectListId(p_lClassId,
                                                        CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

QString CwnDataAccess::GetConnectionDisplayString()
{
    return "";
}

int CwnDataAccess::UpdateUser(CumUser* p_pUser)
{
    INFO("Data Access Call UpdateUser()");
    ++m_iInterfaceCallCounter;
    long lRet = -1;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(m_pCwnUserManager)
        {
            lRet = m_pCwnUserManager->UpdateUser(p_pUser);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call UpdateUser() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId, long p_lId, CdmObjectContainer *&p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
    ++m_iInterfaceCallCounter;
    //BeginTransaction();

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->LoadEmptyContainer(p_lDataBaseId, p_lId, p_pContainer);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    //Rollback();
    INFO("Data Access Call LoadObjectList() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::LoadObjects(QList<long> &p_rqvlObjects, CdmObjectContainer *&p_pCdmObject)
{
    INFO("Data Access Call LoadObjects()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->LoadObjects(p_pCdmObject, p_rqvlObjects);
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call LoadObjects() Finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::IsDemo(QString p_qstrApplication, QString p_qstrVersion)
{
     int iRet = 0;
     bool bDemo = false;
     int p_iModules = 0;
     QString qstrVersion;
     m_pCwnLoginManager->LicenceCheck(p_qstrApplication, bDemo, p_iModules, qstrVersion);

     if (bDemo)
     {
        iRet = EC(eDmTrue);
     }
     else
     {
        iRet = EC(eDmFalse);
        Q_UNUSED(p_qstrVersion);
        /*
        if (qstrVersion != p_qstrVersion)
        {
           iRet = EC(eDmTrue);
        }
        */
     }

     return iRet;
}

long CwnDataAccess::IsObjectUsed(const CdmObject* p_pObject)
{
    INFO("Data Access Call IsObjectUsed()");
    ++m_iInterfaceCallCounter;

    long lRet = 0;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->IsObjectUsed(p_pObject->GetId(), p_pObject->GetObjectContainerId());
       }
       else
       {
          lRet = EC(eDmInvalidPtr);
       }
    }

    INFO("Data Access Call IsObjectUsed() Finished");
    return lRet;
}

bool CwnDataAccess::LicenceCheck(QString p_qstrApplication, bool &p_bDemo, int &p_iModules, QString p_qstrVersion)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    bool bRet = false;

    if(CHKPTR(m_pCwnLoginManager))
    {
       bRet = m_pCwnLoginManager->LicenceCheck(p_qstrApplication, p_bDemo, p_iModules, p_qstrVersion);
    }

    return bRet;

}

bool CwnDataAccess::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
{
    return m_pCwnUserManager->CheckAuthorisationAdmin(p_qstrLogin, p_qstrPassword);
}

bool CwnDataAccess::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
{
    return m_pCwnUserManager->CheckAuthorisation(p_qstrLogin, p_qstrPassword);
}

CumUser *CwnDataAccess::FindUserById(int p_iId)
{
    ++m_iInterfaceCallCounter;
    return m_pCwnUserManager->FindUser(p_iId);
}

CumUser *CwnDataAccess::FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    ++m_iInterfaceCallCounter;
    return m_pCwnUserManager->FindUserByEmail(p_qstrEmail);
}

CumUser *CwnDataAccess::FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    ++m_iInterfaceCallCounter;
    return m_pCwnUserManager->FindUserByLogin(p_qstrLogin);
}

CumUser *CwnDataAccess::FindUser(QString p_qstrUserId, QString p_qstrPassword, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    ++m_iInterfaceCallCounter;
    return m_pCwnUserManager->FindUser(p_qstrUserId,p_qstrPassword);
}

long CwnDataAccess::RefreshObject(CdmObject *p_pCdmObject)
{
    long lRet = -1;
     ++m_iInterfaceCallCounter;
     INFO("RefreshObject Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->RefreshObject(p_pCdmObject);
       }
    }

    INFO("RefreshObject Call finished");
    return lRet;
}

long CwnDataAccess::RefreshObjectContainer(CdmObjectContainer *p_pCdmObject)
{
    long lRet = -1;
    INFO("RefreshObjectList Call");
     ++m_iInterfaceCallCounter;

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->RefreshObjectList(p_pCdmObject);
       }
    }

    INFO("RefreshObjectList Call finished");
    return lRet;
}

long CwnDataAccess::CountObjectsOnDb(CdmObjectContainer *p_pCdmObject)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("CountObjectOnDb Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
          lRet = m_pCwnObjectAccess->CountObjectsOnDb(p_pCdmObject);
       }
    }

    return lRet;
}

int CwnDataAccess::AddLanguage(long p_lDatabaseId, QString p_qstrLanguage)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("AddLanguage Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       lRet = m_pCwnDbAccess->AddLanguage(p_lDatabaseId, p_qstrLanguage);
    }

    return static_cast<int>(lRet);
}

int CwnDataAccess::DeleteLanguage(long p_lDatabaseId, int p_iLanguageId)
{
    long lRet = -1;
    //BeginTransaction();
    ++m_iInterfaceCallCounter;
    INFO("Delete Language Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       lRet = m_pCwnDbAccess->DeleteLanguage(p_lDatabaseId, p_iLanguageId);
    }

    return static_cast<int>(lRet);
}

int CwnDataAccess::GetSchemeModifications(long p_lDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetDatabaseModifications Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       lRet = m_pCwnJournal->GetSchemeModifications(static_cast<int>(p_lDatabaseId), p_qdFrom, p_qdTo, p_qlItems);
    }

    return static_cast<int>(lRet);
}

int CwnDataAccess::GetObjectContainerModifications(const CdmObjectContainer* p_pContainer, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetObjectListModifications Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       lRet = m_pCwnJournal->GetObjectListModifications(static_cast<int>(p_pContainer->GetId()), p_qdFrom, p_qdTo, p_qlItems);
    }

    return static_cast<int>(lRet);
}

int CwnDataAccess::GetObjectModifications(const CdmObject* p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem *> &p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetObjectModifications Call");

    lRet = SessionCheck();

    if(lRet > 0)
    {
       lRet = m_pCwnJournal->GetObjectModifications(static_cast<int>(p_pObject->GetId()), p_qdFrom, p_qdTo, p_qlItems);
    }
    return static_cast<int>(lRet);
}

bool CwnDataAccess::GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject)
{
    bool bRet = false;
    long lRet = SessionCheck();

    if(lRet > 0)
    {
        long lOwnerObjectId = 0;
        long lOwnerContainerId = 0;
        m_pCwnObjectAccess->GetOwner(p_pObject->GetObjectContainerId(), p_pObject->GetId(), lOwnerObjectId, lOwnerContainerId);

        p_pOwnerObject = GetObject(lOwnerContainerId, lOwnerObjectId);
        bRet = (p_pOwnerObject != nullptr);

    }

    return bRet;
}

CdmObject* CwnDataAccess::GetObject(long p_lContainerId, long p_lObjectId)
{
    CdmObject* pObject = nullptr;
    CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmContainerManager* pContainerManager = pDataProvider->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pObject = pContainerManager->FindObject(p_lContainerId, p_lObjectId);
        }
    }

    return pObject;
}

bool CwnDataAccess::GetReferences(const CdmObject* p_pObject, QList<CdmObject*> &p_rqmReferences)
{
    Q_UNUSED(p_rqmReferences);
    Q_UNUSED(p_pObject);

    bool bRet = false;
    long lRet = SessionCheck();

    if(lRet > 0)
    {
    }
    return bRet;
}

bool CwnDataAccess::GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject)
{
    bool bRet = false;
    long lRet = SessionCheck();

    if(lRet > 0)
    {
        long lOwnerObjectId = 0;
        long lOwnerContainerId = 0;
        m_pCwnObjectAccess->GetOwner(p_pContainer->GetId(), lOwnerObjectId, lOwnerContainerId);

        p_pOwnerObject = GetObject(lOwnerContainerId, lOwnerObjectId);
        bRet = (p_pOwnerObject != nullptr);
    }

    return bRet;
}

int CwnDataAccess::UpdateClass(CdmClass *&p_pCdmClass)
{
    long lRet=0;
    INFO("Data Access Call UpdateClass()");
    ++m_iInterfaceCallCounter;

    lRet = SessionCheck();

    if(lRet > 0)
    {
        if(CHKPTR(m_pCwnClassAccess))
        {
            lRet = m_pCwnClassAccess->UpdateClass(p_pCdmClass);
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    INFO("Data Access Call UpdateClass() finished");
    return static_cast<int>(lRet);
}

int CwnDataAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
{
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    //long lRet = BeginTransaction();
    long lRet = 1;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnClassAccess))
          {
              lRet = m_pCwnClassAccess->UpdatePackage(p_pCdmPackage);
          }
       }
    }
    return static_cast<int>(lRet);
}

void CwnDataAccess::SetServerMode(bool p_bServerMode)
{
    Q_UNUSED(p_bServerMode);
    NOTIMPLEMENTED;
    // not for neo4j
}

bool CwnDataAccess::IsInServerMode() const
{
    //not for neo4j
    NOTIMPLEMENTED;
    return false;
}

int CwnDataAccess::GetInterfaceCallCounter() const
{
    return m_iInterfaceCallCounter;
}

CdmObject *CwnDataAccess::CreateObject(CdmObjectContainer *p_pContainer)
{
    Q_UNUSED(p_pContainer);
    NOTIMPLEMENTED;
     return nullptr;
}

bool CwnDataAccess::LockClassMethod(long p_lMethodId)
{
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    long lRet =1;
    bool bSuccess=false;
    //BeginTransaction();

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnClassAccess))
          {
            bSuccess = m_pCwnClassAccess->LockMethod(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(),
                                                     static_cast<int>(p_lMethodId));
          }
       }
    }
    return bSuccess;
}

bool CwnDataAccess::UnlockClassMethod(long p_lMethodId)
{

    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    long lRet =1;
    bool bSuccess=false;

    if(lRet > 0)
    {
       lRet = SessionCheck();

       if(lRet > 0)
       {
          if(CHKPTR(m_pCwnClassAccess))
          {
             bSuccess = m_pCwnClassAccess->UnlockMethod(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(),
                                                        static_cast<int>(p_lMethodId));
          }
       }
    }
    return bSuccess;
}

void CwnDataAccess::StartTransaction()
{
    // not for neo4j
    NOTIMPLEMENTED;
}

void CwnDataAccess::CommitTransaction()
{
    // not for neo4j
    NOTIMPLEMENTED;
}

void CwnDataAccess::RollbackTransaction()
{
    // not for neo4j
    NOTIMPLEMENTED;
}

QVariant CwnDataAccess::ExecuteFunction(CdmObject *p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters)
{
    Q_UNUSED(p_PObject);
    Q_UNUSED(p_qstrFunctionName);
    Q_UNUSED(p_qvlParameters);
    // not for neo4j
    NOTIMPLEMENTED;
    return QVariant();
}

QVariant CwnDataAccess::EvaluateFormula(const CdmObject *p_pObject, QString p_qstrFormula)
{
    Q_UNUSED(p_pObject);
    Q_UNUSED(p_qstrFormula);
    // not for neo4j
    NOTIMPLEMENTED;
    return QVariant();
}

bool CwnDataAccess::GetRfcExecution() const
{
    NOTIMPLEMENTED;
    // not for neo4j
    return false;
}

void CwnDataAccess::PrintContainer(QString p_qstrTemplateName, CdmObjectContainer *p_pContainer)
{
    Q_UNUSED(p_qstrTemplateName);
    Q_UNUSED(p_pContainer);
    NOTIMPLEMENTED;
    // not for neo4j
}

void CwnDataAccess::PrintObject(QString p_qstrTemplateName, CdmObject *p_pObject)
{
    Q_UNUSED(p_qstrTemplateName);
    Q_UNUSED(p_pObject);
    NOTIMPLEMENTED;
    // not for neo4j
}
int CwnDataAccess::LoadRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName)
{
    Q_UNUSED(p_qstrIdFieldName);
    CwnCommandLoadRights rights(p_rCcdmRights,p_lObjectId,p_qstrTableName,this);
    return static_cast<int>(rights.Run());
}
int CwnDataAccess::SaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName, QString p_qstrIdFieldName)
{
    Q_UNUSED(p_qstrIdFieldName);
    CwnCommandSaveRights rights(p_rCcdmRights,p_lObjectId,p_qstrTableName);
    return static_cast<int>(rights.Run());
}
int CwnDataAccess::DeleteRights(long p_lObjectId,QString p_qstrTableName,QString p_qstrIdFieldName)
{
    Q_UNUSED(p_lObjectId);
    Q_UNUSED(p_qstrIdFieldName);
    Q_UNUSED(p_qstrTableName);
    NOTIMPLEMENTED;
    //Will be done by each delete of a scheme, objectContainer, class_group, class_method, class_member, user
    return 0;
}
QString CwnDataAccess::GetBoolAsString(bool p_bValue)
{
   QString qstrRet;

   if(!p_bValue)
   {
      qstrRet = "false";
   }
   else
   {
      qstrRet = "true";
   }

   return qstrRet;
}

CdmSession *CwnDataAccess::FindSession(int p_iSessionId)
{
    return m_pCwnLoginManager->FindSession(p_iSessionId);
}

CdmSession *CwnDataAccess::FindSession(QString p_qstrBaseAuth)
{
    return m_pCwnLoginManager->FindSession(p_qstrBaseAuth);
}

void CwnDataAccess::UpdateSession(int p_iSessionId)
{
    m_pCwnLoginManager->UpdateSession(p_iSessionId);
}

void CwnDataAccess::UpdateSession(QString p_qstrBaseAuth)
{
    m_pCwnLoginManager->UpdateSession(p_qstrBaseAuth);
}

void CwnDataAccess::SessionTimeoutCheck(int p_iTimeoutMin)
{
    m_pCwnLoginManager->SessionTimeoutCheck(p_iTimeoutMin);
}

QList<CumUser*> CwnDataAccess::FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    return m_pCwnUserManager->FindUser(p_qstrUserLoginNameEmail);
}

CumUser *CwnDataAccess::FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    return m_pCwnUserManager->FindUserByIdentKey(p_qstridentKey);
}
CwnJournal* CwnDataAccess::GetJournal()
{
   return m_pCwnJournal;
}

QString CwnDataAccess::GenerateInString(QList<long> &p_rqvlIds)
{
   QString qstrRet = "[";

   QList<long>::iterator qvlIt = p_rqvlIds.begin();
   QList<long>::iterator qvlItEnd = p_rqvlIds.end();

   while (qvlIt != qvlItEnd)
   {
      QString qstrId = QString::number(*qvlIt);
      qstrRet += qstrId;

      ++ qvlIt;

      if (qvlIt != qvlItEnd)
      {
         qstrRet += ", ";
      }
      else
      {
         qstrRet += "]";
         break;
      }
   }

   return qstrRet;
}

CumUserGroup* CwnDataAccess::FindUserGroupById(int p_iId)
{
    return m_pCwnUserManager->FindUserGroupById(p_iId);
}

CumUserGroup* CwnDataAccess::FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    return m_pCwnUserManager->FindUserGroupByName(p_qstrName);
}

QList<CumUserGroup *> CwnDataAccess::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    Q_UNUSED(p_qstrSchemeUri);
    Q_UNUSED(p_qstrName);
    QList<CumUserGroup *> qllGroups;
    NOTIMPLEMENTED;
    return qllGroups;
}

int CwnDataAccess::LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject)
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    lRet = SessionCheck();

    if(lRet > 0)
    {
       if(CHKPTR(m_pCwnObjectAccess))
       {
           m_pCwnObjectAccess->LoadObject(p_pContainer->GetId(), p_qstrKeyname, p_pCdmObject);
       }
    }

    return lRet;
}
