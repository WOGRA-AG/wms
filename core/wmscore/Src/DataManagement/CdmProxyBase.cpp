/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmProxyBase.cpp
 ** Started Implementation: 2011/08/25
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QList>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"

// own Includes
#include "CdmProxyBase.h"

/** +-=---------------------------------------------------------Di 3. Apr 11:46:41 2012-----------*
 * @method  CdmProxyBase::CdmProxyBase                       // public                            *
 * @return                                                   //                                   *
 * @comment The baseclass constructor. it does nothing.                                           *
 *----------------last changed: --------------------------------Di 3. Apr 11:46:41 2012-----------*/
CdmProxyBase::CdmProxyBase()
: m_bValid(false),
  m_iTimeout(1500)
{
}

/** +-=---------------------------------------------------------Di 3. Apr 14:27:24 2012-----------*
 * @method  CdmProxyBase::~CdmProxyBase                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmProxyBase                                                  *
 *----------------last changed: --------------------------------Di 3. Apr 14:27:24 2012-----------*/
CdmProxyBase::~CdmProxyBase()
{
}

/** +-=---------------------------------------------------------Di 3. Apr 14:27:39 2012-----------*
 * @method  CdmProxyBase::IsValid                            // public                            *
 * @return  bool                                             //                                   *
 * @comment returns if the proxy is in an valid state or not.                                     *
 *----------------last changed: --------------------------------Di 3. Apr 14:27:39 2012-----------*/
bool CdmProxyBase::IsValid()
{
   return m_bValid;
}

/** +-=---------------------------------------------------------Di 3. Apr 11:47:22 2012-----------*
 * @method  CdmProxyBase::SetValid                           // protected                         *
 * @return  void                                             //                                   *
 * @comment Sets the proxy to a valid state.                                                      *
 *----------------last changed: --------------------------------Di 3. Apr 11:47:22 2012-----------*/
void CdmProxyBase::SetValid()
{
   m_bValid = true;
}

/** +-=---------------------------------------------------------Di 3. Apr 11:48:35 2012-----------*
 * @method  CdmProxyBase::SetValueChangeTimeout              // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iTimeout                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 11:48:35 2012-----------*/
void CdmProxyBase::SetValueChangeTimeout(int p_iTimeout)
{
   m_iTimeout = p_iTimeout;
}

/** +-=---------------------------------------------------------So 10. Feb 10:02:36 2013----------*
 * @method  CdmProxyBase::GetValueChangeTimeout              // public, const                     *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:02:36 2013----------*/
int CdmProxyBase::GetValueChangeTimeout() const
{
   return m_iTimeout;
}

/** +-=---------------------------------------------------------Do 5. Apr 14:06:17 2012-----------*
 * @method  CdmProxyBase::Check                              // protected, virtual                *
 * @return  bool                                             //                                   *
 * @param   CdmObject*# p_pCdmObject                         //                                   *
 * @comment This method checks the object if it is needed in the component. This method must      *
 *----------------last changed: --------------------------------Do 5. Apr 14:06:17 2012-----------*/
bool CdmProxyBase::Check(CdmObject*)
{
   return true;
}

/** +-=---------------------------------------------------------Di 25. Sep 16:04:31 2012----------*
 * @method  CdmProxyBase::GetQuery                           // public, p virtual                 *
 * @return  CdmQueryEnhanced*                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 25. Sep 16:04:31 2012----------*/

/** +-=---------------------------------------------------------Di 3. Apr 11:48:46 2012-----------*
 * @method  CdmProxyBase::CreateQuery                        // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment Creates the Query for execution.                                                      *
 *----------------last changed: --------------------------------Di 3. Apr 11:48:46 2012-----------*/


/** +-=---------------------------------------------------------Di 3. Apr 11:48:50 2012-----------*
 * @method  CdmProxyBase::ValueChanged                       // protected, p virtual              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 11:48:50 2012-----------*/
