/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwiLogout.cpp
 ** Started Implementation: 2012/04/11
 ** Description:
 **
 ** Implements a interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QThread>

// WMS Includes
#include "CdmSessionManager.h"

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiLogout.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CwiLogout::CwiLogout                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiLogout::CwiLogout(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Logout", false, false)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CwiLogout::~CwiLogout                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwiLogout                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiLogout::~CwiLogout()
{
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:35:42 2012----------*
 * @method  CwiLogout::ExecuteGet                         // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:35:42 2012----------*/
void CwiLogout::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
      int iSession = p_pData->GetSession();

      CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();

      if (pFactory)
      {
         CdmSessionManager::Logout();
         CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
         pResult->SetMessage("Logout succeeded. Session " + QString::number(iSession) + " deleted!");
         pResult->SetMessageCode(1);
         pResult->SetSeverity(eWmscomMessageServerityInfo);
      }
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CwiLogout::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiLogout::executeDescription(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      // ToDo Result Parameters
   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:25:13 2012----------*
 * @method  CwiLogout::GetResourceDescription             // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:25:13 2012----------*/
QString CwiLogout::GetResourceDescription()
{

   return "ToDo Description for function!!! Beat the developer if you receive this!";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:28:07 2013----------*
 * @method  CwiLogout::GetVersion                         // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:28:07 2013----------*/
QString CwiLogout::getVersion()
{
   return "0.1.0";
}
