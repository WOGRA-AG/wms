/******************************************************************************
** WOGRA technologies GmbH & Co. KG Modul Information
** Modulename: CwmsCodeGeneratorCBl.cpp
** Started Implementation: 2012/06/05
** Description:
**
** Implements the code generator for web interfaces.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
*****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"

// own Includes
#include "CwmsCodeGeneratorCWebIf.h"

/** +-=---------------------------------------------------------Fr 8. Jun 16:12:20 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::CwmsCodeGeneratorCWebIf // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QString p_qstrObjectListKeyname                  //                                   *
 * @param   QString p_qstrAdaptorClassname                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 16:12:20 2012-----------*/
CwmsCodeGeneratorCWebIf::CwmsCodeGeneratorCWebIf(QString p_qstrFilename,
                                                 QString p_qstrClassName,
                                                 CdmClass* p_pCdmClass,
                                                 QString p_qstrObjectListKeyname,
                                                 QString p_qstrAdaptorClassname)
   : CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassName),
  m_rpCdmClass(p_pCdmClass),
  m_qstrObjectListKeyname(p_qstrObjectListKeyname),
  m_qstrAdaptorClassname(p_qstrAdaptorClassname)
{
}

/** +-=---------------------------------------------------------Di 5. Jun 16:26:40 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::~CwmsCodeGeneratorCWebIf // public, virtual                  *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorCBl                                          *
 *----------------last changed: --------------------------------Di 5. Jun 16:26:40 2012-----------*/
CwmsCodeGeneratorCWebIf::~CwmsCodeGeneratorCWebIf()
{
}

/** +-=---------------------------------------------------------Di 5. Jun 11:39:39 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateCode            // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:39:39 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      GenerateCodeP();
      SaveFiles();
   }
}


/** +-=---------------------------------------------------------Di 5. Jun 11:39:45 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateCodeP           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:39:45 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateCodeP()
{
   if (CHKPTR(m_rpCdmClass))
   {
      // Source Includes
      AddSourceInclude("CdmQueryEnhanced.h");
      AddSourceInclude("CdmObject.h");
      AddSourceInclude("CdmObjectContainer.h");
      AddSourceInclude("CwmscomData.h");
      AddSourceInclude("CwmscomDataResult.h");
      AddSourceInclude(m_qstrAdaptorClassname + ".h");
      AddSourceInclude(GenerateCodeMemberName(m_rpCdmClass->GetKeyname()) + ".h");

      // Header Includes
      AddHeaderInclude("wmsinterface.h");
      // Header forwards
      AddForward("CwmscomControllerBase");
      AddForward("CwmscomData");
      // Base classes
      AddBaseClassData("CwmscomResourceBase", "CwmscomResourceBase.h");
      SetDllExportDeclaration("BMSINTERFACE_API");

      // Generate Header File head.
      OpenClass();
      GenerateSourceHeader();
      GenerateConstructor();
      GenerateDestructor();
      GenerateGet();
      GeneratePut();
      GenerateDelete();
      GenerateDescription();
      GenerateDetails();
      GenerateList();
      CloseClass();
   }
}

/** +-=---------------------------------------------------------Di 5. Jun 11:44:52 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateConstructor     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:44:52 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateConstructor()
{
   GenerateParameterConstructorSource();
   GenerateParameterConstructorHeader();
}

/** +-=---------------------------------------------------------Di 5. Jun 11:44:21 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateParameterConstructorSource // private                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:44:21 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateParameterConstructorSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::" + GenerateCodeMemberName(m_qstrClassName) + "(CwmscomControllerBase* p_pController)\n";
   m_qstrSource += ": CwmscomResourceBase(p_pController, \"" + GenerateCodeMemberName(m_qstrClassName) + "\", true, true)\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 11:44:06 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateParameterConstructorHeader // private                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:44:06 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateParameterConstructorHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += GenerateCodeMemberName(m_rpCdmClass->GetKeyname()) + "(CwmscomControllerBase* p_pController);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 11:50:15 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDestructor      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:50:15 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDestructor()
{
   GenerateDestructorSource(m_qstrClassName);
   GenerateDestructorHeader(m_qstrClassName);
}

/** +-=---------------------------------------------------------Di 5. Jun 11:58:40 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateGet             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:58:40 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateGet()
{
   GenerateGetHeader();
   GenerateGetSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:09:30 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateGetHeader       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:09:30 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateGetHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "ExecuteGet(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 13:09:40 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateGetSource       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:09:40 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateGetSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::ExecuteGet(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "QString qstrMode = p_pData->GetValue(\"Mode\").toString();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (qstrMode == \"List\");\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "GetList()\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "else\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "GetDetails(p_pData);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 11:58:51 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GeneratePut             // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:58:51 2012-----------*/
