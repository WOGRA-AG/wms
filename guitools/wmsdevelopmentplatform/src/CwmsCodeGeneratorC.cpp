/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsCodeGeneratorC.cpp
 ** Started Implementation: 2011/11/09
 ** Description:
 **
 ** This class generates c++ interface code for classes.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

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


/** +-=---------------------------------------------------------Mo 21. Nov 15:14:00 2011----------*
 * @method  CwmsCodeGeneratorC::CwmsCodeGeneratorC           // public                            *
 * @return                                                   //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:14:00 2011----------*/
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

/** +-=---------------------------------------------------------Mi 9. Nov 14:35:38 2011-----------*
 * @method  CwmsCodeGeneratorC::~CwmsCodeGeneratorC          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorC                                            *
 *----------------last changed: --------------------------------Mi 9. Nov 14:35:38 2011-----------*/
CwmsCodeGeneratorC::~CwmsCodeGeneratorC()
{
   
}

/** +-=---------------------------------------------------------Fr 2. Dez 15:47:35 2011-----------*
 * @method  CwmsCodeGeneratorC::SetGenerateTestCode          // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bGenerate                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 2. Dez 15:47:35 2011-----------*/
void CwmsCodeGeneratorC::SetGenerateTestCode(bool p_bGenerate)
{
   m_bGenerateTestCode = p_bGenerate;
}

/** +-=---------------------------------------------------------Mi 6. Jun 10:40:21 2012-----------*
 * @method  CwmsCodeGeneratorC::SetGenerateBusinessLogicCode // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bGenerate                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 10:40:21 2012-----------*/
void CwmsCodeGeneratorC::SetGenerateBusinessLogicCode(bool p_bGenerate)
{
   m_bGenerateBusinessLogicClass = p_bGenerate;
}

/** +-=---------------------------------------------------------Mi 6. Jun 10:42:40 2012-----------*
 * @method  CwmsCodeGeneratorC::SetGenerateTempClassCode     // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bGenerate                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 10:42:40 2012-----------*/
void CwmsCodeGeneratorC::SetGenerateTempClassCode(bool p_bGenerate)
{
   m_bGenerateTempClass = p_bGenerate;
}

/** +-=---------------------------------------------------------Mi 6. Jun 10:43:12 2012-----------*
 * @method  CwmsCodeGeneratorC::SetGenerateWebInterfaceCode  // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bGenerate                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 10:43:12 2012-----------*/
void CwmsCodeGeneratorC::SetGenerateWebInterfaceCode(bool p_bGenerate)
{
   m_bGenerateWebInterface = p_bGenerate;
}

/** +-=---------------------------------------------------------Fr 8. Jun 10:20:24 2012-----------*
 * @method  CwmsCodeGeneratorC::SetWebInterfaceClassName     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 10:20:24 2012-----------*/
void CwmsCodeGeneratorC::SetWebInterfaceClassName(QString p_qstrClassName)
{
   m_qstrWebInterfaceClassName = p_qstrClassName;
}

/** +-=---------------------------------------------------------Fr 8. Jun 10:20:47 2012-----------*
 * @method  CwmsCodeGeneratorC::SetWebInterfaceObjectListName // public                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrOLName                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 10:20:47 2012-----------*/
void CwmsCodeGeneratorC::SetWebInterfaceObjectListName(QString p_qstrOLName)
{
   m_qstrWebInterfaceOLKeyname = p_qstrOLName;
}

/** +-=---------------------------------------------------------Mi 9. Nov 19:17:25 2011-----------*
 * @method  CwmsCodeGeneratorC::SetCreateBaseClassMemberFunctions // public                       *
 * @return  void                                             //                                   *
 * @param   bool p_bCreate                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 19:17:25 2011-----------*/
void CwmsCodeGeneratorC::SetCreateBaseClassMemberFunctions(bool p_bCreate)
{
   if (!m_rpCdmClass->IsAbstract())
   {
      m_bCreateBaseClassMemberFunctions = p_bCreate;
   }
}

