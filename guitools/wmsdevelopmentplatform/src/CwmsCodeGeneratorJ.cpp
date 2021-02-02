/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsCodeGeneratorJ.cpp
 ** Started Implementation: 2012/07/12
 ** Description:
 **
 ** Implements the generator for java
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QMap>

// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmMember.h"

// own Includes
#include "CwmsCodeGeneratorJ.h"


/** +-=---------------------------------------------------------Fr 13. Jul 10:33:52 2012----------*
 * @method  CwmsCodeGeneratorJ::CwmsCodeGeneratorJ           // public                            *
 * @return                                                   //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrPackage                            //                                   *
 * @param   QString p_qstrObjectListName                     //                                   *
 * @param   QString p_qstrStorePath                          //                                   *
 * @param   QString p_qstrBaseClassName                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:33:52 2012----------*/
CwmsCodeGeneratorJ::CwmsCodeGeneratorJ(CdmClass* p_pCdmClass,
                                       QString p_qstrClassName,
                                       QString p_qstrPackage,
                                       QString p_qstrObjectListName,
                                       QString p_qstrStorePath,
                                       QString p_qstrBaseClassName)
: m_rpCdmClass(p_pCdmClass),
  m_qstrClassName(p_qstrClassName),
  m_qstrPackage(p_qstrPackage),
  m_qstrObjectListKeyname(p_qstrObjectListName),
  m_qstrFilePath(p_qstrStorePath),
  m_qstrBaseClassName(p_qstrBaseClassName)
{

   // nothing to do here ;-)
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:40:35 2012----------*
 * @method  CwmsCodeGeneratorJ::~CwmsCodeGeneratorJ          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorJ                                            *
 *----------------last changed: --------------------------------Fr 13. Jul 09:40:35 2012----------*/
CwmsCodeGeneratorJ::~CwmsCodeGeneratorJ()
{
   // nothing to do here ;-)
}


/** +-=---------------------------------------------------------Fr 13. Jul 09:35:16 2012----------*
 * @method  CwmsCodeGeneratorJ::GenerateCode                 // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:35:16 2012----------*/
void CwmsCodeGeneratorJ::GenerateCode()
{
   if (!m_qstrClassName.isEmpty() && CHKPTR(m_rpCdmClass))
   {
      GenerateCodeP();
      SaveFiles();
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:36:35 2012----------*
 * @method  CwmsCodeGeneratorJ::GenerateCodeP                // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:36:35 2012----------*/
void CwmsCodeGeneratorJ::GenerateCodeP()
{
   SetPackage();
   // ToDo Add Import Packages

   AddImportPackage("java.util.Date");
   AddImportPackage("java.util.Set");
   AddImportPackage("java.lang.String");
   AddImportPackage("com.google.gwt.dev.util.collect.HashMap");
   AddImportPackage("com.google.gwt.json.client.*");

   if (!m_qstrBaseClassName.isEmpty())
   {
      AddImportPackage(m_qstrPackage + "." + m_qstrBaseClassName);
   }

   OpenClass();
   CreateClassMembers();
   CreateConstructors();
   CreateMemberMethods();
   CreateGetJSonMethod();
   CreateGetMemberMapMethod();
   CreateGetStringValueMethod();
   CreateGetIntValueMethod();
   CreateGetDoubleValueMethod();
   CreateGetBoolValueMethod();
   CreateGetFloatValueMethod();
   CreateSetStringValueMethod();
   CreateSetIntValueMethod();
   CreateSetDoubleValueMethod();
   CreateSetBoolValueMethod();
   CreateSetFloatValueMethod();
   CreateCommitMethod();
   CreateDeleteMethod();
   CloseClass();
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:06:41 2012----------*
 * @method  CwmsCodeGeneratorJ::SetPackage                   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:06:41 2012----------*/
void CwmsCodeGeneratorJ::SetPackage()
{
   m_qstrSource += "package " + m_qstrPackage + ";\n\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:05:31 2012----------*
 * @method  CwmsCodeGeneratorJ::AddImportPackage             // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPackage                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:05:31 2012----------*/
void CwmsCodeGeneratorJ::AddImportPackage(QString p_qstrPackage)
{
   m_qstrSource += "import " + p_qstrPackage + ";\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:08:07 2012----------*
 * @method  CwmsCodeGeneratorJ::OpenClass                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:08:07 2012----------*/
void CwmsCodeGeneratorJ::OpenClass()
{
   m_qstrSource += "\n\n";
   m_qstrSource += "public class " + m_qstrClassName;

   if (!m_qstrBaseClassName.isEmpty())
   {
      m_qstrSource += " extends " + m_qstrBaseClassName;
   }
      
   m_qstrSource += " {\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:11:04 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateClassMembers           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:11:04 2012----------*/
void CwmsCodeGeneratorJ::CreateClassMembers()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      GetClassMembers(m_rpCdmClass, !m_qstrBaseClassName.isEmpty(), qmMembers);

      QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            m_qstrSource += AddIndent(1);
            m_qstrSource += "private " + GetReturnType(pCdmMember->GetValueType());
            m_qstrSource += " " + GenerateCodeMemberName(pCdmMember->GetKeyname()) + " " + GetDefaultValue(pCdmMember->GetValueType()) + ";\n";

            if (pCdmMember->GetValueType() == eDmValueString)
            {
               m_qstrlStrings.append(pCdmMember->GetKeyname());
            }
            else if (pCdmMember->GetValueType() == eDmValueInt)
            {
               m_qstrlInts.append(pCdmMember->GetKeyname());
            }
            else if (pCdmMember->GetValueType() == eDmValueDouble)
            {
               m_qstrlDoubles.append(pCdmMember->GetKeyname());
            }
            else if (pCdmMember->GetValueType() == eDmValueBool)
            {
               m_qstrlBools.append(pCdmMember->GetKeyname());
            }
            else if (pCdmMember->GetValueType() == eDmValueFloat)
            {
               m_qstrlFloats.append(pCdmMember->GetKeyname());
            }
         }
      }

      m_qstrSource += AddIndent(1) + "private int objectId = 0;";
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:08:57 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateConstructors           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:08:57 2012----------*/
void CwmsCodeGeneratorJ::CreateConstructors()
{
   CreateDefaultConstructor();
   CreateJSonConstructor();
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:09:28 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateDefaultConstructor     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:09:28 2012----------*/
void CwmsCodeGeneratorJ::CreateDefaultConstructor()
{
   m_qstrSource += "\n\n";
   m_qstrSource += AddIndent(1) + "public " + m_qstrClassName + "() {\n";
   m_qstrSource += AddIndent(2) + "// Nothing to do here\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:09:36 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateJSonConstructor        // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:09:36 2012----------*/
void CwmsCodeGeneratorJ::CreateJSonConstructor()
{
   m_qstrSource += "\n\n";
   m_qstrSource += AddIndent(1) + "public " + m_qstrClassName + "(JSONObject object) {\n\n";
   
   QMap<long, CdmMember*> qmMembers;
   GetClassMembers(m_rpCdmClass, !m_qstrBaseClassName.isEmpty(),  qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (CHKPTR(pCdmMember))
      {
         CreateConstructorAssignment(pCdmMember);
      }
   }

   m_qstrSource += AddIndent(2) + "JSONNumber temp = (JSONNumber)object.get(\"ObjectId\");\n";
   m_qstrSource += AddIndent(2) + "objectId = (int)temp.doubleValue();\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Mo 23. Jul 16:43:34 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateListConstructorAssignment // private                        *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jul 16:43:34 2012----------*/
void CwmsCodeGeneratorJ::CreateListConstructorAssignment(QString p_qstrKeyname, EdmValueType p_eDmValue)
{
   m_qstrSource += AddIndent(3) + "int arraySize = temp.size();\n";
   m_qstrSource += AddIndent(3) + "for (int counter = 0; counter <arraySize, ++counter) {\n\n";

   switch(p_eDmValue)
   {
   case eDmValueListDouble:
      m_qstrSource += AddIndent(4) + "JSONNumber value = temp.get(counter);\n";
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".add(value.doubleValue());\n";
      break;
   case eDmValueListInt:
      m_qstrSource += AddIndent(4) + "JSONNumber value = temp.get(counter);\n";
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".add((int)value.doubleValue());\n";
      break;
   case eDmValueListObjects:
      m_qstrSource += AddIndent(4) + "JSONNumber value = temp.get(counter);\n";
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".add((int)value.doubleValue());\n";
      break;
   case eDmValueListString:
      m_qstrSource += AddIndent(4) + "JSONString value = temp.get(counter);\n";
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".add(value.stringValue());\n";
      break;
   default:
      m_qstrSource += AddIndent(4) + "// Codegenerator error unknown type\n";
      break;
   }

   m_qstrSource += AddIndent(3) + "}\n\n";
}

/** +-=---------------------------------------------------------Mo 23. Jul 12:02:13 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateDictionaryConstructorAssignment // private                  *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jul 12:02:13 2012----------*/
void CwmsCodeGeneratorJ::CreateDictionaryConstructorAssignment(QString p_qstrKeyname,
                                                               EdmValueType p_eDmValue)
{
   m_qstrSource += AddIndent(3) + "Set<String> objSet = temp.keySet();\n";
   m_qstrSource += AddIndent(3) + "Iterator it = objSet.iteraot();\n";
   m_qstrSource += AddIndent(3) + "while (it.hasNext()) {\n\n";

   switch(p_eDmValue)
   {
   case eDmValueDictIntInt:
   case eDmValueDictIntDouble:
   case eDmValueDictIntString:
      m_qstrSource += AddIndent(4) + "Integer key = (Integer) it.next();\n";
      break;
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
      m_qstrSource += AddIndent(4) + "String key = (String) it.next();\n";
      break;
   default:
      m_qstrSource += AddIndent(4) + "// ?????? Codegenerator error;\n";
      break;
   }

   if (p_eDmValue != eDmValueDictIntString && p_eDmValue != eDmValueDictStringString)
   {
      m_qstrSource += AddIndent(4) + "JSONNumber value = temp.get(key.toString());\n";
   }
   else
   {
      m_qstrSource += AddIndent(4) + "JSONString value = temp.get(key.toString());\n";
   }
  
   switch(p_eDmValue)
   {
   case eDmValueDictIntInt:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, (int)value.doubleValue());\n";
      break;
   case eDmValueDictIntDouble:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, value.doubleValue());\n";
      break;
   case eDmValueDictIntString:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, value.stringValue());\n";
      break;
   case eDmValueDictStringDouble:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, value.doubleValue());\n";
      break;
   case eDmValueDictStringInt:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, (int)value.doubleValue());\n";
      break;
   case eDmValueDictStringString:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(key, value.stringValue());\n";
      break;
   default:
      m_qstrSource += AddIndent(4) + GenerateCodeMemberName(p_qstrKeyname) + ".insert(/* Generator error */);\n";
      break;
   }

   m_qstrSource += AddIndent(3) + "}\n\n";
}

/** +-=---------------------------------------------------------Mi 18. Jul 13:36:17 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateConstructorAssignment  // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Jul 13:36:17 2012----------*/
void CwmsCodeGeneratorJ::CreateConstructorAssignment(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      EdmValueType eDmValue = p_pCdmMember->GetValueType();
      QString qstrKeyname = p_pCdmMember->GetKeyname();
      m_qstrSource += AddIndent(2) + "if (object.containsKey(\""+ qstrKeyname + "\") == true){\n\n";
      
      switch(eDmValue)
      {
      case eDmValueDictIntInt:
      case eDmValueDictIntDouble:
      case eDmValueDictIntString:
      case eDmValueDictStringDouble:
      case eDmValueDictStringInt:
      case eDmValueDictStringString:
         CreateDictionaryConstructorAssignment(qstrKeyname, eDmValue);
         break;
      case eDmValueListDouble:
      case eDmValueListInt:
      case eDmValueListObjects:
      case eDmValueListString:
         CreateListConstructorAssignment(qstrKeyname, eDmValue);
         break;
      default:
         m_qstrSource += AddIndent(3) + GetJsonType(eDmValue) + " temp = (" + GetJsonType(eDmValue) + ")object.get(\"" + qstrKeyname + "\");\n";
         m_qstrSource += AddIndent(3) + GenerateCodeMemberName(qstrKeyname) + " = (" + GetJsonCast(eDmValue) + ") temp." + GetJsonFunction(GetJsonType(eDmValue)) + "();\n";
         break;
      }
     
      m_qstrSource += AddIndent(2) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:10:37 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateMemberMethods          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:10:37 2012----------*/
void CwmsCodeGeneratorJ::CreateMemberMethods()
{
   QMap<long, CdmMember*> qmMembers;
   GetClassMembers(m_rpCdmClass, !m_qstrBaseClassName.isEmpty(),  qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (CHKPTR(pCdmMember))
      {
         CreateSetter(pCdmMember);
         CreateGetter(pCdmMember);
      }
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:12:07 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetter                 // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:12:07 2012----------*/
void CwmsCodeGeneratorJ::CreateSetter(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QString qstrKeyname = p_pCdmMember->GetKeyname();
      EdmValueType eDmValue = p_pCdmMember->GetValueType();

      m_qstrSource += AddIndent(2) + "public void set" + GenerateCodeMemberName(qstrKeyname) + "(" + GetParameter(eDmValue) + ") {\n\n";
      m_qstrSource += AddIndent(3) + GenerateCodeMemberName(qstrKeyname) + " = value;\n";
      m_qstrSource += AddIndent(2) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:12:30 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetter                 // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:12:30 2012----------*/
void CwmsCodeGeneratorJ::CreateGetter(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QString qstrKeyname = p_pCdmMember->GetKeyname();
      EdmValueType eDmValue = p_pCdmMember->GetValueType();

      m_qstrSource += AddIndent(2) + "public " + GetReturnType(eDmValue) + " get" + GenerateCodeMemberName(qstrKeyname) + "() {\n\n";
      m_qstrSource += AddIndent(3) + "return " + GenerateCodeMemberName(qstrKeyname) + ";\n";
      m_qstrSource += AddIndent(2) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:13:14 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetJSonMethod          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:13:14 2012----------*/
void CwmsCodeGeneratorJ::CreateGetJSonMethod()
{
   m_qstrSource += AddIndent(1) + "public JSONObject getJson() {\n\n";
   m_qstrSource += AddIndent(2) + "JSONObject obj = new JSONObject();\n";
   m_qstrSource += AddIndent(2) + "JSONNumber valObjectId = new JSONNumber(objectId);\n";
   m_qstrSource += AddIndent(2) + "obj.put(\"ObjectId\", valObjectId);\n";

   QMap<long, CdmMember*> qmMembers;
   GetClassMembers(m_rpCdmClass, !m_qstrBaseClassName.isEmpty(),  qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (CHKPTR(pCdmMember))
      {
         PutMemberToJsonObject(pCdmMember);
      }
   }

   m_qstrSource+= AddIndent(2) + "return obj;\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Mo 23. Jul 17:43:32 2012----------*
 * @method  CwmsCodeGeneratorJ::PutMemberToJsonObject        // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jul 17:43:32 2012----------*/
void CwmsCodeGeneratorJ::PutMemberToJsonObject(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QString qstrKeyname = p_pCdmMember->GetKeyname();
      EdmValueType eDmValue = p_pCdmMember->GetValueType();

      switch(eDmValue)
      {
      case eDmValueDictIntInt:
      case eDmValueDictIntDouble:
      case eDmValueDictIntString:
      case eDmValueDictStringDouble:
      case eDmValueDictStringInt:
      case eDmValueDictStringString:
         PutDictonaryMembersToJsonObject(qstrKeyname, eDmValue);
         break;
      case eDmValueListDouble:
      case eDmValueListInt:
      case eDmValueListObjects:
      case eDmValueListString:
         PutListMembersToJsonObject(qstrKeyname, eDmValue);
         break;
      default:
         m_qstrSource += AddIndent(2) + GetJsonType(eDmValue) + " val" + GenerateCodeMemberName(qstrKeyname) + " = new " + GetJsonType(eDmValue) + "(" + GenerateCodeMemberName(qstrKeyname) + ");\n";
         m_qstrSource += AddIndent(2) + "obj.put(\"" + GenerateCodeMemberName(qstrKeyname) + "\", val" + GenerateCodeMemberName(qstrKeyname) + ");\n";
         break;
      }
   }
}

/** +-=---------------------------------------------------------Di 24. Jul 11:17:00 2012----------*
 * @method  CwmsCodeGeneratorJ::PutDictonaryMembersToJsonObject // private                        *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 11:17:00 2012----------*/
void CwmsCodeGeneratorJ::PutDictonaryMembersToJsonObject(QString p_qstrKeyname, EdmValueType p_eDmValue)
{
   QString qstrObjName = "obj" + GenerateCodeMemberName(p_qstrKeyname);
   m_qstrSource += AddIndent(2) + "JSONObject " + qstrObjName + " = new JSONObject();\n";
   m_qstrSource += AddIndent(2) + "Iterator it = " + GenerateCodeMemberName(p_qstrKeyname) + ".iterator();\n";
   m_qstrSource += AddIndent(2) + "while(it.hasNext()) {\n\n";

   switch(p_eDmValue)
   {
   case eDmValueDictIntInt:
      m_qstrSource += AddIndent(3) + "Integer key = it.next();\n";
      m_qstrSource += AddIndent(3) + "Integer value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key.toString(), valNumber);\n";
      break;
   case eDmValueDictIntDouble:
      m_qstrSource += AddIndent(3) + "Integer key = it.next();\n";
      m_qstrSource += AddIndent(3) + "Double value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key.toString(), valNumber);\n";
      break;
   case eDmValueDictIntString:
      m_qstrSource += AddIndent(3) + "Integer key = it.next();\n";
      m_qstrSource += AddIndent(3) + "String value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONString valString = new JSONString(value);\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key.toString(), valString);\n";
      break;
   case eDmValueDictStringDouble:
      m_qstrSource += AddIndent(3) + "String key = it.next();\n";
      m_qstrSource += AddIndent(3) + "Double value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key, valNumber);\n";
      break;
   case eDmValueDictStringInt:
      m_qstrSource += AddIndent(3) + "String key = it.next();\n";
      m_qstrSource += AddIndent(3) + "Integer value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key, valNumber);\n";
      break;
   case eDmValueDictStringString:
      m_qstrSource += AddIndent(3) + "String key = it.next();\n";
      m_qstrSource += AddIndent(3) + "String value = " + GenerateCodeMemberName(p_qstrKeyname) + ".get(key);\n";
      m_qstrSource += AddIndent(3) + "JSONString valString = new JSONString(value);\n";
      m_qstrSource += AddIndent(3) + qstrObjName + ".put(key, valString);\n";
      break;
   default:
      m_qstrSource += AddIndent(3) + "// Error in Code Generator unknown dict type!\n";
      break;
   }

   m_qstrSource += AddIndent(2) + "}\n\n";
   m_qstrSource += AddIndent(2) + "obj.put(\"" + GenerateCodeMemberName(p_qstrKeyname) + "\", " + qstrObjName + ");\n";
}

/** +-=---------------------------------------------------------Di 24. Jul 11:17:16 2012----------*
 * @method  CwmsCodeGeneratorJ::PutListMembersToJsonObject   // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 11:17:16 2012----------*/
void CwmsCodeGeneratorJ::PutListMembersToJsonObject(QString p_qstrKeyname, EdmValueType p_eDmValue)
{
   QString qstrArrayName = "arr" + GenerateCodeMemberName(p_qstrKeyname);
   m_qstrSource += AddIndent(2) + "JSONArray " + qstrArrayName + " = new JSONArray();\n";
   m_qstrSource += AddIndent(2) + "Iterator it = " + GenerateCodeMemberName(p_qstrKeyname) + ".iterator();\n";
   m_qstrSource += AddIndent(2) + "int counter = 0;\n";
   m_qstrSource += AddIndent(2) + "while(it.hasNext()) {\n\n";

   switch(p_eDmValue)
   {
   case eDmValueListDouble:
      m_qstrSource += AddIndent(3) + "Double value = it.next();\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrArrayName + ".set(counter++, valNumber);\n";
      break;
   case eDmValueListInt:
   case eDmValueListObjects:
      m_qstrSource += AddIndent(3) + "Integer value = it.next();\n";
      m_qstrSource += AddIndent(3) + "JSONNumber valNumber = new JSONNumber(value.doubleValue());\n";
      m_qstrSource += AddIndent(3) + qstrArrayName + ".set(counter++, valNumber);\n";
      break;
   case eDmValueListString:
      m_qstrSource += AddIndent(3) + "String value = it.next();\n";
      m_qstrSource += AddIndent(3) + "JSONString valString = new JSONNumber(value);\n";
      m_qstrSource += AddIndent(3) + qstrArrayName + ".set(counter++, valString);\n";
      break;
   default:
      break;
   }

   m_qstrSource += AddIndent(2) + "}\n\n";
   m_qstrSource += AddIndent(2) + "obj.put(\"" + GenerateCodeMemberName(p_qstrKeyname) + "\", " + qstrArrayName + ");\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:15:11 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetMemberMapMethod     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:15:11 2012----------*/
void CwmsCodeGeneratorJ::CreateGetMemberMapMethod()
{
   m_qstrSource += AddIndent(1) + "public HashMap<String, Integer> getMemberMap() {\n\n";
   m_qstrSource += AddIndent(2) + "// Type definition from WMS used!\n";
   m_qstrSource += AddIndent(2) + "HashMap<String, Integer> map = new HashMap<String, Integer>();\n";
   QMap<long, CdmMember*> qmMembers;
   GetClassMembers(m_rpCdmClass, !m_qstrBaseClassName.isEmpty(),  qmMembers);

   QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
   QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmMember* pCdmMember = qmIt.value();

      if (CHKPTR(pCdmMember))
      {
         m_qstrSource += AddIndent(2) + "map.put(\"" + pCdmMember->GetKeyname() + "\", new Integer(" + QString::number(pCdmMember->GetValueType()) + "));\n";
      }
   }

   m_qstrSource += AddIndent(2) + "return map;\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Di 24. Jul 14:01:27 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetStringValueMethod   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:01:27 2012----------*/
void CwmsCodeGeneratorJ::CreateSetStringValueMethod()
{
   CreateSetValueMethod("String");
}

/** +-=---------------------------------------------------------Di 24. Jul 14:06:29 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetBoolValueMethod     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:06:29 2012----------*/
void CwmsCodeGeneratorJ::CreateSetBoolValueMethod()
{
   CreateSetValueMethod("boolean");
}

/** +-=---------------------------------------------------------Di 24. Jul 14:06:47 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetDoubleValueMethod   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:06:47 2012----------*/
void CwmsCodeGeneratorJ::CreateSetDoubleValueMethod()
{

   CreateSetValueMethod("double");
}

/** +-=---------------------------------------------------------Di 24. Jul 14:07:39 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetFloatValueMethod    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:07:39 2012----------*/
void CwmsCodeGeneratorJ::CreateSetFloatValueMethod()
{
   CreateSetValueMethod("float");
}

/** +-=---------------------------------------------------------Di 24. Jul 14:07:55 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetIntValueMethod      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:07:55 2012----------*/
void CwmsCodeGeneratorJ::CreateSetIntValueMethod()
{
   CreateSetValueMethod("int");
}

/** +-=---------------------------------------------------------Di 24. Jul 14:02:54 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateSetValueMethod         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrType                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 14:02:54 2012----------*/
void CwmsCodeGeneratorJ::CreateSetValueMethod(QString p_qstrType)
{
   QStringList qstrlCurrent;
   
   if (p_qstrType == "String")
   {
      qstrlCurrent = m_qstrlStrings;
   }  
   else if (p_qstrType == "double")
   {
      qstrlCurrent = m_qstrlDoubles;
   } 
   else if (p_qstrType == "int")
   {
      qstrlCurrent = m_qstrlInts;
   } 
   else if (p_qstrType == "float")
   {
      qstrlCurrent = m_qstrlFloats;
   }
   else if (p_qstrType == "boolean")
   {
      qstrlCurrent = m_qstrlBools;
   }

   if (qstrlCurrent.count() > 0)
   {
      m_qstrSource += AddIndent(1) + "public void setValue(String keyname, " + p_qstrType + " value) {\n\n";

      for (int iCounter = 0; iCounter < qstrlCurrent.size(); ++iCounter)
      {
         QString qstrKeyname = qstrlCurrent[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "set" + GenerateCodeMemberName(qstrKeyname) + "(value);\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}


/** +-=---------------------------------------------------------Di 24. Jul 13:24:45 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetStringValueMethod   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 13:24:45 2012----------*/
void CwmsCodeGeneratorJ::CreateGetStringValueMethod()
{
   if (m_qstrlStrings.count() > 0)
   {
      m_qstrSource += AddIndent(1) + "public String getStringValue(String keyname) {\n\n";
      m_qstrSource += AddIndent(2) + "String ret = \"\";\n";

      for (int iCounter = 0; iCounter < m_qstrlStrings.size(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlStrings[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "ret = get" + GenerateCodeMemberName(qstrKeyname) + "();\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(2) + "return ret;\n";
      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Di 24. Jul 13:24:53 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetIntValueMethod      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 13:24:53 2012----------*/
void CwmsCodeGeneratorJ::CreateGetIntValueMethod()
{
   if (m_qstrlInts.size() > 0)
   {
      m_qstrSource += AddIndent(1) + "public int getIntValue(String keyname) {\n\n";
      m_qstrSource += AddIndent(2) + "int ret = 0;\n";

      for (int iCounter = 0; iCounter < m_qstrlInts.size(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlInts[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "ret = get" + GenerateCodeMemberName(qstrKeyname) + "();\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(2) + "return ret;\n";
      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Di 24. Jul 13:25:18 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetDoubleValueMethod   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 13:25:18 2012----------*/
void CwmsCodeGeneratorJ::CreateGetDoubleValueMethod()
{
   if (m_qstrlDoubles.size() > 0)
   {
      m_qstrSource += AddIndent(1) + "public double getDoubleValue(String keyname) {\n\n";
      m_qstrSource += AddIndent(2) + "double ret = 0;\n";

      for (int iCounter = 0; iCounter < m_qstrlDoubles.size(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlDoubles[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "ret = get" + GenerateCodeMemberName(qstrKeyname) + "();\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(2) + "return ret;\n";
      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Di 24. Jul 13:26:37 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetBoolValueMethod     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 13:26:37 2012----------*/
void CwmsCodeGeneratorJ::CreateGetBoolValueMethod()
{
   if (m_qstrlBools.size() > 0)
   {
      m_qstrSource += AddIndent(1) + "public boolean getDoubleValue(String keyname) {\n\n";
      m_qstrSource += AddIndent(2) + "boolean ret = false;\n";

      for (int iCounter = 0; iCounter < m_qstrlBools.size(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlBools[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "ret = get" + GenerateCodeMemberName(qstrKeyname) + "();\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(2) + "return ret;\n";
      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Di 24. Jul 13:52:03 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateGetFloatValueMethod    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 13:52:03 2012----------*/
void CwmsCodeGeneratorJ::CreateGetFloatValueMethod()
{
   if (m_qstrlFloats.size() > 0)
   {
      m_qstrSource += AddIndent(1) + "public float getFloatValue(String keyname) {\n\n";
      m_qstrSource += AddIndent(2) + "float ret = 0;\n";

      for (int iCounter = 0; iCounter < m_qstrlFloats.size(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlFloats[iCounter];

         m_qstrSource += AddIndent(2) + "if (keyname.compareTo(\"" + qstrKeyname + "\") == 0) {\n\n";
         m_qstrSource += AddIndent(3) + "ret = get" + GenerateCodeMemberName(qstrKeyname) + "();\n";
         m_qstrSource += AddIndent(2) + "}\n\n";
      }

      m_qstrSource += AddIndent(2) + "return ret;\n";
      m_qstrSource += AddIndent(1) + "}\n\n";
   }
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:15:33 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateCommitMethod           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:15:33 2012----------*/
void CwmsCodeGeneratorJ::CreateCommitMethod()
{
   m_qstrSource += AddIndent(1) + "public static boolean commit() {\n\n";
   m_qstrSource += AddIndent(2) + "// Not yet implemented in code generator!\n";
   m_qstrSource += AddIndent(2) + "return false;\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:15:43 2012----------*
 * @method  CwmsCodeGeneratorJ::CreateDeleteMethod           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:15:43 2012----------*/
void CwmsCodeGeneratorJ::CreateDeleteMethod()
{
   m_qstrSource += AddIndent(1) + "public static boolean delete() {\n\n";
   m_qstrSource += AddIndent(2) + "// Not yet implemented in code generator!\n";
   m_qstrSource += AddIndent(2) + "return false;\n";
   m_qstrSource += AddIndent(1) + "}\n\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 10:31:08 2012----------*
 * @method  CwmsCodeGeneratorJ::CloseClass                   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 10:31:08 2012----------*/
void CwmsCodeGeneratorJ::CloseClass()
{
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:46:13 2012----------*
 * @method  CwmsCodeGeneratorJ::SaveFiles                    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:46:13 2012----------*/
void CwmsCodeGeneratorJ::SaveFiles()
{
   QString qstrFilename = m_qstrFilePath + "/" + m_qstrClassName + ".java";
   SaveFile(qstrFilename, m_qstrSource);
}

/** +-=---------------------------------------------------------Fr 13. Jul 14:18:05 2012----------*
 * @method  CwmsCodeGeneratorJ::GetParameter                 // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 14:18:05 2012----------*/
QString CwmsCodeGeneratorJ::GetParameter(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "String value";
      break;
   case eDmValueBool:
      qstrRet = "boolean value";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "String value";
      break;
   case eDmValueCounter:
      qstrRet = "int value";
      break;
   case eDmValueDate:
      qstrRet = "Date value";
      break;
   case eDmValueDateTime:
      qstrRet = "Timestamp value";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "int p_iKey, double p_dValue";
      break;
   case eDmValueDictIntInt:
      qstrRet = "int p_iKey, int p_iValue";
      break;
   case eDmValueDictIntString:
      qstrRet = "int p_iKey, String p_qstrValue";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "String p_qstrKey, double p_dValue";
      break;
   case eDmValueDictStringInt:
      qstrRet = "String p_qstrKey, int p_iValue";
      break;
   case eDmValueDictStringString:
      qstrRet = "String p_qstrKey, String p_qstrValue";
      break;
   case eDmValueDouble:
      qstrRet = "double value";
      break;
   case eDmValueFloat:
      qstrRet = "float value";
      break;
   case eDmValueFormula:
      qstrRet = "NO CODE";
      break;
   case eDmValueInt:
      qstrRet = "int value";
      break;
   case eDmValueListDouble:
      qstrRet = "double value";
      break;
   case eDmValueListInt:
      qstrRet = "int value";
      break;
   case eDmValueListObjects:
      qstrRet = "int value";
      break;
   case eDmValueListString:
      qstrRet = "String value";
      break;
   case eDmValueLong:
      qstrRet = "int value";
      break;
   case eDmValueContainerRef:
      qstrRet = "int value";
      break;
   case eDmValueObjectRef:
      qstrRet = "int value";
      break;
   case eDmValueString:
      qstrRet = "String value";
      break;
   case eDmValueTime:
      qstrRet = "Time value";
      break;
   case eDmValueUser:
      qstrRet = "int value";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Fr 13. Jul 14:17:54 2012----------*
 * @method  CwmsCodeGeneratorJ::GetReturnType                // protected                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 14:17:54 2012----------*/
QString CwmsCodeGeneratorJ::GetReturnType(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "String"; // Filename
      break;
   case eDmValueBool:
      qstrRet = "boolean";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "String";
      break;
   case eDmValueCounter:
      qstrRet = "int";
      break;
   case eDmValueDate:
      qstrRet = "Date";
      break;
   case eDmValueDateTime:
      qstrRet = "Timestamp";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "HashMap<int, double>";
      break;
   case eDmValueDictIntInt:
      qstrRet = "HashMap<int, int>";
      break;
   case eDmValueDictIntString:
      qstrRet = "HashMap<int, String>";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "HashMap<String, double>";
      break;
   case eDmValueDictStringInt:
      qstrRet = "HashMap<String, int>";
      break;
   case eDmValueDictStringString:
      qstrRet = "HashMap<String, String>";
      break;
   case eDmValueDouble:
      qstrRet = "double";
      break;
   case eDmValueFloat:
      qstrRet = "float";
      break;
   case eDmValueFormula:
      qstrRet = "String";// Display string
      break;
   case eDmValueInt:
      qstrRet = "int";
      break;
   case eDmValueListDouble:
      qstrRet = "List<double>";
      break;
   case eDmValueListInt:
      qstrRet = "List<int>";
      break;
   case eDmValueListObjects:
      qstrRet = "List<int>";
      break;
   case eDmValueListString:
      qstrRet = "List<String>";
      break;
   case eDmValueLong:
      qstrRet = "long";
      break;
   case eDmValueContainerRef:
      qstrRet = "int";
      break;
   case eDmValueObjectRef:
      qstrRet = "int";
      break;
   case eDmValueString:
      qstrRet = "String";
      break;
   case eDmValueTime:
      qstrRet = "Time";
      break;
   case eDmValueUser:
      qstrRet = "int";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 24. Jul 15:40:10 2012----------*
 * @method  CwmsCodeGeneratorJ::GetDefaultValue              // protected                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 24. Jul 15:40:10 2012----------*/
QString CwmsCodeGeneratorJ::GetDefaultValue(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = " = \"\""; // Filename
      break;
   case eDmValueBool:
      qstrRet = " = false";
      break;
   case eDmValueCharacterDocument:
      qstrRet = " = \"\"";
      break;
   case eDmValueCounter:
      qstrRet = " = 0";
      break;
   case eDmValueDate:
      qstrRet = " = new Date()";
      break;
   case eDmValueDateTime:
      qstrRet = " = new Timestamp";
      break;
   case eDmValueDictIntDouble:
      qstrRet = " = new HashMap<int, double>()";
      break;
   case eDmValueDictIntInt:
      qstrRet = " = new HashMap<int, int>()";
      break;
   case eDmValueDictIntString:
      qstrRet = " = new HashMap<int, String>()";
      break;
   case eDmValueDictStringDouble:
      qstrRet = " = new HashMap<String, double>()";
      break;
   case eDmValueDictStringInt:
      qstrRet = " = new HashMap<String, int>()";
      break;
   case eDmValueDictStringString:
      qstrRet = " = new HashMap<String, String>()";
      break;
   case eDmValueDouble:
      qstrRet = " = 0";
      break;
   case eDmValueFloat:
      qstrRet = " = 0";
      break;
   case eDmValueFormula:
      qstrRet = " = \"\"";// Display string
      break;
   case eDmValueInt:
      qstrRet = "= 0";
      break;
   case eDmValueListDouble:
      qstrRet = " = new List<double>";
      break;
   case eDmValueListInt:
      qstrRet = " = new List<int>";
      break;
   case eDmValueListObjects:
      qstrRet = " = new List<int>";
      break;
   case eDmValueListString:
      qstrRet = " = new List<String>";
      break;
   case eDmValueLong:
      qstrRet = " = 0";
      break;
   case eDmValueContainerRef:
      qstrRet = " = 0";
      break;
   case eDmValueObjectRef:
      qstrRet = " = 0";
      break;
   case eDmValueString:
      qstrRet = " = \"\"";
      break;
   case eDmValueTime:
      qstrRet = " = new Time()";
      break;
   case eDmValueUser:
      qstrRet = " = 0";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------Mo 16. Jul 10:50:07 2012----------*
 * @method  CwmsCodeGeneratorJ::GetJsonType                  // protected                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Jul 10:50:07 2012----------*/
QString CwmsCodeGeneratorJ::GetJsonType(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "JSONString"; // Filename
      break;
   case eDmValueBool:
      qstrRet = "JSONBoolean";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "JSONString";
      break;
   case eDmValueCounter:
      qstrRet = "JSONNumber";
      break;
   case eDmValueDate:
      qstrRet = "JSONString";
      break;
   case eDmValueDateTime:
      qstrRet = "JSONString";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictIntInt:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictIntString:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringInt:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringString:
      qstrRet = "JSONObject";
      break;
   case eDmValueDouble:
      qstrRet = "JSONNumber";
      break;
   case eDmValueFloat:
      qstrRet = "JSONNumber";
      break;
   case eDmValueFormula:
      qstrRet = "JSONString";// Display string
      break;
   case eDmValueInt:
      qstrRet = "JSONNumber";
      break;
   case eDmValueListDouble:
      qstrRet = "JSONArray";
      break;
   case eDmValueListInt:
      qstrRet = "JSONArray";
      break;
   case eDmValueListObjects:
      qstrRet = "JSONArray";
      break;
   case eDmValueListString:
      qstrRet = "JSONArray";
      break;
   case eDmValueLong:
      qstrRet = "JSONNumber";
      break;
   case eDmValueContainerRef:
      qstrRet = "JSONNumber";
      break;
   case eDmValueObjectRef:
      qstrRet = "JSONNumber";
      break;
   case eDmValueString:
      qstrRet = "JSONString";
      break;
   case eDmValueTime:
      qstrRet = "JSONString";
      break;
   case eDmValueUser:
      qstrRet = "JSONNumber";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------Mi 18. Jul 08:39:54 2012----------*
 * @method  CwmsCodeGeneratorJ::GetJsonCast                  // public                            *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Jul 08:39:54 2012----------*/
QString CwmsCodeGeneratorJ::GetJsonCast(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "String"; // Filename
      break;
   case eDmValueBool:
      qstrRet = "boolean";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "String";
      break;
   case eDmValueCounter:
      qstrRet = "int";
      break;
   case eDmValueDate:
      qstrRet = "String";
      break;
   case eDmValueDateTime:
      qstrRet = "String";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictIntInt:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictIntString:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringInt:
      qstrRet = "JSONObject";
      break;
   case eDmValueDictStringString:
      qstrRet = "JSONObject";
      break;
   case eDmValueDouble:
      qstrRet = "double";
      break;
   case eDmValueFloat:
      qstrRet = "float";
      break;
   case eDmValueFormula:
      qstrRet = "String";// Display string
      break;
   case eDmValueInt:
      qstrRet = "int";
      break;
   case eDmValueListDouble:
      qstrRet = "JSONArray";
      break;
   case eDmValueListInt:
      qstrRet = "JSONArray";
      break;
   case eDmValueListObjects:
      qstrRet = "JSONArray";
      break;
   case eDmValueListString:
      qstrRet = "JSONArray";
      break;
   case eDmValueLong:
      qstrRet = "int";
      break;
   case eDmValueContainerRef:
      qstrRet = "int";
      break;
   case eDmValueObjectRef:
      qstrRet = "int";
      break;
   case eDmValueString:
      qstrRet = "String";
      break;
   case eDmValueTime:
      qstrRet = "String";
      break;
   case eDmValueUser:
      qstrRet = "int";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Mi 18. Jul 08:40:02 2012----------*
 * @method  CwmsCodeGeneratorJ::GetJsonFunction              // public                            *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrJsonType                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Jul 08:40:02 2012----------*/
QString CwmsCodeGeneratorJ::GetJsonFunction(QString p_qstrJsonType)
{
   QString qstrRet;

   if (p_qstrJsonType == "JSONNumber")
   {
      qstrRet = "doubleValue";
   }
   else if (p_qstrJsonType == "JSONString")
   {
      qstrRet = "stringValue";
   }
   else if (p_qstrJsonType == "JSONBoolean")
   {
      qstrRet = "booleanValue";
   }
   else if (p_qstrJsonType == "JSONObject")
   {
      qstrRet = "isObject";
   }
   else if (p_qstrJsonType == "JSONArray")
   {
      qstrRet = "isArray";
   }
   else
   {
      qstrRet = "Unknown";
   }

   return qstrRet;
}
