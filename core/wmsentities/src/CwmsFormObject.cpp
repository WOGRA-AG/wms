// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsFormObject.h"

// Forwards

// Enumerations

CwmsFormObject::CwmsFormObject()
 : CwmsFormBase()
{
}

CwmsFormObject::CwmsFormObject(CdmObject* p_pCdmObject)
 : CwmsFormBase(p_pCdmObject)
{
}

CwmsFormObject::~CwmsFormObject()
{
}

QString CwmsFormObject::GetCaptionValue()
{
   return GetString("Caption_Value");
}

void CwmsFormObject::SetCaptionValue(QString p_qstrValue)
{
    SetValue("Caption_Value", p_qstrValue);
}

QString CwmsFormObject::GetWql()
{
   return GetString("Wql");
}

void CwmsFormObject::SetWql(QString p_qstrValue)
{
    SetValue("Wql", p_qstrValue);
}

QList<QString> CwmsFormObject::GetVisibleMembers()
{
   return GetStringList("Visible_Members");
}

void CwmsFormObject::SetVisibleMembers(QList<QString> p_qllValue)
{
   SetStringList("Visible_Members", p_qllValue);
}

QList<QString> CwmsFormObject::GetFunctions()
{
   return GetStringList("Functions");
}

void CwmsFormObject::SetFunctions(QList<QString> p_qllValue)
{
   SetStringList("Functions", p_qllValue);
}

QMap<QString, int> CwmsFormObject::GetDisplayTypes()
{
   return GetStringIntDict("Display_Types");
}

void CwmsFormObject::SetDisplayTypes(QMap<QString, int> p_qmDisplayTypes)
{
   SetStringIntDict("Display_Types", p_qmDisplayTypes);
}

QMap<QString, QString> CwmsFormObject::GetObjectRefAssignment()
{
   return GetStringStringDict("ObjectRef_Assignment");
}

void CwmsFormObject::SetObjectRefAssignment(QMap<QString, QString> p_qmDisplayTypes)
{
   SetStringStringDict("ObjectRef_Assignment", p_qmDisplayTypes);
}

QMap<QString, QString> CwmsFormObject::GetDefaultValues()
{
   return GetStringStringDict("Default_Values");
}

void CwmsFormObject::SetDefaultValues(QMap<QString, QString> p_qmDisplayTypes)
{
   SetStringStringDict("Default_Values", p_qmDisplayTypes);
}

CwmsFormObject CwmsFormObject::Create(CdmObjectContainer* p_pContainer)
{
   CwmsFormObject cCwmsFormObject;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsFormObject.SetObject(pCdmObject);
   }

   return cCwmsFormObject;
}
bool CwmsFormObject::Delete(CwmsFormObject cCwmsFormObject)
{
   bool bSuccess = false;
   if (cCwmsFormObject.IsValid())
   {
      cCwmsFormObject.SetDeleted();
      cCwmsFormObject.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
