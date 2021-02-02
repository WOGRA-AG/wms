/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsCodeGeneratorCBase.cpp
 ** Started Implementation: 2011/11/21
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QTextStream>

// own Includes
#include "CwmsCodeGeneratorCBase.h"


/** +-=---------------------------------------------------------Di 22. Nov 19:06:26 2011----------*
 * @method  CwmsCodeGeneratorCBase::CwmsCodeGeneratorCBase   // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:06:26 2011----------*/
CwmsCodeGeneratorCBase::CwmsCodeGeneratorCBase(QString p_qstrFilename, QString p_qstrClassName)
: m_qstrFilename(p_qstrFilename),
  m_qstrClassName(p_qstrClassName)
{
   m_qstrFilename = m_qstrFilename;
}

/** +-=---------------------------------------------------------Mo 21. Nov 17:03:14 2011----------*
 * @method  CwmsCodeGeneratorCBase::~CwmsCodeGeneratorCBase  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorCBase                                        *
 *----------------last changed: --------------------------------Mo 21. Nov 17:03:14 2011----------*/
CwmsCodeGeneratorCBase::~CwmsCodeGeneratorCBase()
{
}

/** +-=---------------------------------------------------------Di 22. Nov 19:20:44 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateConstructorSourceHead // protected                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrParameter                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:20:44 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateConstructorSourceHead(QString p_qstrClassName,
                                                              QString p_qstrParameter)
{
   return GenerateMethodHeadSource("", p_qstrClassName, p_qstrClassName, p_qstrParameter);
}

/** +-=---------------------------------------------------------Di 5. Jun 11:36:50 2012-----------*
 * @method  CwmsCodeGeneratorCBase::SetDllExportDeclaration  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDeclaration                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:36:50 2012-----------*/
void CwmsCodeGeneratorCBase::SetDllExportDeclaration(QString p_qstrDeclaration)
{
   m_qstrDllExportDeclaration = p_qstrDeclaration;
}

/** +-=---------------------------------------------------------Di 22. Nov 18:55:12 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateConstructorHeader // protected                        *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrParameter                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:55:12 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateConstructorHeader(QString p_qstrClassName,
                                                          QString p_qstrParameter)
{
   return GenerateMethodHeadHeader("public", "", p_qstrClassName, p_qstrParameter);
}

/** +-=---------------------------------------------------------Di 22. Nov 18:55:05 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateDestructorSource // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:55:05 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateDestructorSource(QString p_qstrClassName)
{
   return GenerateMethodHeadSource("", p_qstrClassName, "~" + p_qstrClassName, "");
}

/** +-=---------------------------------------------------------Di 22. Nov 18:55:00 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateDestructorHeader // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:55:00 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateDestructorHeader(QString p_qstrClassName)
{
   return GenerateMethodHeadHeader("public", "", "~" + p_qstrClassName, "");
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:44:08 2012-----------*
 * @method  CwmsCodeGeneratorCBase::GenerateDefaultConstructorHeader // protected                 *
 * @return  void                                             //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:44:08 2012-----------*/
void CwmsCodeGeneratorCBase::GenerateDefaultConstructorHeader(QString p_qstrClassName)
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += p_qstrClassName + "();\n";
}

/** +-=---------------------------------------------------------Mi 6. Jun 13:44:13 2012-----------*
 * @method  CwmsCodeGeneratorCBase::GenerateDefaultConstructorSourceWithoutBaseClasses // protected*
 * @return  void                                             //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Jun 13:44:13 2012-----------*/
