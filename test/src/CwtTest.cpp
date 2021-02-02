/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtTest.cpp
 ** Started Implementation: 2012/04/20
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <qdir.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmValueObjectRef.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmQueryEnhanced.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "wmsdefines.h"


// own Includes
#include "CwtTest.h"

long CwtTest::mem = 0;

/** +-=---------------------------------------------------------Fr 20. Apr 10:40:12 2012----------*
 * @method  CwtTest::CwtTest                                 // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Apr 10:40:12 2012----------*/
CwtTest::CwtTest()
: CwtTestBase(eBmsTestModeDB),
  m_lObjectId(0),
  m_lClassId(0),
  m_iObjectToCreate(1)
{
}

/** +-=---------------------------------------------------------Fr 20. Apr 10:40:20 2012----------*
 * @method  CwtTest::~CwtTest                                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwtTest                                                       *
 *----------------last changed: --------------------------------Fr 20. Apr 10:40:20 2012----------*/
CwtTest::~CwtTest()
{
}

/** +-=---------------------------------------------------------Do 26. Apr 11:11:02 2012----------*
 * @method  CwtTest::initTestCase                            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Apr 11:11:02 2012----------*/
void CwtTest::initTestCase()
{
   m_qTimeStart = QTime::currentTime();
   QString qstr = "Start: " + m_qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());
   
   CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
   int iSessionId = 0;
   iSessionId = pFactory->CreateNewSession("admin", "admin");
   QVERIFY(iSessionId > 0);
   CdmDataProvider* pCdmDataProvider = GetDataProvider();
   QVERIFY(pCdmDataProvider != nullptr);
   m_qstrDbName = "Test_" + QString::number(iSessionId);
   pCdmDataProvider->RemoveScheme(m_qstrDbName);
   pCdmDataProvider->CreateScheme(m_qstrDbName);
   CdmScheme* pCdmDatabase = pCdmDataProvider->GetCurrentScheme();
   QVERIFY(pCdmDatabase != nullptr);
   QString qstrEnglish = "English";
   QString qstrFrancaise = "Francaise";
   pCdmDatabase->AddLanguage(qstrEnglish);
   pCdmDatabase->AddLanguage(qstrFrancaise);
}

/** +-=---------------------------------------------------------Mi 23. Mai 14:53:09 2012----------*
 * @method  CwtTest::FindAdminUserSlot                       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 23. Mai 14:53:09 2012----------*/
void CwtTest::FindAdminUserSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start FindAdminUserSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = GetDataProvider();
   QVERIFY(pCdmDataProvider != nullptr);

   CumUserManager* pUserManager = pCdmDataProvider->GetUserManager();
   QVERIFY(pUserManager != nullptr);

   CumUser* pUser = pUserManager->FindUserById(1);

   QVERIFY(pUser != nullptr);
   QVERIFY(pUser->GetLogin() == "admin");
   QVERIFY(pUser->GetLastName() == "admin");

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End FindAdminUserSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration FindAdminUserSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 10. Mai 19:12:21 2012----------*
 * @method  CwtTest::CheckDatabaseListSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Mai 19:12:21 2012----------*/
