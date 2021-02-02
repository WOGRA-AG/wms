/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMLONG_H
#define CDMLONG_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"



/*
 * This class implements the long value
 * of the framework
 */
class WMSMANAGER_API CdmValueLong : public CdmValue 
{
   Q_OBJECT

   private:    
      /*
       * The long value
       */
      long m_lValue;


   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:52:07 2005*
    * @method  CdmValueLong::CdmValueLong                              // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // Value Keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Obejct                     *
    * @comment The constructor of long value.                                                     *
    *----------------last changed: -----------------------------Fr 19. Aug 23:52:07 2005----------*/
CdmValueLong(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:46:47 2005*
    * @method  CdmValueLong::~CdmValueLong                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueLong                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:46:47 2005----------*/
virtual ~CdmValueLong(  );
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:54:03 2005*
    * @method  CdmValueLong::SetDefaultValue                      // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Fr 19. Aug 23:54:03 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
   protected:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:53:33 2005*
    * @method  CdmValueLong::CdmValueLong                              // protected                         *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value Keyname                     *
    * @param   EdmValue p_eDmValue                           // Value Type                        *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The constructor of value long for derrived classes like counter                    *
    *----------------last changed: -----------------------------Fr 19. Aug 23:53:33 2005----------*/
CdmValueLong(  long p_lDatabaseId,
         long p_lId,
         QString p_qstrKeyname,
         EdmValueType p_eDmValue,
         CdmObject* p_pCdmObject );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:54:03 2012-------*
    * @method  CdmValueLong::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   long p_lValue                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:54:03 2012----------*/
void SetValue( long p_lValue);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:54:30 2012-------*
    * @method  CdmValueLong::GetValue                        // public, const, slots              *
    * @return  long                                          //                                   *
    * @comment returns the long value.                                                            *
    *----------------last changed: -----------------------------Di 20. Nov 09:54:30 2012----------*/
long GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:46 2005*
    * @method  CdmValueLong::IsEqual                              // public, const, virtual            *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:46 2005----------*/
virtual int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:41 2005*
    * @method  CdmValueLong::IsSmaller                            // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:41 2005----------*/
virtual int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:37 2005*
    * @method  CdmValueLong::IsSmallerEqual                       // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:37 2005----------*/
virtual int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:32 2005*
    * @method  CdmValueLong::IsLarger                             // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:32 2005----------*/
virtual int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:29 2005*
    * @method  CdmValueLong::IsLargerEqual                        // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:29 2005----------*/
virtual int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:45:25 2005*
    * @method  CdmValueLong::IsNotEqual                           // public, const, virtual            *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 10:45:25 2005----------*/
virtual int IsNotEqual(  QVariant* p_pqVariant ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:18:48 2013-------*
    * @method  CdmValueLong::XmlExport                       // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:18:48 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:54:47 2005*
    * @method  CdmValueLong::XmlImport                            // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Fr 19. Aug 23:54:47 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   protected:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:06:13 2010-------*
    * @method  CdmValueLong::XmlImportLong                   // protected                         *
    * @return  void                                          //                                   *
    * @param   QDomElement&# p_rqDomElement                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 15. Sep 14:06:13 2010----------*/
    void XmlImportLong(QDomElement& p_rqDomElement);

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:53:55 2005*
    * @method  CdmValueLong::CdmValueLong                              // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Source                        *
    * @param   CdmObject* p_pCdmObject                       // parent Obejct.                    *
    * @comment The XML Constructor for value long                                                 *
    *----------------last changed: -----------------------------Fr 19. Aug 23:53:55 2005----------*/
CdmValueLong(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:19:00 2013-------*
    * @method  CdmValueLong::GetDisplayString                // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:19:00 2013----------*/
    virtual QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:54:54 2005*
    * @method  CdmValueLong::FromStringToValue                    // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Fr 19. Aug 23:54:54 2005----------*/
int FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:28:31 2006*
    * @method  CdmValueLong::CheckUnique                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:28:31 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:47:05 2006-------*
    * @method  CdmValueLong::SetValue                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:47:05 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:19:09 2013-------*
    * @method  CdmValueLong::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:19:09 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 13:36:22 2012-------*
    * @method  CdmValueLong::CdmValueLong                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 13:36:22 2012----------*/
    CdmValueLong( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:19:27 2013-------*
    * @method  CdmValueLong::GetValueVariant                 // public, const, virtual, slots     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:19:27 2013----------*/
      virtual QVariant GetValueVariant( ) const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:35:02 2012--------*
    * @method  CdmValueLong::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:35:02 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:19:18 2013-------*
    * @method  CdmValueLong::GetValueAsString                // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:19:18 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:39:51 2012--------*
    * @method  CdmValueLong::Deploy                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:39:51 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:10:28 2013-------*
    * @method  CdmValueLong::SetVariant                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:10:28 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMLONG_H
