/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDATE_H
#define CDMDATE_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


// forwards

/*
 * This class implements a date value
 */
class WMSMANAGER_API CdmValueDate : public CdmValue 
{
   Q_OBJECT
private:    
    /*
     * The Date value
     */
    QDate m_qdValue;

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:48:13 2005*
    * @method  CdmValueDate::CdmValueDate                              // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value Keyname                     *
    * @param   CdmObject* p_pCdmObject                       // parent object                     *
    * @comment The cosntructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:48:13 2005----------*/
CdmValueDate(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:43:54 2005*
    * @method  CdmValueDate::~CdmValueDate                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueDate                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:43:54 2005----------*/
virtual ~CdmValueDate(  );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:02 2005*
    * @method  CdmValueDate::SetDefaultValue                      // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:02 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:25:43 2012-------*
    * @method  CdmValueDate::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QDate& p_rqdDate                        //                                   *
    * @comment Sets the date value.                                                               *
    *----------------last changed: -----------------------------Di 20. Nov 09:25:43 2012----------*/
void SetValue( const QDate& p_rqdDate);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:25:53 2012-------*
    * @method  CdmValueDate::GetValue                        // public, const, slots              *
    * @return  QDate                                         //                                   *
    * @comment returns the value date                                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:25:53 2012----------*/
QDate GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:43 2005*
    * @method  CdmValueDate::IsEqual                              // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:43 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:46 2005*
    * @method  CdmValueDate::IsSmaller                            // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:46 2005----------*/
int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:49 2005*
    * @method  CdmValueDate::IsSmallerEqual                       // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:49 2005----------*/
int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:53 2005*
    * @method  CdmValueDate::IsLarger                             // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:53 2005----------*/
int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:49:57 2005*
    * @method  CdmValueDate::IsLargerEqual                        // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Sa 13. Aug 21:49:57 2005----------*/
int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:50:00 2005*
    * @method  CdmValueDate::IsNotEqual                           // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Sa 13. Aug 21:50:00 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;


    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:25:37 2012-------*
    * @method  CdmValueDate::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const long p_lDate                            //                                   *
    * @comment Sets the date value.                                                               *
    *----------------last changed: -----------------------------Di 20. Nov 09:25:37 2012----------*/
void SetValue( const long p_lDate);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 12:34:46 2013--------*
    * @method  CdmValueDate::GetValue                        // public, const, slots              *
    * @return  void                                          //                                   *
    * @param   long& p_dValue                                //                                   *
    * @comment This emthod returns the date value in the overgiven double reference as time_t     *
    *----------------last changed: -----------------------------Sa 9. Feb 12:34:46 2013-----------*/
void GetValue( long& p_dValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:35:09 2013--------*
    * @method  CdmValueDate::XmlExport                       // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 12:35:09 2013-----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:50:11 2005*
    * @method  CdmValueDate::XmlImport                            // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 13. Aug 21:50:11 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:50:08 2005*
    * @method  CdmValueDate::XmlImportDate                        // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:50:08 2005----------*/
void XmlImportDate(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:48:54 2005*
    * @method  CdmValueDate::CdmValueDate                              // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElment                    // XML Element                       *
    * @param   CdmObject* p_pCdmObject                       // parent object                     *
    * @comment the cosntructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:48:54 2005----------*/
CdmValueDate(  QDomElement& p_rqDomElment, CdmObject* p_pCdmObject );

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 12:35:21 2013--------*
    * @method  CdmValueDate::GetDisplayString                // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 12:35:21 2013-----------*/
QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:27:20 2006*
    * @method  CdmValueDate::CheckUnique                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:27:20 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:44:50 2006-------*
    * @method  CdmValueDate::SetValue                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:44:50 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:35:48 2013--------*
    * @method  CdmValueDate::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 12:35:48 2013-----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:18:04 2012-------*
    * @method  CdmValueDate::CdmValueDate                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:18:04 2012----------*/
    CdmValueDate( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:44:54 2012--------*
    * @method  CdmValueDate::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:44:54 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:35:56 2013--------*
    * @method  CdmValueDate::GetValueVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 12:35:56 2013-----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:35:41 2013--------*
    * @method  CdmValueDate::GetValueAsString                // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 12:35:41 2013-----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:32:01 2012--------*
    * @method  CdmValueDate::Deploy                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:32:01 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:07:30 2013-------*
    * @method  CdmValueDate::SetVariant                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:07:30 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMDATE_H
