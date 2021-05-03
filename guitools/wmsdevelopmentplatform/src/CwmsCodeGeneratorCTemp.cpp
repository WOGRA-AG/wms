/******************************************************************************
** WOGRA technologies GmbH & Co. KG Modul Information
** Modulename: CwmsCodeGeneratorC.cpp
** Started Implementation: 2011/11/09
** Description:
**
** Generates the code for a temporary class for doing validations
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
#include "CwmsCodeGeneratorCTemp.h"


/** +-=---------------------------------------------------------Mi 6. Jun 17:37:54 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::CwmsCodeGeneratorCTemp   // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrClassNameTwin                      //                                   *
 * @param   QString p_qstrBaseClassName                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:37:54 2012-----------*/
CwmsCodeGeneratorCTemp::CwmsCodeGeneratorCTemp(CdmClass* p_pCdmClass,
                                               QString p_qstrClassName,
                                               QString p_qstrFilename,
                                               QString p_qstrClassNameTwin,
                                               QString p_qstrBaseClassName)
   : CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassName),
  m_rpCdmClass(p_pCdmClass),
  m_bCreateBaseClassMemberFunctions(false),
  m_qstrClassNameTwin(p_qstrClassNameTwin),
  m_qstrBaseClassName(p_qstrBaseClassName)
{
   if (m_qstrBaseClassName.length() > 0)
   {
      AddBaseClassData(m_qstrBaseClassName, m_qstrBaseClassName + ".h");
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 16:27:37 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::~CwmsCodeGeneratorCTemp  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorC                                            *
 *----------------last changed: --------------------------------Mi 6. Jun 16:27:37 2012-----------*/
CwmsCodeGeneratorCTemp::~CwmsCodeGeneratorCTemp()
{

}


/** +-=---------------------------------------------------------Mi 6. Jun 15:36:53 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::SetCreateBaseClassMemberFunctions // public                   *
 * @return  void                                             //                                   *
 * @param   bool p_bCreate                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:53 2012-----------*/
void CwmsCodeGeneratorCTemp::SetCreateBaseClassMemberFunctions(bool p_bCreate)
{
   if (!m_rpCdmClass->IsAbstract())
   {
      m_bCreateBaseClassMemberFunctions = p_bCreate;
   }
}



/** +-=---------------------------------------------------------Mi 6. Jun 15:36:43 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCode             // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:43 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      GenerateCodeP();
      SaveFiles();
   }
}


/** +-=---------------------------------------------------------Mi 6. Jun 15:36:39 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCodeP            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:39 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCodeP()
{

   if (CHKPTR(m_rpCdmClass))
   {
      OpenClass();
      GenerateSourceHeader();
      GeneratesConstructors();
      GenerateDestructors();
      GeneratesMemberAccess();
      GenerateCopyConstructor();
      AddMembersToHeader();

      CloseClass();
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 17:36:33 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructor  // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:36:33 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructor()
{
   GenerateCopyConstructorSource();
   GenerateCopyConstructorHeader();
}


/** +-=---------------------------------------------------------Mi 6. Jun 15:36:34 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GeneratesConstructors    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:34 2012-----------*/
void CwmsCodeGeneratorCTemp::GeneratesConstructors()
{
   GenerateDefaultConstructorSource();
   GenerateParameterConstructorSource();
   GenerateDefaultConstructorHeader();
   GenerateParameterConstructorHeader();
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:36:25 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateMethodInHeader   // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   EwmsCodeGenerationMethodType p_eType             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:25 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateMethodInHeader(QString p_qstrMethodName,
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

/** +-=---------------------------------------------------------Mi 6. Jun 15:36:12 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateMethodInSource   // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   EwmsCodeGenerationMethodType p_eType             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:12 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateMethodInSource(QString p_qstrMethodName,
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

/** +-=---------------------------------------------------------Mi 6. Jun 15:36:06 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateSetterSource     // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:06 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateSetterSource(QString p_qstrMember, EdmValueType p_eReturnValue)
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

/** +-=---------------------------------------------------------Mi 6. Jun 15:36:00 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::CheckSetterMethod        // private                           *
 * @return  bool                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:36:00 2012-----------*/
bool CwmsCodeGeneratorCTemp::CheckSetterMethod(EdmValueType p_eDmValue)
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
   case eDmValueInt:
   case eDmValueLong:
   case eDmValueContainerRef:
   case eDmValueObjectRef:
   case eDmValueString:
   case eDmValueTime:
   case eDmValueUser:
      bRet = true;
      break;

   case eDmValueDictIntDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
   case eDmValueListDouble:
   case eDmValueListInt:
   case eDmValueListObjects:
   case eDmValueListString:

   case eDmValueObjectTree:
   case eDmValueFormula:
   default:
      bRet = false;
      break;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:35:52 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateSetterCode       // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:35:52 2012-----------*/
QString CwmsCodeGeneratorCTemp::GenerateSetterCode(EdmValueType p_eReturnValue, QString p_qstrMember)
{
   QString qstrMember = "m_" + p_qstrMember;
   QString qstrRet = AddIndent(1);

   switch (p_eReturnValue)
   {
   case eDmValueBinaryDocument:
      qstrRet += qstrMember + " = p_qstrFilename;"; // Filename
      AddMemberString("QString " + qstrMember);
      break;
   case eDmValueBool:
      qstrRet += qstrMember + "= p_bValue;";
      AddMemberString("bool " + qstrMember);
      break;
   case eDmValueCharacterDocument:
      qstrRet += qstrMember + " =  p_qstrValue;";
      AddMemberString("QString " + qstrMember);
      break;
   case eDmValueEnum:
   case eDmValueCounter:
      qstrRet += qstrMember + " = p_iValue;";
      AddMemberString("int " + qstrMember);
      break;
   case eDmValueDate:
      qstrRet += qstrMember + " = p_qdValue;";
      AddMemberString("QDate " + qstrMember);
      break;
   case eDmValueDateTime:
      qstrRet += qstrMember + " = p_qdtValue;";
      AddMemberString("QDateTime " + qstrMember);
      break;
   case eDmValueDictIntDouble:
      qstrRet += "";
      break;
   case eDmValueDictIntInt:
      qstrRet += "";
      break;
   case eDmValueDictIntString:
      qstrRet += "";
      break;
   case eDmValueDictStringDouble:
      qstrRet += "";
      break;
   case eDmValueDictStringInt:
      qstrRet += "";
      break;
   case eDmValueDictStringString:
      qstrRet += "";
      break;
   case eDmValueDouble:
      qstrRet += qstrMember + " = p_dValue;";
      AddMemberString("double " + qstrMember);
      break;
   case eDmValueFloat:
      qstrRet += qstrMember + " = p_fValue;";
      AddMemberString("float " + qstrMember);
      break;
   case eDmValueFormula:
      qstrRet += "";
      break;
   case eDmValueInt:
      qstrRet += qstrMember + " = p_iValue;";
      AddMemberString("int " + qstrMember);
      break;
   case eDmValueListDouble:
      qstrRet += "";
      break;
   case eDmValueListInt:
      qstrRet += "";
      break;
   case eDmValueListObjects:
      qstrRet += "";
      break;
   case eDmValueListString:
      qstrRet += "";
      break;
   case eDmValueLong:
      qstrRet += qstrMember + " = p_lValue;";
      AddMemberString("long " + qstrMember);
      break;
   case eDmValueContainerRef:
      qstrRet += qstrMember + " = p_pCdmOLValue;";
      AddMemberString("CdmObjectContainer* " + qstrMember);
      break;
   case eDmValueObjectRef:
      qstrRet += qstrMember + " = p_pCdmValue;";
      AddMemberString("CdmObject* " + qstrMember);
      break;
   case eDmValueString:
      qstrRet += qstrMember + " = p_qstrValue;";
      AddMemberString("QString " + qstrMember);
      break;
   case eDmValueTime:
      qstrRet += qstrMember + " = p_qtValue;";
      AddMemberString("QTime " + qstrMember);
      break;
   case eDmValueUser:
      qstrRet += qstrMember + " = p_pCumValue;";
      AddMemberString("CumUser* " + qstrMember);
      break;
   case eDmValueObjectTree:
      qstrRet += ""; // not yet implemented
      break;
   default:
      qstrRet += "Unknown Type";
   }

   return qstrRet + "\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 16:38:49 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::AddMemberString          // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 16:38:49 2012-----------*/
void CwmsCodeGeneratorCTemp::AddMemberString(QString p_qstrMember)
{
   m_qstrlMembers.append(p_qstrMember);
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:35:43 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GetParameter             // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:35:43 2012-----------*/
QString CwmsCodeGeneratorCTemp::GetParameter(EdmValueType p_eDmValue)
{

   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "QString p_qstrFilename";
      break;
   case eDmValueBool:
      qstrRet = "bool p_bValue";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "QString p_qstrValue";
      break;
   case eDmValueEnum:
   case eDmValueCounter:
      qstrRet = "int p_iValue";
      break;
   case eDmValueDate:
      qstrRet = "QDate p_qdValue";
      break;
   case eDmValueDateTime:
      qstrRet = "QDateTime p_qdtValue";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "int p_iKey, double p_dValue";
      break;
   case eDmValueDictIntInt:
      qstrRet = "int p_iKey, int p_iValue";
      break;
   case eDmValueDictIntString:
      qstrRet = "int p_iKey, QString p_qstrValue";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "QString p_qstrKey, double p_dValue";
      break;
   case eDmValueDictStringInt:
      qstrRet = "QString p_qstrKey, int p_iValue";
      break;
   case eDmValueDictStringString:
      qstrRet = "QString p_qstrKey, QString p_qstrValue";
      break;
   case eDmValueDouble:
      qstrRet = "double p_dValue";
      break;
   case eDmValueFloat:
      qstrRet = "float p_fValue";
      break;
   case eDmValueFormula:
      qstrRet = "NO CODE";
      break;
   case eDmValueInt:
      qstrRet = "int p_iValue";
      break;
   case eDmValueListDouble:
      qstrRet = "double p_dValue";
      break;
   case eDmValueListInt:
      qstrRet = "int p_iValue";
      break;
   case eDmValueListObjects:
      qstrRet = "CdmObject* p_pCdmValue";
      break;
   case eDmValueListString:
      qstrRet = "QString p_qstrValue";
      break;
   case eDmValueLong:
      qstrRet = "long p_lValue";
      break;
   case eDmValueContainerRef:
      qstrRet = "CdmObjectContainer* p_pCdmOLValue";
      break;
   case eDmValueObjectRef:
      qstrRet = "CdmObject* p_pCdmValue";
      break;
   case eDmValueString:
      qstrRet = "QString p_qstrValue";
      break;
   case eDmValueTime:
      qstrRet = "QTime p_qtValue";
      break;
   case eDmValueUser:
      qstrRet = "CumUser* p_pCumValue";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------Mi 6. Jun 15:35:32 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateGetterSource     // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:35:32 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateGetterSource(QString p_qstrMember, EdmValueType p_eReturnValue)
{
   if (CheckGetterMethod(p_eReturnValue))
   {
      m_qstrSource += GetReturnType(p_eReturnValue) + " ";
      m_qstrSource += m_qstrClassName + "::Get" + GenerateCodeMemberName(p_qstrMember) + "()\n";
      m_qstrSource += "{\n";
      m_qstrSource += GenerateGetterCode(p_qstrMember);
      m_qstrSource += "}\n\n";
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:35:20 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::CheckGetterMethod        // private                           *
 * @return  bool                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:35:20 2012-----------*/
bool CwmsCodeGeneratorCTemp::CheckGetterMethod(EdmValueType p_eDmValue)
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
   case eDmValueQObject:
      bRet = true;
      break;

   case eDmValueDictIntDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
   case eDmValueObjectTree:
   case eDmValueArray:
   case eDmValueDimDouble:
   case eDmValueGeoPos:
   case eDmValueNone:
   case eDmValueURI:
   case eDmValueUserGroup:
      bRet = false;
      break;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:35:08 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GetReturnType            // private                           *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:35:08 2012-----------*/
QString CwmsCodeGeneratorCTemp::GetReturnType(EdmValueType p_eDmValue)
{
   QString qstrRet;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
      qstrRet = "QString"; // Filename
      break;
   case eDmValueBool:
      qstrRet = "bool";
      break;
   case eDmValueCharacterDocument:
      qstrRet = "QString";
      break;
   case eDmValueEnum:
   case eDmValueCounter:
      qstrRet = "int";
      break;
   case eDmValueDate:
      qstrRet = "QDate";
      break;
   case eDmValueDateTime:
      qstrRet = "QDateTime";
      break;
   case eDmValueDictIntDouble:
      qstrRet = "QMap<int, double>";
      break;
   case eDmValueDictIntInt:
      qstrRet = "QMap<int, int>";
      break;
   case eDmValueDictIntString:
      qstrRet = "QMap<int, QString>";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "QMap<QString, double>";
      break;
   case eDmValueDictStringInt:
      qstrRet = "QMap<QString, int>";
      break;
   case eDmValueDictStringString:
      qstrRet = "QMap<QString, QString>";
      break;
   case eDmValueDouble:
      qstrRet = "double";
      break;
   case eDmValueFloat:
      qstrRet = "float";
      break;
   case eDmValueFormula:
      qstrRet = "QString";// Display string
      break;
   case eDmValueInt:
      qstrRet = "int";
      break;
   case eDmValueListDouble:
      qstrRet = "QList<double>";
      break;
   case eDmValueListInt:
      qstrRet = "QList<int>";
      break;
   case eDmValueListObjects:
      qstrRet = "QList<CdmObject*>";
      break;
   case eDmValueListString:
      qstrRet = "QList<QString>";
      break;
   case eDmValueLong:
      qstrRet = "long";
      break;
   case eDmValueContainerRef:
      qstrRet = "CdmObjectContainer*";
      break;
   case eDmValueObjectRef:
      qstrRet = "CdmObject*";
      break;
   case eDmValueString:
      qstrRet = "QString";
      break;
   case eDmValueTime:
      qstrRet = "QTime";
      break;
   case eDmValueUser:
      qstrRet = "CumUser*";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------So 4. Nov 09:17:19 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateGetterCode       // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 4. Nov 09:17:19 2012-----------*/
QString CwmsCodeGeneratorCTemp::GenerateGetterCode(QString p_qstrMember)
{
   QString qstrRet;
   QString qstrMember = "m_" + p_qstrMember;

   qstrRet += AddIndent(1);
   qstrRet += "return " + qstrMember;
   return qstrRet + "\n";
}


/** +-=---------------------------------------------------------Mi 6. Jun 15:34:45 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateSetterHeader     // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:34:45 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateSetterHeader(QString p_qstrMethodName,
                                                  EdmMemberAccess p_eAccessType,
                                                  EdmValueType p_eReturnValue)
{
   QString qstrMethod;

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
   QString qstrFunction = "void Set" + GenerateCodeMemberName(p_qstrMethodName) + "(" + GetParameter(p_eReturnValue) + ")";
   qstrMethod += qstrFunction;
   qstrMethod += ";\n";
   m_qstrHeader += qstrMethod;
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:34:35 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateGetterHeader     // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmMemberAccess p_eAccessType                    //                                   *
 * @param   EdmValue p_eReturnValue                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:34:35 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateGetterHeader(QString p_qstrMethodName,
                                                  EdmMemberAccess p_eAccessType,
                                                  EdmValueType p_eReturnValue)
{
   QString qstrMethod;

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
   QString qstrFunction = GetReturnType(p_eReturnValue)+ " Get" + GenerateCodeMemberName(p_qstrMethodName) + "();\n";
   qstrMethod += qstrFunction;
   qstrMethod += ";\n";
   m_qstrHeader += qstrMethod;
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:34:21 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateDestructorHeader // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:34:21 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateDestructorHeader()
{

   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "virtual ~" + m_qstrClassName + "();\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:34:12 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateDestructorSource // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:34:12 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateDestructorSource()
{

   m_qstrSource += m_qstrClassName + "::~" + m_qstrClassName + "()\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:46:01 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorSource // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:46:01 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructorSource()
{
   m_qstrSource += m_qstrClassName + "::" + m_qstrClassName + "(" + m_qstrClassNameTwin + "& p_rCopy)\n";

   if (!m_qmBaseClasses.isEmpty()) 
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
   GenerateCopyConstructorMembers();
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:46:17 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorHeader // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:46:17 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "(" + m_qstrClassNameTwin + "& p_rCopy);\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:34:02 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateDefaultConstructorSource // private                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:34:02 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateDefaultConstructorSource()
{
   m_qstrSource += m_qstrClassName + "::" + m_qstrClassName + "()\n";

  if (!m_qmBaseClasses.isEmpty()) 
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

/** +-=---------------------------------------------------------Mi 6. Jun 15:33:51 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateDefaultConstructorHeader // private                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:33:51 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateDefaultConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "();\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:33:39 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateParameterConstructorSource // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:33:39 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateParameterConstructorSource()
{
   m_qstrSource += m_qstrClassName + "::" + m_qstrClassName + "(CdmObject* p_pCdmObject)\n";

   if (m_qmBaseClasses.isEmpty())
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

/** +-=---------------------------------------------------------Mi 6. Jun 15:33:16 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateParameterConstructorHeader // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:33:16 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateParameterConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += m_qstrClassName + "(CdmObject* p_pCdmObject);\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:33:05 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateDestructors      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:33:05 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateDestructors()
{
   GenerateDestructorSource();
   GenerateDestructorHeader();
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:32:55 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GeneratesMemberAccess    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:32:55 2012-----------*/
void CwmsCodeGeneratorCTemp::GeneratesMemberAccess()
{
   QMap<long, CdmMember*> qmMembers;
   if (m_bCreateBaseClassMemberFunctions)
   {
       m_rpCdmClass->GetMemberMap(qmMembers);
   }
   else
   {
       m_rpCdmClass->GetClassMemberMap(qmMembers);
   }

   GenerateMembersAccess(qmMembers);
}

/** +-=---------------------------------------------------------Mi 6. Jun 18:07:01 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateMembersAccess    // private                           *
 * @return  void                                             //                                   *
 * @param   QMap<long, CdmMember*>& p_rMap                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 18:07:01 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateMembersAccess(QMap<long, CdmMember*>& p_rMap)
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*>::iterator qmIt = p_rMap.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = p_rMap.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateMemberAccess(qmIt.value());
      }
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 15:31:33 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateMemberAccess     // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 15:31:33 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateMemberAccess(CdmMember* p_pCdmMember)
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

/** +-=---------------------------------------------------------Mi 6. Jun 17:35:59 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::AddMembersToHeader       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:35:59 2012-----------*/
void CwmsCodeGeneratorCTemp::AddMembersToHeader()
{
   for (int ICOunter = 0; ICOunter < m_qstrlMembers.size(); ++ICOunter)
   {
      QString qstrMember = m_qstrlMembers[ICOunter];
      m_qstrHeader += "private " + qstrMember + ";\n";
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 17:48:27 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:48:27 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers()
{
   QMap<long, CdmMember*> qmMembers;
   if (m_bCreateBaseClassMemberFunctions)
   {
      m_rpCdmClass->GetMemberMap(qmMembers);
   }
   else
   {
      m_rpCdmClass->GetClassMemberMap(qmMembers);
   }

   GenerateMembersAccess(qmMembers);
}

/** +-=---------------------------------------------------------Mi 6. Jun 17:47:00 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers // private                     *
 * @return  void                                             //                                   *
 * @param   QMap<long, CdmMember*>& p_rMap                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:47:00 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructorMembers(QMap<long, CdmMember*>& p_rMap)
{

   if (CHKPTR(m_rpCdmClass))
   {
      QMap<long, CdmMember*>::iterator qmIt = p_rMap.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = p_rMap.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         GenerateCopyConstructorMember(qmIt.value());
      }
   }
}

/** +-=---------------------------------------------------------Mi 6. Jun 17:47:18 2012-----------*
 * @method  CwmsCodeGeneratorCTemp::GenerateCopyConstructorMember // private                      *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 17:47:18 2012-----------*/
void CwmsCodeGeneratorCTemp::GenerateCopyConstructorMember(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QString qstrKeyname = p_pCdmMember->GetKeyname();
      m_qstrSource += AddIndent(1);
      m_qstrSource += "Set" + qstrKeyname + "(" + m_qstrClassNameTwin + "Get." + qstrKeyname + "());\n";
   }
}
