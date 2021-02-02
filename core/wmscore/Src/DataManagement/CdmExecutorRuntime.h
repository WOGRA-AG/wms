#ifndef CDMEXECUTORRUNTIME_H
#define CDMEXECUTORRUNTIME_H

// System and QT Includes
#include <QStack>
#include <QVariant>
#include <QObject>
#include <QStringList>

// own Includes
#include "datamanager.h"

// forwards
class IdmExecutorEngine;
class CdmClassMethod;
class CdmObject;


class WMSMANAGER_API CdmExecutorRuntime : public QObject
{
    Q_OBJECT

private:
    IdmExecutorEngine* m_rpEngine;
    CdmClassMethod* m_pStartMethod;
    CdmClassMethod* m_pCurrentMethod;
    CdmObject* m_pCurrentThisObject;
    CdmObject* m_StartThisObject;
    QVariant m_qvResultObject;
    QStack<CdmClassMethod*> m_CallStack;
    QStack<CdmObject*> m_ThisStack;
    QVector<CdmObject*> m_ObjectsToCommit;
    QList<QString> m_qstrlExceptions;

public:
    CdmExecutorRuntime(IdmExecutorEngine* p_pEngine);
    virtual ~CdmExecutorRuntime();
    IdmExecutorEngine *GetEngine() const;
    void MethodCallFinished();
    void MethodCallStart(CdmClassMethod *p_pMethod, CdmObject *p_pObject);
    bool NeedsCurrentThisObjectUpdate(CdmObject *p_pObject);
    bool IsScriptRunning();
    void SetMethod(CdmClassMethod *p_pMethod);
    void SetThisObject(CdmObject *p_pObject);
    CdmObject *GetStartThisObject() const;
    CdmObject *GetCurrentThisObject() const;
    CdmClassMethod *GetCurrentMethod() const;
    CdmClassMethod *GetStartMethod() const;
    void AddCurrentObjectToCommit();
    bool IsMethodCallAllowed(CdmClassMethod *p_pMethod);
    void AddException(QString p_qstrException);

    void UpdateThisAndCallStackAfterFinishingMethodCall();
    void CommitingObjectsAfterFinishMethodCall();

public slots:
    QString GetCallStack();
    int GetCallStackDepth();
    bool ExceptionOccured();
    QVariant GetResultObject();
    QStringList GetExceptions();
};

#endif // CDMEXECUTORRUNTIME_H

