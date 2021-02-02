
// WMS Includes
#include "CdmSessionManager.h"

// Own Includes
#include "CwmsContext.h"
#include "CwmsServerLogin.h"

CwmsServerLogin::CwmsServerLogin()
    : m_bLogoutNeeded(true)
{
    SYNCHRONIZED;

    if (CdmSessionManager::GetSessionManager()->FindSessionLocal())
    {
        m_bLogoutNeeded = false;
    }
    else
    {
        CwmsContext::GetContext()->ServerLogin();
    }
}

CwmsServerLogin::~CwmsServerLogin()
{
    if (m_bLogoutNeeded)
    {
        CwmsContext::GetContext()->ServerLogout();
    }
}
