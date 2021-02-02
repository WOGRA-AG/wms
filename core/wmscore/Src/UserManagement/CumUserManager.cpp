/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CumUserManager.cpp
 ** Started Implementation:  12.1.2005
 ** Description:
 **
 ** The usermanager for managing users.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/

// System and QT Includes



// own Includes 
#include "IdmDataAccess.h"
#include "CdmSessionManager.h"
#include "CdmModelElement.h"
#include "CdmLogging.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include <QLinkedList>


CumUserManager::CumUserManager(IdmDataAccess* p_pIdmDataAccess, QString p_qstrSchemeUri)
    : m_rpIdmDataAccess(p_pIdmDataAccess),
      m_qstrSchemeUri(p_qstrSchemeUri)
{
    // nothing to do
}


CumUserManager::~CumUserManager(  )
{
    ClearUsers();
    ClearUserGroups();
}


void CumUserManager::ClearUsers() 
{
    SYNCHRONIZED;
    QMap<int,CumUser*>::iterator qmIt = m_qmUsers.begin();
    QMap<int,CumUser*>::iterator qmItEnd = m_qmUsers.end();

    for(; qmIt != qmItEnd; ++qmIt)
    {
        CumUser* pCumUser = qmIt.value();
        DELPTR(pCumUser);
    }

    m_qmUsers.clear();
}

void CumUserManager::ClearUserGroups() 
{
    SYNCHRONIZED;
    QLinkedList<CumUserGroup*>::iterator qllIt = m_qlUserGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qllItEnd = m_qlUserGroups.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        DELPTR(*qllIt);
    }

    m_qlUserGroups.clear();
}


