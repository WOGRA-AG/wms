/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDOUBLELIST_H
#define CDMDOUBLELIST_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
//Added by qt3to4:
#include <QLinkedList>

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueListDouble : public CdmValueCharacterDocument 
{
   Q_OBJECT

   private:
      QLinkedList<double> m_qvlDoubles;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:43 2007-------*
    * @method  CdmValueListDouble::CdmValueListDouble                  // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:43 2007----------*/
    CdmValueListDouble( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:48 2007-------*
    * @method  CdmValueListDouble::~CdmValueListDouble                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:48 2007----------*/
    virtual ~CdmValueListDouble( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:45:40 2008-------*
    * @method  CdmValueListDouble::SetValue                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:45:40 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:53:30 2013-------*
    * @method  CdmValueListDouble::GetValue                  // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:53:30 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:53:34 2013-------*
    * @method  CdmValueListDouble::Serialize                 // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:53:34 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:35:13 2007-------*
    * @method  CdmValueListDouble::Deserialize                    // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:35:13 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:40:35 2012-------*
    * @method  CdmValueListDouble::AddValue                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:40:35 2012----------*/
void AddValue( double p_dValue);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:40:41 2012-------*
    * @method  CdmValueListDouble::RemoveValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:40:41 2012----------*/
void RemoveValue( double p_dValue);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:07:28 2013-------*
    * @method  CdmValueListDouble::GetList                   // public, const, slots              *
    * @return  QLinkedList<double>                           //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:07:28 2013----------*/
QLinkedList<double> GetList( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:25:49 2007-------*
    * @method  CdmValueListDouble::CdmValueListDouble                  // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:25:49 2007----------*/
    CdmValueListDouble( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:41:06 2012-------*
    * @method  CdmValueListDouble::SetList                   // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QLinkedList<double> p_qllDoubles              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:41:06 2012----------*/
void SetList( QLinkedList<double> p_qllDoubles);


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:48:20 2012-------*
    * @method  CdmValueListDouble::CdmValueListDouble        // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:48:20 2012----------*/
    CdmValueListDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:36:42 2012--------*
    * @method  CdmValueListDouble::Deploy                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:36:42 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:07:56 2013-------*
    * @method  CdmValueListDouble::GetValueVariant           // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:07:56 2013----------*/
    virtual QVariant GetValueVariant() const;

    static void DeserializeXmlToDoubleList(QString &p_qstrXml, QLinkedList<double> &p_qllList);
public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:07:36 2013-------*
    * @method  CdmValueListDouble::GetValueAsString          // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:07:36 2013----------*/
      virtual QString GetValueAsString( ) const;
      virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
