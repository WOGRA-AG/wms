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
      CwmsFormUserDefined(CdmObject* p_pCdmObject);
      virtual ~CwmsFormUserDefined();
      QString GetUICode();
      void SetUICode(QString p_qstrValue);
      QString GetXml();
      void SetXml(QString p_qstrValue);
      bool GetWebForm();
      void SetWebForm(bool p_bValue);
      bool IsModal();
      void SetModal(bool p_bValue);
      bool GetDesktopForm();
      void SetDesktopForm(bool p_bValue);
      bool GetMobileForm();
      void SetMobileForm(bool p_bValue);
      bool GetTabletForm();
      void SetTabletForm(bool p_bValue);
      static CwmsFormUserDefined Create(CdmObjectContainer* p_pContainer);
      static bool Delete(CwmsFormUserDefined cCwmsFormUserDefined);
      EwmsFormContext GetContext();
      void SetContext(EwmsFormContext p_iValue);
       EwmsFormType GetFormType();
    public:
       void SetFormType(EwmsFormType p_iValue);
};
#endif //
