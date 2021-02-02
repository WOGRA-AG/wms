/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMCOUNTER_H
#define CDMCOUNTER_H


// System and QT Includes

// own Includes
#include "CdmValueLong.h"

// forwards


/*
 * This method implements the counter value.
 * The counter value is a value which will
 * automatically set by the database. dependent
 * from start value.
 */
class WMSMANAGER_API CdmValueCounter : public CdmValueLong 
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:19:26 2005*
    * @method  CdmValueCounter::CdmValueCounter                        // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // parent object                     *
    * @comment The constructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:19:26 2005----------*/
CdmValueCounter(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:43:29 2005*
    * @method  CdmValueCounter::~CdmValueCounter                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueCounter                                                 *
    *----------------last changed: -----------------------------Sa 20. Aug 12:43:29 2005----------*/
virtual ~CdmValueCounter(  );
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:06:55 2010-------*
    * @method  CdmValueCounter::SetDefaultValue              // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* #p_pCdmMember                //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:06:55 2010----------*/
    void SetDefaultValue(const CdmMember* p_pCdmMember);
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:07:14 2010-------*
    * @method  CdmValueCounter::Add                          // public                            *
    * @return  void                                          //                                   *
    * @param   long #p_lAdd                                  //                                   *
    * @comment Adds p_dAdd to Value.                                                              *
    *----------------last changed: -----------------------------Mi 15. Sep 14:07:14 2010----------*/
    void Add(long p_lAdd);
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:07:49 2010-------*
    * @method  CdmValueCounter::Subtract                     // public                            *
    * @return  void                                          //                                   *
    * @param   long #p_lSubtract                             //                                   *
    * @comment subtracts p_dSubtract from value.                                                  *
    *----------------last changed: -----------------------------Mi 15. Sep 14:07:49 2010----------*/
    void Subtract(long p_lSubtract);


   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:20:13 2005*
    * @method  CdmValueCounter::CdmValueCounter                        // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Element                       *
    * @param   CdmObject* p_pCdmObject                       // Parent Obejct                     *
    * @comment The constructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:20:13 2005----------*/
CdmValueCounter(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:27:01 2006*
    * @method  CdmValueCounter::CheckUnique                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:27:01 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:08:06 2010-------*
    * @method  CdmValueCounter::SetValue                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString #p_qstrValue                          //                                   *
    * @param   QString #p_qstrValue2                         // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: -----------------------------Mi 15. Sep 14:08:06 2010----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:16:49 2012-------*
    * @method  CdmValueCounter::CdmValueCounter              // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:16:49 2012----------*/
    CdmValueCounter( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:44:30 2013-------*
    * @method  CdmValueCounter::SetVariant                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:44:30 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMCOUNTER_H
