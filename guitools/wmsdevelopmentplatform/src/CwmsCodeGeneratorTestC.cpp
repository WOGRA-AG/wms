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
#include "CdmMember.h"

// own Includes
#include "CwmsCodeGeneratorC.h"
#include "CwmsCodeGeneratorTestC.h"


/** +-=---------------------------------------------------------Fr 8. Jun 13:47:39 2012-----------*
 * @method  CwmsCodeGeneratorTestC::CwmsCodeGeneratorTestC   // public                            *
 * @return                                                   //                                   *
 * @param   CwmsCodeGeneratorC* p_pCodeGenerator             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrClassName                          //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 13:47:39 2012-----------*/
CwmsCodeGeneratorTestC::CwmsCodeGeneratorTestC(CwmsCodeGeneratorC* p_pCodeGenerator,
                                               QString p_qstrFilename,
                                               QString p_qstrClassName,
                                               CdmClass* p_pCdmClass)
   : CwmsCodeGeneratorCBase(p_qstrFilename, p_qstrClassName),
   m_pCodeGenerator(p_pCodeGenerator),
   m_rpCdmClass(p_pCdmClass)
{

}

/** +-=---------------------------------------------------------Fr 2. Dez 16:01:52 2011-----------*
 * @method  CwmsCodeGeneratorTestC::~CwmsCodeGeneratorTestC  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorC                                            *
 *----------------last changed: --------------------------------Fr 2. Dez 16:01:52 2011-----------*/
CwmsCodeGeneratorTestC::~CwmsCodeGeneratorTestC()
{
}

/** +-=---------------------------------------------------------Mo 5. Dez 11:08:33 2011-----------*
 * @method  CwmsCodeGeneratorTestC::AddIncludesAndForwards   // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 11:08:33 2011-----------*/
void CwmsCodeGeneratorTestC::AddIncludesAndForwards()
{
   AddSourceInclude(GenerateCodeMemberName(m_rpCdmClass->GetKeyname()) + ".h");
   AddHeaderInclude("QtTest/QtTest");
}

/** +-=---------------------------------------------------------Fr 2. Dez 16:02:37 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateCode             // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 2. Dez 16:02:37 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateCode()
{
   if (!m_qstrFilename.isEmpty() && !m_qstrClassName.isEmpty())
   {
      AddBaseClassData("QObject", "QObject");
      AddIncludesAndForwards();
      OpenClass();

      GenerateConstructor();
      GenerateDestructorSource(m_qstrClassName);
      GenerateDestructorHeader(m_qstrClassName);
      GenerateCreateTestObjectListMethod();
      GenerateCreateTestObjectClassMethod();
      GenerateTestCodeForMembers();
      GenerateDeleteTestObjectClassMethod();
      GenerateDeleteTestObjectListMethod();

      CloseClass();
      SaveFiles();
   }
}

/** +-=---------------------------------------------------------Mo 5. Dez 11:06:48 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateConstructor      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 11:06:48 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateConstructor()
{
   GenerateConstructorSource();
   AddMemberVariable("CdmObject*", "m_rpCdmObject");
   GenerateConstructorHeader(m_qstrClassName, "");
}

/** +-=---------------------------------------------------------Mo 5. Dez 11:04:28 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateConstructorSource // private                          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 11:04:28 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateConstructorSource()
{
   m_qstrSource += GenerateConstructorSourceHead(m_qstrClassName, "QString p_qstrDatabaseName");
   m_qstrSource += " : m_rpCdmObject(nullptr)\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n";
}


/** +-=---------------------------------------------------------Fr 2. Dez 16:06:53 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateDestructor       // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 2. Dez 16:06:53 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateDestructor()
{
   m_qstrSource += GenerateDestructorSource(m_qstrClassName);
   m_qstrSource += "{\n";
   m_qstrSource += "   // nothing to do here ;-)\n";
   m_qstrSource += "}\n";

   m_qstrHeader += GenerateDestructorHeader(m_qstrClassName);  
}

/** +-=---------------------------------------------------------Mo 5. Dez 12:56:44 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateTestSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 12:56:44 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateTestSlot()
{
   m_qstrHeader += GenerateSlotHeadHeader("private", "void", "TestAllSlot", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "TestAllSlot", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CreateTestObjectList();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CreateTestObject();\n";
   
   for (int iCount = 0; iCount < m_qstrlTestMethods.count(); ++iCount)
   {
      m_qstrSource += AddIndent(1);
      m_qstrSource += m_qstrlTestMethods[iCount] + "();\n";
   }

   m_qstrSource += AddIndent(1);
   m_qstrSource += "DeleteTestObject();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "DeleteTestObjectList();\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Sa 3. Dez 09:26:13 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateCreateTestObjectListMethod // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 3. Dez 09:26:13 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateCreateTestObjectListMethod()
{
   // Create or get standard Objectlist
   QString qstrClassName = m_pCodeGenerator->GetClassName();

   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "CreateTestObjectList", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "CreateTestObjectList", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = " + qstrClassName + "::GetObjectList();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "QVERIFY(pContainer != nullptr);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CdmClass* pCdmClass = pContainer->GetClassPtr();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(3);
   m_qstrSource += "QCOMPARE(" + m_rpCdmClass->GetKeyname() + ", pCdmClass->GetKeyname());\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "}\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Sa 3. Dez 09:26:42 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateCreateTestObjectClassMethod // private                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 3. Dez 09:26:42 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateCreateTestObjectClassMethod()
{
   // Create or get standard Objectlist
   QString qstrClassName = m_pCodeGenerator->GetClassName();

   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "CreateTestObject", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "CreateTestObject", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = " + qstrClassName + "::GetObjectList();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += qstrClassName + " TestObject = " + qstrClassName + "::Create(pContainer);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "QVERIFY(TestObject.IsValid())\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmObject = TestObject.GetObject();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Sa 3. Dez 09:30:55 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateDeleteTestObjectListMethod // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 3. Dez 09:30:55 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateDeleteTestObjectListMethod()
{
   // Create or get standard Objectlist
   QString qstrClassName = m_pCodeGenerator->GetClassName();

   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "DeleteTestObjectList", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "DeleteTestObjectList", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = " + qstrClassName + "::GetObjectList();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "QVERIFY(pContainer != nullptr);\n\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "QString qstrKeyname = pContainer->GetKeyname();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "CdmContainerManager* pCdmOLManager = pContainer->GetObjectListManager();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pContainer->SetDeleted();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pContainer->Commit();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "QVERIFY(pCdmOLManager->FindEmptyObjectListByKeyname(qstrKeyname) == nullptr);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Sa 3. Dez 09:31:00 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateDeleteTestObjectClassMethod // private                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 3. Dez 09:31:00 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateDeleteTestObjectClassMethod()
{
   // Create or get standard Objectlist
   QString qstrClassName = m_pCodeGenerator->GetClassName();
   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "DeleteTestObject", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "DeleteTestObject", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmObjectContainer* pContainer = " + qstrClassName + "::GetObjectList();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (pContainer)\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "qint64 lObjectId = m_rpCdmObject->GetId();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmObject->SetDeleted();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmObject->Commit();\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "QVERIFY(pContainer->FindObjectById(lObjectId) == nullptr);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Sa 3. Dez 09:32:12 2011-----------*
 * @method  CwmsCodeGeneratorTestC::GenerateTestCodeForMembers // public                          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 3. Dez 09:32:12 2011-----------*/
