#ifndef CDMEXECUTORENGINEJS_H
#define CDMEXECUTORENGINEJS_H

// System and Qt Includes
#include <QJSValue>

// Own Includes
#include "IdmExecutorEngine.h"

// Forwards
class QJSEngine;
class CsaFactory;

class CdmExecutorEngineJs : public IdmExecutorEngine
{
private:
    QJSEngine* m_pEngine;
    CsaFactory* m_rpFactory;

    QJSValue GenerateScriptValue(CdmValue *p_pValue);
    void SetupEngine();
public:
    CdmExecutorEngineJs(CsaFactory* p_pFactory);
    virtual ~CdmExecutorEngineJs();
    virtual QVariant Evaluate(QString p_qstrCode, QString qstrName);
    virtual QVariant Call(QString p_qstrName);
    virtual QVariant Call(QString p_qstrName, QVariantList p_qvlArguments);
    virtual void SetProperty(QString p_qstrName, QVariant p_qvProperty);
    virtual void SetProperty(CdmValue* p_pValue);
    virtual void SetProperty(QString p_qstrName,QObject* p_pObject);
    virtual QVariant GetProperty(QString p_qstrName);
    virtual void SetThis(CsaObject* p_pThis);
    virtual void ThrowError(QString p_qstrError);
    virtual void PushContext();
    virtual void PopContext();
    virtual void SetValueToScript(CdmValue* p_pValue);
    virtual bool HasUncaughtExceptions();
    virtual void StartDebugger();
    virtual void EndDebugger();
    virtual bool SupportsDebugger();
    virtual bool SyntaxCheck(QString p_qstrCode);
    virtual void InstallTranslatorFunctions();
    virtual CsaResultObject* GetResultObject();
    virtual void AddMethodProxy(CdmClassMethod* p_pMethod);
    void SetThis(CdmObject *p_pThis);
    void Reset();
};

#endif // CDMEXECUTORENGINEJS_H
