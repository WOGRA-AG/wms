
// System and Qt Includes
#include <QTimer>

// WMS Manager Includes
#include "CsaObject.h"
#include "CdmSessionManager.h"
#include "CdmExecutor.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmObject.h"
#include "CdmExecutorFunction.h"

// own Includes
#include "CwmsScriptableTimer.h"



CwmsScriptableTimer::CwmsScriptableTimer()
{

}

CwmsScriptableTimer::~CwmsScriptableTimer()
{
    stopAllTimers();
}

QString CwmsScriptableTimer::startTimer(QString p_qstrName, CsaObject *p_pObject, QString p_qstrFunction, int intervall)
{
    QString qstrRealName = getRealName(p_qstrName);

    if (p_pObject)
    {
        QTimer* pTimer = new QTimer();
        m_qmTimerNameMapping.insert(qstrRealName, pTimer);
        QPair<QString, QString> pair;
        pair.first = p_pObject->getUri();
        pair.second = p_qstrFunction;
        m_qmTimerData.insert(pTimer, pair);
        connect(pTimer, SIGNAL(timeout()), this, SLOT(timeout()));
        pTimer->start(intervall);
    }
    else
    {
        ERR("WmsObject Pointer is nullptr. Call instead timer function for static functions!");
    }


    return qstrRealName;
}

QString CwmsScriptableTimer::getRealName(QString p_qstrName)
{
    QString qstrRealName = p_qstrName;

    while (m_qmTimerNameMapping.contains(qstrRealName))
    {
        qstrRealName += "0";
    }

    return qstrRealName;
}

QString CwmsScriptableTimer::startSingleShotTimer(QString p_qstrName, CsaObject *p_pObject, QString p_qstrFunction, int intervall)
{
    QString qstrRealName = getRealName(p_qstrName);

    if (p_pObject)
    {
        QTimer* pTimer = new QTimer();
        m_qmTimerNameMapping.insert(qstrRealName, pTimer);
        QPair<QString, QString> pair;
        pair.first = p_pObject->getUri();
        pair.second = p_qstrFunction;
        m_qmTimerData.insert(pTimer, pair);
        connect(pTimer, SIGNAL(timeout()), this, SLOT(timeout()));
        pTimer->setSingleShot(true);
        pTimer->start(intervall);
    }
    else
    {
        ERR("WmsObject Pointer is nullptr. Call instead timer function for static functions!");
    }


    return qstrRealName;
}

QString CwmsScriptableTimer::startTimer(QString p_qstrName, QString p_qstrFunction, int intervall)
{
    QString qstrRealName = getRealName(p_qstrName);

    QTimer* pTimer = new QTimer();
    m_qmTimerNameMapping.insert(qstrRealName, pTimer);
    QPair<QString, QString> pair;
    pair.first = p_qstrFunction;
    pair.second = "static";
    m_qmTimerData.insert(pTimer, pair);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    pTimer->start(intervall);

    return qstrRealName;
}

QString CwmsScriptableTimer::startSingleShotTimer(QString p_qstrName, QString p_qstrFunction, int intervall)
{
    QString qstrRealName = getRealName(p_qstrName);

    QTimer* pTimer = new QTimer();
    m_qmTimerNameMapping.insert(qstrRealName, pTimer);
    QPair<QString, QString> pair;
    pair.first = "static";
    pair.second = p_qstrFunction;
    m_qmTimerData.insert(pTimer, pair);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    pTimer->setSingleShot(true);
    pTimer->start(intervall);

    return qstrRealName;
}

bool CwmsScriptableTimer::stopTimer(QString p_qstrName)
{
    bool bSuccess = false;

    QTimer* pTimer = m_qmTimerNameMapping[p_qstrName];

    if (pTimer)
    {
        m_qmTimerData.remove(pTimer);
        m_qmTimerNameMapping.remove(p_qstrName);
        bSuccess = true;
    }
    else
    {
        ERR("Timer with name " + p_qstrName + " not found!");
    }

    return bSuccess;
}

bool CwmsScriptableTimer::stopAllTimers()
{
    m_qmTimerNameMapping.clear();
    m_qmTimerData.clear();
    return true;
}

void CwmsScriptableTimer::timeout()
{
    QTimer* pTimer = dynamic_cast<QTimer*> (sender());

    if (CHKPTR(pTimer))
    {
        QPair<QString, QString> pair = m_qmTimerData[pTimer];

        if (pair.first == "static")
        {
            executeStaticFunction(pair.second);
        }
        else
        {
            executeFunction(pair.first, pair.second);
        }
    }
    else
    {
        ERR("Somebody called the timeoutslot and sender is not a timer.");
    }
}

CdmClassMethod * CwmsScriptableTimer::getMethodObject(QString p_qstrFunction)
{
    CdmClassMethod* pMethod = nullptr;
    CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        int iPos = p_qstrFunction.lastIndexOf(".");

        if (iPos > 0)
        {
            QString qstrClass = p_qstrFunction.left(iPos);
            QString qstrFunction = p_qstrFunction.mid(iPos + 1, p_qstrFunction.length() - iPos - 1);
            CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

            if (pClass)
            {
                pMethod = pClass->FindMethod(qstrFunction);
            }
            else
            {
                ERR("Class " + qstrClass + " not found for calling static function " + qstrFunction + ".");
            }
        }
        else
        {
            ERR("Invalid Functionname Name must consist of <full qualified class name> + \".\" + <functionname> sample: com.Address.delete.\n Importent no arguments are allowed")
        }
    }

    return pMethod;
}

void CwmsScriptableTimer::executeStaticFunction(QString p_qstrFunction)
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        CdmClassMethod* pMethod = getMethodObject(p_qstrFunction);

        if (pMethod && pMethod->IsStatic() && pMethod->GetParameterCount() == 0)
        {
            QVariantList qlArguments;
            pExecutor->GetFunction()->ExecuteFunctionStatic(pMethod, qlArguments);
        }
        else if (pMethod)
        {
            if (!pMethod->IsStatic())
            {
                ERR("Method " + p_qstrFunction + " is not static.");
            }
            else
            {
                ERR("Timer are only able to call methods without arguments Function " + p_qstrFunction + " needs arguments!");
            }
        }
        else
        {
            ERR("Method " + p_qstrFunction + " not found.");
        }
    }
}

void CwmsScriptableTimer::executeFunction(QString p_qstrObjectUri, QString p_qstrFunction)
{
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        CdmObject* pObject = dynamic_cast<CdmObject*> (CdmSessionManager::GetDataProvider()->GetUriObject(p_qstrObjectUri));

        if (pObject)
        {
            QVariantList qlArguments;
            pExecutor->GetFunction()->ExecuteFunction(p_qstrFunction, pObject, qlArguments);
        }
        else
        {
            ERR("Function object for timer method call not found!");
        }
    }

}
