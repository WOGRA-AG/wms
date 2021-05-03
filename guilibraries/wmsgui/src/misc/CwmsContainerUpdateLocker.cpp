
#include "CdmLogging.h"
#include <CdmDataProvider.h>
#include <CdmSessionManager.h>
#include "CdmContainerManager.h"


#include "CwmsContainerUpdateLocker.h"

CwmsContainerUpdateLocker::CwmsContainerUpdateLocker(QString p_qstrContainerKeyname, bool p_bForceUpdateOnDestruction)
: m_qstrContainerKeyname(p_qstrContainerKeyname),
  m_bForceUpdateOnDestruction(p_bForceUpdateOnDestruction)
{

}

CwmsContainerUpdateLocker::CwmsContainerUpdateLocker(bool p_bForceUpdateOnDestruction)
: m_qstrContainerKeyname(""),
  m_bForceUpdateOnDestruction(p_bForceUpdateOnDestruction)
{

}

void CwmsContainerUpdateLocker::SetContainer(QString p_qstrContainer)
{
    m_qstrContainerKeyname = p_qstrContainer;
}

CdmObjectContainer* CwmsContainerUpdateLocker::GetContainer()
{
    CdmObjectContainer* pContainer = nullptr;
    auto pManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pManager))
    {
        auto pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            pContainer = pContainerManager->FindContainerByKeyname(m_qstrContainerKeyname);
        }
    }


    return pContainer;
}

void CwmsContainerUpdateLocker::AddUpdateException(CdmContainerAdaptor* p_pAdaptor)
{
    if (!m_qllAdaptorExceptions.contains(p_pAdaptor))
    {
        m_qllAdaptorExceptions.append(p_pAdaptor);
    }
}

void CwmsContainerUpdateLocker::StopUpdates()
{
    auto pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        GetAdaptorsFromContainer(pContainer);
        RemoveAdaptorsFromContainer(pContainer);

    }
}

void CwmsContainerUpdateLocker::GetAdaptorsFromContainer(CdmObjectContainer* p_pContainer)
{
    if (CHKPTR(p_pContainer))
    {
        m_qllOriginalContainers = p_pContainer->GetObjectFactoryList();
    }
}

void CwmsContainerUpdateLocker::RemoveAdaptorsFromContainer(CdmObjectContainer* p_pContainer)
{

    QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qllOriginalContainers.begin();
    QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qllOriginalContainers.end();

    for(; qvlIt != qvlItEnd; ++qvlIt)
    {

        if (!m_qllAdaptorExceptions.contains(*qvlIt))
        {
            p_pContainer->RemoveObjectFactory(*qvlIt);
        }
    }
}

void CwmsContainerUpdateLocker::EnableUpdates()
{
    auto pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        QList<CdmContainerAdaptor*>::iterator qvlIt    = m_qllOriginalContainers.begin();
        QList<CdmContainerAdaptor*>::iterator qvlItEnd = m_qllOriginalContainers.end();

        for(; qvlIt != qvlItEnd; ++qvlIt)
        {

            if (!m_qllAdaptorExceptions.contains(*qvlIt))
            {
                pContainer->AddObjectFactory(*qvlIt);
            }
        }
    }
}

void CwmsContainerUpdateLocker::ForceUpdates()
{
    auto pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        pContainer->ObjectCommitedSlot(0);
    }
}

CwmsContainerUpdateLocker::~CwmsContainerUpdateLocker()
{
    EnableUpdates();

    if (m_bForceUpdateOnDestruction)
    {
        ForceUpdates();
    }
}
