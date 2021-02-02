// System and Qt Includes
#include <QDateTime>
#include <QtTest>
#include <QUuid>

// WMS Core Includes
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CumUser.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CwtHelper.h"



QString CwtHelper::CreateUniqueName(QString p_qstrName)
{
    QString qstrName = p_qstrName + QUuid::createUuid().toString();
    qstrName = qstrName.replace("-", "");
    qstrName = qstrName.replace("{", "");
    qstrName = qstrName.replace("}", "");
    return qstrName;
}


void CwtHelper::Login(QString p_qstrLogin, QString p_qstrPassword)
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    QVERIFY(pSessionManager->CreateNewSession(p_qstrLogin, p_qstrPassword) > 0);
}

void CwtHelper::Logout()
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    pSessionManager->Logout();
    QVERIFY(pSessionManager->GetOpenSessions() == 0);
}

CumUserManager* CwtHelper::GetUserManager()
{
    CumUserManager* pUserManager = nullptr;
    CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();

    if (pCdmDataProvider)
    {
       pUserManager = pCdmDataProvider->GetUserManager();

    }

    return pUserManager;
}

void CwtHelper::CreateScheme(QString p_qstrName)
{
    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);
    pCdmDataProvider->RemoveScheme(p_qstrName);
    QVERIFY(pCdmDataProvider->CreateScheme(p_qstrName) > 0);
}

void CwtHelper::DeleteScheme(QString p_qstrName)
{
    CdmDataProvider* pCdmDataProvider = GetDataProvider();
    QVERIFY(pCdmDataProvider != nullptr);
    QVERIFY(pCdmDataProvider->RemoveScheme(p_qstrName) > 0 );
}

CdmDataProvider* CwtHelper::GetDataProvider()
{
   CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();
   return pFactory->GetDataProvider();
}

CdmClassManager* CwtHelper::GetClassManager()
{
    CdmDataProvider* pDataProvider = GetDataProvider();
    return pDataProvider->GetClassManager();
}

CumUser* CwtHelper::CreateUser(QString p_qstrIdentitfier, CumUserManager* pUserManager)
{
    CumUser* pUser = new CumUser(pUserManager);

    pUser->SetActive(true);
    pUser->SetFirstName(p_qstrIdentitfier);
    pUser->SetLastName(p_qstrIdentitfier);
    pUser->SetLogin(p_qstrIdentitfier);
    pUser->SetPassword(p_qstrIdentitfier);
    pUser->SetEmail(p_qstrIdentitfier);
    pUser->SetSchemeIndependent(true);
    pUser->SetIdentityKey(p_qstrIdentitfier);
    pUser->SetAdministrator(false);
    return pUser;
}

CdmClass* CwtHelper::CreateTestClass()
{
    CdmClass* pClass = nullptr;
    CdmClassManager* pClassManager = GetClassManager();

    if(CHKPTR(pClassManager))
    {
        pClass = pClassManager->CreateClass(TEST_CLASS_NAME);
        if (CHKPTR(pClass))
        {
            pClass->SetCaption("blabla");
            pClass->SetComment("blibli");


            CdmMember* pMember = pClass->CreateMember(TEST_MEMBER_KEYNAME, eDmValueString, false, 0);

            if (CHKPTR(pMember))
            {
                pMember->SetCaption("Zeichenkette");
                pMember->SetComment("Das ist eine Zeichenkette.");
            }

            pClass->Commit();
        }
    }

    return pClass;
}
