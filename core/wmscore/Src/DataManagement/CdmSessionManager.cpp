/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmSessionManager.cpp
 ** Started Implementation: 2012/04/03
 ** Description:
 **
 ** Implements the factory for the manager objects
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QThreadPool>
#include <QtQml>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QPluginLoader>
#include <CumUser.h>

//WMS Utilities
#include "CwmsUtilities.h"
#include "wmsdefines.h"

// own Includes
#include "CdmExecutorAddOnManager.h"
#include "CdmLogging.h"
#include "CdmDataAccessConfiguration.h"
#include "CdmSession.h"
#include "IdmDataAccess.h"
#include "IwmsDataAccessPlugin.h"
#include "CdmSettings.h"
#include "CdmExecutor.h"
#include "CdmGlobalContext.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

CdmSessionManager* CdmSessionManager::m_spSessionManager = nullptr;

CdmSessionManager::CdmSessionManager(EdmSettingsMode p_eMode)
    : m_bServerMode(false),
      m_iSessionTimeoutMinutes(120),
      m_iSessionTimeoutIntervallmsecs(m_iSessionTimeoutMinutes* 1000 * 60 +100),
      m_pAddOnManager(nullptr),
      m_bPerSessionManager(true),
      m_pGlobalContext(nullptr),
      m_bCollectSessionGarbage(false),
      m_pDataAccess(nullptr)
{

    m_pAddOnManager = new CdmExecutorAddOnManager();
    m_pGlobalContext = new CdmGlobalContext(p_eMode);
    m_qdtLastSessionCheck = QDateTime::currentDateTime();
}

CdmSessionManager::~CdmSessionManager()
{
    DELPTR(m_pAddOnManager);
    DELPTR(m_pDataAccess);
}

void CdmSessionManager::SetSessionThread(int p_iSession)
{
    SYNCHRONIZED;

    if (p_iSession == 0)
    {
        SetThreadSessionId(0);
    }
    else
    {
        if (m_qmSessionManager.contains(p_iSession))
        {
            SetThreadSessionId(p_iSession);
        }
        else if (FindSessionById(p_iSession))
        {
            SetThreadSessionId(p_iSession);
        }
        else
        {
            SetThreadSessionId(0);
        }
    }
}

void CdmSessionManager::SetSessionThread(QString p_qstrBasicAuth)
{
    SYNCHRONIZED;

    if (m_qmSessionManagerAuth.contains(p_qstrBasicAuth))
    {
        SetThreadBaseAuth(p_qstrBasicAuth);
    }
    else
    {
        if (FindSessionByBaseAuth(p_qstrBasicAuth))
        {
            SetThreadBaseAuth(p_qstrBasicAuth);
        }
    }

}

int CdmSessionManager::GetCurrentSessionId()
{
    return GetThreadSessionId();
}

QString CdmSessionManager::GetCurrentSessionBaseAuth()
{
    return GetThreadBaseAuth();
}

int CdmSessionManager::CreateNewSessionLdap(QString p_qstrLogin, QString p_qstrPassword)
{
    SYNCHRONIZED;
    int iSessionId = 0;

    CdmSession* pSession = new CdmSession;
    pSession->LdapLogin(p_qstrLogin, p_qstrPassword, GetDataAccess());

    if(pSession->GetId())
    {
        m_qmSessionManager.insert(pSession->GetId(), pSession);
        m_qmSessionManagerAuth.insert(pSession->GetBaseAuth(), pSession);
        SetThreadSessionId(pSession->GetId());
        SetThreadBaseAuth(pSession->GetBaseAuth());
        iSessionId = pSession->GetId();
    }
    else
    {
        DELPTR(pSession);
    }

    return iSessionId;
}

void CdmSessionManager::AddSessionToThreadContext(CdmSession* p_pSession)
{
    INFO("New Session Id: " + QString::number(p_pSession->GetId()));
    m_qmSessionManager.insert(p_pSession->GetId(), p_pSession);
    INFO("SessionManager Map Size: " + QString::number(m_qmSessionManager.count()));
    m_qmSessionManagerAuth.insert(p_pSession->GetBaseAuth(), p_pSession);
    INFO("SessionManagerAuth Map Size: " + QString::number(m_qmSessionManagerAuth.count()));
    SetThreadSessionId(p_pSession->GetId());
    SetThreadBaseAuth(p_pSession->GetBaseAuth());
}

