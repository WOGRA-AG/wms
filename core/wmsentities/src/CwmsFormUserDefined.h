#ifndef CWMSFORMUSERDEFINED_H
#define CWMSFORMUSERDEFINED_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "basetools.h"
#include "CwmsFormBase.h"

// Own Includes

// Forwards

// Enumerations
enum EwmsFormType
{
   eWmsFormTypeDialog,
   eWmsFormTypeWidget,
   eWmsFormTypeMainWindow
};

enum EwmsFormContext
{
   eWmsFormContextObject,
   eWmsFormContextContainer,
   eWmsFormContextWms
};

class BASETOOLS_API CwmsFormUserDefined : public CwmsFormBase
{

   public:
      CwmsFormUserDefined();
   public:
      CwmsFormUserDefined(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormUserDefined();
   public:
      QString GetUICode();
   public:
      void SetUICode(QString p_qstrValue);
   public:
      bool GetWebForm();
   public:
      void SetWebForm(bool p_bValue);
   public:
      bool GetDesktopForm();
   public:
      void SetDesktopForm(bool p_bValue);
   public:
      bool GetMobileForm();
   public:
      void SetMobileForm(bool p_bValue);
   public:
      bool GetTabletForm();
   public:
      void SetTabletForm(bool p_bValue);
   public:
      static CwmsFormUserDefined Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsFormUserDefined cCwmsFormUserDefined);
   public:
      EwmsFormContext GetContext();
   public:
      void SetContext(EwmsFormContext p_iValue);
    public:
       EwmsFormType GetFormType();
    public:
       void SetFormType(EwmsFormType p_iValue);
};
#endif //
