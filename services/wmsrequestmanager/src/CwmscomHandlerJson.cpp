/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomHandlerJson.cpp
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


// own Includes
#include "CwmscomDataJson.h"
#include "CwmscomHandlerJson.h"


/** +-=---------------------------------------------------------So 1. Apr 11:13:13 2012-----------*
 * @method  CwmscomHandlerJson::CwmscomHandlerJson           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:13:13 2012-----------*/
CwmscomHandlerJson::CwmscomHandlerJson()
{
}

/** +-=---------------------------------------------------------Mo 2. Apr 16:46:57 2012-----------*
 * @method  CwmscomHandlerJson::~CwmscomHandlerJson          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmscomHandlerJson                                            *
 *----------------last changed: --------------------------------Mo 2. Apr 16:46:57 2012-----------*/
CwmscomHandlerJson::~CwmscomHandlerJson()
{
}

/** +-=---------------------------------------------------------So 1. Apr 11:19:13 2012-----------*
 * @method  CwmscomHandlerJson::CreateDataInstance           // public                            *
 * @return  CwmscomData*                                     // The result                        *
 * @param   QString p_qstrSource                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:19:13 2012-----------*/
CwmscomData* CwmscomHandlerJson::CreateDataInstance(QString p_qstrSource)
{
   return new CwmscomDataJson(p_qstrSource);
}
