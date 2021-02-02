#ifndef CWMSFORMINTERACTIVECOMPONENT_H
#define CWMSFORMINTERACTIVECOMPONENT_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes


// Own Includes
#include "basetools.h"
#include "CwmsFormBase.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormInteractiveComponent: public CwmsFormBase
{

   public:
      CwmsFormInteractiveComponent();
   public:
      CwmsFormInteractiveComponent(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormInteractiveComponent();
   public:
      QString GetView();
   public:
      void SetView(QString p_qstrValue);
   public:
      QString GetViewModel();
   public:
      void SetViewModel(QString p_qstrValue);
   public:
      static bool Delete(CwmsFormInteractiveComponent cCwmsFormInteractiveComponent);
};
#endif //
