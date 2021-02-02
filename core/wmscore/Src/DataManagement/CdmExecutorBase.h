#ifndef CDMEXECUTORBASE_H
#define CDMEXECUTORBASE_H

// System and QT Includes

//WMS Commons Includes
#include "CwmsSynchronizable.h"

// Own Includes
#include "datamanager.h"

// Forwards
class IdmExecutorEngine;
class CdmExecutorPreProcessor;
class CdmExecutorRuntime;
class CdmExecutorRuntimeManager;
class CsaFactory;

class WMSMANAGER_API CdmExecutorBase : public CwmsSynchronizable
{
private:
    IdmExecutorEngine* m_pEngine;
    CsaFactory* m_pFactory;
    CdmExecutorPreProcessor* m_pPreProcessor;

public:
    CdmExecutorBase();
    virtual ~CdmExecutorBase();
    void CreateEngine();
    IdmExecutorEngine *GetEngine() const;
    CsaFactory *GetFactory() const;
    void DetachDebugger();
    void ActivateDebugger();
    void CollectGarbage();
    CdmExecutorPreProcessor* GetPreProcessor() { return m_pPreProcessor; }
    IdmExecutorEngine *GetOrCreateEngine();
protected:
    CdmExecutorRuntime *CreateOrGetRuntime(IdmExecutorEngine *p_pEngine);
};

#endif // CDMEXECUTORBASE_H
