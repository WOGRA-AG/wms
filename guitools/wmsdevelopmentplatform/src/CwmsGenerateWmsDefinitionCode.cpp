/******************************************************************************
** WOGRA technologies Gmbh & Co KG Modul Information
** Modulename: CwmsGenerateWmsDefinitionCode.h
** Started Implementation: 2011/11/20
** Description:
** 
** This class implements the generator for wms definition code
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
*****************************************************************************/ 


// System and QT Includes
#include <QLinkedList>

// WMS Includes
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmLogging.h"

// own Includes
#include"CwmsGenerateWmsDefinitionCode.h"


/** +-=---------------------------------------------------------Mo 21. Nov 14:54:27 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::CwmsGenerateWmsDefinitionCode // public                *
 * @return                                                   //                                   *
 * @param   CdmDatabase* p_pCdmDatabase                      //                                   *
 * @param   QString p_qstrPath                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 14:54:27 2011----------*/
CwmsGenerateWmsDefinitionCode::CwmsGenerateWmsDefinitionCode(CdmScheme* p_pCdmDatabase,
                                                             QString p_qstrPath)
: CwmsCodeGeneratorCBase(p_qstrPath, ""),
   m_rpCdmDatabase(p_pCdmDatabase)
{
   m_qstrClassName = GenerateCodeMemberName(m_rpCdmDatabase->GetSchemeName());
}

/** +-=---------------------------------------------------------Mo 21. Nov 14:45:36 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::~CwmsGenerateWmsDefinitionCode // public, virtual      *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsGenerateWmsDefinitionCode                                 *
 *----------------last changed: --------------------------------Mo 21. Nov 14:45:36 2011----------*/
CwmsGenerateWmsDefinitionCode::~CwmsGenerateWmsDefinitionCode()
{
}


/** +-=---------------------------------------------------------Mo 21. Nov 14:54:48 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateCode      // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 14:54:48 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateCode()
{
   AddIncludesAndForwards();
   OpenClass();
   GenerateSourceHeader();
   GenerateConstructor();
   GenerateDestructor();
   GenerateDatabaseCode();
   GenerateClassesCode();
   GenerateObjectListsCode();
   GenerateDataStructureMethod(); // must be the last call before closing the class
   CloseClass();
}

/** +-=---------------------------------------------------------Di 22. Nov 19:36:54 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::AddIncludesAndForwards // private                      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:36:54 2011----------*/
void CwmsGenerateWmsDefinitionCode::AddIncludesAndForwards()
{
   AddForward("CdmContainerManager");
   AddForward("CdmClassManager");
   AddForward("CdmDatabase");
   AddSourceInclude("CdmClassManager.h");
   AddSourceInclude("CdmContainerManager.h");
   AddSourceInclude("CdmScheme.h");
   AddSourceInclude("CdmClass.h");
   AddSourceInclude("CdmMember.h");
   AddSourceInclude("CdmObjectContainer.h");
}

