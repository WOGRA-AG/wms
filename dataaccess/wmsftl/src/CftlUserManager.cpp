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
#include "CftlDataAccess.h"
#include "CdmLogging.h"
#include "CdmCrypt.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CftlCommandCreateUser.h"
#include "CftlCommandDeleteUser.h"
#include "CftlCommandFindUser.h"
#include "CftlCommandUpdateUser.h"
#include "CftlCommandExistUser.h"
#include "CftlCommandGetUserList.h"
#include "CftlCommandRenameUserGroup.h"
#include "CftlCommandCreateUserGroup.h"
#include "CftlCommandDeleteUserGroup.h"
#include "CftlCommandAddUserToUserGroup.h"
#include "CftlCommandRemoveUserFromUserGroup.h"
#include "CftlCommandGetUserGroupList.h"
#include "CftlCommandGetGroupUserList.h"
#include "CftlCommandFindUserGroup.h"
#include "CftlCommandFindGroups.h"
#include "CftlCommandGetGroupsOfUser.h"
#include "CwmsUtilities.h"
#include "CftlUserManager.h"


CftlUserManager::CftlUserManager(CftlDataAccess* p_pCftlDataAccess)
   : m_pCftlDataAccess(p_pCftlDataAccess)
{
   // nothing else to do
}

CftlUserManager::~CftlUserManager()
{
   // nothing to do here
}


long CftlUserManager::CreateUser(CumUser* p_pUser)
{
    CftlCommandCreateUser command(p_pUser,
                                 m_pCftlDataAccess);
    return command.Run();
}

long CftlUserManager::DeleteUser(QString p_qstrLogin)
{
   CftlCommandDeleteUser command(p_qstrLogin, m_pCftlDataAccess);
   return command.Run();
}

long CftlUserManager::DeleteUser(long p_lUserId)
{
    CftlCommandDeleteUser command(p_lUserId, m_pCftlDataAccess);
    return command.Run();
}


CumUser* CftlUserManager::FindUser(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_qstrLogin, p_qstrPassword, p_qstrSchemeUri, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

bool CftlUserManager::CheckAuthorisationAdmin(QString p_qstrLogin, QString p_qstrPassword)
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

bool CftlUserManager::CheckAuthorisation(QString p_qstrLogin, QString p_qstrPassword)
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

CumUser* CftlUserManager::FindUser(long p_lUserId)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_lUserId, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;

}

