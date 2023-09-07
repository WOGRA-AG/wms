/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtQueryTest.cpp
 ** Started Implementation: 2012/04/20
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <qdir.h>

// WMS Commons Includes
#include "CwmsTimeMeassurement.h"

// WMS Includes
#include "CwmsTimeMeassurement.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmValueObjectRef.h"
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmQueryBuilder.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmQuery.h"
#include "CdmQueryModel.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "wmsdefines.h"


// own Includes
#include "CwtHelper.h"
#include "CwtQuery.h"


CwtQuery::CwtQuery()
: CwtTestBase(eBmsTestModeDB),
  m_lObjectId(0),
  m_lClassId(0),
  m_lRefObjectId(0),
  m_lRefRefObjectId(0),
  m_iObjectToCreate(1)
{
}

CwtQuery::~CwtQuery()
{
}

void CwtQuery::initTestCase()
{
}


void CwtQuery::cleanupTestCase()
{
}

void CwtQuery::init()
{
    InitWithLogin();
    m_lObjectId = 0;
    m_lRefObjectId = 0;
    m_lRefRefObjectId = 0;
    m_qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(m_qstrSchemeName);
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    CreateTestClass();
    CreateTestContainers();
    pClassDerived1 = nullptr;
    pClassDerived2 = nullptr;
    StartPureTest();
}

void CwtQuery::cleanup()
{
    EndPureTest();
    CwtHelper::DeleteScheme(m_qstrSchemeName);
    CleanupWithLogout();
}

void CwtQuery::CreateObject()
{
    CreateObject(TEST_CONTAINER_NAME_ALL_MEMBERS);
}

void CwtQuery::CreateObject(QString p_qstrContainerKeyname)
{
    CdmObjectContainer* pContainer = GetContainer(p_qstrContainerKeyname);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    m_lObjectId = pObject->GetId();
}

void CwtQuery::CreateReferencingObject()
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();
    QString qstrObjectKeyname = pObject->GetKeyname();
    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    m_lRefObjectId = pRefObject->GetId();
    FillObjectData(pRefObject);
    QVERIFY(pRefObject->Commit() > 0);
}

void CwtQuery::CreateReferencingObject(CdmObject* p_pObject)
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();
    QString qstrObjectKeyname = pObject->GetKeyname();
    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    pValueRef->SetValue(p_pObject);
    m_lRefObjectId = p_pObject->GetId();
    FillObjectData(p_pObject);
    QVERIFY(p_pObject->Commit() > 0);
    QVERIFY(pObject->Commit() > 0);
}

void CwtQuery::CreateDoubleReferencingObject()
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF_REF);
    QVERIFY(pContainer != nullptr);
    CdmObjectContainer* pRefContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pRefContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();

    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_REF2_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    m_lRefObjectId = pRefObject->GetId();

    pValue = pRefObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefRefObject = pValueRef->GetObject();
    QVERIFY(pRefRefObject != nullptr);
    m_lRefRefObjectId = pRefRefObject->GetId();
    FillObjectData(pRefRefObject);
    QVERIFY(pRefRefObject->Commit() > 0);
}

void CwtQuery::CreateDoubleReferencingObject(CdmObject* p_pObject)
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF_REF);
    QVERIFY(pContainer != nullptr);
    CdmObjectContainer* pRefContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pRefContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();

    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_REF2_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    m_lRefObjectId = pRefObject->GetId();

    pValue = pRefObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    pValueRef->SetValue(p_pObject);
    m_lRefRefObjectId = p_pObject->GetId();
    FillObjectData(p_pObject);
    QVERIFY(p_pObject->Commit() > 0);
    QVERIFY(pRefObject->Commit() > 0);
}

void CwtQuery::CreateMultipleObjects(int p_iObjectCount)
{
    for (int i = 0; i < p_iObjectCount; ++i)
    {
        CreateObject();
    }
}

void CwtQuery::SimpleQueryWithoutCondition()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithoutCondition");
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select from %1").arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOneValueConditionInt()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOneValueConditionInt");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where %2 = %3")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT);

    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOneValueConditionString()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOneValueConditionString");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where %2 = \"%3\"")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
     cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
    QThread::sleep(2);
}

void CwtQuery::SimpleQueryWithOneValueConditionDate()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOneValueConditionDate");
    CreateObject();
    cTime.finishedTask("Create Object");

    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where %2 = \"%3\"")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
     cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOneValueConditionNoResult()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOneValueConditionNoResult");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where %2 = %3")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(108978);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    QVERIFY(pQuery->GetObjectIdAt(0) == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfTwoValuesBothConditionsFitting()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfTwoValuesBothConditionsFitting");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfTwoValuesOneConditionsFitting()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfTwoValuesOneConditionsFitting");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(9876)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfTwoValuesNoResult()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfTwoValuesNoResult");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(112243)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("qaywsx");
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfTwoValuesBothConditionFitting()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithAndConditionOfTwoValuesBothConditionFitting");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
}

