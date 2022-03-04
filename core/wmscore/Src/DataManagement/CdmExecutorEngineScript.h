#ifndef CDMEXECUTORENGINESCRIPT_H
#define CDMEXECUTORENGINESCRIPT_H

// System and Qt Includes

// Own Includes
#include "IdmExecutorEngine.h"
#include <QScriptValue>

// Forwards
class QScriptEngine;
class QScriptEngineDebugger;
class CsaFactory;

class CdmExecutorEngineScript : public IdmExecutorEngine
{
private:
    QScriptEngine* m_pEngine;
    QScriptEngineDebugger* m_pDebugger;
    CsaFactory* m_rpFactory;
    void SetupEngine();
    QScriptValue GenerateScriptValue(CdmValue *p_pValue);

public:
    CdmExecutorEngineScript(CsaFactory* p_pFactory);
    virtual ~CdmExecutorEngineScript();
    virtual QVariant Evaluate(QString p_qstrCode, QString qstrName);
    virtual QVariant Evaluate(QString p_qstrCode, QString qstrName, EdmValueType p_eReturnType);
    virtual void SetProperty(QString p_qstrName, QVariant p_qvProperty);
    virtual void SetProperty(CdmValue* p_pValue);
    virtual void SetProperty(QString p_qstrName,QObject* p_pObject);
    virtual QVariant GetProperty(QString p_qstrName);
    virtual void SetThis(CsaObject* p_pThis);
    virtual void SetThis(CdmObject* p_pThis);
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
    QVariant Call(QString p_qstrName, QVariantList p_qvlArguments);
    QVariant Call(QString p_qstrName);
    virtual CsaResultObject* GetResultObject();
    virtual void AddMethodProxy(CdmClassMethod* p_pMethod);
    void SetProperty(CdmValue *p_pValue, QString p_qstrVariableName);
    void Reset();
};

#endif // CDMEXECUTORENGINESCRIPT_H
