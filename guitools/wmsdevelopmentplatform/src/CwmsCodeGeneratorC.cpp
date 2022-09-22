// System and QT Includes
#include <QFile>
#include <QFileInfo>
#include <QTextStream>


// WMS Includes
#include "CdmClass.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsCodeGeneratorTestC.h"
#include "CwmsCodeGeneratorCBl.h"
#include "CwmsCodeGeneratorCTemp.h"
#include "CwmsCodeGeneratorCWebIf.h"
#include "CwmsCodeGeneratorC.h"


CwmsCodeGeneratorC::CwmsCodeGeneratorC(CdmClass* p_pCdmClass,
                                       QString p_qstrClassName,
                                       QString p_qstrFilename)
: CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassName),
  m_rpCdmClass(p_pCdmClass),
  m_bCreateBaseClassMemberFunctions(true),
  m_bGenerateStandardObjectList(false),
  m_bGenerateTestCode(false),
  m_bGenerateBusinessLogicClass(false),
  m_bGenerateTempClass(false),
  m_bGenerateWebInterface(false)
{
}

CwmsCodeGeneratorC::~CwmsCodeGeneratorC()
{
   
}

void CwmsCodeGeneratorC::SetGenerateTestCode(bool p_bGenerate)
{
   m_bGenerateTestCode = p_bGenerate;
}

void CwmsCodeGeneratorC::SetGenerateBusinessLogicCode(bool p_bGenerate)
{
   m_bGenerateBusinessLogicClass = p_bGenerate;
}

void CwmsCodeGeneratorC::SetGenerateTempClassCode(bool p_bGenerate)
{
   m_bGenerateTempClass = p_bGenerate;
}

void CwmsCodeGeneratorC::SetGenerateWebInterfaceCode(bool p_bGenerate)
{
   m_bGenerateWebInterface = p_bGenerate;
}

void CwmsCodeGeneratorC::SetWebInterfaceClassName(QString p_qstrClassName)
{
   m_qstrWebInterfaceClassName = p_qstrClassName;
}

void CwmsCodeGeneratorC::SetWebInterfaceObjectListName(QString p_qstrOLName)
{
   m_qstrWebInterfaceOLKeyname = p_qstrOLName;
}

void CwmsCodeGeneratorC::SetCreateBaseClassMemberFunctions(bool p_bCreate)
{
   if (!m_rpCdmClass->IsAbstract())
   {
      m_bCreateBaseClassMemberFunctions = p_bCreate;
   }
}

void CwmsCodeGeneratorC::SetGenerateStandardObjectList(bool p_bStandard)
{
   m_bGenerateStandardObjectList = p_bStandard;
}

void CwmsCodeGeneratorC::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      GenerateCodeP();
      SaveFiles();

      if (m_bGenerateBusinessLogicClass)
      {
         QString qstrClassname = m_qstrClassName + "Bl";
         CwmsCodeGeneratorCBl cBlGenerator(m_qstrFilename, 
                                           qstrClassname, 
                                           m_rpCdmClass, 
                                           m_qstrListAbstractFunctionsForBaseClass);
         cBlGenerator.GenerateCode();
      }

      if (m_bGenerateTempClass)
      {
         QString qstrClassname = m_qstrClassName + "Temp";
         CwmsCodeGeneratorCTemp cTempGenerator(m_rpCdmClass,
                                             qstrClassname, 
                                             m_qstrFilename, 
                                             m_qstrClassName,
                                             m_qstrClassName + "Bl");
         cTempGenerator.GenerateCode();
      }

      if (m_bGenerateTestCode)
      {
         QString qstrClassname = m_qstrClassName + "Test";
         CwmsCodeGeneratorTestC cTestGenerator(this, m_qstrFilename, qstrClassname, m_rpCdmClass);
         cTestGenerator.GenerateCode();
      }

      if (m_bGenerateWebInterface)
      {
         QString qstrOLKeyname;

         if (m_bGenerateStandardObjectList)
         {
            qstrOLKeyname = GenerateStandardObjectListKeyname();
         }
         else
         {
            qstrOLKeyname = m_qstrWebInterfaceOLKeyname;
         }

         CwmsCodeGeneratorCWebIf cWebIfGenerator(m_qstrFilename, m_qstrWebInterfaceClassName, m_rpCdmClass, qstrOLKeyname, m_qstrClassName);
         cWebIfGenerator.GenerateCode();
      }
   }
}