void CwtQuery::SimpleQueryWithAndConditionOfTwoValuesFirstConditionsFitting()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithAndConditionOfTwoValuesFirstConditionsFitting");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("zhnujm");
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfTwoValuesSecondConditionsFitting()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithAndConditionOfTwoValuesSecondConditionsFitting");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(89078)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfTwoValuesNothingFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithAndConditionOfTwoValuesNothingFits");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\")")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(9876)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("zhnujm");
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfMultipleValuesEveryConditionFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfMultipleValuesEveryConditionFits");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfMultipleValuesTwoOfThreeConditionFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfMultipleValuesTwoOfThreeConditionFits");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOrConditionOfMultipleValuesOneOfThreeConditionFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfMultipleValuesOneOfThreeConditionFits");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("ik,ol.")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
}

void CwtQuery::SimpleQueryWithOrConditionOfMultipleValuesNoConditionFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithOrConditionOfMultipleValuesNoConditionFits");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate().addDays(23);
    QString qstrWql = QString("select from %1 where or(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("ik,ol.")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfMultipleValuesEveryConditionFits()
{
    CwmsTimeMeassurement cTime(true, "SimpleQueryWithAndConditionOfMultipleValuesEveryConditionFits");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfMultipleValuesTwoOfThreeConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfMultipleValuesOneOfThreeConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("ik,ol.")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndConditionOfMultipleValuesNoConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate().addDays(23);
    QString qstrWql = QString("select from %1 where and(%2 = %3, %4 = \"%5\", %6 = %7)")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(99999)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("ik,ol.")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndOrConditionOfMultipleValuesEveryConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, or(%4 = \"%5\", %6 = \"%7\"))")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING)
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndOrConditionOfMultipleValuesOneOrConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, or(%4 = \"%5\", %6 = \"%7\"))")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("olki")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithAndOrConditionOfMultipleValuesAndDoesNotFitOneOrConditionFits()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QDate qdCurrent = QDate::currentDate();
    QString qstrWql = QString("select from %1 where and(%2 = %3, or(%4 = \"%5\", %6 = \"%7\"))")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(MEMBER_INT_KEYNAME)
            .arg(56545)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("olki")
            .arg(MEMBER_DATE_KEYNAME)
            .arg(qdCurrent.toString(Qt::ISODate));
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithoutConditionWithLimit()
{
    CwmsTimeMeassurement cTime(true, "test");
    int iObjectsToCreate = 3;
    int iLimitCount = 1;
    CreateMultipleObjects(iObjectsToCreate);
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select from %1 limit 1,%2")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(iLimitCount);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == iLimitCount);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithoutConditionWithLimitMoreThanOneResults()
{
    CwmsTimeMeassurement cTime(true, "test");
    int iObjectsToCreate = 3;
    int iLimitCount = 2;
    CreateMultipleObjects(iObjectsToCreate);
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 limit 1,%2")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
            .arg(iLimitCount);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == iLimitCount);
    cTime.finishedTask("Verified Data");
}



void CwtQuery::SimpleQueryWithoutConditionWithOrderBy()
{
    // This is just a check if the syntax creation is correct.
    // This is not a sorting Test because every object will be
    // created the same way and has the same value content.
    CwmsTimeMeassurement cTime(true, "test");
    int iObjectsToCreate = 3;
    CreateMultipleObjects(iObjectsToCreate);
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select from %1 order by %2")
        .arg(TEST_CONTAINER_NAME_ALL_MEMBERS)
        .arg(MEMBER_STRING_KEYNAME);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == iObjectsToCreate);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleClassQueryWithoutCondition()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select from %1.class").arg(TEST_CLASS_NAME_NO_REF);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleClassQueryModelWithoutCondition()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select from %1.class").arg(TEST_CLASS_NAME_NO_REF);
    cTime.finishedTask("Created Query");

    CdmQueryModel cModel;
    cModel.Execute(qstrWql);

    QVERIFY(cModel.rowCount() == 1);
    CdmObject* pObject = cModel.GetObject(static_cast<int>(0));
    QVERIFY(pObject != nullptr);
    QVERIFY(pObject->GetId() == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleClassQueryWithOneValueConditionNoResult()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1.class where %2 = %3")
            .arg(TEST_CLASS_NAME_NO_REF)
            .arg(MEMBER_INT_KEYNAME)
            .arg(108978);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    QVERIFY(pQuery->GetObjectIdAt(0) == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithOneReferenceCondition()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateReferencingObject();
    cTime.finishedTask("Create Object");


    QString qstrWql = QString("select from %1 where %2.%3 = %4")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithTwoReferenceConditionAnd()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateReferencingObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2.%3 = %4, %5.%6 = %7)")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithTwoReferenceConditionOr()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateReferencingObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where or(%2.%3 = %4, %5.%6 = %7)")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithReferenceToBaseClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select from %1 where %2.%3 = %4")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithReferenceToBaseClassAndCondition()
{
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select from %1 where and(%2.%3 = %4, %5.%6 = \"%7\")")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithReferenceToBaseClassOrCondition()
{
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select from %1 where or(%2.%3 = %4, %5.%6 = \"%7\")")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithReferenceToBaseClassAndConditionFirstWrong()
{
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select from %1 where and(%2.%3 = %4, %5.%6 = \"%7\")")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(8912)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithReferenceToBaseClassAndConditionSecondWrong()
{
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select from %1 where and(%2.%3 = %4, %5.%6 = \"%7\")")
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg("kkljl");
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}


void CwtQuery::QueryEnhancedWithOneSelectMember()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select %1 from %2")
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
}

void CwtQuery::QueryEnhancedWithTwoSelectMember()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select %1, %2 from %3")
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
}

void CwtQuery::QueryEnhancedWithSum()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    CreateObject();
    CreateObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select sum(%1) from %2")
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT * 3);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithAvg()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    CreateObject();
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select avg(%1) from %2")
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMax()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    CreateObject();
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select max(%1) from %2")
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMin()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    CreateObject();
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select min(%1) from %2")
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithCount()
{
    CwmsTimeMeassurement cTime(true, "test");
    CreateObject();
    CreateObject();
    CreateObject();
    cTime.finishedTask("Create Object");
    QString qstrWql = QString("select count(*) from %2")
            .arg(TEST_CONTAINER_NAME_ALL_MEMBERS);
    cTime.finishedTask("Created Query");
    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == 3);
}

