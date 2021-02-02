/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDOUBLE_H
#define CDMDOUBLE_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements the double value
 */
class WMSMANAGER_API CdmValueDouble : public CdmValue 
{
   Q_OBJECT

   private:    
    
      /*
       * The double value
       */
      double m_dValue;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:44:20 2005*
    * @method  CdmValueDouble::CdmValueDouble                          // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:44:20 2005----------*/
CdmValueDouble(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:44:42 2005*
    * @method  CdmValueDouble::~CdmValueDouble                         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueDouble                                                  *
    *----------------last changed: -----------------------------Sa 20. Aug 12:44:42 2005----------*/
virtual ~CdmValueDouble(  );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:44:46 2005*
    * @method  CdmValueDouble::SetDefaultValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 12:44:46 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:39:36 2012-------*
    * @method  CdmValueDouble::SetValue                      // public, slots                     *
    * @return  void                                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment sets tghe value.                                                                   *
    *----------------last changed: -----------------------------Di 20. Nov 09:39:36 2012----------*/
void SetValue( double p_dValue);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:40:03 2012-------*
    * @method  CdmValueDouble::GetValue                      // public, const, slots              *
    * @return  double                                        //                                   *
    * @comment returns its value.                                                                 *
    *----------------last changed: -----------------------------Di 20. Nov 09:40:03 2012----------*/
double GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:01 2005*
    * @method  CdmValueDouble::IsEqual                            // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:01 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:04 2005*
    * @method  CdmValueDouble::IsSmaller                          // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:04 2005----------*/
int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:07 2005*
    * @method  CdmValueDouble::IsSmallerEqual                     // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:07 2005----------*/
int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:10 2005*
    * @method  CdmValueDouble::IsLarger                           // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:10 2005----------*/
int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:13 2005*
    * @method  CdmValueDouble::IsLargerEqual                      // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:13 2005----------*/
int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:16 2005*
    * @method  CdmValueDouble::IsNotEqual                         // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:16 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:05:47 2013-------*
    * @method  CdmValueDouble::XmlExport                     // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:05:47 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:26 2005*
    * @method  CdmValueDouble::XmlImport                          // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:26 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:23 2005*
    * @method  CdmValueDouble::XmlImportDouble                    // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:23 2005----------*/
void XmlImportDouble(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:44:37 2005*
    * @method  CdmValueDouble::CdmValueDouble                          // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:44:37 2005----------*/
CdmValueDouble(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:06:01 2013-------*
    * @method  CdmValueDouble::GetDisplayString              // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:06:01 2013----------*/
    virtual QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:31 2005*
    * @method  CdmValueDouble::FromStringToValue                  // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:31 2005----------*/
int FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:27:46 2006*
    * @method  CdmValueDouble::CheckUnique                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:27:46 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:46:06 2006-------*
    * @method  CdmValueDouble::SetValue                           // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:46:06 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:06:28 2013-------*
    * @method  CdmValueDouble::GetVariant                    // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:06:28 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:42:13 2012-------*
    * @method  CdmValueDouble::CdmValueDouble                // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:42:13 2012----------*/
    CdmValueDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:06:36 2013-------*
    * @method  CdmValueDouble::GetValueVariant               // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:06:36 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 17:17:17 2012--------*
    * @method  CdmValueDouble::SetValueVariant               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 17:17:17 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:06:44 2013-------*
    * @method  CdmValueDouble::GetValueAsString              // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:06:44 2013----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:36:11 2012--------*
    * @method  CdmValueDouble::Deploy                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:36:11 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:08:58 2013-------*
    * @method  CdmValueDouble::SetVariant                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:08:58 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMDOUBLE_H
