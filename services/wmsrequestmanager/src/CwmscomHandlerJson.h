/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomHandlerJson.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the handler for json communication
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMHANDLERJSON_H
#define CBMSCOMHANDLERJSON_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes


// Own Includes
#include "CwmscomHandler.h"
#include "wmscom.h"

// Forwards
class CwmscomData;

// TypeDefs


/* 
 * This class implements the handler for json communication
 */
class WMSCOM_API CwmscomHandlerJson : public CwmscomHandler
{

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:13:13 2012--------*
    * @method  CwmscomHandlerJson::CwmscomHandlerJson        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:13:13 2012-----------*/
    CwmscomHandlerJson( );

   public:
   /** +-=---------------------------------------------------------Mo 2. Apr 16:46:57 2012--------*
    * @method  CwmscomHandlerJson::~CwmscomHandlerJson       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmscomHandlerJson                                         *
    *----------------last changed: -----------------------------Mo 2. Apr 16:46:57 2012-----------*/
    virtual ~CwmscomHandlerJson( );

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:19:13 2012--------*
    * @method  CwmscomHandlerJson::CreateDataInstance        // public                            *
    * @return  CwmscomData*                                  // The result                        *
    * @param   QString p_qstrSource                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:19:13 2012-----------*/
    CwmscomData* CreateDataInstance(QString p_qstrSource);
};

#endif CBMSCOMHANDLERJSON_H
