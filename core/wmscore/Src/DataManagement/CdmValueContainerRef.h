/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTLISTREF_H
#define CDMOBJECTLISTREF_H

// System and QT Includes

// own Includes
#include "CdmMember.h"
#include "CdmValueLong.h"

// forwards

/*
 * This class implements the value reference to an objectlist.
 * The base class contains in value the objectlist id!!!!
 */
class WMSMANAGER_API CdmValueContainerRef : public CdmValueLong 
{
   Q_OBJECT

   private:

      QString m_qstrReferenceUri;
      QString m_qstrContainerKeyname;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:43:24 2005*
    * @method  CdmValueContainerRef::CdmValueContainerRef            // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The cosntructor of the objectlist reference.                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 10:43:24 2005----------*/
CdmValueContainerRef(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:48:07 2005*
    * @method  CdmValueContainerRef::~CdmValueContainerRef           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmValueContainerRef                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 12:48:07 2005----------*/
virtual ~CdmValueContainerRef(  );
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:34:52 2010-------*
    * @method  CdmValueContainerRef::SetDefaultValue        // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmMember* #p_pCdmMember                //                                   *
    * @comment This method sets the default value.                                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:34:52 2010----------*/
    void SetDefaultValue(const CdmMember* p_pCdmMember);

   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:01 2010-------*
    * @method  CdmValueContainerRef::IsSmaller              // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*# p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller then this.                               *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:01 2010----------*/
    int IsSmaller(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:10 2010-------*
    * @method  CdmValueContainerRef::IsSmallerEqual         // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant*# p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is smaller or equal then this.                      *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:10 2010----------*/
    int IsSmallerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:20 2010-------*
    * @method  CdmValueContainerRef::IsLarger               // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger then this.                                *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:20 2010----------*/
    int IsLarger(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:29 2010-------*
    * @method  CdmValueContainerRef::IsLargerEqual          // public, const                     *
    * @return  int                                           // invalid = -1 false = 0 true = 1   *
    * @param   QVariant* #p_pqVariant                        //                                   *
    * @comment returns if the overgiven Value is larger or equal then this.                       *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:29 2010----------*/
    int IsLargerEqual(QVariant* p_pqVariant) const;
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:37 2010-------*
    * @method  CdmValueContainerRef::Add                    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   long #p_lAdd                                  //                                   *
    * @comment Adds p_dAdd to Value.                                                              *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:37 2010----------*/
    virtual void Add(long p_lAdd);
   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 14:35:44 2010-------*
    * @method  CdmValueContainerRef::Subtract               // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   long# p_lSubtract                             //                                   *
    * @comment subtracts p_dSubtract from value.                                                  *
    *----------------last changed: -----------------------------Mi 15. Sep 14:35:44 2010----------*/
    virtual void Subtract(long p_lSubtract);
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:44:00 2005*
    * @method  CdmValueContainerRef::GetContainer               // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment returns the Object list which belongs to this object ref.                          *
    *----------------last changed: -----------------------------Sa 20. Aug 10:44:00 2005----------*/
CdmObjectContainer* GetContainer(  );
    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 10:43:27 2012-------*
    * @method  CdmValueContainerRef::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 10:43:27 2012----------*/
void SetValue( CdmObjectContainer* p_pContainer);


   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:57:31 2013-------*
    * @method  CdmValueContainerRef::GetClassId             // public, const                     *
    * @return  long                                          //                                   *
    * @comment This method returns the Class id for this ref Value.o                              *
    *----------------last changed: -----------------------------So 10. Feb 09:57:31 2013----------*/
    long GetClassId() const;

    public slots:
         /** +-=---------------------------------------------------------Di 20. Nov 10:43:43 2012-------*
    * @method  CdmValueContainerRef::SetValue               // public, slots                     *
    * @return  void                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 10:43:43 2012----------*/
void SetValue(long p_lObjectListId, QString p_qstrContainerKeyname);
void SetValue(long p_lObjectListId);


   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:58:05 2013-------*
    * @method  CdmValueContainerRef::XmlExport              // public, const, virtual            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:58:05 2013----------*/
    virtual void XmlExport(QDomElement& p_rqdeValue) const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:44:55 2005*
    * @method  CdmValueContainerRef::XmlImport                   // public                            *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method is the abstract method to which must be implemented in each derived class.*
    *----------------last changed: -----------------------------Sa 20. Aug 10:44:55 2005----------*/
void XmlImport(  QDomElement& p_rqDomElement );

   private:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:44:51 2005*
    * @method  CdmValueContainerRef::XmlImportContainerRef      // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 10:44:51 2005----------*/
void XmlImportContainerRef(  QDomElement& p_rqDomElement );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:43:47 2005*
    * @method  CdmValueContainerRef::CdmValueContainerRef            // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The xml constructor of the objectlist reference.                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 10:43:47 2005----------*/
CdmValueContainerRef(  QDomElement& p_rqDomElement, CdmObject* p_pCdmObject );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:58:18 2013-------*
    * @method  CdmValueContainerRef::GetDisplayString       // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:58:18 2013----------*/
QString GetDisplayString( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 7. Jan 14:29:08 2006*
    * @method  CdmValueContainerRef::CheckUnique                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method checks if the value complies with the unique rule.                     *
    *----------------last changed: Wolfgang Graßhof-------------Sa 7. Jan 14:29:08 2006-----------*/
virtual void CheckUnique(  );
CdmObjectContainer* GetEmptyContainer( );

    public slots:
         /** +-=---------------------------------------------------------So 10. Feb 09:57:00 2013-------*
    * @method  CdmValueContainerRef::IsTypeOf               // public, const, slots              *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment This method checks if this is object is type of the overgiven classname.           *
    *----------------last changed: -----------------------------So 10. Feb 09:57:00 2013----------*/
bool IsTypeOf( QString p_qstrClassName) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:58:26 2013-------*
    * @method  CdmValueContainerRef::GetVariant             // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment This method returns the value as string for displaying information.                *
    *----------------last changed: -----------------------------So 10. Feb 09:58:26 2013----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 13:50:14 2012-------*
    * @method  CdmValueContainerRef::CdmValueContainerRef  // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 13:50:14 2012----------*/
    CdmValueContainerRef( QVariantMap& p_rqvHash, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:58:35 2013-------*
    * @method  CdmValueContainerRef::GetValueVariant        // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:58:35 2013----------*/
    virtual QVariant GetValueVariant() const;

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 08:35:38 2012--------*
    * @method  CdmValueContainerRef::SetValueVariant        // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 08:35:38 2012-----------*/
    virtual void SetValueVariant(QVariant& p_rqVariant);

   public:
   /** +-=---------------------------------------------------------Mo 3. Dez 15:40:32 2012--------*
    * @method  CdmValueContainerRef::Deploy                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 15:40:32 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------Fr 7. Dez 15:38:42 2012--------*
    * @method  CdmValueContainerRef::GetClass               // public                            *
    * @return  CdmClass*                                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Dez 15:38:42 2012-----------*/
    CdmClass* GetClass();

   public:
   /** +-=---------------------------------------------------------Do 13. Dez 08:19:11 2012-------*
    * @method  CdmValueContainerRef::ResolveValue           // public, virtual                   *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Dez 08:19:11 2012----------*/
    virtual bool ResolveValue();

    virtual void SetValue(QString p_qstrValue, QString p_qstrValue2);
public slots:
         /** +-=---------------------------------------------------------Fr 8. Feb 16:01:49 2013--------*
    * @method  CdmValueContainerRef::HasValue               // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment This method returns if this Values has an value.                                   *
    *----------------last changed: -----------------------------Fr 8. Feb 16:01:49 2013-----------*/
      virtual bool HasValue( ) const;

};
#endif // //CDMOBJECTLISTREF_H
