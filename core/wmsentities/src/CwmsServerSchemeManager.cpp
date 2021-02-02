// System and Qt Includes
#include <QApplication>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmMember.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"

// Own Includes
#include "CwmsServerSchemeManager.h"


#define TECHNICALSCHEME "Technical_Server"

CwmsServerSchemeManager::CwmsServerSchemeManager()
{
}

CwmsServerSchemeManager::~CwmsServerSchemeManager()
{

}

void CwmsServerSchemeManager::CheckServerScheme()
{
    CheckScheme();
    CheckPlugins();
    CheckAppStore();
}

void CwmsServerSchemeManager::CheckScheme()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    QString qstrScheme = TECHNICALSCHEME;

    if (!ExistServerScheme())
    {

        pCdmManager->CreateScheme(qstrScheme);
    }
    else if(pCdmManager->GetCurrentScheme() == nullptr ||
            pCdmManager->GetCurrentScheme()->GetSchemeName() != qstrScheme)
    {
       pCdmManager->LoadScheme(qstrScheme);
    }
}

bool CwmsServerSchemeManager::ExistServerScheme()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    return pCdmManager->ExistScheme(TECHNICALSCHEME);
}

void CwmsServerSchemeManager::CheckPlugins()
{
    QString qstrScheme = TECHNICALSCHEME;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    CdmScheme* pScheme = pCdmManager->FindSchemeByName(qstrScheme);

    if (CHKPTR(pScheme))
    {
       CdmContainerManager* pContainerManager = pScheme->GetContainerManager();
       CdmClassManager* pClassManager = pScheme->GetClassManager();

       if (CHKPTR(pContainerManager) && CHKPTR(pClassManager))
       {
          if (!pClassManager->FindClassByKeyname("Technical_Plugins"))
          {
             pClassManager->CreateClass("Technical_Plugins");
             CreatePluginsClass(pClassManager);
             QString qstrKeyname = "TechnicalServerPlugins";
             pContainerManager->CreateContainer("Technical_Plugins",  qstrKeyname);
          }
       }
    }
}

void CwmsServerSchemeManager::CreatePluginsClass(CdmClassManager* p_pClassManager)
{
   if (CHKPTR(p_pClassManager))
   {
      CdmClass* pCdmClass = p_pClassManager->FindClassByKeyname("Technical_Plugins");

      if (CHKPTR(pCdmClass))
      {
         pCdmClass->SetComment(qApp->tr("Plugin Einstellungen des Schemas"));
         pCdmClass->SetCaption(qApp->tr("Plugins Konfiguration"));
         pCdmClass->SetCaptionMember("");
         CdmMember* pCdmMember = nullptr;

         pCdmMember = pCdmClass->CreateMember("Name",
                                              eDmValueString,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(qApp->tr("Der Name des Plugins"));
            pCdmMember->SetCaption(qApp->tr("Pluginname"));
         }

         pCdmMember = pCdmClass->CreateMember("Active",
                                              eDmValueBool,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetDefaultValue(true);
            pCdmMember->SetComment(qApp->tr("Aktiv Kennzeichen des Plugins"));
            pCdmMember->SetCaption(qApp->tr("Aktiv"));
         }

         pCdmMember = pCdmClass->CreateMember("Version",
                                              eDmValueString,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(qApp->tr("Die Versionsnummer des Plugins"));
            pCdmMember->SetCaption(qApp->tr("Version"));
         }

         pCdmMember = pCdmClass->CreateMember("Library",
                                                eDmValueString,
                                                false,
                                                0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(qApp->tr("Der Dateiname des Plugins"));
            pCdmMember->SetCaption(qApp->tr("Dateiname"));
         }

         pCdmMember = pCdmClass->CreateMember("Plugin_Type",
                                              eDmValueEnum,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(qApp->tr("Die Art des Plugins"));
            pCdmMember->SetCaption(qApp->tr("Typ"));
            pCdmMember->SetValidationCode(qApp->tr("Funktion, Server Funktion, Print Output, User Interface"));
         }

         pCdmMember = pCdmClass->CreateMember("Required",
                                              eDmValueBool,
                                              false,
                                              0);

         if(CHKPTR(pCdmMember))
         {
            pCdmMember->SetComment(qApp->tr("Pflichtplugin für Applikation"));
            pCdmMember->SetCaption(qApp->tr("Benötigt"));
         }

         pCdmClass->Commit();
      }
   }
}

