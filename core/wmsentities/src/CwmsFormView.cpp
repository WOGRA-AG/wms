// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormView.h"

// Forwards

// Enumerations

CwmsFormView::CwmsFormView()
 : CwmsFormContainer()
{
}

CwmsFormView::CwmsFormView(CdmObject* p_pCdmObject)
 : CwmsFormContainer(p_pCdmObject)
{
}

CwmsFormView::~CwmsFormView()
{
}

void CwmsFormView::SetViews(QLinkedList<QString> p_qstrlViews)
{
   SetStringList("Views", p_qstrlViews);
}

QLinkedList<QString> CwmsFormView::GetViews()
{
   return GetStringList("Views");
}

CwmsFormView CwmsFormView::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormView cCwmsFormView;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormView.SetObject(pCdmObject);
   }

   return cCwmsFormView;
}
bool CwmsFormView::Delete(CwmsFormView cCwmsFormView)
{
   bool bSuccess = false;
   if (cCwmsFormView.IsValid())
   {
      cCwmsFormView.SetDeleted();
      cCwmsFormView.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
