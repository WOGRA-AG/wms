#include "DeleteThread.h"

#include <QLinkedList>
#include <QtTest>

#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CwtHelper.h"


DeleteThread::DeleteThread(QString p_qstrSchemeName, long p_lContainerId, long p_lObjectId)
    : QThread(),
      m_qstrSchemeName(p_qstrSchemeName),
      m_lContainerId(p_lContainerId),
      m_lObjectId(p_lObjectId)
{
}

void DeleteThread::Setup()
{
    CwtHelper::Login(LOGIN_ADMIN, PASSWORD_ADMIN);
    CdmDataProvider *pDataProvider = CwtHelper::GetDataProvider();
    QVERIFY(pDataProvider != nullptr);
    pDataProvider->SetCurrentScheme(GetScheme(m_qstrSchemeName));
}

void DeleteThread::Cleanup()
{
    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    pSessionManager->Logout();
}

void DeleteThread::run()
{
    Setup();

    DeleteObjectInContainer();

    Cleanup();
}

void DeleteThread::DeleteObjectInContainer()
{
    CdmContainerManager* pCdmOLManager = GetContainerManager();
    QVERIFY(pCdmOLManager != nullptr);
    CdmObjectContainer* pContainer = pCdmOLManager->FindContainerById(m_lContainerId);
    QVERIFY(pContainer != nullptr);
    CdmObject* pObject = pContainer->FindObjectById(m_lObjectId);
    QVERIFY(pObject != nullptr);
    pObject->SetDeleted();
    pContainer->ObjectDeletedSlot(pObject);
    QVERIFY(pObject->Commit() > 0);

    QLinkedList<CdmObject*> qllObjects;
    pContainer->GetObjectList(qllObjects);
    QVERIFY(qllObjects.size() == 0);

    pCdmOLManager = GetContainerManager();
    pContainer = pCdmOLManager->FindContainerById(m_lContainerId);
    qllObjects.clear();
    pContainer->GetObjectList(qllObjects);
    QVERIFY(qllObjects.size() == 0);
}

CdmContainerManager* DeleteThread::GetContainerManager()
{
   CdmDataProvider* pCdmDataProvider = CdmSessionManager::GetDataProvider();
   CdmContainerManager* pCdmOLManager = nullptr;

   if (pCdmDataProvider)
   {
      pCdmOLManager = pCdmDataProvider->GetContainerManager();
   }

   return pCdmOLManager;
}

CdmScheme* DeleteThread::GetScheme(QString p_qstrSchemeName)
{
    CdmScheme* pScheme = nullptr;
    CdmDataProvider* pDataProvider = CwtHelper::GetDataProvider();

    if(CHKPTR(pDataProvider))
    {
        if (SUCCESSFULL(pDataProvider->LoadScheme(p_qstrSchemeName)))
        {
            pScheme = pDataProvider->GetCurrentScheme();
        }
    }

    return pScheme;
}
