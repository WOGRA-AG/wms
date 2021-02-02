/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMTIME_H
#define CDMTIME_H


// System and QT Includes
#include <qdatetime.h>

// own includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements the value time
 */
class WMSMANAGER_API CdmValueTime : public CdmValue 
{
   Q_OBJECT

   private:    
      /*
       * The Value Time
       */
      QTime m_qtValue;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:03:44 2005*
    * @method  CdmValueTime::CdmValueTime                              // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:03:44 2005----------*/
CdmValueTime(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:49:06 2005*
    * @method  CdmValueTime::~CdmValueTime                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueTime                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:49:06 2005----------*/
virtual ~CdmValueTime(  );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:03:59 2005*
    * @method  CdmValueTime::SetDefaultValue                      // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 11:03:59 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:50:00 2012-------*
    * @method  CdmValueTime::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QTime& p_rqtTime                        //                                   *
    * @comment sets the value of this Value.                                                      *
    *----------------last changed: -----------------------------Di 20. Nov 11:50:00 2012----------*/
void SetValue( const QTime& p_rqtTime);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:50:20 2012-------*
    * @method  CdmValueTime::GetValue                        // public, const, slots              *
    * @return  QTime                                         //                                   *
    * @comment returns the value of this Value.                                                   *
    *----------------last changed: -----------------------------Di 20. Nov 11:50:20 2012----------*/
QTime GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:14 2005*
    * @method  CdmValueTime::IsEqual                              // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:14 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:17 2005*
    * @method  CdmValueTime::IsSmaller                            // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:17 2005----------*/
int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:20 2005*
    * @method  CdmValueTime::IsSmallerEqual                       // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:20 2005----------*/
int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:24 2005*
    * @method  CdmValueTime::IsLarger                             // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:24 2005----------*/
int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:28 2005*
    * @method  CdmValueTime::IsLargerEqual                        // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:28 2005----------*/
int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:31 2005*
    * @method  CdmValueTime::IsNotEqual                           // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:31 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;


    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:50:12 2012-------*
    * @method  CdmValueTime::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   double p_dTime                                //                                   *
    * @comment This method sets the time value as double.                                         *
    *----------------last changed: -----------------------------Di 20. Nov 11:50:12 2012----------*/
void SetValue( double p_dTime);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:11 2005*
    * @method  CdmValueTime::GetValue                             // public, const                     *
    * @return  void                                          //                                   *
    * @param   double& p_dTime                               //                                   *
    * @comment This method sets the time value as double.                                         *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:11 2005----------*/
void GetValue(  double& p_dTime ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:32:58 2013-------*
    * @method  CdmValueTime::XmlExport                       // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:32:58 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:39 2005*
    * @method  CdmValueTime::XmlImport                            // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:39 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:04:37 2005*
    * @method  CdmValueTime::XmlImportTime                        // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:04:37 2005----------*/
void XmlImportTime(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:03:52 2005*
    * @method  CdmValueTime::CdmValueTime                              // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:03:52 2005----------*/
CdmValueTime(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:33:08 2013-------*
    * @method  CdmValueTime::GetDisplayString                // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 11:33:08 2013----------*/
    virtual QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:29:55 2006*
    * @method  CdmValueTime::CheckUnique                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:29:55 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:50:45 2006-------*
    * @method  CdmValueTime::SetValue                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:50:45 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:33:15 2013-------*
    * @method  CdmValueTime::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 11:33:15 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 14:10:20 2012-------*
    * @method  CdmValueTime::CdmValueTime                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 14:10:20 2012----------*/
    CdmValueTime( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 11:33:24 2013-------*
    * @method  CdmValueTime::GetValueVariant                 // public, const, virtual, slots     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:33:24 2013----------*/
      virtual QVariant GetValueVariant( ) const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:41:26 2012--------*
    * @method  CdmValueTime::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:41:26 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:32:52 2013-------*
    * @method  CdmValueTime::GetValueAsString                // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:32:52 2013----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:43:05 2012--------*
    * @method  CdmValueTime::Deploy                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:43:05 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:16:13 2013-------*
    * @method  CdmValueTime::SetVariant                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:16:13 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMTIME_H
