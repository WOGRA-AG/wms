#ifndef CDMEXECUTORREMOTE_H
#define CDMEXECUTORREMOTE_H

// own Includes
#include "CdmExecutor.h"
#include "datamanager.h"

// forwards
class IdmDataAccess;
class CdmObject;
class CdmClassMethod;

class WMSMANAGER_API CdmExecutorRemote : public CdmExecutor
{
public:
    CdmExecutorRemote();
    ~CdmExecutorRemote(){}


    virtual QVariant EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula);
    virtual QVariant ExecuteFunction(CdmClassMethod* p_pMethod, CdmObject* pObject, QVariantList& p_qlParams);

private:
    IdmDataAccess *GetDataAccess();
};

#endif // CDMEXECUTORREMOTE_H
