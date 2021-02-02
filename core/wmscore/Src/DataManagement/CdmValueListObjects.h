/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueListObjects.h
 ** Started Implementation: 2009/04/10
 ** Description:
 ** 
 ** implements the list of objects value
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CDMVALUELISTOBJECTS_H
#define CDMVALUELISTOBJECTS_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QLinkedList>

// Own Includes
#include "CdmValueCharacterDocument.h"


// Forwards
class CdmObject;



// Enumerations

/* 
 * This class implements the list of objects value
 */
class WMSMANAGER_API CdmValueListObjects : public CdmValueCharacterDocument
{
   Q_OBJECT

private:
    QLinkedList<QPair<long, long> > m_qllObjects;

   public:
   /** +-=---------------------------------------------------------Fr 10. Apr 19:54:08 2009-------*
    * @method  CdmValueListObjects::CdmValueListObjects      // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDatabaseId                            // The Database Id                   *
    * @param   long p_lId                                    // The Value Id                      *
    * @param   QString p_qstrKeyname                         // the value keyname                 *
    * @param   CdmObject* p_pCdmObject                       // the parent object                 *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 10. Apr 19:54:08 2009----------*/
    CdmValueListObjects( long p_lDatabaseId,
                         long p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Fr 10. Apr 19:54:36 2009-------*
    * @method  CdmValueListObjects::~CdmValueListObjects     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueListObjects                                        *
    *----------------last changed: -----------------------------Fr 10. Apr 19:54:36 2009----------*/
    virtual ~CdmValueListObjects( );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:40:24 2013-------*
    * @method  CdmValueListObjects::GetList                  // public, const                     *
    * @return  void                                          //                                   *
    * @param   QLinkedList<CdmObject*>& p_rqvlObjects        //                                   *
    * @comment fills the list of objects                                                          *
    *----------------last changed: -----------------------------So 10. Feb 11:40:24 2013----------*/
    void GetList(QLinkedList<CdmObject*>& p_rqvlObjects) const;

   public:
   /** +-=---------------------------------------------------------Mi 9. Jan 15:09:20 2013--------*
    * @method  CdmValueListObjects::AddValue                 // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCmObject                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Jan 15:09:20 2013-----------*/
    void AddValue(CdmObject* p_pCmObject);
    void AddEventValue(CdmObject *pCdmObject, CdmClass *pObjectClass);

   public:
   /** +-=---------------------------------------------------------Mi 9. Jan 15:09:31 2013--------*
    * @method  CdmValueListObjects::RemoveValue              // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 9. Jan 15:09:31 2013-----------*/
    void RemoveValue(CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 12:01:17 2012-------*
    * @method  CdmValueListObjects::FindObjectById           // public, slots                     *
    * @return  CdmObject*                                    //                                   *
    * @param   int p_iId                                     //                                   *
    * @comment finds the object in the list. if it is not in the list NULL will returned.         *
    *----------------last changed: -----------------------------Di 20. Nov 12:01:17 2012----------*/
CdmObject* FindObjectById( int p_iId);

   public:
   /** +-=---------------------------------------------------------Sa 11. Apr 20:21:10 2009-------*
    * @method  CdmValueListObjects::CdmValueListObjects      // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 11. Apr 20:21:10 2009----------*/
    CdmValueListObjects( QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 14:12:17 2012-------*
    * @method  CdmValueListObjects::CdmValueListObjects      // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 14:12:17 2012----------*/
    CdmValueListObjects( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mi 9. Jan 15:06:09 2013--------*
    * @method  CdmValueListObjects::SetList                  // public                            *
    * @return  void                                          //                                   *
    * @param   QLinkedList<CdmObject*>& p_rqvlObjects        //                                   *
    * @comment fills the list of objects                                                          *
    *----------------last changed: -----------------------------Mi 9. Jan 15:06:09 2013-----------*/
    void SetList(QLinkedList<CdmObject*>& p_rqvlObjects);
    void Deserialize();
    void Serialize() const;
    void RemoveValue(long p_iKey);
    void SetValue(int p_iKey, int p_iData);
    void ClearList();
    void SetValueVariant(QVariant &p_rVariant);
    QVariant GetValueVariant() const;
    QString GetValueAsString() const;
    void Deploy(QVariantMap &p_rqvHash);
    void SetValue(QString p_qstrValue);
    QString GetValue() const;
};

#endif //
