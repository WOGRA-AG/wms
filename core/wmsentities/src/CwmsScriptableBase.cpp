
// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CsaFactory.h"

// Own Includes
#include "CwmsScriptableBase.h"

CwmsScriptableBase::CwmsScriptableBase()
{

}

CwmsScriptableBase::~CwmsScriptableBase()
{

}

CsaFactory *CwmsScriptableBase::getFactory()
{
    CsaFactory* pFactory = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmExecutor* pExecutor = pManager->GetExecutor();

        if (CHKPTR(pExecutor))
        {
            CdmExecutorFunction* pExecutorFunction = pExecutor->GetFunction();

            if (CHKPTR(pExecutorFunction))
            {
                pFactory = pExecutorFunction->GetFactory();
            }
        }
    }

    return pFactory;
}

void CwmsScriptableBase::addObjectForGarbageCollection(QObject* p_pObject)
{
    CsaFactory* pFactory = getFactory();

    if (CHKPTR(pFactory))
    {
        pFactory->addObjectForGarbageCollection(p_pObject);
    }
}
