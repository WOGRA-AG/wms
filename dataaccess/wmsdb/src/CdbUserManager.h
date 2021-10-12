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
#include <QList>

// own Includes
#include "CdmLocatedElement.h"
#include "CdbDataAccess.h"

// forwards
class CumUser;
class CumUserGroup;
class CdbDataAccess;



/*
 * This class implements db access to users and groups
 */
class WMSDB_API CdbUserManager
{
   protected:

	  /*
	   * The user and groups access
	   */
      CdbDataAccess* m_pCdbDataAccess;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:14:35 2005*
    * @method  CdbUserManager::CdbUserManager            // public                            *
    * @return                                                //                                   *
    * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:14:35 2005----------*/
CdbUserManager(  CdbDataAccess* p_pCdbDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:51:13 2005*
    * @method  CdbUserManager::~CdbUserManager           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdbUserManager                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 12:51:13 2005----------*/
virtual ~CdbUserManager(  );

   public:
virtual qint64 CreateUser(CumUser* p_pUser);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:15:01 2005*
    * @method  CdbUserManager::DeleteUser                  // public                            *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment This method deletes an user.                                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:15:01 2005----------*/
qint64 DeleteUser(QString p_qstrLogin);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:16:08 2005*
    * @method  CdbUserManager::FindUser                    // public                            *
    * @return  CumUser*                                      //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @param   QString p_qstrPassword                        //                                   *
    * @comment This method finds an user and returns it if found, if not null willr eturned.      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:16:08 2005----------*/
CumUser* FindUser(  QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri );

   public:
    virtual qint64 UpdateUser(CumUser* p_pUser);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:16:48 2005*
    * @method  CdbUserManager::GetUserList                 // public                            *
    * @return qint64                                          //                                   *
    * @param   QValueList<CumUser*>& p_qvlUsers              //                                   *
    * @comment This method returns a list of users from db.                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:16:48 2005----------*/
qint64 GetUserList(  QList<CumUser*>& p_qvlUsers );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:07 2005*
    * @method  CdbUserManager::ExistUser                   // public                            *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrLogin                           //                                   *
    * @comment returns true if the user exists or false if not.                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:07 2005----------*/
qint64 ExistUser(QString p_qstrLogin );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:40:05 2005*
    * @method  CdbUserManager::RenameUserGroup             // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lGroupId                               //                                   *
    * @param   QString p_qstrNewName                         //                                   *
    * @comment This method renames the Usergroup.                                                 *
    *----------------last changed: -----------------------------Mo 5. Sep 19:40:05 2005-----------*/
virtual qint64 RenameUserGroup( qint64 p_lGroupId, QString p_qstrNewName );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:40:44 2005*
    * @method  CdbUserManager::CreateUserGroup             // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param   QString p_qstrGroupName                       //                                   *
    * @comment This method creates a new usergroup.                                               *
    *----------------last changed: -----------------------------Mo 5. Sep 19:40:44 2005-----------*/
virtual qint64 CreateUserGroup(  QString p_qstrGroupName );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:20 2005*
    * @method  CdbUserManager::DeleteUserGroup             // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_llGroupId                              //                                   *
    * @comment This method deletes a usergroup.                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:20 2005----------*/
qint64 DeleteUserGroup( qint64 p_llGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:23 2005*
    * @method  CdbUserManager::AddUserToUserGroup          // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lUserId                                //                                   *
    * @param  qint64 p_lUserGroupId                           //                                   *
    * @comment This method adds an user to an usergroup.                                          *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:23 2005----------*/
qint64 AddUserToUserGroup( qint64 p_lUserId,qint64 p_lUserGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:26 2005*
    * @method  CdbUserManager::RemoveUserFromGroup         // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lUserId                                //                                   *
    * @param  qint64 p_lUserGroupId                           //                                   *
    * @comment This method removes an user from an usergroup.                                     *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:26 2005----------*/
qint64 RemoveUserFromGroup( qint64 p_lUserId,qint64 p_lUserGroupId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:29 2005*
    * @method  CdbUserManager::GetUserGroupList            // public                            *
    * @return qint64                                          //                                   *
    * @param   QValueList<CumUserGroup*>& p_rqvlUserGroups   //                                   *
    * @comment This method returns a list of all Usergroups.                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:29 2005----------*/
qint64 GetUserGroupList(  QList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:33 2005*
    * @method  CdbUserManager::GetListOfUsersInList        // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lUserGroupId                           //                                   *
    * @param   QValueList<CumUser*>& p_rqvlUserList          //                                   *
    * @comment This method returns a list of User in usergroup p_lUserGroupId.                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:33 2005----------*/
qint64 GetListOfUsersInList( qint64 p_lUserGroupId, QList<CumUser*>& p_rqvlUserList );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:37 2005*
    * @method  CdbUserManager::GetUserGroupMemberList      // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lUserId                                //                                   *
    * @param   QValueList<CumUserGroup*>& p_qvlUserGroups    //                                   *
    * @comment This method returns a list of groups in which a is member.                         *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:37 2005----------*/
qint64 GetUserGroupMemberList( qint64 p_lUserId, QList<CumUserGroup*>& p_qvlUserGroups );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:16:30 2005*
    * @method  CdbUserManager::FindUser                    // public                            *
    * @return  CumUser*                                      //                                   *
    * @param  qint64 p_lUserId                                //                                   *
    * @comment This emthod finds an user and returns it if found, if not null will returned.      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:16:30 2005----------*/
CumUser* FindUser( qint64 p_lUserId );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:17:49 2005*
    * @method  CdbUserManager::FindUserGroup               // public                            *
    * @return  CumUserGroup*                                 //                                   *
    * @param  qint64 p_lGroupId                               //                                   *
    * @comment This emthod returns the group with the id.                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 12:17:49 2005----------*/
CumUserGroup* FindUserGroup( qint64 p_lGroupId );

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

    CumUser *FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri);
    CumUser *FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri);

   qint64 DeleteUser(qint64 p_lUserId);
    QList<CumUser*> FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri);
    virtual CumUser* FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri);
    virtual CumUserGroup* FindUserGroupById(int p_iId);
    virtual CumUserGroup* FindUserGroupByName(QString p_qstrGroupName, QString p_qstrSchemeUri);
    QList<CumUserGroup *> FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri);
};

#endif //