void CwmsCodeGeneratorC::GenerateCodeP()
{
   if (CHKPTR(m_rpCdmClass))
   {
      AddSourceInclude("CdmObjectContainer.h");

      if (m_bGenerateBusinessLogicClass)
      {
         AddBaseClassData(m_qstrClassName +"Bl", m_qstrClassName +"Bl" + ".h");
      }

      if (m_bGenerateTempClass)
      {
         AddSourceInclude(m_qstrClassName + "Temp" + ".h");
      }

      OpenClass();
      GenerateSourceHeader();
      GeneratesConstructors();
      GenerateDestructors();
      GeneratesMemberAccess();

      if (!m_rpCdmClass->IsAbstract())
      {
         GenerateCreateMethod();
         GenerateDeleteMethod();

         if (m_bGenerateStandardObjectList)
         {
            GenerateStandardObjectList();
         }
      }
      
      CloseClass();
   }
}

void CwmsCodeGeneratorC::GeneratesConstructors()
{
   GenerateDefaultConstructorSource();
   GenerateParameterConstructorSource();
   GenerateDefaultConstructorHeader();
   GenerateParameterConstructorHeader();
}

void CwmsCodeGeneratorC::GenerateMethodInHeader(QString p_qstrMethodName,
                                                EdmMemberAccess p_eAccessType,
                                                EdmValueType p_eReturnValue,
                                                EwmsCodeGenerationMethodType p_eType)
{
   if (p_eType == eWmsCodeGenerationMethodTypeSetter)
   {
      GenerateSetterHeader(p_qstrMethodName, p_eAccessType, p_eReturnValue);
   }
   else if (p_eType == eWmsCodeGenerationMethodTypeGetter)
   {
      GenerateGetterHeader(p_qstrMethodName, p_eAccessType, p_eReturnValue);
   }
}

void CwmsCodeGeneratorC::GenerateMethodInSource(QString p_qstrMethodName,
                                                EdmValueType p_eReturnValue,
                                                EwmsCodeGenerationMethodType p_eType)
{
   if (p_eType == eWmsCodeGenerationMethodTypeSetter)
   {
      GenerateSetterSource(p_qstrMethodName, p_eReturnValue);
   }
   else if (p_eType == eWmsCodeGenerationMethodTypeGetter)
   {
      GenerateGetterSource(p_qstrMethodName, p_eReturnValue);
   }
}

void CwmsCodeGeneratorC::GenerateSetterSource(QString p_qstrMember, EdmValueType p_eReturnValue)
{
   if (CheckSetterMethod(p_eReturnValue))
   {
      m_qstrSource += "void ";
      m_qstrSource += m_qstrClassName + "::Set" + GenerateCodeMemberName(p_qstrMember) + "(" + GetParameter(p_eReturnValue) + ")\n";
      m_qstrSource += "{\n";
      m_qstrSource += GenerateSetterCode(p_eReturnValue, p_qstrMember);
      m_qstrSource += "}\n\n";
   }
}

