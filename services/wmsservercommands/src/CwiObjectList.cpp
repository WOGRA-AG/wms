/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiObjectContainer.cpp
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

// WMS Includes 
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmScheme.h"
#include "CdmQuery.h"
#include "CdmQuery.h"
#include "CdmContainerManager.h"
#include "CdmClass.h"
#include "CdmSession.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiCommandGetContainerList.h"
#include "CwiCommandDeleteObject.h"
#include "CwiCommandCreateObject.h"
#include "CwiCommandObjectListQuery.h"
#include "CwiCommandObjectListExist.h"
#include "CwiCommandObjectListGetNewId.h"
#include "CwiCommandRefreshObjectList.h"
#include "CwiObjectList.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiObjectContainer::CwiObjectContainer                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiObjectContainer::CwiObjectContainer(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "ObjectList", true, true)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiObjectContainer::~CwiObjectContainer                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiObjectContainer                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiObjectContainer::~CwiObjectContainer()
{
}

/** +-=---------------------------------------------------------So 15. Apr 14:29:56 2012----------*
 * @method  CwiObjectContainer::ExecuteGet                     // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:29:56 2012----------*/
void CwiObjectContainer::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      QString qstrMode;
     qint64 lObjectListId = 0;
      QString qstrKeyname;

      if (p_pData->HasValue("Mode"))
      {
         qstrMode = p_pData->GetValue("Mode").toString();
      }

      if (p_pData->HasValue("ObjectListId"))
      {
         lObjectListId =  p_pData->GetValue("ObjectListId").toInt();
      }
      else if (p_pData->HasValue("Keyname"))
      {
         qstrKeyname = p_pData->GetValue("Keyname").toString();
      }
      
     qint64 lDbId  =  p_pData->GetValue("DatabaseId").toInt();

     
      if (qstrMode == "Refresh")
      {
         Refresh(p_pData, lDbId, lObjectListId);
      }
      else if (qstrMode == "Count")
      {
         Count(p_pData, lDbId, lObjectListId);
      }
      else if (qstrMode == "EmptyList")
      {
         if (lObjectListId > 0)
         {
            GetEmptyList(p_pData, lDbId, lObjectListId);
         }
         else
         {
            GetEmptyList(p_pData, lDbId, qstrKeyname);
         }
      }
      else if (qstrMode == "CompleteList")
      {
         if (lObjectListId > 0)
         {
            GetCompleteList(p_pData, lDbId, lObjectListId);
         }
         else
         {
            GetCompleteList(p_pData, lDbId, qstrKeyname);
         }
      }
      else if (qstrMode == "NewId")
      {
         GetNewId(p_pData);
      }
      else if (qstrMode == "Exist")
      {
         Exist(p_pData);
      }
      else if (qstrMode == "Query")
      {
         Query(p_pData);
      }
      else if (qstrMode == "ContainerList")
      {
         GetContainerList(p_pData, lDbId);
      }
      else
      {
         if (lObjectListId > 0)
         {
            GetEmptyList(p_pData, lDbId, lObjectListId);
         }
         else
         {
            GetEmptyList(p_pData, lDbId, qstrKeyname);
         }
      }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 14:17:19 2012----------*
 * @method  CwiObjectContainer::ExecutePut                     // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:17:19 2012----------*/
