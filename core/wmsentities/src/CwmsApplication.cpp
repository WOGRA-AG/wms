// System and QT Includes
#include <QtQml>


// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmObject.h"
#include "CdmDataProvider.h"
#include "CdmValueContainerRef.h"

// own Includes
#include "CwmsApplicationManager.h"
#include "CwmsApplication.h"

// Forwards

// Enumerations

CwmsApplication::CwmsApplication()
 : CdmObjectAdaptor()
{
}

CwmsApplication::CwmsApplication(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsApplication::~CwmsApplication()
{
}

QString CwmsApplication::GetName()
{
   return GetString("Name");
}

void CwmsApplication::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

QString CwmsApplication::GetDescription()
{
   return GetString("Description");
}

void CwmsApplication::SetDescription(QString p_qstrValue)
{
   SetValue("Description", p_qstrValue);
}

bool CwmsApplication::GetActive()
{
   return GetBool("Active");
}

void CwmsApplication::SetActive(bool p_bValue)
{
   SetValue("Active", p_bValue);
}

int CwmsApplication::GetVersionMajor()
{
   return GetInt("Version_Major");
}

QString CwmsApplication::GetVersion()
{
    return QString::number(GetVersionMajor()) + "." + QString::number(GetVersionMinor()) + "." + QString::number(GetVersionBugfix());
}

void CwmsApplication::SetVersionMajor(int p_iValue)
{
   SetValue("Version_Major", p_iValue);
}

int CwmsApplication::GetVersionMinor()
{
   return GetInt("Version_Minor");
}

void CwmsApplication::SetVersionMinor(int p_iValue)
{
   SetValue("Version_Minor", p_iValue);
}

int CwmsApplication::GetVersionBugfix()
{
   return GetInt("Version_Bugfix");
}

void CwmsApplication::SetVersionBugfix(int p_iValue)
{
   SetValue("Version_Bugfix", p_iValue);
}

QString CwmsApplication::GetHelp()
{
   return GetString("Help");
}

void CwmsApplication::SetHelp(QString p_qstrValue)
{
   SetValue("Help", p_qstrValue);
}

QString CwmsApplication::GetLicence()
{
   return GetString("Licence");
}

void CwmsApplication::SetLicence(QString p_qstrValue)
{
   SetValue("Licence", p_qstrValue);
}

QString CwmsApplication::GetManufacturer()
{
   return GetString("Manufacturer");
}

void CwmsApplication::SetManufacturer(QString p_qstrValue)
{
   SetValue("Manufacturer", p_qstrValue);
}

QString CwmsApplication::GetHotline()
{
   return GetString("Hotline");
}

void CwmsApplication::SetHotline(QString p_qstrValue)
{
   SetValue("Hotline", p_qstrValue);
}

QString CwmsApplication::GetEmail()
{
   return GetString("Email");
}

void CwmsApplication::SetEmail(QString p_qstrValue)
{
   SetValue("Email", p_qstrValue);
}

QString CwmsApplication::GetWebaddress()
{
   return GetString("Webaddress");
}

void CwmsApplication::SetWebaddress(QString p_qstrValue)
{
   SetValue("Webaddress", p_qstrValue);
}

bool CwmsApplication::GetDesktop()
{
   return GetBool("Desktop");
}

void CwmsApplication::SetDesktop(bool p_bValue)
{
   SetValue("Desktop", p_bValue);
}

bool CwmsApplication::GetMobile()
{
   return GetBool("Mobile");
}

void CwmsApplication::SetMobile(bool p_bValue)
{
   SetValue("Mobile", p_bValue);
}

CdmObject* CwmsApplication::GetMainWindow()
{
   return GetObjectRefValue("MainWindow");
}

void CwmsApplication::SetMainWindow(CdmObject* p_pObject)
{
   return SetObjectRefValue("MainWindow", p_pObject);
}

CdmObjectContainer* CwmsApplication::GetModules()
{
   return GetContainerRefValue("Modules");
}

CdmObjectContainer* CwmsApplication::GetTranslations()
{
   return GetContainerRefValue("RuntimeTranslations");
}

CdmObjectContainer* CwmsApplication::GetUserLanguages()
{
    return GetContainerRefValue("UserLanguages");
}

CdmObjectContainer *CwmsApplication::GetPlugins()
{
    return GetContainerRefValue("Plugins");
}

qint64 CwmsApplication::GetModulesId()
{
   return GetContainerRef("Modules");
}

bool CwmsApplication::GetLicenceCheck()
{
   return GetBool("Licence_Check");
}

void CwmsApplication::SetLicenceCheck(bool p_bValue)
{
   SetValue("Licence_Check", p_bValue);
}

bool CwmsApplication::GetWeb()
{
   return GetBool("Web");
}

void CwmsApplication::SetWeb(bool p_bValue)
{
    SetValue("Web", p_bValue);
}

QString CwmsApplication::GetModulesContainerName()
{
    QString qstrContainerName;
    CdmObjectContainer* pContainer = GetModules();

    if (CHKPTR(pContainer))
    {
        qstrContainerName = pContainer->GetKeyname();
    }

    return qstrContainerName;
}

QString CwmsApplication::GetMain()
{
    return GetString("Main");
}

void CwmsApplication::SetMain(QString p_qstrValue)
{
    SetValue("Main", p_qstrValue);
}

CwmsApplication CwmsApplication::Create()
{
   CwmsApplication cCwmsApplication;
   CwmsApplicationManager cAppManager;
   CdmObjectContainer* pContainer = cAppManager.GetObjectList();

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = pContainer->CreateNewObject();
      cCwmsApplication.SetObject(pCdmObject);
   }

   return cCwmsApplication;
}

