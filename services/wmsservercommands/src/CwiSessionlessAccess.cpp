#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

#include "CwmsContext.h"

#include "CwiSessionlessAccess.h"

CwiSessionlessAccess::CwiSessionlessAccess()
    : m_bNeedsLogout(false)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (!pCdmManager)
    {
        CwmsContext::GetContext()->ServerLogin();
        m_bNeedsLogout = true;
    }
}


CwiSessionlessAccess::~CwiSessionlessAccess()
{
    if (m_bNeedsLogout)
    {
        CwmsContext::GetContext()->ServerLogout();
    }
}