long CumUserManager::CreateUser(CumUser* p_pUser)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess) && CHKPTR(p_pUser))
    {
        if (IsCurrentUserAdmin())
        {
            p_pUser->AddSchemeUri(m_qstrSchemeUri);

            if (CheckUserData(p_pUser->GetLogin(), p_pUser->GetEmail(), p_pUser->GetIdentitiyKey()))
            {
                p_pUser->AddSchemeUri(m_qstrSchemeUri);
                lRet = m_rpIdmDataAccess->CreateUser(p_pUser);

                if (SUCCESSFULL(lRet))
                {
                    p_pUser->SetId(lRet);
                    p_pUser->SetUserManager(this);
                    m_qmUsers.insert(lRet, p_pUser);
                }
                else
                {
                    DELPTR(p_pUser);
                }
            }
            else
            {
                DELPTR(p_pUser);
            }
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::RegisterUser(QString p_qstrLogin,
                                  QString p_qstrPassword,
                                  QString p_qstrName,
                                  QString p_qstrSurName,
                                  QString p_qstrEmail,
                                  QString p_qstrIdentKey)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (CheckUserData(p_qstrLogin, p_qstrEmail, p_qstrIdentKey))
        {
            CumUser* pUser = new CumUser(-1, this);
            pUser->SetLogin(p_qstrLogin);
            pUser->SetPassword(p_qstrPassword);
            pUser->SetLastName(p_qstrName);
            pUser->SetFirstName(p_qstrSurName);
            pUser->SetEmail(p_qstrEmail);
            pUser->SetAdministrator(false);
            pUser->SetIdentityKey(p_qstrIdentKey);

            if (!p_qstrPassword.isEmpty())
            {
                pUser->SetActive(true);
            }
            else
            {
                pUser->SetActive(false);
            }

            pUser->SetEncrypted(false);
            pUser->AddSchemeUri(m_qstrSchemeUri);

            lRet = m_rpIdmDataAccess->RegisterUser(pUser);

            if (SUCCESSFULL(lRet))
            {
                pUser->SetId(lRet);
                pUser->SetUserManager(this);
                m_qmUsers.insert(lRet, pUser);
            }
            else
            {
                DELPTR(pUser);
            }
        }
        else
        {
            lRet = EC(eDmRequiredValueIsMissing);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

bool CumUserManager::CheckUserData(QString p_qstrLogin, QString p_qstrEmail, QString p_qstrIdentityKey)
{
    if (p_qstrLogin.isEmpty())
    {
        ERR("Login must be specified for new user!");
        return false;
    }

    if (FindUserByLogin(p_qstrLogin))
    {
        ERR("User Login already exists. Could not register or create new user.");
        return false;
    }

    if (p_qstrEmail.isEmpty())
    {
        ERR("E-Mail must be specified for new user!");
        return false;
    }

    if (FindUserByEmail(p_qstrEmail))
    {
        ERR("User E-Mail already exists. Could not register or create new user.");
        return false;

    }

    if (!p_qstrIdentityKey.isEmpty() && FindUserByIdentityKey(p_qstrIdentityKey))
    {
        ERR("User IdentityKey already exists. Could not register or create new user.");
        return false;
    }

    return true;
}

long CumUserManager::DeleteUser(QString p_qstrLogin)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            CumUser* pUser = FindUserByLogin(p_qstrLogin);

            if (pUser)
            {
                m_qmUsers.remove(pUser->GetId());
                DELPTR(pUser);
            }

            lRet = m_rpIdmDataAccess->DeleteUser(p_qstrLogin);
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::DeleteUser(long p_lUserId)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            if (m_qmUsers.contains(p_lUserId))
            {
                CumUser* pUser = m_qmUsers[p_lUserId];
                m_qmUsers.remove(pUser->GetId());
                DELPTR(pUser);
            }

            lRet = m_rpIdmDataAccess->DeleteUser(p_lUserId);
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::UpdateUser(CumUser *p_pUser)
{
    long lRet = EC(eDmUnknownUserManagerError);

    if (CHKPTR(p_pUser))
    {
        // the user can change it's own data except the admin flag.
        if (IsCurrentUserAdmin() || (p_pUser->GetId() == GetCurrentUserId() && p_pUser->IsAdministrator() == false))
        {
            lRet = m_rpIdmDataAccess->UpdateUser(p_pUser);
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }

    }

    return lRet;
}

long CumUserManager::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    CumUserGroup* pGroup = FindUserGroupById(p_lGroupId);

    if (CHKPTR(pGroup))
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            if (IsCurrentUserAdmin())
            {
                lRet = m_rpIdmDataAccess->RenameUserGroup(p_lGroupId,
                                                          p_qstrNewName);

                if (SUCCESSFULL(lRet))
                {
                    pGroup->SetGroupName(p_qstrNewName);
                }
            }
            else
            {
                lRet = EC(eDmInsufficentPrivileges);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;

}

long CumUserManager::RenameUserGroup(QString qstrOldName, QString p_qstrNewName)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;
    CumUserGroup* pGroup = FindUserGroupByName(qstrOldName);

    if (pGroup)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            if (IsCurrentUserAdmin())
            {
                lRet = m_rpIdmDataAccess->RenameUserGroup(pGroup->GetId(),
                                                          p_qstrNewName);

                if (SUCCESSFULL(lRet))
                {
                    pGroup->SetGroupName(p_qstrNewName);
                }
            }
            else
            {
                lRet = EC(eDmInsufficentPrivileges);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }
    else
    {
        ERR("Group not found!");
    }

    return lRet;
}

long CumUserManager::CreateUserGroup(QString p_qstrGroupName)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            lRet = m_rpIdmDataAccess->CreateUserGroup(p_qstrGroupName);
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::DeleteUserGroup(long p_llGroupId)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            CumUserGroup* pGroup = FindUserGroupById(p_llGroupId);

            if (pGroup)
            {
                m_qlUserGroups.removeAll(pGroup);
                DELPTR(pGroup);
            }

            lRet = m_rpIdmDataAccess->DeleteUserGroup(p_llGroupId);
        }
        else
        {
            lRet = EC(eDmInsufficentPrivileges);
        }


    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::DeleteUserGroup(QString p_qstrGroup)
{
    if (IsCurrentUserAdmin())
    {
        CumUserGroup* pGroup = FindUserGroupByName(p_qstrGroup);

        if (pGroup)
        {
            return DeleteUserGroup(pGroup->GetId());
        }
    }
    else
    {
        return EC(eDmInsufficentPrivileges);
    }

    return CdmLogging::eDmInvalidUserId;
}

CumUserGroup* CumUserManager::FindUserGroupByName(QString p_qstrName)
{
    SYNCHRONIZED;
    CumUserGroup* pCumUserGroup = nullptr;
    QLinkedList<CumUserGroup*>::iterator qllIt = m_qlUserGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qllItEnd = m_qlUserGroups.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUserGroup* pGroupTemp = (*qllIt);

        if (CHKPTR(pGroupTemp))
        {
            QString qstrGroupName = pGroupTemp->GetGroupName();

            int icheckCompare = (qstrGroupName.compare(p_qstrName, Qt::CaseInsensitive));
            if(icheckCompare == 0)
            {
                pCumUserGroup = pGroupTemp;
                break;
            }
        }
    }

    if (!pCumUserGroup)
    {
        pCumUserGroup = m_rpIdmDataAccess->FindUserGroupByName(p_qstrName,
                                                               m_qstrSchemeUri);

        if(pCumUserGroup)
        {
            m_qlUserGroups.append(pCumUserGroup);
            pCumUserGroup->SetUserManager(this);
        }
    }

    return pCumUserGroup;
}