void CwtQuery::PrepareMultiInheritanceTestCase()
{
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);

    pClassDerived1 = pClassManager->CreateClass("DerivedClass1");
    QVERIFY(pClassDerived1 != nullptr);
    pClassDerived2 = pClassManager->CreateClass("DerivedClass2");
    QVERIFY(pClassDerived2 != nullptr);

    pClassDerived1->AddBaseClass(m_pClassNoRef);
    pClassDerived2->AddBaseClass(m_pClassNoRef);

    pClassDerived1->CreateMember("Derived1", eDmValueString, false, 0);
    pClassDerived2->CreateMember("Derived2", eDmValueString, false, 0);

    QVERIFY(SUCCESSFULL(pClassDerived1->Commit()));
    QVERIFY(SUCCESSFULL(pClassDerived2->Commit()));

    CdmContainerManager* pContainerManager = GetContainerManager();
    QVERIFY(pContainerManager != nullptr);

    QString qstrDerived1ContainerKeyname = "Derived1";
    QString qstrDerived2ContainerKeyname = "Derived2";
    QVERIFY(SUCCESSFULL(pContainerManager->CreateContainer(pClassDerived1, qstrDerived1ContainerKeyname)));
    QVERIFY(SUCCESSFULL(pContainerManager->CreateContainer(pClassDerived2, qstrDerived2ContainerKeyname)));

    CdmObjectContainer* pContainerDerived1 = pContainerManager->FindContainerByKeyname("Derived1");
    QVERIFY(pContainerDerived1 != nullptr);
    CdmObjectContainer* pContainerDerived2 = pContainerManager->FindContainerByKeyname("Derived2");
    QVERIFY(pContainerDerived2 != nullptr);

    CdmObject* pObjectDerived1 = pContainerDerived1->CreateNewObject();
    QVERIFY(pObjectDerived1 != nullptr);
    CdmObject* pObjectDerived2 = pContainerDerived2->CreateNewObject();
    QVERIFY(pObjectDerived2 != nullptr);
    CreateReferencingObject(pObjectDerived1);
    CreateReferencingObject(pObjectDerived2);
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelect()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2 from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(0,1).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectSum()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select sum(%1.%2) from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    int iResult = pQuery->GetResultAt(0,0).toInt();
    QVERIFY(iResult == VALUE_INT*2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectAvg()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select avg(%1.%2) from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectMin()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select min(%1.%2) from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectMax()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select max(%1.%2) from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectCount()
{
    // Preparing the testcase
    CwmsTimeMeassurement cTime(true);
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared now do the test
    QString qstrWql = QString("select count(%1.%2) from %3")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == 2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithOneReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2 from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(0,1).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithSumReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select sum(%1.%2) from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT*2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithAvgReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select avg(%1.%2) from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMinReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select min(%1.%2) from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMaxReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select max(%1.%2) from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithCountReferenceInSelectWithClass()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true);
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select count(%1.%2) from %3.class")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(TEST_CLASS_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == 2);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithTwoReferencesInSelect()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4 from %5")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelect()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");

}