void CwmsCodeGeneratorCBase::GenerateDefaultConstructorSourceWithoutBaseClasses(QString p_qstrClassName)
{

   m_qstrSource += p_qstrClassName + "::" + p_qstrClassName + "()\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Di 22. Nov 18:54:51 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateMethodHeadSource // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrReturnType                         //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   QString p_qstrParameters                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:54:51 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateMethodHeadSource(QString p_qstrReturnType,
                                                         QString p_qstrClassName,
                                                         QString p_qstrMethodName,
                                                         QString p_qstrParameters)
{
   QString qstrRet;

   if (!p_qstrReturnType.isEmpty())
   {
      qstrRet += p_qstrReturnType + " ";
   }

   qstrRet += p_qstrClassName + "::" + p_qstrMethodName + "(" + p_qstrParameters + ")\n";

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 22. Nov 18:54:43 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateMethodHeadHeader // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrAccessType                         //                                   *
 * @param   QString p_qstrReturnType                         //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   QString p_qstrParameters                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:54:43 2011----------*/
QString CwmsCodeGeneratorCBase::GenerateMethodHeadHeader(QString p_qstrAccessType,
                                                         QString p_qstrReturnType,
                                                         QString p_qstrMethodName,
                                                         QString p_qstrParameters)
{
   QString qstrRet;

   qstrRet += AddIndent(1);
   qstrRet += p_qstrAccessType +":\n";
   qstrRet += AddIndent(2);

   if (!p_qstrReturnType.isEmpty())
   {
      qstrRet += p_qstrReturnType + " ";
   }

   qstrRet += p_qstrMethodName + "(" + p_qstrParameters + ")\n";
   return qstrRet;
}

/** +-=---------------------------------------------------------Mo 5. Dez 11:48:46 2011-----------*
 * @method  CwmsCodeGeneratorCBase::GenerateSlotHeadHeader   // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrAccessType                         //                                   *
 * @param   QString p_qstrReturnType                         //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   QString p_qstrParameters                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 11:48:46 2011-----------*/
QString CwmsCodeGeneratorCBase::GenerateSlotHeadHeader(QString p_qstrAccessType,
                                                       QString p_qstrReturnType,
                                                       QString p_qstrMethodName,
                                                       QString p_qstrParameters)
{
   QString qstrRet;

   qstrRet += AddIndent(1);
   qstrRet += p_qstrAccessType + " slots:\n";
   qstrRet += AddIndent(2);

   if (!p_qstrReturnType.isEmpty())
   {
      qstrRet += p_qstrReturnType + " ";
   }

   qstrRet += p_qstrMethodName + "(" + p_qstrParameters + ")\n";

   return qstrRet;
}

/** +-=---------------------------------------------------------Mo 21. Nov 17:03:32 2011----------*
 * @method  CwmsCodeGeneratorCBase::SaveFiles                // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 17:03:32 2011----------*/
void CwmsCodeGeneratorCBase::SaveFiles()
{
   SaveHeaderFile();
   SaveSourceFile();
}

/** +-=---------------------------------------------------------Mo 21. Nov 17:03:48 2011----------*
 * @method  CwmsCodeGeneratorCBase::SaveSourceFile           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 17:03:48 2011----------*/
void CwmsCodeGeneratorCBase::SaveSourceFile()
{
   QString qstrFilename = m_qstrFilename + "/" + m_qstrClassName + ".cpp";
   SaveFile(qstrFilename, m_qstrSource);
}

/** +-=---------------------------------------------------------Di 22. Nov 18:54:27 2011----------*
 * @method  CwmsCodeGeneratorCBase::SaveHeaderFile           // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:54:27 2011----------*/
void CwmsCodeGeneratorCBase::SaveHeaderFile()
{
   QString qstrFilename = m_qstrFilename + "/" + m_qstrClassName + ".h";
   SaveFile(qstrFilename, m_qstrHeader);
}

/** +-=---------------------------------------------------------Di 22. Nov 19:06:07 2011----------*
 * @method  CwmsCodeGeneratorCBase::OpenClass                // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:06:07 2011----------*/
void CwmsCodeGeneratorCBase::OpenClass()
{
   QString qstrDefine = m_qstrClassName;
   m_qstrHeader += "#ifndef " + qstrDefine.toUpper() + "_H\n";      
   m_qstrHeader += "#define " + qstrDefine.toUpper() + "_H\n\n";      
   m_qstrHeader += "#ifdef WURZELBLA\n";
   m_qstrHeader += "#define slots\n";
   m_qstrHeader += "#endif //\n\n\n";
   m_qstrHeader += "// System and QT Includes\n\n\n";      
   m_qstrHeader += "// WMS Includes\n";

   if (m_qmBaseClasses.isEmpty())
   {
      m_qstrHeader += "#include \"CdmObjectAdaptor.h\"\n\n";
   }
   else
   {
      QMap<QString, QString>::iterator qmIt = m_qmBaseClasses.begin();
      QMap<QString, QString>::iterator qmItEnd = m_qmBaseClasses.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         m_qstrHeader += "#include \"" + qmIt.value() + "\"\n";
      }

      m_qstrHeader += "\n";
   }

   m_qstrHeader += "// Own Includes\n";
   
   for (int iCounter = 0; iCounter < m_qstrlHeaderIncludes.size(); ++iCounter)
   {
      m_qstrSource += "#include \"" + m_qstrlHeaderIncludes[iCounter] + "\"\n";
   }

   m_qstrHeader += "\n";
   m_qstrHeader += "// Forwards\n";

   for (int iCounter = 0; iCounter < m_qstrlForwards.size(); ++iCounter)
   {
      m_qstrHeader += "class " + m_qstrlForwards[iCounter] + "\"\n";
   }

   m_qstrHeader += "\n";
   m_qstrHeader += "// Enumerations\n\n";

   if (m_qstrDllExportDeclaration != "")
   {
      m_qstrHeader += "class " + m_qstrDllExportDeclaration + " " + m_qstrClassName;
   }
   else
   {
      m_qstrHeader += "class " + m_qstrClassName;
   }
   

   if (!m_qmBaseClasses.isEmpty())
   {
      QMap<QString, QString>::iterator qmIt = m_qmBaseClasses.begin();
      QMap<QString, QString>::iterator qmItEnd = m_qmBaseClasses.end();
      m_qstrHeader += " : ";
      bool bFirst = true;

      for (; qmIt != qmItEnd; ++qmIt)
      {
         if (bFirst)
         {
            m_qstrHeader += "public ";
         }
         else
         {
            m_qstrHeader += ", ";
         }

         m_qstrHeader += qmIt.key();
      }

      m_qstrHeader += "\n";
   }
   else
   {
      m_qstrHeader += ": public CdmObjectAdaptor\n";
   }
   m_qstrHeader += "{\n\n";

   if (m_qmBaseClasses.contains("QObject"))
   {
      m_qstrHeader += AddIndent(1);
      m_qstrHeader += "Q_OBJECT\n";
   }
}