void CwtTest::CheckDatabaseListSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start CheckDatabaseListSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

   if (pCdmDataProvider)
   {
      IdmDataAccess* pIdmDataAccess = pCdmDataProvider->GetDataAccess();

      if (pIdmDataAccess)
      {
         QLinkedList<QString> qllDatabases;
         pIdmDataAccess->GetSchemeList(qllDatabases);

         QVERIFY(qllDatabases.count() > 0);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CheckDatabaseListSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CheckDatabaseListSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Mi 6. Feb 10:19:33 2013-----------*
 * @method  CwtTest::CheckUser                               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 10:19:33 2013-----------*/
void CwtTest::CheckUser()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start CheckUserListSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

   if (pCdmDataProvider)
   {
      CumUserManager* pUserManager = pCdmDataProvider->GetUserManager();
      QVERIFY(pUserManager != nullptr);
      int iUserId = 0;

      if (m_eTestMode != eBmsTestModeWeb)
      {
          CumUser* pUser = new CumUser(pUserManager);
          QString qstrUserValues = "qwertz";
          pUser->SetActive(true);
          pUser->SetFirstName(qstrUserValues);
          pUser->SetLastName(qstrUserValues);
          pUser->SetLogin(qstrUserValues);
          pUser->SetPassword(qstrUserValues);
          pUser->SetEmail(qstrUserValues);
          pUser->SetSchemeIndependent(true);
          pUser->SetAdministrator(false);

         iUserId = pUserManager->CreateUser(pUser);
         QVERIFY(iUserId > 0);

         pUser = pUserManager->FindUserById(iUserId);
         QVERIFY(pUser != nullptr);
      }

      QLinkedList<CumUser*> qllUsers;
      pUserManager->GetUserListUnmanaged(qllUsers);
      QVERIFY(qllUsers.count() > 0);

      if (m_eTestMode != eBmsTestModeWeb)
      {
         QVERIFY(pUserManager->DeleteUser("qwertz") > 0);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CheckUserListSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CheckUserListSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Mi 6. Feb 10:19:43 2013-----------*
 * @method  CwtTest::CheckUserGroup                          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 6. Feb 10:19:43 2013-----------*/
void CwtTest::CheckUserGroup()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start CheckUsergroupListSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

   if (pCdmDataProvider)
   {
      CumUserManager* pUserManager = pCdmDataProvider->GetUserManager();
      QVERIFY(pUserManager != nullptr);
      int iUsergroup = 0;

      if (m_eTestMode != eBmsTestModeWeb)
      {
         iUsergroup = pUserManager->CreateUserGroup("Testgroup");
         QVERIFY(iUsergroup > 0);

         CumUserGroup* pGroup = pUserManager->FindUserGroupById(iUsergroup);
         QVERIFY(pGroup != nullptr);
      }

      QLinkedList<CumUserGroup*> qllUserGroups;
      pUserManager->GetUserGroupList(qllUserGroups);
      QVERIFY(qllUserGroups.count() > 0);

      if (m_eTestMode != eBmsTestModeWeb)
      {
         QVERIFY(pUserManager->DeleteUserGroup(iUsergroup) > 0);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CheckUserGroupListSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CheckUserGroupListSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Fr 20. Apr 11:37:25 2012----------*
 * @method  CwtTest::LoadDatabaseSlot                        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Apr 11:37:25 2012----------*/
void CwtTest::LoadDatabaseSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start LoadDatabaseSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = GetDataProvider();
   QVERIFY(pCdmDataProvider != nullptr);
   
   pCdmDataProvider->LoadScheme(m_qstrDbName);

   CdmScheme* pCdmDatabase = pCdmDataProvider->GetCurrentScheme();
   QVERIFY(pCdmDatabase != nullptr);
   QVERIFY(pCdmDatabase->GetSchemeName() == m_qstrDbName);

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End LoadDatabaseSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration LoadDatabaseSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Mo 23. Apr 15:33:08 2012----------*
 * @method  CwtTest::CreateClassSlot                         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Apr 15:33:08 2012----------*/
void CwtTest::CreateClassSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start CreateClassSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmClassManager* pCdmClassManager = GetClassManager();

   if (pCdmClassManager)
   {
      CdmClass* pCdmClass = pCdmClassManager->CreateClass("TestBaseClass");
      QVERIFY(pCdmClass != nullptr);

      if (pCdmClass)
      {
         CdmClassGroup* pCdmGroup1 = pCdmClass->CreateGroup("Group1", 1);
         CdmClassGroup* pCdmGroup2 = pCdmClass->CreateGroup("Group2", 1);

         m_lClassId = pCdmClass->GetId();
         pCdmClass->SetCaption("Test Basis Klasse");
         pCdmClass->SetComment("Das ist die Basis für die Testklasse");

         CdmMember* pCdmMember = pCdmClass->CreateMember("String", eDmValueString, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Zeichenkette");
            pCdmMember->SetComment("Das ist eine Zeichenkette.");
            pCdmMember->SetGroup(pCdmGroup1);
            pCdmMember->SetTranslation("English", "String", "a string of chars");
         }

         pCdmMember = pCdmClass->CreateMember("Int", eDmValueInt, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Ganze Zahl");
            pCdmMember->SetComment("Das ist eine ganze Zahl.");
            pCdmMember->SetGroup(pCdmGroup2);
            pCdmMember->SetTranslation("English", "Number", "a number");
         }

         pCdmMember = pCdmClass->CreateMember("Double", eDmValueDouble, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Zahl mit doppelter Genauigkeit");
            pCdmMember->SetComment("Das ist eine Zahl mit doppelter Genauigkeit.");
            pCdmMember->SetGroup(pCdmGroup1);
            pCdmMember->SetTranslation("English", "Double", "a double");
         }

         pCdmMember = pCdmClass->CreateMember("Date", eDmValueDate, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Datum");
            pCdmMember->SetComment("Das ist ein Datum.");
            pCdmMember->SetGroup(pCdmGroup2);
            pCdmMember->SetTranslation("English", "Date", "a date");
         }

         pCdmMember = pCdmClass->CreateMember("DateTime", eDmValueDateTime, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Zeitstempel");
            pCdmMember->SetComment("Das ist ein Zeitstempel.");
            pCdmMember->SetGroup(pCdmGroup2);
            pCdmMember->SetTranslation("English", "Timestamp", "a timestamp");
         }

         pCdmMember = pCdmClass->CreateMember("Time", eDmValueTime, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Uhrzeit");
            pCdmMember->SetComment("Das ist eine Uhrzeit.");
            pCdmMember->SetGroup(pCdmGroup1);
            pCdmMember->SetTranslation("English", "Time", "a time");
         }

         pCdmMember = pCdmClass->CreateMember("Bool", eDmValueBool, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Boolscher Ausdruck");
            pCdmMember->SetComment("Das ist ein boolscher Ausdruck (wahr, falsch).");
            pCdmMember->SetTranslation("English", "Bool", "true or false");
         }

         pCdmMember = pCdmClass->CreateMember("StringList", eDmValueListString, false, 0);

         if (pCdmMember)
         {
            pCdmMember->SetCaption("Liste von Zeichenketten");
            pCdmMember->SetComment("Das ist eine Liste von Zeichenketten.");
            pCdmMember->SetTranslation("English", "StringList", "a list of strings");
         }
         
         pCdmClass->Commit();
         pCdmClass = pCdmClassManager->CreateClass("TestClass");

         if (pCdmClass)
         {
            pCdmClass->AddBaseClass("TestBaseClass");
            pCdmClass->SetCaption("Test Basis Klasse");
            pCdmClass->SetComment("Das ist die Basis für die Testklasse");

            CdmMember* pCdmMember = pCdmClass->CreateMember("ObjReferenceNoOwner", eDmValueObjectRef, false, 0);

            if (pCdmMember)
            {
               pCdmMember->SetCaption("Zeichenkette abgeleitet");
               pCdmMember->SetComment("Das ist eine Zeichenkette in der abgeleiteten Klasse.");
               pCdmMember->SetClassReference("TestBaseClass");
               pCdmMember->SetOwner(false);
            }

            pCdmMember = pCdmClass->CreateMember("ObjListReferenceOwner", eDmValueContainerRef, false, 0);

            if (pCdmMember)
            {
               pCdmMember->SetCaption("ObjListRefOwner");
               pCdmMember->SetComment("Reference auf eine Objektliste mit Ownerflag.");
               pCdmMember->SetClassReference("TestBaseClass");
               pCdmMember->SetOwner(true);
            }

			pCdmMember = pCdmClass->CreateMember("ObjReferenceOwner", eDmValueObjectRef, false, 0);

			if (pCdmMember)
			{
				pCdmMember->SetCaption("ObjectRef mit Ownerflag");
				pCdmMember->SetComment("ObjRef mit Ownerflag");
				pCdmMember->SetClassReference("TestBaseClass");
				pCdmMember->SetOwner(true);
			}

            pCdmClass->Commit();
         }
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CreateClassSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CreateClassSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Mo 10. Dez 15:26:15 2012----------*
 * @method  CwtTest::CheckClassUrisSlot                      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Dez 15:26:15 2012----------*/
void CwtTest::CheckClassUrisSlot()
{
   CdmClassManager* pCdmClassManager = GetClassManager();

   if (pCdmClassManager)
   {
      CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname("TestBaseClass");

      if (CHKPTR(pCdmClass))
      {
         CdmDataProvider* pManager = GetDataProvider();

         if (CHKPTR(pManager))
         {
            CdmLocatedElement* pTemp = pManager->GetUriObject(pCdmClass->GetUri());
            QVERIFY(pTemp == pCdmClass);
            pTemp = pManager->GetUriObject(pCdmClass->GetUri());
            QVERIFY(pTemp == pCdmClass);
            QString qstrKeyname = pManager->GetClassKeynameFromUri(pCdmClass->GetUri());
            QVERIFY(qstrKeyname == pCdmClass->GetKeyname());
         }
      }
   }
}

/** +-=---------------------------------------------------------Fr 20. Apr 11:33:53 2012----------*
 * @method  CwtTest::CreateObjectListSlot                    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Apr 11:33:53 2012----------*/
void CwtTest::CreateObjectListSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start CreateObjectListSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      QString qstrOLName = "TestOL";
      int iSuccess = 0;

      iSuccess = pCdmOLManager->CreateContainer("TestClass", qstrOLName);

      QVERIFY(iSuccess > 0);

      if (iSuccess > 0)
      {
         CdmObjectContainer* pContainer = nullptr;
         pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);

         QVERIFY(pContainer != nullptr);
         QVERIFY(pContainer->GetId() > 0);
     }

     qstrOLName += "Base";
	  iSuccess = pCdmOLManager->CreateContainer("TestBaseClass", qstrOLName);

	  QVERIFY(iSuccess > 0);

	  if (iSuccess > 0)
	  {
		  CdmObjectContainer* pContainer = nullptr;
		  pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);

		  QVERIFY(pContainer != nullptr);
		  QVERIFY(pContainer->GetId() > 0);
	  }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CreateObjectListSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CreateObjectListSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:04:21 2012----------*
 * @method  CwtTest::CreateObjectByWebServiceSlot                        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:04:21 2012----------*/
void CwtTest::CreateObjectByWebServiceSlot()
{
   if (m_eTestMode == eBmsTestModeWeb)
   {
      QTime qTimeStart = QTime::currentTime();
      QString qstr = "Start create single object: " + qTimeStart.toString();
      qDebug(qstr.toLocal8Bit());

      CdmContainerManager* pCdmOLManager = GetContainerManager();
      QString qstrOLName = "TestOL";
      QVERIFY(pCdmOLManager != nullptr);

      if (pCdmOLManager)
      {
         CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);

         QVERIFY(pContainer != nullptr);
         QVERIFY(pContainer->GetId() > 0);
         CdmLocatedElement* pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pContainer->GetUri());
         QVERIFY(pTemp == pContainer);
         pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pContainer->GetUri());
         QVERIFY(pTemp == pContainer);
         int iCounter = 0;
      

          QString qstrMessage = "Generating " + QString::number(iCounter + 1) + ". object.";
          qDebug(qstrMessage.toLocal8Bit());
          QTime qTimeStartObj = QTime::currentTime();
          QString qstr = "Start CreateObject: " + qTimeStartObj.toString();
          qDebug(qstr.toLocal8Bit());
        IdmDataAccess* pDataAccess = pCdmOLManager->GetDataProvider()->GetDataAccess();
          CdmObject* pCdmObject = pDataAccess->CreateObject(pContainer);
          QVERIFY(pCdmObject != nullptr);
          QVERIFY(pCdmObject->GetId() > 0);

          if (pCdmObject)
          {
             if (iCounter == 0)
             {
                 m_lObjectId = pCdmObject->GetId();
             }

	         CdmValue* pValue = pCdmObject->GetValue("ObjReferenceOwner");
	         QVERIFY(pValue != nullptr);
	         QVERIFY(((CdmValueObjectRef*)pValue)->GetValue() > 0);

            QTime qTimeEnd = QTime::currentTime();
            qstr = "End CreateObjectSlot: " + qTimeEnd.toString();
            qDebug(qstr.toLocal8Bit());
            qstr = "Duration CreateObjectSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
            qDebug(qstr.toLocal8Bit());
         }
      }
   }
   else
   {
      QVERIFY(0 == 0);
   }
}


/** +-=---------------------------------------------------------Sa 28. Apr 13:04:21 2012----------*
 * @method  CwtTest::CreateObjectSlot                        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:04:21 2012----------*/
void CwtTest::CreateObjectSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start create single object: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);

      QVERIFY(pContainer != nullptr);
      QVERIFY(pContainer->GetId() > 0);
      CdmLocatedElement* pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pContainer->GetUri());
      QVERIFY(pTemp == pContainer);
      pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pContainer->GetUri());
      QVERIFY(pTemp == pContainer);
      int iCounter = 0;
      

      for(; iCounter < m_iObjectToCreate; ++iCounter)
      {
         QString qstrMessage = "Generating " + QString::number(iCounter + 1) + ". object.";
         qDebug(qstrMessage.toLocal8Bit());
         QTime qTimeStartObj = QTime::currentTime();
         QString qstr = "Start CreateObject: " + qTimeStartObj.toString();
         qDebug(qstr.toLocal8Bit());

         CdmObject* pCdmObject = pContainer->CreateNewObject();
         QVERIFY(pCdmObject != nullptr);
         QVERIFY(pCdmObject->GetId() > 0);

         if (pCdmObject)
         {
            if (iCounter == 0)
            {
               m_lObjectId = pCdmObject->GetId();
            }
            
            QVERIFY(pCdmObject->SetValue("String", "String" + QString::number(iCounter)) > 0);
            QVERIFY(pCdmObject->SetValue("Date", QDate::currentDate().addDays(iCounter)) > 0);
            QVERIFY(pCdmObject->SetValue("Int", 789 + iCounter) > 0);
            QVERIFY(pCdmObject->SetValue("Double", 123.456 + iCounter) > 0);

            if (iCounter % 2 == 0)
            {
               QVERIFY(pCdmObject->SetValue("Bool", true) > 0);
            }
            else
            {
               QVERIFY(pCdmObject->SetValue("Bool", false) > 0);
            }
            
            QTime qTime = QTime::currentTime().addSecs(iCounter);

            if (iCounter == 0)
            {
               m_qTestTimeWithPreparation = qTime;
            }

            QVERIFY(pCdmObject->SetValue("Time", qTime) > 0);
            QDateTime qDateTime = QDateTime::currentDateTime().addDays(iCounter);

            if (iCounter == 0)
            {
               m_qdTestDateTime = qDateTime;
            }

            QVERIFY(pCdmObject->SetValue("DateTime", qDateTime) > 0);
            int iResult = pCdmObject->Commit();
            QVERIFY(iResult > 0);
         }

         QTime qTimeEndObj = QTime::currentTime();
         qstr = "End create single object: " + qTimeEndObj.toString();
         qDebug(qstr.toLocal8Bit());
         qstr = "Duration create single object: " + QString::number(qTimeStartObj.msecsTo(qTimeEndObj)) + " msecs.";
         qDebug(qstr.toLocal8Bit());
      }

      pCdmOLManager->RemoveContainerLocally("TestOL");
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End CreateObjectSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration CreateObjectSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:05:16 2012----------*
 * @method  CwtTest::LoadObjectSlot                          // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:05:16 2012----------*/
