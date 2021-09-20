// System and QT Includes
#include <QFile>
#include <QTextStream>

// WMS Includes
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsPrintingTemplate.h"

CwmsPrintingTemplate::CwmsPrintingTemplate(CdmObject* p_pCdmObject)
: CdmObjectAdaptor(p_pCdmObject)
{
}

CwmsPrintingTemplate::CwmsPrintingTemplate()
: CdmObjectAdaptor(nullptr)
{
}

CwmsPrintingTemplate::~CwmsPrintingTemplate()
{
}

QString CwmsPrintingTemplate::GetName()
{
   return GetString("Name");
}

void CwmsPrintingTemplate::SetName(QString p_qstrName)
{
   SetValue("Name", p_qstrName);
}

void CwmsPrintingTemplate::SetLanguage(QString p_iId)
{
   //SetValue("Language", p_iId);
}

QString CwmsPrintingTemplate::GetLanguage()
{
   //return GetString("Language");
   return "";
}

long CwmsPrintingTemplate::GetLanguageId()
{
   return GetObjectRef("Language");
}

void CwmsPrintingTemplate::SetTemplate(QString p_qstrContent)
{
   SetValue("Template", p_qstrContent);
}

QString CwmsPrintingTemplate::GetTemplate()
{
   return GetString("Template");
}

bool CwmsPrintingTemplate::ReadTemplateFromFile(QString p_qstrFilename)
{
   bool bSuccess = false;
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::ReadOnly))
   {
      QTextStream qTextStream(&qFile);
      QString qstrTemplate = qTextStream.readAll();
      SetTemplate(qstrTemplate);
      qFile.close();
      bSuccess = true;
   }

   return bSuccess;
}

bool CwmsPrintingTemplate::SaveTemplateToFile(QString p_qstrFilename)
{
   bool bSuccess = false;
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::WriteOnly))
   {
      QTextStream qTextStream(&qFile);
      qTextStream << GetTemplate();
      qFile.close();
      bSuccess = true;
   }

   return bSuccess;
}

void CwmsPrintingTemplate::SetClass(CdmClass* p_rpCdmClass)
{
   if (p_rpCdmClass)
   {
      SetValue("Class", p_rpCdmClass->GetFullQualifiedName());
   }
   else
   {
      SetValue("Class", "");
   }
}

CdmClass* CwmsPrintingTemplate::GetClass()
{
   CdmClass* pCdmClass = nullptr;
   QString qstrKeyname = GetString("Class");

   if (!qstrKeyname.isEmpty())
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

         if (CHKPTR(pCdmClassManager))
         {
            pCdmClass = pCdmClassManager->FindClassByKeyname(qstrKeyname);
         }
      }
   }

   return pCdmClass;
}

void CwmsPrintingTemplate::SetType(EwmsTemplateType p_eWmsType)
{
   SetValue("Type", p_eWmsType);
}

// depricated
void CwmsPrintingTemplate::SetType(int p_eWmsType) // for keep old bms code working
{
   SetValue("Type", p_eWmsType);
}

// depricated
int CwmsPrintingTemplate::GetTypeAsInt()// for keep old bms code working
{
   return GetInt("Type");
}

EwmsTemplateType CwmsPrintingTemplate::GetType()
{
   return (EwmsTemplateType)GetInt("Type");
}

bool CwmsPrintingTemplate::IsDefault()
{
   return GetBool("Default");
}

void CwmsPrintingTemplate::SetDefault(bool p_bDefault)
{
   SetValue("Default", p_bDefault);
}
