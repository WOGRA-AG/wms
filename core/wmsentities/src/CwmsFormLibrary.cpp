// System and QT Includes


// WMS Includes
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"

// Own Includes
#include "CwmsFormLibrary.h"

// Forwards

// Enumerations

CwmsFormLibrary::CwmsFormLibrary()
 : CdmObjectAdaptor()
{
}

CwmsFormLibrary::CwmsFormLibrary(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsFormLibrary::~CwmsFormLibrary()
{
}

QString CwmsFormLibrary::GetName()
{
   return GetString("Name");
}

void CwmsFormLibrary::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

QString CwmsFormLibrary::GetVersion()
{
   return GetString("Version");
}

void CwmsFormLibrary::SetVersion(QString p_qstrValue)
{
   SetValue("Version", p_qstrValue);
}

QString CwmsFormLibrary::GetCode()
{
   return GetString("Code");
}

void CwmsFormLibrary::SetCode(QString p_qstrValue)
{
   SetValue("Code", p_qstrValue);
}

CwmsFormLibrary CwmsFormLibrary::Create()
{
   CwmsFormLibrary cCwmsFormLibrary;
   CdmObjectContainer* pContainer = GetContainer();

   if (CHKPTR(pContainer))
   {
      CdmObject* pCdmObject = pContainer->CreateNewObject();
      cCwmsFormLibrary.SetObject(pCdmObject);
   }

   return cCwmsFormLibrary;
}

CdmObjectContainer* CwmsFormLibrary::GetContainer()
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerByKeyname("TechnicalFormLibrary");
        }
    }

    return pContainer;
}

bool CwmsFormLibrary::Delete(CwmsFormLibrary cCwmsFormLibrary)
{
   bool bSuccess = false;
   if (cCwmsFormLibrary.IsValid())
   {
      cCwmsFormLibrary.SetDeleted();
      cCwmsFormLibrary.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
