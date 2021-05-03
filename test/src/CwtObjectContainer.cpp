/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtObjectContainer.cpp
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
#include "CwtHelper.h"
#include "CwtObjectContainer.h"

#define TEST_CLASS_NAME "Test"
#define TEST_MEMBER_KEYNAME "zeichen"
#define TEST_CONTAINER_NAME "TestContainer"

CwtObjectContainer::CwtObjectContainer()
: CwtTestBase(eBmsTestModeDB),
  m_pClass(nullptr)
{
}

CwtObjectContainer::~CwtObjectContainer()
{
}

void CwtObjectContainer::initTestCase()
{
}

void CwtObjectContainer::cleanupTestCase()
{
}

void CwtObjectContainer::init()
{
    InitWithLogin();
    m_qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(m_qstrSchemeName);
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    CreateTestClass();
}

void CwtObjectContainer::cleanup()
{
    CwtHelper::DeleteScheme(m_qstrSchemeName);
    CleanupWithLogout();
}


void CwtObjectContainer::CreateTestClass()
{
    CdmClassManager* pClassManager = GetClassManager();
    QVERIFY(pClassManager != nullptr);
    m_pClass = pClassManager->CreateClass(TEST_CLASS_NAME);
    QVERIFY(m_pClass != nullptr);
    CdmMember* pMember = m_pClass->CreateMember(TEST_MEMBER_KEYNAME, eDmValueString, false, -1);
    QVERIFY(pMember != nullptr);
    pMember->SetCaption(TEST_MEMBER_KEYNAME);
    pMember->SetComment("Testmember");
    m_pClass->Commit();
}

void CwtObjectContainer::CheckContainerClass()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->GetClass() == m_pClass);
}

void CwtObjectContainer::CreateAndDeleteContainer()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   long lContainerId = pCdmOLManager->CreateContainer(m_pClass, qstrKeyname);
   QVERIFY (lContainerId > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   qstrKeyname = pContainer->GetKeyname();
   QVERIFY(!qstrKeyname.isEmpty());
   pContainer->SetCaption("TestContainer");
   QVERIFY(pContainer->Commit() > 0);
   pContainer->SetDeleted();
   QVERIFY(pContainer->Commit() > 0);
   QVERIFY(pCdmOLManager->FindContainerByKeyname(qstrKeyname) == nullptr);
}

void CwtObjectContainer::CreateAndDeleteContainerOverContainerManager()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   long lContainerId = pCdmOLManager->CreateContainer(m_pClass, qstrKeyname);
   QVERIFY (lContainerId > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   qstrKeyname = pContainer->GetKeyname();
   QVERIFY(!qstrKeyname.isEmpty());
   pContainer->SetCaption("TestContainer");
   QVERIFY(pContainer->Commit() > 0);
   pCdmOLManager->DeleteContainer(pContainer);
   QVERIFY(pCdmOLManager->FindContainerByKeyname(qstrKeyname) == nullptr);
}

void CwtObjectContainer::FindContainerById()
{
    CdmContainerManager* pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
    QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
    long lContainerId = pContainer->GetId();
    QVERIFY(pContainer != nullptr);
    qstrKeyname = pContainer->GetKeyname();
    QVERIFY(!qstrKeyname.isEmpty());
    pContainer->SetCaption("TestContainer");
    QVERIFY(pContainer->Commit() > 0);
    m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    pContainer = pCdmOLManager->FindContainerById(lContainerId);
    QVERIFY(pContainer != nullptr);
}

void CwtObjectContainer::FindContainerByKeyname()
{
    CdmContainerManager* pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
    QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
    QVERIFY(pContainer != nullptr);
    qstrKeyname = pContainer->GetKeyname();
    QVERIFY(!qstrKeyname.isEmpty());
    pContainer->SetCaption("TestContainer");
    QVERIFY(pContainer->Commit() > 0);
    m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
    QVERIFY(pContainer != nullptr);
}

void CwtObjectContainer::FindContainerByUri()
{
    CdmContainerManager* pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
    QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
    QVERIFY(pContainer != nullptr);
    QString qstrUri = pContainer->GetUri();
    QVERIFY(!qstrUri.isEmpty());
    pContainer->SetCaption("TestContainer");
    QVERIFY(pContainer->Commit() > 0);
    m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    CdmLocatedElement* pElement = pCdmOLManager->GetDataProvider()->GetUriObject(qstrUri);
    QVERIFY(pElement != nullptr);
    QVERIFY(pElement->IsContainer());
}

void CwtObjectContainer::FindContainerByUriInternal()
{
    CdmContainerManager* pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
    QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
    QVERIFY(pContainer != nullptr);
    QString qstrUri = pContainer->GetUriInternal();
    QVERIFY(!qstrUri.isEmpty());
    pContainer->SetCaption("TestContainer");
    QVERIFY(pContainer->Commit() > 0);
    m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
    pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    CdmLocatedElement* pElement = pCdmOLManager->GetDataProvider()->GetUriObject(qstrUri);
    QVERIFY(pElement != nullptr);
    QVERIFY(pElement->IsContainer());
}

void CwtObjectContainer::RemoveContainerLocally()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   qstrKeyname = pContainer->GetKeyname();
   long lContainerId = pContainer->GetId();
   QVERIFY(!qstrKeyname.isEmpty());
   pContainer->SetCaption("TestContainer");
   QVERIFY(pContainer->Commit() > 0);
   pCdmOLManager->RemoveContainerLocally(pContainer);
   pContainer = pCdmOLManager->FindContainerByIdLocal(lContainerId);
   QVERIFY(pContainer == nullptr);
}