/** +-=---------------------------------------------------------Di 22. Nov 18:58:26 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateConstructor // private                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:58:26 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateConstructor()
{
   GenerateConstructorSource();
   AddMemberVariable("CdmDatabase*", "m_rpCdmDatabase");
   AddMemberVariable("CdmContainerManager*", "m_rpCdmOLManager");
   AddMemberVariable("CdmClassManager*", "m_rpCdmClassManager");
   AddMemberVariable("QString", "m_qstrDatabaseName");
   GenerateConstructorHeader(m_qstrClassName, "QString p_qstrDatabaseName");
}

/** +-=---------------------------------------------------------Di 22. Nov 19:18:39 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateConstructorSource // private                   *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 19:18:39 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateConstructorSource()
{
   m_qstrSource += GenerateConstructorSourceHead(m_qstrClassName, "QString p_qstrDatabaseName");
   m_qstrSource += " : m_rpCdmDatabase(nullptr),\n";
   m_qstrSource += "   m_rpCdmOLManager(nullptr),\n";
   m_qstrSource += "   m_rpCdmClassManager(nullptr),\n";
   m_qstrSource += "   m_qstrDatabaseName(p_qstrDatabaseName)\n";
   m_qstrSource += "{\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Di 22. Nov 18:58:41 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateDestructor // private                          *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 22. Nov 18:58:41 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateDestructor()
{
   m_qstrSource += GenerateDestructorSource(m_qstrClassName);
   m_qstrSource += "{\n";
   m_qstrSource += "   // nothing to do here ;-)\n";
   m_qstrSource += "}\n";

   m_qstrHeader += GenerateDestructorHeader(m_qstrClassName);
}


/** +-=---------------------------------------------------------Mo 21. Nov 15:11:35 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateDatabaseCode // private                        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:11:35 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateDatabaseCode()
{
   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "GenerateDatabase", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "GenerateDatabase", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "CdmManager* pCdmManager = CdmSessionManager::GetManager();\n";
   m_qstrSource += "\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(pCdmManager))";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "pCdmManager->CreateDatabase(m_qstrDatabaseName)\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmDatabase = pCdmManager->FindDatabaseByName(m_qstrDatabaseName)\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmClassManager = pCdmManager->GetClassManager(m_qstrDatabaseName);\n";
   m_qstrSource += AddIndent(2);
   m_qstrSource += "m_rpCdmOLManager = pCdmManager->GetObjectListManager(m_qstrDatabaseName);\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:11:46 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateClassesCode // private                         *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:11:46 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateClassesCode()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(m_rpCdmDatabase->GetId());
      QLinkedList<CdmClass*> qllClasses;
      pCdmClassManager->GetClassList(qllClasses);
      GenerateCreateClassesByNameCode(qllClasses);

      QLinkedList<CdmClass*>::iterator qllIt = qllClasses.begin();
      QLinkedList<CdmClass*>::iterator qllItEnd = qllClasses.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         CdmClass* pCdmClass = *qllIt;
         GenerateClassDetailsMethod(pCdmClass);
      }
   }
}

/** +-=---------------------------------------------------------Mi 23. Nov 10:47:35 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateCreateClassesByNameCode // private             *
 * @return  void                                             //                                   *
 * @param   QLinkedList<CdmClass*>& p_rqllClasses            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 10:47:35 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateCreateClassesByNameCode(QLinkedList<CdmClass*>& p_rqllClasses)
{
   m_qstrHeader += GenerateMethodHeadHeader("private", "void", "GenerateClassesByName", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "GenerateClassesByName", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "if (CHKPTR(m_rpCdmClassManager))\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "{\n";

   QLinkedList<CdmClass*>::iterator qllIt = p_rqllClasses.begin();
   QLinkedList<CdmClass*>::iterator qllItEnd = p_rqllClasses.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      CdmClass* pCdmClass = *qllIt;
      m_qstrSource += AddIndent(2);
      m_qstrSource += "m_rpCdmClassManager->CreateClass(\"" + pCdmClass->GetKeyname() + "\");\n";
   }

   m_qstrSource += AddIndent(1);
   m_qstrSource += "}\n";
   m_qstrSource += "}\n";
}

/** +-=---------------------------------------------------------Mi 23. Nov 10:59:32 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateClassDetailsMethod // private                  *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 10:59:32 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateClassDetailsMethod(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QString qstrMethodName = "Create" + GenerateCodeMemberName(p_pCdmClass->GetKeyname());
      m_qstrlMethodsToCall.append(qstrMethodName);
      m_qstrHeader += GenerateMethodHeadHeader("private", "void", qstrMethodName, "");
      m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, qstrMethodName, "");
      m_qstrSource += "{\n";
      m_qstrSource += AddIndent(1);
      m_qstrSource += "CdmClass* pCdmClass = m_rpCdmClassManager->FindClassByKeyname(\""+ p_pCdmClass->GetKeyname() + "\");\n";
      m_qstrSource += AddIndent(1);
      m_qstrSource += "if (CHKPTR(pCdmClass))";
      m_qstrSource += AddIndent(1);
      m_qstrSource += "{\n";
      m_qstrSource += AddIndent(2);
      m_qstrSource += "pCdmClass->SetCaption(\"" + p_pCdmClass->GetCaption() + "\");\n";
      m_qstrSource += AddIndent(2);
      m_qstrSource += "pCdmClass->SetCaptionMember(\"" + p_pCdmClass->GetCaptionMemberKeyname() + "\");\n";
      m_qstrSource += AddIndent(2);
      m_qstrSource += "pCdmClass->SetComment(\"" + p_pCdmClass->GetComment() + "\");\n";
      m_qstrSource += AddIndent(2);

      if (p_pCdmClass->IsAbstract())
      {
         m_qstrSource += "pCdmClass->SetAbstract(true);\n";
      }
      else
      {
         m_qstrSource += "pCdmClass->SetAbstract(false);\n";
      }

      AddMembers(p_pCdmClass);
      AddBaseClassCode(p_pCdmClass);
      m_qstrSource += AddIndent(2);
      m_qstrSource += "pCdmClass->Commit();\n";
      m_qstrSource += AddIndent(1);
      m_qstrSource += "}\n";
      m_qstrSource += "}\n";
   }
}

/** +-=---------------------------------------------------------Mi 23. Nov 11:31:49 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::AddMembers        // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:31:49 2011----------*/
void CwmsGenerateWmsDefinitionCode::AddMembers(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QMap<long, CdmMember*> qmMembers;
      p_pCdmClass->GetClassMemberMap(qmMembers);

      m_qstrSource += AddIndent(2);
      m_qstrSource += "CdmMember* pCdmMember = nullptr;";

      QMap<long, CdmMember*>::iterator qmIt = qmMembers.begin();
      QMap<long, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for (; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            AddMember(pCdmMember);
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 23. Nov 11:32:27 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::AddMember         // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:32:27 2011----------*/
void CwmsGenerateWmsDefinitionCode::AddMember(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      m_qstrSource += AddIndent(2);
      m_qstrSource += "pCdmMember = pCdmClass->CreateMember(\"" + p_pCdmMember->GetKeyname()+ "\", ";
      m_qstrSource += GetValueTypeAsString(p_pCdmMember->GetValueType()) + ", ";

      if (p_pCdmMember->IsMust())
      {
         m_qstrSource += "true, ";
      }
      else
      {
         m_qstrSource += "false, ";
      }

      m_qstrSource += QString::number(p_pCdmMember->GetSize());
      m_qstrSource += ");\n\n";
      m_qstrSource += AddIndent(2);
      m_qstrSource += "if (CHKPTR(pCdmMember))\n";
      m_qstrSource += AddIndent(2);
      m_qstrSource += "{\n";
      m_qstrSource += AddIndent(3);
      m_qstrSource += "pCdmMember->SetCaption(\"" + p_pCdmMember->GetCaption() + "\");\n";
      m_qstrSource += AddIndent(3);
      m_qstrSource += "pCdmMember->SetComment(\"" + p_pCdmMember->GetComment() + "\");\n";
     
      if (p_pCdmMember->GetClassReference() > 0)
      {
         CdmClassManager* pCdmClassManager = p_pCdmMember->GetClassManager();

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(p_pCdmMember->GetClassReference());

            if (CHKPTR(pCdmClass))
            {
                m_qstrSource += AddIndent(3);
                m_qstrSource += "pCdmMember->SetClassReference(\"" + pCdmClass->GetKeyname() + "\");\n";

                if (p_pCdmMember->IsOwner())
                {
                   m_qstrSource += AddIndent(3);
                   m_qstrSource += "pCdmMember->SetOwner(true);\n";
                }
            }
         }
      }

      AddDefaultValue(p_pCdmMember);
      m_qstrSource += AddIndent(2);
      m_qstrSource += "}\n\n";
   }
}