void CwiObjectContainer::ExecutePut(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;

   if (CHKPTR(p_pData))
   {
      if (p_pData->HasValue("Mode"))
      {
         QString qstrMode = p_pData->GetValue("Mode").toString();

         if (qstrMode == "CreateObject")
         {
            CreateObject(p_pData);
         }
      }
      else
      {
         QVariantMap qvObjectList = p_pData->GetValue("ObjectList").toMap();
         int iDbId = qvObjectList["DatabaseId"].toInt();
         QString qstrKeyname = qvObjectList["Keyname"].toString();
         int iId = qvObjectList["Id"].toInt();

         CdmObjectContainer* pContainer = GetEmptyObjectList(iDbId, iId);

         if (pContainer)
         {
            pContainer->SetVariant(qvObjectList);

            const CdmClass *pClass = pContainer->GetClass();

            int iErrorCode = pContainer->Commit();

            if(pClass->IsEventClass())
            {
                saveEvent(pContainer);
            }

            if (iErrorCode > 0)
            {
               pResult = GetResultContainer(p_pData,
                                            1,
                                            "Objectlist updated!",
                                            eWmscomMessageServerityInfo);
               pResult->AddValue("ObjectList", pContainer->GetVariant());
            }
            else
            {
               pResult = GetResultContainer(p_pData,
                                            iErrorCode,
                                            "Error occurred",
                                            eWmscomMessageServerityError);
            }
         }
         else
         {
            pResult = GetResultContainer(p_pData,
                                         -5000,
                                         "ObjectList not found!",
                                         eWmscomMessageServerityError);
         }
      }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 14:17:10 2012----------*
 * @method  CwiObjectContainer::ExecuteDelete                  // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:17:10 2012----------*/
void CwiObjectContainer::ExecuteDelete(CwmscomData* p_pData)
{

   if (CHKPTR(p_pData))
   {
      if (p_pData->HasValue("Mode"))
      {
         QString qstrMode = p_pData->GetValue("Mode").toString();

         if (qstrMode == "DeleteObject")
         {
            DeleteObject(p_pData);
         }
      }
      else
      {
         int iId = p_pData->GetValue("ObjectListId").toInt();
         
         CdmObjectContainer* pContainer = GetEmptyObjectList(iId);

         if (pContainer)
         {
            pContainer->SetDeleted();

            if (pContainer->Commit() > 0)
            {
              GetResultContainer(p_pData,
                                1,
                                "Objectlist deleted!",
                                eWmscomMessageServerityInfo);
            }
            else
            {
               GetResultContainer(p_pData,
                                 -5000,
                                 "Objectlist deletion failed!",
                                 eWmscomMessageServerityError);
            }
        }
        else
        {
           GetResultContainer(p_pData,
                              -5000,
                              "Objectlist not found!",
                              eWmscomMessageServerityError);
        }
      }
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiObjectContainer::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiObjectContainer::executeDescription(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;

   if (p_pData)
   {
      pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      // ToDo Result Parameters
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012-----------*
 * @method  CwiObjectContainer::GetResourceDescription               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:19:08 2012-----------*/
QString CwiObjectContainer::GetResourceDescription()
{
   return "This resource manages objectlists";
}

/** +-=---------------------------------------------------------Mi 18. Apr 11:04:58 2012----------*
 * @method  CwiObjectContainer::GetEmptyObjectList             // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 11:04:58 2012----------*/
CdmObjectContainer* CwiObjectContainer::GetEmptyObjectList(qint64 p_lDatabaseId,qint64 p_lObjectListId)
{
   return GetObjectListInternal(p_lDatabaseId, p_lObjectListId, true);
}

/** +-=---------------------------------------------------------Di 1. Mai 11:31:59 2012-----------*
 * @method  CwiObjectContainer::GetEmptyObjectList             // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 1. Mai 11:31:59 2012-----------*/
CdmObjectContainer* CwiObjectContainer::GetEmptyObjectList(qint64 p_lObjectListId)
{
  qint64 lDbId = 0;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         lDbId = pCdmDatabase->GetId();
      }
   }

   return GetObjectListInternal(lDbId, p_lObjectListId, true);
}

/** +-=---------------------------------------------------------Mi 18. Apr 13:24:07 2012----------*
 * @method  CwiObjectContainer::GetEmptyObjectList             // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 13:24:07 2012----------*/
CdmObjectContainer* CwiObjectContainer::GetEmptyObjectList(qint64 p_lDatabaseId, QString p_qstrKeyname)
{
   return GetObjectListInternal(p_lDatabaseId, p_qstrKeyname, true);
}

/** +-=---------------------------------------------------------Mi 18. Apr 15:18:11 2012----------*
 * @method  CwiObjectContainer::GetObjectListInternal          // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param   QVariant qValue                                  //                                   *
 * @param   bool p_bEmpty                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 15:18:11 2012----------*/
CdmObjectContainer* CwiObjectContainer::GetObjectListInternal(qint64 p_lDatabaseId,
                                                       QVariant qValue,
                                                       bool p_bEmpty)
{
   CdmObjectContainer* pContainer = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
   bool bConvert = false;
   int iId = qValue.toInt(&bConvert);
   QString qstrKeyname;

   if (!bConvert)
   {
      iId = -1;
      qstrKeyname = qValue.toString();
   }


   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pOLManager = pCdmManager->GetContainerManager(p_lDatabaseId);

      if (CHKPTR(pOLManager))
      {
         if (iId == -1)
         {
            if (p_bEmpty)
            {
               pContainer = pOLManager->FindEmptyContainerByKeyname(qstrKeyname);
            }
            else
            {
               pContainer = pOLManager->FindContainerByKeyname(qstrKeyname);

               if (CHKPTR(pContainer))
               {
                  pOLManager->ReloadContainerComplete(pContainer);
               }
            }
         }
         else
         {
            if (p_bEmpty)
            {
               pContainer = pOLManager->FindEmptyContainerById(iId);
            }
            else
            {
               pContainer = pOLManager->FindContainerById(iId);

               if (CHKPTR(pContainer))
               {
                  pOLManager->ReloadContainerComplete(pContainer);
               }
            }
         }
      }
   }

   return pContainer;
}


/** +-=---------------------------------------------------------Mi 18. Apr 18:22:21 2012----------*
 * @method  CwiObjectContainer::GetCompleteObjectList          // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 18:22:21 2012----------*/
CdmObjectContainer* CwiObjectContainer::GetCompleteObjectList(qint64 p_lDatabaseId,qint64 p_lObjectListId)
{
   return GetObjectListInternal(p_lDatabaseId, p_lObjectListId, false);
}

/** +-=---------------------------------------------------------Mi 18. Apr 13:23:28 2012----------*
 * @method  CwiObjectContainer::GetCompleteObjectList          // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 13:23:28 2012----------*/
CdmObjectContainer* CwiObjectContainer::GetCompleteObjectList(qint64 p_lDatabaseId, QString p_qstrKeyname)
{
   return GetObjectListInternal(p_lDatabaseId, p_qstrKeyname, false);
}


/** +-=---------------------------------------------------------Mi 18. Apr 10:53:25 2012----------*
 * @method  CwiObjectContainer::Refresh                        // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_ObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:53:25 2012----------*/
void CwiObjectContainer::Refresh(CwmscomData* p_pData,qint64 p_lDbId,qint64 p_ObjectListId)
{
    CwmscomDataResult* pResult = nullptr;
    CdmObjectContainer* pContainer = GetEmptyObjectList(p_lDbId, p_ObjectListId);

    if (pContainer)
    {
       CdmContainerManager* pManager = pContainer->GetContainerManager();

       if (CHKPTR(pManager))
       {
          pManager->ReloadContainerComplete(pContainer);
          pResult = GetResultContainer(p_pData,
                                       1,
                                       "Refresh executed!",
                                       eWmscomMessageServerityInfo);

          pResult->AddValue("ObjectList", pContainer->GetVariant());
       }
    }
    else
    {
       pResult = GetResultContainer(p_pData,
                                    -5000,
                                    "Objectlist not found!",
                                    eWmscomMessageServerityError);
    }
}

/** +-=---------------------------------------------------------Mi 18. Apr 10:53:39 2012----------*
 * @method  CwiObjectContainer::Count                          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_ObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:53:39 2012----------*/
void CwiObjectContainer::Count(CwmscomData* p_pData,qint64 p_lDbId,qint64 p_ObjectListId)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObjectContainer* pContainer = GetEmptyObjectList(p_lDbId, p_ObjectListId);

   if (pContainer)
   {
      int iCount = pContainer->CountObjectsOnDb();
      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Count executed!",
                                   eWmscomMessageServerityInfo);
      pResult->AddValue("Count", iCount);
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 10:54:08 2012----------*
 * @method  CwiObjectContainer::GetEmptyList                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_ObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:54:08 2012----------*/
void CwiObjectContainer::GetEmptyList(CwmscomData* p_pData,qint64 p_lDbId,qint64 p_ObjectListId)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObjectContainer* pContainer = GetEmptyObjectList(p_lDbId, p_ObjectListId);

   if (pContainer)
   {
      pResult = GetResultContainer(p_pData,
                                    1,
                                    "Objectlist found!",
                                    eWmscomMessageServerityInfo);

      pResult->AddValue("ObjectList", pContainer->GetVariant());
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 10:54:23 2012----------*
 * @method  CwiObjectContainer::GetCompleteList                // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param  qint64 p_ObjectListId                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:54:23 2012----------*/
void CwiObjectContainer::GetCompleteList(CwmscomData* p_pData,qint64 p_lDbId,qint64 p_ObjectListId)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObjectContainer* pContainer = GetCompleteObjectList(p_lDbId, p_ObjectListId);

   if (pContainer)
   {
      pResult = GetResultContainer(p_pData,
                                    1,
                                    "Objectlist found!",
                                    eWmscomMessageServerityInfo);
      pResult->AddValue("ObjectList", pContainer->GetVariant());
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                    -5000,
                                    "Objectlist not found!",
                                    eWmscomMessageServerityError);
   }

}

/** +-=---------------------------------------------------------Mi 18. Apr 13:43:04 2012----------*
 * @method  CwiObjectContainer::GetEmptyList                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 13:43:04 2012----------*/
void CwiObjectContainer::GetEmptyList(CwmscomData* p_pData,qint64 p_lDbId, QString p_qstrKeyname)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObjectContainer* pContainer = GetEmptyObjectList(p_lDbId, p_qstrKeyname);

   if (pContainer)
   {
      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Objectlist found!",
                                   eWmscomMessageServerityInfo);

      pResult->AddValue("ObjectList", pContainer->GetVariant());
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 13:42:48 2012----------*
 * @method  CwiObjectContainer::GetCompleteList                // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param  qint64 p_lDbId                                     //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 13:42:48 2012----------*/
void CwiObjectContainer::GetCompleteList(CwmscomData* p_pData,qint64 p_lDbId, QString p_qstrKeyname)
{
   CwmscomDataResult* pResult = nullptr;
   CdmObjectContainer* pContainer = GetCompleteObjectList(p_lDbId, p_qstrKeyname);

   if (pContainer)
   {
      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Objectlist found!",
                                   eWmscomMessageServerityInfo);
      pResult->AddValue("ObjectList", pContainer->GetVariant());
   }
   else
   {
      pResult = GetResultContainer(p_pData,
                                   -5000,
                                   "Objectlist not found!",
                                   eWmscomMessageServerityError);
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 15:29:10 2012----------*
 * @method  CwiObjectContainer::GetNewId                       // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 15:29:10 2012----------*/
void CwiObjectContainer::GetNewId(CwmscomData* p_pData)
{
    CwiCommandObjectListGetNewId command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Mi 18. Apr 19:08:42 2012----------*
 * @method  CwiObjectContainer::Exist                          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 19:08:42 2012----------*/
void CwiObjectContainer::Exist(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
        CwiCommandObjectListExist command(p_pData);
        command.Execute();
   }
}

/** +-=---------------------------------------------------------Do 19. Apr 10:44:11 2012----------*
 * @method  CwiObjectContainer::Query                          // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Apr 10:44:11 2012----------*/
void CwiObjectContainer::Query(CwmscomData* p_pData)
{
    CwiCommandObjectListQuery command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 14. Mrz 14:15:45 2013----------*
 * @method  CwiObjectContainer::CreateObject                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 14. Mrz 14:15:45 2013----------*/
void CwiObjectContainer::CreateObject(CwmscomData* p_pData)
{
    CwiCommandCreateObject command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Mi 8. Mai 16:15:22 2013-----------*
 * @method  CwiObjectContainer::DeleteObject                   // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 8. Mai 16:15:22 2013-----------*/
void CwiObjectContainer::DeleteObject(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
        CwiCommandDeleteObject command(p_pData);
        command.Execute();
   }
}

void CwiObjectContainer::GetContainerList(CwmscomData* p_pData,qint64 p_lDbId)
{
    CwiCommandGetContainerList command(p_pData, p_lDbId);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 10. Okt 16:28:56 2013----------*
 * @method  CwiObjectContainer::GetVersion                     // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:28:56 2013----------*/
QString CwiObjectContainer::getVersion()
{
   return "0.1.0";
}

void CwiObjectContainer::saveEvent(CdmObjectContainer *pContainer)
{
    CdmSessionManager *pSessionManager = CdmSessionManager::GetSessionManager();
    CdmSession *pSession = pSessionManager->FindSession();
    if(pSession)
    {
        IdmEventStoreManager *pEventStoreManager = pSession->getEventStoreManager();
        QList<CdmObject*> qlObjects;
        pContainer->GetObjectList(qlObjects);
        if(!qlObjects.isEmpty())
        {
            CdmObject *pEventObject = qlObjects.first();
            CdmClass *pEventClass = pEventObject->GetClass();

            subcribeSubscribersForEventSourcing(pEventClass->GetClassManager(), pEventStoreManager);

            QVariant qvEventClass = pEventClass->GetVariant();
            QVariant qvEventObject = pEventObject->GetVariant();

            QVariantList qvlEventContentFormatted;
            qvlEventContentFormatted.append(pEventStoreManager->formatEventContent(qvEventClass, qvEventObject));
            QString qstrEvent = pEventStoreManager->getFormattedEventContentAsString(qvlEventContentFormatted);

            QObject* pEventDto = pEventStoreManager->createEventDtoObject(qvlEventContentFormatted);
            pEventStoreManager->startEvent(qstrEvent);
            pEventStoreManager->stopEvent(qstrEvent, pEventDto);
            pEventStoreManager->fireEvents(pEventDto);
        }
    }
}

void CwiObjectContainer::subcribeSubscribersForEventSourcing(CdmClassManager *pClassManager, IdmEventStoreManager *pEventStoreManager)
{
    QList<CdmClass*> qllClasses;
    pClassManager->GetClassList(qllClasses);
    QList<CdmClass*>::iterator qmIt = qllClasses.begin();
    QList<CdmClass*>::iterator qmItEnd = qllClasses.end();
    for(; qmIt != qmItEnd; ++qmIt)
    {
        CdmClass *pSubscriberClass = (*qmIt);
        if(pSubscriberClass->HasMethod("onDomainEvent"))
        {
            pEventStoreManager->subscribe(pSubscriberClass->GetMethod("onDomainEvent"));
        }
    }
}