void CwtTest::LoadObjectSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start LoadObjectSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      QVERIFY(pContainer != nullptr);
      QVERIFY(pContainer->GetId() > 0);
      QVERIFY(pContainer->IsModified() == false);
      QVERIFY(pContainer->IsNew() == false);
      QVERIFY(pContainer->IsDeleted() == false);

      if (pContainer)
      {
         CdmObject* pCdmObject = nullptr;
         pCdmObject = pContainer->FindObjectById(m_lObjectId);

         QVERIFY(pCdmObject != nullptr);
         CdmLocatedElement* pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pCdmObject->GetUri());
         QVERIFY(pTemp == pCdmObject);
         pTemp = pCdmOLManager->GetDataProvider()->GetUriObject(pCdmObject->GetUri());
         QVERIFY(pTemp == pCdmObject);
         QVERIFY(pCdmObject->GetId() == m_lObjectId);
         QVERIFY(pCdmObject->IsModified() == false);
         QVERIFY(pCdmObject->IsNew() == false);
         QVERIFY(pCdmObject->IsDeleted() == false);
         QVERIFY(pCdmObject->IsValid() == true);
         QVERIFY(pCdmObject->GetDisplayString("String")  ==  "String0");
         QVERIFY(pCdmObject->GetDisplayString("Int")  ==  "789");
         double dValue = 0;
         pCdmObject->GetValue("Double", dValue);
         QVERIFY(dValue  > 123);
         QDate qDate;
         pCdmObject->GetValue("Date", qDate);
         QVERIFY(qDate  == QDate::currentDate());
         QTime qSavedTime;
         pCdmObject->GetValue("Time", qSavedTime);
         QString qstrSavedTime = qSavedTime.toString();
         QString qstrTestTime = m_qTestTimeWithPreparation.toString();
         QVERIFY(qstrSavedTime  == qstrTestTime);
         QDateTime qSavedDateTime;
         pCdmObject->GetValue("DateTime", qSavedDateTime);
         QString qstrSavedDateTime = qSavedDateTime.toString();
         QString qstrTestDateTime = m_qdTestDateTime.toString();
         QVERIFY(qstrSavedDateTime  == qstrTestDateTime);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End LoadObjectSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration LoadObjectSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:04:30 2012-----------*
 * @method  CwtTest::QueryTestSlotAnd                        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:04:30 2012-----------*/
