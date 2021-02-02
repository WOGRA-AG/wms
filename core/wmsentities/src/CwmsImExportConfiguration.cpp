// System and QT Includes


// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes
#include "CwmsImExportConfiguration.h"

// Forwards

// Enumerations

CwmsImExportConfiguration::CwmsImExportConfiguration()
 : CdmObjectAdaptor()
{
}

CwmsImExportConfiguration::CwmsImExportConfiguration(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsImExportConfiguration::~CwmsImExportConfiguration()
{
}

int CwmsImExportConfiguration::GetId()
{
   return GetInt("Id");
}

QString CwmsImExportConfiguration::GetName()
{
   return GetString("Name");
}

void CwmsImExportConfiguration::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

int CwmsImExportConfiguration::GetClassId()
{
   return GetInt("ClassId");
}

QString CwmsImExportConfiguration::GetClassUri()
{
    QString qstrUri;

    if (GetObject()->GetClass()->FindMember("ClassUri"))
    {
        qstrUri = GetString("ClassUri");
    }
    else
    {
        WARNING("Old Scheme Type, no member ClassUri found");
    }

   return qstrUri;
}

QString CwmsImExportConfiguration::GetEncoding()
{
    return GetString("Encoding");
}


void CwmsImExportConfiguration::SetEncoding(QString p_qstrEncoding)
{
    SetValue("Encoding", p_qstrEncoding);
}

void CwmsImExportConfiguration::SetClassId(int p_iValue)
{
   SetValue("ClassId", p_iValue);
}

void CwmsImExportConfiguration::SetClassUri(QString p_qstrUri)
{
    if (GetObject()->GetClass()->FindMember("ClassUri"))
    {
        SetValue("ClassUri", p_qstrUri);
    }
    else
    {
        WARNING("Old Scheme Type, no member ClassUri found");
    }
}

void CwmsImExportConfiguration::SetClass(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        SetClassId(p_pClass->GetId());
        SetClassUri(p_pClass->GetUriInternal());
    }
}

CdmClass* CwmsImExportConfiguration::GetClass()
{
    CdmClass* pClass = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        if (!GetUriInternal().isEmpty())
        {
            QString qstrUri = GetUriInternal();
            pClass = dynamic_cast<CdmClass*>(pManager->GetUriObject(qstrUri));
        }
        else
        {
            CdmClassManager* pClassManager = pManager->GetClassManager();

            if (CHKPTR(pClassManager))
            {
                pClass = pClassManager->FindClassById(GetClassId());
            }
        }
    }

    return pClass;
}

QString CwmsImExportConfiguration::GetConfiguration()
{
   return GetString("Configuration");
}

void CwmsImExportConfiguration::SetConfiguration(QString p_qstrValue)
{
   SetValue("Configuration", p_qstrValue);
}

CwmsImExportConfiguration CwmsImExportConfiguration::Create(CdmObjectContainer* p_pContainer)
{
   CwmsImExportConfiguration cCwmsImExportConfiguration;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsImExportConfiguration.SetObject(pCdmObject);
   }

   return cCwmsImExportConfiguration;
}
bool CwmsImExportConfiguration::Delete(CwmsImExportConfiguration cCwmsImExportConfiguration)
{
   bool bSuccess = false;
   if (cCwmsImExportConfiguration.IsValid())
   {
      cCwmsImExportConfiguration.SetDeleted();
      cCwmsImExportConfiguration.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