/** +-=---------------------------------------------------------Di 22. Nov 19:05:56 2011----------*
 * @method  CwmsCodeGeneratorCBase::CloseClass               // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:05:56 2011----------*/
void CwmsCodeGeneratorCBase::CloseClass()
{
   m_qstrHeader += "};\n";
   m_qstrHeader += "#endif //\n";
}

/** +-=---------------------------------------------------------Di 22. Nov 19:17:29 2011----------*
 * @method  CwmsCodeGeneratorCBase::GenerateSourceHeader     // protected                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:17:29 2011----------*/
void CwmsCodeGeneratorCBase::GenerateSourceHeader()
{
   m_qstrSource += "// System and QT Includes\n\n\n";      
   m_qstrSource += "// WMS Includes\n";
   m_qstrSource += "#include \"CdmLogging.h\"\n\n";
   m_qstrSource += "// Own Includes\n";

   for (int iCounter = 0; iCounter < m_qstrlSourceIncludes.size(); ++iCounter)
   {
      m_qstrSource += "#include \"" + m_qstrlSourceIncludes[iCounter] + "\"\n";
   }

   m_qstrSource += "#include \"" + m_qstrClassName + ".h\"\n\n";
   m_qstrSource += "// Forwards\n\n";
   m_qstrSource += "// Enumerations\n\n";
}

/** +-=---------------------------------------------------------Di 22. Nov 19:22:55 2011----------*
 * @method  CwmsCodeGeneratorCBase::AddMemberVariable        // protected                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrType                               //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:22:55 2011----------*/
void CwmsCodeGeneratorCBase::AddMemberVariable(QString p_qstrType, QString p_qstrName)
{
   m_qstrHeader += "private: " + p_qstrType + " " + p_qstrName + ";\n";
}

/** +-=---------------------------------------------------------Mi 23. Nov 11:40:10 2011----------*
 * @method  CwmsCodeGeneratorCBase::AddSourceInclude         // protected                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrInclude                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:40:10 2011----------*/
