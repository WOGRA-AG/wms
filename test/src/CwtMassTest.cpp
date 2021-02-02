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
// Own Includes
#include "CwtTest.h"
#include "CwtMassTest.h"

#define TEST_CLASS_NAME "MassTestClass"
#define TEST_CONTAINER_NAME "MassContainer"
#define MESSAGE_INTERVALL 100000
#define CLEANUP_INTERVALL 1000
#define MASS_QUANTITY 3000000

CwtMassTest::CwtMassTest()
{
    m_qstrlMembers.append("Member01");
    m_qstrlMembers.append("Member02");
    m_qstrlMembers.append("Member03");
    m_qstrlMembers.append("Member04");
    m_qstrlMembers.append("Member05");
    m_qstrlMembers.append("Member06");
    m_qstrlMembers.append("Member07");
    m_qstrlMembers.append("Member08");
    m_qstrlMembers.append("Member09");
    m_qstrlMembers.append("Member10");
    m_qstrlMembers.append("Member11");
    m_qstrlMembers.append("Member12");
    m_qstrlMembers.append("Member13");
    m_qstrlMembers.append("Member14");
    m_qstrlMembers.append("Member15");
    m_qstrlMembers.append("Member16");
    m_qstrlMembers.append("Member17");
    m_qstrlMembers.append("Member18");
    m_qstrlMembers.append("Member19");
    m_qstrlMembers.append("Member20");
}

void CwtMassTest::initTestCase()
{
    m_qTimeStart = QTime::currentTime();
   CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
   int iSessionId = 0;
   iSessionId = pFactory->CreateNewSession("admin", "admin");
   QVERIFY(iSessionId > 0);
   CdmDataProvider* pCdmDataProvider = pFactory->GetDataProvider();
   QVERIFY(pCdmDataProvider != nullptr);
   m_qstrDbName = "Test_" + QString::number(iSessionId);
   pCdmDataProvider->RemoveScheme(m_qstrDbName);
   pCdmDataProvider->CreateScheme(m_qstrDbName);
   CdmScheme* pScheme = pCdmDataProvider->GetCurrentScheme();
   QVERIFY(pScheme != nullptr);
}

void CwtMassTest::cleanupTestCase()
{
   //CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();
   //CdmDataProvider* pCdmDataProvider = pFactory->GetDataProvider();
   //pCdmDataProvider->RemoveScheme(m_qstrDbName);

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

void CwtMassTest::MassDataTest()
{
    CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();
    CdmDataProvider* pCdmDataProvider = pFactory->GetDataProvider();
    CdmClass* pClass = CreateClass();

    CdmContainerManager* pContainerManager = pCdmDataProvider->GetContainerManager();
    QVERIFY(pContainerManager != nullptr);
    QString qstrContainerName = TEST_CONTAINER_NAME;
    QVERIFY(pContainerManager->CreateContainer(pClass,qstrContainerName) > 0);

    CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerByKeyname(qstrContainerName);
     QVERIFY(pContainer != nullptr);
     CreateData(pContainer);
}

CdmClass* CwtMassTest::CreateClass()
{
    CdmClass* pClass = nullptr;
    CdmSessionManager* pFactory = CdmSessionManager::GetSessionManager();
    CdmDataProvider* pCdmDataProvider = pFactory->GetDataProvider();

    CdmClassManager* pClassManager = pCdmDataProvider->GetClassManager();
  //  QVERIFY(pClassManager != nullptr);

    pClass = pClassManager->CreateClass(TEST_CLASS_NAME);
 //   QVERIFY(pClass != nullptr);

    for (int i = 0; i < m_qstrlMembers.count(); ++i)
    {
        pClass->CreateMember(m_qstrlMembers[i], eDmValueInt, false,0);
    }

    pClass->Commit();
    return pClass;
}

void CwtMassTest::CreateData(CdmObjectContainer* p_pContainer)
{
    QTime qTimeStart = QTime::currentTime();
    QString qstr = "Start Create Data: " + qTimeStart.toString();
    qDebug(qstr.toLocal8Bit());

    int iValueCounter = 0;
    QTime qTimeObjects = QTime::currentTime();
    QTime qTimeCreateObj;

    for(int iCounter = 0; iCounter <= MASS_QUANTITY; ++iCounter)
    {
        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            qTimeCreateObj = QTime::currentTime();

        }

        CdmObject* pObject = p_pContainer->CreateNewObject();
        QVERIFY(pObject != nullptr);

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            QTime qTimeEndObjects = QTime::currentTime();
            qstr = "Duration p_pContainer->CreateNewObject() " + QString::number(MESSAGE_INTERVALL) + " Objects: " + QString::number(qTimeCreateObj.msecsTo(qTimeEndObjects)) + " msecs.";
            qDebug(qstr.toLocal8Bit());
        }

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            qTimeCreateObj = QTime::currentTime();
        }

        for (int i = 0; i < m_qstrlMembers.count(); ++i)
        {
            pObject->SetValue(m_qstrlMembers[i], QVariant(iValueCounter++));
        }

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            QTime qTimeEndObjects = QTime::currentTime();
            qstr = "Duration p_pContainer->SetValues() " + QString::number(MESSAGE_INTERVALL) + " Objects: " + QString::number(qTimeCreateObj.msecsTo(qTimeEndObjects)) + " msecs.";
            qDebug(qstr.toLocal8Bit());
        }

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            qTimeCreateObj = QTime::currentTime();
        }

        pObject->Commit();

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            QTime qTimeEndObjects = QTime::currentTime();
            qstr = "Duration p_pContainer->Commit() " + QString::number(CLEANUP_INTERVALL) + " Objects: " + QString::number(qTimeCreateObj.msecsTo(qTimeEndObjects)) + " msecs.";
            qDebug(qstr.toLocal8Bit());
        }

        if (iCounter % CLEANUP_INTERVALL == 0 && iCounter > 0)
        {
            p_pContainer->ClearContainerLocal();
        }

        if (iCounter % MESSAGE_INTERVALL == 0 && iCounter > 0)
        {
            qDebug() << iCounter << " objects created";
            QTime qTimeEndObjects = QTime::currentTime();
            qstr = "Duration create " + QString::number(MESSAGE_INTERVALL) + " Objects: " + QString::number(qTimeObjects.msecsTo(qTimeEndObjects)) + " msecs.";
            qDebug(qstr.toLocal8Bit());
            qTimeObjects = QTime::currentTime();
            qDebug() << "Instance count: " << CdmLocatedElement::GetInstanceCount();
        }
    }

    QTime qTimeEnd = QTime::currentTime();
    qstr = "End CreateData: " + qTimeEnd.toString();
    qDebug(qstr.toLocal8Bit());
    qstr = "Duration CreateData: " + QString::number(qTimeStart.msecsTo(qTimeEnd)) + " msecs.";
    qDebug(qstr.toLocal8Bit());
}
