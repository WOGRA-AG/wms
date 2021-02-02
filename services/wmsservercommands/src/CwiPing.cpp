/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CbiWebPing.cpp
 ** Started Implementation: 2012/04/08
 ** Description:
 **
 ** Implements the ping interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QDateTime>

// BMSCOM Includes
#include "CwmscomData.h"
#include "CwmscomDataResult.h"

// own Includes
#include "CwiPing.h"


/** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012-----------*
 * @method  CbiWebPing::CbiWebPing                           // public                            *
 * @return                                                   //                                   *
 * @param   CwmscomControllerBase* p_pController             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:09 2012-----------*/
CwiPing::CwiPing(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "Ping", false, false)
{
}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012-----------*
 * @method  CbiWebPing::~CbiWebPing                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbiWebPing                                                    *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:15 2012-----------*/
CwiPing::~CwiPing()
{
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:32:51 2012----------*
 * @method  CbiWebPing::ExecuteGet                           // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:32:51 2012----------*/
void CwiPing::ExecuteGet(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      pResult->AddValue("Timestamp", QDateTime::currentDateTime().toString());
   }
}

/** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012-----------*
 * @method  CbiWebPing::ExecuteDescription                   // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomData* p_pData                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 10:17:53 2012-----------*/
void CwiPing::executeDescription(CwmscomData* p_pData)
{
   if (p_pData)
   {
      CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);
      pResult->SetMessage("Returning Interface Description for Ping");
      pResult->SetMessageCode(1);
      pResult->SetSeverity(eWmscomMessageServerityInfo);
      AddCallParameters(pResult);
      pResult->AddValue("Timestamp", "String - Result");
   }
}

/** +-=---------------------------------------------------------Fr 13. Apr 17:49:49 2012----------*
 * @method  CbiWebPing::GetResourceDescription               // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 17:49:49 2012----------*/
QString CwiPing::GetResourceDescription()
{
   return "This method returns the timestamp of the ping request.";
}

/** +-=---------------------------------------------------------Do 10. Okt 16:26:13 2013----------*
 * @method  CbiWebPing::GetVersion                           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Okt 16:26:13 2013----------*/
QString CwiPing::getVersion()
{
   return "0.1.0";
}
