/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsSmtpManager.cpp
 ** Started Implementation: 2012/11/21
 ** Description:
 **
 ** implements the smtp manager.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMember.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// own Includes
#include "CwmsbtMailMessage.h"
#include "CwmsSmtpManager.h"


/** +-=---------------------------------------------------------Mi 21. Nov 10:26:33 2012----------*
 * @method  CwmsSmtpManager::CwmsSmtpManager                 // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:26:33 2012----------*/
CwmsSmtpManager::CwmsSmtpManager()
{
   if (!CheckDataStructure())
   {
      CreateDataStructure();
   }
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:26:41 2012----------*
 * @method  CwmsSmtpManager::~CwmsSmtpManager                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsSmtpManager                                               *
 *----------------last changed: --------------------------------Mi 21. Nov 10:26:41 2012----------*/
CwmsSmtpManager::~CwmsSmtpManager()
{
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:28:25 2012----------*
 * @method  CwmsSmtpManager::CheckDataStructure              // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:28:25 2012----------*/
bool CwmsSmtpManager::CheckDataStructure()
{
   bool bRet = false;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      CdmClassManager* pClassManager = pCdmManager->GetClassManager();

      if (pClassManager)
      {
          CdmClass* pClass = pClassManager->FindClassByKeyname("Technical_Smtp");
         if (pClass)
         {
             if (!pClass->FindMember("Smtp_Sender"))
             {
                CreateSender(pClass);
             }

             bRet = true;
         }
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:28:43 2012----------*
 * @method  CwmsSmtpManager::CreateDataStructure             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:28:43 2012----------*/
void CwmsSmtpManager::CreateDataStructure()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      CdmClassManager* pClassManager = pCdmManager->GetClassManager();

      if (pClassManager)
      {
         pClassManager->CreateClass("Technical_Smtp");
         CreateSmtpClass(pClassManager);
      }

      CdmContainerManager* pOLManager = pCdmManager->GetContainerManager();

      if (CHKPTR(pOLManager))
      {
         QString qstrObjectListKeyname = "SmtpSettings";
         pOLManager->CreateContainer("Technical_Smtp", 
                                      qstrObjectListKeyname, 
                                      tr("Smtp Konfiguration"), 
                                      tr("Smtp Einstellungen zur Versendung von E-Mails"));
      }
   }
}

/** +-=---------------------------------------------------------Mi 21. Nov 10:30:16 2012----------*
 * @method  CwmsSmtpManager::CreateSmtpClass                 // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pClassManager                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 10:30:16 2012----------*/
void CwmsSmtpManager::CreateSmtpClass(CdmClassManager* p_pClassManager)
{
   if (CHKPTR(p_pClassManager))
   {
      CdmClass* pCdmClass = p_pClassManager->FindClassByKeyname("Technical_Smtp");

      if (CHKPTR(pCdmClass))
      {
         pCdmClass->SetComment(tr("Smtp Einstellungen zur Versendung von Emails"));
         pCdmClass->SetCaption(tr("Smtp Konfiguration"));
         pCdmClass->SetCaptionMember("SmtpServer");
         CdmMember* pCdmMember = nullptr;

         pCdmMember = pCdmClass->CreateMember("Smtp_Server", 
                                              eDmValueString, 
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Der Name oder die IP Adresse des SMTP Servers"));
            pCdmMember->SetCaption(tr("SMTP Server"));
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Port", 
                                              eDmValueInt, 
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetDefaultValue(25);
            pCdmMember->SetComment(tr("Der Port des SMTP Servers"));
            pCdmMember->SetCaption(tr("SMTP Port"));
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Username", 
                                              eDmValueString, 
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Der Name des Benutzers der sich an den SMTP Server anmeldet."));
            pCdmMember->SetCaption(tr("SMTP Benutzername"));
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Password", 
                                              eDmValueString, 
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Das Passwort des Benutzers"));
            pCdmMember->SetCaption(tr("SMTP Passwort"));
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Sender",
                                              eDmValueString,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Die Adresse des Absenders, falls keine andere vorliegt."));
            pCdmMember->SetCaption(tr("Absende Adresse"));
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Authentification", 
                                              eDmValueEnum,
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Die Art der Authentifizierung am SMTP Servers"));
            pCdmMember->SetCaption(tr("Authentifizierung"));
            pCdmMember->SetValidationCode("Keine, Login, Plain");
         }

         pCdmMember = pCdmClass->CreateMember("Smtp_Encryption", 
                                              eDmValueEnum,
                                              false, 
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(tr("Die Art der Verschlüsselung am SMTP Servers"));
            pCdmMember->SetCaption(tr("Verschlüsselung"));
            pCdmMember->SetValidationCode("Keine, SSL, TLS");
         }


         pCdmClass->Commit();
      }
   }
}


void CwmsSmtpManager::CreateSender(CdmClass* p_pClass)
{
    CdmMember* pCdmMember = p_pClass->CreateMember("Smtp_Sender",
                                         eDmValueString,
                                         false,
                                         0);

    if(CHKPTR(pCdmMember))
    {
       pCdmMember->SetComment(tr("Die Adresse des Absenders, falls keine andere vorliegt."));
       pCdmMember->SetCaption(tr("Absende Adresse"));
    }
}

/** +-=---------------------------------------------------------Mi 21. Nov 16:20:15 2012----------*
 * @method  CwmsSmtpManager::GetSmtpConfiguration            // public                            *
 * @return  CwmsSmtpConfiguration*                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 16:20:15 2012----------*/
CwmsSmtpConfiguration* CwmsSmtpManager::GetSmtpConfiguration()
{
   CwmsSmtpConfiguration* pConfig = nullptr;
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = GetSmtpObject();

      if (CHKPTR(pCdmObject))
      {
         pConfig = new CwmsSmtpConfiguration(pCdmObject);
      }
   }

   return pConfig;
}

/** +-=---------------------------------------------------------Mi 21. Nov 11:42:19 2012----------*
 * @method  CwmsSmtpManager::GetSmtpObject                   // public                            *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 11:42:19 2012----------*/
CdmObject* CwmsSmtpManager::GetSmtpObject()
{
   CdmObject* pCdmObject = nullptr;
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      if (pContainer->CountObjectsOnDb() > 0)
      {
         CdmContainerManager* pManager = pContainer->GetContainerManager();

         if (CHKPTR(pManager))
         {
            pManager->ReloadContainerComplete(pContainer);
            QList<CdmObject*> qllObjects;
            pContainer->GetObjectList(qllObjects);
            pCdmObject = *qllObjects.begin();
         }
      }
      else
      {
         pCdmObject = pContainer->CreateNewObject();
      }
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 21. Nov 11:41:56 2012----------*
 * @method  CwmsSmtpManager::GetObjectList                   // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 21. Nov 11:41:56 2012----------*/
CdmObjectContainer* CwmsSmtpManager::GetObjectList()
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      pContainer = pCdmManager->GetObjectContainer("SmtpSettings");
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Di 8. Jan 17:18:47 2013-----------*
 * @method  CwmsSmtpManager::CreateMailMessage               // public                            *
 * @return  CwmsbtMailMessage*                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Jan 17:18:47 2013-----------*/
CwmsbtMailMessage*  CwmsSmtpManager::CreateMailMessage()
{
   CwmsbtMailMessage* pMessage = nullptr;
   CwmsSmtpConfiguration* pConfig = GetSmtpConfiguration();

   if (CHKPTR(pConfig))
   {
      pMessage = new CwmsbtMailMessage(pConfig);
   }

   return pMessage;
}
