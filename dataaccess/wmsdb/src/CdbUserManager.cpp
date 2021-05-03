/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qsqlquery.h>
#include <qvariant.h>
#include <QList>
#include <QCryptographicHash>

// WMS Includes
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdbDataAccess.h"
#include "CdmLogging.h"
#include "CdmCrypt.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbCommandCreateUser.h"
#include "CdbCommandDeleteUser.h"
#include "CdbCommandFindUser.h"
#include "CdbCommandUpdateUser.h"
#include "CdbCommandExistUser.h"
#include "CdbCommandGetUserList.h"
#include "CdbCommandRenameUserGroup.h"
#include "CdbCommandCreateUserGroup.h"
#include "CdbCommandDeleteUserGroup.h"
#include "CdbCommandAddUserToUserGroup.h"
#include "CdbCommandRemoveUserFromUserGroup.h"
#include "CdbCommandGetUserGroupList.h"
#include "CdbCommandGetGroupUserList.h"
#include "CdbCommandFindUserGroup.h"
#include "CdbCommandFindGroups.h"
#include "CdbCommandFindUserGroupById.h"
#include "CdbCommandFindUserGroupByName.h"
#include "CdbCommandGetGroupsOfUser.h"
#include "CdbUserManager.h"


/** +-=---------------------------------------------------------Sa 20. Aug 12:14:35 2005----------*
 * @method  CdbUserManager::CdbUserManager               // public                            *
 * @return                                                   //                                   *
 * @param   CdbDataAccess* p_pCdbDataAccess              //                                   *
 * @comment The cosntructor.                                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:14:35 2005----------*/
CdbUserManager::CdbUserManager(  CdbDataAccess* p_pCdbDataAccess )
   : m_pCdbDataAccess(p_pCdbDataAccess)
{
   // nothing else to do
}


/** +-=---------------------------------------------------------Sa 20. Aug 12:51:13 2005----------*
 * @method  CdbUserManager::~CdbUserManager              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdbUserManager                                              *
 *----------------last changed: --------------------------------Sa 20. Aug 12:51:13 2005----------*/
CdbUserManager::~CdbUserManager(  )
{
   // nothing to do here
}

