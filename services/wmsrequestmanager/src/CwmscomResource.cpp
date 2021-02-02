/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomResourceBase.cpp
 ** Started Implementation: 2012/04/01
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QThread>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CumUser.h"

// own Includes

#include "CwmscomController.h"
#include "CwmscomData.h"
#include "CwmsComDataResultJson.h"
#include "CwmscomResource.h"



/** +-=---------------------------------------------------------Fr 13. Apr 17:52:32 2012----------*
 * @method  CwmscomResourceBase::CwmscomResourceBase         // protected                         *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   bool p_bPutPossible                              //                                   *
 * @param   bool p_bDeletePossible                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:52:32 2012----------*/
CwmscomResourceBase::CwmscomResourceBase(CwmscomController* p_pController,
                                         QString p_qstrName,
                                         bool p_bPutPossible,
                                         bool p_bDeletePossible)
: m_qstrName(p_qstrName),
  m_pController(p_pController),
  m_bPutPossible(p_bPutPossible),
  m_bDeletePossible(p_bDeletePossible)
{
   if (m_pController)
   {
      m_pController->AddResource(m_qstrName, this);
   }
}

/** +-=---------------------------------------------------------Mo 2. Apr 16:27:20 2012-----------*
 * @method  CwmscomResourceBase::~CwmscomResourceBase        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmscomResourceBase                                           *
 *----------------last changed: --------------------------------Mo 2. Apr 16:27:20 2012-----------*/
CwmscomResourceBase::~CwmscomResourceBase()
{

}

/** +-=---------------------------------------------------------So 1. Apr 11:36:31 2012-----------*
 * @method  CwmscomResourceBase::GetName                     // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:36:31 2012-----------*/
