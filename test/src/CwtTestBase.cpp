/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwtTestBase.h
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
#include <qdir.h>

// WMS Includes
#include "CdmGlobalContext.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
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
#include "CdmValue.h"
#include "CdmValueUserGroup.h"
#include "CdmValueListDouble.h"
#include "CdmValueFormula.h"
#include "CdmValueListInt.h"
#include "CdmValueListString.h"
#include "CdmValueListObjects.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueDictStringString.h"

// own Includes
#include "CwtHelper.h"
#include "CwtTestBase.h"

CwtTestBase::CwtTestBase(EwmsTestMode p_eMode)
: m_TestTimeWithPreparation(true, "TestTimeWithPreparation"),
 m_pureTestTime(true, "PureTestTime"),
 m_eTestMode(p_eMode)

{

}

CwtTestBase::~CwtTestBase()
{
}

int CwtTestBase::Login()
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    int iSessionId = 0;
    iSessionId = pSessionManager->Login(LOGIN_ADMIN, PASSWORD_ADMIN);
   return iSessionId;
}

CdmDataProvider* CwtTestBase::GetDataProvider()
{
   CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();
   return pFactory->GetDataProvider();
}

CdmClassManager* CwtTestBase::GetClassManager()
{
   CdmClassManager* pCdmClassManager = nullptr;
   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

   if (pCdmDataProvider)
   {
      pCdmClassManager = pCdmDataProvider->GetClassManager();
   }

   return pCdmClassManager;
}

CdmScheme* CwtTestBase::GetScheme(QString p_qstrSchemeName)
{
    CdmScheme* pScheme = nullptr;
    CdmDataProvider* pDataProvider = GetDataProvider();

    if(CHKPTR(pDataProvider))
    {
        if (SUCCESSFULL(pDataProvider->LoadScheme(p_qstrSchemeName)))
        {
            pScheme = pDataProvider->GetCurrentScheme();
        }
    }

    return pScheme;
}

CdmContainerManager* CwtTestBase::GetContainerManager()
{
   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();
   CdmContainerManager* pCdmOLManager = nullptr;

   if (pCdmDataProvider)
   {
      pCdmOLManager = pCdmDataProvider->GetContainerManager();
   }

   return pCdmOLManager;
}

CdmObjectContainer* CwtTestBase::GetContainer(QString p_qstrKeyname)
{
    CdmObjectContainer* pContainer = nullptr;
    CdmContainerManager* pContainerManager = GetContainerManager();

    if (pContainerManager)
    {
        pContainer = pContainerManager->FindContainerByKeyname(p_qstrKeyname);
    }

    return pContainer;
}

void CwtTestBase::Logout()
{
   CdmSessionManager::GetSessionManager()->GetGlobalContext()->DeleteAllClassManagers();
   CdmSessionManager::Logout();
   QVERIFY(GetDataProvider() == nullptr);
}

void CwtTestBase::ResetSession()
{
    Logout();
    Login();
}

void CwtTestBase::InitWithLogin()
{
    InitWithoutLogin();
    Login();
}

void CwtTestBase::InitWithoutLogin()
{
    m_TestTimeWithPreparation.start();
}

void CwtTestBase::CleanupWithLogout()
{
    CleanupWithoutLogout();
    Logout();
}

void CwtTestBase::CleanupWithoutLogout()
{
    m_TestTimeWithPreparation.finished();
    m_TestTimeWithPreparation.printResulttoDebugOutput();
}

void CwtTestBase::StartPureTest()
{
    m_pureTestTime.start();
}

void CwtTestBase::EndPureTest()
{
    m_pureTestTime.finished();
    m_pureTestTime.printResulttoDebugOutput();
}

CumUser* CwtTestBase::CreateTestUser()
{
    CumUser* pUser = nullptr;
    CumUserManager* pUserManager = CwtHelper::GetUserManager();

    if (CHKPTR(pUserManager))
    {
        pUser = CwtHelper::CreateUser("test", pUserManager);
        pUserManager->CreateUser(pUser);
    }

    return pUser;
}

