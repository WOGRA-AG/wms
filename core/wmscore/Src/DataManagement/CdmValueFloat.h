/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMFLOAT_H
#define CDMFLOAT_H


// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"


/*
 * This class implements the float value
 */
class WMSMANAGER_API CdmValueFloat : public CdmValue 
{
   Q_OBJECT

   private:    
      /*
       * The float value
       */
      float m_fValue;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:31:21 2005*
    * @method  CdmValueFloat::CdmValueFloat                            // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // Value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The constructor of Cdmfloat                                                        *
    *----------------last changed: -----------------------------Fr 19. Aug 23:31:21 2005----------*/
CdmValueFloat(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:45:51 2005*
    * @method  CdmValueFloat::~CdmValueFloat                           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueFloat                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:45:51 2005----------*/
virtual ~CdmValueFloat(  );
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:32:34 2005*
    * @method  CdmValueFloat::SetDefaultValue                     // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Fr 19. Aug 23:32:34 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:47:57 2012-------*
    * @method  CdmValueFloat::SetValue                       // public, slots                     *
    * @return  void                                          //                                   *
    * @param   float p_fValue                                //                                   *
    * @comment this method sets the value.                                                        *
    *----------------last changed: -----------------------------Di 20. Nov 09:47:57 2012----------*/
void SetValue( float p_fValue);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:48:12 2012-------*
    * @method  CdmValueFloat::GetValue                       // public, const, slots              *
    * @return  float                                         //                                   *
    * @comment This method returns the value.                                                     *
    *----------------last changed: -----------------------------Di 20. Nov 09:48:12 2012----------*/
float GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:32:54 2005*
    * @method  CdmValueFloat::IsEqual                             // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Fr 19. Aug 23:32:54 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:32:57 2005*
    * @method  CdmValueFloat::IsSmaller                           // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Fr 19. Aug 23:32:57 2005----------*/
int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:00 2005*
    * @method  CdmValueFloat::IsSmallerEqual                      // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:00 2005----------*/
int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:04 2005*
    * @method  CdmValueFloat::IsLarger                            // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:04 2005----------*/
int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:08 2005*
    * @method  CdmValueFloat::IsLargerEqual                       // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:08 2005----------*/
int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:11 2005*
    * @method  CdmValueFloat::IsNotEqual                          // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:11 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;
   
   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:10:37 2013-------*
    * @method  CdmValueFloat::XmlExport                      // public, const                     *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:10:37 2013----------*/
    void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:21 2005*
    * @method  CdmValueFloat::XmlImport                           // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:21 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:18 2005*
    * @method  CdmValueFloat::XmlImportFloat                      // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:18 2005----------*/
void XmlImportFloat(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:32:25 2005*
    * @method  CdmValueFloat::CdmValueFloat                            // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // xml source                        *
    * @param   CdmObject* p_pCdmObject                       // the parent Obejct                 *
    * @comment he xml import constructor.                                                         *
    *----------------last changed: -----------------------------Fr 19. Aug 23:32:25 2005----------*/
CdmValueFloat(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:10:47 2013-------*
    * @method  CdmValueFloat::GetDisplayString               // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:10:47 2013----------*/
    QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:33:34 2005*
    * @method  CdmValueFloat::FromStringToValue                   // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Fr 19. Aug 23:33:34 2005----------*/
int FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:28:02 2006*
    * @method  CdmValueFloat::CheckUnique                         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:28:02 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:46:22 2006-------*
    * @method  CdmValueFloat::SetValue                            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:46:22 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:11:03 2013-------*
    * @method  CdmValueFloat::GetVariant                     // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:11:03 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:49:28 2012-------*
    * @method  CdmValueFloat::CdmValueFloat                  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqHash                        //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:49:28 2012----------*/
    CdmValueFloat( QVariantMap& p_rqHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 17:17:49 2012--------*
    * @method  CdmValueFloat::SetValueVariant                // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 17:17:49 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:11:18 2013-------*
    * @method  CdmValueFloat::GetValueVariant                // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:11:18 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:11:11 2013-------*
    * @method  CdmValueFloat::GetValueAsString               // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:11:11 2013----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:37:46 2012--------*
    * @method  CdmValueFloat::Deploy                         // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:37:46 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:09:34 2013-------*
    * @method  CdmValueFloat::SetVariant                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:09:34 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMFLOAT_H