/** +-=---------------------------------------------------------Fr 18. Nov 15:30:30 2011----------*
 * @method  CwmsCodeGeneratorC::SetGenerateStandardObjectList // public                           *
 * @return  void                                             //                                   *
 * @param   bool p_bStandard                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 18. Nov 15:30:30 2011----------*/
void CwmsCodeGeneratorC::SetGenerateStandardObjectList(bool p_bStandard)
{
   m_bGenerateStandardObjectList = p_bStandard;
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:15:07 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateCode                 // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:15:07 2011----------*/
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


/** +-=---------------------------------------------------------Mo 21. Nov 15:15:45 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateCodeP                // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:15:45 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:16:19 2011----------*
 * @method  CwmsCodeGeneratorC::GeneratesConstructors        // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:16:19 2011----------*/
void CwmsCodeGeneratorC::GeneratesConstructors()
{
   GenerateDefaultConstructorSource();
   GenerateParameterConstructorSource();
   GenerateDefaultConstructorHeader();
   GenerateParameterConstructorHeader();
}

/** +-=---------------------------------------------------------Mi 9. Nov 15:16:17 2011-----------*
 * @method  CwmsCodeGeneratorC::GenerateMethodInHeader       // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   EwmsCodeGenerationMethodType p_eType             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 15:16:17 2011-----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:16:46 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateMethodInSource       // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   EwmsCodeGenerationMethodType p_eType             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:16:46 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:17:04 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateSetterSource         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:17:04 2011----------*/
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

/** +-=---------------------------------------------------------Mi 9. Nov 17:43:54 2011-----------*
 * @method  CwmsCodeGeneratorC::GenerateSetterCode           // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 17:43:54 2011-----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:17:44 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateGetterSource         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:17:44 2011----------*/
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

/** +-=---------------------------------------------------------Mi 9. Nov 16:56:21 2011-----------*
 * @method  CwmsCodeGeneratorC::GenerateGetterCode           // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 16:56:21 2011-----------*/
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


/** +-=---------------------------------------------------------Mi 9. Nov 16:33:12 2011-----------*
 * @method  CwmsCodeGeneratorC::GenerateSetterHeader         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 16:33:12 2011-----------*/
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

/** +-=---------------------------------------------------------Mi 9. Nov 16:33:17 2011-----------*
 * @method  CwmsCodeGeneratorC::GenerateGetterHeader         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 16:33:17 2011-----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:18:34 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDestructorHeader     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:18:34 2011----------*/
void CwmsCodeGeneratorC::GenerateDestructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "virtual ~" + m_qstrClassName + "();\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:18:47 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDestructorSource     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:18:47 2011----------*/
void CwmsCodeGeneratorC::GenerateDestructorSource()
{
   m_qstrSource += m_qstrClassName + "::~" + m_qstrClassName + "()\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:19:01 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDefaultConstructorSource // private                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:19:01 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:19:24 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDefaultConstructorHeader // private                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:19:24 2011----------*/
void CwmsCodeGeneratorC::GenerateDefaultConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "();\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:19:37 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateParameterConstructorSource // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:19:37 2011----------*/
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

/** +-=---------------------------------------------------------Di 22. Nov 18:53:46 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateParameterConstructorHeader // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *--------.힐Ȯ-----last changed: --------------------------------Di 22. Nov 18:53:46 2011----------*/
void CwmsCodeGeneratorC::GenerateParameterConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "(CdmObject* p_pCdmObject);\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:20:10 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDestructors          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:20:10 2011----------*/
void CwmsCodeGeneratorC::GenerateDestructors()
{
   GenerateDestructorSource();
   GenerateDestructorHeader();
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:20:24 2011----------*
 * @method  CwmsCodeGeneratorC::GeneratesMemberAccess        // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:20:24 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:20:41 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateClassMembersAccess   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:20:41 2011----------*/
void CwmsCodeGeneratorC::GenerateClassMembersAccess()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      m_rpCdmClass->GetClassMemberMap(qmMembers);
      QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateMemberAccess(qmIt.value());
      }
   }
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:21:06 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateAllMembersAccess     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:21:06 2011----------*/
void CwmsCodeGeneratorC::GenerateAllMembersAccess()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      m_rpCdmClass->GetMemberMap(qmMembers);
      QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateMemberAccess(qmIt.value());
      }
   }
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:21:23 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateMemberAccess         // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:21:23 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:22:38 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateCreateMethod         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:22:38 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:22:50 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDeleteMethod         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:22:50 2011----------*/
void CwmsCodeGeneratorC::GenerateDeleteMethod()
{
   GenerateDeleteMethodSource();
   GenerateDeleteMethodHeader();
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:23:16 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDeleteMethodSource   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:23:16 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:23:44 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateDeleteMethodHeader   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:23:44 2011----------*/
void CwmsCodeGeneratorC::GenerateDeleteMethodHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static bool Delete(" + m_qstrClassName + " c" + m_qstrClassName + ");\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:24:03 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateCreateMethodSource   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:24:03 2011----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:24:33 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateCreateMethodHeader   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:24:33 2011----------*/
void CwmsCodeGeneratorC::GenerateCreateMethodHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static " + m_qstrClassName + " Create(CdmObjectContainer* p_pContainer);\n";
}

