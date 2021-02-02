/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiLogin.cpp
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

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmSettings.h"
#include "CdmDataProvider.h"
#include "wmsServerDefines.h"

// BAsetools includes
#include "CwmsContext.h"

// WMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"
#include "CwmsSmtpManager.h"
#include "CwmsbtMailMessage.h"

// own Includes
#include "CwiLogin.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:00:38 2012-----------*
 * @method  CwiLogin::CwiLogin                         // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:00:38 2012-----------*/
CwiLogin::CwiLogin(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Login", false, false)
{

}

/** +-=---------------------------------------------------------Mo 9. Apr 12:00:46 2012-----------*
 * @method  CwiLogin::~CwiLogin                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiLogin                                                   *
 *----------------last changed: --------------------------------Mo 9. Apr 12:00:46 2012-----------*/
CwiLogin::~CwiLogin()
{

}

/** +-=---------------------------------------------------------Fr 13. Apr 17:34:47 2012----------*
 * @method  CwiLogin::ExecuteGet                          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:34:47 2012----------*/
void CwiLogin::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
       QString qstrMode;
       if (p_pData->HasValue("Mode"))
       {
          qstrMode = p_pData->GetValue("Mode").toString();
          if (qstrMode == "SmtpConfiguration")
          {
             getSmtpConfiguration(p_pData);
          }
       }
       else
       {
           QMutexLocker locker(&m_qMutex);
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
                 pResult->SetMessage("Login succeeded. New Session established!");
                 pResult->SetMessageCode(1);
                 pResult->SetSeverity(eWmscomMessageServerityInfo);
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
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:34:42 2012-----------*
 * @method  CwiLogin::ExecuteDescription                  // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:34:42 2012-----------*/
void CwiLogin::executeDescription(CwmscomData* p_pData)
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

   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:24:54 2012----------*
 * @method  CwiLogin::GetResourceDescription              // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:24:54 2012----------*/
QString CwiLogin::GetResourceDescription()
{
   return "This method tries to logon to the wms framework if successfull it returns a sessionid > 0.";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:27:22 2013----------*
 * @method  CwiLogin::GetVersion                          // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:27:22 2013----------*/
QString CwiLogin::getVersion()
{
   return "0.1.0";
}


void CwiLogin::getSmtpConfiguration(CwmscomData* p_pData)
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (!pCdmManager)
    {
        CwmsContext::GetContext()->ServerLogin();
        pCdmManager = CdmSessionManager::GetDataProvider();
    }

    CdmSessionManager*pSessionManager = CdmSessionManager::GetSessionManager();

    if (pSessionManager)
    {
        CdmDataProvider* pManager = pSessionManager->GetDataProvider();

        if(pManager)
        {
            QString qstrScheme = WMS_TECHNICAL_SERVER;
            pManager->LoadScheme(qstrScheme);
        }
    }

    CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
    CwmsSmtpManager cSmtpManager;
    CwmsbtMailMessage* pMailMessage = cSmtpManager.CreateMailMessage();

    if(pMailMessage)
    {
        CwmsSmtpConfiguration* config = (CwmsSmtpConfiguration*)pMailMessage->getSmtpConfigurations();
        //TODO put needed configurations in result
        pResult->SetMessage("Success");
        pResult->SetMessageCode(1);
        QVariantMap resultMap;
        resultMap.insert("Smtp_Port", config->GetSmtpPort());
        resultMap.insert("Smtp_Username", config->GetSmtpUsername());
        resultMap.insert("Smtp_Authentification", config->GetSmtpAuthentication());
        resultMap.insert("Smtp_Server", config->GetSmtpServer());
        resultMap.insert("Smtp_Password", config->GetSmtpPassword());
        resultMap.insert("Smtp_Sender", config->GetSmtpSender());
        resultMap.insert("Smtp_Encryption", config->GetSmtpEncryption());
        pResult->AddValue("Results", resultMap);
        pResult->SetSeverity(eWmscomMessageServerityInfo);
    }
    else
    {
        pResult->SetMessage("MailMessage not found");
        pResult->SetMessageCode(-5000);
        pResult->SetSeverity(eWmscomMessageServerityFatal);
    }

    CwmsContext::GetContext()->ServerLogout();
}
