
// WMS Includes
#include "CumUser.h"
#include "CdmScheme.h"

#include "CwmsCloudServices.h"

CwmsCloudServices::CwmsCloudServices()
{
}

bool CwmsCloudServices::IsUserSchemeAdmin(const CumUser* p_pUser, CdmScheme* p_pScheme)
{
    Q_UNUSED(p_pScheme);
    Q_UNUSED(p_pUser);
    return false;
}