QLinkedList<CumUserGroup*> CumUserManager::FindUserGroupsByNameUnmanaged(QString p_qstrName)
{
    return m_rpIdmDataAccess->FindUserGroups(p_qstrName, m_qstrSchemeUri);
}

long CumUserManager::AddUserToUserGroup(long p_lUserId, long p_lUserGroupId)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            lRet = m_rpIdmDataAccess->AddUserToUserGroup(p_lUserId,
                                                         p_lUserGroupId);
        }
        else
        {
            return EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::AddUserToUserGroup(QString p_qstrLogin, QString p_qstrGroup)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    CumUser* pUser = FindUserByLogin(p_qstrLogin);
    CumUserGroup* pGroup = FindUserGroupByName(p_qstrGroup);

    if (pUser && pGroup)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            if (IsCurrentUserAdmin())
            {
                lRet = m_rpIdmDataAccess->AddUserToUserGroup(pUser->GetId(),
                                                             pGroup->GetId());
            }
            else
            {
                return EC(eDmInsufficentPrivileges);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }
    else
    {
        if (!pUser)
        {
            ERR("User not found!");
        }

        if (!pGroup)
        {
            ERR("Group not found!")
        }
    }

    return lRet;
}

long CumUserManager::RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        if (IsCurrentUserAdmin())
        {
            lRet = m_rpIdmDataAccess->RemoveUserFromGroup(p_lUserId,
                                                          p_lUserGroupId);
        }
        else
        {
            return EC(eDmInsufficentPrivileges);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::RemoveUserFromGroup(QString p_qstrLogin, QString p_qstrGroup)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    CumUser* pUser = FindUserByLogin(p_qstrLogin);
    CumUserGroup* pGroup = FindUserGroupByName(p_qstrGroup);

    if (pUser && pGroup)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            if (IsCurrentUserAdmin())
            {
                lRet = m_rpIdmDataAccess->RemoveUserFromGroup(pUser->GetId(),
                                                              pGroup->GetId());
            }
            else
            {
                return EC(eDmInsufficentPrivileges);
            }
        }
        else
        {
            lRet = EC(eDmInvalidPtr);
        }
    }
    else
    {
        if (!pUser)
        {
            ERR("User not found!");
        }

        if (!pGroup)
        {
            ERR("Group not found!")
        }
    }

    return lRet;
}

long CumUserManager::GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;
    ClearUserGroups();
    LoadUserGroups();
    p_rqvlUserGroups = m_qlUserGroups;

    return lRet;
}

CumUserGroup* CumUserManager::FindUserGroupById(int p_iId)
{
    SYNCHRONIZED;
    CumUserGroup* pCumUserGroup = nullptr;
    QLinkedList<CumUserGroup*>::iterator qlIt = m_qlUserGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qlItEnd = m_qlUserGroups.end();

    for (; qlIt != qlItEnd; ++qlIt)
    {
        CumUserGroup* pGroupTemp = (*qlIt);

        if(CHKPTR(pGroupTemp))
        {
            int iGroupId = pGroupTemp->GetId();

            if(iGroupId == p_iId)
            {
                pCumUserGroup = pGroupTemp;
                break;

            }
        }
    }

    if (!pCumUserGroup)
    {
        pCumUserGroup = m_rpIdmDataAccess->FindUserGroupById(p_iId);

        if(pCumUserGroup)
        {
            pCumUserGroup->SetUserManager(this);
            m_qlUserGroups.append(pCumUserGroup);
        }
    }

    return pCumUserGroup;
}

void CumUserManager::LoadUserGroups()
{
    if(CHKPTR(m_rpIdmDataAccess))
    {
        m_rpIdmDataAccess->GetUserGroupList(m_qlUserGroups,
                                            m_qstrSchemeUri);

        QLinkedList<CumUserGroup*>::iterator qllIt = m_qlUserGroups.begin();
        QLinkedList<CumUserGroup*>::iterator qllItEnd = m_qlUserGroups.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            (*qllIt)->SetUserManager(this);
        }

    }
}

