

// own Includes
#include "IdmExecutorEngine.h"
#include "CdmLogging.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorRuntimeManager.h"

CdmExecutorRuntimeManager::CdmExecutorRuntimeManager()
{
}

CdmExecutorRuntimeManager::~CdmExecutorRuntimeManager()
{
    SYNCHRONIZED;
    if (m_qmRuntimes.count() > 0)
    {
        INFO("Runtimes not cleaned up! There are " + QString::number(m_qmRuntimes.count()) + " still in memory.");

        QMap<IdmExecutorEngine*, CdmExecutorRuntime*>::iterator qmIt = m_qmRuntimes.begin();
        QMap<IdmExecutorEngine*, CdmExecutorRuntime*>::iterator qmItEnd = m_qmRuntimes.end();

        for (; qmIt != qmItEnd; ++ qmIt)
        {
            CdmExecutorRuntime* pRuntime = qmIt.value();
            DELPTR(pRuntime);
            // don't delete scriptengines they will deleted by itselves and are probably already invalid.
        }

        m_qmRuntimes.clear();
    }
}

CdmExecutorRuntime* CdmExecutorRuntimeManager::CreateOrGetRuntime(IdmExecutorEngine* p_pEngine)
{
    CdmExecutorRuntime* pRuntime = nullptr;

    if (CHKPTR(p_pEngine))
    {
        SYNCHRONIZED

        if (m_qmRuntimes.contains(p_pEngine))
        {
            INFO("Engine found returning runtime");
            pRuntime = m_qmRuntimes[p_pEngine];
        }
        else
        {
            INFO("Engine not found creating new runtime");
            pRuntime = new CdmExecutorRuntime(p_pEngine);
            m_qmRuntimes.insert(p_pEngine, pRuntime);
        }
    }

    return pRuntime;
}

CdmExecutorRuntime* CdmExecutorRuntimeManager::GetRuntime(IdmExecutorEngine* p_pEngine)
{
    CdmExecutorRuntime* pRuntime = nullptr;

    if (CHKPTR(p_pEngine))
    {
        SYNCHRONIZED

        if (m_qmRuntimes.contains(p_pEngine))
        {
            INFO("Engine found returning runtime");
            pRuntime = m_qmRuntimes[p_pEngine];
        }
    }

    return pRuntime;
}

void CdmExecutorRuntimeManager::EndRuntime(IdmExecutorEngine* p_pEngine)
{
    if (CHKPTR(p_pEngine))
    {
        SYNCHRONIZED

        if (m_qmRuntimes.contains(p_pEngine))
        {
            INFO("Engine found returning runtime");
            CdmExecutorRuntime* pRuntime = m_qmRuntimes[p_pEngine];
            DELPTR(pRuntime);
            m_qmRuntimes.remove(p_pEngine);
        }
    }
}

int CdmExecutorRuntimeManager::GetActiveRuntimesCount()
{
    SYNCHRONIZED;
    return m_qmRuntimes.count();
}

