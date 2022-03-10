// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormObjectList.h"

// Forwards

// Enumerations

CwmsFormContainer::CwmsFormContainer()
 : CwmsFormBase()
{
}

CwmsFormContainer::CwmsFormContainer(CdmObject* p_pCdmObject)
 : CwmsFormBase(p_pCdmObject)
{
}

CwmsFormContainer::~CwmsFormContainer()
{
}

QString CwmsFormContainer::GetName()
{
   return GetString("Name");
}

void CwmsFormContainer::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

bool CwmsFormContainer::GetPrintEnabled()
{
   return GetBool("Print_Enabled");
}

void CwmsFormContainer::SetPrintEnabled(bool p_bValue)
{
   SetValue("Print_Enabled", p_bValue);
}

bool CwmsFormContainer::GetJournalEnabled()
{
   return GetBool("Journal_Enabled");
}

void CwmsFormContainer::SetJournalEnabled(bool p_bValue)
{
   SetValue("Journal_Enabled", p_bValue);
}

bool CwmsFormContainer::GetReadOnly()
{
   return GetBool("Read_Only");
}

void CwmsFormContainer::SetReadOnly(bool p_bValue)
{
   SetValue("Read_Only", p_bValue);
}

bool CwmsFormContainer::GetExportEnabled()
{
   return GetBool("Export_Enabled");
}

void CwmsFormContainer::SetExportEnabled(bool p_bValue)
{
   SetValue("Export_Enabled", p_bValue);
}

bool CwmsFormContainer::GetImportEnabled()
{
   return GetBool("Import_Enabled");
}

void CwmsFormContainer::SetImportEnabled(bool p_bValue)
{
   SetValue("Import_Enabled", p_bValue);
}

bool CwmsFormContainer::GetCopyEnabled()
{
   return GetBool("Copy_Enabled");
}

void CwmsFormContainer::SetCopyEnabled(bool p_bValue)
{
   SetValue("Copy_Enabled", p_bValue);
}

bool CwmsFormContainer::GetSaveAsCsvEnabled()
{
   return GetBool("SaveAsCsv_Enabled");
}

void CwmsFormContainer::SetSaveAsCsvEnabled(bool p_bValue)
{
   SetValue("SaveAsCsv_Enabled", p_bValue);
}

bool CwmsFormContainer::GetNewEnabled()
{
   return GetBool("New_Enabled");
}

void CwmsFormContainer::SetNewEnabled(bool p_bValue)
{
   SetValue("New_Enabled", p_bValue);
}

bool CwmsFormContainer::GetSearchEnabled()
{
   return GetBool("Search_Enabled");
}

void CwmsFormContainer::SetSearchEnabled(bool p_bValue)
{
   SetValue("Search_Enabled", p_bValue);
}

bool CwmsFormContainer::GetDefault()
{
   return GetBool("Default");
}

void CwmsFormContainer::SetDefault(bool p_bValue)
{
   SetValue("Default", p_bValue);
}

QList<QString> CwmsFormContainer::GetFunctions()
{
   return GetStringList("Functions");
}

void CwmsFormContainer::SetFunctions(QList<QString> p_qstrlMembers)
{
   SetStringList("Functions", p_qstrlMembers);
}

CdmObject* CwmsFormContainer::GetPrintingTemplate()
{
   return GetObjectRefValue("Printing_Template");
}

void CwmsFormContainer::SetPrintingTemplate(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Printing_Template", p_pCdmValue);
}