long CumUserManager::GetListOfUsersInList(long p_lUserGroupId,
                                          QLinkedList<CumUser*>& p_rqvlUserList)
{

    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        lRet = m_rpIdmDataAccess->GetListOfUsersInList(p_lUserGroupId,
                                                       p_rqvlUserList);

        QLinkedList<CumUser*>::iterator qllIt = p_rqvlUserList.begin();
        QLinkedList<CumUser*>::iterator qllItEnd = p_rqvlUserList.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            (*qllIt)->SetUserManager(this);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::GetUserGroupMemberList(long p_lUserId,
                                            QLinkedList<CumUserGroup*>& p_qvlUserGroups)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        lRet = m_rpIdmDataAccess->GetUserGroupMemberList(p_lUserId,
                                                         p_qvlUserGroups);

        QLinkedList<CumUserGroup*>::iterator qllIt = p_qvlUserGroups.begin();
        QLinkedList<CumUserGroup*>::iterator qllItEnd = p_qvlUserGroups.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            (*qllIt)->SetUserManager(this);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}

long CumUserManager::GetUserListUnmanaged(QLinkedList<CumUser*>& p_rqvlUsers)
{
    long lRet = CdmLogging::eDmUnknownDataAccessError;

    BODY_TRY
    p_rqvlUsers.clear();

    if (CHKPTR(m_rpIdmDataAccess))
    {
        lRet = m_rpIdmDataAccess->GetUserList(p_rqvlUsers);

        for (CumUser* pCumUser : p_rqvlUsers)
        {
            pCumUser->SetUserManager(this);
        }
    }
    else
    {
        lRet = EC(eDmInvalidPtr);
    }
    BODY_CATCH

    return lRet;
}

CumUser* CumUserManager::FindUserById(int p_iUserId)
{
    SYNCHRONIZED;
    CumUser* pCumUser = nullptr;

    if (m_qmUsers.contains(p_iUserId))
    {
        pCumUser = m_qmUsers[p_iUserId];
    }

    // not found in memory let's search for it in DB
    if (!pCumUser)
    {
        if (CHKPTR(m_rpIdmDataAccess))
        {
            pCumUser = m_rpIdmDataAccess->FindUserById(p_iUserId);

            if (pCumUser)
            {
                pCumUser->SetUserManager(this);
                m_qmUsers.insert(pCumUser->GetId(), pCumUser);
            }
        }
    }

    return pCumUser;
}

CumUser* CumUserManager::FindUserByLogin(QString p_qstrUserLogin)
{
    SYNCHRONIZED;
    CumUser* pCumUser = nullptr;
    QMapIterator<int,CumUser*> qmIt(m_qmUsers);

    while (qmIt.hasNext())
    {
        qmIt.next();
        CumUser* pUserTemp = qmIt.value();

        if (CHKPTR(pUserTemp))
        {
            if (pUserTemp->GetLogin() == p_qstrUserLogin)
            {
                pCumUser = pUserTemp;
                break;
            }
        }
    }

    // not found in memory lets search for it in DB
    if (!pCumUser)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            pCumUser = m_rpIdmDataAccess->FindUserByLogin(p_qstrUserLogin,
                                                          m_qstrSchemeUri);

            if (pCumUser)
            {
                pCumUser->SetUserManager(this);
                m_qmUsers.insert(pCumUser->GetId(), pCumUser);
            }
        }
    }

    return pCumUser;
}

CumUser* CumUserManager::FindUserByEmail(QString p_qstrUserEmail)
{
    SYNCHRONIZED;
    CumUser* pCumUser = nullptr;
    QMapIterator<int,CumUser*> qmIt(m_qmUsers);

    while (qmIt.hasNext())
    {
        qmIt.next();
        CumUser* pUserTemp = qmIt.value();

        if (CHKPTR(pUserTemp))
        {
            if (pUserTemp->GetEmail() == p_qstrUserEmail)
            {
                pCumUser = pUserTemp;
                break;
            }
        }
    }

    // not found in memory lets search for it on DB.
    if (!pCumUser)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            pCumUser = m_rpIdmDataAccess->FindUserByEmail(p_qstrUserEmail,
                                                          m_qstrSchemeUri);

            if (pCumUser)
            {
                pCumUser->SetUserManager(this);
                m_qmUsers.insert(pCumUser->GetId(), pCumUser);
            }
        }
    }

    return pCumUser;
}

CumUser* CumUserManager::FindUserByIdentityKey(QString p_qstrIdentityKey)
{
    SYNCHRONIZED;
    CumUser* pCumUser = nullptr;
    QMapIterator<int,CumUser*> qmIt(m_qmUsers);

    while (qmIt.hasNext())
    {
        qmIt.next();
        CumUser* pUserTemp = qmIt.value();

        if (CHKPTR(pUserTemp))
        {
            if (pUserTemp->GetIdentitiyKey() == p_qstrIdentityKey)
            {
                pCumUser = pUserTemp;
                break;
            }
        }
    }

    // not found in memory lets search for it on DB.
    if (!pCumUser)
    {
        if(CHKPTR(m_rpIdmDataAccess))
        {
            pCumUser = m_rpIdmDataAccess->FindUserByIdentKey(p_qstrIdentityKey,
                                                             m_qstrSchemeUri);

            if (pCumUser)
            {
                pCumUser->SetUserManager(this);
                m_qmUsers.insert(pCumUser->GetId(), pCumUser);
            }
        }
    }

    return pCumUser;
}

