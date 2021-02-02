
// System and QT Includes
#include <QScriptEngine>

// Own Includes
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmLogging.h"
#include "CdmClassMethod.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmExecutorPreProcessor.h"
#include "CsaFactory.h"
#include "CsaResultObject.h"
#include "CdmExecutorRuntime.h"

CdmExecutorRuntime::CdmExecutorRuntime(IdmExecutorEngine* p_pEngine)
    : QObject(),
      m_rpEngine(p_pEngine),
      m_pStartMethod(nullptr),
      m_pCurrentMethod(nullptr),
      m_pCurrentThisObject(nullptr),
      m_StartThisObject(nullptr)
{
    INFO("Runtime created");
}

CdmExecutorRuntime::~CdmExecutorRuntime()
{
    INFO("Runtime destroyed");
}

IdmExecutorEngine *CdmExecutorRuntime::GetEngine() const
{
    return m_rpEngine;
}

void CdmExecutorRuntime::SetMethod(CdmClassMethod* p_pMethod)
{
    m_pCurrentMethod = p_pMethod;

    if (!m_pStartMethod)
    {
        m_pStartMethod = p_pMethod;
    }

    m_CallStack.push(p_pMethod);
    INFO("Added Method " + p_pMethod->GetMethodName() + " to Runtime");
}

void CdmExecutorRuntime::SetThisObject(CdmObject* p_pObject)
{
    m_pCurrentThisObject = p_pObject;

    if (!m_StartThisObject)
    {
        m_StartThisObject = p_pObject;
    }

    m_ThisStack.push(p_pObject);
}

CdmObject *CdmExecutorRuntime::GetStartThisObject() const
{
    return m_StartThisObject;
}


CdmObject *CdmExecutorRuntime::GetCurrentThisObject() const
{
    return m_pCurrentThisObject;
}


CdmClassMethod *CdmExecutorRuntime::GetCurrentMethod() const
{
    return m_pCurrentMethod;
}

CdmClassMethod *CdmExecutorRuntime::GetStartMethod() const
{
    return m_pStartMethod;
}

void CdmExecutorRuntime::MethodCallStart(CdmClassMethod* p_pMethod, CdmObject* p_pObject)
{
    SetMethod(p_pMethod);
    SetThisObject(p_pObject);
}

void CdmExecutorRuntime::UpdateThisAndCallStackAfterFinishingMethodCall()
{
    m_CallStack.pop();
    m_ThisStack.pop();

    if (m_CallStack.count() == 0)
    {
        m_pStartMethod = nullptr;
        m_pCurrentMethod = nullptr;
        m_pCurrentThisObject = nullptr;
        m_StartThisObject = nullptr;
        CsaResultObject* pObject = m_rpEngine->GetResultObject();

        if (pObject)
        {
            m_qvResultObject = pObject->getVariantMap();
        }

        m_rpEngine->Reset();
    }
    else
    {
        m_pCurrentMethod = m_CallStack.last();
        m_pCurrentThisObject = m_ThisStack.last();
    }

    if (m_pCurrentThisObject)
    {
        m_rpEngine->SetThis(m_pCurrentThisObject);
    }
}

void CdmExecutorRuntime::CommitingObjectsAfterFinishMethodCall()
{
    QVector<CdmObject*>::iterator qIt = m_ObjectsToCommit.begin();
    QVector<CdmObject*>::iterator qItEnd = m_ObjectsToCommit.end();

    for (; qIt != qItEnd; ++qIt)
    {
        CdmObject* pObject = *qIt;

        if (CHKPTR(pObject))
        {
            pObject->Commit();
        }
    }

    m_ObjectsToCommit.clear();
}

void CdmExecutorRuntime::MethodCallFinished()
{
    UpdateThisAndCallStackAfterFinishingMethodCall();
    CommitingObjectsAfterFinishMethodCall();
}

QString CdmExecutorRuntime::GetCallStack()
{
    QString qstrCallStack;

    QStack<CdmClassMethod*>::iterator qIt = m_CallStack.begin();
    QStack<CdmClassMethod*>::iterator qItEnd = m_CallStack.end();

    for (; qIt != qItEnd; ++qIt)
    {
        CdmClassMethod* pMethod = *qIt;
        qstrCallStack += pMethod->GetMethodName() + "\n";
    }

    return qstrCallStack;
}

bool CdmExecutorRuntime::IsScriptRunning()
{
    return (m_CallStack.count() > 0);
}

int CdmExecutorRuntime::GetCallStackDepth()
{
    return m_CallStack.count();
}

bool CdmExecutorRuntime::NeedsCurrentThisObjectUpdate(CdmObject* p_pObject)
{
    bool ret = false;

    if (IsScriptRunning())
    {
        ret = (p_pObject != m_pCurrentThisObject);
    }
    else
    {
        ret = true;
    }

    return ret;
}

void CdmExecutorRuntime::AddCurrentObjectToCommit()
{
    if (m_pCurrentThisObject != m_StartThisObject && m_pCurrentThisObject)
    {
        if (!m_ObjectsToCommit.contains(m_pCurrentThisObject))
        {
            m_ObjectsToCommit.append(m_pCurrentThisObject);
        }
    }
}

bool CdmExecutorRuntime::IsMethodCallAllowed(CdmClassMethod* p_pMethod)
{
    bool ret = false;
    CdmClassMethod* pCurrentMethod = GetCurrentMethod();

    if (pCurrentMethod)
    {
        // the methods are in the same class a call is allowed
        if (pCurrentMethod->GetClass() == p_pMethod->GetClass())
        {
            INFO("Both methods are in the same class. Method call allowed");
            ret = true;
        }
        else
        {
            INFO("Methods are not in the same class Further checks needed");
            if (p_pMethod->GetAccess() == eDmMemberAccessPublic)
            {
                INFO("Methodcall is allowed, because the Method is public");
                ret = true;
            }
            else if (p_pMethod->GetAccess() == eDmMemberAccessProtected)
            {
                INFO("The method is protected, we check now if there is an existing inheritance");
                CdmClass* pClassCurrent =  pCurrentMethod->GetClass();
                CdmClass* pClassNew = p_pMethod->GetClass();

                if (pClassCurrent->IsInherited(pClassNew))
                {
                    INFO("Called protected inherited class.");
                    ret = true;
                }
                else
                {
                    ERR("Tried to call a protected method of a different class without inheritance.");
                }
            }
            else
            {
                ERR("Method call forbidden. call of a private method of a different class");
            }
        }
    }
    else
    {
        if (p_pMethod->GetAccess() == eDmMemberAccessPublic)
        {
            INFO("First Methodcall is allowed, because the Method is public");
            ret = true;
        }
        else
        {
            ERR("Method is not a public method, so a methodcall is forbidden");
        }
    }

    return ret;
}

bool CdmExecutorRuntime::ExceptionOccured()
{
    return (m_qstrlExceptions.count() > 0);
}

void CdmExecutorRuntime::AddException(QString p_qstrException)
{
    m_qstrlExceptions.append(p_qstrException);
}

QStringList CdmExecutorRuntime::GetExceptions()
{
    return m_qstrlExceptions;
}

QVariant CdmExecutorRuntime::GetResultObject()
{
    return m_qvResultObject;
}