void CwmsCodeGeneratorTestC::GenerateTestCodeForMembers()
{
   if (CHKPTR(m_rpCdmClass))
   {
      QMap<qint64, CdmMember*> qmMembers;
      m_rpCdmClass->GetClassMemberMap(qmMembers);

      QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            CreateMemberTestMethod(pCdmMember);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 5. Dez 14:52:38 2011-----------*
 * @method  CwmsCodeGeneratorTestC::CreateMemberTestMethod   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 14:52:38 2011-----------*/
void CwmsCodeGeneratorTestC::CreateMemberTestMethod(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      
   }
}


/** +-=---------------------------------------------------------Mo 5. Dez 15:14:20 2011-----------*
 * @method  CwmsCodeGeneratorTestC::ReadTestData             // private                           *
 * @return  void                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @param   QStringList& p_rqstrlTestData                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 5. Dez 15:14:20 2011-----------*/
void CwmsCodeGeneratorTestC::ReadTestData(EdmValueType p_eDmValue, QStringList& p_rqstrlTestData)
{
   p_rqstrlTestData.clear();
   switch (p_eDmValue)
   {
   case eDmValueBool:
      p_rqstrlTestData.append("true");
      p_rqstrlTestData.append("false");
      break;
   case eDmValueCharacterDocument:
   case eDmValueString:
      p_rqstrlTestData.append("Das ist ein Test!");
      p_rqstrlTestData.append("Umlautetest Ä Ö Ü ß ");
      p_rqstrlTestData.append("Das ist ein längerer TEXT. Das ist ein längerer TEXT. Das ist ein längerer TEXT. Das ist ein längerer TEXT. Das ist ein längerer TEXT. Das ist ein längerer TEXT. Das ist ein längerer TEXT. ");
      p_rqstrlTestData.append("1");
      p_rqstrlTestData.append("1,4367");
      p_rqstrlTestData.append("1.4367");
      break;
   case eDmValueDate:
      p_rqstrlTestData.append("QDate(2011,11,25)");
      p_rqstrlTestData.append("QDate(2051,3,14)");
      p_rqstrlTestData.append("QDate(1998,8,21)");
      p_rqstrlTestData.append("QDate(1845,2,28)");
      break;
   case eDmValueDateTime:
      p_rqstrlTestData.append("QDateTime(QDate(2011,11,25), QTime(0, 0, 0, 1))");
      p_rqstrlTestData.append("QDateTime(QDate(2051,3,14), QTime(23, 59, 59, 99))");
      p_rqstrlTestData.append("QDateTime(QDate(1998,8,21), QTime(12, 59))");
      p_rqstrlTestData.append("QDateTime(QDate(1845,2,28), QTime(15, 26))");
      break;
   case eDmValueDouble:
   case eDmValueFloat:
      p_rqstrlTestData.append("0.0001");
      p_rqstrlTestData.append("4131678345.678");
      p_rqstrlTestData.append("5800.0");
      p_rqstrlTestData.append("-34.699989");
      break;
   case eDmValueInt:
   case eDmValueLong:
      p_rqstrlTestData.append("0");
      p_rqstrlTestData.append("4131678345");
      p_rqstrlTestData.append("5800");
      p_rqstrlTestData.append("-347897");
      break;
   case eDmValueTime:
      p_rqstrlTestData.append("QTime(0, 0, 0, 1)");
      p_rqstrlTestData.append("QTime(23, 59, 59, 99)");
      p_rqstrlTestData.append("QTime(12, 59)");
      break;
   default:
      p_rqstrlTestData.clear();
      break;
   }

}
