#include "CwnCommandCreateUser.h"
#include "CwnCommandDeleteUser.h"
#include "CwnCommandFindUser.h"
#include "CwnCommandCreateUserGroup.h"
#include "CwnCommandDeleteGroup.h"
#include "CwnCommandAddUserToGroup.h"
#include "CwnCommandUpdateUser.h"
#include "CwnCommandGetUserList.h"
#include "CwnCommandExistUser.h"
#include "CwnCommandFindUserGroup.h"
#include "CwnCommandRenameUserGroup.h"
#include "CwnCommandRemoveUserFromGroup.h"
#include "CwnCommandGetUserGroupList.h"
#include "CwnCommandGetListOfUsersInList.h"
#include "CwnCommandFindGroups.h"
#include "CwnCommandGetUserGroupMemberList.h"
#include "CwnCommandCheckAuthorisationAdmin.h"
#include "CwnCommandCheckAuthorisation.h"
#include "CwnCommandFindUserByEmail.h"
#include "CwnCommandFindUserByLogin.h"
#include "CwnCommandFindUserGroupById.h"
#include "CwnCommandFindUserGroupByName.h"

#include "CwnDataAccess.h"
#include "CumUser.h"
#include "CumUserGroup.h"

#include "CwnUserManager.h"

#include <QLinkedList>


CwnUserManager::CwnUserManager(CwnDataAccess* p_pCwnDataAccess)
    : m_pCwnDataAccess(p_pCwnDataAccess)
{
}

CwnUserManager::~CwnUserManager()
{
    //Nothing to do.
}

long CwnUserManager::CreateUser(CumUser* p_pUser)
{
    CwnCommandCreateUser createU(m_pCwnDataAccess,p_pUser->GetIdentitiyKey());

    // a registration will only be activated after activating the user.
    if (!p_pUser->GetIdentitiyKey().isEmpty())
    {
        createU.setActive(false);
    }
    else
    {
        createU.setActive(true);
    }
    createU.setAdmin(p_pUser->IsAdministrator());
    createU.setEmail(p_pUser->GetEmail());
    createU.setFirstname(p_pUser->GetFirstName());
    createU.setLastname(p_pUser->GetLastName());
    createU.setLogin(p_pUser->GetLogin());
    createU.setPass(p_pUser->GetPassword());

    return createU.Run();
}

long CwnUserManager::DeleteUser(QString p_qstrLogin)
{
    CwnCommandDeleteUser deleteU(m_pCwnDataAccess);
    deleteU.setLogin(p_qstrLogin);

    return deleteU.Run();
}

long CwnUserManager::DeleteUser(long p_lUserId)
{
    CwnCommandDeleteUser command(p_lUserId, m_pCwnDataAccess);
    return command.Run();
}


CumUser *CwnUserManager::FindUser(QString p_qstrLogin, QString p_qstrPassword)
{
    CwnCommandFindUser findU(m_pCwnDataAccess);
    findU.setLogin(p_qstrLogin);
    findU.setPassw(p_qstrPassword);

    findU.setDecider(0);
    CumUser* cu = nullptr;

    if(findU.Run() > 0)
    {
        cu = findU.getResult();

    }
    return cu;
}

long CwnUserManager::UpdateUser(CumUser* p_pUser)
{
    CwnCommandUpdateUser updateU(m_pCwnDataAccess);
    updateU.setUserId(p_pUser->GetId());
    updateU.setLogin(p_pUser->GetLogin());
    updateU.setActive(p_pUser->IsActive());
    updateU.setAdmin(p_pUser->IsAdministrator());
    updateU.setEmail(p_pUser->GetEmail());
    updateU.setFirstname(p_pUser->GetFirstName());
    updateU.setLastname(p_pUser->GetLastName());
    updateU.setPassw(p_pUser->GetPassword(), p_pUser->IsEncrypted());

    return updateU.Run();
}

long CwnUserManager::GetUserList(QLinkedList<CumUser *> &p_qvlUsers)
{
    CwnCommandGetUserList getUserList(m_pCwnDataAccess);

    long val = getUserList.Run();

    if(val>0)
    {
        p_qvlUsers = getUserList.getResult();
    }

    return val;
}

long CwnUserManager::ExistUser(QString p_qstrLogin)
{
    CwnCommandExistUser exUser(m_pCwnDataAccess);
    exUser.setLogin(p_qstrLogin);

    return exUser.Run();
}

long CwnUserManager::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    CwnCommandRenameUserGroup updateG(m_pCwnDataAccess);
    updateG.setGroupId(p_lGroupId);
    updateG.setGroupname(p_qstrNewName);

    return updateG.Run();
}

long CwnUserManager::CreateUserGroup(QString p_qstrGroupName)
{
    CwnCommandCreateUserGroup createGroup(m_pCwnDataAccess);
    createGroup.setGroupName(p_qstrGroupName);

    return createGroup.Run();
}

long CwnUserManager::DeleteUserGroup(long p_llGroupId)
{
    CwnCommandDeleteGroup deleteGroup(m_pCwnDataAccess);
    deleteGroup.setGroupId(p_llGroupId);

    return deleteGroup.Run();
}

