// System and QT Includes
#include <qdir.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmValueObjectRef.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmQuery.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "wmsdefines.h"

// Own Includes
#include "CwtHelper.h"
#include "CwtMassLoginLogout.h"

#define REPEATS 100



CwtLoginLogout::CwtLoginLogout()
: CwtTestBase(eBmsTestModeDB)
{

}

void CwtLoginLogout::init()
{
    StartPureTest();
}

void CwtLoginLogout::cleanup()
{
    EndPureTest();
}

void CwtLoginLogout::initTestCase()
{
}

void CwtLoginLogout::cleanupTestCase()
{
}

void CwtLoginLogout::LoginAdmin()
{
    CwtHelper::Login(LOGIN_ADMIN, PASSWORD_ADMIN);
}

void CwtLoginLogout::LoginWrongPassword()
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    QVERIFY(pSessionManager->CreateNewSession(LOGIN_ADMIN, LOGIN_UNKNOWN) < 0);
}

void CwtLoginLogout::LoginUnknowUser()
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    QVERIFY(pSessionManager->CreateNewSession(LOGIN_UNKNOWN, LOGIN_UNKNOWN) < 0);

}

void CwtLoginLogout::Logout()
{
     CwtHelper::Logout();
}

void CwtLoginLogout::MassLoginLogout()
{
    for (int i = 0; i < REPEATS; ++i)
    {
        CwtHelper::Login(LOGIN_ADMIN, PASSWORD_ADMIN);
        CwtHelper::Logout();
    }
}
