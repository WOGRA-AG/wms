// System and Qt Includes
#include <QObject>

// own Includes
#include "CdmGlobalContext.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmDataAccessConfiguration.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmContainerManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmSession.h"

#define SESSION_UPDATE_INTERVALL_MSECS 1000 * 60 * 1

CdmSession::CdmSession()
    : m_lSessionId(0),
      m_pSessionUser(nullptr),
      m_pDataProvider(nullptr),
      m_qdtLastUpdate(QDateTime::currentDateTime()),
      m_pEventStoreManager(nullptr)

{
}

CdmSession::~CdmSession()
{
    DELPTR(m_pSessionUser);
    DELPTR(m_pDataProvider);
}


const CumUser* CdmSession::GetCurrentUser() const
{
    return m_pSessionUser;
}

qint64 CdmSession::GetCurrentUserId() const
{
   qint64 lRet = CdmLogging::eDmUnknownUserManagerError;

    if(CHKPTR(m_pSessionUser))
    {
        lRet = m_pSessionUser->GetId();
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

bool CdmSession::IsExpired() const
{
    bool timedOut = false;

   CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        int iTimeoutSpan = pSessionManager->GetSessionTimeoutMinutes();
        QDateTime qdCurrent = QDateTime::currentDateTime();
        int minsFromLastCall = m_qdtLastRequest.secsTo(qdCurrent) / 60;

        if (minsFromLastCall > iTimeoutSpan)
        {
            timedOut = true;
        }
    }

    return timedOut;
}

void CdmSession::LdapLogin(QString p_qstrLogin, QString p_qstrPassword, IdmDataAccess* p_pDataAccess)
{
    InitNewManager(p_pDataAccess);

    if(m_pDataProvider)
    {
        m_pDataProvider->GetDataAccess()->LoginLdap("UNKNOWN",
                                               p_qstrLogin,
                                               p_qstrPassword,
                                               m_lSessionId,
                                               m_pSessionUser);
    }
}

void CdmSession::Login(QString p_qstrLogin, QString p_qstrPassword, IdmDataAccess* p_pDataAccess)
{
    InitNewManager(p_pDataAccess);

    if(m_pDataProvider)
    {
        bool bDemo = false;
        int iModules = 0;
        m_pDataProvider->GetDataAccess()->Login("UNKNOWN",
                                           p_qstrLogin,
                                           p_qstrPassword,
                                           bDemo,
                                           iModules,
                                           "",
                                           m_lSessionId,
                                           m_pSessionUser);
    }
}

CdmDataProvider *CdmSession::GetDataProvider() const
{
    return m_pDataProvider;
}

QDateTime CdmSession::GetLastRequest() const
{
    return m_qdtLastRequest;
}

void CdmSession::SetLastRequest(const QDateTime &qdtLastRequest)
{
    m_qdtLastRequest = qdtLastRequest;
}

qint64 CdmSession::GetId()
{
    return m_lSessionId;
}

QString CdmSession::GetBaseAuth() const
{
    if (!m_pSessionUser)
    {
        ERR("User is nullptr");
        return "";
    }

    return m_pSessionUser->GetBaseAuth();
}

void CdmSession::InitNewManager(IdmDataAccess* p_pDataAccess)
{
    if(p_pDataAccess)
    {
        if (m_pDataProvider)
        {
            return;
        }

        m_pDataProvider = new CdmDataProvider(p_pDataAccess);

        if(CHKPTR(m_pDataProvider))
        {
            CdmExecutor* pExecutor = m_pDataProvider->GetExecutor();

            if (CHKPTR(pExecutor))
            {
                pExecutor->CreateEngines();
                pExecutor->InstallAddOnManager(CdmSessionManager::GetSessionManager()->m_pAddOnManager);
            }
        }
    }
    else
    {
        ERR(QObject::tr("Konnte Datenzugriff nicht instanziieren."))
    }
}

qint64 CdmSession::Logout()
{
   qint64 lRet = CdmLogging::eDmUnknownDataAccessError;
    CdmDataProvider* pManager = GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if(CHKPTR(pDataAccess))
        {
            lRet = pDataAccess->Logout();
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }

    return lRet;
}

QString CdmSession::GetServerRequestPath() const
{
   return m_qstrServerRequestPath;
}

void CdmSession::SetServerRequestPath(QString p_qstrPath)
{
   m_qstrServerRequestPath = p_qstrPath;
}


void CdmSession::setEventStoreManager(IdmEventStoreManager *pEventStore)
{
    m_pEventStoreManager = pEventStore;
}

IdmEventStoreManager *CdmSession::getEventStoreManager()
{
    return m_pEventStoreManager;
}

void CdmSession::SessionUpdated()
{
    m_qdtLastUpdate = QDateTime::currentDateTime();
}

bool CdmSession::NeedsUpdate()
{
    return (m_qdtLastUpdate.addMSecs(SESSION_UPDATE_INTERVALL_MSECS) < QDateTime::currentDateTime());
}
