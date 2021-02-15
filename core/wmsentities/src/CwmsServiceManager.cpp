
// System and Qt Includes
#include <QUuid>
#include <QTimer>
#include <QNetworkInterface>
#include <QHostAddress>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmScheme.h"
#include "CdmPackage.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmContainerManager.h"


// own Includes
#include "CwmsTechnicalSchemeSwitch.h"
#include "CwmsServerLogin.h"
#include "CwmsContext.h"
#include "CwmsServiceManager.h"

#define SERVICE_MANAGER_CLASS "ServiceManager"
#define SERVICE_INSTANCE_CLASS "ServiceInstance"
#define SERVICE_MANAGER_CONTAINER "RunningServices"
#define SERVICE_INSTANCE_CCONTAINER "ServiceInstances"

#define SERVICE_ID "ServiceId"
#define SERVICE_LAST_UPDATE "LastUpdate"
#define SERVER_ID "ServerId"
#define TECHNICAL_PACKAGE "Technical"
#define SERVICE_MANAGER_PACKAGE "ServiceManager"
#define SERVICE_INSTANCE_STARTED "InstanceStarted"
#define SERVICE_INSTANCE_IP "Ips"
#define SERVICE_INSTANCE_STOPPED "InstanceStopped"
#define SERVICE_CONTEXT_TYPE "ContextType"

CwmsServiceManager::CwmsServiceManager()
{
    WMS_SERVER_LOGIN;
    WMS_TECHNICALSCHEME_SWITCH;

    if (!CheckDataStructure())
    {
        CreateDataStructure();
    }

    m_qstrServiceManagerId = QUuid::createUuid().toString();
    RegisterServiceManager();
}

CwmsServiceManager::~CwmsServiceManager()
{
    DeleteAllServices();
    SignOffServiceManager();
}

void CwmsServiceManager::AddService(IwmsRunningService *p_pService)
{
    SYNCHRONIZED;
    if (p_pService)
    {
        m_qmServices.insert(p_pService->GetServiceId(), p_pService);
        ServiceCheck(p_pService);
        QTimer* pTimer = new QTimer();
        pTimer->setSingleShot(true);
        m_qmServiceTimers.insert(pTimer, p_pService->GetServiceId());
        connect(pTimer, SIGNAL(timeout()), this, SLOT(ServiceCheckSlot()));
        pTimer->start(GetTimerIntervall(p_pService));
    }
}

void CwmsServiceManager::DeleteService(QString p_qstrServiceId)
{
    SYNCHRONIZED;
    DeleteTimer(p_qstrServiceId);

    if (m_qmServices.contains(p_qstrServiceId))
    {
        IwmsRunningService* pService = m_qmServices[p_qstrServiceId];
        m_qmServices.remove(p_qstrServiceId);
        DELPTR(pService);
    }
}

void CwmsServiceManager::DeleteAllServices()
{
    SYNCHRONIZED;
    DeleteTimers();
    DeleteServices();
}

void CwmsServiceManager::DeleteServices()
{
    SYNCHRONIZED;
    QMap<QString, IwmsRunningService*>::iterator qmIt = m_qmServices.begin();
    QMap<QString, IwmsRunningService*>::iterator qmItEnd = m_qmServices.end();

    for (;qmIt != qmItEnd; ++qmIt)
    {
        DELPTR(qmIt.value());
    }

    m_qmServices.clear();
}

void CwmsServiceManager::DeleteTimers()
{
    SYNCHRONIZED;
    QMap<QTimer*, QString>::iterator qmIt = m_qmServiceTimers.begin();
    QMap<QTimer*, QString>::iterator qmItEnd= m_qmServiceTimers.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        QTimer* pTimer = qmIt.key();
        DELPTR(pTimer);
    }

    m_qmServiceTimers.clear();
}

void CwmsServiceManager::DeleteTimer(QString p_qstrServiceId)
{
    SYNCHRONIZED;
    QMap<QTimer*, QString>::iterator qmIt = m_qmServiceTimers.begin();
    QMap<QTimer*, QString>::iterator qmItEnd= m_qmServiceTimers.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        if (qmIt.value() == p_qstrServiceId)
        {
            QTimer* pTimer = qmIt.key();
            m_qmServiceTimers.remove(pTimer);
            DELPTR(pTimer);
            break;
        }
    }
}