int CdmSessionManager::CreateNewSession(QString p_qstrLogin,
                                        QString p_qstrPassword)
{
    SYNCHRONIZED;
    int iSessionId = 0;
    CdmSession* pSession = new CdmSession;
    pSession->Login(p_qstrLogin, p_qstrPassword, GetDataAccess());
    iSessionId = pSession->GetId();

    if(SUCCESSFULL(iSessionId))
    {
        AddSessionToThreadContext(pSession);
        SessionGarbageCollection();
    }
    else
    {
        DELPTR(pSession);
    }

    return iSessionId;
}

CdmSession* CdmSessionManager::FindSession()
{
    SYNCHRONIZED;
    CdmSession* pSession = nullptr;

    if (m_iSessionTimeoutMinutes > 0 &&
            QDateTime::currentDateTime() > m_qdtLastSessionCheck.addMSecs(m_iSessionTimeoutIntervallmsecs)){
        SessionGarbageCollection();
        m_qdtLastSessionCheck = QDateTime::currentDateTime();
    }

    int iSessionId = GetThreadSessionId();

    if (iSessionId != 0)
    {
        pSession = FindSessionById(iSessionId);
    }
    else
    {
        QString qstrBaseAuth = GetThreadBaseAuth();

        if (!qstrBaseAuth.isEmpty())
        {
            pSession = FindSessionByBaseAuth(qstrBaseAuth);
        }
    }

    return pSession;
}

CdmSession* CdmSessionManager::FindSessionLocal()
{
    CdmSession* pSession = nullptr;
    int iSession = 0;
    SYNCHRONIZED;

    if (m_iSessionTimeoutMinutes > 0 &&
            QDateTime::currentDateTime() > m_qdtLastSessionCheck.addMSecs(m_iSessionTimeoutIntervallmsecs)){
        SessionGarbageCollection();
        m_qdtLastSessionCheck = QDateTime::currentDateTime();
    }

    if (GetThreadSessionId() != 0)
    {
        iSession = GetThreadSessionId();
    }

    if (iSession != 0)
    {
        pSession = FindSessionByIdLocal(iSession);
    }
    else
    {
        QString qstrBaseAuth;


        if (!GetThreadBaseAuth().isEmpty())
        {
            pSession = FindSessionByBaseAuthLocal(GetThreadBaseAuth());
        }
    }

    return pSession;
}

CdmSession* CdmSessionManager::FindSessionByIdLocal(int p_iSessionId)
{
    CdmSession* pSession = nullptr;
    SYNCHRONIZED;

    if (p_iSessionId != 0)
    {
        if (m_qmSessionManager.contains(p_iSessionId))
        {
            pSession = m_qmSessionManager[p_iSessionId];
        }
    }
    else
    {
        if (!m_qmSessionManager.isEmpty())
        {
            pSession = m_qmSessionManager.begin().value(); // WHY???????
        }
    }

    return pSession;
}

CdmSession* CdmSessionManager::FindSessionById(int p_iSessionId)
{
    CdmSession* pSession = nullptr;
    SYNCHRONIZED;
    pSession = FindSessionByIdLocal(p_iSessionId);

    if (!pSession && p_iSessionId != 0)
    {
        IdmDataAccess* pDataAccess = GetDataAccess();

        if(CHKPTR(pDataAccess))
        {
            pSession = pDataAccess->FindSession(p_iSessionId);
        }
    }

    if (pSession)
    {
        pSession->SetLastRequest(QDateTime::currentDateTime());
    }

    return pSession;
}

CdmSession* CdmSessionManager::FindSessionByBaseAuthLocal(QString p_qstrAuth)
{
    CdmSession* pSession = nullptr;
    SYNCHRONIZED;

    if (m_qmSessionManagerAuth.contains(p_qstrAuth))
    {
        pSession = m_qmSessionManagerAuth[p_qstrAuth];
    }

    return pSession;
}

CdmSession* CdmSessionManager::FindSessionByBaseAuth(QString p_qstrAuth)
{
    SYNCHRONIZED;
    QString qstrUser;
    QString qstrPassword;
    QString qstrPasswordEncrypted;
    QString qstrBaseAuthEncrypted;
    QString qstrAuth = QByteArray::fromBase64(p_qstrAuth.toLatin1(), QByteArray::Base64UrlEncoding);
    QStringList qstrlAuth = qstrAuth.split(":");
    if (qstrlAuth.count() == 2)
    {
       qstrUser = qstrlAuth[0];
       qstrPassword = qstrlAuth[1];
       qstrPasswordEncrypted = CwmsUtilities::EncryptPassword(qstrPassword);
       qstrBaseAuthEncrypted = qstrUser + ":" + qstrPasswordEncrypted;
    }

    CdmSession* pSession = FindSessionByBaseAuthLocal(qstrBaseAuthEncrypted);

    if (!pSession)
    {
        IdmDataAccess* pDataAccess = GetDataAccess();

        if(CHKPTR(pDataAccess))
        { 
            pSession = pDataAccess->FindSession(qstrBaseAuthEncrypted);

            if (!pSession)
            {
                int iSessionId = CreateNewSession(qstrUser, qstrPassword);
                if (SUCCESSFULL(iSessionId))
                {
                    pSession = FindSessionById(iSessionId);
                }
            }
        }


    }

    if (pSession)
    {
        pSession->SetLastRequest(QDateTime::currentDateTime());
    }

    return pSession;
}