void CwtTest::QueryTestSlotAnd()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotAnd: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsRight(cCdmQuery, eDmQueryElementTypeAnd);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 1);
      
      long lObjectId = (*qllResults.begin());
      QVERIFY(lObjectId == m_lObjectId);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotAnd: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotAnd: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:04:49 2012-----------*
 * @method  CwtTest::QueryTestSlotOr                         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:04:49 2012-----------*/
void CwtTest::QueryTestSlotOr()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotOr: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsRight(cCdmQuery, eDmQueryElementTypeOr);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 1);

      long lObjectId = (*qllResults.begin());
      QVERIFY(lObjectId == m_lObjectId);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotOr: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotOr: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:08:29 2012-----------*
 * @method  CwtTest::QueryTestSlotAndOneWrong                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:08:29 2012-----------*/
void CwtTest::QueryTestSlotAndOneWrong()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotAndOneWrong: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsOneWrong(cCdmQuery, eDmQueryElementTypeAnd);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 0);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotAndOneWrong: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotAndOneWrong: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:08:56 2012-----------*
 * @method  CwtTest::QueryTestSlotOrOneWrong                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:08:56 2012-----------*/
void CwtTest::QueryTestSlotOrOneWrong()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotOrOneWrong: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsOneWrong(cCdmQuery, eDmQueryElementTypeOr);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 1);

      long lObjectId = (*qllResults.begin());
      QVERIFY(lObjectId == m_lObjectId);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotOrOneWrong: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotOrOneWrong: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:13:40 2012-----------*
 * @method  CwtTest::QueryTestSlotAndBothWrong               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:13:40 2012-----------*/
