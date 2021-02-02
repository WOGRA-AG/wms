/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwtTest.h
 ** Started Implementation: 2013/10/06
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/


// System and QT Includes
#include <qtimer.h>

// WMS Includes
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmQueryEnhanced.h"
#include "CdmSessionManager.h"
#include "CdmPackage.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"


// own Includes
#include "CwtHelper.h"
#include "CwtClass.h"

#define TEST_LANGUAGE "Englisch"


CwtClass::CwtClass()
    : CwtTestBase(eBmsTestModeDB)
{

}

CwtClass::~CwtClass()
{
}

void CwtClass::initTestCase()
{
}

void CwtClass::cleanupTestCase()
{
}

void CwtClass::init()
{
    InitWithLogin();
    m_qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(m_qstrSchemeName);
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    QString qstrLanguage = TEST_LANGUAGE;
    pScheme->AddLanguage(qstrLanguage);
    QVERIFY(pScheme->Commit() > 0);
    StartPureTest();
}

void CwtClass::cleanup()
{
    CwtHelper::DeleteScheme(m_qstrSchemeName);
    CleanupWithLogout();
}

void CwtClass::CreateAndDeleteSimpleClass()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    pClass->SetCaption("Test Basis Klasse");
    pClass->SetComment("Das ist die Basis für die Testklasse");

    CdmMember* pMember = pClass->CreateMember("zahl", eDmValueInt, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("Ganze Zahl");
    pMember->SetComment("Das ist eine ganze Zahl.");

    QVERIFY(pClass->Commit() > 0);
    QVERIFY(pClass->IsModified() == false);
    QVERIFY(pClass->IsNew() == false);
    QVERIFY(pClass->IsDeleted() == false);
}

void CwtClass::UpdateClassRenameMemberKeyname()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetKeyname("zeichen222");
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassRenameMemberCaption()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("zeichen222");
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassChangeType()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetValueType(eDmValueBool);
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassRenameMemberKeynameAndChangeType()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetValueType(eDmValueBool);
    pMember->SetKeyname("blubb");
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassDeleteMember()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    pClass->DeleteMember(TEST_MEMBER_KEYNAME);
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassChangeClassCaptionAndComment()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    pClass->SetCaption("blabla");
    pClass->SetComment("blibli");
    QVERIFY(pClass->Commit() > 0);
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    QVERIFY(pClass->GetCaption() == "blabla");
    QVERIFY(pClass->GetComment() == "blibli");
}


void CwtClass::UpdateClassChangeKeyname()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    pClass->SetKeyname("blabla");
    QVERIFY(pClass->Commit() > 0);
    pClass = ResetSessionAndLoadClass("blabla");
    QVERIFY(pClass != nullptr);
}

void CwtClass::CheckClassUris()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmDataProvider* pManager = GetDataProvider();
    QVERIFY(pManager != nullptr);
    QString qstrClassUri = pClass->GetUri();

    CdmLocatedElement* pTemp = pManager->GetUriObject(qstrClassUri);
    QVERIFY(pTemp == pClass);
    QString qstrKeyname = pManager->GetClassKeynameFromUri(qstrClassUri);
    QCOMPARE(qstrKeyname,pClass->GetKeyname());
}

void CwtClass::CheckGroups()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    CdmClassGroup* pGroup = pClass->CreateGroup("Group1", 1, nullptr);
    QVERIFY(pGroup != nullptr);

    CdmMember* pMember = pClass->CreateMember("InGroup1", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Gruppe 1");
    pMember->SetComment("Bool in Gruppe 1");
    pMember->SetGroup(pGroup);

    QVERIFY(pClass->Commit() > 0);
    QVERIFY(pClass->IsModified() == false);
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    QVERIFY(pClass->GetClassGroups().count() == 1);
    pGroup = pClass->FindGroupByName("Group1");
    QVERIFY(pGroup != nullptr);
    QList<CdmMember*> qlMembers;
    pGroup->GetMembers(qlMembers);
    QVERIFY(qlMembers.count() == 1);
}

void CwtClass::CheckMethods()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmClassMethod* pMethod = pClass->CreateMethod("Test1");
    pMethod->SetAccess(eDmMemberAccessPublic);
    pMethod->SetStatic(true);
    pMethod->SetSourceCode("return 25 * 5;");


    QVERIFY(pClass->Commit() > 0);
    QVERIFY(pClass->IsModified() == false);
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    pMethod = pClass->FindMethod("Test1");
    QVariantList qlParams;
    QVariant qvResult = CdmExecutor::GetExecutor()->GetFunction()->ExecuteFunctionStatic(pMethod, qlParams);
    QVERIFY(qvResult.toInt() == 25 * 5);
}

