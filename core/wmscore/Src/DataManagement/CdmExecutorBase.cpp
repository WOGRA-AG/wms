
// System and QT Includes
#include <QScriptEngine>


// Own Includes
#include "CdmExecutorAddOnManager.h"
#include "CdmExecutor.h"
#include "CdmExecutorPreProcessor.h"
#include "CsaFactory.h"
#include "CdmLogging.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorRuntimeManager.h"
#include "CdmExecutorEngineJs.h"
#include "CdmExecutorEngineScript.h"
#include "CdmExecutorBase.h"


CdmExecutorBase::CdmExecutorBase()
:  m_pEngine(nullptr),
   m_pFactory(nullptr),
   m_pPreProcessor(nullptr)
{
   m_pPreProcessor = new CdmExecutorPreProcessor(this);
}

CdmExecutorBase::~CdmExecutorBase()
{
   DELPTR(m_pPreProcessor);
   DELPTR(m_pEngine);
   DELPTR(m_pFactory);
}

IdmExecutorEngine *CdmExecutorBase::GetEngine() const
{
    return m_pEngine;
}

CsaFactory *CdmExecutorBase::GetFactory() const
{
    return m_pFactory;
}

IdmExecutorEngine *CdmExecutorBase::GetOrCreateEngine()
{
    IdmExecutorEngine * pEngine = nullptr;
    pEngine = GetEngine();

    if (!pEngine)
    {
        CreateEngine();
        pEngine = GetEngine();
    }

    return pEngine;
}

void CdmExecutorBase::CreateEngine()
{
   if (m_pEngine)
   {
      CdmExecutor::GetExecutor()->GetRuntimeManager()->EndRuntime(m_pEngine);
      DELPTR(m_pEngine);
   }

   if (!m_pFactory)
   {
      m_pFactory = new CsaFactory(nullptr);
   }

   m_pEngine = new CdmExecutorEngineScript(m_pFactory);
   m_pEngine->InstallTranslatorFunctions();
   m_pFactory->setEngine(m_pEngine);
}

void CdmExecutorBase::ActivateDebugger()
{
    m_pEngine->StartDebugger();
}

void CdmExecutorBase::DetachDebugger()
{
    m_pEngine->EndDebugger();
}

void CdmExecutorBase::CollectGarbage()
{
   m_pFactory->collectGarbage();
}


CdmExecutorRuntime* CdmExecutorBase::CreateOrGetRuntime(IdmExecutorEngine* p_pEngine)
{
    CdmExecutorRuntime* pRuntime = nullptr;
    CdmExecutorRuntimeManager* pRuntimeManager = CdmExecutor::GetExecutor()->GetRuntimeManager();

    if (CHKPTR(pRuntimeManager))
    {
        pRuntime = pRuntimeManager->CreateOrGetRuntime(p_pEngine);
    }

    return pRuntime;
}

