/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwtDatabaseTest.cpp
 ** Started Implementation: 2013/08/30
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
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmMember.h"
#include "CdmQuery.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"

//// WEB Client Includes
//#include "CwcDataAccess.h"

//// ODBC Access Includes
//#include "CdbDataAccess.h"

//// SQLITE Access Includes
//#include "CslDataAccess.h"

// own Includes
#include "CwtHelper.h"
#include "CwtScheme.h"

#define LANGUAGE_1 "Deutsch"
#define LANGUAGE_2 "Englisch"
#define LANGUAGE_3 "Französisch"

CwtScheme::CwtScheme()
    : CwtTestBase(eBmsTestModeDB)
{
}

CwtScheme::~CwtScheme()
{
}

void CwtScheme::initTestCase()
{
}

void CwtScheme::cleanupTestCase()
{
}

void CwtScheme::init()
{
    InitWithLogin();
    StartPureTest();
}

void CwtScheme::cleanup()
{
    EndPureTest();
    CleanupWithLogout();
}

void CwtScheme::CreateAndDeleteScheme()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);

    CdmScheme* pScheme = GetScheme(qstrSchemeName);

    QVERIFY(pScheme != nullptr);
    QVERIFY(pScheme->GetVersion() == 1);
    QVERIFY(pScheme->GetClassManager() != nullptr);
    QVERIFY(pScheme->GetContainerManager() != nullptr);
    QVERIFY(pScheme->GetCurrentLanguageName() == "");
    QVERIFY(pScheme->GetId() > 0);

    CwtHelper::DeleteScheme(qstrSchemeName);
}

void CwtScheme::CheckSchemeListSlot()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);
    CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

    if (pCdmDataProvider)
    {
        IdmDataAccess* pIdmDataAccess = pCdmDataProvider->GetDataAccess();

        if (pIdmDataAccess)
        {
            QList<QString> qllDatabases;
            pIdmDataAccess->GetSchemeList(qllDatabases);

            QVERIFY(qllDatabases.count() > 0);
        }
    }

    CwtHelper::DeleteScheme(qstrSchemeName);
}

void CwtScheme::LoadSchemeSlot()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);
    ResetSession();
    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);

    pCdmDataProvider->LoadScheme(qstrSchemeName);

    CdmScheme* pCdmDatabase = pCdmDataProvider->GetCurrentScheme();
    QVERIFY(pCdmDatabase != nullptr);
    QVERIFY(pCdmDatabase->GetSchemeName() == qstrSchemeName);
    CwtHelper::DeleteScheme(qstrSchemeName);
}


void CwtScheme::TryToLoadNotExistingSchemeSlot()
{
    QString qstrDbName = "t123Ubvu";

    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);

    pCdmDataProvider->LoadScheme(qstrDbName);

    CdmScheme* pCdmDatabase = pCdmDataProvider->GetCurrentScheme();
    QVERIFY(pCdmDatabase == nullptr);
}


void CwtScheme::AddLanguagesToScheme()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);
    CdmScheme* pScheme = GetScheme(qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    QString qstrLanguage1 = LANGUAGE_1;
    QString qstrLanguage2 = LANGUAGE_2;
    QString qstrLanguage3 = LANGUAGE_3;
    pScheme->AddLanguage(qstrLanguage1);
    pScheme->AddLanguage(qstrLanguage2);
    pScheme->AddLanguage(qstrLanguage3);
    ResetSession();
    pScheme = GetScheme(qstrSchemeName);
    QVERIFY (pScheme->GetLanguageId(qstrLanguage1) > 0);
    QVERIFY (pScheme->GetLanguageId(qstrLanguage2) > 0);
    QVERIFY (pScheme->GetLanguageId(qstrLanguage3) > 0);
    CwtHelper::DeleteScheme(qstrSchemeName);
}

void CwtScheme::TryToCreateTwoSchemesWithTheSameName()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);
    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);
    QVERIFY(pCdmDataProvider->CreateScheme(qstrSchemeName) < 0);
    CwtHelper::DeleteScheme(qstrSchemeName);
}

void CwtScheme::AddTheSameLanguageTwice()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);
    CdmScheme* pScheme = GetScheme(qstrSchemeName);
    QVERIFY(pScheme != nullptr);

    QString qstrLanguage1 = LANGUAGE_1;

    pScheme->AddLanguage(qstrLanguage1);
    pScheme->AddLanguage(qstrLanguage1);


    QVERIFY(pScheme->GetLanguageMap().count() == 1);

    CwtHelper::DeleteScheme(qstrSchemeName);
}


void CwtScheme::UpdateVersion()
{
    QString qstrSchemeName = CwtHelper::CreateUniqueName("Test");
    CwtHelper::CreateScheme(qstrSchemeName);

    CdmScheme* pScheme = GetScheme(qstrSchemeName);
    QVERIFY(pScheme != nullptr);
    pScheme->SetVersion(2);
    QVERIFY(pScheme->Commit() > 0);
    ResetSession();
    pScheme = GetScheme(qstrSchemeName);
    QVERIFY(pScheme->GetVersion() == 2);
    CwtHelper::DeleteScheme(qstrSchemeName);
}