void CwtTest::QueryTestSlotAndBothWrong()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotAndBothWrong: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsBothWrong(cCdmQuery, eDmQueryElementTypeAnd);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 0);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotAndBothWrong: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotAndBothWrong: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:14:01 2012-----------*
 * @method  CwtTest::QueryTestSlotOrBothWrong                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:14:01 2012-----------*/
void CwtTest::QueryTestSlotOrBothWrong()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryTestSlotOrBothWrong: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQuery cCdmQuery(pContainer);
      cCdmQuery.SetSchemeSearch();

      AddQueryElementsBothWrong(cCdmQuery, eDmQueryElementTypeOr);
      int iSuccess = cCdmQuery.Execute();

      QVERIFY(iSuccess > 0);
      QLinkedList<long> qllResults = cCdmQuery.GetResultList();
      QVERIFY(qllResults.count() == 0);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryTestSlotOrBothWrong: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryTestSlotOrBothWrong: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 3. Mai 11:10:54 2012-----------*
 * @method  CwtTest::AddQueryElementsRight                   // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rQuery                               //                                   *
 * @param   EdmQueryElementType p_eType                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:10:54 2012-----------*/
void CwtTest::AddQueryElementsRight(CdmQuery& p_rQuery, EdmQueryElementType p_eType)
{
   AddQueryElements(p_rQuery, p_eType, "String0", 789);
}

