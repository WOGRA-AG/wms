/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiDatabase.cpp
 ** Started Implementation: 2012/04/16
 ** Description:
 **
 ** Implements a interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"
#include "CdmJournalItem.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiCommandGetSchemeChanges.h"
#include "CwiCommandGetLanguages.h"
#include "CwiCommandCreateDatabase.h"
#include "CwiCommandUpdateDatabase.h"
#include "CwiCommandGetSchemeList.h"
#include "CwiCommandAddLanguage.h"
#include "CwiCommandGetServerSettings.h"
#include "CwiDatabase.h"
#include "CwiCommandGetAppStoreData.h"

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiDatabase::CwiDatabase                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiDatabase::CwiDatabase(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Database", true, true)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiDatabase::~CwiDatabase                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiDatabase                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiDatabase::~CwiDatabase()
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012-----------*
 * @method  CwiDatabase::ExecuteGet                      // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:18:13 2012-----------*/
void CwiDatabase::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      if (p_pData->HasValue("Mode"))
      {
         QString qstrMode = p_pData->GetValue("Mode").toString();

         if (qstrMode == "List")
         {
            GetList(p_pData);
         }
         else if (qstrMode == "Changes")
         {
             GetSchemeChanges(p_pData);
         }
         else if (qstrMode == "SupportedLanguages")
         {
             GetLanguages(p_pData);
         }
         else if (qstrMode == "ServerSettings")
         {
             GetServerSettings(p_pData);
         }
         else if (qstrMode == "GetAppstoreData")
         {
             GetAppstoreData(p_pData);
         }
      }
      else
      {
         CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
         CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
         CdmScheme* pCdmDatabase = nullptr;

         if (pCdmManager)
         {
            if (p_pData->HasValue("Id"))
            {
               pCdmDatabase = pCdmManager->FindSchemeById(p_pData->GetValue("Id").toInt());
            }
            else if (p_pData->HasValue("Name"))
            {
                QString qstrScheme = p_pData->GetValue("Name").toString();
               pCdmDatabase = pCdmManager->FindSchemeByName(qstrScheme);
            }
            
            if (pCdmDatabase)
            {
               pResult->AddValue("Database", pCdmDatabase->GetVariant());
			      pResult->SetMessage("Database found");
               pResult->SetMessageCode(1);
               pResult->SetSeverity(eWmscomMessageServerityInfo);
            }
            else
            {
               pResult->SetMessage("Database not found");
               pResult->SetMessageCode(-5000);
               pResult->SetSeverity(eWmscomMessageServerityError);
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

/** +-=---------------------------------------------------------Mo 16. Apr 16:34:42 2012----------*
 * @method  CwiDatabase::ExecutePut                       // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 16:34:42 2012----------*/
void CwiDatabase::ExecutePut(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
      CdmScheme* pCdmDatabase = nullptr;

      if (pCdmManager)
      {
         if (p_pData->HasValue("Id"))
         {
            pCdmDatabase = pCdmManager->FindSchemeById(p_pData->GetValue("Id").toInt());
         }

         QString qstrMode = p_pData->GetValue("Mode").toString();

         if (qstrMode == "AddLanguage")
         {
            AddLanguage(p_pData, pCdmDatabase);
         }
         else
         {
            if (pCdmDatabase)
            {
               UpdateDatabase(p_pData, pCdmDatabase);
            }
            else
            {
               CreateDatabase(p_pData);
            }
         }
      }
      else
      {
         GetResultContainer(p_pData,
                            -5000,
                            "Session not found!",
                            eWmscomMessageServerityFatal);
      }
   }
}

/** +-=---------------------------------------------------------Mo 16. Apr 16:34:34 2012----------*
 * @method  CwiDatabase::ExecuteDelete                    // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 16:34:34 2012----------*/
void CwiDatabase::ExecuteDelete(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
      CdmScheme* pCdmDatabase = nullptr;

      if (pCdmManager)
      {
          QString qstrScheme = p_pData->GetValue("Name").toString();

         if (p_pData->HasValue("Id"))
         {
            pCdmDatabase = pCdmManager->FindSchemeById(p_pData->GetValue("Id").toInt());
         }
         else if (p_pData->HasValue("Name"))
         {

            pCdmDatabase = pCdmManager->FindSchemeByName(qstrScheme);
         }

         if (pCdmDatabase)
         {
            if (pCdmManager->RemoveScheme(qstrScheme) > 0)
            {
               GetResultContainer(p_pData,
                                  1,
                                  "Scheme deleted!",
                                  eWmscomMessageServerityInfo);
            }
            else
            {
               GetResultContainer(p_pData,
                                  -5000,
                                  "Could not delete Scheme!",
                                  eWmscomMessageServerityError);
            }
         }
         else
         {
            GetResultContainer(p_pData,
                               -5000,
                               "Scheme not found!",
                               eWmscomMessageServerityFatal);
         }
      }
      else
      {
         GetResultContainer(p_pData,
                            -5000,
                            "Session not found!",
                             eWmscomMessageServerityFatal);
      }
   }
}


/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiDatabase::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiDatabase::executeDescription(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      // ToDo Result Parameters
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012-----------*
 * @method  CwiDatabase::GetResourceDescription               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:19:08 2012-----------*/
QString CwiDatabase::GetResourceDescription()
{
   return "Implements the WMS Database Interface usually you don't need it (except wms clients).";
}

/** +-=---------------------------------------------------------Fr 27. Apr 15:03:14 2012----------*
 * @method  CwiDatabase::GetList                          // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 27. Apr 15:03:14 2012----------*/
void CwiDatabase::GetList(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwiCommandGetSchemeList command(p_pData);
      command.Execute();
   }
}

/** +-=---------------------------------------------------------Mi 13. Feb 09:28:42 2013----------*
 * @method  CwiDatabase::AddLanguage                      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param   CdmDatabase* p_pDatabase                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 13. Feb 09:28:42 2013----------*/
void CwiDatabase::AddLanguage(CwmscomData* p_pData, CdmScheme* p_pDatabase)
{
  CwiCommandAddLanguage command(p_pData, p_pDatabase);
  command.Execute();
}

/** +-=---------------------------------------------------------Mi 13. Feb 09:29:46 2013----------*
 * @method  CwiDatabase::UpdateDatabase                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param   CdmDatabase* p_pDatabase                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 13. Feb 09:29:46 2013----------*/
void CwiDatabase::UpdateDatabase(CwmscomData* p_pData, CdmScheme* p_pDatabase)
{
    CwiCommandUpdateDatabase command(p_pData, p_pDatabase);
    command.Execute();
}

/** +-=---------------------------------------------------------Mi 13. Feb 09:31:21 2013----------*
 * @method  CwiDatabase::CreateDatabase                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 13. Feb 09:31:21 2013----------*/
void CwiDatabase::CreateDatabase(CwmscomData* p_pData)
{
    CwiCommandCreateDatabase command(p_pData);
    command.Execute();
}

void CwiDatabase::GetLanguages(CwmscomData *p_pData)
{
    CwiCommandGetLanguages command(p_pData);
    command.Execute();
}

void CwiDatabase::GetServerSettings(CwmscomData* p_pData)
{
    CwiCommandGetServerSettings command(p_pData);
    command.Execute();
}

void CwiDatabase::GetAppstoreData(CwmscomData* p_pData)
{
    CwiCommandGetAppStoreData command(p_pData);
    command.Execute();
}

void CwiDatabase::GetSchemeChanges(CwmscomData* p_pData)
{
    CwiCommandGetSchemeChanges command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 10. Okt 16:27:03 2013----------*
 * @method  CwiDatabase::GetVersion                       // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:27:03 2013----------*/
QString CwiDatabase::getVersion()
{
   return "0.1.0";
}
