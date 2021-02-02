// WMS Manager
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

#include "CwmsUserCommandAbstract.h"

CwmsUserCommandAbstract::CwmsUserCommandAbstract()
{
}

CwmsUserCommandAbstract::~CwmsUserCommandAbstract()
{

}

CumUserManager *CwmsUserCommandAbstract::GetUserManager()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        return pManager->GetUserManager();
    }

    return nullptr;
}