void CwtTestBase::DeleteUser(CumUser* p_pUser)
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();

    if (CHKPTR(pUserManager) && CHKPTR(p_pUser))
    {
        pUserManager->DeleteUser(p_pUser->GetId());
    }
}

void CwtTestBase::DeleteUser(QString p_qstrUser)
{
    CumUserManager* pUserManager = CwtHelper::GetUserManager();

    if (CHKPTR(pUserManager))
    {
        CumUser* pUser = pUserManager->FindUserByLogin(p_qstrUser);
        if (CHKPTR(pUser))
        {
            pUserManager->DeleteUser(pUser->GetId());
        }
    }
}

void CwtTestBase::DeleteTestUser()
{
    DeleteUser("test");
}

CdmClass* CwtTestBase::ResetSessionAndLoadClass(QString p_qstrClassName)
{
    CdmClass* pClass = nullptr;
    ResetSession();
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    if (CHKPTR(pScheme))
    {
        CdmClassManager* pClassManager = GetClassManager();
        if (CHKPTR(pClassManager))
        {
            pClass = pClassManager->FindClassByKeyname(p_qstrClassName);
        }
    }

    return pClass;
}

CumUserManager* CwtTestBase::GetUserManager()
{
    return CwtHelper::GetUserManager();
}

void CwtTestBase::CreateTestClass()
{
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);
    m_pClassNoRef = pClassManager->CreateClass(TEST_CLASS_NAME_NO_REF);
    QVERIFY(m_pClassNoRef != nullptr);
    m_pClassNoRef->CreateMember(MEMBER_STRING_KEYNAME, eDmValueString, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_INT_KEYNAME, eDmValueInt, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_LONG_KEYNAME, eDmValueLong, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_FLOAT_KEYNAME, eDmValueFloat, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_DOUBLE_KEYNAME, eDmValueDouble, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_BOOL_KEYNAME, eDmValueBool, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_CHARDOC_KEYNAME, eDmValueCharacterDocument, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_BINDOC_KEYNAME, eDmValueBinaryDocument, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_USER_KEYNAME, eDmValueUser, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_USER_GROUP_KEYNAME, eDmValueUserGroup, false, -1);
    CdmMember* pMember = m_pClassNoRef->CreateMember(MEMBER_ENUM_KEYNAME, eDmValueEnum, false, -1);
    pMember->SetValidationCode("first, second, third");
    pMember = m_pClassNoRef->CreateMember(MEMBER_FORMULA_KEYNAME, eDmValueFormula, false, -1);
    pMember->SetValidationCode(MEMBER_INT_KEYNAME " + " MEMBER_LONG_KEYNAME);
    m_pClassNoRef->CreateMember(MEMBER_DATE_KEYNAME, eDmValueDate, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_TIME_KEYNAME, eDmValueTime, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_DATE_TIME_KEYNAME, eDmValueDateTime, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_COUNTER_KEYNAME, eDmValueCounter, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_LIST_INT_KEYNAME, eDmValueListInt, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_LIST_DOUBLE_KEYNAME, eDmValueListDouble, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_LIST_STRING_KEYNAME, eDmValueListString, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_INT_INT_KEYNAME, eDmValueDictIntInt, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_INT_DOUBLE_KEYNAME, eDmValueDictIntDouble, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_INT_STRING_KEYNAME, eDmValueDictIntString, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_STRING_INT_KEYNAME, eDmValueDictStringInt, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_STRING_DOUBLE_KEYNAME, eDmValueDictStringDouble, false, -1);
    m_pClassNoRef->CreateMember(MEMBER_MAP_STRING_STRING_KEYNAME, eDmValueDictStringString, false, -1);
    m_pClassNoRef->Commit();

    m_pClassRef = pClassManager->CreateClass(TEST_CLASS_NAME_REF);
    QVERIFY(m_pClassRef != nullptr);
    pMember = m_pClassRef->CreateMember(MEMBER_OBJREF_KEYNAME, eDmValueObjectRef, false, -1);
    pMember->SetClassReference(m_pClassNoRef);
    pMember->SetOwner(true);
    m_pClassRef->CreateMember(MEMBER_STRING_KEYNAME, eDmValueString, false, -1);
    m_pClassRef->Commit();

    m_pClassRefRef = pClassManager->CreateClass(TEST_CLASS_NAME_REF_REF);
    QVERIFY(m_pClassRefRef != nullptr);
    pMember = m_pClassRefRef->CreateMember(MEMBER_OBJREF_REF2_KEYNAME, eDmValueObjectRef, false, -1);
    pMember->SetClassReference(m_pClassRef);
    pMember->SetOwner(true);
    m_pClassRefRef->CreateMember(MEMBER_STRING_KEYNAME, eDmValueString, false, -1);
    m_pClassRefRef->Commit();
}