QString CwmscomResourceBase::getName()
{
   return m_qstrName;
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:08:54 2012-----------*
 * @method  CwmscomResourceBase::AddCallParameters           // protected                         *
 * @return  void                                             //                                   *
 * @param   CwmscomDataResult* p_pResult                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:08:54 2012-----------*/
void CwmscomResourceBase::AddCallParameters(CwmscomDataResult* p_pResult)
{
   if (p_pResult)
   {
      p_pResult->AddValue("Description", GetResourceDescription());
      p_pResult->AddValue("Controller", m_pController->GetName());
      p_pResult->AddValue("Resource", m_qstrName);
      p_pResult->AddValue("DescriptionMode", "Boolean - Parameter (optional)");
      p_pResult->AddValue("MessageCode", "Int - Result ( > 0 success < 0 Error)");
      p_pResult->AddValue("Message", "String - Result (The result message)");
      p_pResult->AddValue("MessageSeverity", "Int - Result (Info, Warning, Error, Fatal)");
      p_pResult->AddValue("PutPossible", m_bPutPossible);
      p_pResult->AddValue("DeletePossible", m_bDeletePossible);
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:12:59 2012-----------*
 * @method  CwmscomResourceBase::Execute                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:12:59 2012-----------*/
void CwmscomResourceBase::execute(CwmscomData* p_pData)
{
   if (p_pData)
   {
      if (p_pData->HasValue("DescriptionMode"))
      {
         if (p_pData->GetValue("DescriptionMode").toBool() == true)
         {
            executeDescription(p_pData);
         }
         else
         {
            ExecuteP(p_pData);
         }
      }
      else
      {
         ExecuteP(p_pData);            
      }
   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:31:45 2012----------*
 * @method  CwmscomResourceBase::ExecuteP                    // private                           *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:31:45 2012----------*/
void CwmscomResourceBase::ExecuteP(CwmscomData* p_pData)
{
   QString qstrCommand = p_pData->GetValue("Command").toString();
   int iSession = 0;

   if (p_pData->HasValue("SessionId"))
   {
      iSession = p_pData->GetValue("SessionId").toInt();

      CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

      if (pFactory)
      {
         pFactory->SetSessionThread(iSession);
      }
   }

   if (qstrCommand.toUpper() == QString("Get").toUpper())
   {
      ExecuteGet(p_pData);
   }
   else if (qstrCommand.toUpper() == QString("put").toUpper())
   {
      ExecutePut(p_pData);
   }
   else if (qstrCommand.toUpper() == QString("post").toUpper())
   {
      ExecutePut(p_pData); // PUT and Post is the same for WMS.
   }
   else if (qstrCommand.toUpper() == QString("delete").toUpper())
   {
      ExecuteDelete(p_pData);
   }
   else
   {
      ExecuteGet(p_pData);
   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:48:20 2012----------*
 * @method  CwmscomResourceBase::ExecutePut                  // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:48:20 2012----------*/
void CwmscomResourceBase::ExecutePut(CwmscomData* p_pData)
{
   if (!m_bPutPossible)
   {
      ExecuteGet(p_pData);
   }
   else
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Put not implemented!!!");
      pResult->SetMessageCode(-1);
      pResult->SetSeverity(eWmscomMessageServerityFatal);
   }
   
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:48:40 2012----------*
 * @method  CwmscomResourceBase::ExecuteDelete               // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:48:40 2012----------*/
void CwmscomResourceBase::ExecuteDelete(CwmscomData* p_pData)
{
   if (!m_bDeletePossible)
   {
      ExecuteGet(p_pData);
   }
   else
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Delete not implemented!!!");
      pResult->SetMessageCode(-1);
      pResult->SetSeverity(eWmscomMessageServerityFatal);
   }
}

/** +-=---------------------------------------------------------Mi 18. Apr 10:08:06 2012----------*
 * @method  CwmscomResourceBase::GetResultContainer          // protected                         *
 * @return  CwmscomDataResult*                               //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @param   int p_iReturnCode                                //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   EbmscomMessageServerity p_eSeverity              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Apr 10:08:06 2012----------*/
CwmscomDataResult* CwmscomResourceBase::GetResultContainer(CwmscomData* p_pData,
                                                           int p_iReturnCode,
                                                           QString p_qstrMessage,
                                                           EwmscomMessageServerity p_eSeverity)
{

   CwmscomDataResult* pResult = nullptr;

   if (p_pData)
   {
      pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage(p_qstrMessage);
      pResult->SetMessageCode(p_iReturnCode);
      pResult->SetSeverity(p_eSeverity);
   }

   return pResult;
}

/** +-=---------------------------------------------------------Mo 4. Jun 11:58:01 2012-----------*
 * @method  CwmscomResourceBase::GetManager                  // protected                         *
 * @return  CdmManager*                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 11:58:01 2012-----------*/
CdmDataProvider* CwmscomResourceBase::GetManager()
{
   return CdmSessionManager::GetDataProvider();
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:40:38 2013----------*
 * @method  CwmscomResourceBase::GetCurrentUser              // protected                         *
 * @return  const CumUser*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:40:38 2013----------*/
const CumUser* CwmscomResourceBase::GetCurrentUser()
{
   const CumUser* pCumUser = nullptr;
   CdmDataProvider* pCdmManager = GetManager();

   if (pCdmManager)
   {  
      pCumUser = pCdmManager->GetUser();
   }

   return pCumUser;
}

/** +-=---------------------------------------------------------Mo 4. Jun 12:05:02 2012-----------*
 * @method  CwmscomResourceBase::GetCurrentUserId            // protected                         *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 12:05:02 2012-----------*/
int CwmscomResourceBase::GetCurrentUserId()
{
   int iUserId = 0;
   CdmDataProvider* pCdmManager = GetManager();

   if (pCdmManager)
   {  
      iUserId = pCdmManager->GetUserId();
   }

   return iUserId;
}

/** +-=---------------------------------------------------------Mo 4. Jun 12:04:53 2012-----------*
 * @method  CwmscomResourceBase::GetObjectListByKeyname      // protected                         *
 * @return  CdmObjectContainer*                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 12:04:53 2012-----------*/
CdmObjectContainer* CwmscomResourceBase::GetObjectListByKeyname(QString p_qstrKeyname)
{

   CdmObjectContainer* pContainer = nullptr;
   CdmContainerManager* pContainerManager = GetObjectListManager();

   if (pContainerManager)
   {  
      pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrKeyname);
   }

   return pContainer;
}


/** +-=---------------------------------------------------------Mo 4. Jun 12:02:46 2012-----------*
 * @method  CwmscomResourceBase::GetObjectListManager        // protected                         *
 * @return  CdmContainerManager*                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Jun 12:02:46 2012-----------*/
CdmContainerManager* CwmscomResourceBase::GetObjectListManager()
{
   CdmContainerManager* pContainerManager = nullptr;
   CdmDataProvider* pCdmManager = GetManager();

   if (pCdmManager)
   {
      pContainerManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentScheme());
   }

   return pContainerManager;
}

/** +-=---------------------------------------------------------Do 10. Okt 21:06:36 2013----------*
 * @method  CwmscomResourceBase::GetConfiguration            // public                            *
 * @return  QVariantMap                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 21:06:36 2013----------*/
QVariantMap CwmscomResourceBase::getConfiguration()
{
   QVariantMap qmConfig;

   // ToDo

   return qmConfig;
}

CwmscomController* CwmscomResourceBase::GetController()
{
    return m_pController;
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:36:48 2012----------*
 * @method  CwmscomResourceBase::ExecuteGet                  // protected, p virtual              *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:36:48 2012----------*/


/** +-=---------------------------------------------------------Mo 9. Apr 10:17:23 2012-----------*
 * @method  CwmscomResourceBase::ExecuteDescription          // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:23 2012-----------*/

/** +-=---------------------------------------------------------Mo 9. Apr 10:16:52 2012-----------*
 * @method  CwmscomResourceBase::GetResourceDescription      // public, p virtual                 *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:16:52 2012-----------*/
