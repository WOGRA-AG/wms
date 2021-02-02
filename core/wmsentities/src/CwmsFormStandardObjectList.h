#ifndef CWMSFORMSTANDARDOBJECTLIST_H
#define CWMSFORMSTANDARDOBJECTLIST_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "basetools.h"
#include "CwmsFormObjectList.h"

// Own Includes

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormStandardContainer : public CwmsFormContainer
{

   public:
      CwmsFormStandardContainer();
   public:
      CwmsFormStandardContainer(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormStandardContainer();
   public:
      QLinkedList<QString> GetDisplayMembers();
   public:
      void SetDisplayMembers(QString p_qstrValue);
   public:
      QLinkedList<QString> GetSearchMembers();
   public:
      void SetSearchMembers(QString p_qstrValue);
   public:
      CdmObject* GetView();
   public:
      void SetView(CdmObject* p_pCdmValue);
   public:
      static CwmsFormStandardContainer Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsFormStandardContainer cCwmsFormStandardObjectList);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:18:57 2012-------*
    * @method  CwmsFormStandardObjectList::SetSearchMembers  // public                            *
    * @return  void                                          //                                   *
    * @param   QLinkedList<QString> p_qstrlMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:18:57 2012----------*/
    void SetSearchMembers(QLinkedList<QString> p_qstrlMembers);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:19:07 2012-------*
    * @method  CwmsFormStandardObjectList::SetDisplayMembers // public                            *
    * @return  void                                          //                                   *
    * @param   QLinkedList<QString> p_qstrlMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:19:07 2012----------*/
    void SetDisplayMembers(QLinkedList<QString> p_qstrlMembers);
};
#endif //
