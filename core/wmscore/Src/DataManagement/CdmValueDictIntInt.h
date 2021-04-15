/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTINTINT_H
#define CDMDICTINTINT_H

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
class WMSMANAGER_API CdmValueDictIntInt : public CdmValueCharacterDocument
{
   Q_OBJECT

   private:
      /*
       * The list of strings
       */
      QMap<int,int> m_qmMap;



   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:48:44 2007-------*
    * @method  CdmValueDictIntInt::CdmValueDictIntInt                  // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:48:44 2007----------*/
    CdmValueDictIntInt( long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:48:54 2007-------*
    * @method  CdmValueDictIntInt::~CdmValueDictIntInt                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:48:54 2007----------*/
    virtual ~CdmValueDictIntInt( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:31:09 2008-------*
    * @method  CdmValueDictIntInt::SetValue                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:31:09 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:54:26 2013-------*
    * @method  CdmValueDictIntInt::GetValue                  // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:54:26 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:54:34 2013-------*
    * @method  CdmValueDictIntInt::Serialize                 // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:54:34 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:49:32 2007-------*
    * @method  CdmValueDictIntInt::Deserialize                    // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:49:32 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:31:13 2012-------*
    * @method  CdmValueDictIntInt::SetValue                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   int p_iData                                   //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:31:13 2012----------*/
void SetValue( int p_iKey, int p_iData);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:00:30 2013-------*
    * @method  CdmValueDictIntInt::GetDict                   // public, const, slots              *
    * @return  QMap<int, int>                                //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:00:30 2013----------*/
QMap<int, int> GetDict( ) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:31:23 2012-------*
    * @method  CdmValueDictIntInt::RemoveValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:31:23 2012----------*/
void RemoveValue( int p_iKey);


   public:
   /** +-=---------------------------------------------------------Sa 11. Apr 09:48:28 2009-------*
    * @method  CdmValueDictIntInt::CdmValueDictIntInt        // public                            *
    * @return  void                                          //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Sa 11. Apr 09:48:28 2009----------*/
    CdmValueDictIntInt( EdmValueType p_eDmValue,
                        long p_lDatabaseId,
                        long p_lId,
                        QString p_qstrKeyname,
                        CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:31:31 2012-------*
    * @method  CdmValueDictIntInt::ClearDict                 // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:31:31 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:30:03 2012-------*
    * @method  CdmValueDictIntInt::CdmValueDictIntInt        // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:30:03 2012----------*/
    CdmValueDictIntInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:33:54 2012--------*
    * @method  CdmValueDictIntInt::Deploy                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:33:54 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:00:42 2013-------*
    * @method  CdmValueDictIntInt::GetValueAsString          // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:00:42 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:00:52 2013-------*
    * @method  CdmValueDictIntInt::GetValueVariant           // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:00:52 2013----------*/
    QVariant GetValueVariant() const;

    static  void DeserializeXmlToMap(QString &p_qstrXml, QMap<int, int> &p_qMao);
public slots:
   /** +-=---------------------------------------------------------Di 28. Mai 14:52:36 2013-------*
    * @method  CdmValueDictIntInt::SetValue                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<int, int> p_qmValue                      //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 28. Mai 14:52:36 2013----------*/
   void SetValue( QMap<int, int> p_qmValue);
   public slots:
   virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
