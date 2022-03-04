#ifndef CDMEXECUTORFUNCTION_H
#define CDMEXECUTORFUNCTION_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QScriptEngine>
#include <QVariant>

// Own Includes
#include "datamanager.h"
#include "CdmExecutorBase.h"
#include "CdmExecutorFunction.h"

// Forwards
class QScriptEngineDebugger;
class CdmModelElement;
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CdmClassValidator;
class CdmClassMethod;
class CdmValue;
class CdmMember;
class QScriptProgram;
class QScriptContext;
class CdmExecutor;
class IwmsPluginInterface;
class CdmExecutorRuntime;
class CdmClassManager;

// TypeDefs

// DEFINES


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutorFunction : public CdmExecutorBase
{

private:
    bool m_bAllowAskForParameters;
    CdmExecutor* m_rpExecutor;
    bool m_bIsInitEvent;

public:
    CdmExecutorFunction(CdmExecutor* p_pExecutor);
    virtual ~CdmExecutorFunction( );
    QVariant ExecStaticMethod(QString qstrObjectRefMember,
                              QString qstrFunctionMemberName,
                              CdmClass* pCdmClass,
                              QScriptContext* p_pContext);
    QVariant ExecStaticMethod(QString qstrObjectRefMember,
                              QString qstrFunctionMemberName,
                              QScriptEngine* p_pEngine,
                              QScriptContext* p_pContext);
    QVariant Exec(QScriptContext* p_pContext, QScriptEngine* p_pEngine);
    QVariant ExecLocalObjectMethod(QString qstrFunctionMemberName,
                                   QScriptEngine* p_pEngine,
                                   QScriptContext* p_pContext,
                                   CdmExecutorRuntime* p_pRuntime);
    QVariant Delete(QScriptContext* p_pContext, QScriptEngine* p_pEngine);
    QVariant ExecObjectMethod(CdmObject* p_pCdmObject,
                              QString qstrFunctionMemberName,
                              QScriptEngine* p_pEngine,
                              QScriptContext* p_pContext);
    void CallConstructor(CdmObject *p_pObject);
    void CallDestructor(CdmObject *p_pObject);
    QVariant ExecuteFunction(QString p_qstrFunction, CdmObject* p_pCdmObject, QVariantList p_qlParameters);
    QVariant ExecuteFunctionStatic(CdmClassMethod* p_pMethod, QVariantList p_qlParameters);
    QVariant ExecStaticFunction(QString qstrMethodName, CdmClassManager* pClassManager, QScriptEngine* p_pEngine, QScriptContext* p_pContext, QString qstrRefName);
    void setAskForParametersAllowed(bool bAllowAskForParameters);
    bool IsAskForParametersAllowed() const;

public slots:
    QVariant ExecuteObject( QString p_qstrFunction,
                            CdmObject* p_pCdmObject,
                            QVariantList p_qlParameters);
    QVariant Execute( CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase, QVariantList p_qlParams);
    QVariant Execute(CdmClassMethod* p_pMethod, CdmModelElement* p_pCdmBase);
    QVariant ExecuteStatic( CdmClassMethod* p_pMethod, QVariantList p_qlParameters);

private:
    void AddMethodDataToEngine(QScriptEngine& p_rqEngine, CdmClassMethod* p_pMethod);
    void CallConstructor(CdmObject *p_pObject, CdmClass *p_pClass);
    void CallDestructor(CdmObject *p_pObject, CdmClass *p_pClass);
    void CallClassConstructor(CdmObject *p_pObject, CdmClass* p_pClass);
    void CallClassDestructor(CdmObject *p_pObject, CdmClass* p_pClass);
    QString GenerateArguments(QVariantList p_qlParams, CdmClassMethod* p_pMethod);
    QVariant ExecuteReferencedFunction(QString qstrMethodName, QScriptEngine* p_pEngine, QScriptContext* p_pContext, CdmValue* pValue, CdmObject* pCallingObject, QString qstrRefName);
    QVariant ExecRefOrStaticFunction(QScriptEngine* p_pEngine, QString qstrMethodName, QScriptContext* p_pContext, CdmObject* pCallingObject, QString qstrRefName);
    QVariant ExecFunction(QVariant qsPrototype, QScriptEngine* p_pEngine, CdmExecutorRuntime* pRuntime, QScriptContext* p_pContext);
    QVariant ConvertToResultVariant(const QVariant &p_rQVariant);
    QString ConvertToJsDateConstructor(int pYear, int pMonth, int pDay, int pHour, int pMinute, int pSecond);
};
#endif