QString CwmsCodeGeneratorC::GenerateSetterCode(EdmValueType p_eReturnValue, QString p_qstrMember)
{
   QString qstrRet = AddIndent(1);

   switch (p_eReturnValue)
   {
   case eDmValueBinaryDocument:
      qstrRet += "SetBinDocNewFilename(\"" + p_qstrMember + "\", p_qstrFilename);"; // Filename
      break;
   case eDmValueBool:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_bValue);";
      break;
   case eDmValueCharacterDocument:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_qstrValue);";
      break;
   case eDmValueEnum:
   case eDmValueCounter:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_iValue);";
      break;
   case eDmValueDate:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_qdValue);";
      break;
   case eDmValueDateTime:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_qdtValue);";
      break;
   case eDmValueDictIntDouble:
      qstrRet += "SetIntDoubleDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDictIntInt:
      qstrRet += "SetIntIntDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDictIntString:
      qstrRet += "SetIntStringDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDictStringDouble:
      qstrRet += "SetStringDoubleDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDictStringInt:
      qstrRet += "SetStringIntDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDictStringString:
      qstrRet += "SetStringStringDict(\"" + p_qstrMember + "\", p_qmValue);";
      break;
   case eDmValueDouble:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_dValue);";
      break;
   case eDmValueFloat:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_fValue);";
      break;
   case eDmValueFormula:
      qstrRet += "";
      break;
   case eDmValueInt:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_iValue);";
      break;
   case eDmValueListDouble:
      qstrRet += "SetDoubleList(\"" + p_qstrMember + "\", p_qlValue);";
      break;
   case eDmValueListInt:
      qstrRet += "SetIntList(\"" + p_qstrMember + "\", p_qlValue);";
      break;
   case eDmValueListObjects:
      qstrRet += "SetListObjects(\"" + p_qstrMember + "\", p_qlValue);";
      break;
   case eDmValueListString:
      qstrRet += "SetStringList(\"" + p_qstrMember + "\", p_qlValue);";
      break;
   case eDmValueLong:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_lValue);";
      break;
   case eDmValueContainerRef:
      qstrRet += "SetContainerRefValue(\"" + p_qstrMember + "\", p_pCdmOLValue);";
      break;
   case eDmValueObjectRef:
      qstrRet += "SetObjectRefValue(\"" + p_qstrMember + "\", p_pCdmValue);";
      break;
   case eDmValueString:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_qstrValue);";
      break;
   case eDmValueTime:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_qtValue);";
      break;
   case eDmValueUser:
      qstrRet += "SetValue(\"" + p_qstrMember + "\", p_pCumValue);";
      break;
   case eDmValueObjectTree:
      qstrRet += ""; // not yet implemented
      break;
   default:
      qstrRet += "Unknown Type";
   }

   return qstrRet + "\n";
}

void CwmsCodeGeneratorC::GenerateGetterSource(QString p_qstrMember, EdmValueType p_eReturnValue)
{
   if (CheckGetterMethod(p_eReturnValue))
   {
      m_qstrSource += GetReturnType(p_eReturnValue) + " ";
      m_qstrSource += m_qstrClassName + "::Get" + GenerateCodeMemberName(p_qstrMember) + "()\n";
      m_qstrSource += "{\n";
      m_qstrSource += GenerateGetterCode(p_eReturnValue, p_qstrMember);
      m_qstrSource += "}\n\n";
   }
}

QString CwmsCodeGeneratorC::GenerateGetterCode(EdmValueType p_eDmValue, QString p_qstrMember)
{
   QString qstrRet;

   qstrRet += AddIndent(1);

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet += "return GetBinDocCurrentFilename(\"" + p_qstrMember + "\");";
      break;
   case eDmValueBool:
      qstrRet += "return GetBool(\"" + p_qstrMember + "\");";
      break;
   case eDmValueCharacterDocument:
      qstrRet += "return GetString(\"" + p_qstrMember + "\");";
      break;
   case eDmValueEnum:
   case eDmValueCounter:
      qstrRet += "return GetInt(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDate:
      qstrRet += "return GetDate(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDateTime:
      qstrRet += "return GetDateTime(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictIntDouble:
      qstrRet += "return GetIntDoubleDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictIntInt:
      qstrRet += "return GetIntIntDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictIntString:
      qstrRet += "return GetIntStringDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictStringDouble:
      qstrRet += "return GetStringDoubleDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictStringInt:
      qstrRet += "return GetStringIntDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDictStringString:
      qstrRet += "return GetStringStringDict(\"" + p_qstrMember + "\");";
      break;
   case eDmValueDouble:
      qstrRet += "return GetDouble(\"" + p_qstrMember + "\");";
      break;
   case eDmValueFloat:
      qstrRet += "return GetFloat(\"" + p_qstrMember + "\");";
      break;
   case eDmValueFormula:
      qstrRet += "return GetDisplayString(\"" + p_qstrMember + "\");";
      break;
   case eDmValueInt:
      qstrRet += "return GetInt(\"" + p_qstrMember + "\");";
      break;
   case eDmValueListDouble:
      qstrRet += "return GetDoubleList(\"" + p_qstrMember + "\");";
      break;
   case eDmValueListInt:
      qstrRet += "return GetIntList(\"" + p_qstrMember + "\");";
      break;
   case eDmValueListObjects:
      qstrRet += "return GetListObjects(\"" + p_qstrMember + "\");";
      break;
   case eDmValueListString:
      qstrRet += "return GetStringList(\"" + p_qstrMember + "\");";
      break;
   case eDmValueLong:
      qstrRet += "return GetLong(\"" + p_qstrMember + "\");";
      break;
   case eDmValueContainerRef:
      qstrRet += "return GetContainerRefValue(\"" + p_qstrMember + "\");";
      break;
   case eDmValueObjectRef:
      qstrRet += "return GetObjectRefValue(\"" + p_qstrMember + "\");";
      break;
   case eDmValueString:
      qstrRet += "return GetString(\"" + p_qstrMember + "\");";
      break;
   case eDmValueTime:
      qstrRet += "return GetTime(\"" + p_qstrMember + "\");";
      break;
   case eDmValueUser:
      qstrRet += "return GetUser(\"" + p_qstrMember + "\");";
      break;
   case eDmValueObjectTree:
      qstrRet += "NYI"; // not yet implemented
      break;
   default:
      qstrRet += "Unknown Type";
   }

   return qstrRet + "\n";
}

