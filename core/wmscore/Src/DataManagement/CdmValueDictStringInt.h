/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTSTRINGINT_H
#define CDMDICTSTRINGINT_H

// Sytsem and QT Includes
#include <QMap>

// own Includes
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"

// forwards
class QString;

/*
 * This class implements the string vlaue.
 */
class WMSMANAGER_API CdmValueDictStringInt : public CdmValueCharacterDocument
{
   Q_OBJECT
      private:
      /*
       * The list of strings
       */
      QMap<QString,int> m_qmMap;



   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:44:43 2007-------*
    * @method  CdmValueDictStringInt::CdmValueDictStringInt            // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:44:43 2007----------*/
    CdmValueDictStringInt( long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject);

   

   public:
   /** +-=---------------------------------------------------------Fr 13. Jun 16:50:58 2008-------*
    * @method  CdmValueDictStringInt::SetValue               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Fr 13. Jun 16:50:58 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 12. Feb 10:55:55 2013-------*
    * @method  CdmValueDictStringInt::GetValue               // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Di 12. Feb 10:55:55 2013----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Di 12. Feb 10:56:00 2013-------*
    * @method  CdmValueDictStringInt::Serialize              // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Di 12. Feb 10:56:00 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:23:47 2007-------*
    * @method  CdmValueDictStringInt::Deserialize                 // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: -----------------------------Mo 13. Aug 15:23:47 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:34:44 2012-------*
    * @method  CdmValueDictStringInt::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   int p_iData                                   //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:34:44 2012----------*/
void SetValue( QString p_qstrKey, int p_iData);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:35:19 2012-------*
    * @method  CdmValueDictStringInt::RemoveValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:35:19 2012----------*/
void RemoveValue( QString p_qstrKey);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:03:41 2013-------*
    * @method  CdmValueDictStringInt::GetDict                // public, const, slots              *
    * @return  QMap<QString, int>                            //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------So 10. Feb 09:03:41 2013----------*/
QMap<QString, int> GetDict( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 15:44:50 2007-------*
    * @method  CdmValueDictStringInt::~CdmValueDictStringInt           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: -----------------------------Mo 13. Aug 15:44:50 2007----------*/
    virtual ~CdmValueDictStringInt( );

   public:
   /** +-=---------------------------------------------------------Mo 13. Aug 16:21:44 2007-------*
    * @method  CdmValueDictStringInt::CdmValueDictStringInt            // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Mo 13. Aug 16:21:44 2007----------*/
    CdmValueDictStringInt( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:03:09 2013-------*
    * @method  CdmValueDictStringInt::ExistValue             // public, const, slots              *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment returns if a value exists.                                                         *
    *----------------last changed: -----------------------------So 10. Feb 09:03:09 2013----------*/
bool ExistValue( QString p_qstrKey) const;

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:03:32 2013-------*
    * @method  CdmValueDictStringInt::GetValue               // public, const, slots              *
    * @return  int                                           //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment returns the value to the given key.                                                *
    *----------------last changed: -----------------------------So 10. Feb 09:03:32 2013----------*/
int GetValue( QString p_qstrKey) const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:35:26 2012-------*
    * @method  CdmValueDictStringInt::ClearDict              // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:35:26 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:39:34 2012-------*
    * @method  CdmValueDictStringInt::CdmValueDictStringInt  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObejct                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:39:34 2012----------*/
    CdmValueDictStringInt( QVariantMap& p_rqvHash, CdmObject* p_pCdmObejct);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:34:53 2012-------*
    * @method  CdmValueDictStringInt::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<QString, int> p_qmValue                  //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:34:53 2012----------*/
void SetValue( QMap<QString, int> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:35:08 2012--------*
    * @method  CdmValueDictStringInt::Deploy                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:35:08 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:03:50 2013-------*
    * @method  CdmValueDictStringInt::GetValueAsString       // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:03:50 2013----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:03:58 2013-------*
    * @method  CdmValueDictStringInt::GetValueVariant        // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:03:58 2013----------*/
QVariant GetValueVariant() const;
static void DeserializeXmlToMap(QString &p_qstrXml, QMap<QString, int> &p_qmMap);
public slots:
    virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
