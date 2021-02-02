/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiUser.cpp
 ** Started Implementation: 2012/04/15
 ** Description:
 **
 ** Implements a interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QVariant>

// WMS Includes
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "IdmDataAccess.h"

#include"CwmsContext.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiSessionlessAccess.h"
#include "CwiCommandChangePasswordSession.h"
#include "CwiCommandGetUserByIdentityKey.h"
#include "CwiCommandChangePasswordWithoutSession.h"
#include "CwiCommandUpdateUser.h"
#include "CwiCommandAddUser.h"
#include "CwiCommandGetUserByEmail.h"
#include "CwiCommandGetUserByLogin.h"
#include "CwiCommandGetUserById.h"
#include "CwiCommandRegisterCompany.h"
#include "CwiCommandRegisterUser.h"
#include "CwiCommandFindUsers.h"
#include "CwiUser.h"
#include "CdmLogging.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiUser::CwiUser                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiUser::CwiUser(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "User", true, true)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiUser::~CwiUser                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiUser                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiUser::~CwiUser()
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012-----------*
 * @method  CwiUser::ExecuteGet                      // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:18:13 2012-----------*/
void CwiUser::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {   
       QString qstrMode;
       if (p_pData->HasValue("Mode"))
       {
          qstrMode = p_pData->GetValue("Mode").toString();
          if (qstrMode ==  "Email")
          {
             GetUserByEmail(p_pData);
          }
          else if (qstrMode == "Login")
          {
              GetUserByLogin(p_pData);
          }
          else if (qstrMode == "IdentityKey")
          {
              GetUserByidentityKey(p_pData);
          }
          else if(qstrMode == "FindUsers")
          {
              GetFindUsers(p_pData);
          }
          else if(qstrMode == "UserId")
          {
              GetUserById(p_pData);
          }
       }
       else
       {
          CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
          int iUserId = p_pData->GetValue("UserId").toInt();

          if (iUserId > 0)
          {
             CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

             if (pCdmManager)
             {
                CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

                if (pCumUserManager)
                {
                   CumUser* pCumUser = pCumUserManager->FindUserById(iUserId);

                   if (pCumUser)
                   {
                      pResult->AddValue("User", pCumUser->GetVariant());
                      pResult->SetMessage("User found!");
                      pResult->SetMessageCode(1);
                      pResult->SetSeverity(eWmscomMessageServerityInfo);
                   }
                   else
                   {
                      pResult->SetMessage("User not found on Server");
                      pResult->SetMessageCode(-5000);
                      pResult->SetSeverity(eWmscomMessageServerityError);
                   }
                }
                else
                {
                   pResult->SetMessage("User Manager not found");
                   pResult->SetMessageCode(-5000);
                   pResult->SetSeverity(eWmscomMessageServerityFatal);
                }
             }
             else
             {
                pResult->SetMessage("Session not found");
                pResult->SetMessageCode(-5000);
                pResult->SetSeverity(eWmscomMessageServerityFatal);
             }
          }
       }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 11:47:14 2012----------*
 * @method  CwiUser::ExecutePut                           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 11:47:14 2012----------*/
void CwiUser::ExecutePut(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
       QString qstrMode;
       if (p_pData->HasValue("Mode"))
       {
          qstrMode = p_pData->GetValue("Mode").toString();
          if (qstrMode == "RegisterNewUser")
          {
             RegisterNewUser(p_pData);
          }
          else if(qstrMode == "RegisterNewCompany")
          {
              CwiCommandRegisterCompany command(p_pData);
              command.Execute();
          }
          else if(qstrMode == "AddUser")
          {
              AddUser(p_pData);
          }
          else if(qstrMode == "ChangePasswordWithoutSession")
          {
              ChangePasswordWithoutSession(p_pData);
          }
          else if(qstrMode == "ChangePasswordSession")
          {
              ChangePasswordSession(p_pData);
          }
          else if(qstrMode == "UpdateUser")
          {
              UpdateUser(p_pData);
          }
       }
       else
       {

           CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
           QVariant qUser = p_pData->GetValue("User");
           CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

           if (pCdmManager)
           {
             CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

             if (pCumUserManager)
             {
                int iSuccess = -5000;
                CumUser* pCumUser = new CumUser(qUser.toMap(), pCumUserManager);

                if (pCumUser->GetId() <= 0)
                {
                   int UserId = pCumUserManager->CreateUser(pCumUser);

                   if (UserId > 0)
                   {
                      pResult->AddValue("UserId", UserId);
                   }
                }
                else
                {
                   iSuccess = pCumUserManager->UpdateUser(pCumUser);
                }

                pResult->SetMessage("User created/updated!");
                pResult->SetMessageCode(iSuccess);
                pResult->SetSeverity(eWmscomMessageServerityInfo);

             }
             else
             {;
                pResult->SetMessage("User Manager not found");
                pResult->SetMessageCode(-5000);
                pResult->SetSeverity(eWmscomMessageServerityFatal);
             }
          }
          else
          {
             pResult->SetMessage("Session not found");
             pResult->SetMessageCode(-5000);
             pResult->SetSeverity(eWmscomMessageServerityFatal);
          }
       }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 11:47:08 2012----------*
 * @method  CwiUser::ExecuteDelete                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 11:47:08 2012----------*/
void CwiUser::ExecuteDelete(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      int iUserId = p_pData->GetValue("UserId").toInt();

      if (iUserId > 0)
      {
          CwiSessionlessAccess access;
          CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

         if (pCdmManager)
         {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if (pCumUserManager)
            {
               CumUser* pCumUser = pCumUserManager->FindUserById(iUserId);

               if (pCumUser)
               {
                  int iSuccess = pCumUserManager->DeleteUser(pCumUser->GetId());

                  if (iSuccess > 0)
                  {
                     pResult->SetMessage("User deleted on Server");
                     pResult->SetSeverity(eWmscomMessageServerityInfo);
                  }
                  else
                  {
                     pResult->SetMessage("User couldn't be deleted on Server");
                     pResult->SetSeverity(eWmscomMessageServerityError);
                  }
                  
                  pResult->SetMessageCode(iSuccess);
               }
               else
               {
                  pResult->SetMessage("User not found on Server");
                  pResult->SetMessageCode(0);
                  pResult->SetSeverity(eWmscomMessageServerityWarning);
               }
            }
            else
            {
               pResult->SetMessage("User Manager not found");
               pResult->SetMessageCode(-5000);
               pResult->SetSeverity(eWmscomMessageServerityFatal);
            }
         }
         else
         {
            pResult->SetMessage("Session not found");
            pResult->SetMessageCode(-5000);
            pResult->SetSeverity(eWmscomMessageServerityFatal);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiUser::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiUser::executeDescription(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      pResult->AddValue("UserId", "The User Id - Parameter");
      pResult->AddValue("User", "The found or to change/create User Object - Parameter / Result");
   }
}

/** +-=---------------------------------------------------------So 15. Apr 12:44:23 2012----------*
 * @method  CwiUser::GetResourceDescription               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 12:44:23 2012----------*/
QString CwiUser::GetResourceDescription()
{

   return "Finds updates, creates( for creating a new user the userid must be < 0) or deletes users on server";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:29:39 2013----------*
 * @method  CwiUser::GetVersion                           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:29:39 2013----------*/
QString CwiUser::getVersion()
{
   return "0.1.0";
}

void CwiUser::GetFindUsers(CwmscomData* p_pData)
{
    CwiCommandFindUsers command(p_pData);
    command.Execute();
}

void CwiUser::GetUserByLogin(CwmscomData* p_pData)
{
    CwiCommandGetUserByLogin command(p_pData);
    command.Execute();
}

void CwiUser::GetUserById(CwmscomData *p_pData)
{
    CwiCommandGetUserById command(p_pData);
    command.Execute();
}

void CwiUser::GetUserByidentityKey(CwmscomData* p_pData)
{
    CwiCommandGetUserByIdentityKey command(p_pData);
    command.Execute();
}

void CwiUser::GetUserByEmail(CwmscomData* p_pData)
{
    CwiCommandGetUserByEmail command(p_pData);
    command.Execute();
}

void CwiUser::AddUser(CwmscomData* p_pData)
{
    CwiCommandAddUser command(p_pData);
    command.Execute();
}

void CwiUser::UpdateUser(CwmscomData *p_pData)
{
    CwiCommandUpdateUser command(p_pData);
    command.Execute();
}


void CwiUser::ChangePasswordWithoutSession(CwmscomData* p_pData)
{
    CwiCommandChangePasswordWithoutSession command(p_pData);
    command.Execute();
}

void CwiUser::ChangePasswordSession(CwmscomData* p_pData)
{
    CwiCommandChangePasswordSession command(p_pData);
    command.Execute();
}

void CwiUser::RegisterNewUser(CwmscomData* p_pData)
{
    CwiCommandRegisterUser command(p_pData);
    command.Execute();
}
