/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMINTLIST_H
#define CDMINTLIST_H

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
class WMSMANAGER_API CdmValueListInt : public CdmValueCharacterDocument
{
   Q_OBJECT

   private:
      /*
       * The list of ints
       */
      QLinkedList<int> m_qvlInts;

 

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:14 2007-------*
    * @method  CdmValueListInt::CdmValueListInt                        // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the intlist.                                                    *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:14 2007----------*/
    CdmValueListInt( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:19 2007-------*
    * @method  CdmValueListInt::~CdmValueListInt                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:19 2007----------*/
    virtual ~CdmValueListInt( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:46:00 2008-------*
    * @method  CdmValueListInt::SetValue                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:46:00 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:32:37 2007-------*
    * @method  CdmValueListInt::GetValue                          // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:32:37 2007----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:32:42 2007-------*
    * @method  CdmValueListInt::Serialize                         // private                           *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 15:32:42 2007----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:32:46 2007-------*
    * @method  CdmValueListInt::Deserialize                       // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:32:46 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:49:34 2012-------*
    * @method  CdmValueListInt::AddValue                     // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:49:34 2012----------*/
void AddValue( int p_iValue);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:49:44 2012-------*
    * @method  CdmValueListInt::RemoveValue                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:49:44 2012----------*/
void RemoveValue( int p_iValue);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:13:35 2013-------*
    * @method  CdmValueListInt::GetList                      // public, const, slots              *
    * @return  QLinkedList<int>                              //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:13:35 2013----------*/
QLinkedList<int> GetList( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:24:43 2007-------*
    * @method  CdmValueListInt::CdmValueListInt                        // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:24:43 2007----------*/
    CdmValueListInt( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:50:15 2012-------*
    * @method  CdmValueListInt::SetList                      // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QLinkedList<int> p_qllInts                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:50:15 2012----------*/
void SetList( QLinkedList<int> p_qllInts);


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 13:33:50 2012-------*
    * @method  CdmValueListInt::CdmValueListInt              // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 13:33:50 2012----------*/
    CdmValueListInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:39:12 2012--------*
    * @method  CdmValueListInt::Deploy                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:39:12 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:13:45 2013-------*
    * @method  CdmValueListInt::GetValueAsString             // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:13:45 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:14:08 2013-------*
    * @method  CdmValueListInt::GetValueVariant              // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:14:08 2013----------*/
    QVariant GetValueVariant() const;
    static void DeserializeXmlToIntList(QString &p_qstrXml, QLinkedList<int> &p_qllList);
public slots:
    virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