/** +-=---------------------------------------------------------Mi 23. Nov 12:38:07 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::AddDefaultValue   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 12:38:07 2011----------*/
void CwmsGenerateWmsDefinitionCode::AddDefaultValue(CdmMember* p_pCdmMember)
{
   if (CHKPTR(p_pCdmMember))
   {
      QVariant qvDefault = p_pCdmMember->GetVariant();
      m_qstrSource += AddIndent(3);

      switch (p_pCdmMember->GetValueType())
      {
      case eDmValueBool:

         if (qvDefault.toBool())
         {
            m_qstrSource += "pCdmMember->SetDefaultValue(true);\n";           
         }
         else
         {
            m_qstrSource += "pCdmMember->SetDefaultValue(false);\n";
         }
         break;
      case eDmValueInt:
          m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      case eDmValueLong:
          m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      case eDmValueFloat:
          m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      case eDmValueDouble:
          m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      case eDmValueString:
          m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      case eDmValueDate:
          m_qstrSource += "pCdmMember->SetDefaultValue(QDate(" + qvDefault.toString() + "));\n";
         break;
      case eDmValueTime:
          m_qstrSource += "pCdmMember->SetDefaultValue(QTime(" + qvDefault.toString() + "));\n";
         break;
      case eDmValueDateTime:
          m_qstrSource += "pCdmMember->SetDefaultValue(QDateTime(" + qvDefault.toString() + "));\n";
         break;
      case eDmValueCharacterDocument:
         m_qstrSource += "pCdmMember->SetDefaultValue(" + qvDefault.toString() + ");\n";
         break;
      default:
          break;
      };
   }
}

