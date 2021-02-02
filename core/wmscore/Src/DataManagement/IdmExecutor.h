#ifndef IDMEXECUTOR_H
#define IDMEXECUTOR_H

// System and QT Includes
#include <QVariant>
#include <QString>

// forwards
class CdmObject;
class CdmClassMethod;


class IdmExecutor
{
    virtual QVariant EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula) = 0;
    virtual QVariant ExecuteFunction(CdmClassMethod* p_pMethod, CdmObject* pObject, QVariantList& p_qlParams) = 0;

};



#endif // IDMEXECUTOR_H
