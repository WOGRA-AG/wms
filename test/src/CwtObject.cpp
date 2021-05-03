/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtObject.cpp
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
#include "CwtObject.h"


CwtObject::CwtObject()
: CwtTestBase(eBmsTestModeDB),
  m_iObjectToCreate(1)
{
}

CwtObject::~CwtObject()
{
}

void CwtObject::initTestCase()
{
}

void CwtObject::cleanupTestCase()
{
}

void CwtObject::init()
{
    InitWithLogin();
    m_lObjectId = 0;
    m_qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(m_qstrSchemeName);
    CdmScheme* pScheme = GetScheme(m_qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    CreateTestClass();
    CreateTestContainers();
}

void CwtObject::cleanup()
{
    CwtHelper::DeleteScheme(m_qstrSchemeName);
    CleanupWithLogout();
}


void CwtObject::CreateObjectSlot()
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    FillObjectData(pObject);
    QVERIFY(pObject->Commit() > 0);
    m_lObjectId = pObject->GetId();
    m_qstrObjectKeyname = pObject->GetKeyname();
}

void CwtObject::LoadObjecByIdSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    QString qstrStringValue;
    pObject->GetValue(MEMBER_STRING_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_STRING);
    bool bBool = false;
    pObject->GetValue(MEMBER_BOOL_KEYNAME, bBool);
    QVERIFY(bBool == VALUE_BOOL);
    pObject->GetValue(MEMBER_CHARDOC_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_CHARDOC);
    QDate qdDate;
    pObject->GetValue(MEMBER_DATE_KEYNAME, qdDate);
    QVERIFY(qdDate == QDate::currentDate());
    QDateTime qdtDateTime;
    pObject->GetValue(MEMBER_DATE_TIME_KEYNAME, qdtDateTime);
    QVERIFY(qdtDateTime.date() == QDate::currentDate());
    double dDouble = 0.0;
    pObject->GetValue(MEMBER_DOUBLE_KEYNAME, dDouble);
    QVERIFY(QString::number(dDouble) == QString::number(VALUE_DOUBLE));
    double fFloat = 0.0;
    pObject->GetValue(MEMBER_FLOAT_KEYNAME, fFloat);
    QVERIFY(QString::number(fFloat) == QString::number(VALUE_FLOAT));
    int iEnum = 0;
    pObject->GetValue(MEMBER_ENUM_KEYNAME, iEnum);
    QVERIFY(iEnum == VALUE_ENUM);
    QCOMPARE(pObject->GetCaption(),QString(VALUE_STRING));
}

void CwtObject::LoadObjecByKeynametSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectByKeyname(m_qstrObjectKeyname);
    QVERIFY(pObject != nullptr);
    QString qstrStringValue;
    pObject->GetValue(MEMBER_STRING_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_STRING);
}

void CwtObject::DeleteObjectSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    pObject->SetDeleted();
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->CountObjectsOnDb() == 0);
}

void CwtObject::DoubleTestSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectByKeyname(m_qstrObjectKeyname);
    QVERIFY(pObject != nullptr);
    double dDouble = 0.0;
    pObject->GetValue(MEMBER_DOUBLE_KEYNAME, dDouble);
    QVERIFY(QString::number(dDouble) == QString::number(VALUE_DOUBLE));
}

void CwtObject::FloatTestSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectByKeyname(m_qstrObjectKeyname);
    QVERIFY(pObject != nullptr);
    double fFloat = 0.0;
    pObject->GetValue(MEMBER_FLOAT_KEYNAME, fFloat);
    QVERIFY(QString::number(fFloat) == QString::number(VALUE_FLOAT));
}

void CwtObject::OwnershipTest()
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();
    m_qstrObjectKeyname = pObject->GetKeyname();
    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    FillObjectData(pRefObject);
    QVERIFY(pRefObject->Commit() > 0);
    pObject->SetValue(MEMBER_STRING_KEYNAME, VALUE_STRING);
    QVERIFY(pObject->Commit() > 0);
    pContainer->RemoveObjectLocal(m_lObjectId);
    pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    QString qstrStringValue;
    pObject->GetValue(MEMBER_STRING_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_STRING);
}

void CwtObject::DeleteOwnershipObjectTest()
{
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_REF);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->CreateNewObject();
    QVERIFY(pObject != nullptr);
    m_lObjectId = pObject->GetId();
    m_qstrObjectKeyname = pObject->GetKeyname();
    CdmValue* pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueObjectRef* pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    CdmObject* pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    FillObjectData(pRefObject);
    QVERIFY(pRefObject->Commit() > 0);
    pRefObject->SetDeleted();
    QVERIFY(pRefObject->Commit() > 0);
    pRefObject = pValueRef->GetObject();
    QVERIFY(pRefObject != nullptr);
    FillObjectData(pRefObject);
    QVERIFY(pRefObject->Commit() > 0);
    pObject->SetValue(MEMBER_STRING_KEYNAME, VALUE_STRING);
    QVERIFY(pObject->Commit() > 0);
    pContainer->RemoveObjectLocal(m_lObjectId);
    pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    pValue = pObject->GetValue(MEMBER_OBJREF_KEYNAME);
    QVERIFY(pValue != nullptr);
    pValueRef = dynamic_cast<CdmValueObjectRef*>(pValue);
    QVERIFY(pValueRef != nullptr);
    QString qstrStringValue;
    pObject->GetValue(MEMBER_STRING_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_STRING);
}

void CwtObject::IsTypeOfTest()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    QVERIFY(pObject->IsTypeOf(TEST_CLASS_NAME_NO_REF));
    QVERIFY(!pObject->IsTypeOf(TEST_CLASS_NAME_REF));
    QVERIFY(!pObject->IsTypeOf("bla"));
}

