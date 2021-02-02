// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormBase.h"

// Forwards

// Enumerations

CwmsFormBase::CwmsFormBase()
 : CdmObjectAdaptor()
{
}

CwmsFormBase::CwmsFormBase(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsFormBase::~CwmsFormBase()
{
}

QString CwmsFormBase::GetName()
{
   return GetString("Name");
}

void CwmsFormBase::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

bool CwmsFormBase::GetPrintEnabled()
{
   return GetBool("Print_Enabled");
}

void CwmsFormBase::SetPrintEnabled(bool p_bValue)
{
   SetValue("Print_Enabled", p_bValue);
}

bool CwmsFormBase::GetJournalEnabled()
{
   return GetBool("Journal_Enabled");
}

void CwmsFormBase::SetJournalEnabled(bool p_bValue)
{
   SetValue("Journal_Enabled", p_bValue);
}

bool CwmsFormBase::GetReadOnly()
{
   return GetBool("Read_Only");
}

void CwmsFormBase::SetReadOnly(bool p_bValue)
{
   SetValue("Read_Only", p_bValue);
}

bool CwmsFormBase::GetDefault()
{
   return GetBool("Default");
}

void CwmsFormBase::SetDefault(bool p_bValue)
{
   SetValue("Default", p_bValue);
}

QString CwmsFormBase::GetClassUri()
{
   return GetString("Class_Uri");
}

void CwmsFormBase::SetClassUri(QString p_iValue)
{
   SetValue("Class_Uri", p_iValue);
}

CdmObject* CwmsFormBase::GetPrintingTemplate()
{
   return GetObjectRefValue("Printing_Template");
}

void CwmsFormBase::SetPrintingTemplate(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Printing_Template", p_pCdmValue);
}

