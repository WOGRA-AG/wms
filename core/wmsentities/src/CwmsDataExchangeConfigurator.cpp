/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsDataExchangeConfigurator.cpp
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

// WMS Includes
#include "CdmLogging.h"
#include "IwmsParser.h"
#include "IwmsSerializer.h"

// own Includes
#include "CwmsDataExchangeConfigurator.h"


/** +-=---------------------------------------------------------So 1. Apr 10:10:35 2012-----------*
 * @method  CwmsDataExchangeConfigurator::CwmsDataExchangeConfigurator                   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:10:35 2012-----------*/
CwmsDataExchangeConfigurator::CwmsDataExchangeConfigurator()
: m_pSerializer(nullptr),
  m_pParser(nullptr)
{

}

/** +-=---------------------------------------------------------So 1. Apr 10:10:30 2012-----------*
 * @method  CwmsDataExchangeConfigurator::~CwmsDataExchangeConfigurator                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsDataExchangeConfigurator                                                *
 *----------------last changed: --------------------------------So 1. Apr 10:10:30 2012-----------*/
CwmsDataExchangeConfigurator::~CwmsDataExchangeConfigurator()
{
   DELPTR(m_pSerializer);
   DELPTR(m_pParser);
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:12:27 2012-----------*
 * @method  CwmsDataExchangeConfigurator::SetParser                        // public                            *
 * @return  void                                             //                                   *
 * @param   IbmscomParser* p_pParser                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:12:27 2012-----------*/
void CwmsDataExchangeConfigurator::SetParser(IwmsParser* p_pParser)
{
   m_pParser = p_pParser;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:12:41 2012-----------*
 * @method  CwmsDataExchangeConfigurator::GetParser                        // public                            *
 * @return  IbmscomParser*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:12:41 2012-----------*/
IwmsParser* CwmsDataExchangeConfigurator::GetParser()
{
   return m_pParser;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:13:02 2012-----------*
 * @method  CwmsDataExchangeConfigurator::SetSerializer                    // public                            *
 * @return  void                                             //                                   *
 * @param   IbmscomSerializer* p_pSerializer                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:13:02 2012-----------*/
void CwmsDataExchangeConfigurator::SetSerializer(IwmsSerializer* p_pSerializer)
{
   m_pSerializer = p_pSerializer;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:13:19 2012-----------*
 * @method  CwmsDataExchangeConfigurator::GetSerializer                    // public                            *
 * @return  IbmscomSerializer*                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:13:19 2012-----------*/
IwmsSerializer* CwmsDataExchangeConfigurator::GetSerializer()
{
   return m_pSerializer;
}