void CwmsCodeGeneratorC::GenerateSetterHeader(QString p_qstrMethodName,
                                              EdmMemberAccess p_eAccessType,
                                              EdmValueType p_eReturnValue)
{
   QString qstrMethod;
   QString qstrAbstract;

   switch(p_eAccessType)
   {
   case eDmMemberAccessPublic:
   case eDmMemberAccessProtected:
   case eDmMemberAccessPrivate:
      qstrMethod += AddIndent(1);
      qstrMethod += "public:\n"; // at the moment the access type plays no role
      break;
   default:
      break;
   }

   qstrMethod += AddIndent(2);
   qstrAbstract += qstrMethod + "virtual ";
   QString qstrFunction = "void Set" + GenerateCodeMemberName(p_qstrMethodName) + "(" + GetParameter(p_eReturnValue) + ")";
   qstrMethod += qstrFunction;
   qstrAbstract += qstrFunction;
   qstrAbstract += " = 0;\n";
   m_qstrListAbstractFunctionsForBaseClass.append(qstrAbstract);
   qstrMethod += ";\n";
   m_qstrHeader += qstrMethod;
}

void CwmsCodeGeneratorC::GenerateGetterHeader(QString p_qstrMethodName,
                                              EdmMemberAccess p_eAccessType,
                                              EdmValueType p_eReturnValue)
{
   QString qstrMethod;
   QString qstrAbstract;

   switch(p_eAccessType)
   {
   case eDmMemberAccessPublic:
   case eDmMemberAccessProtected:
   case eDmMemberAccessPrivate:
      qstrMethod += AddIndent(1);
      qstrMethod += "public:\n"; // at the moment the access type plays no role
      break;
   default:
      break;
   }

   qstrMethod += AddIndent(2);
   qstrAbstract += qstrMethod + "virtual ";
   QString qstrFunction = GetReturnType(p_eReturnValue)+ " Get" + GenerateCodeMemberName(p_qstrMethodName) + "()";
   qstrMethod += qstrFunction;
   qstrAbstract += qstrFunction;
   qstrAbstract += " = 0;\n";
   m_qstrListAbstractFunctionsForBaseClass.append(qstrAbstract);
   qstrMethod += ";\n";
   m_qstrHeader += qstrMethod;
}

void CwmsCodeGeneratorC::GenerateDestructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "virtual ~" + m_qstrClassName + "();\n";
}