/** +-=---------------------------------------------------------Do 3. Mai 11:11:11 2012-----------*
 * @method  CwtTest::AddQueryElements                        // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rQuery                               //                                   *
 * @param   EdmQueryElementType p_eType                      //                                   *
 * @param   QString p_qstrString                             //                                   *
 * @param   int p_iInt                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:11:11 2012-----------*/
void CwtTest::AddQueryElements(CdmQuery& p_rQuery,
                               EdmQueryElementType p_eType,
                               QString p_qstrString,
                               int p_iInt)
{

   CdmQueryElement* pCdmElementRoot = new CdmQueryElement(&p_rQuery, p_eType);
   p_rQuery.SetQueryElement(pCdmElementRoot);

   CdmQueryElement* pCdmElement = new CdmQueryElement(&p_rQuery, eDmQueryElementTypeCompare, eDmQueryCompareTypeEqual);
   pCdmElement->SetComparisonValue("String", p_qstrString);
   pCdmElementRoot->AddChild(pCdmElement);

   pCdmElement = new CdmQueryElement(&p_rQuery, eDmQueryElementTypeCompare, eDmQueryCompareTypeEqual);
   pCdmElement->SetComparisonValue("Int", p_iInt);
   pCdmElementRoot->AddChild(pCdmElement);
}