bool CwmsApplication::Delete(CwmsApplication cCwmsApplication)
{
   bool bSuccess = false;
   if (cCwmsApplication.IsValid())
   {
      cCwmsApplication.SetDeleted();
      cCwmsApplication.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}

QString CwmsApplication::GetCurrentUserLanguage()
{
   QString qstrLanguage;
   CdmQueryEnhanced* pCdmQuery = CreateQuery();

   if (pCdmQuery && pCdmQuery->GetResultCount() > 0)
   {
      qstrLanguage = pCdmQuery->GetResultAt(0,0).toString();
   }

   DELPTR(pCdmQuery);
   return qstrLanguage;
}

void CwmsApplication::SetCurrentUserLanguage(QString p_qstrqsLanguage)
{
   CdmObject* pCdmObject = nullptr;
   CdmObjectContainer* pContainer = GetUserLanguages();

   if (CHKPTR(pContainer))
   {
     qint64 lObjectId;
      CdmQueryEnhanced* pCdmQuery = CreateQuery();

      if (pCdmQuery && pCdmQuery->GetResultCount() > 0)
      {
         lObjectId = pCdmQuery->GetObjectIdAt(0);

         if (lObjectId > 0)
         {
            pCdmObject = pContainer->FindObjectById(lObjectId);
         }
      }

      if (!pCdmObject)
      {
         pCdmObject = pContainer->CreateNewObject();
      }
   }

   if (CHKPTR(pCdmObject))
   {
      pCdmObject->SetValue("Language", p_qstrqsLanguage);
      pCdmObject->SetValue("User", pCdmObject->GetUserId());
      pCdmObject->Commit();
   }
}

CdmQueryEnhanced* CwmsApplication::CreateQuery()
{
   CdmQueryEnhanced* pCdmQuery = nullptr;
   CdmObjectContainer* pContainer = GetUserLanguages();

   if (CHKPTR(pContainer))
   {
      QString qstrWql = "select Language from \"" + 
         pContainer->GetKeyname() + 
         "\" where User = " + QString::number(pContainer->GetUserId());

      pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);
   }

   return pCdmQuery;
}

bool CwmsApplication::HasApplicationRight()
{

   bool bRet = false;
   CdmObjectContainer* pContainer = GetModules();

   if (CHKPTR(pContainer))
   {
      bRet = pContainer->CheckExplicitReadAccess();
   }

   return bRet;
}