/** +-=---------------------------------------------------------Mi 23. Nov 12:24:36 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GetValueTypeAsString // public                         *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment This method generates from the Value a string translation.                            *
 *----------------last changed: --------------------------------Mi 23. Nov 12:24:36 2011----------*/
QString CwmsGenerateWmsDefinitionCode::GetValueTypeAsString(EdmValueType p_eDmValue)
{
   QString qstrValue;

   switch(p_eDmValue)
   {
   case eDmValueBool:
      qstrValue = "eDmValueBool";
      break;
   case eDmValueInt:
      qstrValue = "eDmValueInt";
      break;
   case eDmValueLong:
      qstrValue = "eDmValueLong";
      break;
   case eDmValueFloat:
      qstrValue = "eDmValueFloat";
      break;
   case eDmValueDouble:
      qstrValue = "eDmValueDouble";
      break;
   case eDmValueString:
      qstrValue = "eDmValueString";
      break;
   case eDmValueDate:
      qstrValue = "eDmValueDate";
      break;
   case eDmValueTime:
      qstrValue = "eDmValueTime";
      break;
   case eDmValueDateTime:
      qstrValue = "eDmValueDateTime";
      break;
   case eDmValueObjectRef:
      qstrValue = "eDmValueObjectRef";
      break;
   case eDmValueContainerRef:
      qstrValue = "eDmValueObjectListRef";
      break;
   case eDmValueCounter:
      qstrValue = "eDmValueCounter";
      break;
   case eDmValueBinaryDocument:
      qstrValue = "eDmValueBinaryDocument";
      break;
   case eDmValueCharacterDocument:
      qstrValue = "eDmValueCharacterDocument";
      break;
   case eDmValueListDouble:
      qstrValue = "eDmValueListDouble";
      break;
   case eDmValueListInt:
      qstrValue = "eDmValueListInt";
      break;
   case eDmValueListString:
      qstrValue = "eDmValueListString";
      break;
   case eDmValueDictIntInt:
      qstrValue = "eDmValueDictIntInt";
      break;
   case eDmValueDictIntDouble:
      qstrValue = "eDmValueDictIntDouble";
      break;
   case eDmValueDictIntString:
      qstrValue = "eDmValueDictIntString";
      break;
   case eDmValueDictStringDouble:
      qstrValue = "eDmValueDictStringDouble";
      break;
   case eDmValueDictStringInt:
      qstrValue = "eDmValueDictStringInt";
      break;
   case eDmValueDictStringString:
      qstrValue = "eDmValueDictStringString";
      break;
   default:
       break;
   };

   return qstrValue;
}


/** +-=---------------------------------------------------------Mi 23. Nov 11:18:18 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::AddBaseClassCode  // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Nov 11:18:18 2011----------*/
void CwmsGenerateWmsDefinitionCode::AddBaseClassCode(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      CdmClassManager* pCdmClassManager = p_pCdmClass->GetClassManager();

      if (CHKPTR(pCdmClassManager))
      {
         const QMap<long,long>& qmBaseClasses = p_pCdmClass->GetBaseClasses();
         QMap<long,long>::const_iterator qmIt = qmBaseClasses.begin();
         QMap<long,long>::const_iterator qmItEnd = qmBaseClasses.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(qmIt.value());

            if (pCdmClass)
            {
               m_qstrSource += AddIndent(2);
               m_qstrSource += "pCdmClass->AddBaseClass(\"" + pCdmClass->GetKeyname() + "\");+\n";
            }
         }
      }      
   }
}

