/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsApplicationManager.cpp
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 ** manages the user defined applications in WMS Runtime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmScheme.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmContainerManager.h"
#include "CdmSessionManager.h"

// own Includes
#include "CwmsPluginManager.h"
#include "CwmsApplicationManager.h"

/** +-=---------------------------------------------------------Do 30. Aug 13:29:51 2012----------*
 * @method  CwmsApplicationManager::CwmsApplicationManager   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 13:29:51 2012----------*/
CwmsApplicationManager::CwmsApplicationManager()
{
   CheckApplicationDataStructure();
}

/** +-=---------------------------------------------------------Do 30. Aug 13:29:58 2012----------*
 * @method  CwmsApplicationManager::~CwmsApplicationManager  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsApplicationManager                                        *
 *----------------last changed: --------------------------------Do 30. Aug 13:29:58 2012----------*/
CwmsApplicationManager::~CwmsApplicationManager()
{
}

/** +-=---------------------------------------------------------Do 30. Aug 13:32:24 2012----------*
 * @method  CwmsApplicationManager::CheckApplicationDataStructure // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 13:32:24 2012----------*/
void CwmsApplicationManager::CheckApplicationDataStructure()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

      if (CHKPTR(pCdmClassManager))
      {
         CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname("Technical_Application");

         if (!pCdmClass)
         {
            CwmsPluginManager cPluginManager;
            CreateApplicationClass(pCdmClassManager);
         }
         else
         {
             if (!pCdmClass->FindMember("Main"))
             {
                 AddMainMethodToClass(pCdmClass);
                 pCdmClass->UpdateVersion();
                 pCdmClass->Commit();
             }

             if (!pCdmClass->FindMember("Icon"))
             {
                 AddIconToClass(pCdmClass);
                 pCdmClass->UpdateVersion();
                 pCdmClass->Commit();
             }
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 13:32:46 2012----------*
 * @method  CwmsApplicationManager::CreateApplicationClass   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 13:32:46 2012----------*/
void CwmsApplicationManager::CreateApplicationClass(CdmClassManager* p_pCdmClassManager)
{
   if (CHKPTR(p_pCdmClassManager))
   {
      CdmClass* pCdmClassAppModule = p_pCdmClassManager->CreateClass("Technical_Application_Module");
      CdmClass* pCdmClass = p_pCdmClassManager->CreateClass("Technical_Application");
      CdmClass* pCdmClassAppUserLanguage = p_pCdmClassManager->CreateClass("Technical_Application_User_Language");
      CdmClass* pCdmClassAppRuntime = p_pCdmClassManager->CreateClass("Technical_Application_Runtime_Translation");
      

      if (CHKPTR(pCdmClass))
      {
         pCdmClass->SetCaption(tr("Applikation"));
         pCdmClass->SetComment(tr("Speichert Applikationseinstellungen für den Aufruf über die Runtime"));
         CdmClassGroup* pCdmClassGroupInfo = pCdmClass->CreateGroup(tr("Information"), 1, nullptr);
         CdmClassGroup* pCdmClassGroupDetails = pCdmClass->CreateGroup(tr("Details"), 1, nullptr);
         CdmClassGroup* pCdmClassGroupApplicationType = pCdmClass->CreateGroup(tr("Applikationsart"), 1, nullptr);
         pCdmClass->Commit();

         CdmMember* pCdmMember = nullptr;
        
         pCdmMember = pCdmClass->CreateMember("Name", eDmValueString, true, 200);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Name"));
            pCdmMember->SetComment(tr("Name der Datensicht"));
            pCdmMember->SetGroup(pCdmClassGroupInfo);
            pCdmMember->SetUnique(true);
         }

         pCdmMember = pCdmClass->CreateMember("Description", eDmValueCharacterDocument, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Beschreibung"));
            pCdmMember->SetComment(tr("Beschreibung zur Applikation (Ziel und Zweck)"));
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("Active", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Aktiv"));
            pCdmMember->SetComment(tr("Eigenschaft ob die Applikation verwendet werden kann"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetDefaultValue("true");
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Version_Major", eDmValueInt, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Hauptversion"));
            pCdmMember->SetComment(tr("Der erste Teil der Versionsnummer"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Version_Minor", eDmValueInt, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Unterversion"));
            pCdmMember->SetComment(tr("Der zweite Teil der Versionsnummer"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Version_Bugfix", eDmValueInt, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Bugfix-Version"));
            pCdmMember->SetComment(tr("Der dritte Teil der Versionsnummer"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Help", eDmValueCharacterDocument, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Hilfe"));
            pCdmMember->SetComment(tr("Der Hilfetext für die Applikation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Licence", eDmValueCharacterDocument, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Lizenz"));
            pCdmMember->SetComment(tr("Der Lizenztext für die Applikation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Manufacturer", eDmValueString, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Hersteller"));
            pCdmMember->SetComment(tr("Der Hersteller der Applikation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Hotline", eDmValueString, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Support Hotline"));
            pCdmMember->SetComment(tr("Die Supporthotline des Herstellers"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Email", eDmValueString, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Support Email"));
            pCdmMember->SetComment(tr("Die Supportemailadresse des Herstellers"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Webaddress", eDmValueString, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Internetadresse"));
            pCdmMember->SetComment(tr("Die Internetadresse des Herstellers"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupInfo);
         }

         pCdmMember = pCdmClass->CreateMember("Desktop", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Desktop"));
            pCdmMember->SetComment(tr("Ist die Applikation eine Desktopanwendung."));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetDefaultValue("true");
            pCdmMember->SetGroup(pCdmClassGroupApplicationType);
         }

         pCdmMember = pCdmClass->CreateMember("Web", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Web"));
            pCdmMember->SetComment(tr("Ist die Applikation eine Webanwendung."));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupApplicationType);
         }

         pCdmMember = pCdmClass->CreateMember("Mobile", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Mobil"));
            pCdmMember->SetComment(tr("Ist die Applikation eine Mobile-App."));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupApplicationType);
         }

         pCdmMember = pCdmClass->CreateMember("Modules", eDmValueContainerRef, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Module"));
            pCdmMember->SetComment(tr("Module der Applikation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetOwner(true);
            pCdmMember->SetClassReference("Technical_Application_Module");
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("Plugins", eDmValueContainerRef, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Plugins"));
            pCdmMember->SetComment(tr("Pluginkonfiguration der Applikation"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetOwner(true);
            pCdmMember->SetClassReference("Technical_Plugins");
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("UserLanguages", eDmValueContainerRef, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Benutzersprachen"));
            pCdmMember->SetComment(tr("Die Spracheinstellungen der Benutzer"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
            pCdmMember->SetOwner(true);
            pCdmMember->SetClassReference("Technical_Application_User_Language");
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("RuntimeTranslations", eDmValueContainerRef, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Runtimeübersetzung"));
            pCdmMember->SetComment(tr("Die Übersetzung der Runtime in eine Sprache"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetOwner(true);
            pCdmMember->SetClassReference("Technical_Application_Runtime_Translation");
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("Licence_Check", eDmValueBool, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Lizenzprüfung"));
            pCdmMember->SetComment(tr("Soll die Lizenzprüfung bei dieser Anwendung aktiviert werden"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         pCdmMember = pCdmClass->CreateMember("MainWindow", eDmValueObjectRef, false, 0);

         if (CHKPTR(pCdmMember))
         {
            pCdmMember->SetCaption(tr("Hauptfenster"));
            pCdmMember->SetComment(tr("Das von der Applikation darzustellende Hauptfenster"));
            pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
            pCdmMember->SetClassReference("Technical_Form_Base");
            pCdmMember->SetGroup(pCdmClassGroupDetails);
         }

         AddMainMethodToClass(pCdmClass);
         pCdmClass->UpdateVersion();
         pCdmClass->Commit();

         CdmContainerManager* pCdmOLManager = pCdmClass->GetContainerManager();

         if (CHKPTR(pCdmOLManager))
         {
            QString qstrOLName = "TechnicalApplications";
            pCdmOLManager->CreateContainer(pCdmClass, qstrOLName);
         }
      }

      CreateAppModuleClass(pCdmClassAppModule);
      CreateUserLanguageClass(pCdmClassAppUserLanguage);
      CreateRuntimeTranslationClass(pCdmClassAppRuntime);
   }
}

void CwmsApplicationManager::AddMainMethodToClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        CdmMember* pCdmMember = nullptr;

        pCdmMember = p_pClass->CreateMember("Main", eDmValueString, false,0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(tr("Main Funktion"));
           pCdmMember->SetComment(tr("Die Funktion die aufgerufen soll, sobald sich der Anwender eingeloggt hat."));
           pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
        }
    }
}

void CwmsApplicationManager::AddIconToClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        CdmMember* pCdmMember = nullptr;

        pCdmMember = p_pClass->CreateMember("Icon", eDmValueBinaryDocument, false,0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(tr("Icon"));
           pCdmMember->SetComment(tr("Symbol für die Applikation"));
           pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
        }
    }
}


void CwmsApplicationManager::AddPluginsMember(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
       CdmMember* pCdmMember = nullptr;

        pCdmMember = p_pCdmClass->CreateMember("Plugins", eDmValueContainerRef, false, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(tr("Plugins"));
           pCdmMember->SetComment(tr("Pluginkonfiguration der Applikation"));
           pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
           pCdmMember->SetOwner(true);
           pCdmMember->SetClassReference("Technical_Plugins");
        }

        p_pCdmClass->Commit();
    }
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:02:43 2012-----------*
 * @method  CwmsApplicationManager::CreateUserLanguageClass  // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:02:43 2012-----------*/
void CwmsApplicationManager::CreateUserLanguageClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetCaption(tr("Benutzersprache"));
      p_pCdmClass->SetComment(tr("Speichert die Spracheinstellung der Benutzer."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("User", eDmValueUser, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Benutzer"));
         pCdmMember->SetComment(tr("Der von der Einstellung betroffene Benutzer."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Language", eDmValueString, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Sprache"));
         pCdmMember->SetComment(tr("Die gewählte Sprache."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:02:32 2012-----------*
 * @method  CwmsApplicationManager::CreateRuntimeTranslationClass // private                      *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:02:32 2012-----------*/
void CwmsApplicationManager::CreateRuntimeTranslationClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetCaption(tr("Runtimeübersetzung"));
      p_pCdmClass->SetComment(tr("Speichert die Übersetzung der Runtime in verschiedenen Sprachen."));

      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Language", eDmValueString, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Sprache"));
         pCdmMember->SetComment(tr("Die Übersetzungssprache."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Original", eDmValueString, true, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Original"));
         pCdmMember->SetComment(tr("Der Originaltext."));
         pCdmMember->SetMemberAccess(eDmMemberAccessProtected);
      }

      pCdmMember = p_pCdmClass->CreateMember("Translation", eDmValueString, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Übersetzung"));
         pCdmMember->SetComment(tr("Die Übersetzung."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 13:45:52 2012----------*
 * @method  CwmsApplicationManager::CreateAppModuleClass     // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 13:45:52 2012----------*/
void CwmsApplicationManager::CreateAppModuleClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetCaption(tr("Applikationsmodule"));
      p_pCdmClass->SetComment(tr("Speichert die Konfiguration der Applikationsmodule"));
      CdmClassGroup* pCdmClassGroupInfo = p_pCdmClass->CreateGroup(tr("Darstellung"), 1, nullptr);
      CdmClassGroup* pCdmClassGroupTechnical = p_pCdmClass->CreateGroup(tr("Technische Information"), 1, nullptr);
      p_pCdmClass->Commit();

      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Name", eDmValueString, true, 200);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Name"));
         pCdmMember->SetComment(tr("Name des Modules dargestellt in der Modulliste."));
         pCdmMember->SetGroup(pCdmClassGroupInfo);
      }

      pCdmMember = p_pCdmClass->CreateMember("ObjectList_Module", eDmValueContainerRef, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Objektlistenmodul"));
         pCdmMember->SetComment(tr("Modul als Objektliste"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupTechnical);
      }

      pCdmMember = p_pCdmClass->CreateMember("Object_Module", eDmValueObjectRef, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Objektmodul"));
         pCdmMember->SetComment(tr("Modul als Objekt"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupTechnical);
      }

      pCdmMember = p_pCdmClass->CreateMember("User_Interface", eDmValueObjectRef, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Oberflächendarstellung"));
         pCdmMember->SetComment(tr("Die Oberfläche, die für diese Modul beim Aufruf dargestellt werden soll."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupTechnical);
      }

      pCdmMember = p_pCdmClass->CreateMember("Default", eDmValueBool, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Standardmodul"));
         pCdmMember->SetComment(tr("Das Modul, dass nach Programmstart geöffnet wird."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupInfo);
      }

      pCdmMember = p_pCdmClass->CreateMember("Active", eDmValueBool, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Aktiv"));
         pCdmMember->SetComment(tr("Kennzeichen ob das Modul in der Applikation zur Verfügung steht."));
         pCdmMember->SetDefaultValue("true");
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupInfo);
      }

      pCdmMember = p_pCdmClass->CreateMember("Position", eDmValueInt, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Position"));
         pCdmMember->SetComment(tr("Die Position des Modules in der Modulliste."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupInfo);
      }

      pCdmMember = p_pCdmClass->CreateMember("View", eDmValueObjectRef, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Sicht"));
         pCdmMember->SetComment(tr("Die gefilterte Sicht der Liste"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
         pCdmMember->SetGroup(pCdmClassGroupTechnical);
         pCdmMember->SetClassReference("Technical_View");
      }

      pCdmMember = p_pCdmClass->CreateMember("Icon", eDmValueBinaryDocument, false, 0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Icon"));
         pCdmMember->SetComment(tr("Das Icon des Moduls."));
         pCdmMember->SetGroup(pCdmClassGroupInfo);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 13:31:06 2012----------*
 * @method  CwmsApplicationManager::GetObjectList            // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 13:31:06 2012----------*/
CdmObjectContainer* CwmsApplicationManager::GetObjectList()
{
   return CdmDataProvider::GetObjectContainer("TechnicalApplications");
}

/** +-=---------------------------------------------------------Do 30. Aug 16:16:51 2012----------*
 * @method  CwmsApplicationManager::GetApplication           // public                            *
 * @return  CwmsApplication                                  //                                   *
 * @param   int p_iObjectId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:16:51 2012----------*/
CwmsApplication CwmsApplicationManager::GetApplication(int p_iObjectId)
{
   CwmsApplication cApplication;
   CdmObjectContainer* pContainer = GetObjectList();

   if (CHKPTR(pContainer))
   {
      cApplication.SetObject(pContainer->FindObjectById(p_iObjectId));
   }

   return cApplication;
}

/** +-=---------------------------------------------------------Do 30. Aug 16:42:07 2012----------*
 * @method  CwmsApplicationManager::FindApplication          // public                            *
 * @return  CwmsApplication                                  //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 16:42:07 2012----------*/
CwmsApplication CwmsApplicationManager::FindApplication(QString p_qstrName)
{
   CwmsApplication cApplication;
   QString qstrQuery = "select from TechnicalApplications where Name = \"" + p_qstrName +"\"";

   CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrQuery);

   if (pQuery)
   {
      QList<qint64> qllResults = pQuery->GetResultList();

      if (qllResults.count() > 0)
      {
         cApplication = GetApplication(*(qllResults.begin()));
      }

      DELPTR(pQuery);
   }

   return cApplication;
}

/** +-=---------------------------------------------------------Do 30. Aug 14:44:05 2012----------*
 * @method  CwmsApplicationManager::GetApplicationList       // public                            *
 * @return  QStringList                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:44:05 2012----------*/
QStringList CwmsApplicationManager::GetApplicationList()
{
   QStringList qstrlApplications;

   QString qstrWql = "select Name from TechnicalApplications";

   CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

   if (pQuery)
   {
      for (int iCounter = 0; iCounter < pQuery->GetResultCount(); ++iCounter)
      {
         qstrlApplications.append(pQuery->GetResultAt(0,iCounter).toString());
      }

      DELPTR(pQuery);
   }

   return qstrlApplications;
}
