/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMCHARACTERDOCUMENT_H
#define CDMCHARACTERDOCUMENT_H


// System and QT Includes
#include <qstring.h>

// own Includes
#include "CdmValue.h"

// forwards


/*
 * This class implements the character document value
 * this is a document which consists of characters like
 * xml documents
 */
class WMSMANAGER_API CdmValueCharacterDocument : public CdmValue
{
   Q_OBJECT

   protected:
   /*
    * The Document Value
    */
   mutable QString m_qstrDocument;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:40:28 2005*
    * @method  CdmValueCharacterDocument::CdmValueCharacterDocument    // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:40:28 2005----------*/
CdmValueCharacterDocument(  long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:40:53 2005*
    * @method  CdmValueCharacterDocument::~CdmValueCharacterDocument   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmDateTime                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 12:40:53 2005----------*/
virtual ~CdmValueCharacterDocument(  );
   public:
   /** +-=---------------------------------------------------------Mo 19. Nov 16:48:09 2012-------*
    * @method  CdmValueCharacterDocument::SetValue           // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDocument                        //                                   *
    * @comment This method sets the document value.                                               *
    *----------------last changed: -----------------------------Mo 19. Nov 16:48:09 2012----------*/
    virtual void SetValue(QString p_qstrDocument);
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:58:34 2013--------*
    * @method  CdmValueCharacterDocument::GetValue           // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment This method returns the doumentvalue                                               *
    *----------------last changed: -----------------------------Sa 9. Feb 11:58:34 2013-----------*/
    virtual QString GetValue() const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:19:24 2010-------*
    * @method  CdmValueCharacterDocument::SetDefaultValue    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   const CdmMember* #p_pCdmMember                //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:19:24 2010----------*/
    virtual void SetDefaultValue(const CdmMember* p_pCdmMember);
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:41:54 2005*
    * @method  CdmValueCharacterDocument::IsEqual                 // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has the same value as this parameter.   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:41:54 2005----------*/
int IsEqual(  QVariant* p_pqVariant ) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:19:45 2010-------*
    * @method  CdmValueCharacterDocument::IsSmaller          // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Mi 15. Sep 14:19:45 2010----------*/
    int IsSmaller(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:19:54 2010-------*
    * @method  CdmValueCharacterDocument::IsSmallerEqual     // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Mi 15. Sep 14:19:54 2010----------*/
    int IsSmallerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:20:03 2010-------*
    * @method  CdmValueCharacterDocument::IsLarger           // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:20:03 2010----------*/
    int IsLarger(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:20:11 2010-------*
    * @method  CdmValueCharacterDocument::IsLargerEqual      // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*# p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Mi 15. Sep 14:20:11 2010----------*/
    int IsLargerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:39:23 2010-------*
    * @method  CdmValueCharacterDocument::IsNotEqual         // public, const                     *
    * @return  int                                           // -1 = invalid 0 = false 1 = true   *
    * @param   QVariant* p_pqVariant                         //                                   *
    * @comment This emthod returns if the overgiven Value has not the same value as this          *
    *          parameter.                                                                         *
    *----------------last changed: -----------------------------Mi 15. Sep 14:39:23 2010----------*/
    int IsNotEqual(QVariant* p_pqVariant) const;




   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:58:53 2013--------*
    * @method  CdmValueCharacterDocument::XmlExport          // public, const                     *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:58:53 2013-----------*/
    void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:42:53 2005*
    * @method  CdmValueCharacterDocument::XmlImport               // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:42:53 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:42:50 2005*
    * @method  CdmValueCharacterDocument::XmlImportCharacterDocument // private                        *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:42:50 2005----------*/
void XmlImportCharacterDocument(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:40:46 2005*
    * @method  CdmValueCharacterDocument::CdmValueCharacterDocument    // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:40:46 2005----------*/
CdmValueCharacterDocument(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:59:03 2013--------*
    * @method  CdmValueCharacterDocument::GetDisplayString   // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 11:59:03 2013-----------*/
    QString GetDisplayString() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:42:59 2005*
    * @method  CdmValueCharacterDocument::FromStringToValue       // public                            *
    * @return  int                                           // Succcessflag                      *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method tries to convert a string to a Value.                                  *
    *----------------last changed: -----------------------------Sa 20. Aug 12:42:59 2005----------*/
int FromStringToValue(  QString p_qstrValue );

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:26:35 2006*
    * @method  CdmValueCharacterDocument::CheckUnique             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:26:35 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:43:37 2006-------*
    * @method  CdmValueCharacterDocument::SetValue                // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:43:37 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:40:46 2007-------*
    * @method  CdmValueCharacterDocument::CdmValueCharacterDocument    // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   EdmValue p_edmValue                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 15:40:46 2007----------*/
    CdmValueCharacterDocument( long p_lDatabaseId,
                          long p_lId,
                          QString p_qstrKeyname,
                          EdmValueType p_edmValue,
                          CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:59:17 2013--------*
    * @method  CdmValueCharacterDocument::GetVariant         // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------Sa 9. Feb 11:59:17 2013-----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:12:36 2012-------*
    * @method  CdmValueCharacterDocument::CdmValueCharacterDocument // public                     *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqHash                        //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:12:36 2012----------*/
    CdmValueCharacterDocument( QVariantMap& p_rqHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:43:44 2012--------*
    * @method  CdmValueCharacterDocument::SetValueVariant    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:43:44 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:59:44 2013--------*
    * @method  CdmValueCharacterDocument::GetValueVariant    // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:59:44 2013-----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:59:36 2013--------*
    * @method  CdmValueCharacterDocument::GetValueAsString   // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:59:36 2013-----------*/
    virtual QString GetValueAsString() const;

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:31:08 2012--------*
    * @method  CdmValueCharacterDocument::Deploy             // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:31:08 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:06:20 2013-------*
    * @method  CdmValueCharacterDocument::SetVariant         // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:06:20 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
};

#endif //
