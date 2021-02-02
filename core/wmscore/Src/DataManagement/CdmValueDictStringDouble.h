/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTSTRINGDOUBLE_H
#define CDMDICTSTRINGDOUBLE_H

// Sytsem and QT Includes
#include <qmap.h>

// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueDictStringDouble : public CdmValueCharacterDocument
{
   Q_OBJECT
   
   private:
      /*
       * The list of strings
       */
      QMap<QString,double> m_qmMap;


   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:44:30 2007-------*
    * @method  CdmValueDictStringDouble::CdmValueDictStringDouble      // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:44:30 2007----------*/
    CdmValueDictStringDouble( long p_lDatabaseId,
                         long p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:44:34 2007-------*
    * @method  CdmValueDictStringDouble::~CdmValueDictStringDouble     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:44:34 2007----------*/
    virtual ~CdmValueDictStringDouble( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:32:04 2008-------*
    * @method  CdmValueDictStringDouble::SetValue            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:32:04 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:55:27 2013-------*
    * @method  CdmValueDictStringDouble::GetValue            // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:55:27 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:55:35 2013-------*
    * @method  CdmValueDictStringDouble::Serialize           // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:55:35 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:22:11 2007-------*
    * @method  CdmValueDictStringDouble::Deserialize              // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:22:11 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:33:34 2012-------*
    * @method  CdmValueDictStringDouble::SetValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   double p_dData                                //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:33:34 2012----------*/
void SetValue( QString p_qstrKey, double p_dData);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:33:44 2012-------*
    * @method  CdmValueDictStringDouble::RemoveValue         // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:33:44 2012----------*/
void RemoveValue( QString p_qstrKey);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:02:14 2013-------*
    * @method  CdmValueDictStringDouble::GetDict             // public, const, slots              *
    * @return  QMap<QString, double>                         //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:02:14 2013----------*/
QMap<QString, double> GetDict( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:21:19 2007-------*
    * @method  CdmValueDictStringDouble::CdmValueDictStringDouble      // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:21:19 2007----------*/
    CdmValueDictStringDouble( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:33:51 2012-------*
    * @method  CdmValueDictStringDouble::ClearDict           // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:33:51 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:33:22 2012-------*
    * @method  CdmValueDictStringDouble::CdmValueDictStringDouble // public                       *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:33:22 2012----------*/
    CdmValueDictStringDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:34:46 2012--------*
    * @method  CdmValueDictStringDouble::Deploy              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:34:46 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:02:32 2013-------*
    * @method  CdmValueDictStringDouble::GetValueAsString    // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:02:32 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:02:42 2013-------*
    * @method  CdmValueDictStringDouble::GetValueVariant     // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:02:42 2013----------*/
    QVariant GetValueVariant() const;

    static void DeserializeXmlToMap(QString &p_qstrDocument, QMap<QString, double> &p_qmMap);
public slots:
         /** +-=---------------------------------------------------------Di 28. Mai 14:51:43 2013-------*
    * @method  CdmValueDictStringDouble::SetValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<QString, double> p_qmValue               //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 28. Mai 14:51:43 2013----------*/
void SetValue( QMap<QString, double> p_qmValue);
public slots: 
virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
