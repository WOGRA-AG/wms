/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFormManager.cpp
 ** Started Implementation: 2012/09/09
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmObject.h"
#include "CdmScheme.h"
#include "CdmValueBinaryDocument.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmMember.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"

// own Includes
#include "cwmsbtplattforminformation.h"
#include "CwmsFormManager.h"


/** +-=---------------------------------------------------------So 9. Sep 13:33:41 2012-----------*
 * @method  CwmsFormManager::CwmsFormManager                 // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:33:41 2012-----------*/
CwmsFormManager::CwmsFormManager()
{
   CheckFormDataStructure();
}

/** +-=---------------------------------------------------------So 9. Sep 13:33:50 2012-----------*
 * @method  CwmsFormManager::~CwmsFormManager                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFormManager                                               *
 *----------------last changed: --------------------------------So 9. Sep 13:33:50 2012-----------*/
CwmsFormManager::~CwmsFormManager()
{
}

/** +-=---------------------------------------------------------So 9. Sep 13:34:49 2012-----------*
 * @method  CwmsFormManager::CheckFormDataStructure          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:34:49 2012-----------*/
void CwmsFormManager::CheckFormDataStructure()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

      if (CHKPTR(pCdmClassManager))
      {
         CdmClass* pClass = pCdmClassManager->FindClassByKeyname("Technical_Form_Base");

         if (!pClass)
         {
            CreateFormClasses(pCdmClassManager);
         }

         pClass = pCdmClassManager->FindClassByKeyname("Technical_Form_Resources");

         if (pClass)
         {
             if(!pClass->FindMember("Name"))
             {
                 CreateFormResourceClass(pClass);
             }
         }

         pClass = pCdmClassManager->FindClassByKeyname("Technical_Form_Object");

         if (pClass)
         {
             if(!pClass->FindMember("Wql"))
             {
                 AddWqlMemberToClass(pClass);
                 pClass->UpdateVersion();
                 pClass->Commit();
             }
         }

         pClass = pCdmClassManager->FindClassByKeyname("Technical_Form_Interactive_Component");

         if (!pClass)
         {
            CreateInteractiveComponent();
         }
      }
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:35:23 2012-----------*
 * @method  CwmsFormManager::CreateFormClasses               // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClassManager* p_pCdmManager                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:35:23 2012-----------*/
void CwmsFormManager::CreateFormClasses(CdmClassManager* p_pCdmManager)
{
   if (CHKPTR(p_pCdmManager))
   {
      CdmClass* pCdmClassFormBase = p_pCdmManager->CreateClass("Technical_Form_Base");
      CdmClass* pCdmClassFormObjectList = p_pCdmManager->CreateClass("Technical_Form_ObjectList");
      CdmClass* pCdmClassFormUserDefined = p_pCdmManager->CreateClass("Technical_Form_UserDefined");
      CdmClass* pCdmClassFormObject = p_pCdmManager->CreateClass("Technical_Form_Object");
      CdmClass* pCdmClassFormView = p_pCdmManager->CreateClass("Technical_Form_View");
      CdmClass* pCdmClassFormLibrary = p_pCdmManager->CreateClass("Technical_Form_Library");
      CdmClass* pCdmClassFormStandardObjectList = p_pCdmManager->CreateClass("Technical_Form_Standard_ObjectList");
      CdmClass* pCdmClassFormObjectObjectList = p_pCdmManager->CreateClass("Technical_Form_Object_ObjectList");
      CdmClass* pCdmClassFormSearch = p_pCdmManager->CreateClass("Technical_Form_Search");
      
      CreateFormBaseClass(pCdmClassFormBase);
      CreateFormObjectClass(pCdmClassFormObject);
      CreateFormObjectListClass(pCdmClassFormObjectList);
      CreateFormObjectObjectListClass(pCdmClassFormObjectObjectList);
      CreateFormStandardObjectListClass(pCdmClassFormStandardObjectList);
      CreateFormUserDefinedClass(pCdmClassFormUserDefined);
      CreateFormViewClass(pCdmClassFormView);
      CreateFormSearchClass(pCdmClassFormSearch);
      CreateFormLibrary(pCdmClassFormLibrary);

      CreateObjectContainer(pCdmClassFormObject, "TechnicalFormObjects");
      CreateObjectContainer(pCdmClassFormObjectObjectList, "TechnicalFormObjectObjectLists");
      CreateObjectContainer(pCdmClassFormView, "TechnicalFormViewObjectLists");
      CreateObjectContainer(pCdmClassFormStandardObjectList, "TechnicalFormStandardObjectLists");
      CreateObjectContainer(pCdmClassFormUserDefined, "TechnicalFormUserDefined");
      CreateObjectContainer(pCdmClassFormSearch, "TechnicalFormSearch");
      CreateObjectContainer(pCdmClassFormLibrary, "TechnicalFormLibrary");
      CreateResource();
      CreateInteractiveComponent();
   }
}

