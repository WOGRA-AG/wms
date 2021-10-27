
// System and Qt Includes
#include <QApplication>

// WMS Commons Includes
#include "CwmsServerSettings.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"

// own Includes
#include "CwmsServiceManager.h"
#include "CwmsContext.h"

CwmsContext* CwmsContext::m_spContext = nullptr;

CwmsContext::CwmsContext(EwmsApplicationContext p_eContext)
    : m_eContext(p_eContext),
      m_pApplicationObject(nullptr),
      m_pPluginManager(nullptr),
      m_bTimedOut(false),
      m_pServiceManager(nullptr)
{
}

CwmsContext::~CwmsContext()
{
    DELPTR(m_pServiceManager);
    DELPTR(m_pPluginManager);
}


bool CwmsContext::CreateContext(EwmsApplicationContext p_eContext)
{
    bool success = false;
    if (!m_spContext)
    {
        m_spContext = new CwmsContext(p_eContext);
        m_spContext->Init();
        success = true;
    }
    else
    {
        ERR("Context already created. Context can only exist once");
    }

    return success;
}

bool CwmsContext::CreateContext(CdmObject* p_pApplicationObject)
{
    bool success = false;

    if (CHKPTR(p_pApplicationObject))
    {
        if (p_pApplicationObject->IsTypeOf("Technical_Application"))
        {
            m_spContext = new CwmsContext(eWmsApplicationContextApplication);
            m_spContext->m_pApplicationObject = p_pApplicationObject;
            m_spContext->Init();
    }
        else
        {
            ERR("Wrong type of application object context not created");
        }
    }
    else
    {
        ERR("Application object is nullptr context not created");
    }

    return success;
}

void CwmsContext::DestroyContext()
{
    CwmsContext* pContext = CwmsContext::GetContext();
    DELPTR(pContext);
}

CwmsContext* CwmsContext::GetContext()
{
    return m_spContext;
}

CwmsApplication CwmsContext::GetApplication()
{
    return CwmsApplication(m_pApplicationObject);
}

void CwmsContext::Init()
{
    m_pPluginManager = new CwmsPluginManager();
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        if (GetContextType() == eWmsApplicationContextServer)
        {
            pSessionManager->SetServerMode(true);
        }
        else
        {
            connect(pSessionManager, SIGNAL(SessionTimedOut(qint64)), this, SLOT(SessionTimedOutSlot()));
        }
    }
}

EwmsApplicationContext CwmsContext::GetContextType()
{
    return m_eContext;
}

CwmsPluginManager* CwmsContext::GetPluginManager()
{
    return m_pPluginManager;
}

void CwmsContext::SessionTimedOutSlot()
{
    MSG_CRIT("Session ist abgelaufen", "Die Session ist abgelaufen. Anwendung wird beendet.");
    m_bTimedOut = true;
    emit ApplicationShutdownSignal();
}

bool CwmsContext::IsTimedOut()
{
    return m_bTimedOut;
}

CwmsServiceManager* CwmsContext::GetServiceManager()
{
    if (m_pServiceManager == nullptr &&
            m_eContext != eWmsApplicationContextCommandLineInterface)
    {
        m_pServiceManager = new CwmsServiceManager();
    }

    return m_pServiceManager;
}

bool CwmsContext::ServerLogout()
{
    bool bRet = false;
    if (GetContextType() == eWmsApplicationContextServer)
    {

        CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

        if (CHKPTR(pFactory))
        {
            pFactory->Logout();
            bRet = true;
        }
    }
    return bRet;
}

bool CwmsContext::ServerLogin()
{
    bool bRet = false;

    if (GetContextType() == eWmsApplicationContextServer)
    {
        CwmsServerSettings cSettings;
        QString qstrUser = cSettings.getServerUser();
        QString qstrPassword = cSettings.getServerUserPassword();

        if (!qstrUser.isEmpty() && !qstrPassword.isEmpty())
        {
            CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

            if (CHKPTR(pFactory))
            {
                if (pFactory->CreateNewSession(qstrUser, qstrPassword) > 0)
                {
                    bRet = true;
                }
            }
        }

        if (!bRet)
        {
            ERR("Can not create connection to plugin configuration in Database perhaps Server Username or Password are wrong configured.\n"
                "Plugins not loaded.");
        }
    }
    return bRet;
}