long CwnUserManager::AddUserToUserGroup(long p_lUserId, long p_lUserGroupId)
{
    CwnCommandAddUserToGroup UserToGroup(m_pCwnDataAccess);
    UserToGroup.setUserId(p_lUserId);
    UserToGroup.setGroupId(p_lUserGroupId);

    return UserToGroup.Run();
}

long CwnUserManager::RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId)
{
    CwnCommandRemoveUserFromGroup RemoveFromGroup(m_pCwnDataAccess);
    RemoveFromGroup.setUserId(p_lUserId);
    RemoveFromGroup.setGroupId(p_lUserGroupId);

    return RemoveFromGroup.Run();
}

long CwnUserManager::GetUserGroupList(QLinkedList<CumUserGroup *> &p_rqvlUserGroups)
{
    CwnCommandGetUserGroupList getGroupList(m_pCwnDataAccess);

    long val = getGroupList.Run();

    if(val>0)
    {
        p_rqvlUserGroups = getGroupList.getResult();
    }

    return val;
}

long CwnUserManager::GetListOfUsersInList(long p_lUserGroupId, QLinkedList<CumUser *> &p_rqvlUserList)
{
    CwnCommandGetListOfUsersInList getListOfUsersInList(m_pCwnDataAccess);

    getListOfUsersInList.setGroupId(p_lUserGroupId);
    long val = getListOfUsersInList.Run();

    if(val>0)
    {
        p_rqvlUserList = getListOfUsersInList.getResult();
    }

    return val;
}

long CwnUserManager::GetUserGroupMemberList(long p_lUserId, QLinkedList<CumUserGroup *> &p_qvlUserGroups)
{
    CwnCommandGetUserGroupMemberList getGroupMemberList(m_pCwnDataAccess);

    getGroupMemberList.setUserId(p_lUserId);
    long val = getGroupMemberList.Run();

    if(val>0)
    {
        p_qvlUserGroups = getGroupMemberList.getResult();
    }

    return val;
}

CumUser* CwnUserManager::FindUser(long p_lUserId)
{
    CwnCommandFindUser findU(m_pCwnDataAccess);
    findU.setUserId(p_lUserId);
    findU.setDecider(1);
    CumUser* cu = nullptr;

    if(findU.Run() > 0)
    {
        cu = findU.getResult();
    }

    return cu;
}

CumUserGroup *CwnUserManager::FindUserGroup(long p_lGroupId)
{
    CwnCommandFindUserGroup findG(m_pCwnDataAccess);
    findG.setGroupid(p_lGroupId);

    CumUserGroup* cu = nullptr;

    if(findG.Run() > 0)
    {
        cu = findG.getResult();
    }
    return cu;
}

bool CwnUserManager::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
{
    CwnCommandCheckAuthorisationAdmin checkAdmin(m_pCwnDataAccess);
    checkAdmin.setLogin(p_qstrLogin);
    checkAdmin.setPassw(p_qstrPassword);

    return checkAdmin.Run();
}

bool CwnUserManager::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
{
    CwnCommandCheckAuthorisation check(m_pCwnDataAccess);
    check.setLogin(p_qstrLogin);
    check.setPassw(p_qstrPassword);

    return check.Run();
}

CumUser *CwnUserManager::FindUserByEmail(QString p_qstrEmail)
{
    CwnCommandFindUserByEmail findBE(m_pCwnDataAccess);
    findBE.setEmail(p_qstrEmail);
    CumUser* cu = nullptr;

    if(findBE.Run() > 0)
    {
        cu = findBE.getResult();
    }
    return cu;
}

CumUser *CwnUserManager::FindUserByLogin(QString p_qstrLogin)
{
    CwnCommandFindUserByLogin findLo(m_pCwnDataAccess);
    findLo.setLogin(p_qstrLogin);
    CumUser* cu = nullptr;

    if(findLo.Run() > 0)
    {
        cu = findLo.getResult();
    }

    return cu;
}

void CwnUserManager::EncryptAllPasswords()
{
    //Not implemented, because not needed
}


CumUserGroup* CwnUserManager::FindUserGroupById(int p_iId)
{
    CwnCommandFindUserGroupById command(p_iId, m_pCwnDataAccess);
    command.Run();
    return command.GetResult();
}

CumUserGroup* CwnUserManager::FindUserGroupByName(QString p_qstrName)
{
    CwnCommandFindUserGroupByName command(p_qstrName, m_pCwnDataAccess);
    command.Run();
    return command.GetResult();
}

QLinkedList<CumUser*> CwnUserManager::FindUser(QString p_qstrUserLoginNameEmail)
{
    QLinkedList<CumUser*> lUsers;
    CwnCommandGetUserList command(p_qstrUserLoginNameEmail, m_pCwnDataAccess);
    command.Run();
    lUsers = command.getResult();
    return lUsers;
}

CumUser *CwnUserManager::FindUserByIdentKey(QString p_qstridentKey)
{
    CumUser* pCumUser = nullptr;
    CwnCommandFindUser command(m_pCwnDataAccess);

    command.setUserIdentKey(p_qstridentKey);
    command.setDecider(3);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.getResult();
    }

    return pCumUser;
}

QLinkedList<CumUserGroup *> CwnUserManager::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    CwnCommandFindGroups command(p_qstrName, p_qstrSchemeUri, m_pCwnDataAccess);
    command.Run();
    return command.GetResult();
}
