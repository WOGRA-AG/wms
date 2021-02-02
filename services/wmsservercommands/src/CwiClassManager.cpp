/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiClassManager.cpp
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
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiCommandExecuteFunction.h"
#include "CwiCommandUpdateClass.h"
#include "CwiCommandDeleteClass.h"
#include "CwiCommandGetNewClassID.h"
#include "CwiCommandGetClass.h"
#include "CwiClassManager.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiClassManager::CwiClassManager                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiClassManager::CwiClassManager(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "ClassManager", false, false)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiClassManager::~CwiClassManager                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiClassManager                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiClassManager::~CwiClassManager()
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012-----------*
 * @method  CwiClassManager::ExecuteGet                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:18:13 2012-----------*/
void CwiClassManager::ExecuteGet(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      QString qstrMode = p_pData->GetValue("Mode").toString();

      if (qstrMode == "NewClassId")
      {
         GetNewClassId(p_pData);
      }
      else
      {
         GetClass(p_pData);
      }
   }
}

/** +-=---------------------------------------------------------Mo 23. Apr 15:39:53 2012----------*
 * @method  CwiClassManager::ExecutePut                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Apr 15:39:53 2012----------*/
void CwiClassManager::ExecutePut(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {

       QString qstrMode = p_pData->GetValue("Mode").toString();

       if (qstrMode == "ExecuteFunction")
       {
          ExecuteFunction(p_pData);
       }
       else
       {
           UpdateClass(p_pData);
       }
   }
}

/** +-=---------------------------------------------------------Mo 23. Apr 15:40:08 2012----------*
 * @method  CwiClassManager::ExecuteDelete                // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Apr 15:40:08 2012----------*/
void CwiClassManager::ExecuteDelete(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
      DeleteClass(p_pData);
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiClassManager::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiClassManager::executeDescription(CwmscomData* p_pData)
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
 * @method  CwiClassManager::GetResourceDescription               // public, virtual                   *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:19:08 2012-----------*/
QString CwiClassManager::GetResourceDescription()
{
   return "Resource for class management load, create, update and delete classes.";
}


void CwiClassManager::GetClass(CwmscomData* p_pData)
{
    CwiCommandGetClass command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Mo 30. Apr 11:07:23 2012----------*
 * @method  CwiClassManager::GetNewClassId                // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 30. Apr 11:07:23 2012----------*/
void CwiClassManager::GetNewClassId(CwmscomData* p_pData)
{
   if (CHKPTR(p_pData))
   {
       CwiCommandGetNewClassID command(p_pData);
       command.Execute();
   }
}

void CwiClassManager::DeleteClass(CwmscomData* p_pData)
{
    if (CHKPTR(p_pData))
    {
        CwiCommandDeleteClass command(p_pData);
        command.Execute();
    }
}

void CwiClassManager::UpdateClass(CwmscomData* p_pData)
{
    CwiCommandUpdateClass command(p_pData);
    command.Execute();
}


void CwiClassManager::ExecuteFunction(CwmscomData* p_pData)
{
    CwiCommandExecuteFunction command(p_pData);
    command.Execute();
}

/** +-=---------------------------------------------------------Do 10. Okt 16:26:42 2013----------*
 * @method  CwiClassManager::GetVersion                   // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:26:42 2013----------*/
QString CwiClassManager::getVersion()
{
   return "0.1.0";
}
