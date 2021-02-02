#ifndef CWMSCLOUDSERVICES_H
#define CWMSCLOUDSERVICES_H


// Own Incldues
#include "basetools.h"

class BASETOOLS_API CwmsCloudServices
{
public:
    CwmsCloudServices();
    static bool IsUserSchemeAdmin(const CumUser *p_pUser, CdmScheme *p_pScheme);
};

#endif // CWMSCLOUDSERVICES_H
