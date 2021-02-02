/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbmsComDataResultJson.h
 ** Started Implementation: 2012/04/08
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMDATARESULTJSON_H
#define CBMSCOMDATARESULTJSON_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes


// Own Includes
#include "CwmscomDataResult.h"

// Forwards
class CwmscomData;

// TypeDefs


/* 
 * This class implements the Json Data Result;
 */
class CwmsComDataResultJson : public CwmscomDataResult
{

   private:
   /** +-=---------------------------------------------------------So 8. Apr 11:24:08 2012--------*
    * @method  CbmsComDataResultJson::CbmsComDataResultJson  // private                           *
    * @return                                                //                                   *
    * @param   CwmscomData* p_pRequest                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 8. Apr 11:24:08 2012-----------*/
    CwmsComDataResultJson( CwmscomData* p_pRequest);

   private:
   /** +-=---------------------------------------------------------So 8. Apr 11:24:28 2012--------*
    * @method  CbmsComDataResultJson::~CbmsComDataResultJson // private, virtual                  *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbmsComDataResultJson                                      *
    *----------------last changed: -----------------------------So 8. Apr 11:24:28 2012-----------*/
    virtual ~CwmsComDataResultJson( );

   protected:
   /** +-=---------------------------------------------------------So 8. Apr 11:29:18 2012--------*
    * @method  CbmsComDataResultJson::ConvertToString        // protected, virtual                *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 8. Apr 11:29:18 2012-----------*/
    virtual QString ConvertToString();
};

#endif