bool CwmsServiceManager::CheckDataStructure()
{
    SYNCHRONIZED;
    bool bRet = false;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

       if (CHKPTR(pCdmClassManager))
       {
           if (pCdmClassManager->ExistPackage(TECHNICAL_PACKAGE "." SERVICE_MANAGER_PACKAGE))
           {
               bRet = true;
           }
       }
    }

    return bRet;
}

void CwmsServiceManager::CreateDataStructure()
{
    SYNCHRONIZED;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

       if (CHKPTR(pCdmClassManager))
       {
           CdmPackage* pPackage = FindOrCreateTechnicalPackage();

           if (CHKPTR(pPackage))
           {
               pPackage = pCdmClassManager->CreatePackage(SERVICE_MANAGER_PACKAGE, pPackage);
               CdmClass* pClassServiceManager = pCdmClassManager->CreateClass(SERVICE_MANAGER_CLASS, pPackage);
               CdmClass* pClassServiceInstance = pCdmClassManager->CreateClass(SERVICE_INSTANCE_CLASS, pPackage);

               AddRunningServiceClassMembers(pClassServiceManager);
               AddServiceInstanceClassMembers(pClassServiceInstance);

               CreateServiceManagerContainer(pClassServiceManager);
               CreateServiceInstanceContainer(pClassServiceInstance);
           }
       }
    }

}

void CwmsServiceManager::AddServiceInstanceClassMembers(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        p_pClass->SetCaption(SERVICE_MANAGER_CLASS);
        p_pClass->SetComment("The class for for running services in background");
        CdmMember* pCdmMember = nullptr;

        pCdmMember = p_pClass->CreateMember(SERVER_ID, eDmValueString, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVER_ID);
           pCdmMember->SetComment("The server Manager for managing background services");
        }

        pCdmMember = p_pClass->CreateMember(SERVICE_INSTANCE_IP, eDmValueString, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_INSTANCE_IP);
           pCdmMember->SetComment("The server IP addresses running a service");
        }

        pCdmMember = p_pClass->CreateMember(SERVICE_INSTANCE_STARTED, eDmValueDateTime, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_INSTANCE_STARTED);
           pCdmMember->SetComment("The timestamp of the instance start");
        }

        pCdmMember = p_pClass->CreateMember(SERVICE_INSTANCE_STOPPED, eDmValueDateTime, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_INSTANCE_STOPPED);
           pCdmMember->SetComment("The timestamp of the instance start");
        }

        pCdmMember = p_pClass->CreateMember(SERVICE_CONTEXT_TYPE, eDmValueEnum, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_CONTEXT_TYPE);
           pCdmMember->SetComment("The timestamp of the instance start");
           pCdmMember->SetValidationCode("Server, Admin, Application, CommandLineInterface");
        }

        p_pClass->Commit();
    }
}

void CwmsServiceManager::AddRunningServiceClassMembers(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        p_pClass->SetCaption(SERVICE_MANAGER_CLASS);
        p_pClass->SetComment("The class for for running services in background");

        CdmMember* pCdmMember = nullptr;
        pCdmMember = p_pClass->CreateMember(SERVICE_ID, eDmValueString, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_ID);
           pCdmMember->SetComment("The running configuration");
        }

        pCdmMember = p_pClass->CreateMember(SERVICE_LAST_UPDATE, eDmValueDateTime, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVICE_LAST_UPDATE);
           pCdmMember->SetComment("The timestamp of the last refresh");
        }

        pCdmMember = p_pClass->CreateMember(SERVER_ID, eDmValueString, true, 0);

        if (CHKPTR(pCdmMember))
        {
           pCdmMember->SetCaption(SERVER_ID);
           pCdmMember->SetComment("The servermanager which runs the service");
        }

        p_pClass->Commit();
    }
}

CdmPackage* CwmsServiceManager::FindOrCreateTechnicalPackage()
{
    CdmPackage* pPackage = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
       CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

       if (CHKPTR(pCdmClassManager))
       {
           pPackage = pCdmClassManager->FindPackageByName(TECHNICAL_PACKAGE);

           if (!pPackage)
           {
               pPackage = pCdmClassManager->CreatePackage(TECHNICAL_PACKAGE, nullptr);
           }
       }
    }

    return pPackage;
}

