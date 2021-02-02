/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomDataJson.cpp
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
#include <QVariantMap>

// own Includes
#include "CwmscomJson.h"
#include "CwmscomDataJson.h"


/** +-=---------------------------------------------------------So 1. Apr 11:03:02 2012-----------*
 * @method  CwmscomDataJson::CwmscomDataJson                 // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrSource                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:03:02 2012-----------*/
CwmscomDataJson::CwmscomDataJson(QString p_qstrSource)
: CwmscomData(p_qstrSource)
{

}

/** +-=---------------------------------------------------------So 1. Apr 11:03:08 2012-----------*
 * @method  CwmscomDataJson::~CwmscomDataJson                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmscomDataJson                                               *
 *----------------last changed: --------------------------------So 1. Apr 11:03:08 2012-----------*/
CwmscomDataJson::~CwmscomDataJson()
{

}


/** +-=---------------------------------------------------------So 1. Apr 11:25:02 2012-----------*
 * @method  CwmscomDataJson::Parse                           // public, virtual                   *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrSource                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:25:02 2012-----------*/
bool CwmscomDataJson::Parse(QString p_qstrSource)
{
   bool bRet = false;

   //json is a QString containing the JSON data
   m_qmMembers = CwmscomJson::parse(p_qstrSource, bRet).toMap();

   if(!bRet) 
   {
      // ToDo Error handling
   }

   return bRet;
}