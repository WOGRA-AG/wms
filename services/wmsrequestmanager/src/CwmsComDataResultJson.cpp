/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CbmsComDataResultJson.cpp
 ** Started Implementation: 2012/04/08
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// own Includes
#include "CwmscomJson.h"
#include "CwmsComDataResultJson.h"


/** +-=---------------------------------------------------------So 8. Apr 11:24:08 2012-----------*
 * @method  CbmsComDataResultJson::CbmsComDataResultJson     // private                           *
 * @return                                                   //                                   *
 * @param   CwmscomData* p_pRequest                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 8. Apr 11:24:08 2012-----------*/
CwmsComDataResultJson::CwmsComDataResultJson(CwmscomData* p_pRequest)
: CwmscomDataResult(p_pRequest)
{
}

/** +-=---------------------------------------------------------So 8. Apr 11:24:28 2012-----------*
 * @method  CbmsComDataResultJson::~CbmsComDataResultJson    // private, virtual                  *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbmsComDataResultJson                                         *
 *----------------last changed: --------------------------------So 8. Apr 11:24:28 2012-----------*/
CwmsComDataResultJson::~CwmsComDataResultJson()
{
}

/** +-=---------------------------------------------------------So 8. Apr 11:29:18 2012-----------*
 * @method  CbmsComDataResultJson::ConvertToString           // protected, virtual                *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 8. Apr 11:29:18 2012-----------*/
QString CwmsComDataResultJson::ConvertToString()
{
   QString qstrResult;
   bool bSuccess = false;
   qstrResult = CwmscomJson::serialize(m_qmResult, bSuccess);
   return qstrResult;
}