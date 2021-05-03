/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtUser.cpp
 ** Started Implementation: 2012/04/20
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <qdir.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmValueObjectRef.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmQueryEnhanced.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "wmsdefines.h"


// own Includes
#include "CwtHelper.h"
#include "CwtUser.h"

CwtUser::CwtUser()
    : CwtTestBase(eBmsTestModeDB)
{
}


CwtUser::~CwtUser()
{
}

void CwtUser::initTestCase()
{
    m_qTimeStartAllTests = QTime::currentTime();
    QString qstr = "Start: " + m_qTimeStartAllTests.toString();
    qDebug(qstr.toLocal8Bit());
}

void CwtUser::cleanupTestCase()
{
    QTime qTime = QTime::currentTime();
    QString qstr = "End: " + qTime.toString();
    qDebug(qstr.toLocal8Bit());
    int iMSecs = m_qTimeStartAllTests.msecsTo(qTime);
    int iSecs = iMSecs / 1000;
    int iMins = iSecs / 60;
    int iMinSecs = iSecs % 60;
    qstr = "Duration: " + QString::number(iMSecs) + " msecs.\n";
    qstr += "Seconds: " + QString::number(iSecs) + ".\n";
    qstr += "Minutes: " + QString::number(iMins) + " and " + QString::number(iMinSecs) + " secs.\n";
    qDebug(qstr.toLocal8Bit());
}

void CwtUser::init()
{
    InitWithLogin();
    StartPureTest();
}

void CwtUser::cleanup()
{
    EndPureTest();
    CleanupWithLogout();
}

void CwtUser::FindAdminUserSlot()
{
    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);

    CumUserManager* pUserManager = pCdmDataProvider->GetUserManager();
    QVERIFY(pUserManager != nullptr);

    CumUser* pUser = pUserManager->FindUserById(ADMIN_USER_ID);

    QVERIFY(pUser != nullptr);
    QVERIFY(pUser->GetLogin() == LOGIN_ADMIN);
    QVERIFY(pUser->GetLastName() == LOGIN_ADMIN);
}

void CwtUser::CreateFindDeleteUser()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);
    pUser = pUserManager->FindUserById(iUserId);
    QVERIFY(pUser != nullptr);
    QList<CumUser*> qllUsers;
    pUserManager->GetUserListUnmanaged(qllUsers);
    QVERIFY(qllUsers.count() > 0);

    QList<CumUser*>::iterator qllIt = qllUsers.begin();
    QList<CumUser*>::iterator qllItEnd = qllUsers.end();
    bool found = false;

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUser* pUser = (*qllIt);

        if (pUser->GetLogin() == qstrLogin)
        {
            found = true;
        }

        DELPTR(pUser); // because it is unmanaged
    }

    QVERIFY(found == true);

    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::CreateFindDeleteUserGroup()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUsergroup = 0;
    QString qstrGroupName = CwtHelper::CreateUniqueName("Testgroup");
    iUsergroup = pUserManager->CreateUserGroup(qstrGroupName);
    QVERIFY(iUsergroup > 0);
    CumUserGroup* pGroup = pUserManager->FindUserGroupById(iUsergroup);
    QVERIFY(pGroup != nullptr);
    QList<CumUserGroup*> qllUserGroups;
    pUserManager->GetUserGroupList(qllUserGroups);
    QVERIFY(qllUserGroups.count() > 0);

    QList<CumUserGroup*>::iterator qllIt = qllUserGroups.begin();
    QList<CumUserGroup*>::iterator qllItEnd = qllUserGroups.end();
    bool found = false;

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUserGroup* pGroup = (*qllIt);

        if (pGroup->GetGroupName() == qstrGroupName)
        {
            found = true;
        }
    }

    QVERIFY(found == true);
    QVERIFY(pUserManager->DeleteUserGroup(iUsergroup) > 0);
    QVERIFY(pUserManager->FindUserGroupById(iUsergroup) == nullptr);
}

void CwtUser::FindUserByLogin()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserByLogin(LOGIN_ADMIN);
    QVERIFY(pUser != nullptr);
}

void CwtUser::FindUnknownUserByLogin()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserByLogin(CwtHelper::CreateUniqueName("blub"));
    QVERIFY(pUser == nullptr);
}

void CwtUser::FindUserById()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserById(ADMIN_USER_ID);
    QVERIFY(pUser != nullptr);
}

void CwtUser::FindUnknownUserById()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserById(-100);
    QVERIFY(pUser == nullptr);
}

void CwtUser::FindUnknownUserByEmail()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserByEmail(CwtHelper::CreateUniqueName("blub"));
    QVERIFY(pUser == nullptr);
}

void CwtUser::FindUserByEmail()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);
    pUserManager->ClearUsers();
    pUser = pUserManager->FindUserByEmail(qstrLogin);
    QVERIFY(pUser != nullptr);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::FindUserByIdentityKey()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);
    pUserManager->ClearUsers();
    pUser = pUserManager->FindUserByIdentityKey(qstrLogin);
    QVERIFY(pUser != nullptr);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::FindUnknownUserByIdentityKey()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserByIdentityKey(CwtHelper::CreateUniqueName("blub"));
    QVERIFY(pUser == nullptr);
}