void CwmsFormManager::CreateResource()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pCdmClassFormResources = pClassManager->CreateClass("Technical_Form_Resources");
            if (pCdmClassFormResources)
            {
                CreateFormResourceClass(pCdmClassFormResources);
            }
            else
            {
                pCdmClassFormResources = pClassManager->FindClassByKeyname("Technical_Form_Resources");
            }

            if (CHKPTR(pCdmClassFormResources))
            {            
                CreateObjectContainer(pCdmClassFormResources, "TechnicalFormResources");
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:42 2012----------*
 * @method  CwmsFormManager::GetFormUserDefinedContainer    // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:42 2012----------*/
CdmObjectContainer* CwmsFormManager::GetFormUserDefinedContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormUserDefined");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:34 2012----------*
 * @method  CwmsFormManager::GetFormViewContainer           // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:34 2012----------*/
CdmObjectContainer* CwmsFormManager::GetFormViewContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormViewObjectLists");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:26 2012----------*
 * @method  CwmsFormManager::GetFormObjectObjectContainer         // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:26 2012----------*/
CdmObjectContainer* CwmsFormManager::GetFormObjectObjectContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormObjectObjectLists");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:19 2012----------*
 * @method  CwmsFormManager::GetGenericFormContainer        // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:19 2012----------*/
CdmObjectContainer* CwmsFormManager::GetGenericFormContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormObjects");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:11 2012----------*
 * @method  CwmsFormManager::GetStandardFormContainer       // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:11 2012----------*/
CdmObjectContainer* CwmsFormManager::GetStandardFormContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormStandardObjectLists");
}

/** +-=---------------------------------------------------------Mo 10. Sep 16:53:11 2012----------*
 * @method  CwmsFormManager::GetFormLibrary       // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 16:53:11 2012----------*/
CdmObjectContainer* CwmsFormManager::GetFormLibrary()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormLibrary");
}


/** +-=---------------------------------------------------------Di 18. Sep 09:22:26 2012----------*
 * @method  CwmsFormManager::GetFormSearchObjectList         // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 18. Sep 09:22:26 2012----------*/
CdmObjectContainer* CwmsFormManager::GetFormSearchContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormSearch");
}