void CwtTestBase::CreateTestContainers()
{
    CdmContainerManager* pContainerManager = GetContainerManager();
    QVERIFY(pContainerManager != nullptr);
    QString qstrContainerName = TEST_CONTAINER_NAME_ALL_MEMBERS;
    pContainerManager->CreateContainer(m_pClassNoRef, qstrContainerName);
    qstrContainerName = TEST_CONTAINER_NAME_REF;
    pContainerManager->CreateContainer(m_pClassRef, qstrContainerName);
    qstrContainerName = TEST_CONTAINER_NAME_REF_REF;
    pContainerManager->CreateContainer(m_pClassRefRef, qstrContainerName);
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    pContainer = GetContainer(TEST_CONTAINER_NAME_REF_REF);
    QVERIFY(pContainer != nullptr);
}

void CwtTestBase::FillObjectData(CdmObject* p_pObject)
{
    QVERIFY(p_pObject != nullptr);
    QDate qDate = QDate::currentDate();
    QTime qTime = QTime::currentTime();
    m_qdtDateTime.setDate(qDate);
    m_qdtDateTime.setTime(qTime);

    p_pObject->SetValue(MEMBER_STRING_KEYNAME, VALUE_STRING);
    p_pObject->SetValue(MEMBER_BOOL_KEYNAME, VALUE_BOOL);
    p_pObject->SetValue(MEMBER_CHARDOC_KEYNAME, VALUE_CHARDOC);
    p_pObject->SetValue(MEMBER_DATE_KEYNAME, qDate);
    p_pObject->SetValue(MEMBER_DATE_TIME_KEYNAME,m_qdtDateTime);
    p_pObject->SetValue(MEMBER_DOUBLE_KEYNAME, VALUE_DOUBLE);
    p_pObject->SetValue(MEMBER_ENUM_KEYNAME, VALUE_ENUM);
    p_pObject->SetValue(MEMBER_FLOAT_KEYNAME, VALUE_FLOAT);
    p_pObject->SetValue(MEMBER_INT_KEYNAME, VALUE_INT);
    long lValue = VALUE_LONG;
    p_pObject->SetValue(MEMBER_LONG_KEYNAME, lValue);
    p_pObject->SetValue(MEMBER_TIME_KEYNAME, qTime);
    p_pObject->SetValue(MEMBER_USER_KEYNAME, 0);
    AddUserGroup(p_pObject);
    AddListValues(p_pObject);
    AddDictValues(p_pObject);
    p_pObject->SetCaption(OBJECT_CAPTION);
}

void CwtTestBase::AddIntDoubleDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_INT_DOUBLE_KEYNAME);
    CdmValueDictIntDouble* pDictValue = dynamic_cast<CdmValueDictIntDouble*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue(0, 42.78);
    pDictValue->SetValue(1, 142.78);
    pDictValue->SetValue(2, 1042.7809867);
}

void CwtTestBase::AddIntIntDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_INT_INT_KEYNAME);
    CdmValueDictIntInt* pDictValue = dynamic_cast<CdmValueDictIntInt*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue(0, 1);
    pDictValue->SetValue(1, 2);
    pDictValue->SetValue(2, 4);
}

