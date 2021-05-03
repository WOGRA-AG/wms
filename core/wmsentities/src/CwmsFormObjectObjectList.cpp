// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CwmsFormObjectObjectList.h"

// Forwards

// Enumerations

CwmsFormObjectContainer::CwmsFormObjectContainer()
 : CwmsFormStandardContainer()
{
}

CwmsFormObjectContainer::CwmsFormObjectContainer(CdmObject* p_pCdmObject)
 : CwmsFormStandardContainer(p_pCdmObject)
{
}

CwmsFormObjectContainer::~CwmsFormObjectContainer()
{
}

QList<QString> CwmsFormObjectContainer::GetSelectionDisplayMembers()
{
   return GetStringList("Selection_Display_Members");
}

void CwmsFormObjectContainer::SetSelectionDisplayMembers(QList<QString> p_qllMembers)
{
	return SetStringList("Selection_Display_Members", p_qllMembers);
}

bool CwmsFormObjectContainer::GetSelectionListReadOnly()
{
   return GetBool("Selection_List_ReadOnly");
}

void CwmsFormObjectContainer::SetSelectionListReadOnly(bool p_bValue)
{
   SetValue("Selection_List_ReadOnly", p_bValue);
}

QString CwmsFormObjectContainer::GetEditorKeyname()
{
   return GetString("Editor_Keyname");
}

void CwmsFormObjectContainer::SetEditorKeyname(QString p_qstrValue)
{
   SetValue("Editor_Keyname", p_qstrValue);
}

QString CwmsFormObjectContainer::GetEditorWql()
{
   return GetString("Editor_Wql");
}

void CwmsFormObjectContainer::SetEditorWql(QString p_qstrValue)
{
   SetValue("Editor_Wql", p_qstrValue);
}

CdmObject* CwmsFormObjectContainer::GetSelectionView()
{
   return GetObjectRefValue("Selection_View");
}

void CwmsFormObjectContainer::SetSelectionView(CdmObject* p_pValue)
{
   SetObjectRefValue("Selection_View", p_pValue);
}

CdmObjectContainer* CwmsFormObjectContainer::GetSelectionObjectList()
{
   return GetContainerRefValue("Selection_ObjectList");
}

void CwmsFormObjectContainer::SetSelectionObjectList(CdmObjectContainer* p_pValue)
{
   if (p_pValue)
   {
      const CdmClass* pClass = p_pValue->GetClass();

      if (CHKPTR(pClass))
      {
         SetClassUri(pClass->GetUriInternal());
      }
   }

   SetContainerRefValue("Selection_ObjectList", p_pValue);
}

CwmsFormObjectContainer CwmsFormObjectContainer::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormObjectContainer cCwmsFormObjectObjectList;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormObjectObjectList.SetObject(pCdmObject);
   }

   return cCwmsFormObjectObjectList;
}
bool CwmsFormObjectContainer::Delete(CwmsFormObjectContainer cCwmsFormObjectObjectList)
{
   bool bSuccess = false;

   if (cCwmsFormObjectObjectList.IsValid())
   {
      cCwmsFormObjectObjectList.SetDeleted();
      cCwmsFormObjectObjectList.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
