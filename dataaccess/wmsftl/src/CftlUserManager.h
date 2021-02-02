/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CODBCUSERMANAGER_H
#define CODBCUSERMANAGER_H


// System and QT Includes
#include <qstring.h>
#include <QLinkedList>

// own Includes
#include "CdmLocatedElement.h"
#include "CftlDataAccess.h"

// forwards
class CumUser;
class CumUserGroup;
class CftlDataAccess;



/*
 * This class implements db access to users and groups
 */
class CftlUserManager
{
   protected:

	  /*
	   * The user and groups access
	   */
      CftlDataAccess* m_pCftlDataAccess;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:14:35 2005*
    * @method  CftlUserManager::CftlUserManager            // public                            *
    * @return                                                //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:14:35 2005----------*/
CftlUserManager(  CftlDataAccess* p_pCftlDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:51:13 2005*
    * @method  CftlUserManager::~CftlUserManager           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlUserManager                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 12:51:13 2005----------*/
virtual ~CftlUserManager(  );

   public:
virtual long CreateUser(CumUser* p_pUser);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:15:01 2005*
    * @method  CftlUserManager::DeleteUser                  // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment This method deletes an user.                                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:15:01 2005----------*/
long DeleteUser(  QString p_qstrLogin );

   public:
CumUser* FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri);

   public:
    virtual long UpdateUser(CumUser* p_pUser);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:16:48 2005*
    * @method  CftlUserManager::GetUserList                 // public                            *
    * @return  long                                          //                                   *
    * @param   QValueList<CumUser*>& p_qvlUsers              //                                   *
    * @comment This method returns a list of users from db.                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:16:48 2005----------*/
long GetUserList(  QLinkedList<CumUser*>& p_qvlUsers );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:07 2005*
    * @method  CftlUserManager::ExistUser                   // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment returns true if the user exists or false if not.                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:07 2005----------*/
long ExistUser(  QString p_qstrLogin );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:40:05 2005*
    * @method  CftlUserManager::RenameUserGroup             // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lGroupId                               //                                   *
    * @param   QString p_qstrNewName                         //                                   *
    * @comment This method renames the Usergroup.                                                 *
    *----------------last changed: -----------------------------Mo 5. Sep 19:40:05 2005-----------*/
virtual long RenameUserGroup(  long p_lGroupId, QString p_qstrNewName );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:40:44 2005*
    * @method  CftlUserManager::CreateUserGroup             // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   QString p_qstrGroupName                       //                                   *
    * @comment This method creates a new usergroup.                                               *
    *----------------last changed: -----------------------------Mo 5. Sep 19:40:44 2005-----------*/
virtual long CreateUserGroup(  QString p_qstrGroupName );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:20 2005*
    * @method  CftlUserManager::DeleteUserGroup             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_llGroupId                              //                                   *
    * @comment This method deletes a usergroup.                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:20 2005----------*/
long DeleteUserGroup(  long p_llGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:23 2005*
    * @method  CftlUserManager::AddUserToUserGroup          // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lUserId                                //                                   *
    * @param   long p_lUserGroupId                           //                                   *
    * @comment This method adds an user to an usergroup.                                          *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:23 2005----------*/
long AddUserToUserGroup(  long p_lUserId, long p_lUserGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:26 2005*
    * @method  CftlUserManager::RemoveUserFromGroup         // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lUserId                                //                                   *
    * @param   long p_lUserGroupId                           //                                   *
    * @comment This method removes an user from an usergroup.                                     *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:26 2005----------*/
long RemoveUserFromGroup(  long p_lUserId, long p_lUserGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:29 2005*
    * @method  CftlUserManager::GetUserGroupList            // public                            *
    * @return  long                                          //                                   *
    * @param   QValueList<CumUserGroup*>& p_rqvlUserGroups   //                                   *
    * @comment This method returns a list of all Usergroups.                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:29 2005----------*/
long GetUserGroupList(  QLinkedList<CumUserGroup*>& p_rqvlUserGroups );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:33 2005*
    * @method  CftlUserManager::GetListOfUsersInList        // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lUserGroupId                           //                                   *
    * @param   QValueList<CumUser*>& p_rqvlUserList          //                                   *
    * @comment This method returns a list of User in usergroup p_lUserGroupId.                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:33 2005----------*/
long GetListOfUsersInList(  long p_lUserGroupId, QLinkedList<CumUser*>& p_rqvlUserList );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:37 2005*
    * @method  CftlUserManager::GetUserGroupMemberList      // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lUserId                                //                                   *
    * @param   QValueList<CumUserGroup*>& p_qvlUserGroups    //                                   *
    * @comment This method returns a list of groups in which a is member.                         *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:37 2005----------*/
long GetUserGroupMemberList(  long p_lUserId, QLinkedList<CumUserGroup*>& p_qvlUserGroups );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:16:30 2005*
    * @method  CftlUserManager::FindUser                    // public                            *
    * @return  CumUser*                                      //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment This emthod finds an user and returns it if found, if not null will returned.      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:16:30 2005----------*/
CumUser* FindUser(long p_lUserId);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:49 2005*
    * @method  CftlUserManager::FindUserGroup               // public                            *
    * @return  CumUserGroup*                                 //                                   *
    * @param   long p_lGroupId                               //                                   *
    * @comment This emthod returns the group with the id.                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:49 2005----------*/
CumUserGroup* FindUserGroup(  long p_lGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 10. Mai 10:28:52 2008-------*
    * @method  CftlUserManager::CheckAuthorisationAdmin     // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 10. Mai 10:28:52 2008----------*/
    bool CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword);

   public:
   /** +-=---------------------------------------------------------Sa 10. Mai 10:29:08 2008-------*
    * @method  CftlUserManager::CheckAuthorisation          // public                            *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 10. Mai 10:29:08 2008----------*/
    bool CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword);

    CumUser *FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    CumUser *FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);

    long DeleteUser(long p_lUserId);
    CumUser *FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    QLinkedList<CumUser *> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    CumUser* FindUserById(long p_iId);
    CumUserGroup* FindUserGroupById(int p_lId);
    CumUserGroup* FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri);
    QLinkedList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
};

#endif //