void CwtTestBase::AddIntStringDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_INT_STRING_KEYNAME);
    CdmValueDictIntString* pDictValue = dynamic_cast<CdmValueDictIntString*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue(0, "first");
    pDictValue->SetValue(1, "second");
    pDictValue->SetValue(2, "third");
}

void CwtTestBase::AddStringDoubleDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_STRING_DOUBLE_KEYNAME);
    CdmValueDictStringDouble* pDictValue = dynamic_cast<CdmValueDictStringDouble*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue("first", 0.6778);
    pDictValue->SetValue("second", 14.7979);
    pDictValue->SetValue("third", -56.7979);
}

void CwtTestBase::AddStringIntDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_STRING_INT_KEYNAME);
    CdmValueDictStringInt* pDictValue = dynamic_cast<CdmValueDictStringInt*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue("first", 0);
    pDictValue->SetValue("second", 100);
    pDictValue->SetValue("third", -56);
}

void CwtTestBase::AddStringStringDictValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_MAP_STRING_STRING_KEYNAME);
    CdmValueDictStringString* pDictValue = dynamic_cast<CdmValueDictStringString*> (pValue);
    QVERIFY(pDictValue != nullptr);
    pDictValue->SetValue("first", "first");
    pDictValue->SetValue("second", "second");
    pDictValue->SetValue("third", "third");
}

void CwtTestBase::AddDictValues(CdmObject* p_pObject)
{
    AddIntDoubleDictValues(p_pObject);
    AddIntIntDictValues(p_pObject);
    AddIntStringDictValues(p_pObject);
    AddStringDoubleDictValues(p_pObject);
    AddStringIntDictValues(p_pObject);
    AddStringStringDictValues(p_pObject);
}

void CwtTestBase::AddListValues(CdmObject* p_pObject)
{
    CdmValue* pValue = p_pObject->GetValue(MEMBER_LIST_DOUBLE_KEYNAME);
    CdmValueListDouble* pDoubleListValue = dynamic_cast<CdmValueListDouble*> (pValue);
    QVERIFY(pDoubleListValue != nullptr);
    pDoubleListValue->AddValue(0.78);
    pDoubleListValue->AddValue(15.3456);
    pDoubleListValue->AddValue(-17.89023);

    pValue = p_pObject->GetValue(MEMBER_LIST_INT_KEYNAME);
    CdmValueListInt* pIntListValue = dynamic_cast<CdmValueListInt*> (pValue);
    QVERIFY(pIntListValue != nullptr);
    pIntListValue->AddValue(78);
    pIntListValue->AddValue(15);
    pIntListValue->AddValue(-17);

    pValue = p_pObject->GetValue(MEMBER_LIST_STRING_KEYNAME);
    CdmValueListString* pStringListValue = dynamic_cast<CdmValueListString*> (pValue);
    QVERIFY(pStringListValue != nullptr);
    pStringListValue->AddValue("78");
    pStringListValue->AddValue("Test");
    pStringListValue->AddValue("üäö*#-.,!!!2}[9");
    pStringListValue->AddValue("");
}

CumUserGroup* CwtTestBase::CreateTestUserGroup()
{
    CumUserManager* pUserManager = GetUserManager();
    if (pUserManager != nullptr)
    {
        QString qstrGroupName = CwtHelper::CreateUniqueName("TestGroup");
        pUserManager->CreateUserGroup(qstrGroupName);
        CumUserGroup* pGroup = pUserManager->FindUserGroupByName(qstrGroupName);
        return pGroup;
    }

    return nullptr;
}

void CwtTestBase::AddUserGroup(CdmObject* p_pObject)
{
    CumUserGroup* pGroup = CreateTestUserGroup();
    QVERIFY(pGroup != nullptr);

    CdmValue* pValue = p_pObject->GetValue(MEMBER_USER_GROUP_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueUserGroup* pGroupValue = dynamic_cast<CdmValueUserGroup*> (pValue);
    QVERIFY(pGroupValue != nullptr);
    pGroupValue->SetUserGroup(pGroup);
}

