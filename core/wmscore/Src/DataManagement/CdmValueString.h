/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMSTRING_H
#define CDMSTRING_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueString : public CdmValue 
{
   Q_OBJECT

   protected:    

      /*
       * The string value.
       */
      QString m_qstrValue;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:14:12 2005*
    * @method  CdmValueString::CdmValueString                          // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The csontructor of the string value.                                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:14:12 2005----------*/
CdmValueString(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:48:56 2005*
    * @method  CdmValueString::~CdmValueString                         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueString                                                  *
    *----------------last changed: -----------------------------Sa 20. Aug 12:48:56 2005----------*/
virtual ~CdmValueString(  );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:14:47 2005*
    * @method  CdmValueString::SetDefaultValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 11:14:47 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:47:45 2012-------*
    * @method  CdmValueString::GetValue                      // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 20. Nov 11:47:45 2012----------*/
      virtual QString GetValue( ) const;
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:47:35 2012-------*
    * @method  CdmValueString::SetValue                      // public, virtual, slots            *
    * @return  void                                          //                                   *
    * @param   const QString& p_qstrValue                    //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Di 20. Nov 11:47:35 2012----------*/
      virtual void SetValue( const QString& p_qstrValue);
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:15:01 2005*
    * @method  CdmValueString::IsEqual                            // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:15:01 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:04:25 2010-------*
    * @method  CdmValueString::IsSmaller                     // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Mi 15. Sep 14:04:25 2010----------*/
    int IsSmaller(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:04:41 2010-------*
    * @method  CdmValueString::IsSmallerEqual                // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Mi 15. Sep 14:04:41 2010----------*/
    int IsSmallerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:04:55 2010-------*
    * @method  CdmValueString::IsLarger                      // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:04:55 2010----------*/
    int IsLarger(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:05:08 2010-------*
    * @method  CdmValueString::IsLargerEqual                 // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Mi 15. Sep 14:05:08 2010----------*/
    int IsLargerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:32:19 2010-------*
    * @method  CdmValueString::IsNotEqual                    // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Mi 15. Sep 14:32:19 2010----------*/
    int IsNotEqual(QVariant* p_pqVariant) const;




   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:28:54 2013-------*
    * @method  CdmValueString::XmlExport                     // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:28:54 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:15:26 2005*
    * @method  CdmValueString::XmlImport                          // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 11:15:26 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:15:22 2005*
    * @method  CdmValueString::XmlImportString                    // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:15:22 2005----------*/
void XmlImportString(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:14:37 2005*
    * @method  CdmValueString::CdmValueString                          // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The cosntructor of the string value.                                               *
    *----------------last changed: -----------------------------Sa 20. Aug 11:14:37 2005----------*/
CdmValueString(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:29:03 2013-------*
    * @method  CdmValueString::GetDisplayString              // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 10:29:03 2013----------*/
      virtual QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:15:31 2005*
    * @method  CdmValueString::FromStringToValue                  // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Sa 20. Aug 11:15:31 2005----------*/
int FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:29:42 2006*
    * @method  CdmValueString::CheckUnique                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:29:42 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:48:39 2006-------*
    * @method  CdmValueString::SetValue                           // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:48:39 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:29:21 2013-------*
    * @method  CdmValueString::GetVariant                    // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 10:29:21 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 14:06:34 2012-------*
    * @method  CdmValueString::CdmValueString                // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 14:06:34 2012----------*/
    CdmValueString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:29:28 2013-------*
    * @method  CdmValueString::GetValueVariant               // public, const, virtual, slots     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:29:28 2013----------*/
      virtual QVariant GetValueVariant( ) const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:40:39 2012--------*
    * @method  CdmValueString::SetValueVariant               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:40:39 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:29:13 2013-------*
    * @method  CdmValueString::GetValueAsString              // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:29:13 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:41:54 2012--------*
    * @method  CdmValueString::Deploy                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:41:54 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------Fr 8. Feb 15:59:43 2013--------*
    * @method  CdmValueString::HasValue                      // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment This method returns if this Values has an value.                                   *
    *----------------last changed: -----------------------------Fr 8. Feb 15:59:43 2013-----------*/
      virtual bool HasValue( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:15:45 2013-------*
    * @method  CdmValueString::SetVariant                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:15:45 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMSTRING_H
