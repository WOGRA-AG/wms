/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueCounter.h"


/** +-=---------------------------------------------------------Sa 13. Aug 21:19:26 2005----------*
 * @method  CdmValueCounter::CdmValueCounter                           // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // parent object                     *
 * @comment The constructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:19:26 2005----------*/
CdmValueCounter::CdmValueCounter(  long p_lDatabaseId,
                        long p_lId,
                        QString p_qstrKeyname,
                        CdmObject* p_pCdmObject )
   : CdmValueLong( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueCounter, p_pCdmObject)
{
   // nothing to do
}


/** +-=---------------------------------------------------------Sa 13. Aug 21:20:13 2005----------*
 * @method  CdmValueCounter::CdmValueCounter                           // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Element                       *
 * @param   CdmObject* p_pCdmObject                          // Parent Obejct                     *
 * @comment The constructor                                                                       *
 *----------------last changed: --------------------------------Sa 13. Aug 21:20:13 2005----------*/
CdmValueCounter::CdmValueCounter(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject )
   : CdmValueLong(p_rqDomElement, p_pCdmObject)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:16:49 2012----------*
 * @method  CdmValueCounter::CdmValueCounter                 // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:16:49 2012----------*/
CdmValueCounter::CdmValueCounter(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueLong(p_rqvHash, p_pCdmObject)
{
   // nothing to do
}

/** +-=---------------------------------------------------------Sa 20. Aug 12:43:29 2005----------*
 * @method  CdmValueCounter::~CdmValueCounter                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueCounter                                                    *
 *----------------last changed: --------------------------------Sa 20. Aug 12:43:29 2005----------*/
CdmValueCounter::~CdmValueCounter(  )
{
   // nothing to do
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:06:55 2010----------*
 * @method  CdmValueCounter::SetDefaultValue                 // public                            *
 * @return  void                                             //                                   *
 * @param   const CdmMember* #p_pCdmMember                   //                                   *
 * @comment This method sets the default value.                                                   *
 *----------------last changed: --------------------------------Mi 15. Sep 14:06:55 2010----------*/
void CdmValueCounter::SetDefaultValue(const CdmMember* )
{
   // there are no default values for this Value must be ignored
}


/** +-=---------------------------------------------------------Mi 15. Sep 14:07:14 2010----------*
 * @method  CdmValueCounter::Add                             // public                            *
 * @return  void                                             //                                   *
 * @param   long #p_lAdd                                     //                                   *
 * @comment Adds p_dAdd to Value.                                                                 *
 *----------------last changed: --------------------------------Mi 15. Sep 14:07:14 2010----------*/
void CdmValueCounter::Add(long )
{
   ERR( "You can not add on a counter!" );
   EC(eDmUnallowedValueOperation);
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:07:49 2010----------*
 * @method  CdmValueCounter::Subtract                        // public                            *
 * @return  void                                             //                                   *
 * @param   long #p_lSubtract                                //                                   *
 * @comment subtracts p_dSubtract from value.                                                     *
 *----------------last changed: --------------------------------Mi 15. Sep 14:07:49 2010----------*/
void CdmValueCounter::Subtract(long )
{

   ERR( "You can not subtract on a counter!" );
   EC(eDmUnallowedValueOperation);
}

/** +-=---------------------------------------------------------Sa 7. Jan 14:27:01 2006-----------*
 * @method  CdmValueCounter::CheckUnique                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method checks if the value complies with the unique rule.                        *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jan 14:27:01 2006-----------*/
void CdmValueCounter::CheckUnique(  )
{
   // todo
}

/** +-=---------------------------------------------------------Mi 15. Sep 14:08:06 2010----------*
 * @method  CdmValueCounter::SetValue                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString #p_qstrValue                             //                                   *
 * @param   QString #p_qstrValue2                            // needed for object values          *
 *                                                           //  (objectlistid, objectid)         *
 * @comment This method sets the value for an datatype as string.                                 *
 *----------------last changed: --------------------------------Mi 15. Sep 14:08:06 2010----------*/
void CdmValueCounter::SetValue(QString , QString )
{
   ERR("Set Value is not supported by Counters");
}

/** +-=---------------------------------------------------------Mo 13. Mai 14:44:30 2013----------*
 * @method  CdmValueCounter::SetVariant                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 13. Mai 14:44:30 2013----------*/
void CdmValueCounter::SetVariant(QVariantMap& p_rqvHash)
{
   // Does nothing
   Q_UNUSED(p_rqvHash);
}