long CdbUserManager::CreateUser(CumUser* p_pUser)
{
    CdbCommandCreateUser command(p_pUser,
                                 m_pCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:15:01 2005----------*
 * @method  CdbUserManager::DeleteUser                     // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment This method deletes an user.                                                          *
 *----------------last changed: --------------------------------Sa 20. Aug 12:15:01 2005----------*/
long CdbUserManager::DeleteUser(  QString p_qstrLogin )
{
   CdbCommandDeleteUser command(p_qstrLogin, m_pCdbDataAccess);
   return command.Run();
}

long CdbUserManager::DeleteUser(long p_lUserId)
{
    CdbCommandDeleteUser command(p_lUserId, m_pCdbDataAccess);
    return command.Run();
}

CumUser *CdbUserManager::FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CdbCommandFindUser command(p_qstridentKey, p_qstrSchemeUri, m_pCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}


CumUser* CdbUserManager::FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CdbCommandFindUser command(p_qstrLogin, p_qstrPassword, p_qstrSchemeUri, m_pCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

/** +-=---------------------------------------------------------Sa 10. Mai 10:28:52 2008----------*
 * @method  CdbUserManager::CheckAuthorisationAdmin        // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 10. Mai 10:28:52 2008----------*/
bool CdbUserManager::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
{
   bool bRet = false;
   CumUser* pCumUser = FindUser(p_qstrLogin, p_qstrPassword, "");

   if (pCumUser)
   {
      if (pCumUser->IsActive())
      {
         bRet = pCumUser->IsAdministrator();
      }

      DELPTR(pCumUser);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 10. Mai 10:29:08 2008----------*
 * @method  CdbUserManager::CheckAuthorisation             // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @param   QString p_qstrPassword                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 10. Mai 10:29:08 2008----------*/
bool CdbUserManager::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
{
   bool bRet = false;
   CumUser* pCumUser = FindUser(p_qstrLogin, p_qstrPassword, "");

   if (pCumUser)
   {
      bRet = pCumUser->IsActive();
      DELPTR(pCumUser);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:16:30 2005----------*
 * @method  CdbUserManager::FindUser                       // public                            *
 * @return  CumUser*                                         //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @comment This emthod finds an user and returns it if found, if not nullptr will returned.         *
 *----------------last changed: --------------------------------Sa 20. Aug 12:16:30 2005----------*/
CumUser* CdbUserManager::FindUser(long p_lUserId)
{
    CumUser* pCumUser = nullptr;
    CdbCommandFindUser command(p_lUserId, m_pCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;

}

CumUser* CdbUserManager::FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CdbCommandFindUser command(p_qstrLogin, false, p_qstrSchemeUri, m_pCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

CumUser* CdbUserManager::FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CdbCommandFindUser command(p_qstrEmail, true, p_qstrSchemeUri, m_pCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

long CdbUserManager::UpdateUser(CumUser* p_pUser)
{
    CdbCommandUpdateUser command(p_pUser,
                                 m_pCdbDataAccess);

   return command.Run();
}

long CdbUserManager::GetUserList(QList<CumUser*>& p_qvlUsers)
{
    long lRet = 0;
    CdbCommandGetUserList command(m_pCdbDataAccess);
    lRet = command.Run();
    p_qvlUsers = command.GetResult();
    return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:07 2005----------*
 * @method  CdbUserManager::ExistUser                      // public                            *
 * @return  long                                             //                                   *
 * @param   QString p_qstrLogin                              //                                   *
 * @comment returns true if the user exists or false if not.                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:07 2005----------*/
long CdbUserManager::ExistUser(QString p_qstrLogin)
{
   CdbCommandExistUser command(p_qstrLogin, m_pCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:40:05 2005-----------*
 * @method  CdbUserManager::RenameUserGroup                // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   long p_lGroupId                                  //                                   *
 * @param   QString p_qstrNewName                            //                                   *
 * @comment This method renames the Usergroup.                                                    *
 *----------------last changed: --------------------------------Mo 5. Sep 19:40:05 2005-----------*/
long CdbUserManager::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    CdbCommandRenameUserGroup command(p_lGroupId, p_qstrNewName, m_pCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Mo 5. Sep 19:40:44 2005-----------*
 * @method  CdbUserManager::CreateUserGroup                // public, virtual                   *
 * @return  long                                             //                                   *
 * @param   QString p_qstrGroupName                          //                                   *
 * @comment This method creates a new usergroup.                                                  *
 *----------------last changed: --------------------------------Mo 5. Sep 19:40:44 2005-----------*/
long CdbUserManager::CreateUserGroup(QString p_qstrGroupName)
{
    CdbCommandCreateUserGroup command(p_qstrGroupName, m_pCdbDataAccess);
    return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:20 2005----------*
 * @method  CdbUserManager::DeleteUserGroup                // public                            *
 * @return  long                                             //                                   *
 * @param   long p_llGroupId                                 //                                   *
 * @comment This method deletes a usergroup.                                                      *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:20 2005----------*/
long CdbUserManager::DeleteUserGroup(long p_llGroupId)
{
   CdbCommandDeleteUserGroup command(p_llGroupId, m_pCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:23 2005----------*
 * @method  CdbUserManager::AddUserToUserGroup             // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @param   long p_lUserGroupId                              //                                   *
 * @comment This method adds an user to an usergroup.                                             *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:23 2005----------*/
long CdbUserManager::AddUserToUserGroup(long p_lUserId, long p_lUserGroupId)
{
   CdbCommandAddUserToUserGroup command(p_lUserId, p_lUserGroupId, m_pCdbDataAccess);
   return command.Run();
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:26 2005----------*
 * @method  CdbUserManager::RemoveUserFromGroup            // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @param   long p_lUserGroupId                              //                                   *
 * @comment This method removes an user from an usergroup.                                        *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:26 2005----------*/
long CdbUserManager::RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId)
{
    CdbCommandRemoveUserFromUserGroup command(p_lUserId, p_lUserGroupId, m_pCdbDataAccess);
    return command.Run();
}

long CdbUserManager::GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups, QString p_qstrSchemeUri)
{
   long lRet = CdmLogging::eDmUnknownUserQueryError;
   CdbCommandGetUserGroupList command(m_pCdbDataAccess, p_qstrSchemeUri);
   lRet = command.Run();
   p_rqvlUserGroups = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:33 2005----------*
 * @method  CdbUserManager::GetListOfUsersInList           // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lUserGroupId                              //                                   *
 * @param   QValueList<CumUser*>& p_rqvlUserList             //                                   *
 * @comment This method returns a list of User in usergroup p_lUserGroupId.                       *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:33 2005----------*/
long CdbUserManager::GetListOfUsersInList(long p_lUserGroupId,
                                          QList<CumUser*>& p_rqvlUserList)
{
   CdbCommandGetGroupUserList command(p_lUserGroupId, m_pCdbDataAccess);
   long lRet = command.Run();
   p_rqvlUserList = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:37 2005----------*
 * @method  CdbUserManager::GetUserGroupMemberList         // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lUserId                                   //                                   *
 * @param   QValueList<CumUserGroup*>& p_qvlUserGroups       //                                   *
 * @comment This method returns a list of groups in which a is member.                            *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:37 2005----------*/
long CdbUserManager::GetUserGroupMemberList(long p_lUserId,
                                            QList<CumUserGroup*>& p_qvlUserGroups)
{
   long lRet = CdmLogging::eDmUnknownUserQueryError;
   CdbCommandGetGroupsOfUser command(p_lUserId, m_pCdbDataAccess);
   lRet = command.Run();
   p_qvlUserGroups = command.GetResult();
   return lRet;
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:17:49 2005----------*
 * @method  CdbUserManager::FindUserGroup                  // public                            *
 * @return  CumUserGroup*                                    //                                   *
 * @param   long p_lGroupId                                  //                                   *
 * @comment This emthod returns the group with the id.                                            *
 *----------------last changed: --------------------------------Sa 20. Aug 12:17:49 2005----------*/
CumUserGroup* CdbUserManager::FindUserGroup(long p_lGroupId)
{
   CdbCommandFindUserGroup command(p_lGroupId, m_pCdbDataAccess);
   command.Run();
   return command.GetResult();
}

CumUserGroup* CdbUserManager::FindUserGroupByName(QString p_qstrGroupName, QString p_qstrSchemeUri)
{
    CdbCommandFindUserGroupByName command(p_qstrGroupName, p_qstrSchemeUri, m_pCdbDataAccess);
    command.Run();
    return command.GetResult();
}

CumUserGroup* CdbUserManager::FindUserGroupById(int p_iId)
{
    CdbCommandFindUserGroupById command(p_iId, m_pCdbDataAccess);
    command.Run();
    return command.GetResult();
}

QList<CumUser*> CdbUserManager::FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri)
{
    QList<CumUser*> lUsers;
    CdbCommandGetUserList command(p_qstrUserLoginNameEmail, p_qstrSchemeUri, m_pCdbDataAccess);
    command.Run();
    lUsers = command.GetResult();
    return lUsers;
}

QList<CumUserGroup*> CdbUserManager::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    CdbCommandFindGroups command(p_qstrName, p_qstrSchemeUri, m_pCdbDataAccess);
    command.Run();
    return command.GetResult();
}
