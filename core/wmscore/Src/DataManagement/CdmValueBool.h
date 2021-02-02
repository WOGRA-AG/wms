/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMBOOL_H
#define CDMBOOL_H

// System and QT Includes


// own Incldues
#include "CdmMember.h"
#include "CdmValue.h"

// forwards
class QString;

/**
 * This class implements the Bool value
 */
class WMSMANAGER_API CdmValueBool : public CdmValue 
{
   Q_OBJECT

   private:    
      /*
       * The Value
       */
       bool m_bValue;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:39:58 2005*
    * @method  CdmValueBool::~CdmValueBool                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueBool                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:39:58 2005----------*/
virtual ~CdmValueBool(  );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 20:59:24 2005*
    * @method  CdmValueBool::CdmValueBool                              // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // Value Keyname                     *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The Constructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 20:59:24 2005----------*/
CdmValueBool(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:58:02 2012-------*
    * @method  CdmValueBool::SetValue                        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   bool p_bValue                                 //                                   *
    * @comment This method sets the bool value.                                                   *
    *----------------last changed: -----------------------------Mo 19. Nov 15:58:02 2012----------*/
void SetValue( bool p_bValue);
    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:58:11 2012-------*
    * @method  CdmValueBool::GetValue                        // public, const, slots              *
    * @return  bool                                          //                                   *
    * @comment returns the bool value.                                                            *
    *----------------last changed: -----------------------------Mo 19. Nov 15:58:11 2012----------*/
bool GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:00:53 2005*
    * @method  CdmValueBool::SetDefaultValue                      // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:00:53 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:01:00 2005*
    * @method  CdmValueBool::IsEqual                              // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 13. Aug 21:01:00 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:21:00 2010-------*
    * @method  CdmValueBool::IsSmaller                       // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*#p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Mi 15. Sep 14:21:00 2010----------*/
    int IsSmaller(QVariant*p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:21:10 2010-------*
    * @method  CdmValueBool::IsSmallerEqual                  // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Mi 15. Sep 14:21:10 2010----------*/
    int IsSmallerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:21:22 2010-------*
    * @method  CdmValueBool::IsLarger                        // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*# p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:21:22 2010----------*/
    int IsLarger(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:21:33 2010-------*
    * @method  CdmValueBool::IsLargerEqual                   // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*# p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Mi 15. Sep 14:21:33 2010----------*/
    int IsLargerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:01:15 2005*
    * @method  CdmValueBool::IsNotEqual                           // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Sa 13. Aug 21:01:15 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;


   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:57:10 2013--------*
    * @method  CdmValueBool::XmlExport                       // public, const                     *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:57:10 2013-----------*/
    void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:01:25 2005*
    * @method  CdmValueBool::XmlImport                            // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 13. Aug 21:01:25 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:01:22 2005*
    * @method  CdmValueBool::XmlImportBool                        // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:01:22 2005----------*/
void XmlImportBool(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:00:13 2005*
    * @method  CdmValueBool::CdmValueBool                              // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Element                       *
    * @param   CdmObject* p_pCdmObject                       // Parent Object                     *
    * @comment The constructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:00:13 2005----------*/
CdmValueBool(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:57:20 2013--------*
    * @method  CdmValueBool::GetDisplayString                // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 11:57:20 2013-----------*/
QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:01:30 2005*
    * @method  CdmValueBool::FromStringToValue                    // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Sa 13. Aug 21:01:30 2005----------*/
void FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:26:09 2006*
    * @method  CdmValueBool::CheckUnique                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:26:09 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:42:23 2006-------*
    * @method  CdmValueBool::SetValue                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:42:23 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:57:34 2013--------*
    * @method  CdmValueBool::GetVariant                      // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 11:57:34 2013-----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:10:49 2012-------*
    * @method  CdmValueBool::CdmValueBool                    // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_qVariant                      //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:10:49 2012----------*/
    CdmValueBool( QVariantMap& p_qVariant, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:57:43 2013--------*
    * @method  CdmValueBool::GetValueVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:57:43 2013-----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:42:52 2012--------*
    * @method  CdmValueBool::SetValueVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:42:52 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:57:52 2013--------*
    * @method  CdmValueBool::GetValueAsString                // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:57:52 2013-----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:29:42 2012--------*
    * @method  CdmValueBool::Deploy                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:29:42 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 13:59:45 2013-------*
    * @method  CdmValueBool::SetVariant                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 13:59:45 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMBOOL_H