void CwtUser::AddAndRemoveUserToUsergroupByIds()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);

    QString qstrGroupName = CwtHelper::CreateUniqueName("Testgroup");
    int iUsergroup = pUserManager->CreateUserGroup(qstrGroupName);
    QVERIFY(iUsergroup > 0);
    QVERIFY(pUserManager->AddUserToUserGroup(iUserId, iUsergroup) > 0);

    pUserManager->ClearUsers();
    pUserManager->ClearUserGroups();

    CumUserGroup* pGroup = pUserManager->FindUserGroupById(iUsergroup);
    QVERIFY(pGroup != nullptr);

    QList<CumUser*> qllUsers;
    pGroup->GetUserListNewPointers(qllUsers);
    QVERIFY(qllUsers.count() == 1);
    pUser = *qllUsers.begin();
    QVERIFY(pUser->GetLogin() == qstrLogin);

    pUserManager->ClearUsers();
    pUserManager->ClearUserGroups();

    QVERIFY(pUserManager->RemoveUserFromGroup(iUserId, iUsergroup) > 0);
    pGroup = pUserManager->FindUserGroupById(iUsergroup);
    pGroup->GetUserListNewPointers(qllUsers);
    QVERIFY(qllUsers.count() == 0);

    QVERIFY(pUserManager->DeleteUserGroup(qstrGroupName) > 0);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::AddAndRemoveUserToUsergroupByNames()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);

    QString qstrGroupName = CwtHelper::CreateUniqueName("Testgroup");
    int iUsergroup = pUserManager->CreateUserGroup(qstrGroupName);
    QVERIFY(iUsergroup > 0);
    QVERIFY(pUserManager->AddUserToUserGroup(qstrLogin, qstrGroupName) > 0);

    pUserManager->ClearUsers();
    pUserManager->ClearUserGroups();

    CumUserGroup* pGroup = pUserManager->FindUserGroupById(iUsergroup);
    QVERIFY(pGroup != nullptr);

    QList<CumUser*> qllUsers;
    pGroup->GetUserListNewPointers(qllUsers);
    QVERIFY(qllUsers.count() == 1);
    pUser = *qllUsers.begin();
    QVERIFY(pUser->GetLogin() == qstrLogin);

    pUserManager->ClearUsers();
    pUserManager->ClearUserGroups();

    QVERIFY(pUserManager->RemoveUserFromGroup(qstrLogin, qstrGroupName) > 0);
    pGroup = pUserManager->FindUserGroupById(iUsergroup);
    pGroup->GetUserListNewPointers(qllUsers);
    QVERIFY(qllUsers.count() == 0);

    QVERIFY(pUserManager->DeleteUserGroup(qstrGroupName) > 0);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::LoginInactivatedUser()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);
    pUser = pUserManager->FindUserByEmail(qstrLogin);
    pUser->SetActive(false);
    QVERIFY(pUserManager->UpdateUser(pUser) > 0);
    CwtHelper::Logout();
    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();
    QVERIFY(pSessionManager->Login(qstrLogin, qstrLogin) < 0);
    QVERIFY(pSessionManager->Login(LOGIN_ADMIN, PASSWORD_ADMIN) > 0);
    pUserManager = CwtHelper::GetUserManager();
    pUserManager->DeleteUser(iUserId);
}

void CwtUser::CreateUserWithoutLogin()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    pUser->SetLogin("");
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId < 0);
}

void CwtUser::CreateUserWithoutEmail()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    pUser->SetEmail("");
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId < 0);
}

void CwtUser::FindUsersUnmanaged()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    CumUser* pUser = CwtHelper::CreateUser(qstrLogin, pUserManager);
    iUserId = pUserManager->CreateUser(pUser);
    QVERIFY(iUserId > 0);
    pUserManager->ClearUsers();
    QList<CumUser*> qllUsers = pUserManager->FindUsersUnmanaged(qstrLogin);
    QVERIFY(qllUsers.count() == 1);
    pUser = *qllUsers.begin();
    QVERIFY(pUser->GetLogin() == qstrLogin);
    DELPTR(pUser);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::RegisterUser()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUserId = 0;
    QString qstrLogin = CwtHelper::CreateUniqueName("qwertz");
    iUserId = pUserManager->RegisterUser(qstrLogin, "", qstrLogin, qstrLogin, qstrLogin, qstrLogin);
    QVERIFY(iUserId > 0);
    pUserManager->ClearUsers();
    CumUser* pUser = pUserManager->FindUserByIdentityKey(qstrLogin);
    QVERIFY(pUser != nullptr);
    QVERIFY(pUser->IsActive() == false);
    QVERIFY(pUserManager->DeleteUser(qstrLogin) > 0);
}

void CwtUser::CreateAndFindUserGroupUnmanaged()
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();
    QVERIFY(pUserManager != nullptr);
    int iUsergroup = 0;
    QString qstrGroupName = CwtHelper::CreateUniqueName("Testgroup");
    iUsergroup = pUserManager->CreateUserGroup(qstrGroupName);
    QVERIFY(iUsergroup > 0);
    QList<CumUserGroup*> qllUserGroups = pUserManager->FindUserGroupsByNameUnmanaged("test");
    QVERIFY(qllUserGroups.count() > 0);

    QList<CumUserGroup*>::iterator qllIt = qllUserGroups.begin();
    QList<CumUserGroup*>::iterator qllItEnd = qllUserGroups.end();
    bool found = false;

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUserGroup* pGroup = (*qllIt);

        if (pGroup->GetGroupName() == qstrGroupName)
        {
            found = true;
            break;
        }
    }

    QVERIFY(found == true);
    QVERIFY(pUserManager->DeleteUserGroup(iUsergroup) > 0);
}