void CwtObject::FindObjectByIndexTest()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectByIndex(0);
    QVERIFY(pObject != nullptr);
    QString qstrStringValue;
    pObject->GetValue(MEMBER_STRING_KEYNAME, qstrStringValue);
    QVERIFY(qstrStringValue == VALUE_STRING);
}

void CwtObject::FormulaTest()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectByIndex(0);
    QVERIFY(pObject != nullptr);
    CdmValue* pValue = pObject->GetValue(MEMBER_FORMULA_KEYNAME);
    QVERIFY(pValue != nullptr);
    CdmValueFormula* pFormula = dynamic_cast<CdmValueFormula*>(pValue);
    QVERIFY(pFormula != nullptr);
    int i = pFormula->GetValueAsInt();
    QVERIFY(i == VALUE_LONG + VALUE_INT);
}

void CwtObject::CheckListContentSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmValueListInt* pValue = dynamic_cast<CdmValueListInt*> (pObject->GetValue(MEMBER_LIST_INT_KEYNAME));
    QVERIFY(pValue != nullptr);
    QList<int> qListInt = pValue->GetList();
    QVERIFY(qListInt.count() == 3);
    QVERIFY(qListInt.contains(78));
    QVERIFY(qListInt.contains(15));
    QVERIFY(qListInt.contains(-17));
}

void CwtObject::CheckMapContentSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmValue* pValue = pObject->GetValue(MEMBER_MAP_STRING_STRING_KEYNAME);
    CdmValueDictStringString* pDictValue = dynamic_cast<CdmValueDictStringString*> (pValue);
    QVERIFY(pDictValue != nullptr);
    QMap<QString, QString> qMap = pDictValue->GetDict();
    QVERIFY(qMap["first"] == "first");
    QVERIFY(qMap["second"] == "second");
    QVERIFY(qMap["third"] == "third");
}

void CwtObject::LockObjectSlot()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    pContainer->RemoveObjectLocal(m_lObjectId);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    QVERIFY(pObject->LockObjectOnDb() > 0);
    QVERIFY(pObject->UnlockObjectOnDb() > 0);
}

void CwtObject::BinDocTestSlot()
{
    QString qstrFile = "bindoc.txt";
    QString qstrFilePathAndName = QApplication::applicationDirPath() + "/" + qstrFile;
    QFile qFile(qstrFilePathAndName);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&qFile);
        stream << "test";
        qFile.close();
    }

    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmValue* pValue = pObject->GetValue(MEMBER_BINDOC_KEYNAME);
    auto pBinDoc = dynamic_cast<CdmValueBinaryDocument*> (pValue);
    QVERIFY(pBinDoc != nullptr);
    pBinDoc->SetValue(qstrFilePathAndName, "txt");
    pObject->Commit();
    pContainer->RemoveObjectLocal(m_lObjectId);
    pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    pValue = pObject->GetValue(MEMBER_BINDOC_KEYNAME);
    pBinDoc = dynamic_cast<CdmValueBinaryDocument*> (pValue);
    qstrFilePathAndName = pBinDoc->GetFilename();
    QVERIFY(qstrFilePathAndName == qstrFile);
    QByteArray qqbaValue = pBinDoc->GetByteArray();
    QVERIFY(qqbaValue == "test");
}

void CwtObject::CreateObjectChangeMemberTypeAndDeleteObject()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmClass* pClass = pObject->GetClass();
    QVERIFY(pClass != nullptr);
    CdmMember* pMember = const_cast<CdmMember*> (pClass->FindMember(MEMBER_STRING_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetValueType(eDmValueBool);
    QVERIFY(SUCCESSFULL(pClass->Commit()));
    pObject->SetDeleted();
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->CountObjectsOnDb() == 0);
}

void CwtObject::CreateObjectSetUniqueCaptionMemberAndSearchForKeyname()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmClass* pClass = pObject->GetClass();
    QVERIFY(pClass != nullptr);
    CdmMember* pMember = const_cast<CdmMember*> (pClass->FindMember(MEMBER_STRING_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetUnique(true);
    pClass->SetCaptionMember(MEMBER_STRING_KEYNAME);
    QVERIFY(SUCCESSFULL(pClass->Commit()));
    QString qstrTargetKeyname = "UNIQUE";
    pObject->SetValue(MEMBER_STRING_KEYNAME,qstrTargetKeyname);
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->FindObjectByKeyname(qstrTargetKeyname) == pObject);
}

void CwtObject::CreateObjectSetNotUniqueCaptionMemberAndSearchForKeyname()
{
    CreateObjectSlot();
    CdmObjectContainer* pContainer = GetContainer(TEST_CONTAINER_NAME_ALL_MEMBERS);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    CdmClass* pClass = pObject->GetClass();
    QVERIFY(pClass != nullptr);
    CdmMember* pMember = const_cast<CdmMember*> (pClass->FindMember(MEMBER_STRING_KEYNAME));
    QVERIFY(pMember != nullptr);
    pMember->SetUnique(false);
    pClass->SetCaptionMember(MEMBER_STRING_KEYNAME);
    QVERIFY(SUCCESSFULL(pClass->Commit()));
    QString qstrTargetKeyname = "NOTUNIQUE";
    pObject->SetValue(MEMBER_STRING_KEYNAME,qstrTargetKeyname);
    QVERIFY(pObject->Commit() > 0);
    QVERIFY(pContainer->FindObjectByKeyname(qstrTargetKeyname) == nullptr);
}