void CwmsCodeGeneratorCBase::AddSourceInclude(QString p_qstrInclude)
{
   m_qstrlSourceIncludes.append(p_qstrInclude);
}

/** +-=---------------------------------------------------------Mi 23. Nov 11:40:15 2011----------*
 * @method  CwmsCodeGeneratorCBase::AddHeaderInclude         // protected                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrInclude                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:40:15 2011----------*/
void CwmsCodeGeneratorCBase::AddHeaderInclude(QString p_qstrInclude)
{
   m_qstrlHeaderIncludes.append(p_qstrInclude);
}


/** +-=---------------------------------------------------------Mi 23. Nov 11:40:21 2011----------*
 * @method  CwmsCodeGeneratorCBase::AddForward               // protected                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrForward                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:40:21 2011----------*/
void CwmsCodeGeneratorCBase::AddForward(QString p_qstrForward)
{
   m_qstrlForwards.append(p_qstrForward);
}



/** +-=---------------------------------------------------------Mi 23. Nov 11:02:32 2011----------*
 * @method  CwmsCodeGeneratorCBase::AddBaseClassData         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrBaseClassName                      //                                   *
 * @param   QString p_qstrBaseClassFilename                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:02:32 2011----------*/
void CwmsCodeGeneratorCBase::AddBaseClassData(QString p_qstrBaseClassName,
                                              QString p_qstrBaseClassFilename)
{
   if (!p_qstrBaseClassName.isEmpty())
   {
      m_qmBaseClasses.insert(p_qstrBaseClassName, p_qstrBaseClassFilename);
   }
}

/** +-=---------------------------------------------------------Mo 5. Dez 11:38:54 2011-----------*
 * @method  CwmsCodeGeneratorCBase::GetClassName             // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 11:38:54 2011-----------*/
QString CwmsCodeGeneratorCBase::GetClassName()
{
   return m_qstrClassName;
}

/** +-=---------------------------------------------------------Fr 13. Jul 15:38:51 2012----------*
 * @method  CwmsCodeGeneratorCBase::GetParameter             // protected                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 15:38:51 2012----------*/
QString CwmsCodeGeneratorCBase::GetParameter(EdmValueType p_eDmValue)
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
   case eDmValueInt:
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
      qstrRet = "QMap<int,double> p_qmValue";
      break;
   case eDmValueDictIntInt:
      qstrRet = "QMap<int,int> p_qmValue";
      break;
   case eDmValueDictIntString:
      qstrRet = "QMap<int,QString> p_qmValue";
      break;
   case eDmValueDictStringDouble:
      qstrRet = "QMap<QString,double> p_qmValue";
      break;
   case eDmValueDictStringInt:
      qstrRet = "QMap<QString,int> p_qmValue";
      break;
   case eDmValueDictStringString:
      qstrRet = "QMap<QString,QString> p_qmValue";
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
   case eDmValueListDouble:
      qstrRet = "QLinkedList<double> p_qlValue";
      break;
   case eDmValueListInt:
      qstrRet = "QLinkedList<int> p_qlValue";
      break;
   case eDmValueListObjects:
      qstrRet = "QLinkedList<CdmObject*> p_qlValue";
      break;
   case eDmValueListString:
      qstrRet = "QLinkedList<QString> p_qlValue";
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

/** +-=---------------------------------------------------------Fr 13. Jul 13:37:35 2012----------*
 * @method  CwmsCodeGeneratorCBase::GetReturnType            // protected                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 13:37:35 2012----------*/
QString CwmsCodeGeneratorCBase::GetReturnType(EdmValueType p_eDmValue)
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
   case eDmValueInt:
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
   case eDmValueListDouble:
      qstrRet = "QLinkedList<double>";
      break;
   case eDmValueListInt:
      qstrRet = "QLinkedList<int>";
      break;
   case eDmValueListObjects:
      qstrRet = "QLinkedList<CdmObject*>";
      break;
   case eDmValueListString:
      qstrRet = "QLinkedList<QString>";
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
   case eDmValueUserGroup:
      qstrRet = "CumUserGroup*";
      break;
   case eDmValueObjectTree:
      qstrRet = "NYI"; // not yet implemented
      break;
   default:
      qstrRet = "Unknown Type";
   }

   return qstrRet;
}
