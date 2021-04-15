/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTINTSTRING_H
#define CDMDICTINTSTRING_H

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
class WMSMANAGER_API CdmValueDictIntString : public CdmValueCharacterDocument
{
   Q_OBJECT
   
   private:
      /*
       * The list of strings
       */
      QMap<int,QString> m_qmMap;



   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:51:34 2007-------*
    * @method  CdmValueDictIntString::CdmValueDictIntString            // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:51:34 2007----------*/
    CdmValueDictIntString( long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:51:51 2007-------*
    * @method  CdmValueDictIntString::~CdmValueDictIntString           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:51:51 2007----------*/
    virtual ~CdmValueDictIntString( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:31:44 2008-------*
    * @method  CdmValueDictIntString::SetValue               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:31:44 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:54:55 2013-------*
    * @method  CdmValueDictIntString::GetValue               // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:54:55 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:55:05 2013-------*
    * @method  CdmValueDictIntString::Serialize              // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:55:05 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:52:09 2007-------*
    * @method  CdmValueDictIntString::Deserialize                 // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:52:09 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:32:13 2012-------*
    * @method  CdmValueDictIntString::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   QString p_qstrData                            //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:32:13 2012----------*/
void SetValue( int p_iKey, QString p_qstrData);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:01:29 2013-------*
    * @method  CdmValueDictIntString::GetDict                // public, const, slots              *
    * @return  QMap<int, QString>                            //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:01:29 2013----------*/
QMap<int, QString> GetDict( ) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:32:19 2012-------*
    * @method  CdmValueDictIntString::RemoveValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:32:19 2012----------*/
void RemoveValue( int p_iKey);



    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:32:27 2012-------*
    * @method  CdmValueDictIntString::ClearDict              // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:32:27 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:31:25 2012-------*
    * @method  CdmValueDictIntString::CdmValueDictIntString  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:31:25 2012----------*/
    CdmValueDictIntString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:34:25 2012--------*
    * @method  CdmValueDictIntString::Deploy                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:34:25 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:01:36 2013-------*
    * @method  CdmValueDictIntString::GetValueAsString       // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:01:36 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:01:42 2013-------*
    * @method  CdmValueDictIntString::GetValueVariant        // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:01:42 2013----------*/
    QVariant GetValueVariant() const;

    static void DeserializeXmlToMap(QString &p_qstrDocument, QMap<int, QString> &p_qmMap);
public slots:
         /** +-=---------------------------------------------------------Di 28. Mai 14:53:04 2013-------*
    * @method  CdmValueDictIntString::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<int, QString> p_qmValue                  //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 28. Mai 14:53:04 2013----------*/
   void SetValue( QMap<int, QString> p_qmValue);
   public slots:
   virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
