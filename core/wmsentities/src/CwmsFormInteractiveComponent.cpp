// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormInteractiveComponent.h"

// Forwards

// Enumerations

CwmsFormInteractiveComponent::CwmsFormInteractiveComponent()
 : CwmsFormBase()
{
}

CwmsFormInteractiveComponent::CwmsFormInteractiveComponent(CdmObject* p_pCdmObject)
 : CwmsFormBase(p_pCdmObject)
{
}

CwmsFormInteractiveComponent::~CwmsFormInteractiveComponent()
{
}

QString CwmsFormInteractiveComponent::GetView()
{
   return GetString("View");
}

void CwmsFormInteractiveComponent::SetView(QString p_qstrValue)
{
   SetValue("View", p_qstrValue);
}

QString CwmsFormInteractiveComponent::GetViewModel()
{
   return GetString("ViewModel");
}

void CwmsFormInteractiveComponent::SetViewModel(QString p_qstrValue)
{
   SetValue("ViewModel", p_qstrValue);
}

bool CwmsFormInteractiveComponent::Delete(CwmsFormInteractiveComponent cCwmsFormInteractiveComponent)
{
   bool bSuccess = false;
   if (cCwmsFormInteractiveComponent.IsValid())
   {
      cCwmsFormInteractiveComponent.SetDeleted();
      cCwmsFormInteractiveComponent.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
