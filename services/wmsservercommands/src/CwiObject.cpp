/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiObject.cpp
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
#include "CdmValueBinaryDocument.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmJournalItem.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsReportManager.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiCommandGetObjectChanges.h"
#include "CwiCommandGetContainerChanges.h"
#include "CwiCommandExecuteWQL.h"
#include "CwiCommandPrintContainer.h"
#include "CwiCommandPrintObject.h"
#include "CwiCommandIsObjectUsed.h"
#include "CwiCommandCounterValue.h"
#include "CwiCommandUpdateBinaryDocument.h"
#include "CwiCommandReadBinaryDocument.h"
#include "CwiCommandUnlockObject.h"
#include "CwiCommandLockObject.h"
#include "CwiCommandGetNewObjectId.h"
#include "CwiCommandRefreshObject.h"
#include "CwiObject.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiObject::CwiObject                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiObject::CwiObject(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Object", true, true)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiObject::~CwiObject                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiObject                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiObject::~CwiObject()
{
}

/** +-=---------------------------------------------------------So 15. Apr 14:30:02 2012----------*
 * @method  CwiObject::ExecuteGet                         // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:30:02 2012----------*/
void CwiObject::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      QString qstrMode;

      if (p_pData->HasValue("Mode"))
      {
         qstrMode = p_pData->GetValue("Mode").toString();
      }

      if (qstrMode == "Refresh")
      {
         Refresh(p_pData);
      }
      else if (qstrMode == "NewId")
      {
         GetNewId(p_pData);
      }
      else if (qstrMode == "Lock")
      {
         Lock(p_pData);
      }
      else if (qstrMode == "Unlock")
      {
         Unlock(p_pData);
      }
      else if (qstrMode == "BinaryDocument")
      {
         ReadBinaryDocument(p_pData);
      }
      else if (qstrMode == "CounterValue")
      {
         CounterValue(p_pData);
      }
      else if (qstrMode == "IsObjectUsed")
      {
         IsObjectUsed(p_pData);
      }
      else if (qstrMode == "WQL")
      {
         ExecuteWQL(p_pData);
      }
      else if (qstrMode == "PrintObject")
      {
         PrintObject(p_pData);
      }
      else if (qstrMode == "PrintContainer")
      {
         PrintContainer(p_pData);
      }
      else if (qstrMode == "ObjectListChanges")
      {
         GetContainerChanges(p_pData);
      }
      else if (qstrMode == "ObjectChanges")
      {
         GetObjectChanges(p_pData);
      }
      else
      {
         GetObject(p_pData);
      }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 14:18:03 2012----------*
 * @method  CwiObject::ExecutePut                         // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:18:03 2012----------*/
void CwiObject::ExecutePut(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
   if (CHKPTR(p_pData))
   {
      if (p_pData->HasValue("Mode"))
      {
         QString qstrMode = p_pData->GetValue("Mode").toString();

         if (qstrMode == "BinaryDocument")
         {
            UpdateBinaryDocument(p_pData);
         }
      }
      else
      {
         QVariantMap qvObject = p_pData->GetValue("Object").toMap();

         int iDbId = qvObject["DatabaseId"].toInt();
         int iObjectId = qvObject["Id"].toInt();
         int iObjectListId = qvObject["ObjectListId"].toInt();

         //md test
         //CwiCommandGetObject commandGetObject = nullptr;

         CdmObject* pCdmObject =  GetObject(iDbId, iObjectListId, iObjectId);

         if (pCdmObject)
         {
            QVariantMap qvValues = qvObject["Values"].toMap();
            pCdmObject->SetValues(qvValues);
            pCdmObject->Commit();

            pResult = GetResultContainer(p_pData,
                                         1,
                                         "Update executed!",
                                         eWmscomMessageServerityInfo);
            pResult->AddValue("Object", pCdmObject->GetVariant());
         }
         else
         {
            pResult = GetResultContainer(p_pData,
                                         -5000,
                                         "Object not found!",
                                         eWmscomMessageServerityInfo);
         }
      }
   }
}

/** +-=---------------------------------------------------------So 15. Apr 14:17:55 2012----------*
 * @method  CwiObject::ExecuteDelete                      // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 15. Apr 14:17:55 2012----------*/