void CwmsServiceManager::CreateServiceManagerContainer(CdmClass* p_pClass)
{
    CreateContainer(p_pClass, SERVICE_MANAGER_CONTAINER);
}

void CwmsServiceManager::CreateServiceInstanceContainer(CdmClass* p_pClass)
{
   CreateContainer(p_pClass, SERVICE_INSTANCE_CCONTAINER);
}

void CwmsServiceManager::CreateContainer(CdmClass* p_pClass, QString p_qstrKeyname)
{
    if (CHKPTR(p_pClass))
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
        {
            CdmContainerManager*pContainerManager = pCdmManager->GetContainerManager();

            if (CHKPTR(pContainerManager))
            {
                pContainerManager->CreateContainer(p_pClass, p_qstrKeyname);
            }
        }
    }
}

CdmObjectContainer* CwmsServiceManager::GetServiceManagerContainer()
{
    return GetContainer(SERVICE_MANAGER_CONTAINER);
}

CdmObjectContainer* CwmsServiceManager::GetServiceInstanceContainer()
{
    return GetContainer(SERVICE_INSTANCE_CCONTAINER);
}

CdmObjectContainer* CwmsServiceManager::GetContainer(QString p_qstrKeyname)
{
    SYNCHRONIZED;
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager) && pCdmManager->GetCurrentScheme())
    {
        CdmContainerManager*pContainerManager = pCdmManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindEmptyContainerByKeyname(p_qstrKeyname);
        }
    }

    return pContainer;
}

void CwmsServiceManager::ServiceCheckSlot()
{
    SYNCHRONIZED;
    QTimer* pTimer = dynamic_cast<QTimer*> (sender());

    if (CHKPTR(pTimer))
    {
        if (m_qmServiceTimers.contains(pTimer))
        {
            IwmsRunningService* pService = m_qmServices[m_qmServiceTimers[pTimer]];

            if (CHKPTR(pService))
            {
                ServiceCheck(pService);
                pTimer->start(GetTimerIntervall(pService));
            }
        }
    }
}

int CwmsServiceManager::GetTimerIntervall(IwmsRunningService* p_pService)
{
    int iRet = -1;

    if (CHKPTR(p_pService))
    {
        if (p_pService->IsRunning())
        {
            iRet = p_pService->GetCheckIntervall() * 1000 / 2;
        }
        else
        {
            iRet = p_pService->GetCheckIntervall() * 1000;
        }
    }

    return iRet;
}

void CwmsServiceManager::ServiceCheck(IwmsRunningService* p_pService)
{
    SYNCHRONIZED;
    WMS_SERVER_LOGIN;
    WMS_TECHNICALSCHEME_SWITCH;

    if (CHKPTR(p_pService))
    {
        if (p_pService->IsRunning())
        {
            UpdateRunningData(p_pService);
        }
        else
        {
            if (ServiceCanStartCheck(p_pService))
            {
                UpdateRunningData(p_pService);
                p_pService->StartService();
            }
        }
    }
}

void CwmsServiceManager::UpdateRunningData(IwmsRunningService* p_pService)
{
    if (CHKPTR(p_pService))
    {
        QString qstrServiceId = p_pService->GetServiceId();
        WMS_TECHNICALSCHEME_SWITCH;
        CdmObjectContainer* pContainer = GetServiceManagerContainer();

        if (CHKPTR(pContainer))
        {
            QString qstrWql = QString("select from %1 where AND(" SERVER_ID " = \"%2\", " SERVICE_ID " = \"%3\")")
                    .arg(pContainer->GetKeyname())
                    .arg(m_qstrServiceManagerId)
                    .arg(qstrServiceId);

            CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

            if (CHKPTR(pQuery) && pQuery->IsValid())
            {
                int iResults = pQuery->GetResultCount();

                if (iResults > 1)
                {
                    ERR("Only one ServiceManager entry expected but got " + QString::number(iResults));
                }
                else if (iResults == 1)
                {
                    CdmObject* pObject = pQuery->GetResultObjectAt(0);

                    if (CHKPTR(pObject))
                    {
                        pObject->SetValue(SERVICE_LAST_UPDATE, QDateTime::currentDateTime());
                        pObject->Commit();
                    }
                }
                else if (iResults == 0)
                {
                    CdmObject* pObject = pContainer->CreateNewObject();

                    if (CHKPTR(pObject))
                    {
                        pObject->SetValue(SERVICE_ID, p_pService->GetServiceId());
                        pObject->SetValue(SERVER_ID, m_qstrServiceManagerId);
                        pObject->SetValue(SERVICE_LAST_UPDATE, QDateTime::currentDateTime());
                        pObject->Commit();
                    }
                }
            }

            DELPTR(pQuery);
        }
    }
}

