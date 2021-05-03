#ifndef CWMSFORMVIEW_H
#define CWMSFORMVIEW_H

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

class BASETOOLS_API CwmsFormView : public CwmsFormContainer
{

   public:
      CwmsFormView();
   public:
      CwmsFormView(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormView();
   public:
      void SetViews(QList<QString> p_qstrlViews);
   public:
      QList<QString> GetViews();
   public:
      static CwmsFormView Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsFormView cCwmsFormView);
};
#endif //
