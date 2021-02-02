/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiLoginInt.cpp
 ** Started Implementation: 2012/04/08
 ** Description:
 **
 ** Implements the interface for logging into the application
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QThread>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmSettings.h"
#include "CumUser.h"
#include "wmsServerDefines.h"
#include "CdmDataProvider.h"

// WMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// BASETOOLS Includes
#include "CwmsApplicationServices.h"

// own Includes
#include "CwiLogin.h"
#include "CwiLoginInt.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:00:38 2012-----------*
 * @method  CwiLoginInt::CwiLoginInt                         // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:00:38 2012-----------*/
CwiLoginInt::CwiLoginInt(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "LoginInt", false, false)
{

}

/** +-=---------------------------------------------------------Mo 9. Apr 12:00:46 2012-----------*
 * @method  CwiLoginInt::~CwiLoginInt                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiLoginInt                                                   *
 *----------------last changed: --------------------------------Mo 9. Apr 12:00:46 2012-----------*/
CwiLoginInt::~CwiLoginInt()
{

}

/** +-=---------------------------------------------------------Fr 13. Apr 17:34:47 2012----------*
 * @method  CwiLoginInt::ExecuteGet                       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:34:47 2012----------*/
void CwiLoginInt::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
      int iSession = 0;
      QString qstrLogin = p_pData->GetValue("Login").toString();
      QString qstrPassword = p_pData->GetValue("Password").toString();
      
      if (qstrLogin.isEmpty() || qstrPassword.isEmpty())
      {
         executeDescription(p_pData);
      }
      else
      {
         CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
        iSession = CdmSessionManager::Login(qstrLogin, qstrPassword);

        if (iSession > 0)
        {
			CwmsApplicationServices::InstallFunctionsAndPlugins();
           pResult->SetMessage("Login succeeded. New Session established!");
           pResult->SetMessageCode(1);
           pResult->SetSeverity(eWmscomMessageServerityInfo);

           // Getting User
           CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

           if (pFactory)
           {
              pFactory->SetSessionThread(iSession);
              CdmDataProvider* pCdmManager = pFactory->FindDataProvider();

              if (pCdmManager)
              {
                 const CumUser* pCumUser = pCdmManager->GetUser();
                 QVariant qvUser = pCumUser->GetVariant();
                 pResult->AddValue("User", qvUser);
                 pResult->AddValue("Modules", pCdmManager->GetModulesId());
              }
           }
        }
        else
        {
           pResult->SetMessage("Login failed!");
           pResult->SetMessageCode(iSession);
           pResult->SetSeverity(eWmscomMessageServerityFatal);
        }
         
         pResult->AddValue("SessionId", iSession);
      }
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:34:42 2012-----------*
 * @method  CwiLoginInt::ExecuteDescription               // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:34:42 2012-----------*/
void CwiLoginInt::executeDescription(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      pResult->AddValue("Login", "String - Parameter");
      pResult->AddValue("Password", "String - Parameter");
      pResult->AddValue("SessionId", "Int - Result");
      pResult->AddValue("User", "User Object - Result");

   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:24:54 2012----------*
 * @method  CwiLoginInt::GetResourceDescription              // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:24:54 2012----------*/
QString CwiLoginInt::GetResourceDescription()
{
   return "This ressource is for wms to wms communication. it won't be needed for browserclients and returns aditionally the user object.";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:27:48 2013----------*
 * @method  CwiLoginInt::GetVersion                       // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:27:48 2013----------*/
QString CwiLoginInt::getVersion()
{
   return "0.1.0";
}