bool CwmsServiceManager::ServiceCanStartCheck(IwmsRunningService* p_pService)
{
    bool bRet = false;

    if (CHKPTR(p_pService))
    {
        QString qstrServiceId = p_pService->GetServiceId();
        WMS_TECHNICALSCHEME_SWITCH;
        CdmObjectContainer* pContainer = GetServiceManagerContainer();

        if (CHKPTR(pContainer))
        {
            QDateTime qdtStart = QDateTime::currentDateTime();
            qdtStart = qdtStart.addMSecs(p_pService->GetCheckIntervall() * (-1000));
            QString qstrWql = QString("select from %1 where AND(" SERVICE_ID " = \"%2\", " SERVICE_LAST_UPDATE " >= \"%3\", " SERVICE_LAST_UPDATE " <= \"%4\")")
                    .arg(pContainer->GetKeyname())
                    .arg(qstrServiceId)
                    .arg(qdtStart.toString("yyyy-MM-dd HH:mm:ss"))
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

            CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

            if (CHKPTR(pQuery) && pQuery->IsValid())
            {
                bRet = (pQuery->GetResultCount() == 0);
            }

            DELPTR(pQuery);
        }
    }

    return bRet;
}

void CwmsServiceManager::RegisterServiceManager()
{
    SYNCHRONIZED;
    WMS_SERVER_LOGIN;
    WMS_TECHNICALSCHEME_SWITCH;
    CdmObjectContainer* pContainer = GetServiceInstanceContainer();

    if (pContainer)
    {
        CdmObject* pObject = pContainer->CreateNewObject();

        if (CHKPTR(pObject))
        {
            pObject->SetValue(SERVER_ID, m_qstrServiceManagerId);
            pObject->SetValue(SERVICE_INSTANCE_STARTED, QDateTime::currentDateTime());

            CwmsContext* pContext = CwmsContext::GetContext();

            if (CHKPTR(pContext))
            {
                pObject->SetValue(SERVICE_CONTEXT_TYPE, pContext->GetContextType());
            }

            QString qstrAddresses;

            foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
                     qstrAddresses += address.toString() + " ";
            }

            pObject->SetValue(SERVICE_INSTANCE_IP, qstrAddresses);
            pObject->Commit();
        }
    }
}

CdmObject* CwmsServiceManager::GetServiceInstanceObject()
{
    SYNCHRONIZED;
    WMS_SERVER_LOGIN;
    WMS_TECHNICALSCHEME_SWITCH;
    CdmObject* pObject = nullptr;
    CdmObjectContainer* pContainer = GetServiceInstanceContainer();

    if (CHKPTR(pContainer))
    {
        QString qstrWql = QString("select from %1 where " SERVER_ID " = %2")
                .arg(pContainer->GetKeyname())
                .arg(m_qstrServiceManagerId);

        CdmQuery* pQuery = CdmQueryBuilder::ExecuteQuery(qstrWql);

        if (CHKPTR(pQuery) && pQuery->IsValid())
        {
            int iResults = pQuery->GetResultCount();

            if (iResults != 1)
            {
                ERR("Only one ServiceManager instance expected but got " + QString::number(iResults));
            }
            else
            {
                pObject = pQuery->GetResultObjectAt(0);
            }
        }

        DELPTR(pQuery);
    }

    return pObject;
}

void CwmsServiceManager::SignOffServiceManager()
{
    SYNCHRONIZED;
    WMS_SERVER_LOGIN;
    WMS_TECHNICALSCHEME_SWITCH;
    CdmObject* pObject = GetServiceInstanceObject();

    if (CHKPTR(pObject))
    {
        pObject->SetValue(SERVICE_INSTANCE_STOPPED, QDateTime::currentDateTime());
        pObject->Commit();
    }
}