void CwtClass::CheckBaseClass()
{
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);
    CdmClass* pClass = pClassManager->CreateClass("BaseClassCheck0");
    QVERIFY(pClass != nullptr);
    CdmClass* pBaseClass1 = pClassManager->CreateClass("BaseClassCheck1");
    QVERIFY(pBaseClass1 != nullptr);
    CdmClass* pBaseClass2 = pClassManager->CreateClass("BaseClassCheck2");
    QVERIFY(pBaseClass2 != nullptr);
    CdmMember* pMember = pClass->CreateMember("BaseClassCheck0Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 0");
    pMember->SetComment("Bool in Klasse 0");
    pMember = pBaseClass1->CreateMember("BaseClassCheck1Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 1");
    pMember->SetComment("Bool in Klasse 1");
    pMember = pBaseClass2->CreateMember("BaseClassCheck2Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 2");
    pMember->SetComment("Bool in Klasse 2");
    QVERIFY(pBaseClass2->Commit() > 0);
    QVERIFY(pBaseClass1->AddBaseClass(pBaseClass2) > 0);
    QVERIFY(pBaseClass1->Commit() > 0);
    QVERIFY(pClass->AddBaseClass(pBaseClass1) > 0);
    QVERIFY(pClass->Commit() > 0);
    pClass = ResetSessionAndLoadClass("BaseClassCheck0");
    QMap<long, CdmMember*> qmMembers;
    pClass->GetMemberMap(qmMembers);
    QVERIFY(qmMembers.count() == 3);
    pClassManager = GetClassManager();
}

void CwtClass::CheckLoopingBaseClass()
{
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);
    CdmClass* pClass = pClassManager->CreateClass("BaseClassCheckLoop0");
    QVERIFY(pClass != nullptr);
    CdmClass* pBaseClass1 = pClassManager->CreateClass("BaseClassCheckLoop1");
    QVERIFY(pBaseClass1 != nullptr);
    CdmClass* pBaseClass2 = pClassManager->CreateClass("BaseClassCheckLoop2");
    QVERIFY(pBaseClass2 != nullptr);


    CdmMember* pMember = pClass->CreateMember("BaseClassCheck0Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 0");
    pMember->SetComment("Bool in Klasse 0");
    pMember = pBaseClass1->CreateMember("BaseClassCheck1Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 1");
    pMember->SetComment("Bool in Klasse 1");
    pMember = pBaseClass2->CreateMember("BaseClassCheck2Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 2");
    pMember->SetComment("Bool in Klasse 2");
    QVERIFY(pBaseClass1->AddBaseClass(pBaseClass2) > 0);
    QVERIFY(pClass->AddBaseClass(pBaseClass1) > 0);
    QVERIFY(pBaseClass2->AddBaseClass(pClass) < 0);
}

void CwtClass::AddMemberWithTheSameName()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = pClass->CreateMember("Same", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Gruppe 1");
    pMember->SetComment("Bool in Gruppe 1");
    pMember = pClass->CreateMember("Same", eDmValueBool, false, 0);
    QVERIFY(pMember == nullptr);
}

void CwtClass::CheckTranslations()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    QString qstrLanguage = TEST_LANGUAGE;

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetTranslation(qstrLanguage, "characters", "characters");
    QVERIFY(pClass->Commit());
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    pScheme->SetCurrentLanguage(qstrLanguage);
    QVERIFY(pMember->GetCaption() == "characters");
    QVERIFY(pMember->GetComment() == "characters");
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);

}

void CwtClass::CheckMemberRights()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    CumUser* pUser = CreateTestUser();
    CdmRights& cRights = pMember->GetRights();
    cRights.AddRight(pUser, eDmRightWrite);
    //pMember->SetModified();
    QVERIFY(pClass->Commit() > 0);
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    CdmRights& cRightsReloaded = pMember->GetRights();
    QMap<int, EdmRight> qmRights = cRightsReloaded.GetRights();
    QVERIFY(qmRights.count() == 1);
    DeleteTestUser();
}

void CwtClass::CheckIsInherited()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);
    CdmClass* pBaseClass = pClassManager->CreateClass("base");
    QVERIFY(pBaseClass->Commit() > 0);
    pClass->AddBaseClass(pBaseClass);
    QVERIFY(pClass->Commit() > 0);
    QVERIFY(pClass->IsInherited(pBaseClass) > 0);
    QVERIFY(pBaseClass->IsInherited(pClass) == 0);
}

void CwtClass::CreateClassesWithTheSameName()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass == nullptr);
}

void CwtClass::MemberSequenceTest()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    pClass->CreateMember("price", eDmValueDouble, false, 0);
    QVector<QString> qv;
    qv.append("price");
    qv.append("zeichen");
    pClass->SetMemberSequence(qv);
    QVERIFY(pClass->Commit());
    pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    qv = pClass->GetMemberSequence();
    QString qstrFirst = qv[0];
    QString qstrSecond = qv[1];

    QVERIFY(qstrFirst == "price");
    QVERIFY(qstrSecond == "zeichen");
}