/** +-=---------------------------------------------------------Mo 21. Nov 15:12:36 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateObjectListsCode // private                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 21. Nov 15:12:36 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateObjectListsCode()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(m_rpCdmDatabase->GetId());
      QLinkedList<CdmClass*> qllClasses;
      pCdmClassManager->GetClassList(qllClasses);
      GenerateCreateClassesByNameCode(qllClasses);

      QLinkedList<CdmClass*>::iterator qllIt = qllClasses.begin();
      QLinkedList<CdmClass*>::iterator qllItEnd = qllClasses.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         CdmClass* pCdmClass = *qllIt;

         if (CHKPTR(pCdmClass))
         {
            GenerateObjectListMethod(pCdmClass);
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 2. Dez 12:49:27 2011-----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateObjectListMethod // private                    *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 2. Dez 12:49:27 2011-----------*/
void CwmsGenerateWmsDefinitionCode::GenerateObjectListMethod(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager))
      {
         CdmContainerManager* pContainerManager = pCdmManager->GetContainerManager(m_rpCdmDatabase->GetId());

         if (CHKPTR(pContainerManager))
         {
            QLinkedList<QString> qllObjectLists;
            qllObjectLists = pContainerManager->GetContainerList(p_pCdmClass->GetId());

            if (!qllObjectLists.isEmpty())
            {
               QString qstrMethodName = "Create" + GenerateCodeMemberName(p_pCdmClass->GetKeyname()) + "ObjectLists";
               m_qstrlMethodsToCall.append(qstrMethodName);
               m_qstrHeader += GenerateMethodHeadHeader("private", "void", qstrMethodName, "");
               m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, qstrMethodName, "");

               m_qstrSource += AddIndent(1);
               m_qstrSource += "if (CHKPTR(m_rpCdmOLManager))";
               m_qstrSource += AddIndent(1);
               m_qstrSource += "{\n";
               
               QLinkedList<QString>::iterator qllIt = qllObjectLists.begin();
               QLinkedList<QString>::iterator qllItEnd = qllObjectLists.end();

               for (; qllIt != qllItEnd; ++qllIt)
               {
                  m_qstrSource += AddIndent(2);
                  m_qstrSource += "QString qstrOLName = \"" + *qllIt + "\";\n";
                  m_qstrSource += AddIndent(2);
                  m_qstrSource += "m_rpCdmOLManager->CreateObjectList(\"" + p_pCdmClass->GetKeyname() +"\", ";
                  m_qstrSource += ", qstrOLName, \"" + p_pCdmClass->GetCaption() + "\", "");\n";
               }

               m_qstrSource += AddIndent(1);
               m_qstrSource += "}\n";
            }

            m_qstrSource += "}\n";
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 25. Nov 15:36:47 2011----------*
 * @method  CwmsGenerateWmsDefinitionCode::GenerateDataStructureMethod // private                 *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 25. Nov 15:36:47 2011----------*/
void CwmsGenerateWmsDefinitionCode::GenerateDataStructureMethod()
{
   m_qstrHeader += GenerateMethodHeadHeader("public", "void", "GenerateDataStructure", "");
   m_qstrSource += GenerateMethodHeadSource("void", m_qstrClassName, "GenerateDataStructure", "");
   m_qstrSource += "{\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "GenerateDatabase();\n";
   m_qstrSource += AddIndent(1);
   m_qstrSource += "GenerateClassesByName();\n";
  
   for (int iPos = 0; iPos < m_qstrlMethodsToCall.count(); ++iPos)
   {
      QString qstrMethod = m_qstrlMethodsToCall[iPos];
      m_qstrSource += AddIndent(1);
      m_qstrSource += qstrMethod + ";\n";
   }

   m_qstrSource += "}\n";
}