QStringList CwmsApplication::GetModuleList()
{
    QStringList qstrlModules;
    CdmObjectContainer* pContainer = GetModules();

    if (CHKPTR(pContainer))
    {
       QString qstrWql =
               QString("select Name, Default, Position from \"%1\" where Active = true order by Position")
                .arg(pContainer->GetKeyname());

       CdmQueryEnhanced* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);
       int iResultCount = pCdmQuery->GetResultCount();

       for (int iCounter = 0; iCounter < iResultCount; ++iCounter)
       {
          QString qstrName = pCdmQuery->GetResultAt(0, iCounter).toString();
          qstrlModules.append(qstrName);
       }
    }

    return qstrlModules;
}


QStringList CwmsApplication::GetApplicationList(bool p_bDesktop, bool p_bWeb, bool p_bMobile)
{
   QStringList qstrlApps;
   CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainer("TechnicalApplications");

   if (pContainer)
   {
      CdmContainerManager* pManager = pContainer->GetContainerManager();
      if (CHKPTR(pManager))
      {
         pManager->ReloadContainerComplete(pContainer);
         QList<CdmObject*> qllObjects;
         pContainer->GetObjectList(qllObjects);
         QList<CdmObject*>::iterator qllIt = qllObjects.begin();
         QList<CdmObject*>::iterator qllItEnd = qllObjects.end();
         

         for (; qllIt != qllItEnd; ++qllIt)
         {
            CdmObject* pObject = (*qllIt);

            if (pObject && pObject->IsValid())
            {
               CwmsApplication cApp(pObject);

               if (cApp.HasApplicationRight() && !cApp.GetName().isEmpty() &&
                   ((cApp.GetDesktop() == true && p_bDesktop == true) ||
                    (cApp.GetWeb() == true && p_bWeb == true) ||
                    (cApp.GetMobile() == true && p_bMobile == true)))
               {
                   qstrlApps.append(cApp.GetName());
               }
            }
         }
      }
   }

   return qstrlApps;
}

CdmObject* CwmsApplication::GetApplication(QString p_qstrApplication)
{
   CdmObject* pCdmObject = nullptr;
   QString qstrWql = "select from TechnicalApplications where Name = \"" + p_qstrApplication + "\"";
   CdmQuery* pCdmQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

   if (pCdmQuery)
   {
      QList<qint64> qllResults = pCdmQuery->GetResultList();         

      if (qllResults.count() > 0)
      {
        qint64 lObjectId = *qllResults.begin();
         CdmObjectContainer* pContainer = CdmDataProvider::GetObjectContainer("TechnicalApplications");

         if (CHKPTR(pContainer))
         {
            pCdmObject = pContainer->FindObjectById(lObjectId);
         }
      }
   }

   return pCdmObject;        
}

CdmObject* CwmsApplication::LoadModule(qint64 p_lObjectId)
{
   CdmObject* pModule = nullptr;

   if (p_lObjectId > 0)
   {
      CdmObjectContainer* pCdmOLModules = GetModules();

      if (CHKPTR(pCdmOLModules))
      {
         pModule = pCdmOLModules->FindObjectById(p_lObjectId);
      }
   }

   return pModule;
}
CdmObject* CwmsApplication::LoadDefaultModule()
{
   CdmObject* pDefaultModule = 0;

   QString qstrWql = "select  from \"" + GetModulesContainerName() + "\" where and(Default = true, Active = true)";
   CdmQuery* pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::ExecuteQuery(qstrWql);
   int iResultCount = pCdmQuery->GetResultCount();

   if (iResultCount > 0)
   {
      pDefaultModule = pCdmQuery->GetFirstResultObject();

      if (iResultCount > 1)
      {
          WARNING("More than one default objects found. taking first.")
      }
   }

   return pDefaultModule;
}

QPixmap CwmsApplication::GetIcon()
{
    QPixmap qPixmap;
    if (!GetBinDocCurrentFilename("Icon").isEmpty())
    {
        QByteArray pByteArray = LoadBinDoc("Icon");
        qPixmap.loadFromData(pByteArray);
    }

    return qPixmap;
}

void CwmsApplication::SetIcon(QString p_qstrFilename)
{
    SetBinDocNewFilename("Icon", p_qstrFilename);
}
