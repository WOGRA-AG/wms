/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiUserList.cpp
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

// WMS INcludes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserManager.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiUserList.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiUserList::CwiUserList                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiUserList::CwiUserList(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "UserList", false, false)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiUserList::~CwiUserList                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiUserList                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiUserList::~CwiUserList()
{
}

/** +-=---------------------------------------------------------So 15. Apr 10:53:13 2012----------*
 * @method  CwiUserList::ExecuteGet                       // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 10:53:13 2012----------*/
void CwiUserList::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (pCdmManager)
      {
         CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

         if (pCumUserManager)
         {
            QLinkedList<CumUser*> qllUsers;
            pCumUserManager->GetUserListUnmanaged(qllUsers);
            QList<QVariant> qllResult;

            QLinkedList<CumUser*>::iterator qllIt = qllUsers.begin();
            QLinkedList<CumUser*>::iterator qllItEnd = qllUsers.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
               CumUser* pCumUser = *qllIt;

               if (pCumUser)
               {
                  QVariant qvUser = pCumUser->GetVariant();
                  qllResult.append(qvUser);
               }
            }

            pResult->AddValue("Users", qllResult);
            pResult->SetMessage("Returning User List");
            pResult->SetMessageCode(1);
            pResult->SetSeverity(eWmscomMessageServerityInfo);
         }
         else
         {
            pResult->SetMessage("Invalid UserManager pointer!");
            pResult->SetMessageCode(-5000);
            pResult->SetSeverity(eWmscomMessageServerityFatal);
         }   
      }
      else
      {
         pResult->SetMessage("Session not found!");
         pResult->SetMessageCode(-5000);
         pResult->SetSeverity(eWmscomMessageServerityFatal);
      }   
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiUserList::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiUserList::executeDescription(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Userlist");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      pResult->AddValue("Users", "List of Users - Result");
   }
}

/** +-=---------------------------------------------------------So 15. Apr 12:45:35 2012----------*
 * @method  CwiUserList::GetResourceDescription           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 12:45:35 2012----------*/
QString CwiUserList::GetResourceDescription()
{
   return "Returns the list of users from server";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:30:38 2013----------*
 * @method  CwiUserList::GetVersion                       // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:30:38 2013----------*/
QString CwiUserList::getVersion()
{
   return "0.1.0";
}
