/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTREF_H
#define CDMOBJECTREF_H

// System and QT Includes


// own Includes
#include "CdmMember.h"
#include "CdmValueLong.h"

// forwards

/*
 * This class implements the value reference to a single
 * object. The objectid is contained by the baseclass in
 * member value.
 */
class WMSMANAGER_API CdmValueObjectRef : public CdmValueLong 
{
   Q_OBJECT

private:    
   /*
    * The objectlist id in which the object is a member
    */
   long m_lObjectListId;

   /*
    *
    */
   mutable bool m_bObjectConnected;
   QString m_qstrObjectKeyname;
   QString m_qstrContainerKeyname;
   QString m_qstrReferenceUri;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:48:01 2005*
    * @method  CdmValueObjectRef::CdmValueObjectRef                    // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the object reference.                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 10:48:01 2005----------*/
CdmValueObjectRef(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:48:17 2005*
    * @method  CdmValueObjectRef::~CdmValueObjectRef                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueObjectRef                                               *
    *----------------last changed: -----------------------------Sa 20. Aug 12:48:17 2005----------*/
virtual ~CdmValueObjectRef(  );
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:33:30 2010-------*
    * @method  CdmValueObjectRef::SetDefaultValue            // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember*# p_pCdmMember                //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:33:30 2010----------*/
    void SetDefaultValue(const CdmMember* p_pCdmMember);
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:33:41 2010-------*
    * @method  CdmValueObjectRef::IsSmaller                  // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Mi 15. Sep 14:33:41 2010----------*/
    virtual int IsSmaller(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:33:50 2010-------*
    * @method  CdmValueObjectRef::IsSmallerEqual             // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Mi 15. Sep 14:33:50 2010----------*/
    virtual int IsSmallerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:34:00 2010-------*
    * @method  CdmValueObjectRef::IsLarger                   // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:34:00 2010----------*/
    virtual int IsLarger(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:34:15 2010-------*
    * @method  CdmValueObjectRef::IsLargerEqual              // public, const, virtual            *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Mi 15. Sep 14:34:15 2010----------*/
    virtual int IsLargerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:34:23 2010-------*
    * @method  CdmValueObjectRef::Add                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   long# p_lAdd                                  //                                   *
    * @comment Adds p_dAdd to Value.                                                              *
    *----------------last changed: -----------------------------Mi 15. Sep 14:34:23 2010----------*/
    virtual void Add(long p_lAdd);
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:34:31 2010-------*
    * @method  CdmValueObjectRef::Subtract                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   long #p_lSubtract                             //                                   *
    * @comment subtracts p_dSubtract from value.                                                  *
    *----------------last changed: -----------------------------Mi 15. Sep 14:34:31 2010----------*/
    virtual void Subtract(long p_lSubtract);
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 10:45:44 2012-------*
    * @method  CdmValueObjectRef::SetValue                   // public, slots                     *
    * @return  void                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @comment This emthod sets the object value.                                                 *
    *----------------last changed: -----------------------------Di 20. Nov 10:45:44 2012----------*/
void SetValue(long p_lObjectListId, long p_lObjectId, QString p_qstrObjectKeyname, QString p_qstrContainerKeyname);
    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 18:36:25 2013-------*
    * @method  CdmValueObjectRef::SetValue                   // public, slots                     *
    * @return  void                                          //                                   *
    * @param   const CdmObject* p_pCdmObject                 //                                   *
    * @comment This method sets the value over the object itselves.                               *
    *----------------last changed: -----------------------------So 10. Feb 18:36:25 2013----------*/
void SetValue( const CdmObject* p_pCdmObject);
void SetEventValue(const CdmObject *p_pCdmObject, const CdmObject *pEventObject);
    public slots:
         /** +-=---------------------------------------------------------Mo 11. Feb 09:55:39 2013-------*
    * @method  CdmValueObjectRef::GetObject                  // public, slots                     *
    * @return  CdmObject*                                    //                                   *
    * @comment returns the object of this object ref or null if this object was not found.        *
    *----------------last changed: -----------------------------Mo 11. Feb 09:55:39 2013----------*/
CdmObject* GetObject( );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 10:47:16 2012-------*
    * @method  CdmValueObjectRef::GetObjectListId            // public, slots                     *
    * @return  long                                          //                                   *
    * @comment returns the Objectlist Id of this ObjectRef                                        *
    *----------------last changed: -----------------------------Di 20. Nov 10:47:16 2012----------*/
long GetObjectListId( );


    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 17:48:34 2013-------*
    * @method  CdmValueObjectRef::GetClassId                 // public, const, slots              *
    * @return  long                                          //                                   *
    * @comment This method returns the Class id for this ref Value.o                              *
    *----------------last changed: -----------------------------So 10. Feb 17:48:34 2013----------*/
long GetClassId( ) const;


   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:00:30 2013-------*
    * @method  CdmValueObjectRef::XmlExport                  // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:00:30 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:50:02 2005*
    * @method  CdmValueObjectRef::XmlImport                       // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 10:50:02 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:49:59 2005*
    * @method  CdmValueObjectRef::XmlImportObjectRef              // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 10:49:59 2005----------*/
void XmlImportObjectRef(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:48:24 2005*
    * @method  CdmValueObjectRef::CdmValueObjectRef                    // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor of the object reference.                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 10:48:24 2005----------*/
CdmValueObjectRef(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:00:39 2013-------*
    * @method  CdmValueObjectRef::GetDisplayString           // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 10:00:39 2013----------*/
QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:29:22 2006*
    * @method  CdmValueObjectRef::CheckUnique                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:29:22 2006-----------*/
virtual void CheckUnique(  );

   public:
   /** +-=---------------------------------------------------------So 18. Jun 18:48:00 2006-------*
    * @method  CdmValueObjectRef::SetValue                        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          // needed for object values          *
    *                                                        //  (objectlistid, objectid)         *
    * @comment This method sets the value for an datatype as string.                              *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Jun 18:48:00 2006----------*/
    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);

    private slots:
   /** +-=---------------------------------------------------------So 9. Mrz 15:51:21 2008--------*
    * @method  CdmValueObjectRef::ObjectRefModifiedSlot      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 9. Mrz 15:51:21 2008-----------*/
void ObjectRefModifiedSlot( );

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:34:12 2013-------*
    * @method  CdmValueObjectRef::ObjectRefModifiedSignal    // private, signals                  *
    * @return  void                                          //                                   *
    * @param   CdmObject*                                    //                                   *
    * @param   CdmValue*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:34:12 2013----------*/
    signals:
       void ObjectRefModifiedSignal( CdmObject*, CdmValue*);

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 10:00:01 2013-------*
    * @method  CdmValueObjectRef::IsTypeOf                   // public, const, slots              *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment This method checks if this is object is type of the overgiven classname.           *
    *----------------last changed: -----------------------------So 10. Feb 10:00:01 2013----------*/
bool IsTypeOf( QString p_qstrClassName) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:00:58 2013-------*
    * @method  CdmValueObjectRef::GetVariant                 // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 10:00:58 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 13:52:42 2012-------*
    * @method  CdmValueObjectRef::CdmValueObjectRef          // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 13:52:42 2012----------*/
    CdmValueObjectRef( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 10:01:06 2013-------*
    * @method  CdmValueObjectRef::GetValueVariant            // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 10:01:06 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:39:21 2012--------*
    * @method  CdmValueObjectRef::SetValueVariant            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:39:21 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   private:
   /** +-=---------------------------------------------------------Mi 7. Nov 13:59:58 2012--------*
    * @method  CdmValueObjectRef::TryToCreateOwnerObject     // private                           *
    * @return  CdmObject*                                    // if nut successfull null will be returned*
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 7. Nov 13:59:58 2012-----------*/
    CdmObject* TryToCreateOwnerObject();
    CdmObject* TryToGetOwnerObject();
    CdmObject* TryToGetOwnerObjectByEventObject(CdmObject *pEventObject);
    void SetValueVariantMap(QVariant &p_rqVariant);
    
    void SetValueVariantUri(QVariant& p_rqVariant);

public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:41:06 2012--------*
    * @method  CdmValueObjectRef::Deploy                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:41:06 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 17:48:56 2013-------*
    * @method  CdmValueObjectRef::GetClass                   // public, const                     *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 17:48:56 2013----------*/
    CdmClass* GetClass() const;

   public:
   /** +-=---------------------------------------------------------Do 13. Dez 08:19:29 2012-------*
    * @method  CdmValueObjectRef::ResolveValue               // public, virtual                   *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 08:19:29 2012----------*/
    virtual bool ResolveValue();

    public slots:
         /** +-=---------------------------------------------------------Fr 8. Feb 16:01:17 2013--------*
    * @method  CdmValueObjectRef::HasValue                   // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment This method returns if this Values has an value.                                   *
    *----------------last changed: -----------------------------Fr 8. Feb 16:01:17 2013-----------*/
      virtual bool HasValue( ) const;

   public:
   /** +-=---------------------------------------------------------Mo 13. Mai 14:13:39 2013-------*
    * @method  CdmValueObjectRef::SetVariant                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 13. Mai 14:13:39 2013----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);
    CdmObject *GetEventObject();
    CdmObject *GetReferenceObjectFromEvent(CdmObject *pEventObject);
};
#endif // //CDMOBJECTREF_H
