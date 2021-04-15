/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDICTINTDOUBLE_H
#define CDMDICTINTDOUBLE_H

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
class WMSMANAGER_API CdmValueDictIntDouble : public CdmValueCharacterDocument
{
   Q_OBJECT

   private:
      /*
       * The list of strings
       */
      QMap<int,double> m_qmMap;



   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:41:38 2007-------*
    * @method  CdmValueDictIntDouble::CdmValueDictIntDouble            // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the stringlist.                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:41:38 2007----------*/
    CdmValueDictIntDouble( long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:02:52 2007-------*
    * @method  CdmValueDictIntDouble::~CdmValueDictIntDouble           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmIntList                                                 *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:02:52 2007----------*/
    virtual ~CdmValueDictIntDouble( );

   public:
   /** +-=---------------------------------------------------------Sa 14. Jun 18:30:42 2008-------*
    * @method  CdmValueDictIntDouble::SetValue               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method sets the value of this Value.                                          *
    *----------------last changed: -----------------------------Sa 14. Jun 18:30:42 2008----------*/
    virtual void SetValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 13:00:34 2013--------*
    * @method  CdmValueDictIntDouble::GetValue               // public, const, virtual            *
    * @return  QString                                       //                                   *
    * @comment returns the value.                                                                 *
    *----------------last changed: -----------------------------Sa 9. Feb 13:00:34 2013-----------*/
    virtual QString GetValue() const;

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 10:06:02 2013-------*
    * @method  CdmValueDictIntDouble::Serialize              // private, const                    *
    * @return  void                                          //                                   *
    * @comment This method serializes the list to xml document.                                   *
    *----------------last changed: -----------------------------Mo 11. Feb 10:06:02 2013----------*/
    void Serialize() const;

   private:
   /** +-=---------------------------------------------------------Sa 11. Aug 20:03:09 2007-------*
    * @method  CdmValueDictIntDouble::Deserialize                 // private                           *
    * @return  void                                          //                                   *
    * @comment This mehtod deserialize the xml document to the list.                              *
    *----------------last changed: Wolfgang Graßhof-------------Sa 11. Aug 20:03:09 2007----------*/
    void Deserialize();

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:29:28 2012-------*
    * @method  CdmValueDictIntDouble::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   double p_dData                                //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:29:28 2012----------*/
void SetValue( int p_iKey, double p_dData);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:29:40 2012-------*
    * @method  CdmValueDictIntDouble::RemoveValue            // public, slots                     *
    * @return  void                                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment This method removes a value from list.                                             *
    *----------------last changed: -----------------------------Di 20. Nov 09:29:40 2012----------*/
void RemoveValue( int p_iKey);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 13:01:08 2013--------*
    * @method  CdmValueDictIntDouble::GetDict                // public, const, slots              *
    * @return  QMap<int, double>                             //                                   *
    * @comment This method returns a copy of the list.                                            *
    *----------------last changed: -----------------------------Sa 9. Feb 13:01:08 2013-----------*/
QMap<int, double> GetDict( ) const;



    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 09:29:51 2012-------*
    * @method  CdmValueDictIntDouble::ClearDict              // public, slots                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 09:29:51 2012----------*/
void ClearDict( );


   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 11:25:37 2012-------*
    * @method  CdmValueDictIntDouble::CdmValueDictIntDouble  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 11:25:37 2012----------*/
    CdmValueDictIntDouble( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:33:17 2012--------*
    * @method  CdmValueDictIntDouble::Deploy                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:33:17 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 13:01:15 2013--------*
    * @method  CdmValueDictIntDouble::GetValueAsString       // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 13:01:15 2013-----------*/
      virtual QString GetValueAsString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 13:01:35 2013--------*
    * @method  CdmValueDictIntDouble::GetValueVariant        // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 13:01:35 2013-----------*/
    QVariant GetValueVariant() const;

    static void DeserializeXmlToMap(QString &p_qstrXml, QMap<int, double> &p_qmMap);
public slots:
         /** +-=---------------------------------------------------------Di 28. Mai 14:52:09 2013-------*
    * @method  CdmValueDictIntDouble::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QMap<int, double> p_qmValue                   //                                   *
    * @comment This method adds an value to the list.                                             *
    *----------------last changed: -----------------------------Di 28. Mai 14:52:09 2013----------*/
void SetValue( QMap<int, double> p_qmValue);
public slots:
virtual void SetValueVariant(QVariant& p_rVariant);
};

#endif //