/** +-=---------------------------------------------------------Fr 8. Jun 16:51:54 2012-----------*
 * @method  CwmsCodeGeneratorC::GenerateCreateMethodSourceWithoutParameter // private             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 16:51:54 2012-----------*/
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

/** +-=---------------------------------------------------------Fr 8. Jun 16:52:11 2012-----------*
 * @method  CwmsCodeGeneratorC::GenerateCreateMethodHeaderWithoutParameter // private             *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 16:52:11 2012-----------*/
void CwmsCodeGeneratorC::GenerateCreateMethodHeaderWithoutParameter()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static " + m_qstrClassName + " Create();\n";
}



/** +-=---------------------------------------------------------Mo 21. Nov 15:24:55 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateStandardObjectList   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:24:55 2011----------*/
void CwmsCodeGeneratorC::GenerateStandardObjectList()
{
   QString qstrObjListName = GenerateStandardObjectListKeyname();

   GenerateStandardObjectListSource(qstrObjListName);
   GenerateStandardObjectListHeader();
}

/** +-=---------------------------------------------------------Fr 8. Jun 10:18:09 2012-----------*
 * @method  CwmsCodeGeneratorC::GenerateStandardObjectListKeyname // private                      *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 10:18:09 2012-----------*/
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

/** +-=---------------------------------------------------------Mo 21. Nov 15:25:24 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateStandardObjectListSource // private                       *
 * @return  void                                             //                                   *
 * @param   QString p_qstrObjListName                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:25:24 2011----------*/
void CwmsCodeGeneratorC::GenerateStandardObjectListSource(QString p_qstrObjListName)
{
   m_qstrSource += GenerateMethodHeadSource("CdmObjectContainer*", m_qstrClassName, "GetContainer", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmManager* pCdmManager = CdmSessionManager::GetManager();\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(pCdmManager))\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pContainer = pCdmManager->GetContainer(\"" + p_qstrObjListName + "\");\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (!pContainer) // create the container if does not exists\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CdmContainerManager* pCdmOLManager = pCdmManager->GetContainerManager(pCdmManager->GetCurrentDatabase());\n\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (CHKPTR(pCdmOLManager))\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "QString qstrKeyname = \"" + p_qstrObjListName + "\";\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pCdmOLManager->CreateContainer(\"" + m_rpCdmClass->GetKeyname() + "\", qstrKeyname, \"Standard\", \"\");\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pContainer = pCdmManager->GetContainer(\"" + p_qstrObjListName + "\");\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "return pContainer;\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:25:52 2011----------*
 * @method  CwmsCodeGeneratorC::GenerateStandardObjectListHeader // private                       *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:25:52 2011----------*/
void CwmsCodeGeneratorC::GenerateStandardObjectListHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "static CdmObjectContainer* GetContainer();\n";
}