void CwmsCodeGeneratorC::GenerateDestructorSource()
{
   m_qstrSource += m_qstrClassName + "::~" + m_qstrClassName + "()\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

void CwmsCodeGeneratorC::GenerateDefaultConstructorSource()
{
   m_qstrSource += m_qstrClassName + "::" + m_qstrClassName + "()\n";

   if (m_qmBaseClasses.isEmpty() || (m_qmBaseClasses.count() == 1 && m_bGenerateBusinessLogicClass))
   {
      m_qstrSource += " : CdmObjectAdaptor()\n";
   }
   else
   {
      QMap<QString, QString>::iterator qmIt = m_qmBaseClasses.begin();
      QMap<QString, QString>::iterator qmItEnd = m_qmBaseClasses.end();
      bool bFirst = true;

      for (; qmIt != qmItEnd; ++qmIt)
      {
         if (bFirst)
         {
            m_qstrSource += " : ";
         }
         else
         {
            m_qstrSource += ",\n";
         }

         m_qstrSource += qmIt.key() + "()";
      }

      m_qstrSource += "\n";
   }
   
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

void CwmsCodeGeneratorC::GenerateDefaultConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "();\n";
}

void CwmsCodeGeneratorC::GenerateParameterConstructorSource()
{
   m_qstrSource += m_qstrClassName + "::" + m_qstrClassName + "(CdmObject* p_pCdmObject)\n";

   // no base classes there or the businesslogic base class should be generated
   if (m_qmBaseClasses.isEmpty() || (m_qmBaseClasses.count() == 1 && m_bGenerateBusinessLogicClass))
   {
      m_qstrSource += " : CdmObjectAdaptor(p_pCdmObject)\n";
   }
   else
   {
      QMap<QString, QString>::iterator qmIt = m_qmBaseClasses.begin();
      QMap<QString, QString>::iterator qmItEnd = m_qmBaseClasses.end();
      bool bFirst = true;

      for (; qmIt != qmItEnd; ++qmIt)
      {
         if (bFirst)
         {
            m_qstrSource += " : ";
         }
         else
         {
            m_qstrSource += ",\n";
         }

         m_qstrSource += qmIt.key() + "(p_pCdmObject)";
      }

      m_qstrSource += "\n";
   }

   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

void CwmsCodeGeneratorC::GenerateParameterConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "(CdmObject* p_pCdmObject);\n";
}

void CwmsCodeGeneratorC::GenerateDestructors()
{
   GenerateDestructorSource();
   GenerateDestructorHeader();
}

void CwmsCodeGeneratorC::GeneratesMemberAccess()
{
   if (m_bCreateBaseClassMemberFunctions)
   {
      GenerateAllMembersAccess();
   }
   else
   {
      GenerateClassMembersAccess();
   }
}

void CwmsCodeGeneratorC::GenerateClassMembersAccess()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<qint64, CdmMember*> qmMembers;
      m_rpCdmClass->GetClassMemberMap(qmMembers);
      QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateMemberAccess(qmIt.value());
      }
   }
}

void CwmsCodeGeneratorC::GenerateAllMembersAccess()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<qint64, CdmMember*> qmMembers;
      m_rpCdmClass->GetMemberMap(qmMembers);
      QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateMemberAccess(qmIt.value());
      }
   }
}

void CwmsCodeGeneratorC::GenerateMemberAccess(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      GenerateMethodInHeader(p_pCdmMember->GetKeyname(), 
                              p_pCdmMember->GetAccessMode(), 
                              p_pCdmMember->GetValueType(), 
                              eWmsCodeGenerationMethodTypeGetter);

      GenerateMethodInSource(p_pCdmMember->GetKeyname(), 
                             p_pCdmMember->GetValueType(), 
                             eWmsCodeGenerationMethodTypeGetter);

      GenerateMethodInHeader(p_pCdmMember->GetKeyname(), 
                              p_pCdmMember->GetAccessMode(), 
                              p_pCdmMember->GetValueType(), 
                              eWmsCodeGenerationMethodTypeSetter);

      GenerateMethodInSource(p_pCdmMember->GetKeyname(), 
                             p_pCdmMember->GetValueType(), 
                             eWmsCodeGenerationMethodTypeSetter);
   }
}

void CwmsCodeGeneratorC::GenerateCreateMethod()
{
   if (!m_qstrWebInterfaceOLKeyname.isEmpty())
   {
      GenerateCreateMethodSourceWithoutParameter();
      GenerateCreateMethodHeaderWithoutParameter();
   }
   else
   {
      GenerateCreateMethodSource();
      GenerateCreateMethodHeader();         
   }
   
}

