/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomDataJson.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the Data container for json messages
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMDATAJSON_H
#define CBMSCOMDATAJSON_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes


// Own Includes
#include "CwmscomData.h"

// Forwards


// TypeDefs


/* 
 * This class implements the Data container for json messages
 */
class CwmscomDataJson : public CwmscomData
{


   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:03:02 2012--------*
    * @method  CwmscomDataJson::CwmscomDataJson              // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrSource                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:03:02 2012-----------*/
    CwmscomDataJson( QString p_qstrSource);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:03:08 2012--------*
    * @method  CwmscomDataJson::~CwmscomDataJson             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmscomDataJson                                            *
    *----------------last changed: -----------------------------So 1. Apr 11:03:08 2012-----------*/
    virtual ~CwmscomDataJson( );

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:25:02 2012--------*
    * @method  CwmscomDataJson::Parse                        // public, virtual                   *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrSource                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:25:02 2012-----------*/
    virtual bool Parse(QString p_qstrSource);
};

#endif CBMSCOMDATAJSON_H