void CwiObject::ExecuteDelete(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      // ToDo
      Q_UNUSED(pResult);
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiObject::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiObject::executeDescription(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      CwmscomDataResult* pResult = nullptr;
      pResult = GetResultContainer(p_pData,
                                   1,
                                   "Returning Interface Description for Ping",
                                   eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      // ToDo Result Parameters
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012-----------*
 * @method  CwiObject::GetResourceDescription               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:19:08 2012-----------*/
QString CwiObject::GetResourceDescription()
{
   return "This resource manages objects.";
}

/** +-=---------------------------------------------------------Mi 18. Apr 15:42:48 2012----------*
 * @method  CwiObject::Refresh                            // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 15:42:48 2012----------*/
void CwiObject::Refresh(CwmscomData* p_pData)
{
    CwiCommandRefreshObject command(p_pData);
    command.Execute();

}

/** +-=---------------------------------------------------------Mi 18. Apr 15:43:11 2012----------*
 * @method  CwiObject::GetObject                          // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 15:43:11 2012----------*/
void CwiObject::GetObject(CwmscomData* p_pData)
{
   CwmscomDataResult* pResult = nullptr;
  qint64 lObjectId     =  p_pData->GetValue("ObjectId").toInt();
  qint64 lObjectListId =  p_pData->GetValue("ObjectListId").toInt();

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         CdmObject* pCdmObject = GetObject(pCdmDatabase->GetId(), lObjectListId, lObjectId);

         if (pCdmObject)
         {
            pResult = GetResultContainer(p_pData,
                                          1,
                                          "Object found!",
                                          eWmscomMessageServerityInfo);
            pResult->AddValue("Object", pCdmObject->GetVariant());
         }
         else
         {
            pResult = GetResultContainer(p_pData,
                                          -5000,
                                          "Object not found!",
                                          eWmscomMessageServerityError);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 10:01:28 2012----------*
 * @method  CwiObject::GetObject                          // public                            *
 * @return  CdmObject*                                       //                                   *
 * @param  qint64 p_lDatabaseId                               //                                   *
 * @param  qint64 p_lObjectListId                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:01:28 2012----------*/
CdmObject* CwiObject::GetObject(qint64 p_lDatabaseId,qint64 p_lObjectListId,qint64 p_lObjectId)
{
   CdmObject* pCdmObject = nullptr;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pOLManager = pCdmManager->GetContainerManager(p_lDatabaseId);

      if (CHKPTR(pOLManager))
      {
         CdmObjectContainer* pContainer = pOLManager->FindEmptyContainerById(p_lObjectListId);

         if (CHKPTR(pContainer))
         {
            pCdmObject = pContainer->FindObjectById(p_lObjectId);

            if (CHKPTR(pCdmObject))
            {
                pCdmObject->Refresh();
            }
         }
      }
   }

   return pCdmObject;
}

/** +-=---------------------------------------------------------Mi 18. Apr 15:42:18 2012----------*
 * @method  CwiObject::GetNewId                           // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 15:42:18 2012----------*/
void CwiObject::GetNewId(CwmscomData* p_pData)
{
    CwiCommandGetNewObjectId command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Mi 18. Apr 18:29:02 2012----------*
 * @method  CwiObject::Lock                               // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 18:29:02 2012----------*/
void CwiObject::Lock(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
       CwiCommandLockObject command(p_pData);
       command.Execute();
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 18:29:18 2012----------*
 * @method  CwiObject::Unlock                             // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 18:29:18 2012----------*/
void CwiObject::Unlock(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
       CwiCommandUnlockObject command(p_pData);
       command.Execute();
   }
}

/** +-=---------------------------------------------------------Do 19. Apr 11:29:32 2012----------*
 * @method  CwiObject::ReadBinaryDocument                 // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Apr 11:29:32 2012----------*/
void CwiObject::ReadBinaryDocument(CwmscomData* p_pData)
{
    CwiCommandReadBinaryDocument command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 19. Apr 11:29:47 2012----------*
 * @method  CwiObject::UpdateBinaryDocument               // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Apr 11:29:47 2012----------*/
void CwiObject::UpdateBinaryDocument(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
       CwiCommandUpdateBinaryDocument command(p_pData);
       command.Execute();
   }
}

/** +-=---------------------------------------------------------Do 19. Apr 11:27:41 2012----------*
 * @method  CwiObject::CounterValue                       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Apr 11:27:41 2012----------*/
void CwiObject::CounterValue(CwmscomData* p_pData)
{
    CwiCommandCounterValue command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 19. Apr 15:10:49 2012----------*
 * @method  CwiObject::IsObjectUsed                       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 19. Apr 15:10:49 2012----------*/
void CwiObject::IsObjectUsed(CwmscomData* p_pData)
{
    CwiCommandIsObjectUsed command(p_pData);
    command.Execute();
}



void CwiObject::PrintObject(CwmscomData* p_pData)
{
    CwiCommandPrintObject command(p_pData);
    command.Execute();
}

void CwiObject::PrintContainer(CwmscomData* p_pData)
{
    CwiCommandPrintContainer command(p_pData);
    command.Execute();
}


/** +-=---------------------------------------------------------Di 5. Feb 13:47:33 2013-----------*
 * @method  CwiObject::ExecuteWQL                         // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Feb 13:47:33 2013-----------*/
void CwiObject::ExecuteWQL(CwmscomData* p_pData)
{
    CwiCommandExecuteWQL command(p_pData);
    command.Execute();
}

void CwiObject::GetContainerChanges(CwmscomData* p_pData)
{
    CwiCommandGetContainerChanges command(p_pData);
    command.Execute();
}

void CwiObject::GetObjectChanges(CwmscomData* p_pData)
{
    CwiCommandGetObjectChanges command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 10. Okt 16:28:26 2013----------*
 * @method  CwiObject::GetVersion                         // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:28:26 2013----------*/
QString CwiObject::getVersion()
{
   return "0.1.0";
}