void CwmsCodeGeneratorCWebIf::GeneratePut()
{
   GeneratePutHeader();
   GeneratePutSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:11:04 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GeneratePutHeader       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:11:04 2012-----------*/
void CwmsCodeGeneratorCWebIf::GeneratePutHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "ExecutePut(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 13:49:48 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GeneratePutSource       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:49:48 2012-----------*/
void CwmsCodeGeneratorCWebIf::GeneratePutSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::ExecutePut(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CwmscomDataResult* pResult = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (p_pData->HasValue(\"Object\"))\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "QVariant qvObject = p_pData->GetValue(\"Object\");\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += m_qstrAdaptorClassname + " c" + m_qstrAdaptorClassname + ";\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "c" + m_qstrAdaptorClassname +".SetVariant(qvObject, \"" + m_qstrObjectListKeyname + "\");\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "c" + m_qstrAdaptorClassname +".CommitObject();\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pResult = GetResultContainer(p_pData, 1,  \"Save executed\", eBmscomMessageServerityInfo);\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pResult->AddValue(\"Object\", c" + m_qstrAdaptorClassname + ".GetVariant());\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 11:59:01 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDelete          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:59:01 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDelete()
{
   GenerateDeleteHeader();
   GenerateDeleteSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:11:28 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDeleteHeader    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:11:28 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDeleteHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "ExecuteDelete(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 14:11:35 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDeleteSource    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 14:11:35 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDeleteSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::ExecuteDelete(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CwmscomDataResult* pResult = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "qint64 lObjectId = p_pData->GetValue(\"ObjectId\").toInt();\n\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (lObjectId > 0)\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "CdmObjectContainer* pContainer = " + m_qstrAdaptorClassname + "::GetObjectList();\n\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "CdmObject* pCdmObject = pContainer->FindObjectById(lObjectId);\n\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "if (pCdmObject)\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pCdmObject->SetDeleted();\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pCdmObject->Commit();\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pResult = GetResultContainer(p_pData, 1,  \"Delete executed\", eBmscomMessageServerityInfo);\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "else\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pResult = GetResultContainer(p_pData, -5000,  \"object not found\", eBmscomMessageServerityError);\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "else\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "pResult = GetResultContainer(p_pData, -5000,  \"datastructure not found\", eBmscomMessageServerityError);\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "else\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "pResult = GetResultContainer(p_pData, -5000,  \"session not found\", eBmscomMessageServerityFatal);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "else\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pResult = GetResultContainer(p_pData, -5000,  \"data are missing\", eBmscomMessageServerityFatal);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 11:59:13 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDescription     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:59:13 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDescription()
{
   GenerateDescriptionHeader();
   GenerateDescriptionSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:12:00 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDescriptionHeader // private                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:12:00 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDescriptionHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "public:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "ExecuteDescription(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 14:23:58 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDescriptionSource // private                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 14:23:58 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDescriptionSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::ExecuteDescription(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CwmscomDataResult* pResult = new CwmscomDataResult(p_pData);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pResult->SetMessage(\"Returning Interface Description for " + m_qstrClassName + "\");\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pResult->SetMessageCode(1);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pResult->SetSeverity(eBmscomMessageServerityInfo);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "AddCallParameters(pResult);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "// ToDo Result Parameters\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}


/** +-=---------------------------------------------------------Di 5. Jun 11:59:34 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDetails         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 11:59:34 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDetails()
{
   GenerateDetailsHeader();
   GenerateDetailsSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:12:36 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDetailsHeader   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:12:36 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDetailsHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "private:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "GetDetails(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 14:31:13 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateDetailsSource   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 14:31:13 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateDetailsSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::GetDetails(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CwmscomDataResult* pResult = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CwmscomDataResult* pResult = nullptr;\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "qint64 lObjectId = p_pData->GetValue(\"ObjectId\").toInt();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (lObjectId > 0)\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "CdmObjectContainer* pContainer = " + m_qstrAdaptorClassname + "::GetObjectList();\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "if (pContainer)\n\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "CdmObject* pCdmObject = pContainer->FindObjectById(lObjectId);\n\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "if (pCdmObject)\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += m_qstrAdaptorClassname + " c" + m_qstrAdaptorClassname + "(pCdmObject);\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "QVariant qvObject = c" + m_qstrAdaptorClassname + ".GetVariant();\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pResult = GetResultContainer(p_pData, 1,  \"object found\", eBmscomMessageServerityInfo);\n";
   m_qstrSource += AddIndent(5);
   m_qstrSource += "pResult->AddValue(\"Data\", qvObject);\n";
   m_qstrSource += AddIndent(4);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 13:20:55 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateList            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:20:55 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateList()
{
   GenerateListHeader();
   GenerateListSource();
}

/** +-=---------------------------------------------------------Di 5. Jun 13:20:46 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateListHeader      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:20:46 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateListHeader()
{
   m_qstrHeader += AddIndent(1);
   m_qstrHeader += "private:\n";
   m_qstrHeader += AddIndent(2);
   m_qstrHeader += "GetList(CwmscomData* p_pData);\n";
}

/** +-=---------------------------------------------------------Di 5. Jun 13:22:02 2012-----------*
 * @method  CwmsCodeGeneratorCWebIf::GenerateListSource      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 5. Jun 13:22:02 2012-----------*/
void CwmsCodeGeneratorCWebIf::GenerateListSource()
{
   m_qstrSource += GenerateCodeMemberName(m_qstrClassName) + "::GetList(CwmscomData* p_pData)\n";
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CwmscomDataResult* pResult = nullptr;\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (p_pData)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "// ToDo implement your displaying list here\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}