/** +-=---------------------------------------------------------Do 3. Mai 11:07:23 2012-----------*
 * @method  CwtTest::AddQueryElementsOneWrong                // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rQuery                               //                                   *
 * @param   EdmQueryElementType p_eType                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:07:23 2012-----------*/
void CwtTest::AddQueryElementsOneWrong(CdmQuery& p_rQuery, EdmQueryElementType p_eType)
{
   AddQueryElements(p_rQuery, p_eType, "Wrong can not found", 789);
}

/** +-=---------------------------------------------------------Do 3. Mai 11:10:33 2012-----------*
 * @method  CwtTest::AddQueryElementsBothWrong               // private                           *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rQuery                               //                                   *
 * @param   EdmQueryElementType p_eType                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 3. Mai 11:10:33 2012-----------*/
void CwtTest::AddQueryElementsBothWrong(CdmQuery& p_rQuery, EdmQueryElementType p_eType)
{
   AddQueryElements(p_rQuery, p_eType, "Wrong can not found", 123);
}

/** +-=---------------------------------------------------------Mi 2. Mai 10:57:44 2012-----------*
 * @method  CwtTest::QueryEnhancedTestSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 2. Mai 10:57:44 2012-----------*/
void CwtTest::QueryEnhancedTestSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start QueryEnhancedTestSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      CdmQueryEnhanced cCdmQuery;
      cCdmQuery.SetContainer(pContainer);

      AddQueryElementsRight(cCdmQuery, eDmQueryElementTypeOr);
      
      cCdmQuery.AddResultElement("Bool");
      cCdmQuery.AddResultElement("Date");
      cCdmQuery.AddResultElement("Double");
      
      int iSuccess = cCdmQuery.Execute();
      QVERIFY(iSuccess > 0);
      int iResults = cCdmQuery.GetResultCount();

      QVERIFY(iResults == 1);

      bool bBool = cCdmQuery.GetResultAt(0,0).toBool();
      QDate qDate = cCdmQuery.GetResultAt(1,0).toDate();
      double dDouble = cCdmQuery.GetResultAt(2,0).toDouble();

      QVERIFY(bBool == true);
      QVERIFY(qDate == QDate::currentDate());
      QVERIFY(dDouble > 123 && dDouble < 124);
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End QueryEnhancedTestSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration QueryEnhancedTestSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:04:30 2012----------*
 * @method  CwtTest::DeleteObjectSlot                        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:04:30 2012----------*/
