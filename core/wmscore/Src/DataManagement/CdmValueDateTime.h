/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDATETIME_H
#define CDMDATETIME_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValue.h"

// forwards

/*
 *This method implements the datetime value (timestamp)
 */
class WMSMANAGER_API CdmValueDateTime : public CdmValue 
{
   Q_OBJECT

private:    
    /*
     * The datetime value (timestamp)
     */
    QDateTime m_qdtValue;
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:51:59 2005*
    * @method  CdmValueDateTime::CdmValueDateTime                      // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            // Database Id                       *
    * @param   long p_lId                                    // Value Id                          *
    * @param   QString p_qstrKeyname                         // value keyname                     *
    * @param   CdmObject* p_pCdmObject                       // parent objectp                    *
    * @comment The cosntructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:51:59 2005----------*/
CdmValueDateTime(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:44:01 2005*
    * @method  CdmValueDateTime::~CdmValueDateTime                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueDateTime                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 12:44:01 2005----------*/
virtual ~CdmValueDateTime(  );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:52:35 2005*
    * @method  CdmValueDateTime::SetDefaultValue                  // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:52:35 2005----------*/
void SetDefaultValue(  const CdmMember* p_pCdmMember );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:27:58 2012-------*
    * @method  CdmValueDateTime::SetValue                    // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const QDateTime& p_rqdtDateTime               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:27:58 2012----------*/
void SetValue( const QDateTime& p_rqdtDateTime);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:28:15 2012-------*
    * @method  CdmValueDateTime::GetValue                    // public, const, slots              *
    * @return  QDateTime                                     //                                   *
    * @comment returns its Value.                                                                 *
    *----------------last changed: -----------------------------Di 20. Nov 09:28:15 2012----------*/
QDateTime GetValue( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:39 2005*
    * @method  CdmValueDateTime::IsEqual                          // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:39 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:43 2005*
    * @method  CdmValueDateTime::IsSmaller                        // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:43 2005----------*/
int IsSmaller(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:47 2005*
    * @method  CdmValueDateTime::IsSmallerEqual                   // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:47 2005----------*/
int IsSmallerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:50 2005*
    * @method  CdmValueDateTime::IsLarger                         // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:50 2005----------*/
int IsLarger(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:54 2005*
    * @method  CdmValueDateTime::IsLargerEqual                    // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:54 2005----------*/
int IsLargerEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:59 2005*
    * @method  CdmValueDateTime::IsNotEqual                       // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:59 2005----------*/
int IsNotEqual(  QVariant* p_pqVariant ) const;


   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:24:26 2005*
    * @method  CdmValueDateTime::SetValue                         // public                            *
    * @return  void                                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment This method sets the value as double.                                              *
    *----------------last changed: -----------------------------Fr 19. Aug 23:24:26 2005----------*/
void SetValue(  double p_dValue );

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:58:32 2013--------*
    * @method  CdmValueDateTime::GetValue                    // public, const                     *
    * @return  void                                          //                                   *
    * @param   double& p_dDateTime                           //                                   *
    * @comment This method returns the datetime value as double.                                  *
    *----------------last changed: -----------------------------Sa 9. Feb 12:58:32 2013-----------*/
    void GetValue(double& p_dDateTime) const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:58:59 2013--------*
    * @method  CdmValueDateTime::XmlExport                   // public, const                     *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment Exports a datetime datatype                                                        *
    *----------------last changed: -----------------------------Sa 9. Feb 12:58:59 2013-----------*/
    void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:25:39 2005*
    * @method  CdmValueDateTime::XmlImport                        // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Fr 19. Aug 23:25:39 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Fr 19. Aug 23:25:19 2005*
    * @method  CdmValueDateTime::XmlImportDateTime                // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment IMport a Datatype.                                                                 *
    *----------------last changed: -----------------------------Fr 19. Aug 23:25:19 2005----------*/
void XmlImportDateTime(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:52:53 2005*
    * @method  CdmValueDateTime::CdmValueDateTime                      // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   // XML Element                       *
    * @param   CdmObject* p_pCdmObject                       // parent Object                     *
    * @comment The cosntructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:52:53 2005----------*/
CdmValueDateTime(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:59:12 2013--------*
    * @method  CdmValueDateTime::GetDisplayString            // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 12:59:12 2013-----------*/
    QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:27:34 2006*
    * @method  CdmValueDateTime::CheckUnique                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:27:34 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:45:41 2006-------*
    * @method  CdmValueDateTime::SetValue                         // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:45:41 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:59:33 2013--------*
    * @method  CdmValueDateTime::GetVariant                  // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 12:59:33 2013-----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:23:30 2012-------*
    * @method  CdmValueDateTime::CdmValueDateTime            // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:23:30 2012----------*/
    CdmValueDateTime( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:59:53 2013--------*
    * @method  CdmValueDateTime::GetValueVariant             // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 12:59:53 2013-----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 17:15:47 2012--------*
    * @method  CdmValueDateTime::SetValueVariant             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 17:15:47 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:59:44 2013--------*
    * @method  CdmValueDateTime::GetValueAsString            // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 12:59:44 2013-----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:32:25 2012--------*
    * @method  CdmValueDateTime::Deploy                      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:32:25 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:07:59 2013-------*
    * @method  CdmValueDateTime::SetVariant                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:07:59 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};
#endif // //CDMDATETIME_H