void CwmsCodeGeneratorC::GenerateDeleteMethod()
{
   GenerateDeleteMethodSource();
   GenerateDeleteMethodHeader();
}

void CwmsCodeGeneratorC::GenerateDeleteMethodSource()
{
   QString qstrParameter = "c" + m_qstrClassName;
   m_qstrSource += "bool " + m_qstrClassName + "::Delete(" + m_qstrClassName + " " + qstrParameter + ")\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "bool bSuccess = false;\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (" + qstrParameter + ".IsValid())\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += qstrParameter + ".SetDeleted();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += qstrParameter + ".CommitObject();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "bSuccess = true;\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "return bSuccess;\n";
   m_qstrSource += "}\n";
}

void CwmsCodeGeneratorC::GenerateDeleteMethodHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static bool Delete(" + m_qstrClassName + " c" + m_qstrClassName + ");\n";
}

void CwmsCodeGeneratorC::GenerateCreateMethodSource()
{
   m_qstrSource += m_qstrClassName + " " + m_qstrClassName + "::Create(CdmObjectContainer* p_pContainer)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += m_qstrClassName + " c" + m_qstrClassName + ";\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(p_pContainer))\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CdmObject* pCdmObject = p_pContainer->CreateNewObject();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "c" + m_qstrClassName + ".SetObject(pCdmObject);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "return c" + m_qstrClassName + ";\n";
   m_qstrSource += "}\n";
}

void CwmsCodeGeneratorC::GenerateCreateMethodHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static " + m_qstrClassName + " Create(CdmObjectContainer* p_pContainer);\n";
}

void CwmsCodeGeneratorC::GenerateCreateMethodSourceWithoutParameter()
{

   m_qstrSource += m_qstrClassName + " " + m_qstrClassName + "::Create()\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += m_qstrClassName + " c" + m_qstrClassName + ";\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = GetContainer;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(pContainer))\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CdmObject* pCdmObject = pContainer->CreateNewObject();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "c" + m_qstrClassName + ".SetObject(pCdmObject);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "return c" + m_qstrClassName + ";\n";
   m_qstrSource += "}\n";
}

void CwmsCodeGeneratorC::GenerateCreateMethodHeaderWithoutParameter()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static " + m_qstrClassName + " Create();\n";
}



void CwmsCodeGeneratorC::GenerateStandardObjectList()
{
   QString qstrObjListName = GenerateStandardObjectListKeyname();

   GenerateStandardObjectListSource(qstrObjListName);
   GenerateStandardObjectListHeader();
}

QString CwmsCodeGeneratorC::GenerateStandardObjectListKeyname()
{
   QString qstrObjListName = m_rpCdmClass->GetKeyname();
   qstrObjListName = qstrObjListName.remove("_");
   qstrObjListName = qstrObjListName.remove(" ");

   if (qstrObjListName.endsWith("s"))
   {
      qstrObjListName += "es";
   }
   else
   {
      qstrObjListName += "s";
   }
   
   return qstrObjListName;
}

void CwmsCodeGeneratorC::GenerateStandardObjectListSource(QString p_qstrObjListName)
{
   m_qstrSource += GenerateMethodHeadSource("CdmObjectContainer*", m_qstrClassName, "GetContainer", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "auto pCdmDataProvider = CdmSessionManager::GetDataProvider();\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(pCdmDataProvider))\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pContainer = pCdmDataProvider->GetObjectContainer(\"" + p_qstrObjListName + "\");\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (!pContainer) // create the container if does not exists\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "auto pCdmContainerManager = pCdmDataProvider->GetContainerManager();\n\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (CHKPTR(pCdmContainerManager))\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "QString qstrKeyname = \"" + p_qstrObjListName + "\";\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pCdmContainerManager->CreateContainer(\"" + m_rpCdmClass->GetKeyname() + "\", qstrKeyname, \"Standard\", \"\");\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pContainer = pCdmDataProvider->GetObjectContainer(\"" + p_qstrObjListName + "\");\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "return pContainer;\n";
   m_qstrSource += "}\n";
}

void CwmsCodeGeneratorC::GenerateStandardObjectListHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static CdmObjectContainer* GetContainer();\n";
}