QLinkedList<CumUser*> CumUserManager::FindUsersUnmanaged(QString p_qstrSearchString)
{
    SYNCHRONIZED;
    QLinkedList<CumUser*> qlUsers;

    if(CHKPTR(m_rpIdmDataAccess))
    {
        qlUsers = m_rpIdmDataAccess->FindUser(p_qstrSearchString,
                                              m_qstrSchemeUri);

        QLinkedList<CumUser*>::iterator qllIt = qlUsers.begin();
        QLinkedList<CumUser*>::iterator qllItEnd = qlUsers.end();

        for (; qllIt != qllItEnd; ++qllIt)
        {
            (*qllIt)->SetUserManager(this);
        }
    }

    return qlUsers;
}

void CumUserManager::GetUserBaseIds(QLinkedList<long>& p_rqllUserBaseIds)
{
    SYNCHRONIZED;
    p_rqllUserBaseIds.append(GetCurrentUserId());

    QLinkedList<CumUserGroup*> qllUserGroups;
    GetUserGroupMemberList(GetCurrentUserId(), qllUserGroups);

    QLinkedList<CumUserGroup*>::iterator qllIt = qllUserGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qllItEnd = qllUserGroups.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUserGroup* pCumGroup = *qllIt;

        if (CHKPTR(pCumGroup))
        {
            p_rqllUserBaseIds.append(pCumGroup->GetId());
        }
    }
}

QVariant CumUserManager::GetVariant() const
{
    SYNCHRONIZED;
    QVariantMap qMap;
    QLinkedList<CumUser*> qlUsers;
    QLinkedList<CumUserGroup*> qlUsersGroups;
    (const_cast<CumUserManager*>(this))->GetUserListUnmanaged(qlUsers);
    (const_cast<CumUserManager*>(this))->GetUserGroupList(qlUsersGroups);
    QVariantList qvlGroups;
    QVariantList qvlUsers;
    QLinkedList<CumUser*>::iterator qllIt = qlUsers.begin();
    QLinkedList<CumUser*>::iterator qllItEnd = qlUsers.end();

    for (; qllIt != qllItEnd; ++qllIt)
    {
        CumUser* pUser = *qllIt;

        if (CHKPTR(pUser))
        {
            qvlUsers.append(pUser->GetVariant());
        }
    }

    QLinkedList<CumUserGroup*>::iterator qllItGroup = qlUsersGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qllItGroupEnd = qlUsersGroups.end();

    for (; qllItGroup != qllItGroupEnd; ++qllItGroup)
    {
        CumUserGroup* pGroup= *qllItGroup;

        if (CHKPTR(pGroup))
        {
            qvlGroups.append(pGroup->GetVariant());
        }
    }

    qMap.insert("Users", qvlUsers);
    qMap.insert("Groups", qvlGroups);

    return qMap;
}

QVariant CumUserManager::GetGroupVariant() const
{
    SYNCHRONIZED;
    QVariantMap qMap;
    QLinkedList<CumUserGroup*> qlUsersGroups;
    (const_cast<CumUserManager*>(this))->GetUserGroupList(qlUsersGroups);
    QVariantList qvlGroups;

    QLinkedList<CumUserGroup*>::iterator qllItGroup = qlUsersGroups.begin();
    QLinkedList<CumUserGroup*>::iterator qllItGroupEnd = qlUsersGroups.end();

    for (; qllItGroup != qllItGroupEnd; ++qllItGroup)
    {
        CumUserGroup* pGroup= *qllItGroup;

        if (CHKPTR(pGroup))
        {
            qvlGroups.append(pGroup->GetVariantForDeplyoment());
        }
    }
    return qvlGroups;
}

long CumUserManager::GetSessionId()
{
    return CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
}

long CumUserManager::GetCurrentUserId()
{
    return CdmSessionManager::GetSessionManager()->GetCurrentUserId();
}

bool CumUserManager::IsCurrentUserAdmin()
{
    const CumUser* pUser = CdmSessionManager::GetSessionManager()->GetCurrentUser();

    if (CHKPTR(pUser))
    {
        return pUser->IsAdministrator();
    }

    return false;
}

QString CumUserManager::GetSchemeUri() const
{
    return m_qstrSchemeUri;
}
