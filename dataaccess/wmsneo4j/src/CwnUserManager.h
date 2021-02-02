#ifndef CWNUSERMANAGER_H
#define CWNUSERMANAGER_H

#include "CwnDataAccess.h"

// forwards
class CumUser;
class CumUserGroup;

class CwnUserManager
{
public:
    CwnUserManager(CwnDataAccess *p_pCwnDataAccess);
    virtual ~CwnUserManager();

    CwnDataAccess* m_pCwnDataAccess;

public:
/** +-=---------------------------------------------------------Mo 5. Sep 19:37:16 2005*
 * @method  CdbUserManager::CreateUser                  // public, virtual                   *
 * @return  long                                          //                                   *
 * @param   QString p_qstrSurName                         //                                   *
 * @param   QString p_qstrName                            //                                   *
 * @param   QString p_qstrLogin                           //                                   *
 * @param   QString p_qstrPassword                        //                                   *
 * @param   bool p_bAdministrator                         //                                   *
 * @comment This method creates an new user.                                                   *
 *----------------last changed: -----------------------------Mo 5. Sep 19:37:16 2005-----------*/
virtual long CreateUser(CumUser* p_pUser);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:15:01 2005*
 * @method  CdbUserManager::DeleteUser                  // public                            *
 * @return  long                                          //                                   *
 * @param   QString p_qstrLogin                           //                                   *
 * @comment This method deletes an user.                                                       *
 *----------------last changed: -----------------------------Sa 20. Aug 12:15:01 2005----------*/
long DeleteUser(QString p_qstrLogin );
long DeleteUser(long p_lUserId);

public:
CumUser* FindUser(long p_lUserId);
CumUser* FindUser(QString p_qstrLogin, QString p_qstrPassword );
QLinkedList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail);
virtual long UpdateUser(CumUser* p_pUser);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:16:48 2005*
 * @method  CdbUserManager::GetUserList                 // public                            *
 * @return  long                                          //                                   *
 * @param   QValueList<CumUser*>& p_qvlUsers              //                                   *
 * @comment This method returns a list of users from db.                                       *
 *----------------last changed: -----------------------------Sa 20. Aug 12:16:48 2005----------*/
long GetUserList(QLinkedList<CumUser*>& p_qvlUsers);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:07 2005*
 * @method  CdbUserManager::ExistUser                   // public                            *
 * @return  long                                          //                                   *
 * @param   QString p_qstrLogin                           //                                   *
 * @comment returns true if the user exists or false if not.                                   *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:07 2005----------*/
long ExistUser(QString p_qstrLogin);
public:
/** +-=---------------------------------------------------------Mo 5. Sep 19:40:05 2005*
 * @method  CdbUserManager::RenameUserGroup             // public, virtual                   *
 * @return  long                                          //                                   *
 * @param   long p_lGroupId                               //                                   *
 * @param   QString p_qstrNewName                         //                                   *
 * @comment This method renames the Usergroup.                                                 *
 *----------------last changed: -----------------------------Mo 5. Sep 19:40:05 2005-----------*/
virtual long RenameUserGroup(long p_lGroupId, QString p_qstrNewName);
public:
/** +-=---------------------------------------------------------Mo 5. Sep 19:40:44 2005*
 * @method  CdbUserManager::CreateUserGroup             // public, virtual                   *
 * @return  long                                          //                                   *
 * @param   QString p_qstrGroupName                       //                                   *
 * @comment This method creates a new usergroup.                                               *
 *----------------last changed: -----------------------------Mo 5. Sep 19:40:44 2005-----------*/
virtual long CreateUserGroup(QString p_qstrGroupName);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:20 2005*
 * @method  CdbUserManager::DeleteUserGroup             // public                            *
 * @return  long                                          //                                   *
 * @param   long p_llGroupId                              //                                   *
 * @comment This method deletes a usergroup.                                                   *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:20 2005----------*/
long DeleteUserGroup(long p_llGroupId);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:23 2005*
 * @method  CdbUserManager::AddUserToUserGroup          // public                            *
 * @return  long                                          //                                   *
 * @param   long p_lUserId                                //                                   *
 * @param   long p_lUserGroupId                           //                                   *
 * @comment This method adds an user to an usergroup.                                          *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:23 2005----------*/