void CwtQuery::EnhancedQueryWithoutConditionWithGroupBy()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select sum(%1.%2), %3.%4 from %5 group by %3.%4")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT*2);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithSimpleWhereClause()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where %1.%2 = %6")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(VALUE_INT);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithAndWhereClause()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where and(%1.%2 = %6, %3.%4 = \"%7\")")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(VALUE_INT)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClause()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where or(%1.%2 = %6, %3.%4 = \"%7\")")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(VALUE_INT)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithAndWhereClauseOneConditionWrong()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where and(%1.%2 = %6, %3.%4 = \"%7\")")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(89)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClauseOneConditionWrong()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where or(%1.%2 = %6, %3.%4 = \"%7\")")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(89)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferencesAndNoReferenecesInSelectWithOrWhereClauseBothConditionWrong()
{
    // Preparing the tescase
    CwmsTimeMeassurement cTime(true, "test");
    PrepareMultiInheritanceTestCase();
    cTime.finishedTask("Create Object");

    // all prepared no do the test
    QString qstrWql = QString("select %1.%2, %3.%4, zeichen from %5 where or(%1.%2 = %6, %3.%4 = \"%7\")")
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF)
            .arg(89)
            .arg("hjhjk");
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 0);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferenceChainsAndNoReferenecesInSelect()
{
    // Preparing the testcase
    CwmsTimeMeassurement cTime(true);
    CreateDoubleReferencingObject();
    CreateDoubleReferencingObject();
    cTime.finishedTask("Create Object");

    // all prepared now do the test
    QString qstrWql = QString("select %1.%2.%3, %1.%2.%4, %1.%4, %4 from %5")
            .arg(MEMBER_OBJREF_REF2_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithMixedReferenceChainsAndReferenecesInSelect()
{
    // Preparing the testcase
    CwmsTimeMeassurement cTime(true);
    CreateDoubleReferencingObject();
    CreateDoubleReferencingObject();
    cTime.finishedTask("Create Object");

    // all prepared now do the test
    QString qstrWql = QString("select %1.%2.%3, %1.%2.%4, %1.%4, %4, %1 from %5")
            .arg(MEMBER_OBJREF_REF2_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 2);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == VALUE_INT);
    QVERIFY(pQuery->GetResultAt(1,0).toString() == VALUE_STRING);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithTwoReferenceChainsConditionAnd()
{
    CwmsTimeMeassurement cTime(true);
    CreateDoubleReferencingObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where and(%2.%3.%4 = %5, %2.%3.%6 = %7)")
            .arg(TEST_CONTAINER_NAME_REF_REF)
            .arg(MEMBER_OBJREF_REF2_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::SimpleQueryWithTwoReferenceChainsConditionOr()
{
    CwmsTimeMeassurement cTime(true);
    CreateDoubleReferencingObject();
    cTime.finishedTask("Create Object");

    QString qstrWql = QString("select from %1 where or(%2.%3.%4 = %5, %2.%3.%6 = %7)")
            .arg(TEST_CONTAINER_NAME_REF_REF)
            .arg(MEMBER_OBJREF_REF2_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(MEMBER_INT_KEYNAME)
            .arg(VALUE_INT)
            .arg(MEMBER_STRING_KEYNAME)
            .arg(VALUE_STRING);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}

void CwtQuery::QueryEnhancedWithReferenceReferenceChainInSelect()
{
    // Preparing the testcase
    CwmsTimeMeassurement cTime(true);
    CreateDoubleReferencingObject();
    cTime.finishedTask("Create Object");

    // all prepared now do the test
    QString qstrWql = QString("select %1.%2, %1 from %3")
            .arg(MEMBER_OBJREF_REF2_KEYNAME)
            .arg(MEMBER_OBJREF_KEYNAME)
            .arg(TEST_CONTAINER_NAME_REF_REF);
    cTime.finishedTask("Created Query");

    QScopedPointer<CdmQuery> pQuery(dynamic_cast<CdmQuery*>(CdmQueryBuilder::ExecuteQuery(qstrWql)));
    cTime.finishedTask("Executed Query");
    QVERIFY(!pQuery.isNull());
    QVERIFY(pQuery->GetResultCount() == 1);
    QVERIFY(pQuery->GetResultAt(0,0).toInt() == m_lRefRefObjectId);
    QVERIFY(pQuery->GetResultAt(1,0).toInt() == m_lRefObjectId);
    QVERIFY(pQuery->GetObjectIdAt(0) == m_lObjectId);
    cTime.finishedTask("Verified Data");
}