void CwtObjectContainer::RemoveAllContainerLocally()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   qstrKeyname = pContainer->GetKeyname();
   long lContainerId = pContainer->GetId();
   QVERIFY(!qstrKeyname.isEmpty());
   pContainer->SetCaption("TestContainer");
   QVERIFY(pContainer->Commit() > 0);
   pCdmOLManager->RemoveContainerLocally();
   pContainer = pCdmOLManager->FindContainerByIdLocal(lContainerId);
   QVERIFY(pContainer == nullptr);
}

void CwtObjectContainer::CheckUniqueName()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QString qstrDoubleKeyname = qstrKeyname;
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrDoubleKeyname) > 0);
   QVERIFY(qstrKeyname != qstrDoubleKeyname);
}

void CwtObjectContainer::GetContainerList()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY(SUCCESSFULL(pCdmOLManager->CreateContainer(m_pClass, qstrKeyname)));
   QList<QString> qlContainers = pCdmOLManager->GetContainerList(m_pClass->GetId());
   QVERIFY(qlContainers.count() > 0);
}

void CwtObjectContainer::CheckConfigItems()
{
    /* NOT YET IMplemented in Container
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   long lContainerId = pCdmOLManager->CreateContainer(m_pClass, qstrKeyname);
   QVERIFY (lContainerId > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   pContainer->SetC
   QVERIFY(!qstrKeyname.isEmpty());
   pContainer->SetCaption("TestContainer");
   QVERIFY(pContainer->Commit() > 0);
   pCdmOLManager->RemoveContainerLocally();
   pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer == nullptr);
   */
}

void CwtObjectContainer::CreateAndDeleteObject()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   long lContainerId = pContainer->GetId();
   CdmObject* pObject = pContainer->CreateNewObject();
   QVERIFY(pObject != nullptr);
   pObject->SetValue(TEST_MEMBER_KEYNAME, "Test");
   QVERIFY(pObject->Commit() > 0);
   long lObjectId = pObject->GetId();
   m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
   pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   pContainer = pCdmOLManager->FindContainerById(lContainerId);
   QVERIFY(pContainer != nullptr);
   pObject = pContainer->FindObjectById(lObjectId);
   QVERIFY(pObject != nullptr);
   pObject->SetDeleted();
   QVERIFY(pObject->Commit() > 0);
}

void CwtObjectContainer::FindContainerWithObject()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   long lContainerId = pContainer->GetId();
   CdmObject* pObject = pContainer->CreateNewObject();
   QVERIFY(pObject != nullptr);
   pObject->SetValue(TEST_MEMBER_KEYNAME, "Test");
   QVERIFY(pObject->Commit() > 0);
   m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
   pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   pContainer = pCdmOLManager->FindContainerById(lContainerId);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->CountObjects() == 1);
}

void CwtObjectContainer::FindContainerWithoutObjects()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   long lContainerId = pContainer->GetId();
   CdmObject* pObject = pContainer->CreateNewObject();
   QVERIFY(pObject != nullptr);
   pObject->SetValue(TEST_MEMBER_KEYNAME, "Test");
   QVERIFY(pObject->Commit() > 0);
   m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
   pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   pContainer = pCdmOLManager->FindEmptyContainerById(lContainerId);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->CountObjects() == 0);
}

void CwtObjectContainer::CopyContainer()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   CdmObject* pObject = pContainer->CreateNewObject();
   QVERIFY(pObject != nullptr);
   pObject->SetValue(TEST_MEMBER_KEYNAME, "Test");
   QVERIFY(pObject->Commit() > 0);
   CdmObjectContainer* pCopy = pCdmOLManager->CopyContainer(pContainer, true);
   QVERIFY(pCopy != nullptr);
   QVERIFY(pCopy->CountObjects() == 1);
}

void CwtObjectContainer::CreateTreeContainer()
{
   CdmContainerManager* pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   QString qstrKeyname = CwtHelper::CreateUniqueName(TEST_CONTAINER_NAME);
   QVERIFY (pCdmOLManager->CreateContainer(m_pClass, qstrKeyname) > 0);
   CdmObjectContainer* pContainer = pCdmOLManager->FindContainerByKeyname(qstrKeyname);
   QVERIFY(pContainer != nullptr);
   long lContainerId = pContainer->GetId();
   pContainer->SetTree(true);
   QVERIFY(pContainer->Commit() > 0);
   CdmObject* pObject = pContainer->CreateNewObject();
   QVERIFY(pObject != nullptr);
   pObject->SetValue(TEST_MEMBER_KEYNAME, "Test");
   QVERIFY(pObject->Commit() > 0);
   long lObjectParentId = pObject->GetId();
   CdmObject* pObjectChild = pContainer->CreateNewObject();
   QVERIFY(pObjectChild != nullptr);
   pObjectChild->SetValue(TEST_MEMBER_KEYNAME, "Child");
   pObjectChild->SetParent(pObject->GetId());
   long lChildId = pObjectChild->GetId();
   QVERIFY(pObjectChild->Commit() > 0);
   m_pClass = ResetSessionAndLoadClass(TEST_CLASS_NAME);
   pCdmOLManager = GetContainerManager();
   QVERIFY(pCdmOLManager != nullptr);
   pContainer = pCdmOLManager->FindEmptyContainerById(lContainerId);
   QVERIFY(pContainer != nullptr);
   QVERIFY(pContainer->CountObjectsOnDb() == 2);
   pObjectChild = pContainer->FindObjectById(lChildId);
   QVERIFY(pObjectChild != nullptr);
   pObject = pObjectChild->GetParent();
   QVERIFY(pObject != nullptr);
   QVERIFY(lObjectParentId == pObject->GetId());
}
// DeleteAllObjects

// Check Rights assignments




