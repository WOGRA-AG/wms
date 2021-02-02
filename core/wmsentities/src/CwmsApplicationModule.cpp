// System and QT Includes
#include <QtQml>

// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdmObjectContainer.h"
#include "CwmsApplicationModule.h"

// Forwards

// Enumerations

CwmsApplicationModule::CwmsApplicationModule()
 : CdmObjectAdaptor()
{
}

CwmsApplicationModule::CwmsApplicationModule(CdmObject* p_pCdmObject)
 : CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsApplicationModule::~CwmsApplicationModule()
{
}

QString CwmsApplicationModule::GetName()
{
   return GetString("Name");
}

void CwmsApplicationModule::SetName(QString p_qstrValue)
{
   SetValue("Name", p_qstrValue);
}

int CwmsApplicationModule::GetPosition()
{
   return GetInt("Position");
}

void CwmsApplicationModule::SetPosition(int p_iValue)
{
   SetValue("Position", p_iValue);
}

CdmObjectContainer* CwmsApplicationModule::GetContainerModule()
{
   return GetContainerRefValue("ObjectList_Module");
}

void CwmsApplicationModule::SetContainerModule(CdmObjectContainer* p_pCdmOLValue)
{
   SetContainerRefValue("ObjectList_Module", p_pCdmOLValue);
}

CdmObject* CwmsApplicationModule::GetObjectModule()
{
   return GetObjectRefValue("Object_Module");
}

void CwmsApplicationModule::SetObjectModule(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("Object_Module", p_pCdmValue);
}

CdmObject* CwmsApplicationModule::GetUserInterface()
{
   return GetObjectRefValue("User_Interface");
}

void CwmsApplicationModule::SetUserInterface(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("User_Interface", p_pCdmValue);
}

bool CwmsApplicationModule::GetDefault()
{
   return GetBool("Default");
}

void CwmsApplicationModule::SetDefault(bool p_bValue)
{
   SetValue("Default", p_bValue);
}

CdmObject* CwmsApplicationModule::GetView()
{
   return GetObjectRefValue("View");
}

void CwmsApplicationModule::SetView(CdmObject* p_pCdmValue)
{
   SetObjectRefValue("View", p_pCdmValue);
}

bool CwmsApplicationModule::GetActive()
{
   return GetBool("Active");
}

void CwmsApplicationModule::SetActive(bool p_bValue)
{
   SetValue("Active", p_bValue);
}

QPixmap CwmsApplicationModule::GetIcon()
{
   QPixmap qPixmap;
   if (!GetBinDocCurrentFilename("Icon").isEmpty())
   {
       QByteArray pByteArray = LoadBinDoc("Icon");
       qPixmap.loadFromData(pByteArray);
   }
   
   return qPixmap;
} 

void CwmsApplicationModule::SetIcon(QString p_qstrFilename)
{
   SetBinDocNewFilename("Icon", p_qstrFilename);
}


CwmsApplicationModule CwmsApplicationModule::Create(CdmObjectContainer* p_pContainer)
{
   CwmsApplicationModule cCwmsApplicationModule;

   if (CHKPTR(p_pContainer))
   {
      CdmObject* pCdmObject = p_pContainer->CreateNewObject();
      cCwmsApplicationModule.SetObject(pCdmObject);
   }

   return cCwmsApplicationModule;
}
bool CwmsApplicationModule::Delete(CwmsApplicationModule cCwmsApplicationModule)
{
   bool bSuccess = false;
   if (cCwmsApplicationModule.IsValid())
   {
      cCwmsApplicationModule.SetDeleted();
      cCwmsApplicationModule.CommitObject();
      bSuccess = true;
   }

   return bSuccess;
}
