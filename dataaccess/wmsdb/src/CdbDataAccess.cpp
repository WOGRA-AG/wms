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
#include <QLinkedList>

#ifdef WIN32
#include <CdmValueCounter.h>
#include <qt_windows.h>
#else
#include <unistd.h>
#endif //

// own Includes
#include "CumUserGroup.h"
#include "CumUser.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmModelElement.h"
#include "CdmDataProvider.h"
#include "CdmSettings.h"
#include "CdmJournalItem.h"
#include "CdmValue.h"
#include "CdmSessionManager.h"
#include "CdbDbAccess.h"
#include "CdbUserManager.h"
#include "CdbLoginManager.h"
#include "CdbClassAccess.h"
#include "CdbObjectAccess.h"
#include "CdbJournal.h"
#include "CdbDataAccess.h"

#define KEEP_ALIVE_INTERVALL_MINUTES 5

CdbDataAccess::CdbDataAccess(  )
    : QObject(nullptr),
      m_pCdbUserManager(nullptr),
      m_pCdbLoginManager(nullptr),
      m_pCdbDbAccess(nullptr),
      m_pCdbObjectAccess(nullptr),
      m_pCdbClassAccess(nullptr),
      m_pCdbJournal(nullptr),
      m_iQueryCountGlobal(0),
      m_iQueryCountSuccess(0),
      m_iMsecsSum(0),
      m_bServerMode(false),
      m_iInterfaceCallCounter(0)
{
}

CdbDataAccess::~CdbDataAccess(  )
{
    DELPTR(m_pCdbDbAccess);
    DELPTR(m_pCdbUserManager);
    DELPTR(m_pCdbLoginManager);
    DELPTR(m_pCdbObjectAccess);
    DELPTR(m_pCdbClassAccess);
    DELPTR(m_pCdbJournal);
}

int CdbDataAccess::Init(CdbDataAccessConfigurator* p_pConfig)
{
    m_rpConfig = p_pConfig;
    m_pCdbDbAccess     = new CdbSchemeAccess(this);
    m_pCdbUserManager  = new CdbUserManager(this);
    m_pCdbLoginManager = new CdbLoginManager(this, m_pCdbUserManager);
    m_pCdbObjectAccess = new CdbObjectAccess(this);
    m_pCdbClassAccess  = new CdbClassAccess(this);
    m_pCdbJournal = new CdbJournal(this);
    return EC(eDmOk);
}

int CdbDataAccess::GetInterfaceCallCounter() const
{
    return m_iInterfaceCallCounter;
}

void CdbDataAccess::SetServerMode(bool p_bServerMode)
{
    m_bServerMode = p_bServerMode;
}

bool CdbDataAccess::IsInServerMode() const
{
    return m_bServerMode;
}

CdbJournal* CdbDataAccess::GetJournal()
{
    return m_pCdbJournal;
}

int CdbDataAccess::GetQueryCount()
{
    return m_iQueryCountGlobal;
}

int CdbDataAccess::GetSuccessfullQueryCount()
{
    return m_iQueryCountSuccess;
}

CdbInterface* CdbDataAccess::GetDbInterface()
{
    CdbInterface* pInterface = nullptr;
    QThread* pThread = QThread::currentThread();

    if (pThread != nullptr)
    {
        qint64 lThreadPtr = reinterpret_cast<qint64> (pThread);
        QMutexLocker locker(&m_qMutex);
        if (m_qmConnections.contains(lThreadPtr))
        {
            pInterface = m_qmConnections[lThreadPtr];
            INFO("DB Interface found for Thread. ");
        }
        else
        {
            if (CHKPTR(m_rpConfig))
            {
                QString qstrThreadId = QString::number(lThreadPtr);
                INFO("Create new DB interface for Thread.");
                pInterface = new CdbInterface(qstrThreadId);
                pInterface->Init(*m_rpConfig);
                m_qmConnections.insert(lThreadPtr, pInterface);
            }
        }
    }

    return pInterface;
}

long CdbDataAccess::ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CdbInterface* pInterface = GetDbInterface();

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

long CdbDataAccess::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CdbInterface* pInterface = GetDbInterface();

    if (CHKPTR(pInterface))
    {
        lRet = pInterface->ExecuteQuery(p_rqsqlQuery);
    }
    else
    {
        FATAL("DB connection not established. Execution of Query failed");
    }

    return lRet;
}



