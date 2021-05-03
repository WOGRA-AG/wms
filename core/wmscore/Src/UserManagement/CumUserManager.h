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

#ifndef CUMUSERMANAGER_H
#define CUMUSERMANAGER_H

// System and QT Includes
#include <QList>
#include <QMap>


// own Includes
#include "CdmLocatedElement.h"
#include "datamanager.h"


// forwards
class IdmDataAccess;
class CumUser;
class CumUserGroup;
class WMSMANAGER_API CumUserManager;

/*
 * This class manages users and usergrourps
 */
class CumUserManager : public CdmLocatedElement
{
    Q_OBJECT

private:
    /*
       * The dataaccess for user and groups manipulation
       */
    IdmDataAccess*            m_rpIdmDataAccess;

    /*
       * the map of found users
       */
    QMap<int,CumUser*>        m_qmUsers;

    // The List Usergroupds
    QList<CumUserGroup*> m_qlUserGroups;
    QString m_qstrSchemeUri;


    bool CheckUserData(QString p_qstrLogin, QString p_qstrEmail, QString p_qstrIdentityKey);
public:
    CumUserManager(IdmDataAccess* p_pIdmDataAccess, QString p_qstrSchemeUri = "");
    virtual ~CumUserManager();
    long UpdateUser(CumUser* p_pUser);
    long DeleteUser(QString p_qstrLogin);
    long CreateUser(CumUser* p_pUser);
    long LogOut();
    long LogIn(QString p_qstrApplication,
               QString p_qstrLogin,
               QString p_qstrPassword,
               bool& p_bDemoMode,
               int& p_iModules,
               QString& p_qstrVersion);
    long RenameUserGroup(long p_lGroupId, QString p_qstrNewName);
    long CreateUserGroup(QString p_qstrGroupName);
    long DeleteUserGroup(long p_llGroupId);
    long AddUserToUserGroup(long p_lUserId, long p_lUserGroupId);
    long RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId);
    void LoadUserGroups();
    long GetSessionId();
    long GetCurrentUserId();
    CumUserGroup* FindUserGroupById(int p_iId);
    void GetUserBaseIds(QList<long>& p_rqllUserBaseIds);
    QVariant GetVariant() const;
    void ClearUsers();
    void ClearUserGroups();
    long RegisterUser(QString p_qstrLogin,
                      QString p_qstrPassword,
                      QString p_qstrName,
                      QString p_qstrSurName,
                      QString p_qstrEmail,
                      QString p_qstrIdentKey);
    CumUser* FindUserByEmail(QString p_qstrUserEmail);
    CumUser* FindUserByLogin(QString p_qstrUserLogin);
    long DeleteUser(long p_lUserId);
    CumUser *FindUserByIdentityKey(QString p_qstrIdentityKey);
    QList<CumUser *> FindUsersUnmanaged(QString p_qstrSearchString);
    long DeleteUserGroup(QString p_qstrGroup);
    CumUserGroup *FindUserGroupByName(QString p_qstrName);
    long RemoveUserFromGroup(QString p_qstrLogin, QString p_qstrGroup);
    long AddUserToUserGroup(QString p_qstrLogin, QString p_qstrGroup);
    long RenameUserGroup(QString qstrOldName, QString p_qstrNewName);
    QList<CumUserGroup *> FindUserGroupsByNameUnmanaged(QString p_qstrName);
    QVariant GetGroupVariant() const;
    QString GetSchemeUri() const;

    bool IsCurrentUserAdmin();
public slots:
    long GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups);
    long GetListOfUsersInList(long p_lUserGroupId, QList<CumUser*>& p_rqvlUserList);
    long GetUserGroupMemberList(long p_lUserId, QList<CumUserGroup*>& p_qvlUserGroups);
    long GetUserListUnmanaged(QList<CumUser*>& p_rqvlUsers);
    CumUser* FindUserById(int p_iUserId);

};

#endif //