CumUser* CftlUserManager::FindUserByLogin(QString p_qstrLogin, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_qstrLogin, false, p_qstrSchemeUri, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

CumUser* CftlUserManager::FindUserByEmail(QString p_qstrEmail, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_qstrEmail, true, p_qstrSchemeUri, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

long CftlUserManager::UpdateUser(CumUser* p_pUser)
{
    CftlCommandUpdateUser command(p_pUser,
                                 m_pCftlDataAccess);

   return command.Run();
}

long CftlUserManager::GetUserList(QList<CumUser*>& p_qvlUsers)
{
    long lRet = 0;
    CftlCommandGetUserList command(m_pCftlDataAccess);
    lRet = command.Run();
    p_qvlUsers = command.GetResult();
    return lRet;
}

long CftlUserManager::ExistUser(QString p_qstrLogin)
{
   CftlCommandExistUser command(p_qstrLogin, m_pCftlDataAccess);
   return command.Run();
}

long CftlUserManager::RenameUserGroup(long p_lGroupId, QString p_qstrNewName)
{
    CftlCommandRenameUserGroup command(p_lGroupId, p_qstrNewName, m_pCftlDataAccess);
    return command.Run();
}

long CftlUserManager::CreateUserGroup(QString p_qstrGroupName)
{
    CftlCommandCreateUserGroup command(p_qstrGroupName, m_pCftlDataAccess);
    return command.Run();
}

long CftlUserManager::DeleteUserGroup(long p_llGroupId)
{
   CftlCommandDeleteUserGroup command(p_llGroupId, m_pCftlDataAccess);
   return command.Run();
}

long CftlUserManager::AddUserToUserGroup(long p_lUserId, long p_lUserGroupId)
{
   CftlCommandAddUserToUserGroup command(p_lUserId, p_lUserGroupId, m_pCftlDataAccess);
   return command.Run();
}

long CftlUserManager::RemoveUserFromGroup(long p_lUserId, long p_lUserGroupId)
{
    CftlCommandRemoveUserFromUserGroup command(p_lUserId, p_lUserGroupId, m_pCftlDataAccess);
    return command.Run();
}

long CftlUserManager::GetUserGroupList(QList<CumUserGroup*>& p_rqvlUserGroups)
{
   long lRet = CdmLogging::eDmUnknownUserQueryError;
   CftlCommandGetUserGroupList command(m_pCftlDataAccess);
   lRet = command.Run();
   p_rqvlUserGroups = command.GetResult();
   return lRet;
}

long CftlUserManager::GetListOfUsersInList(long p_lUserGroupId,
                                          QList<CumUser*>& p_rqvlUserList)
{
   CftlCommandGetGroupUserList command(p_lUserGroupId, m_pCftlDataAccess);
   long lRet = command.Run();
   p_rqvlUserList = command.GetResult();
   return lRet;
}

long CftlUserManager::GetUserGroupMemberList(long p_lUserId,
                                            QList<CumUserGroup*>& p_qvlUserGroups)
{
   long lRet = CdmLogging::eDmUnknownUserQueryError;
   CftlCommandGetGroupsOfUser command(p_lUserId, m_pCftlDataAccess);
   lRet = command.Run();
   p_qvlUserGroups = command.GetResult();
   return lRet;
}

CumUserGroup* CftlUserManager::FindUserGroup(long p_lGroupId)
{
   CftlCommandFindUserGroup command(p_lGroupId, m_pCftlDataAccess);
   command.Run();
   return command.GetResult();
}

QList<CumUser*> CftlUserManager::FindUser(QString p_qstrUserLoginNameEmail, QString p_qstrSchemeUri)
{
    QList<CumUser*> lUsers;
    CftlCommandGetUserList command(p_qstrUserLoginNameEmail, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        lUsers = command.GetResult();
    }

    return lUsers;
}

CumUser *CftlUserManager::FindUserByIdentKey(QString p_qstridentKey, QString p_qstrSchemeUri)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_qstridentKey, p_qstrSchemeUri, m_pCftlDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }

    return pCumUser;
}

CumUser* CftlUserManager::FindUserById(long p_lId)
{
    CumUser* pCumUser = nullptr;
    CftlCommandFindUser command(p_lId, m_pCftlDataAccess);

    if(SUCCESSFULL(command.Run()))
    {
        pCumUser = command.GetResult();
    }
    return pCumUser;
}

CumUserGroup* CftlUserManager::FindUserGroupById(int p_iId)
{
    CumUserGroup* pCumUserGroup = nullptr;
    CftlCommandFindUserGroup command(p_iId, m_pCftlDataAccess);

    if(SUCCESSFULL(command.Run())){
        pCumUserGroup = command.GetResult();
    }
    return pCumUserGroup;
}

CumUserGroup* CftlUserManager::FindUserGroupByName(QString p_qstrName, QString p_qstrSchemeUri)
{
    CumUserGroup* pCumUserGroup = nullptr;
    CftlCommandFindUserGroup command(p_qstrName, p_qstrSchemeUri, m_pCftlDataAccess);

    if(SUCCESSFULL(command.Run()))
    {
        pCumUserGroup = command.GetResult();
    }
    return pCumUserGroup;
}

QList<CumUserGroup*> CftlUserManager::FindUserGroups(QString p_qstrName, QString p_qstrSchemeUri)
{
    CftlCommandFindGroups command(p_qstrName, p_qstrSchemeUri, m_pCftlDataAccess);
    command.Run();
    return command.GetResult();
}