QLinkedList<CumUserGroup*> CdbDataAccess::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    QLinkedList<CumUserGroup*> qllGroups;
    qllGroups = m_pCdbUserManager->FindUserGroups(p_qstrName, p_qstrSchemeUri);
    return qllGroups;
}

int CdbDataAccess::LoadObject(const CdmObjectContainer* p_pContainer, QString p_qstrKeyname, CdmObject *&p_pCdmObject)
{
    return m_pCdbObjectAccess->LoadObject(p_pContainer->GetId(), p_qstrKeyname, p_pCdmObject);
}

CdbDataAccess::EodbcBaseType CdbDataAccess::ConvertValueType(EdmValueType p_eValue)
{
    switch (p_eValue)
    {
    case eDmValueNone:
    case eDmValueBool:
            return eOdbcBool;
    case eDmValueInt:
            return eOdbcInt;
    case eDmValueLong:
            return eOdbcLong;
    case eDmValueFloat:
            return eOdbcFloat;
    case eDmValueDouble:
            return eOdbcDouble;
    case eDmValueString:
            return eOdbcString;
    case eDmValueDate:
            return eOdbcDate;
    case eDmValueTime:
            return eOdbcTime;
    case eDmValueDateTime:
            return eOdbcDateTime;
    case eDmValueObjectRef:
            return eOdbcObjRef;
    case eDmValueContainerRef:
            return eOdbcObjListRef;
    case eDmValueCounter:
            return eOdbcCounter;
    case eDmValueBinaryDocument:
            return eOdbcBinDoc;
    case eDmValueCharacterDocument:
            return eOdbcCharDoc;
    case eDmValueListInt:
            return eOdbcListInt;
    case eDmValueListDouble:
            return eOdbcListDouble;
    case eDmValueListString:
            return eOdbcListString;
    case eDmValueDictStringInt:
            return eOdbcDictStringInt;
    case eDmValueDictStringString:
            return eOdbcDictStringString;
    case eDmValueDictStringDouble:
            return eOdbcDictStringDouble;
    case eDmValueDictIntInt:
            return eOdbcDictIntInt;
    case eDmValueDictIntString:
            return eOdbcDictIntString;
    case eDmValueDictIntDouble:
            return eODbcDictIntDouble;
    case eDmValueListObjects:
            return eOdbcListObjects;
    case eDmValueFormula:
            return eOdbcFormula;
    case eDmValueUser:
            return eOdbcUser;
    case eDmValueEnum:
            return eOdbcEnum;
    case eDmValueUserGroup:
            return eOdbcUserGroup;
    default:
            return eOdbcNone;
    }
}

int CdbDataAccess::LoadObjects(QLinkedList<long>& p_rqvlObjects, CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadObjects()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->LoadObjects(p_pContainer, p_rqvlObjects);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjects() Finished");
    return lRet;
}

