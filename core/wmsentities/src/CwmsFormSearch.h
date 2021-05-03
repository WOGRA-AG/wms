#ifndef CWMSFORMSEARCH_H
#define CWMSFORMSEARCH_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes


// Own Includes
#include "basetools.h"
#include "CwmsFormObjectList.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormSearch : public CwmsFormContainer
{

   public:
      CwmsFormSearch();
   public:
      CwmsFormSearch(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormSearch();
   public:
      QList<QString> GetDisplayMembers();
   public:
      void SetDisplayMembers(QString p_qstrValue);
   public:
      CdmObjectContainer* GetSearchList();
   public:
      void SetSearchList(CdmObjectContainer* p_pCdmOLValue);
   public:
      QList<QString> GetSearchMembers();
   public:
      void SetSearchMembers(QString p_qstrValue);
   public:
      static CwmsFormSearch Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsFormSearch cCwmsFormSearch);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:47:41 2012-------*
    * @method  CwmsFormSearch::SetDisplayMembers             // public                            *
    * @return  void                                          //                                   *
    * @param   QList<QString> p_qstrlMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:47:41 2012----------*/
    void SetDisplayMembers(QList<QString> p_qstrlMembers);

   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 18:47:45 2012-------*
    * @method  CwmsFormSearch::SetSearchMembers              // public                            *
    * @return  void                                          //                                   *
    * @param   QList<QString> p_qstrlMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 17. Sep 18:47:45 2012----------*/
    void SetSearchMembers(QList<QString> p_qstrlMembers);
};
#endif //