void CwtClass::AddClassToPackage()
{
    CdmClassManager* pClassManager = GetClassManager();
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    CdmPackage* pPackage = pClassManager->CreatePackage("com");
    QVERIFY(pPackage != nullptr);
    pClass->SetPackage(pPackage);
    QVERIFY(pClass->Commit() > 0);
    ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pClassManager = GetClassManager();
    pClass = pClassManager->FindClassByKeyname("com." TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    pPackage = pClass->GetPackage();
    QVERIFY(pPackage->GetKeyname() == "com");
}

void CwtClass::TryVeryLongClassName()
{
    CdmClassManager* pClassManager = GetClassManager();
    CdmClass* pClass = pClassManager->CreateClass("ThisIsAVeryLongClassNameWhichMustFitDataBaseNeeds");
    QVERIFY(pClass != nullptr);
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::TryVeryLongPackageQueueClass()
{
    CdmClassManager* pClassManager = GetClassManager();
    CdmPackage* pPackage = pClassManager->CreatePackage("first");
    pPackage = pClassManager->CreatePackage("second", pPackage);
    pPackage = pClassManager->CreatePackage("third", pPackage);
    pPackage = pClassManager->CreatePackage("Fourth", pPackage);
    pPackage = pClassManager->CreatePackage("fivth", pPackage);
    pPackage = pClassManager->CreatePackage("sixth", pPackage);
    pPackage = pClassManager->CreatePackage("seventh", pPackage);

    CdmClass* pClass = pClassManager->CreateClass("SmallClassName", pPackage);
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::TryVeryLongMemberName()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    pClass->CreateMember("thisIsAVeryLongMemberKeynameAndImVeryCoriousWhatWMSDoesWithIt", eDmValueLong, false, 0);
    QVERIFY(pClass->Commit() > 0);
}

// NOT IMPLEMENTED IN WMS UNTIL NOW!!!
void CwtClass::CheckDiamondProblemSlot()
{
    CdmClassManager* pCdmClassManager = GetClassManager();
    QVERIFY(pCdmClassManager != nullptr);
    CdmClass* pClass = pCdmClassManager->CreateClass("Diamond0");
    QVERIFY(pClass != nullptr);
    CdmClass* pBaseClass1 = pCdmClassManager->CreateClass("Diamond1");
    QVERIFY(pBaseClass1 != nullptr);
    CdmClass* pBaseClass2 = pCdmClassManager->CreateClass("Diamond2");
    QVERIFY(pBaseClass2 != nullptr);
    CdmClass* pBaseClass3 = pCdmClassManager->CreateClass("Diamond3");
    QVERIFY(pBaseClass3 != nullptr);
    CdmMember* pMember = pClass->CreateMember("BaseClassCheck0Member", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 0");
    pMember->SetComment("Bool in Klasse 0");
    pMember = pBaseClass1->CreateMember("SameMember", eDmValueBool, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 1");
    pMember->SetComment("Bool in Klasse 1");
    pMember = pBaseClass2->CreateMember("SameMember", eDmValueInt, false, 0);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption("In Klasse 2");
    pMember->SetComment("Bool in Klasse 2");
    QVERIFY(pClass->AddBaseClass(pBaseClass1) > 0);
    QVERIFY(pClass->AddBaseClass(pBaseClass2) > 0);
    QVERIFY(pBaseClass2->AddBaseClass(pBaseClass3) < 0);
    QVERIFY(pBaseClass1->AddBaseClass(pBaseClass3) < 0);
    pBaseClass1->Commit();
    pBaseClass2->Commit();
    pBaseClass3->Commit();
    QVERIFY(pClass->Commit() < 0); // diamond check must return error
}

void CwtClass::AddMethodStaticPublic()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    pClass->CreateMember("price", eDmValueDouble, false, 0);
    CdmClassMethod* pMethod = pClass->CreateMethod("test");
    pMethod->SetAccess(eDmMemberAccessPublic);
    pMethod->SetCaption("Test");
    pMethod->SetClass(pClass);
    pMethod->SetComment("Test method");
    pMethod->SetMethodName("test");
    pMethod->SetReturnType(eDmValueInt);
    pMethod->SetSourceCode("return 1;");
    pMethod->SetStatic(true);
    pMethod->SetVersion(1);
    QVERIFY(SUCCESSFULL(pClass->Commit()));
    pMethod->SetSourceCode("return 2;");
    QVERIFY(SUCCESSFULL(pClass->Commit()));
}

void CwtClass::UpdateClassChangeMemberType()
{
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);

    CdmMember* pMember = const_cast<CdmMember*>(pClass->FindMember(TEST_MEMBER_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetValueType(eDmValueInt);
    QVERIFY(pClass->Commit() > 0);
}

void CwtClass::UpdateClassAfterReset()
{
    CdmClassManager* pClassManager = GetClassManager();
    CdmClass* pClass = CwtHelper::CreateTestClass();
    QVERIFY(pClass != nullptr);
    QVERIFY(pClass->Commit() > 0);
    ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pClassManager = GetClassManager();
    pClass = pClassManager->FindClassByKeyname(TEST_CLASS_NAME);
    QVERIFY(pClass != nullptr);
    QVERIFY(pClass->Commit() > 0);
}