CdmObjectContainer* CwmsFormManager::GetResourceContainer()
{
   CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainer("TechnicalFormResources");

   if (!pContainer)
   {
       CreateResource();
       pContainer = CdmDataProvider::GetObjectContainer("TechnicalFormResources");
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Mo 10. Sep 09:52:35 2012----------*
 * @method  CwmsFormManager::GetOLManager                    // private                           *
 * @return  CdmContainerManager*                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 09:52:35 2012----------*/
CdmContainerManager* CwmsFormManager::GetContainerManager()
{
   CdmContainerManager* pRet = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
   {
      pRet = pCdmManager->GetContainerManager();
   }

   return pRet;
}

/** +-=---------------------------------------------------------Mo 10. Sep 09:55:54 2012----------*
 * @method  CwmsFormManager::CreateObjectList                // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Sep 09:55:54 2012----------*/
void CwmsFormManager::CreateObjectContainer(CdmClass* p_pCdmClass, QString p_qstrKeyname)
{
   CdmContainerManager* pOLManager = GetContainerManager();

   if (CHKPTR(p_pCdmClass) && CHKPTR(pOLManager))
   {
      pOLManager->CreateContainer(p_pCdmClass, p_qstrKeyname);
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:39:10 2012-----------*
 * @method  CwmsFormManager::CreateFormBaseClass             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:39:10 2012-----------*/
void CwmsFormManager::CreateFormBaseClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetAbstract(true);
      p_pCdmClass->SetCaption(tr("Formular_Basis"));
      p_pCdmClass->SetComment(tr("Basisklasse für alle Formulartypen"));

      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Name", eDmValueString, true,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Name"));
         pCdmMember->SetComment(tr("Der Name des Formulars"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Default", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Standard"));
         pCdmMember->SetComment(tr("Kennzeichen ob des sich um ein Standardformular für eine Klasse handelt."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Class_Uri", eDmValueString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Klasse"));
         pCdmMember->SetComment(tr("Zuordnung zur Klasse für die dieses Formular definiert wurde."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Print_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Druck möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob der Druck in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Journal_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Journalbafrage möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob die Abfrage des Änderungsjournals möglich sein soll."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Read_Only", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Nur lesender Zugriff"));
         pCdmMember->SetComment(tr("Kennzeichen ob das Formular nur lesenden Zugriff erlaubt."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Printing_Template", eDmValueObjectRef, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Druckvorlage"));
         pCdmMember->SetComment(tr("Die Druckvorlage, die mit diesem Formular verwendet werden soll."));
         pCdmMember->SetClassReference("Technical_Report");
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:40:04 2012-----------*
 * @method  CwmsFormManager::CreateFormObjectListClass       // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:40:04 2012-----------*/
void CwmsFormManager::CreateFormObjectListClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetAbstract(true);
      p_pCdmClass->AddBaseClass("Technical_Form_Base");
      p_pCdmClass->SetCaption(tr("Formular_Objektliste_Basis"));
      p_pCdmClass->SetComment(tr("Basisklasse für alle Objektlisten-Formulartypen"));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Export_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Export möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob der Datenexport in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Import_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Import möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob der Datenimport in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Search_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Suche möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob die Suche in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("SaveAsCsv_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Als CSV speichern möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob das Speichern als CSV in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("New_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Neues Objekt anlegen möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob die Anlage eines neuen Objektes in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Copy_Enabled", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Kopieren möglich"));
         pCdmMember->SetComment(tr("Kennzeichen ob das Kopieren eines Objektes in diesem Formular grundsätzlich möglich ist"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Functions", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Funktionen"));
         pCdmMember->SetComment(tr("Liste der Funktionen, die über Buttons aufgerufen werden sollen."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:40:21 2012-----------*
 * @method  CwmsFormManager::CreateFormObjectClass           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:40:21 2012-----------*/
void CwmsFormManager::CreateFormObjectClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_Base");
      p_pCdmClass->SetCaption(tr("Formular_Objekt"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von generischen Objektformularen."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Caption_Value", eDmValueString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Darstellungsname"));
         pCdmMember->SetComment(tr("Der Wert im Objekt, der den Darstellungsnamen übernimmt."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Visible_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Dargestellte Elemente"));
         pCdmMember->SetComment(tr("Die Members des Objekts, die dargestellt werden sollen (Unter Berücksichtigung der Reihenfolge)."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("ObjectRef_Assignment", eDmValueDictStringString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Auswahlmöglichkeiten Objektreferenz-Members"));
         pCdmMember->SetComment(tr("Die Zuordnung einer Auswahl (Objektliste oder WQL) zu einer Objektreferenz (<Member, ObjList oder WQL>)."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Default_Values", eDmValueDictStringString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Standardwerte"));
         pCdmMember->SetComment(tr("Die Standardwerte bei der Neuanlage eines Objekts."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Display_Types", eDmValueDictStringInt, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Darstellungsarten"));
         pCdmMember->SetComment(tr("Zuordnung von Darstellungsarten zu String-Members (<Member, Darstellungsart>)."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Functions", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Funktionen"));
         pCdmMember->SetComment(tr("Liste der Funktionen, die über Buttons aufgerufen werden sollen."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      AddWqlMemberToClass(p_pCdmClass);

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:40:42 2012-----------*
 * @method  CwmsFormManager::CreateFormUserDefinedClass      // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:40:42 2012-----------*/
void CwmsFormManager::CreateFormUserDefinedClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_Base");
      p_pCdmClass->SetCaption(tr("Formular_Benutzerdefiniert"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von benutzerdefinierten Formularen."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("UI_Code", eDmValueCharacterDocument, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Formularbeschreibung"));
         pCdmMember->SetComment(tr("Die Beschreibung des Formulars im JSon Format."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Web_Form", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Webformular"));
         pCdmMember->SetComment(tr("Das Formular ist für Internetbrowser geeignet."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Desktop_Form", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Desktopformular"));
         pCdmMember->SetComment(tr("Das Formular ist für Desktops geeignet."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Mobile_Form", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Mobileformular"));
         pCdmMember->SetComment(tr("Das Formular ist für Mobileendgeräte geeignet."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Tablet_Form", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Tabletformular"));
         pCdmMember->SetComment(tr("Das Formular ist für Tablets geeignet."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Context", eDmValueEnum, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Kontext"));
         pCdmMember->SetComment(tr("Der Kontext für den das Formular geeignet ist."));
         pCdmMember->SetValidationCode(tr("Objekt, Container, WMS Kontext"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      pCdmMember = p_pCdmClass->CreateMember("Form_Type", eDmValueEnum, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Formularart"));
         pCdmMember->SetComment(tr("Die Art des Formulars"));
         pCdmMember->SetValidationCode(tr("Dialog, Widget, Hauptfenster"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:41:07 2012-----------*
 * @method  CwmsFormManager::CreateFormViewClass             // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:41:07 2012-----------*/
void CwmsFormManager::CreateFormViewClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_ObjectList");
      p_pCdmClass->SetCaption(tr("Formular_Sichten_Objektliste"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von Formularen mit Objektlisten und Sichten."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Views", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Sichten"));
         pCdmMember->SetComment(tr("Zuordnung der Sichten."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------So 9. Sep 13:49:08 2012-----------*
 * @method  CwmsFormManager::CreateFormStandardObjectListClass // private                         *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:49:08 2012-----------*/
void CwmsFormManager::CreateFormStandardObjectListClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_ObjectList");
      p_pCdmClass->SetCaption(tr("Formular_Standard_Objektliste"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von Standardformularen für Objektlisten."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Display_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Dargestellte Felder"));
         pCdmMember->SetComment(tr("Auflistung der darzustellender Felder."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("View", eDmValueObjectRef, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Sicht"));
         pCdmMember->SetComment(tr("Die Sicht, die für dieses Formular verwendet werden soll."));
         pCdmMember->SetClassReference("Technical_View");
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Search_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Suchfelder"));
         pCdmMember->SetComment(tr("Auflistung der möglichen Suchfelder in der Suche."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 18:17:26 2012----------*
 * @method  CwmsFormManager::CreateFormSearchClass           // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 18:17:26 2012----------*/
void CwmsFormManager::CreateFormSearchClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_ObjectList");
      p_pCdmClass->SetCaption(tr("Formular_Suche_Objektliste"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von Suchformularen für Objektlisten."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Display_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Dargestellte Felder"));
         pCdmMember->SetComment(tr("Auflistung der darzustellender Felder."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("SearchList", eDmValueContainerRef, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Suchliste"));
         pCdmMember->SetComment(tr("Die Objektliste innerhalb der gesucht werden soll."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Search_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Suchfelder"));
         pCdmMember->SetComment(tr("Auflistung der möglichen Suchfelder in der Suche."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}


/** +-=---------------------------------------------------------So 9. Sep 13:49:25 2012-----------*
 * @method  CwmsFormManager::CreateFormObjectObjectListClass // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 9. Sep 13:49:25 2012-----------*/
void CwmsFormManager::CreateFormObjectObjectListClass(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->AddBaseClass("Technical_Form_Standard_ObjectList");
      p_pCdmClass->SetCaption(tr("Formular_Objekt_Objektliste"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von Formularen für Objektlisten. mit Objektbezug"));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Selection_Display_Members", eDmValueListString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("In Auswahl dargestellte Felder"));
         pCdmMember->SetComment(tr("Auflistung der darzustellender Felder in der Auswahl Objektliste."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Selection_List_ReadOnly", eDmValueBool, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Auswahl nur lesend"));
         pCdmMember->SetComment(tr("Kennzeichen ob auf die Auswahlliste nur lesende zugegriffen werden kann."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Editor_Keyname", eDmValueString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Editor_Schlüssel"));
         pCdmMember->SetComment(tr("Name des Objectreferenz Feld, dass für die Befüllung des Editors verantwortlich ist."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Editor_Wql", eDmValueCharacterDocument, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Editor_Abfrage"));
         pCdmMember->SetComment(tr("Abfrage für die Darstellung im Editor."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Selection_View", eDmValueObjectRef, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Auswahl_Sicht"));
         pCdmMember->SetComment(tr("Sicht für die Darstellung im Auswahlfenster."));
         pCdmMember->SetClassReference("Technical_View");
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Selection_ObjectList", eDmValueContainerRef, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Auswahl_Objektliste"));
         pCdmMember->SetComment(tr("Die im Auswahlfenster dargestellte Objektliste."));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->UpdateVersion();
      p_pCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Fr 14. Dez 11:26:44 2012----------*
 * @method  CwmsFormManager::GeDefaultObjectForm             // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 14. Dez 11:26:44 2012----------*/
CdmObject* CwmsFormManager::GeDefaultObjectForm(CdmObject* p_pCdmObject)
{
   CdmObject* pObject = nullptr;

   if (CHKPTR(p_pCdmObject))
   {
      CdmClass* pClass = p_pCdmObject->GetClass();

      if (CHKPTR(pClass))
      {
         QString qstrWQL = "select from TechnicalFormObjects where AND(Default = true, Class_Uri = \"" + pClass->GetUriInternal() +"\")";
         CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWQL);

         if (CHKPTR(pQuery))
         {
            QList<qint64> qllResults;
            qllResults = pQuery->GetResultList();

            if (qllResults.count() > 0)
            {
              qint64 lObjectId = (*qllResults.begin());
               CdmObjectContainer* pList = GetGenericFormContainer();

               if (CHKPTR(pList))
               {
                  pObject = pList->FindObjectById(lObjectId);
               }
            }
         }
      }
   }

   return pObject;
}

CdmObject* CwmsFormManager::GeDefaultContainerForm(CdmObjectContainer* p_pContainer)
{
	CdmObject* pObject = nullptr;

	if (p_pContainer) // can be nullptr(e.g. displaying views)
	{
		const CdmClass* pClass = p_pContainer->GetClass();

		if (CHKPTR(pClass))
		{
            QString qstrWQL = "select from TechnicalFormStandardObjectLists where AND(Default = true, Class_Uri = \"" + pClass->GetUriInternal() + "\")";
			CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWQL);

			if (CHKPTR(pQuery))
			{
				QList<qint64> qllResults;
				qllResults = pQuery->GetResultList();

				if (qllResults.count() > 0)
				{
					qint64 lObjectId = (*qllResults.begin());
					CdmObjectContainer* pList = GetStandardFormContainer();

					if (CHKPTR(pList))
					{
						pObject = pList->FindObjectById(lObjectId);
					}
				}
			}
		}
	}

	return pObject;
}

void CwmsFormManager::CreateFormLibrary(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      p_pCdmClass->SetCaption(tr("Formular_Bibliothek"));
      p_pCdmClass->SetComment(tr("Klasse für die Definition von Bibliothekselementen."));
      CdmMember* pCdmMember = nullptr;

      pCdmMember = p_pCdmClass->CreateMember("Name", eDmValueString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Name"));
         pCdmMember->SetComment(tr("Der Name der Library"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Version", eDmValueString, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Version"));
         pCdmMember->SetComment(tr("Die Versionsnummer der Library"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      pCdmMember = p_pCdmClass->CreateMember("Code", eDmValueCharacterDocument, false,0);

      if (CHKPTR(pCdmMember))
      {
         pCdmMember->SetCaption(tr("Code"));
         pCdmMember->SetComment(tr("Der Programmcode der Library"));
         pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
      }

      p_pCdmClass->Commit();
   }
}


void CwmsFormManager::CreateFormResourceClass(CdmClass* pCdmClassFormResources)
{
    if (CHKPTR(pCdmClassFormResources))
    {
       pCdmClassFormResources->SetCaption(tr("Resource_Bibliothek"));
       pCdmClassFormResources->SetComment(tr("Klasse für die Definition von QML Resourcen."));
       CdmMember* pCdmMember = nullptr;

       pCdmMember = pCdmClassFormResources->CreateMember("Name", eDmValueString, false,0);

       if (CHKPTR(pCdmMember))
       {
          pCdmMember->SetCaption(tr("Name"));
          pCdmMember->SetComment(tr("Der Name der Resource"));
          pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
       }

       pCdmMember = pCdmClassFormResources->CreateMember("Type", eDmValueEnum, false,0);

       if (CHKPTR(pCdmMember))
       {
          pCdmMember->SetCaption(tr("Typ"));
          pCdmMember->SetComment(tr("Art der Resource"));
          pCdmMember->SetValidationCode("Image, Pixmap");
          pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
       }

       pCdmMember = pCdmClassFormResources->CreateMember("Resource", eDmValueBinaryDocument, false,0);

       if (CHKPTR(pCdmMember))
       {
          pCdmMember->SetCaption(tr("Resource"));
          pCdmMember->SetComment(tr("Die Resource, die dagestellt werden soll."));
          pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
       }

       pCdmClassFormResources->Commit();
    }

}

void CwmsFormManager::AddWqlMemberToClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        CdmMember* pCdmMember = nullptr;

        pCdmMember = p_pClass->CreateMember("Wql", eDmValueCharacterDocument, false,0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(tr("Wql"));
           pCdmMember->SetComment(tr("Die Abfrage, die als Ergebnis das zu öffnende Objekt liefert."));
           pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
        }

    }
}

QString CwmsFormManager::GetClassUri(CdmModelElement* p_pElement)
{
    QString qstrClassUri;
    const CdmClass* pClass = nullptr;

    if (p_pElement->IsContainer())
    {
        pClass = (static_cast<CdmObjectContainer*> (p_pElement))->GetClass();
    }
    else if (p_pElement->IsObject())
    {
        pClass = (static_cast<CdmObject*> (p_pElement))->GetClass();
    }
    else
    {
        ERR("Wrong Element for loading UI");
    }

    if (CHKPTR(pClass))
    {
        qstrClassUri = pClass->GetUriInternal();
    }

    return qstrClassUri;
}

QString CwmsFormManager::GenerateWqlByClassUri(QString qstrClassUri, CdmObjectContainer* pContainer)
{
    CwmsbtPlattformInformation platformInfo;
    QString qstrWql;

    if (platformInfo.isDesktop())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Desktop_Form = true, Class_Uri = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(qstrClassUri);
    }
    else if (platformInfo.isMobile())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Mobile_Form = true, Class_Uri = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(qstrClassUri);
    }
    else if (platformInfo.isTablet())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Tablet_Form = true, Class_Uri = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(qstrClassUri);
    }

    return qstrWql;
}

QString CwmsFormManager::GenerateWqlByName(QString p_qstrName, CdmObjectContainer* pContainer)
{
    CwmsbtPlattformInformation platformInfo;
    QString qstrWql;

    if (platformInfo.isDesktop())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Desktop_Form = true, Name = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qstrName);
    }
    else if (platformInfo.isMobile())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Mobile_Form = true, Name = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qstrName);
    }
    else if (platformInfo.isTablet())
    {
        qstrWql = QString("select UI_Code from \"%1\" where and(Tablet_Form = true, Name = \"%2\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qstrName);
    }

    return qstrWql;
}

QString CwmsFormManager::GetUserDefinedUi(CdmObject* p_pElement)
{
	return GetUserDefinedUiForElement(p_pElement);
}

QString CwmsFormManager::GetUserDefinedUi(CdmObjectContainer* p_pElement)
{
	return GetUserDefinedUiForElement(p_pElement);
}

QString CwmsFormManager::GetUserDefinedUiForElement(CdmModelElement* p_pElement)
{
    QString qstrQml;

    if (CHKPTR(p_pElement))
    {
        CdmObjectContainer* pContainer = GetFormUserDefinedContainer();
        QString qstrClassUri = GetClassUri(p_pElement);


        if (CHKPTR(pContainer) && !qstrClassUri.isEmpty())
        {
            QString qstrWql = GenerateWqlByClassUri(qstrClassUri, pContainer);
            CdmQueryEnhanced* pQuery =
                    (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

            if (CHKPTR(pQuery))
            {
                int iResults = pQuery->GetResultCount();

                if (iResults > 0)
                {
                    qstrQml = pQuery->GetResultAt(0,0).toString();

                    if (iResults > 1)
                    {
                        WARNING("More than one result found. Taking first found");
                    }
                }
                else
                {
                    WARNING("No user defined UI found with Query: "+ qstrWql);
                }
            }
        }
    }

    return qstrQml;
}

QString CwmsFormManager::GetUserDefinedUi(QString p_qstrName)
{
    QString qstrQml;
    CdmObjectContainer* pContainer = GetFormUserDefinedContainer();

    if (CHKPTR(pContainer))
    {
        QString qstrWql = GenerateWqlByName(p_qstrName, pContainer);
        CdmQueryEnhanced* pQuery =
                (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

        if (CHKPTR(pQuery))
        {
            int iResults = pQuery->GetResultCount();

            if (iResults > 0)
            {
                qstrQml = pQuery->GetResultAt(0,0).toString();

                if (iResults > 1)
                {
                    WARNING("More than one result found. Taking first found");
                }
            }
            else
            {
                WARNING("No user defined UI found with Query: "+ qstrWql);
            }
        }
    }


    return qstrQml;
}

QString CwmsFormManager::GetWmsLibrary(QString p_qstrName, QString p_qstrVersion)
{
    QString qstrQml;
    CdmObjectContainer* pContainer = GetFormLibrary();

    if (CHKPTR(pContainer))
    {
        QString qstrWql = GenerateLibraryWql(p_qstrName, p_qstrVersion, pContainer);
        CdmQueryEnhanced* pQuery =
                (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);

        if (CHKPTR(pQuery))
        {
            int iResults = pQuery->GetResultCount();

            if (iResults > 0)
            {
                qstrQml = pQuery->GetResultAt(0,0).toString();

                if (iResults > 1)
                {
                    WARNING("More than one result found. Taking first found");
                }
            }
            else
            {
                WARNING("No user defined UI found with Query: "+ qstrWql);
            }
        }
    }

    return qstrQml;
}

QString CwmsFormManager::GenerateLibraryWql(QString p_qstrName,
                                            QString p_qstrVersion,
                                            CdmObjectContainer* pContainer)
{
    QString qstrWql;

        qstrWql = QString("select Code from \"%1\" where and(Name = \"%2\", Version = \"%3\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qstrName)
                .arg(p_qstrVersion);

    return qstrWql;
}

QByteArray CwmsFormManager::GetResource(QString p_qstrName, int p_iType)
{
    QByteArray qByteArray;
    CdmObjectContainer* pContainer = GetResourceContainer();

    if (CHKPTR(pContainer))
    {
        QString qstrWql = GenerateResourceWql(p_qstrName, p_iType, pContainer);

        CdmQuery* pQuery =CdmQueryBuilder::ExecuteQuery(qstrWql);

        if (CHKPTR(pQuery))
        {
            int iResults = pQuery->GetResultCount();

            if (iResults > 0)
            {
                CdmObject* pObject = pQuery->GetFirstResultObject();

                if (CHKPTR(pObject))
                {
                    CdmValue* pValue = pObject->GetValue("Resource");

                    if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
                    {
                        qByteArray = (static_cast<CdmValueBinaryDocument*>(pValue)->GetByteArray());
                    }
                }

                if (iResults > 1)
                {
                    WARNING("Resource \"" + p_qstrName + "\" of Type " + p_iType + "(0 = Image 1 = Pixmap) found more than once.\n Taking first.")
                }
            }
            else
            {
                ERR("Resource \"" + p_qstrName + "\" of Type " + p_iType + "(0 = Image 1 = Pixmap) not found.")
            }
        }
    }

    return qByteArray;
}

QString CwmsFormManager::GenerateResourceWql(QString p_qstrName,
                                            int p_iType,
                                            CdmObjectContainer* pContainer)
{
    QString qstrWql;

        qstrWql = QString("select from \"%1\" where and(Name = \"%2\", Type = \"%3\")")
                .arg(pContainer->GetKeyname())
                .arg(p_qstrName)
                .arg(p_iType);

    return qstrWql;
}

void CwmsFormManager::CreateInteractiveComponent()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pCdmManager))
    {
        CdmClassManager* pClassManager = pCdmManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->CreateClass("Technical_Form_Interactive_Component");

            if (pClass)
            {
                CreateInteractiveComponentClass(pClass);
            }
            else
            {
                pClass = pClassManager->FindClassByKeyname("Technical_Form_Interactive_Component");
            }

            if (CHKPTR(pClass))
            {
                CreateObjectContainer(pClass, "TechnicalFormInteractiveComponents");
            }
        }
    }
}

CdmObjectContainer* CwmsFormManager::GetInteractiveComponentContainer()
{
   return CdmDataProvider::GetObjectContainer("TechnicalFormInteractiveComponents");
}

void CwmsFormManager::CreateInteractiveComponentClass(CdmClass* pClass)
{
    if (CHKPTR(pClass))
    {
       pClass->SetCaption(tr("Interactive Component View"));
       pClass->SetComment(tr("Klasse für die Definition eines Interactive Component Views"));
       CdmMember* pCdmMember = nullptr;

       pCdmMember = pClass->CreateMember("View", eDmValueCharacterDocument, false,0);

       if (CHKPTR(pCdmMember))
       {
          pCdmMember->SetCaption(tr("View"));
          pCdmMember->SetComment(tr("Der View für Interactive Component."));
          pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
          pCdmMember->SetClassReference(1); // Unformated Text
       }

       pCdmMember = pClass->CreateMember("ViewModel", eDmValueCharacterDocument, false,0);

       if (CHKPTR(pCdmMember))
       {
          pCdmMember->SetCaption(tr("ViewModel"));
          pCdmMember->SetComment(tr("Das ViewModel für Interactive Component."));
          pCdmMember->SetMemberAccess(eDmMemberAccessPublic);
          pCdmMember->SetClassReference(1); // Unformated Text
       }

       pClass->AddBaseClass("Technical_Form_Base");
       pClass->Commit();
    }
}
