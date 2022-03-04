#ifndef CDMEXECUTOR_H
#define CDMEXECUTOR_H

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

// MACROS
#define SCRIPT_CONSTRUCTOR "onCreate"
#define SCRIPT_DESTRUCTOR "onDelete"
#define SCRIPT_COMMIT "onCommit"

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
class IwmsPluginInterface;
class CdmExecutorPreProcessor;
class CdmExecutorAddOnManager;
class CdmExecutorFormula;
class CdmExecutorFunction;
class CdmExecutorValidator;
class CdmExecutorRuntimeManager;
class CdmObjectContainer;
class CsaFactory;

// TypeDefs


/* 
 * This class implements the executor for functions and validations in Objects
 */
class WMSMANAGER_API CdmExecutor : public QObject
{
   Q_OBJECT

    friend class CdmDataProvider;

   private:
      CdmExecutorAddOnManager* m_rpAddOnManager; // Manged by Session Manager
      CdmExecutorFormula* m_pFormula;
      CdmExecutorFunction* m_pFunction;
      CdmExecutorValidator* m_pValidator;
      CdmExecutorRuntimeManager* m_pRuntimeManager;
      QList<qint64> m_qlCommitRunningContainers;
      
   public:
      CdmExecutorAddOnManager* GetAddOnManager() const { return m_rpAddOnManager; }
      CdmExecutorValidator* GetValidator() const { return m_pValidator; }
      CdmExecutorFunction* GetFunction() const { return m_pFunction; }
      CdmExecutorFormula* GetFormula() const { return m_pFormula; }
      bool GetCommitRunning(CdmObjectContainer* p_pContainer) const;
      void SetCommitRunning(CdmObjectContainer* p_pContainer, bool p_bRunning);


   protected:
    CdmExecutor( );

   public:
    virtual ~CdmExecutor( );
    virtual QVariant EvaluateFormula(const CdmObject* p_pCdmObject, QString p_qstrFormula);
    virtual QVariant ExecuteFunction(CdmClassMethod* p_pMethod, CdmObject* pObject, QVariantList& p_qlParams);
    void CreateEngines();
    CdmExecutorRuntimeManager* GetRuntimeManager() const;
    void InstallAddOnManager(CdmExecutorAddOnManager* p_pAddOnManager);

    static bool ExecuteValidation(CdmObject* p_pCdmObject);
    static bool ExecuteValidation(CdmObjectContainer* p_pContainer);
    static CdmExecutor* GetExecutor();
    static void DetachDebugger();
    static void ActivateDebugger();
    static QVariant ExecuteFunction(CdmClassMethod* p_pMethod, CdmObject* pObject, QVariantList p_qlParams, bool p_bDevelopment, bool p_bAskForParams, bool p_bDebug, bool p_bEngineCreated);
    static QVariant DebugFunction(CdmClassMethod* p_pMethod, CdmObject* pObject, QVariantList p_qlParams, bool p_bDevelopment = false, bool p_bAskForParams = false);
    static QVariant ExecStatic(QScriptContext* p_pContext, QScriptEngine* p_pEngine);
};

#endif //
