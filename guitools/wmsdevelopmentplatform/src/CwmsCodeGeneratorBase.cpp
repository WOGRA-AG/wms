// System and QT Includes
#include <QFile>
#include <QTextStream>

// WMS Includes
#include "CdmClass.h"

// own Includes
#include "CwmsCodeGeneratorBase.h"


CwmsCodeGeneratorBase::CwmsCodeGeneratorBase()
{
}

CwmsCodeGeneratorBase::~CwmsCodeGeneratorBase()
{
}

void CwmsCodeGeneratorBase::SaveFile(QString p_qstrFilename, QString p_qstrContent)
{
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::WriteOnly | QIODevice::Text))
   {
      QTextStream qTextStream(&qFile);
      qTextStream << p_qstrContent;
      qFile.close();
   }
}

QString CwmsCodeGeneratorBase::GenerateCodeMemberName(QString p_qstrMember)
{
   QString qstrRet;
   qstrRet = p_qstrMember.remove("_");
   qstrRet = p_qstrMember.remove(" ");
   qstrRet = p_qstrMember.remove(":");
   qstrRet = p_qstrMember.remove("!");
   return qstrRet;
}

QString CwmsCodeGeneratorBase::AddIndent(int p_iIndentStage)
{
   QString qstrIndent;

   while (p_iIndentStage > 0)
   {
      qstrIndent += "   ";
      p_iIndentStage--;
   }

   return qstrIndent;
}

bool CwmsCodeGeneratorBase::CheckSetterMethod(EdmValueType p_eDmValue)
{
   bool bRet = false;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
   case eDmValueBool:
   case eDmValueCharacterDocument:
   case eDmValueDate:
   case eDmValueDateTime:
   case eDmValueDouble:
   case eDmValueEnum:
   case eDmValueFloat:
   case eDmValueInt:
   case eDmValueLong:
   case eDmValueContainerRef:
   case eDmValueObjectRef:
   case eDmValueString:
   case eDmValueTime:
   case eDmValueUser:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
   case eDmValueListDouble:
   case eDmValueListInt:
   case eDmValueListObjects:
   case eDmValueListString:
   case eDmValueDictIntDouble:
      bRet = true;
      break;
   case eDmValueCounter:
   case eDmValueObjectTree:
   case eDmValueFormula:
   default:
      bRet = false;
      break;
   }

   return bRet;
}

bool CwmsCodeGeneratorBase::CheckGetterMethod(EdmValueType p_eDmValue)
{
   bool bRet = false;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
   case eDmValueBool:
   case eDmValueCharacterDocument:
   case eDmValueCounter:
   case eDmValueDate:
   case eDmValueDateTime:
   case eDmValueDouble:
   case eDmValueEnum:
   case eDmValueFloat:
   case eDmValueFormula:
   case eDmValueInt:
   case eDmValueListDouble:
   case eDmValueListInt:
   case eDmValueListObjects:
   case eDmValueListString:
   case eDmValueLong:
   case eDmValueContainerRef:
   case eDmValueObjectRef:
   case eDmValueString:
   case eDmValueTime:
   case eDmValueUser:
   case eDmValueDictIntDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
      bRet = true;
      break;

   case eDmValueObjectTree:
   default:
      bRet = false;
      break;
   }

   return bRet;
}

void CwmsCodeGeneratorBase::GetClassMembers(CdmClass* p_pCdmClass,
                                            bool p_bIncludeBaseClassMembers,
                                            QMap<qint64,
                                            CdmMember*>& p_rqmMembers)
{
   if (p_bIncludeBaseClassMembers)
   {
      p_rqmMembers = p_pCdmClass->GetClassMemberMap();
   }
   else
   {
      p_pCdmClass->GetMemberMap(p_rqmMembers);
   }
}