CdmDataProvider* CdmSessionManager::FindDataProvider()
{
    CdmDataProvider* pCdmManager = nullptr;
    CdmSession* pSession = FindSession();

    if (pSession)
    {
        pCdmManager = pSession->GetDataProvider();
    }

    return pCdmManager;
}

void CdmSessionManager::DeleteSession()
{
    CdmSession* pSession = FindSessionLocal();

    if (pSession)
    {
        DeleteSession(pSession);
    }
}

void CdmSessionManager::SessionGarbageCollection()
{
    SYNCHRONIZED;
    if (!m_bCollectSessionGarbage)
    {
        m_bCollectSessionGarbage = true;
        QMap<int, CdmSession*>::iterator qmIt = m_qmSessionManager.begin();
        QMap<int, CdmSession*>::iterator qmItEnd = m_qmSessionManager.end();
        QList<int> qlSessionsToRemove;
        QList<QString> qlSessionBaseAuthsToRemove;

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmSession* pSession = qmIt.value();

            if (CHKPTR(pSession) && pSession->IsExpired())
            {
                // timeout occurred
                INFO("Session with ID " + QString::number(qmIt.key()) + " received timeout.");
                qlSessionsToRemove.append(qmIt.key());
                qlSessionBaseAuthsToRemove.append(pSession->GetBaseAuth());
                emit SessionTimedOut(pSession->GetId());
                emit SessionTimedOut(pSession->GetBaseAuth());
                DeleteSessionObject(pSession);
            }
        }

        for (int iCounter = 0; iCounter < qlSessionsToRemove.count(); ++iCounter)
        {
            m_qmSessionManager.remove(qlSessionsToRemove[iCounter]);
        }

        for (int iCounter = 0; iCounter < qlSessionBaseAuthsToRemove.count(); ++iCounter)
        {
            m_qmSessionManagerAuth.remove(qlSessionBaseAuthsToRemove[iCounter]);
        }


        IdmDataAccess* pDataAccess = GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            pDataAccess->SessionTimeoutCheck(m_iSessionTimeoutMinutes);
        }


        m_bCollectSessionGarbage = false;
    }
}

IdmDataAccess* CdmSessionManager::GetDataAccess()
{
    if (m_pDataAccess == nullptr)
    {
        m_pDataAccess = CdmDataAccessConfiguration::EstablishConnection();
    }

    return m_pDataAccess;
}

void CdmSessionManager::DeleteSession(CdmSession* p_pSession)
{
    if (p_pSession)
    {
        SYNCHRONIZED;
       qint64 lId = p_pSession->GetId();
        QString qstrBaseAuth = p_pSession->GetBaseAuth();
        p_pSession->Logout();
        m_qmSessionManager.remove(lId);
        m_qmSessionManagerAuth.remove(qstrBaseAuth);
        DeleteSessionObject(p_pSession);
    }
}

void CdmSessionManager::DeleteSessionObject(CdmSession* p_pSession)
{
    if (p_pSession)
    {      
        INFO("Session logged out.");
        DELPTR(p_pSession);
        INFO("Session deleted.");
    }
}

void CdmSessionManager::InsertSession(CdmSession* p_pSession)
{
    SYNCHRONIZED;

    if (p_pSession)
    {
        m_qmSessionManager.insert(0, p_pSession);
        m_qmSessionManagerAuth.insert(p_pSession->GetBaseAuth(), p_pSession);
    }
}

int CdmSessionManager::GetSessionCount()
{
    int iRet = 0;
    SYNCHRONIZED;
    iRet = m_qmSessionManager.count();
    return iRet;
}

int CdmSessionManager::GetThreadCount()
{
    int iRet = 0;
    QThreadPool* pool = QThreadPool::globalInstance();

    if (pool)
    {
        iRet = pool->activeThreadCount();
    }

    return iRet;
}

CdmSessionManager* CdmSessionManager::CreateSessionManager(EdmSettingsMode p_eMode)
{
    if (!m_spSessionManager)
    {
        m_spSessionManager = new CdmSessionManager(p_eMode);
    }

    return m_spSessionManager;
}

CdmSessionManager* CdmSessionManager::GetSessionManager()
{
    return m_spSessionManager;
}

