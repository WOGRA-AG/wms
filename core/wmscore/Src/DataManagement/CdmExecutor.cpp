// System and QT Includes
#include <QScriptSyntaxCheckResult>
#include <QScriptProgram>
#include <QScriptEngineDebugger>

// own Includes
#include "CsaFactory.h"
#include "IdmExecutorEngine.h"
#include "IwmsPluginInterface.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"
#include "CdmValue.h"
#include "CdmObjectContainer.h"
#include "CdmMember.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmValueObjectRef.h"
#include "CdmClassValidator.h"
#include "CdmValue.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmExecutorRuntimeManager.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmExecutorFunction.h"
#include "CdmExecutorFormula.h"
#include "CdmExecutorValidator.h"
#include "CdmExecutor.h"

/** +-=---------------------------------------------------------Mi 19. Sep 14:17:10 2012----------*
 * @method  CdmExecutor::CdmExecutor                         // private                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Sep 14:17:10 2012----------*/
CdmExecutor::CdmExecutor()

    : m_rpAddOnManager(nullptr),
      m_pFormula(nullptr),
      m_pFunction(nullptr),
      m_pValidator(nullptr),
      m_pRuntimeManager(nullptr)
{
    m_pRuntimeManager = new CdmExecutorRuntimeManager();
}

/** +-=---------------------------------------------------------Mi 19. Sep 14:18:59 2012----------*
 * @method  CdmExecutor::~CdmExecutor                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmExecutor                                                   *
 *----------------last changed: --------------------------------Mi 19. Sep 14:18:59 2012----------*/
CdmExecutor::~CdmExecutor()
{
    DELPTR(m_pRuntimeManager);
    DELPTR(m_pFormula);
    DELPTR(m_pFunction);
    DELPTR(m_pValidator);
}

void CdmExecutor::CreateEngines()
{
   m_pFormula = new CdmExecutorFormula(this);
   m_pFunction = new CdmExecutorFunction(this);
   m_pValidator = new CdmExecutorValidator(this);
}


CdmExecutor* CdmExecutor::GetExecutor()
{
   CdmExecutor* pExecutor = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (pManager)
   {
      pExecutor = pManager->GetExecutor();
   }

   return pExecutor;
}

QVariant CdmExecutor::EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula)
{
   return GetExecutor()->GetFormula()->EvaluateFormula(p_pCdmObject, p_qstrFormula);
}

bool CdmExecutor::ExecuteValidation(CdmObject* p_pCdmObject)
{
   return GetExecutor()->GetValidator()->Validate(p_pCdmObject);
}

bool CdmExecutor::ExecuteValidation(CdmObjectContainer* p_pContainer)
{
   return GetExecutor()->GetValidator()->Validate(p_pContainer);
}

QVariant CdmExecutor::ExecuteFunction(CdmClassMethod* p_pMethod,
                                      CdmObject* pObject,
                                      QVariantList p_qlParams,
                                      bool p_bDevelopment,
                                      bool p_bAskForParams,
                                      bool p_bDebug,
                                      bool p_bEngineCreated)
{
    QVariant qvResult;
	Q_UNUSED(p_bDevelopment);

    CdmExecutorFunction* pFunction = GetExecutor()->GetFunction();

    if (CHKPTR(pFunction))
    {
      if (!p_bEngineCreated)
       {
         pFunction->CreateEngine();
       }
    
       if (p_bDebug)
       {
           pFunction->ActivateDebugger();
       }
       else
       {
           CdmMessageManager::StartAsyncMessageCollection();
       }

       pFunction->setAskForParametersAllowed(p_bAskForParams);

       // call function
       if (pObject)
       {
           qvResult = pFunction->ExecuteFunction(p_pMethod->GetMethodName(), pObject, p_qlParams);
       }
       else
       {
           qvResult = pFunction->ExecuteFunctionStatic(p_pMethod, p_qlParams);
       }

       pFunction->setAskForParametersAllowed(false);

       if (p_bDebug)
       {
           pFunction->DetachDebugger();
       }
       else
       {
           CdmMessageManager::EndAndShowAsyncMessageCollection();
       }
    }

    return qvResult;
}

QVariant CdmExecutor::ExecuteFunction(CdmClassMethod* p_pMethod,
                                      CdmObject* pObject,
                                      QVariantList& p_qlParams)
{
   CdmExecutorFunction* pFunction = GetExecutor()->GetFunction();

   if (CHKPTR(pFunction))
   {
      pFunction->CreateEngine();
   }

   return ExecuteFunction(p_pMethod, pObject, p_qlParams, false, true, false, true);
}


QVariant CdmExecutor::DebugFunction(CdmClassMethod* p_pMethod,
                                        CdmObject *pObject,
                                        QVariantList p_qlParams,
                                        bool p_bDevelopment,
                                        bool p_bAskForParams)
{
    return ExecuteFunction(p_pMethod, pObject, p_qlParams, p_bDevelopment, p_bAskForParams, true, false);
}

CdmExecutorRuntimeManager *CdmExecutor::GetRuntimeManager() const
{
    return m_pRuntimeManager;
}

void CdmExecutor::InstallAddOnManager(CdmExecutorAddOnManager* p_pAddOnManager)
{
    if (p_pAddOnManager)
    {
        if (m_rpAddOnManager && p_pAddOnManager != m_rpAddOnManager) // it must be another addon manager
        {
            DELPTR(m_rpAddOnManager);
        }

        m_rpAddOnManager = p_pAddOnManager;
    }
}

bool CdmExecutor::GetCommitRunning(CdmObjectContainer *p_pContainer) const
{
    return m_qlCommitRunningContainers.contains(p_pContainer->GetId());
}

void CdmExecutor::SetCommitRunning(CdmObjectContainer *p_pContainer, bool p_bRunning)
{
    if (CHKPTR(p_pContainer))
    {
        if (p_bRunning)
        {
            if (!m_qlCommitRunningContainers.contains(p_pContainer->GetId()))
            {
                m_qlCommitRunningContainers.append(p_pContainer->GetId());
            }
        }
        else
        {
            m_qlCommitRunningContainers.removeAll(p_pContainer->GetId());
        }

    }
}
