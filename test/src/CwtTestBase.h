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

#ifndef CWTTESTBASE_H
#define CWTTESTBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QtTest>
#include <QObject>
#include <QDateTime>

#include "CwmsTimeMeassurement.h"

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"


// Forwards
class CdmScheme;
class CdmDataProvider;
class CdmClassManager;
class CumUserManager;
class CdmContainerManager;

// Defines
#define TEST_CLASS_NAME_NO_REF "TestNoRef"
#define TEST_CLASS_NAME_REF "TestRef"
#define TEST_CLASS_NAME_REF_REF "TestRefRef"
#define MEMBER_STRING_KEYNAME "zeichen"
#define VALUE_STRING "blubb"
#define OBJECT_CAPTION "Caption"
#define MEMBER_INT_KEYNAME "einfachezahl"
#define VALUE_INT 42
#define MEMBER_LONG_KEYNAME "doppeltezahl"
#define VALUE_LONG 42000
#define MEMBER_FLOAT_KEYNAME "einfachenummer"
#define VALUE_FLOAT 42.6699982
#define MEMBER_DOUBLE_KEYNAME "doppeltenummer"
#define VALUE_DOUBLE 42.6778967
#define MEMBER_BOOL_KEYNAME "wahrheit"
#define VALUE_BOOL true
#define MEMBER_CHARDOC_KEYNAME "textdoc"
#define VALUE_CHARDOC "blubb\ntest"
#define MEMBER_BINDOC_KEYNAME "doc"
#define MEMBER_USER_KEYNAME "benutzer"
#define MEMBER_USER_GROUP_KEYNAME "gruppe"
#define MEMBER_ENUM_KEYNAME "auswahl"
#define VALUE_ENUM 1
#define MEMBER_DATE_KEYNAME "datum"
#define MEMBER_TIME_KEYNAME "zeit"
#define MEMBER_DATE_TIME_KEYNAME "zeitstempel"
#define MEMBER_FORMULA_KEYNAME "formel"
#define MEMBER_COUNTER_KEYNAME "zaehler"
#define MEMBER_LIST_INT_KEYNAME "listezahlen"
#define MEMBER_LIST_DOUBLE_KEYNAME "listnummer"
#define MEMBER_LIST_STRING_KEYNAME "listzeichen"
#define MEMBER_MAP_INT_INT_KEYNAME "mapintint"
#define MEMBER_MAP_INT_DOUBLE_KEYNAME "mapintdouble"
#define MEMBER_MAP_INT_STRING_KEYNAME "mapintstring"
#define MEMBER_MAP_STRING_INT_KEYNAME "mapstringint"
#define MEMBER_MAP_STRING_DOUBLE_KEYNAME "mapstringdouble"
#define MEMBER_MAP_STRING_STRING_KEYNAME "mapstringstring"
#define MEMBER_OBJREF_KEYNAME "objref"
#define MEMBER_OBJREF_REF2_KEYNAME "objref2"

#define TEST_CONTAINER_NAME_ALL_MEMBERS "TestContainerAllMembers"
#define TEST_CONTAINER_NAME_REF "TestContainerRef"
#define TEST_CONTAINER_NAME_REF_REF "TestContainerRefRef"

// enums
enum EwmsTestMode
{
   eBmsTestModeWeb,
   eBmsTestModeDB,
   eBmsTestModeSQLITE,
};

/* 
 * This class implements the base class for all tests
 */
class CwtTestBase : public QObject
{
   Q_OBJECT

private:
    CwmsTimeMeassurement m_TestTimeWithPreparation;
    CwmsTimeMeassurement m_pureTestTime;
    QTime m_qTimeStartSingleTest;
    QDateTime m_qdTestDateTime;
    QDateTime m_qdtDateTime;

    void AddUserGroup(CdmObject *p_pObject);
    void AddListValues(CdmObject *p_pObject);
    void AddDictValues(CdmObject *p_pObject);
    void AddIntDoubleDictValues(CdmObject* p_pObject);
    void AddIntIntDictValues(CdmObject* p_pObject);
    void AddIntStringDictValues(CdmObject* p_pObject);
    void AddStringDoubleDictValues(CdmObject* p_pObject);
    void AddStringIntDictValues(CdmObject* p_pObject);
    void AddStringStringDictValues(CdmObject* p_pObject);

   protected:


      EwmsTestMode m_eTestMode;
      QString m_qstrSchemeName;
      CdmClass* m_pClassNoRef;
      CdmClass* m_pClassRef;
      CdmClass* m_pClassRefRef;

      
    CwtTestBase(EwmsTestMode p_eMode);
    virtual ~CwtTestBase( );
    int Login();
    void FillObjectData(CdmObject *p_pObject);

    CdmDataProvider* GetDataProvider();

    CdmContainerManager* GetContainerManager();
    CdmClassManager* GetClassManager();
    void Logout();
    void ResetSession();
    CdmScheme *GetScheme(QString p_qstrSchemeName);
    void InitWithLogin();
    void InitWithoutLogin();
    void CleanupWithoutLogout();
    void CleanupWithLogout();
    void DeleteUser(CumUser *p_pUser);
    CumUser *CreateTestUser();
    void DeleteUser(QString p_qstrUser);
    void DeleteTestUser();
    CdmClass *ResetSessionAndLoadClass(QString p_qstrClassName);
    CdmObjectContainer *GetContainer(QString p_qstrKeyname);
    CumUserManager *GetUserManager();
    void CreateTestClass();
    void CreateTestContainers();
    void StartPureTest();
    void EndPureTest();
    CumUserGroup *CreateTestUserGroup();
};

#endif //