void CwtTest::DeleteObjectSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start DeleteObjectSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      QVERIFY(pContainer != nullptr);
      QVERIFY(pContainer->GetId() > 0);

      if (pContainer)
      {
         CdmObject* pCdmObject = pContainer->FindObjectById(m_lObjectId);
         QVERIFY(pCdmObject != nullptr);
         QVERIFY(pCdmObject->GetId() == m_lObjectId);

         pCdmObject->SetDeleted();
         pContainer->Commit();

         pCdmObject = pContainer->FindObjectById(m_lObjectId);
         QVERIFY(pCdmObject == nullptr);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End DeleteObjectSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration DeleteObjectSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:04:47 2012----------*
 * @method  CwtTest::DeleteObjectListSlot                    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:04:47 2012----------*/
void CwtTest::DeleteObjectListSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start DeleteObjectListSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QString qstrOLName = "TestOL";
   QVERIFY(pCdmOLManager != nullptr);

   if (pCdmOLManager)
   {
      CdmObjectContainer* pContainer = pCdmOLManager->FindEmptyContainerByKeyname(qstrOLName);
      QVERIFY(pContainer != nullptr);
      QVERIFY(pContainer->GetId() > 0);

      if (pContainer)
      {
         long lId = pContainer->GetId();
         int iSuccess = 0;

         pContainer->SetDeleted();               
         iSuccess = pContainer->Commit();
         
         QVERIFY(iSuccess > 0);
         pContainer = pCdmOLManager->FindEmptyContainerById(lId);
         QVERIFY(pContainer == nullptr);
      }
   }

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End DeleteObjectListSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration DeleteObjectListSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:04:57 2012----------*
 * @method  CwtTest::DeleteClassSlot                         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:04:57 2012----------*/
void CwtTest::DeleteClassSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start DeleteClassSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmClassManager* pCdmClasssManager = GetClassManager();
   QVERIFY(pCdmClasssManager != nullptr);

   pCdmClasssManager->DeleteClass(m_lClassId);

   CdmClass* pCdmClass = pCdmClasssManager->FindClassById(m_lClassId);
   QVERIFY(pCdmClass == nullptr);
   QTime qTimeEnd = QTime::currentTime();
   qstr = "End DeleteClassSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration DeleteClassSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Sa 28. Apr 13:17:59 2012----------*
 * @method  CwtTest::DeleteDatabaseSlot                      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 28. Apr 13:17:59 2012----------*/
void CwtTest::DeleteDatabaseSlot()
{
   QTime qTimeStart = QTime::currentTime();
   QString qstr = "Start DeleteDatabaseSlot: " + qTimeStart.toString();
   qDebug(qstr.toLocal8Bit());

   CdmDataProvider* pCdmDataProvider = GetDataProvider();
   QVERIFY(pCdmDataProvider != nullptr);
   int iSuccess = 0;
   
   iSuccess = pCdmDataProvider->RemoveScheme(m_qstrDbName);

   QVERIFY(iSuccess > 0);
   QVERIFY(pCdmDataProvider->ExistScheme(m_qstrDbName) <= 0);

   QTime qTimeEnd = QTime::currentTime();
   qstr = "End DeleteDatabaseSlot: " + qTimeEnd.toString();
   qDebug(qstr.toLocal8Bit());
   qstr = "Duration DeleteDatabaseSlot: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Do 26. Apr 11:11:20 2012----------*
 * @method  CwtTest::cleanupTestCase                         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 26. Apr 11:11:20 2012----------*/
void CwtTest::cleanupTestCase()
{
   QTime qTime = QTime::currentTime();
   QString qstr = "End: " + qTime.toString();
   qDebug(qstr.toLocal8Bit());
   int iMSecs = m_qTimeStart.msecsTo(qTime);
   int iSecs = iMSecs / 1000;
   int iMins = iSecs / 60;
   int iMinSecs = iSecs % 60;
   qstr = "Duration: " + QString::number(iMSecs) + " msecs.\n";
   qstr += "Seconds: " + QString::number(iSecs) + ".\n";
   qstr += "Minutes: " + QString::number(iMins) + " and " + QString::number(iMinSecs) + " secs.\n";
   
   qDebug(qstr.toLocal8Bit());
}

/** +-=---------------------------------------------------------Fr 20. Apr 10:49:29 2012----------*
 * @method  CwtTest::LogoutSlot                              // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 20. Apr 10:49:29 2012----------*/
void CwtTest::LogoutSlot()
{
   CdmSessionManager::Logout();
   QVERIFY(GetDataProvider() == nullptr);
}
