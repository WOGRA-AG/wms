/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsDataExchangeConfigurator.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the handler for incoming requests
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSDATAEXCHANGECONFIGURATOR_H
#define CWMSDATAEXCHANGECONFIGURATOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMap>
#include <QString>

// Own Includes
#include "basetools.h"

// Forwards
class IwmsParser;
class IwmsSerializer;

// TypeDefs


/* 
 * This class implements the handler for incoming requests
 */
class BASETOOLS_API CwmsDataExchangeConfigurator
{
   protected:
      IwmsSerializer* m_pSerializer;
      IwmsParser* m_pParser;

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:10:35 2012--------*
    * @method  CwmsDataExchangeConfigurator::CwmsDataExchangeConfigurator                // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:10:35 2012-----------*/
    CwmsDataExchangeConfigurator( );

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:10:30 2012--------*
    * @method  CwmsDataExchangeConfigurator::~CwmsDataExchangeConfigurator               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsDataExchangeConfigurator                                             *
    *----------------last changed: -----------------------------So 1. Apr 10:10:30 2012-----------*/
    virtual ~CwmsDataExchangeConfigurator( );

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:12:27 2012--------*
    * @method  CwmsDataExchangeConfigurator::SetParser                     // public                            *
    * @return  void                                          //                                   *
    * @param   IbmscomParser* p_pParser                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:12:27 2012-----------*/
    void SetParser(IwmsParser* p_pParser);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:12:41 2012--------*
    * @method  CwmsDataExchangeConfigurator::GetParser                     // public                            *
    * @return  IbmscomParser*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:12:41 2012-----------*/
    IwmsParser* GetParser();

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:13:02 2012--------*
    * @method  CwmsDataExchangeConfigurator::SetSerializer                 // public                            *
    * @return  void                                          //                                   *
    * @param   IbmscomSerializer* p_pSerializer              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:13:02 2012-----------*/
    void SetSerializer(IwmsSerializer* p_pSerializer);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:13:19 2012--------*
    * @method  CwmsDataExchangeConfigurator::GetSerializer                 // public                            *
    * @return  IbmscomSerializer*                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:13:19 2012-----------*/
    IwmsSerializer* GetSerializer();
};

#endif // CBMSCOMHANDLER_H