long AddUserToUserGroup(long p_lUserId, long p_lUserGroupId);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:26 2005*
 * @method  CdbUserManager::RemoveUserFromGroup         // public                            *
 * @return  long                                          //                                   *
 * @param   long p_lUserId                                //                                   *
 * @param   long p_lUserGroupId                           //                                   *
 * @comment This method removes an user from an usergroup.                                     *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:26 2005----------*/
long RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:29 2005*
 * @method  CdbUserManager::GetUserGroupList            // public                            *
 * @return  long                                          //                                   *
 * @param   QValueList<CumUserGroup*>& p_rqvlUserGroups   //                                   *
 * @comment This method returns a list of all Usergroups.                                      *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:29 2005----------*/
long GetUserGroupList(QLinkedList<CumUserGroup*>& p_rqvlUserGroups);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:33 2005*
 * @method  CdbUserManager::GetListOfUsersInList        // public                            *
 * @return  long                                          //                                   *
 * @param   long p_lUserGroupId                           //                                   *
 * @param   QValueList<CumUser*>& p_rqvlUserList          //                                   *
 * @comment This method returns a list of User in usergroup p_lUserGroupId.                    *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:33 2005----------*/
long GetListOfUsersInList(long p_lUserGroupId, QLinkedList<CumUser*>& p_rqvlUserList);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:37 2005*
 * @method  CdbUserManager::GetUserGroupMemberList      // public                            *
 * @return  long                                          //                                   *
 * @param   long p_lUserId                                //                                   *
 * @param   QValueList<CumUserGroup*>& p_qvlUserGroups    //                                   *
 * @comment This method returns a list of groups in which a is member.                         *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:37 2005----------*/
long GetUserGroupMemberList(long p_lUserId, QLinkedList<CumUserGroup*>& p_qvlUserGroups);
public:
/** +-=---------------------------------------------------------Sa 20. Aug 12:17:49 2005*
 * @method  CdbUserManager::FindUserGroup               // public                            *
 * @return  CumUserGroup*                                 //                                   *
 * @param   long p_lGroupId                               //                                   *
 * @comment This emthod returns the group with the id.                                         *
 *----------------last changed: -----------------------------Sa 20. Aug 12:17:49 2005----------*/
CumUserGroup* FindUserGroup(long p_lGroupId);
CumUserGroup* FindUserGroupById(int p_iId);
CumUserGroup* FindUserGroupByName(QString p_qstrName);

public:
/** +-=---------------------------------------------------------Sa 10. Mai 10:28:52 2008-------*
 * @method  CdbUserManager::CheckAuthorisationAdmin     // public                            *
 * @return  bool                                          //                                   *
 * @param   QString p_qstrLogin                           //                                   *
 * @param   QString p_qstrPassword                        //                                   *
 * @comment                                                                                    *
 *----------------last changed: -----------------------------Sa 10. Mai 10:28:52 2008----------*/
bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);
public:
/** +-=---------------------------------------------------------Sa 10. Mai 10:29:08 2008-------*
 * @method  CdbUserManager::CheckAuthorisation          // public                            *
 * @return  bool                                          //                                   *
 * @param   QString p_qstrLogin                           //                                   *
 * @param   QString p_qstrPassword                        //                                   *
 * @comment                                                                                    *
 *----------------last changed: -----------------------------Sa 10. Mai 10:29:08 2008----------*/
bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);
CumUser *FindUserByEmail(QString p_qstrEmail);
CumUser *FindUserByLogin(QString p_qstrLogin);
virtual CumUser* FindUserByIdentKey(QString p_qstridentKey);
QLinkedList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
private:
/** +-=---------------------------------------------------------Fr 22. Jun 11:39:32 2012-------*
 * @method  CdbUserManager::EncryptAllPasswords         // private                           *
 * @return  void                                          //                                   *
 * @comment                                                                                    *
 *----------------last changed: -----------------------------Fr 22. Jun 11:39:32 2012----------*/
void EncryptAllPasswords();
};

#endif // CWNUSERMANAGER_H





