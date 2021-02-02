/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMSTRINGLIST_H
#define CDMSTRINGLIST_H

// Sytsem and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"
#include <QLinkedList>

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueListString : public CdmValueCharacterDocument
{
   Q_OBJECT

      private:
      /*
       * The list of strings
       */
      QLinkedList<QString> m_qvlStrings;




   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:28 2007-------*
    * @method  CdmValueListString::CdmValueListString                  // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:28 2007----------*/
    CdmValueListString( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:32 2007-------*
    * @method  CdmValueListString::~CdmValueListString                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:32 2007----------*/
    virtual ~CdmValueListString( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:46:18 2008-------*
    * @method  CdmValueListString::SetValue                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:46:18 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:52:42 2013-------*
    * @method  CdmValueListString::GetValue                  // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:52:42 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:52:47 2013-------*
    * @method  CdmValueListString::Serialize                 // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:52:47 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:33:58 2007-------*
    * @method  CdmValueListString::Deserialize                    // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:33:58 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:49:07 2012-------*
    * @method  CdmValueListString::AddValue                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 11:49:07 2012----------*/
void AddValue( QString p_qstrValue);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:49:14 2012-------*
    * @method  CdmValueListString::RemoveValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 11:49:14 2012----------*/
void RemoveValue( QString p_qstrValue);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:30:17 2013-------*
    * @method  CdmValueListString::GetList                   // public, const, slots              *
    * @return  QLinkedList<QString>                          //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 10:30:17 2013----------*/
QLinkedList<QString> GetList( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:25:21 2007-------*
    * @method  CdmValueListString::CdmValueListString                  // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:25:21 2007----------*/
    CdmValueListString( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 11:49:27 2012-------*
    * @method  CdmValueListString::ClearList                 // public, slots                     *
    * @return  void                                          //                                   *
    * @comment This method clears the list.                                                       *
    *----------------last changed: -----------------------------Di 20. Nov 11:49:27 2012----------*/
void ClearList( );

   public:
   /** +-=---------------------------------------------------------So 6. Jun 11:43:23 2010--------*
    * @method  CdmValueListString::SetList                   // public                            *
    * @return  void                                          //                                   *
    * @param   QLinkedList<QString> p_qllStrings             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 6. Jun 11:43:23 2010-----------*/
    void SetList(QLinkedList<QString> p_qllStrings);


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 14:07:52 2012-------*
    * @method  CdmValueListString::CdmValueListString        // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 14:07:52 2012----------*/
    CdmValueListString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:42:27 2012--------*
    * @method  CdmValueListString::Deploy                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:42:27 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:30:55 2013-------*
    * @method  CdmValueListString::GetValueVariant           // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:30:55 2013----------*/
    QVariant GetValueVariant() const;

    static void DeserializeXmlToStringList(QString &p_qstrXml, QLinkedList<QString> &p_qllResultList);
    QStringList GetStringList() const;
    int GetListSize() const;
public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:30:43 2013-------*
    * @method  CdmValueListString::GetValueAsString          // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:30:43 2013----------*/
      virtual QString GetValueAsString( ) const;
      virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
