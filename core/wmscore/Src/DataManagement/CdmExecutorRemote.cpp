
// System and QT Includes


// own Includes
#include "CdmClassMethod.h"
#include "IdmDataAccess.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmExecutorRemote.h"

CdmExecutorRemote::CdmExecutorRemote()
    : CdmExecutor()
{
}

QVariant CdmExecutorRemote::EvaluateFormula(const CdmObject *p_pCdmObject, QString p_qstrFormula)
{
    QVariant qResult;
    IdmDataAccess* pDataAccess = GetDataAccess();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataAccess) && CHKPTR(pManager))
    {
        qResult = pDataAccess->EvaluateFormula(p_pCdmObject, p_qstrFormula);
    }

    return qResult;
}

QVariant CdmExecutorRemote::ExecuteFunction(CdmClassMethod *p_pMethod, CdmObject *pObject, QVariantList &p_qlParams)
{
    QVariant qResult;
    IdmDataAccess* pDataAccess = GetDataAccess();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pDataAccess) && CHKPTR(pManager))
    {
        qResult = pDataAccess->ExecuteFunction(pObject, p_pMethod->GetMethodName(), p_qlParams);

    }

    return qResult;
}

IdmDataAccess* CdmExecutorRemote::GetDataAccess()
{
    IdmDataAccess* pDataAccess = nullptr;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        pDataAccess = pManager->GetDataAccess();
    }

    return pDataAccess;
}