long CdbDataAccess::IsObjectUsed(const CdmObject* p_pObject)
{
    INFO("Data Access Call IsObjectUsed()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess) && CHKPTR(p_pObject))
    {
        lRet = m_pCdbObjectAccess->IsObjectUsed(p_pObject->GetId(), p_pObject->GetObjectContainerId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call IsObjectUsed() Finished");
    return lRet;
}

int CdbDataAccess::LoadObject(const CdmObjectContainer* p_pContainer,
                              long p_lObjectId,
                              CdmObject*& p_pCdmObject)
{
    INFO("Data Access Call LoadObject()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess) && CHKPTR(p_pContainer))
    {
        lRet = m_pCdbObjectAccess->LoadObject(p_pContainer->GetId(), p_lObjectId, p_pCdmObject);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObject() Finished");
    return lRet;
}

int CdbDataAccess::LoadObjectContainer(long p_lObjectListId, CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->LoadContainer(p_lObjectListId, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObject() finished");
    return lRet;
}

int CdbDataAccess::LoadObjectContainer(long p_lDatabaseId,
                                       QString p_qstrKeyname,
                                       CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->LoadContainer(p_lDatabaseId, p_qstrKeyname, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CdbDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId,
                                            QString p_qstrKeyname,
                                            CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->LoadEmptyObjectList(p_lDataBaseId, p_qstrKeyname, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CdbDataAccess::LoadEmptyObjectContainer(long p_lDataBaseId,
                                            long p_lId,
                                            CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call LoadEmptyObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->LoadEmptyObjectList(p_lDataBaseId, p_lId, p_pContainer);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CdbDataAccess::GetNewContainerId(long p_lClassId)
{
    INFO("Data Access Call GetNewObjectListId()");

    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->GetNewObjectListId(p_lClassId, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CdbDataAccess::GetNewClassId(long p_lDbId)
{
    INFO("Data Access Call GetNewClassId()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->GetNewClassId(p_lDbId, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

long CdbDataAccess::GetNewObjectId(const CdmObjectContainer* p_pContainer)
{
    INFO("Data Access Call GetNewObjectId()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->GetNewObjectId(p_pContainer->GetId(), CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CdbDataAccess::UpdateObject(CdmObject*& p_pCdmObject)
{
    INFO("Data Access Call UpdateObject()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->UpdateObject(p_pCdmObject, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadObjectList() finished");
    return lRet;
}

int CdbDataAccess::UpdateObjectContainer(CdmObjectContainer*& p_pContainer)
{
    INFO("Data Access Call UpdateObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->UpdateObjectList(p_pContainer, CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateObjectList() finished");
    return lRet;
}

int CdbDataAccess::CreateScheme(QString p_qstrKeyname,
                                CdmScheme*& p_pCdmDatabaseManager)
{
    INFO("Data Access Call CreateDb()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbDbAccess))
    {
        lRet = m_pCdbDbAccess->CreateScheme(p_qstrKeyname, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateDb() finished");
    return lRet;
}

int CdbDataAccess::LoadSchemeBaseData(QString p_qstrKeyname,
                                      CdmScheme*& p_pCdmDatabaseManager )
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbDbAccess))
    {
        lRet = m_pCdbDbAccess->FindScheme(p_qstrKeyname, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return lRet;
}

int CdbDataAccess::LoadSchemeBaseData(long p_lDb, CdmScheme *&p_pCdmDatabaseManager)
{
    INFO("Data Access Call LoadDbBaseData()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbDbAccess))
    {
        lRet = m_pCdbDbAccess->FindScheme(p_lDb, p_pCdmDatabaseManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadDbBaseData() finished");
    return lRet;
}

int CdbDataAccess::IsDemo(QString p_qstrApplication, QString p_qstrVersion)
{
    int iRet = 0;
    bool bDemo = false;
    int p_iModules = 0;
    QString qstrVersion;
    m_pCdbLoginManager->LicenceCheck(p_qstrApplication, bDemo, p_iModules, qstrVersion);

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

bool CdbDataAccess::LicenceCheck(QString p_qstrApplication,
                                 bool& p_bDemo,
                                 int& p_iModules,
                                 QString p_qstrVersion)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    bool bRet = false;

    if(CHKPTR(m_pCdbLoginManager))
    {
        bRet = m_pCdbLoginManager->LicenceCheck(p_qstrApplication, p_bDemo, p_iModules, p_qstrVersion);
    }

    return bRet;
}

int CdbDataAccess::Login(QString p_qstrApplication,
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
    long lRet =0;

    if(CHKPTR(m_pCdbLoginManager))
    {
        p_lSessionId = m_pCdbLoginManager->Login(p_qstrApplication,
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

int CdbDataAccess::Logout()
{
    INFO("Data Access Call LogOut()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbLoginManager))
    {
        lRet = m_pCdbLoginManager->Logout(CdmSessionManager::GetSessionManager()->GetCurrentSessionId());
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LogOut() finished. SessionId");
    return lRet;
}

int CdbDataAccess::CreateUser(CumUser* p_pUser)
{
    INFO("Data Access Call CreateUser()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if (m_pCdbUserManager)
    {
        lRet = m_pCdbUserManager->CreateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateUser() finished");
    return lRet;
}

int CdbDataAccess::RegisterUser(CumUser* p_pUser)
{
    INFO("Data Access Call CreateUser()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if (m_pCdbUserManager)
    {
        lRet = m_pCdbUserManager->CreateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateUser() finished");
    return lRet;
}

int CdbDataAccess::DeleteUser(QString p_qstrLogin)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->DeleteUser(p_qstrLogin);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteUser() finished");
    return lRet;
}

int CdbDataAccess::DeleteUser(long p_lUserToDeleteId)
{
    INFO("Data Access Call DeleteUser()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->DeleteUser(p_lUserToDeleteId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteUser() finished");
    return lRet;
}

CdmSession *CdbDataAccess::FindSession(int p_iSessionId)
{
    return m_pCdbLoginManager->FindSession(p_iSessionId);
}

CdmSession *CdbDataAccess::FindSession(QString p_qstrBaseAuth)
{
    return m_pCdbLoginManager->FindSession(p_qstrBaseAuth);
}

int CdbDataAccess::LoadClassManager(long p_SchemeId,
                                    CdmClassManager*& p_pCdmClassManager)
{
    INFO("Data Access Call LoadClassManager()");

    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->LoadClassManager(p_SchemeId, p_pCdmClassManager);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LoadClassManager() finsihed");
    return lRet;
}

int CdbDataAccess::UpdateClass(CdmClass*& p_pCdmClass)
{
    INFO("Data Access Call UpdateClass()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->UpdateClass(p_pCdmClass);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateClass() finished");
    return lRet;
}

int CdbDataAccess::DeleteClass(long p_lClassId)
{
    INFO("Data Access Call DeleteClass()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->DeleteClass(p_lClassId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteClass() finished");
    return lRet;
}

int CdbDataAccess::DeleteScheme(QString p_qstrKeyname)
{
    INFO("Data Access Call DeleteDb()")
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if (CHKPTR(m_pCdbDbAccess))
    {
        lRet = m_pCdbDbAccess->DeleteDb(p_qstrKeyname);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteDb() finished")
    return lRet;
}

int CdbDataAccess::DeleteObjectContainer(long p_lObjectListId)
{
    INFO("Data Access Call DeleteObjectList()")
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->DeleteObjectList(p_lObjectListId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteObjectList() finished")
    return lRet;
}

int CdbDataAccess::GetUserList(QLinkedList<CumUser*>& p_rqvlUser)
{
    INFO("Data Access Call GetUserList()")
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (m_pCdbUserManager)
    {
        lRet = m_pCdbUserManager->GetUserList(p_rqvlUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetUserList() finished")
    return lRet;
}

int CdbDataAccess::UpdateUser(CumUser* p_pUser)
{

    INFO("Data Access Call UpdateUser()")
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if (m_pCdbUserManager)
    {
        lRet = m_pCdbUserManager->UpdateUser(p_pUser);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateUser() finished")
    return lRet;
}

int CdbDataAccess::GetContainerList(long p_lDbId,
                                    long p_lClassId,
                                    QMap<long, QString>& p_rqmObjectListsLList)
{
    INFO("Data Access Call GetObjectListsList()")
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->GetObjectListsList(p_lDbId, p_lClassId, p_rqmObjectListsLList);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetObjectListsList() finished")
    return lRet;
}

int CdbDataAccess::ExecuteQuery(CdmQuery* p_pCdmQuery)
{
    INFO("Data Access Call ExecuteQuery()")
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->ExecuteQuery(p_pCdmQuery);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExecuteQuery() finished")
    return lRet;
}

int CdbDataAccess::ExistScheme(QString p_qstrKeyname, bool& p_bResult)
{
    INFO("Data Access Call ExistDb()")
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if (CHKPTR(m_pCdbDbAccess))
    {
        lRet = m_pCdbDbAccess->ExistDb(p_qstrKeyname, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistDb() finished")
    return lRet;
}

int CdbDataAccess::ExistClass(long p_lDbId, QString p_qstrClassKeyname, bool & p_bResult)
{
    INFO("Data Access Call ExistClass()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->ExistClass(p_lDbId, p_qstrClassKeyname, p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistClass() finished");
    return lRet;
}

int CdbDataAccess::ExistObjectContainer(long p_lDbId, QString p_qstrObjectListKeyname)
{
    INFO("Data Access Call ExistObjectList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->ExistObjectList(p_lDbId, p_qstrObjectListKeyname);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call ExistObjectList() finished");
    return lRet;
}

int CdbDataAccess::LockObject(CdmObject* p_pObject, bool & p_bResult)
{
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess) && CHKPTR(p_pObject))
    {
        lRet = m_pCdbObjectAccess->LockObject(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(), p_pObject->GetId(), p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call LockObject() finished");
    return lRet;
}

int CdbDataAccess::UnLockObject(CdmObject* p_pObject, bool & p_bResult)
{
    INFO("Data Access Call UnLockObject()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->UnLockObject(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(), p_pObject->GetId(), p_bResult);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UnLockObject() finished");
    return lRet;
}

QByteArray CdbDataAccess::ReadBinaryDocument(long p_lSchemeId,
                                             CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
    INFO("Data Access Call ReadBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lSchemeId)
    QByteArray qbaResult;

    if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCdbObjectAccess))
    {
        qbaResult = m_pCdbObjectAccess->ReadBinaryDocument(p_pCdmBinaryDocument);
    }

    INFO("Data Access Call ReadBinaryDocument() finished");
    return qbaResult;
}

int CdbDataAccess::UpdateBinaryDocument(long p_lSchemeId, CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
    INFO("Data Access Call UpdateBinaryDocument()");
    ++m_iInterfaceCallCounter;
    Q_UNUSED(p_lSchemeId)
    long lRet =0;

    if(CHKPTR(p_pCdmBinaryDocument) && CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->UpdateBinaryDocument(p_pCdmBinaryDocument);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateBinaryDocument() finished");
    return lRet;
}

long CdbDataAccess::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    INFO("Data Access Call RenameUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->RenameUserGroup(p_lGroupId, p_qstrNewName);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call RenameUserGroup() finished");
    return lRet;
}

long CdbDataAccess::CreateUserGroup(QString p_qstrGroupName)
{
    INFO("Data Access Call CreateUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->CreateUserGroup(p_qstrGroupName);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call CreateUserGroup() finished");
    return lRet;
}

long CdbDataAccess::DeleteUserGroup(long p_llGroupId)
{
    INFO("Data Access Call DeleteUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->DeleteUserGroup(p_llGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call DeleteUserGroup() finished");
    return lRet;
}

long CdbDataAccess::AddUserToUserGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call AddUserToUserGroup()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->AddUserToUserGroup(p_lChangeUserId, p_lUserGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call AddUserToUserGroup() finished");
    return lRet;
}

long CdbDataAccess::RemoveUserFromGroup(long p_lChangeUserId, long p_lUserGroupId)
{
    INFO("Data Access Call RemoveUserFromGroup()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->RemoveUserFromGroup(p_lChangeUserId, p_lUserGroupId);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call RemoveUserFromGroup() finished");
    return lRet;
}

long CdbDataAccess::GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri)
{
    INFO("Data Access Call GetUserGroupList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->GetUserGroupList(p_rqvlUserGroups, p_qstrSchemeUri);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetUserGroupList() finished");
    return lRet;
}

CumUserGroup* CdbDataAccess::FindUserGroupById(int p_iId)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUserGroupById(p_iId);
}

CumUserGroup* CdbDataAccess::FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUserGroupByName(p_qstrName, p_qstrSchemeUri);
}

long CdbDataAccess::GetListOfUsersInList(long p_lUserGroupId, QLinkedList<CumUser*>& p_rqvlUserList)
{
    INFO("Data Access Call GetListOfUsersInList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->GetListOfUsersInList(p_lUserGroupId, p_rqvlUserList);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetListOfUsersInList() finished");
    return lRet;
}

long CdbDataAccess::GetUserGroupMemberList(long p_lChangeUserId, QLinkedList<CumUserGroup*>& p_qvlUserGroups)
{
    INFO("Data Access Call GetUserGroupMemberList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;
    if(CHKPTR(m_pCdbUserManager))
    {
        lRet = m_pCdbUserManager->GetUserGroupMemberList(p_lChangeUserId, p_qvlUserGroups);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetUserGroupMemberList() finished");
    return lRet;
}

long CdbDataAccess::AddLicense(QString p_qstrApplication, QString p_qstrLicensee, QString p_qstrLicensekey)
{
    Q_UNUSED(p_qstrApplication);
    Q_UNUSED(p_qstrLicensee);
    Q_UNUSED(p_qstrLicensekey);
    NOTIMPLEMENTED;
    return -1;
}

long CdbDataAccess::FreeLicense()
{
    NOTIMPLEMENTED;
    return -1;
}

long CdbDataAccess::GetSchemeList(QLinkedList<QString>& p_qvlDatabases)
{
    INFO("Data Access Call GetDatbaseList()");
    ++m_iInterfaceCallCounter;
    long lRet = 0;

    if(CHKPTR(m_pCdbDbAccess))
    {
        m_pCdbDbAccess->GetDatabaseList(p_qvlDatabases);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call GetDatbaseList() finished");
    return lRet;
}

long CdbDataAccess::UpdateScheme(CdmScheme* p_pCdmDatabase)
{
    INFO("Data Access Call UpdateDatabase()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbDbAccess) && CHKPTR(p_pCdmDatabase))
    {
        lRet = m_pCdbDbAccess->UpdateDatabase(p_pCdmDatabase);
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    INFO("Data Access Call UpdateDatabase() finished");
    return lRet;
}

long CdbDataAccess::GetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue)
{
    Q_UNUSED(p_pContainer)
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->GetCounterValue(dynamic_cast<CdmValueCounter*>(p_pValue));
    }

    INFO("Data Access Call GetCounterValue() finished");
    return lRet;
}

QString CdbDataAccess::GetConnectionDisplayString()
{
    QString qstrConnection;
    CdbInterface* pInterface = GetDbInterface();

    if (pInterface)
    {
        qstrConnection = pInterface->GetConnectionDisplayString();
    }

    return qstrConnection;
}

bool CdbDataAccess::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
{
    return m_pCdbUserManager->CheckAuthorisationAdmin(p_qstrLogin, p_qstrPassword);
}

bool CdbDataAccess::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
{
    return m_pCdbUserManager->CheckAuthorisation(p_qstrLogin, p_qstrPassword);
}

CumUser* CdbDataAccess::FindUserById(int p_iId)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUser(p_iId);
}

CumUser* CdbDataAccess::FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUserByEmail(p_qstrEmail, p_qstrSchemeUri);
}

CumUser* CdbDataAccess::FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUserByLogin(p_qstrLogin, p_qstrSchemeUri);
}

CumUser* CdbDataAccess::FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri)
{
    ++m_iInterfaceCallCounter;
    return m_pCdbUserManager->FindUser(p_qstrLogin, p_qstrPassword, p_qstrSchemeUri);
}

int CdbDataAccess::LoginLdap(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword, long& p_lSessionId, CumUser*& p_rUser)
{
    INFO("Data Access Call LogIn()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbLoginManager))
    {
        p_lSessionId = m_pCdbLoginManager->LoginLdap(p_qstrApplication,
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

int CdbDataAccess::UpdatePackage(CdmPackage *&p_pCdmPackage)
{
    INFO("Data Access Call GetCounterValue()");
    ++m_iInterfaceCallCounter;
    long lRet =0;

    if(CHKPTR(m_pCdbClassAccess))
    {
        lRet = m_pCdbClassAccess->UpdatePackage(p_pCdmPackage);
    }

    return lRet;
}

long CdbDataAccess::RefreshObject(CdmObject* p_pCdmObject)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("RefreshObject Call");

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->RefreshObject(p_pCdmObject);
    }

    INFO("RefreshObject Call finished");
    return lRet;
}

long CdbDataAccess::RefreshObjectContainer(CdmObjectContainer* p_pCdmObject)
{
    long lRet = -1;
    INFO("RefreshObjectList Call");
    ++m_iInterfaceCallCounter;

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->RefreshObjectList(p_pCdmObject);
    }

    INFO("RefreshObjectList Call finished");
    return lRet;
}

long CdbDataAccess::CountObjectsOnDb(CdmObjectContainer* p_pCdmObject)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("CountObjectOnDb Call");

    if(CHKPTR(m_pCdbObjectAccess))
    {
        lRet = m_pCdbObjectAccess->CountObjectsOnDb(p_pCdmObject);
    }

    return lRet;
}

int CdbDataAccess::DeleteRights(long p_lObjectId,
                                QString p_qstrTableName,
                                QString p_qstrIdFieldName)
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    CdbInterface* pInterface = GetDbInterface();
    pInterface->BeginTransaction();
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
        pInterface->Commit();
    }
    else
    {
        pInterface->Rollback();
    }

    return iRet;
}

int CdbDataAccess::SaveRights(CdmRights& p_rCcdmRights,
                              long p_lObjectId,
                              QString p_qstrTableName,
                              QString p_qstrIdFieldName)
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;
    CdbInterface* pInterface = GetDbInterface();
    pInterface->BeginTransaction();


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
                int iUserBaseId = 0;
                QString qstrInsert;
                QString qstrUri = qvIt.key();
                CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

                if (CHKPTR(pManager))
                {
                    CdmLocatedElement* pElement = pManager->GetUriObject(qstrUri);

                    if (pElement)
                    {
                        if (pElement->IsUser() || pElement->IsUserGroup())
                        {
                            iUserBaseId = static_cast<CumAccessor*> (pElement)->GetId();
                        }
                        else
                        {
                            ERR("Wrong URI Type");
                        }
                    }
                    else
                    {
                        ERR("Unknown Element:" + qstrUri);
                        continue;
                    }
                }

                QSqlQuery cQuery;
                qstrInsert = QString("insert into %1 (%2, UserBaseId, RightId) values (%3, %4, %5)")
                        .arg(p_qstrTableName)
                        .arg(p_qstrIdFieldName)
                        .arg(p_lObjectId)
                        .arg(iUserBaseId)
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
        pInterface->Commit();
    }
    else
    {
        pInterface->Rollback();
    }

    return iRet;
}

int CdbDataAccess::LoadRights(CdmRights& p_rCcdmRights,
                              long p_lObjectId,
                              QString p_qstrTableName,
                              QString p_qstrIdFieldName)
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
                EdmRight eDmRight = (EdmRight)cQuery.value(1).toInt();
                p_rCcdmRights.AddRight(iUserBaseId, eDmRight);
            }
            while(cQuery.next());
        }
    }

    return iRet;
}

int CdbDataAccess::DeleteLanguage(long p_lDatabaseId, int p_iLanguageId)
{
    long lRet = -1;
    CdbInterface* pInterface = GetDbInterface();
    pInterface->BeginTransaction();

    ++m_iInterfaceCallCounter;
    INFO("Delete Language Call");

    lRet = m_pCdbDbAccess->DeleteLanguage(p_lDatabaseId, p_iLanguageId);

    if (lRet > 0)
    {
        pInterface->Commit();
    }
    else
    {
        pInterface->Rollback();
    }

    return lRet;
}

int CdbDataAccess::AddLanguage(long p_lDatabaseId, QString p_qstrLanguage)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("AddLanguage Call");
    lRet = m_pCdbDbAccess->AddLanguage(p_lDatabaseId, p_qstrLanguage);
    return lRet;
}


int CdbDataAccess::GetSchemeModifications(long p_lDatabaseId,
                                            QDate p_qdFrom,
                                            QDate p_qdTo,
                                            QList<CdmJournalItem*>& p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetDatabaseModifications Call");
    lRet = m_pCdbJournal->GetDatabaseModifications(p_lDatabaseId, p_qdFrom, p_qdTo, p_qlItems);
    return lRet;
}

int CdbDataAccess::GetObjectContainerModifications(const CdmObjectContainer* p_pContainer,
                                                   QDate p_qdFrom,
                                                   QDate p_qdTo,
                                                   QList<CdmJournalItem*>& p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetObjectListModifications Call");
    lRet = m_pCdbJournal->GetContainerModifications(p_pContainer->GetId(), p_qdFrom, p_qdTo, p_qlItems);
    return lRet;
}

int CdbDataAccess::GetObjectModifications(const CdmObject* p_pObject,
                                          QDate p_qdFrom,
                                          QDate p_qdTo,
                                          QList<CdmJournalItem*>& p_qlItems)
{
    long lRet = -1;
    ++m_iInterfaceCallCounter;
    INFO("GetObjectModifications Call");
    lRet = m_pCdbJournal->GetObjectModifications(p_pObject->GetId(), p_qdFrom, p_qdTo, p_qlItems);
    return lRet;
}

bool CdbDataAccess::GetOwner(const CdmObject* p_pObject, CdmObject*& p_pOwnerObject)
{
    bool bRet = false;
    long lOwnerContainerId = 0;
    long lOwnerObjectId = 0;
    bRet = m_pCdbObjectAccess->GetOwner(p_pObject->GetObjectContainerId(), p_pObject->GetId(), lOwnerContainerId, lOwnerObjectId);

    if (bRet)
    {
        p_pOwnerObject = GetObject(lOwnerContainerId, lOwnerObjectId);
    }

    return bRet;
}

CdmObject* CdbDataAccess::GetObject(long p_lContainerId, long p_lObjectId)
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

bool CdbDataAccess::GetOwner(const CdmObjectContainer* p_pContainer, CdmObject*& p_pOwnerObject)
{
    bool bRet = false;
    long lOwnerContainerId = 0;
    long lOwnerObjectId = 0;
    bRet = m_pCdbObjectAccess->GetOwner(p_pContainer->GetId(), lOwnerContainerId, lOwnerObjectId);

    if (bRet)
    {
        p_pOwnerObject = GetObject(lOwnerContainerId, lOwnerObjectId);
    }

    return bRet;
}

bool CdbDataAccess::GetReferences(const CdmObject* p_pObject,
                                  QList<CdmObject*>& p_rqmReferences)
{
    Q_UNUSED(p_rqmReferences);
    Q_UNUSED(p_pObject);

    bool bRet = false;
    NOTIMPLEMENTED;
    return bRet;
}

CdmObject* CdbDataAccess::CreateObject(CdmObjectContainer* p_pContainer)
{
    Q_UNUSED(p_pContainer);
    // only implemented for webclient
    NOTIMPLEMENTED;
    return nullptr;
}

int CdbDataAccess::Init(QString p_qstrApplicationName, QString p_qstrVersion)
{
    Q_UNUSED(p_qstrApplicationName);
    Q_UNUSED(p_qstrVersion);
    return 0;
}

void CdbDataAccess::CreateDatabase(EdbSupportedDatabase database)
{
    QString qstrSQLFile = ":/sql/";

    switch (database)
    {
    case eDbSupportedDatabaseMySQL:
        qstrSQLFile += "mysql";
        break;
    case eDbSupportedDatabasePostgreSQL:
        qstrSQLFile += "postgresql";
        break;
    case eDbSupportedDatabaseOracle:
        qstrSQLFile += "oracle";
        break;
    }

    qstrSQLFile += "-create-script.sql";
    CdbInterface* pInterface = GetDbInterface();
    pInterface->BeginTransaction();
    CreateDatabase(qstrSQLFile);
    pInterface->Commit();
}

void CdbDataAccess::CreateDatabase(QString p_qstrFilename)
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


bool CdbDataAccess::LockClassMethod(long p_lMethodId)
{
    bool bSuccess = false;
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;

    if(CHKPTR(m_pCdbClassAccess))
    {
        bSuccess = m_pCdbClassAccess->LockMethod(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(), p_lMethodId);
    }


    return bSuccess;
}

bool CdbDataAccess::UnlockClassMethod(long p_lMethodId)
{
    bool bSuccess = false;
    INFO("Data Access Call LockObject()");
    ++m_iInterfaceCallCounter;

    if(CHKPTR(m_pCdbClassAccess))
    {
        bSuccess = m_pCdbClassAccess->UnlockMethod(CdmSessionManager::GetSessionManager()->GetCurrentSessionId(), p_lMethodId);
    }

    return bSuccess;
}

QVariant CdbDataAccess::ExecuteFunction(CdmObject* p_PObject, QString p_qstrFunctionName, QVariantList p_qvlParameters)
{
    Q_UNUSED(p_PObject);
    Q_UNUSED(p_qstrFunctionName);
    Q_UNUSED(p_qvlParameters);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
    return QVariant();
}

QVariant CdbDataAccess::EvaluateFormula(const CdmObject* p_pObject, QString p_qstrFormula)
{
    Q_UNUSED(p_pObject);
    Q_UNUSED(p_qstrFormula);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
    return QVariant();
}

void CdbDataAccess::PrintObject(QString p_qstrTemplateName, CdmObject* p_pObject)
{
    Q_UNUSED(p_pObject);
    Q_UNUSED(p_qstrTemplateName);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
}

void CdbDataAccess::PrintContainer(QString p_qstrTemplateName, CdmObjectContainer* p_pContainer)
{
    Q_UNUSED(p_pContainer);
    Q_UNUSED(p_qstrTemplateName);
    ERR("This call is not allowed for direct DB Access");
    NOTIMPLEMENTED;
}

void CdbDataAccess::UpdateSession(int p_iSessionId)
{
    m_pCdbLoginManager->UpdateSession(p_iSessionId);
}

void CdbDataAccess::UpdateSession(QString p_qstrBaseAuth)
{
    m_pCdbLoginManager->UpdateSession(p_qstrBaseAuth);
}

void CdbDataAccess::SessionTimeoutCheck(int p_iTimeoutMin)
{
    m_pCdbLoginManager->SessionTimeoutCheck(p_iTimeoutMin);
}

CumUser *CdbDataAccess::FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri)
{
    return m_pCdbUserManager->FindUserByIdentKey(p_qstridentKey, p_qstrSchemeUri);
}

QLinkedList<CumUser*> CdbDataAccess::FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri)
{
    return m_pCdbUserManager->FindUser(p_qstrUserLoginNameEmail, p_qstrSchemeUri);
}
