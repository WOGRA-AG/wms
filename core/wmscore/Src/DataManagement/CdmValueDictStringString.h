/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTSTRINGSTRING_H
#define CDMDICTSTRINGSTRING_H

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
class WMSMANAGER_API CdmValueDictStringString : public CdmValueCharacterDocument
{
   Q_OBJECT
      private:
      /*
       * The list of strings
       */
      QMap<QString,QString> m_qmMap;



   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:44:57 2007-------*
    * @method  CdmValueDictStringString::CdmValueDictStringString      // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:44:57 2007----------*/
    CdmValueDictStringString( long p_lDatabaseId,
                         long p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:45:02 2007-------*
    * @method  CdmValueDictStringString::~CdmValueDictStringString     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:45:02 2007----------*/
    virtual ~CdmValueDictStringString( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:45:16 2008-------*
    * @method  CdmValueDictStringString::SetValue            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:45:16 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:56:19 2013-------*
    * @method  CdmValueDictStringString::GetValue            // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:56:19 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:56:32 2013-------*
    * @method  CdmValueDictStringString::Serialize           // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:56:32 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:11:20 2007-------*
    * @method  CdmValueDictStringString::Deserialize              // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:11:20 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:37:21 2012-------*
    * @method  CdmValueDictStringString::SetValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QString p_qstrData                            //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:37:21 2012----------*/
void SetValue( QString p_qstrKey, QString p_qstrData);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:38:51 2012-------*
    * @method  CdmValueDictStringString::RemoveValue         // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:38:51 2012----------*/
void RemoveValue( QString p_qstrKey);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:04:28 2013-------*
    * @method  CdmValueDictStringString::GetDict             // public, const, slots              *
    * @return  QMap<QString, QString>                        //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:04:28 2013----------*/
QMap<QString, QString> GetDict( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:24:15 2007-------*
    * @method  CdmValueDictStringString::CdmValueDictStringString      // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:24:15 2007----------*/
    CdmValueDictStringString( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:36:56 2012-------*
    * @method  CdmValueDictStringString::ExistValue          // public, slots                     *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment returns if a value exists.                                                         *
    *----------------last changed: -----------------------------Di 20. Nov 09:36:56 2012----------*/
bool ExistValue( QString p_qstrKey);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:36:48 2012-------*
    * @method  CdmValueDictStringString::GetValue            // public, slots                     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment returns the value to the given key.                                                *
    *----------------last changed: -----------------------------Di 20. Nov 09:36:48 2012----------*/
QString GetValue( QString p_qstrKey);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:39:00 2012-------*
    * @method  CdmValueDictStringString::ClearDict           // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:39:00 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:40:43 2012-------*
    * @method  CdmValueDictStringString::CdmValueDictStringString // public                       *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:40:43 2012----------*/
    CdmValueDictStringString( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:37:43 2012-------*
    * @method  CdmValueDictStringString::SetValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<QString, QString> p_qmValue              //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:37:43 2012----------*/
void SetValue( QMap<QString, QString> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:35:39 2012--------*
    * @method  CdmValueDictStringString::Deploy              // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:35:39 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:04:34 2013-------*
    * @method  CdmValueDictStringString::GetValueAsString    // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:04:34 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:04:39 2013-------*
    * @method  CdmValueDictStringString::GetValueVariant     // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:04:39 2013----------*/
QVariant GetValueVariant() const;
static void DeserializeXmlToMap(QString &p_qstrXml, QMap<QString, QString> &p_qmMap);
public slots:
   virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