int CdmSessionManager::Login(QString p_qstrLogin,
                             QString p_qstrPassword)
{
    int iSessionId = 0;
    CdmSessionManager* pFactory = GetSessionManager();

    if (pFactory)
    {
        iSessionId = pFactory->CreateNewSession(p_qstrLogin, p_qstrPassword);
    }

    return iSessionId;
}

CdmDataProvider* CdmSessionManager::GetDataProvider()
{
    CdmDataProvider* pManager = nullptr;
    CdmSessionManager* pSessionManager = GetSessionManager();

    if (pSessionManager)
    {
        pManager = pSessionManager->FindDataProvider();
    }
    return pManager;
}

void CdmSessionManager::Logout()
{
    CdmSessionManager* pFactory = GetSessionManager();

    if (pFactory)
    {
        pFactory->DeleteSession();
    }

}

int CdmSessionManager::GetOpenSessions()
{
    int iOpenSessions = 0;
    CdmSessionManager* pFactory = GetSessionManager();

    if (pFactory)
    {
        iOpenSessions = pFactory->GetSessionCount();
    }

    return iOpenSessions;
}

int CdmSessionManager::GetOpenThreads()
{
    int iOpenThreads = 0;
    CdmSessionManager* pFactory = GetSessionManager();

    if (pFactory)
    {
        iOpenThreads = pFactory->GetThreadCount();
    }

    return iOpenThreads;
}


void CdmSessionManager::SetAddOnManager(CdmExecutorAddOnManager *rpAddOnManager)
{
    SYNCHRONIZED;
    m_pAddOnManager = rpAddOnManager;
}

CdmExecutorAddOnManager *CdmSessionManager::getAddonManager()
{
    return m_pAddOnManager;
}


bool CdmSessionManager::GetServerMode() const
{
    SYNCHRONIZED;
    return m_bServerMode;
}

void CdmSessionManager::SetServerMode(bool bServerMode)
{
    SYNCHRONIZED;
    m_bServerMode = bServerMode;
}


int CdmSessionManager::GetSessionTimeoutMinutes() const
{
    SYNCHRONIZED;
    return m_iSessionTimeoutMinutes;
}

void CdmSessionManager::SetSessionTimeoutMinutes(int iSessionTimeoutMinutes)
{
    SYNCHRONIZED;
    m_iSessionTimeoutMinutes = iSessionTimeoutMinutes;
    m_iSessionTimeoutIntervallmsecs = m_iSessionTimeoutMinutes * 1000 * 60 + 100;
}

const CumUser* CdmSessionManager::GetCurrentUser() const
{
    const CumUser* pUser = nullptr;
    CdmSession* pSession = const_cast<CdmSessionManager*> (this)->FindSession();

    if (pSession)
    {
        pUser = pSession->GetCurrentUser();
    }

    return pUser;
}

qint64 CdmSessionManager::GetCurrentUserId() const
{
   qint64 lRet = 0;
    const CumUser* pUser = GetCurrentUser();

    if(CHKPTR(pUser))
    {
        lRet = pUser->GetId();
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

CdmGlobalContext* CdmSessionManager::GetGlobalContext()
{
    SYNCHRONIZED;
    return m_pGlobalContext;
}

QVariant CdmSessionManager::GetVariant() const
{
    return QVariant();
}


int CdmSessionManager::GetThreadSessionId()
{
    int iSession = 0;
    if (m_qSessionData.hasLocalData())
    {
        if (m_qSessionData.localData().contains("SessionId"))
            iSession = m_qSessionData.localData()["SessionId"]->toInt();
    }

    return iSession;
}

QString CdmSessionManager::GetThreadBaseAuth()
{
    QString qstrBaseAuth;
    if (m_qSessionData.hasLocalData())
    {
        if (m_qSessionData.localData().contains("SessionBaseAuth"))
        {
            qstrBaseAuth = m_qSessionData.localData()["SessionBaseAuth"]->toString();
        }
    }

    return qstrBaseAuth;
}

void CdmSessionManager::SetThreadSessionId(int p_iSessionId)
{
    m_qSessionData.localData().insert("SessionId",new QVariant(p_iSessionId));
}

void CdmSessionManager::SetThreadBaseAuth(QString p_qstrBaseAuth)
{
    m_qSessionData.localData().insert("SessionBaseAuth",new QVariant(p_qstrBaseAuth));
}

void CdmSessionManager::setEventStoreManager(IdmEventStoreManager *pEventStore)
{
    m_pEventStoreManager = pEventStore;
}

IdmEventStoreManager *CdmSessionManager::getEventStoreManager() const
{
    return m_pEventStoreManager;
}
