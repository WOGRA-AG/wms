// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormUserDefined.h"

// Forwards

// Enumerations

CwmsFormUserDefined::CwmsFormUserDefined()
 : CwmsFormBase()
{
}

CwmsFormUserDefined::CwmsFormUserDefined(CdmObject* p_pCdmObject)
 : CwmsFormBase(p_pCdmObject)
{
}

CwmsFormUserDefined::~CwmsFormUserDefined()
{
}

QString CwmsFormUserDefined::GetUICode()
{
   return GetString("UI_Code");
}

void CwmsFormUserDefined::SetUICode(QString p_qstrValue)
{
   SetValue("UI_Code", p_qstrValue);
}

bool CwmsFormUserDefined::GetWebForm()
{
   return GetBool("Web_Form");
}

void CwmsFormUserDefined::SetWebForm(bool p_bValue)
{
   SetValue("Web_Form", p_bValue);
}

bool CwmsFormUserDefined::GetDesktopForm()
{
   return GetBool("Desktop_Form");
}

void CwmsFormUserDefined::SetDesktopForm(bool p_bValue)
{
   SetValue("Desktop_Form", p_bValue);
}

bool CwmsFormUserDefined::GetMobileForm()
{
   return GetBool("Mobile_Form");
}

void CwmsFormUserDefined::SetMobileForm(bool p_bValue)
{
   SetValue("Mobile_Form", p_bValue);
}

bool CwmsFormUserDefined::GetTabletForm()
{
   return GetBool("Tablet_Form");
}

void CwmsFormUserDefined::SetTabletForm(bool p_bValue)
{
   SetValue("Tablet_Form", p_bValue);
}

EwmsFormContext CwmsFormUserDefined::GetContext()
{
   return (EwmsFormContext)GetInt("Context");
}

void CwmsFormUserDefined::SetContext(EwmsFormContext p_iValue)
{
   SetValue("Context", p_iValue);
}

EwmsFormType CwmsFormUserDefined::GetFormType()
{
   return (EwmsFormType)GetInt("Form_Type");
}

void CwmsFormUserDefined::SetFormType(EwmsFormType p_iValue)
{
   SetValue("Form_Type", p_iValue);
}

CwmsFormUserDefined CwmsFormUserDefined::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormUserDefined cCwmsFormUserDefined;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormUserDefined.SetObject(pCdmObject);
   }

   return cCwmsFormUserDefined;
}
bool CwmsFormUserDefined::Delete(CwmsFormUserDefined cCwmsFormUserDefined)
{
   bool bSuccess = false;
   if (cCwmsFormUserDefined.IsValid())
   {
      cCwmsFormUserDefined.SetDeleted();
      cCwmsFormUserDefined.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