void CwmsServerSchemeManager::CheckAppStore()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    QString qstrScheme = TECHNICALSCHEME;
    CdmScheme* pScheme = pCdmManager->FindSchemeByName(qstrScheme);

    if (CHKPTR(pScheme))
    {
        if (pScheme->GetVersion() < APP_STORE_VERSION)
        {
            CreateAppStore(pScheme);
        }
    }
}

void CwmsServerSchemeManager::CreateAppStore(CdmScheme* p_pScheme)
{
    if (CHKPTR(p_pScheme))
    {
        CdmContainerManager* pContainerManager = p_pScheme->GetContainerManager();
        CdmClassManager* pClassManager = p_pScheme->GetClassManager();

        if (CHKPTR(pContainerManager) && CHKPTR(pClassManager))
        {
            CdmClass* pClass = CreateAppStoreClass(pClassManager);

            if (CHKPTR(pClass))
            {
                CreateAppStoreContainer(pContainerManager, pClass);
            }

            p_pScheme->SetVersion(APP_STORE_VERSION);
            p_pScheme->Commit();
        }
    }
}

void CwmsServerSchemeManager::CreateAppStoreContainer(CdmContainerManager* p_pContainerManager, CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass) && CHKPTR(p_pContainerManager))
    {
        QString qstrContainerName = APP_STORE_CONTAINER_NAME;
        p_pContainerManager->CreateContainer(p_pClass, qstrContainerName);
    }
}

CdmClass* CwmsServerSchemeManager::CreateAppStoreClass(CdmClassManager* p_pClassManager)
{
    CdmClass* pClass = nullptr;

    if (CHKPTR(p_pClassManager))
    {
        pClass = p_pClassManager->CreateClass(APP_STORE_CLASS_NAME);

        if (CHKPTR(pClass))
        {
            pClass->SetCaption(qApp->tr("App Store"));
            pClass->SetComment(qApp->tr("Applikationsauswahl, die in einem Cloud Schema installiert werden können."));

            CdmMember* pCdmMember = nullptr;

            pCdmMember = pClass->CreateMember("Name",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Name"));
               pCdmMember->SetComment(qApp->tr("Der Name des Schemas"));
            }

            pCdmMember = pClass->CreateMember("Description",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Beschreibung"));
               pCdmMember->SetComment(qApp->tr("Beschreibung der Applikationen"));
            }

            pCdmMember = pClass->CreateMember("Sign",
                                                 eDmValueBinaryDocument,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Logo"));
               pCdmMember->SetComment(qApp->tr("Logo und Darstellung"));
            }

            pCdmMember = pClass->CreateMember("Applications",
                                                 eDmValueDictStringString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Applikationen"));
               pCdmMember->SetComment(qApp->tr("Applikationen und Versionen"));
            }

            pCdmMember = pClass->CreateMember("WDF",
                                                 eDmValueCharacterDocument,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Deployment Datei"));
               pCdmMember->SetComment(qApp->tr("Die Datei die alle wichtigen Informationen."));
            }

            pCdmMember = pClass->CreateMember("Manufacturer",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("Hersteller"));
               pCdmMember->SetComment(qApp->tr("Der Name des Herstellers"));
            }

            pCdmMember = pClass->CreateMember("E-Mail",
                                                 eDmValueString,
                                                 false,
                                                 0);

            if(CHKPTR(pCdmMember))
            {
               pCdmMember->SetCaption(qApp->tr("E-Mail"));
               pCdmMember->SetComment(qApp->tr("E-Mail des Herstellers"));
            }

            pClass->Commit();
        }
    }

    return pClass;
}
