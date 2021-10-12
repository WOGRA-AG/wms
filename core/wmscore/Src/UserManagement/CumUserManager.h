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
   qint64 UpdateUser(CumUser* p_pUser);
   qint64 DeleteUser(QString p_qstrLogin);
   qint64 CreateUser(CumUser* p_pUser);
   qint64 LogOut();
   qint64 LogIn(QString p_qstrApplication,
               QString p_qstrLogin,
               QString p_qstrPassword,
               bool& p_bDemoMode,
               int& p_iModules,
               QString& p_qstrVersion);
   qint64 RenameUserGroup(qint64 p_lGroupId, QString p_qstrNewName);
   qint64 CreateUserGroup(QString p_qstrGroupName);
   qint64 DeleteUserGroup(qint64 p_llGroupId);
   qint64 AddUserToUserGroup(qint64 p_lUserId,qint64 p_lUserGroupId);
   qint64 RemoveUserFromGroup(qint64 p_lUserId,qint64 p_lUserGroupId);
    void LoadUserGroups();
   qint64 GetSessionId();
   qint64 GetCurrentUserId();
    CumUserGroup* FindUserGroupById(int p_iId);
    void GetUserBaseIds(QList<qint64>& p_rqllUserBaseIds);
    QVariant GetVariant() const;
    void ClearUsers();
    void ClearUserGroups();
   qint64 RegisterUser(QString p_qstrLogin,
                      QString p_qstrPassword,
                      QString p_qstrName,
                      QString p_qstrSurName,
                      QString p_qstrEmail,
                      QString p_qstrIdentKey);
    CumUser* FindUserByEmail(QString p_qstrUserEmail);
    CumUser* FindUserByLogin(QString p_qstrUserLogin);
   qint64 DeleteUser(qint64 p_lUserId);
    CumUser *FindUserByIdentityKey(QString p_qstrIdentityKey);
    QList<CumUser *> FindUsersUnmanaged(QString p_qstrSearchString);
   qint64 DeleteUserGroup(QString p_qstrGroup);
    CumUserGroup *FindUserGroupByName(QString p_qstrName);
   qint64 RemoveUserFromGroup(QString p_qstrLogin, QString p_qstrGroup);
   qint64 AddUserToUserGroup(QString p_qstrLogin, QString p_qstrGroup);
   qint64 RenameUserGroup(QString qstrOldName, QString p_qstrNewName);
    QList<CumUserGroup *> FindUserGroupsByNameUnmanaged(QString p_qstrName);
    QVariant GetGroupVariant() const;
    QString GetSchemeUri() const;

    bool IsCurrentUserAdmin();
public slots:
   qint64 GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups);
   qint64 GetListOfUsersInList(qint64 p_lUserGroupId, QList<CumUser*>& p_rqvlUserList);
   qint64 GetUserGroupMemberList(qint64 p_lUserId, QList<CumUserGroup*>& p_qvlUserGroups);
   qint64 GetUserListUnmanaged(QList<CumUser*>& p_rqvlUsers);
    CumUser* FindUserById(int p_iUserId);

};

#endif //
