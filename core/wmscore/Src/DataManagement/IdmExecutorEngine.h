#ifndef IDMEXECUTORENGINE_H
#define IDMEXECUTORENGINE_H

// System and Qt Includes
#include <QVariant>

// own Includes
#include "CdmModelElement.h"
#include "datamanager.h"

// Forwards
class CdmValue;
class CsaObject;
class CdmClassMethod;
class CdmObject;
class CsaResultObject;

class WMSMANAGER_API IdmExecutorEngine
{
public:
    IdmExecutorEngine();
    virtual ~IdmExecutorEngine();
    virtual QVariant Evaluate(QString p_qstrCode, QString qstrName) = 0;
    virtual QVariant Evaluate(QString p_qstrCode, QString qstrName, EdmValueType p_eReturnType) = 0;
    virtual QVariant Call(QString p_qstrName) = 0;
    virtual QVariant Call(QString p_qstrName, QVariantList p_qvlArguments) = 0;
    virtual void SetProperty(QString p_qstrName, QVariant p_qvProperty) = 0;
    virtual void SetProperty(QString p_qstrName,QObject* p_pObject) = 0;
    virtual void SetProperty(CdmValue* p_pValue) = 0;
    virtual void SetThis(CsaObject* p_pThis) = 0;
    virtual void SetThis(CdmObject* p_pThis) = 0;
    virtual QVariant GetProperty(QString p_qstrName) = 0;
    virtual void ThrowError(QString p_qstrError) = 0;
    virtual void PushContext() = 0;
    virtual void PopContext() = 0;
    virtual void SetValueToScript(CdmValue* p_pValue) = 0;
    virtual bool HasUncaughtExceptions() = 0;
    virtual void StartDebugger() = 0;
    virtual void EndDebugger() = 0;
    virtual bool SupportsDebugger() = 0;
    virtual bool SyntaxCheck(QString p_qstrCode) = 0;
    virtual void InstallTranslatorFunctions() = 0;
    virtual CsaResultObject* GetResultObject() = 0;
    virtual void AddMethodProxy(CdmClassMethod* p_pMethod) = 0;
    virtual void SetProperty(CdmValue *p_pValue, QString p_qstrVariableName) = 0;
    virtual void Reset() = 0;
};

#endif // IDMEXECUTORENGINE_H
