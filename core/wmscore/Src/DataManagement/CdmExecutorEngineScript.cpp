
// System and Qt Includes
#include <QCoreApplication>
#include <QAction>
#include <QScriptEngine>
#include <QScriptContextInfo>
#include <QScriptEngineDebugger>
#include <QScriptValue>
#include <QDebug>

// Own Includes
#include "CsaFactory.h"
#include "CsaModelElement.h"
#include "CsaResultObject.h"
#include "CdmObject.h"
#include "CsaObject.h"
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorRuntimeManager.h"
#include "CdmExecutorRuntime.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmValue.h"
#include "CdmExecutorEngineScript.h"

CdmExecutorEngineScript::CdmExecutorEngineScript(CsaFactory* p_pFactory)
    : m_pEngine(nullptr),
      m_pDebugger(nullptr),
      m_rpFactory(p_pFactory)

{
    SetupEngine();
}

CdmExecutorEngineScript::~CdmExecutorEngineScript()
{
    DELPTR(m_pEngine);
}

QVariant CdmExecutorEngineScript::Evaluate(QString p_qstrCode, QString qstrName)
{
    CsaResultObject* pResult = nullptr;
    QScriptValue qsResultObject = m_pEngine->globalObject().property("resultObject");

    if (qsResultObject.isQObject())
    {
        pResult = dynamic_cast<CsaResultObject*>(qsResultObject.toQObject());
    }

    if (!pResult)
    {
        pResult = m_rpFactory->createResultObject();
    }

    m_pEngine->globalObject().setProperty("resultObject", m_pEngine->newQObject(pResult));
    QScriptValue qsValue = m_pEngine->evaluate(p_qstrCode, qstrName);
    QVariant qvResult = qsValue.toVariant();
    pResult->setResult(qvResult);

    return qvResult;
}

QVariant CdmExecutorEngineScript::Evaluate(QString p_qstrCode, QString qstrName, EdmValueType p_eReturnType)
{
    CsaResultObject* pResult = nullptr;
    QScriptValue qsResultObject = m_pEngine->globalObject().property("resultObject");

    if (qsResultObject.isQObject())
    {
        pResult = dynamic_cast<CsaResultObject*>(qsResultObject.toQObject());
    }

    if (!pResult)
    {
        pResult = m_rpFactory->createResultObject();
    }

    m_pEngine->globalObject().setProperty("resultObject", m_pEngine->newQObject(pResult));
    QScriptValue qsValue = m_pEngine->evaluate(p_qstrCode, qstrName);
    QVariant qvResult = qsValue.toVariant();
    pResult->setResult(qvResult);
    pResult->setResultType(p_eReturnType);

    return qvResult;
}

QVariant CdmExecutorEngineScript::Call(QString p_qstrName)
{
    return Call(p_qstrName, QVariantList());
}

CsaResultObject *CdmExecutorEngineScript::GetResultObject()
{
    QVariant qvResult = GetProperty("resultObject");
    return qvResult.value<CsaResultObject*>();
}

void CdmExecutorEngineScript::AddMethodProxy(CdmClassMethod *p_pMethod)
{
    Q_UNUSED(p_pMethod);
}

QVariant CdmExecutorEngineScript::Call(QString p_qstrName, QVariantList p_qvlArguments)
{
    QScriptValue qsResult;
    QScriptValue qsValue = m_pEngine->globalObject().property(p_qstrName);

    if (!qsValue.isNull())
    {
        if (p_qvlArguments.isEmpty())
        {
            qsResult = qsValue.call();
        }
        else
        {
            QList<QScriptValue> qsArgs;

            for (int iPos = 0; iPos < p_qvlArguments.count(); ++iPos)
            {
                QVariant qvArg = p_qvlArguments[iPos];
                qsArgs.append(m_pEngine->newVariant(qvArg));
            }

            qsResult = qsValue.call(QScriptValue(), qsArgs);
        }
    }
    else
    {
        ERR(p_qstrName + " not found for calling");
    }

    return qsResult.toVariant();
}

void CdmExecutorEngineScript::SetProperty(QString p_qstrName, QVariant p_qvProperty)
{
    m_pEngine->globalObject().setProperty(p_qstrName, m_pEngine->newVariant(p_qvProperty));
}

void CdmExecutorEngineScript::SetProperty(CdmValue *p_pValue)
{
    SetProperty(p_pValue, p_pValue->GetKeyname());
}

void CdmExecutorEngineScript::SetProperty(QString p_qstrName, QObject *p_pObject)
{
    m_pEngine->globalObject().setProperty(p_qstrName, m_pEngine->newQObject(p_pObject));
}

void CdmExecutorEngineScript::SetProperty(CdmValue *p_pValue, QString p_qstrVariableName)
{
    QScriptValue qsValue;
    if (CHKPTR(p_pValue))
    {
        if (p_pValue->GetValueType() == eDmValueObjectRef ||
            p_pValue->GetValueType() == eDmValueContainerRef)
        {
           CsaLocatedElement* pElement = m_rpFactory->createScriptObject(p_pValue);
           qsValue = m_pEngine->newQObject(pElement);
        }
        else
        {
           if (p_pValue->GetValueType() == eDmValueFormula)
           {
               WARNING("Formulas will be ignored. Keyname: " + p_pValue->GetKeyname());
              return;
           }

            qsValue = GenerateScriptValue(p_pValue);
        }

        m_pEngine->globalObject().setProperty(p_qstrVariableName, qsValue);
    }
}

void CdmExecutorEngineScript::SetThis(CsaObject *p_pThis)
{
    QScriptValue qjsThis = m_pEngine->newQObject(p_pThis);
    m_pEngine->globalObject().setProperty("currentObject",  qjsThis);
    m_pEngine->globalObject().setProperty("me",  qjsThis);
}

void CdmExecutorEngineScript::SetThis(CdmObject *p_pThis)
{
    SetThis(static_cast<CsaObject*>(m_rpFactory->createThisScriptObject(p_pThis)));
}

QVariant CdmExecutorEngineScript::GetProperty(QString p_qstrName)
{
    return m_pEngine->globalObject().property(p_qstrName).toVariant();
}

QScriptValue CdmExecutorEngineScript::GenerateScriptValue(CdmValue* p_pValue)
{
    QScriptValue qsValue;

    if (CHKPTR(p_pValue))
    {
        if (p_pValue->GetValueType() == eDmValueObjectRef ||
            p_pValue->GetValueType() == eDmValueContainerRef)
        {
           CsaLocatedElement* pElement = m_rpFactory->createScriptObject(p_pValue);
           qsValue = m_pEngine->newQObject(pElement);
        }
        else
        {
           if (p_pValue->GetValueType() == eDmValueFormula)
           {
               WARNING("Formulas will be ignored. Keyname: " + p_pValue->GetKeyname());
              return qsValue;
           }

           QVariant qvValue = p_pValue->GetValueVariant();

            switch(p_pValue->GetValueType())
            {
                case eDmValueBool:
                    qsValue = QScriptValue(qvValue.toBool());
                    break;
                case eDmValueCharacterDocument:
                    qsValue = QScriptValue(qvValue.toString());
                    break;
                case eDmValueDate:
                {
                    QDateTime qdateTime;
                    qdateTime.setDate(qvValue.toDate());
                    qsValue = m_pEngine->newDate(qdateTime);
                    break;
                }
                case eDmValueDateTime:
                    qsValue = m_pEngine->newDate(qvValue.toDateTime());
                    break;
                case eDmValueDouble:
                    qsValue = QScriptValue(qvValue.toDouble());
                    break;
                case eDmValueEnum:
                    qsValue = QScriptValue(qvValue.toInt());
                    break;
                case eDmValueFloat:
                    qsValue = QScriptValue(qvValue.toDouble());
                    break;
                case eDmValueInt:
                    qsValue = QScriptValue(qvValue.toInt());
                    break;
                case eDmValueLong:
                    qsValue = QScriptValue(qvValue.toInt());
                    break;
                case eDmValueString:
                    qsValue = QScriptValue(qvValue.toString());
                    break;
                case eDmValueTime:
                    {
                        QDateTime qdateTime;
                        qdateTime.setTime(qvValue.toTime());
                        qsValue = m_pEngine->newDate(qdateTime);
                    }
                    break;
                case eDmValueFormula:
                    qsValue = QScriptValue(m_pEngine->newVariant(qvValue));
                    break;
                default:
                    qsValue = QScriptValue(m_pEngine->newVariant(qvValue));
                    WARNING("Invalid type for script engine");
            }
        }
    }

    return qsValue;
}

void CdmExecutorEngineScript::ThrowError(QString p_qstrError)
{
    m_pEngine->currentContext()->throwError(p_qstrError);
    ERR(p_qstrError);
}

void CdmExecutorEngineScript::PushContext()
{
    m_pEngine->pushContext();
}

void CdmExecutorEngineScript::PopContext()
{
    m_pEngine->popContext();
}

void CdmExecutorEngineScript::SetValueToScript(CdmValue *p_pValue)
{
    if (CHKPTR(p_pValue))
    {
        m_pEngine->globalObject().setProperty("value", GenerateScriptValue(p_pValue));
    }
}

bool CdmExecutorEngineScript::HasUncaughtExceptions()
{
    bool bRet = false;

    if (m_pEngine->hasUncaughtException())
    {
        int line = m_pEngine->uncaughtExceptionLineNumber();
        QScriptValue qValue = m_pEngine->uncaughtException();
        QString qstrBacktrace = m_pEngine->uncaughtExceptionBacktrace().join("\n");
        QScriptContext* pContext = m_pEngine->currentContext();
        QScriptContextInfo contextInfo(pContext);
        EndDebugger();

        QString qstrException = QString(qApp->tr("Fehler in Programmlogik\nFehler im Code der Funktion %1 in Zeile  %1\n%2\nTrace:\n%3"))
                .arg(contextInfo.functionName())
                .arg(line)
                .arg(qValue.toString())
                .arg(qstrBacktrace);

        CdmExecutorRuntimeManager* pRuntimeManager = CdmExecutor::GetExecutor()->GetRuntimeManager();

         if (CHKPTR(pRuntimeManager))
         {
             CdmExecutorRuntime* pRuntime = pRuntimeManager->GetRuntime(this);

             if (CHKPTR(pRuntime))
             {
                 pRuntime->AddException(qstrException);
             }
         }

         ERR(qstrException);
         bRet = true;
    }

    return bRet;
}

void CdmExecutorEngineScript::StartDebugger()
{
    if (!m_pDebugger)
    {
       m_pDebugger = new QScriptEngineDebugger();
    }

    m_pDebugger->attachTo(m_pEngine);
    m_pDebugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
}

void CdmExecutorEngineScript::EndDebugger()
{
    if (m_pDebugger)
    {
       m_pDebugger->detach();
       DELPTR(m_pDebugger);
    }
}

bool CdmExecutorEngineScript::SupportsDebugger()
{
    return true;
}

bool CdmExecutorEngineScript::SyntaxCheck(QString p_qstrCode)
{
   bool bRet = false;

   QScriptSyntaxCheckResult qCheck = m_pEngine->checkSyntax(p_qstrCode);

   if (qCheck.state() == QScriptSyntaxCheckResult::Valid)
   {
      bRet = true;
   }
   else
   {
      QString qstrErrorMessage;
      qstrErrorMessage = QString(qApp->tr("Kompilierungsfehler in Zeile %1, Spalte %2\n"))
         .arg(qCheck.errorLineNumber())
         .arg(qCheck.errorColumnNumber());
      QString qstrError = qCheck.errorMessage();
      qstrErrorMessage += qstrError;
      ERR(qApp->tr("Fehler bei der Kompilierung.\n%1").arg(qstrErrorMessage));
   }

   return bRet;
}

void CdmExecutorEngineScript::InstallTranslatorFunctions()
{
    m_pEngine->installTranslatorFunctions();
}

void CdmExecutorEngineScript::Reset()
{
    DELPTR(m_pEngine);
    SetupEngine();
}

void CdmExecutorEngineScript::SetupEngine()
{
    m_pEngine = new QScriptEngine();
    m_rpFactory->collectGarbage();
    m_pEngine->globalObject().setProperty("wmsFactory", m_pEngine->toScriptValue(m_rpFactory));
    CdmExecutorAddOnManager* pAddOnManager = CdmExecutor::GetExecutor()->GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
       pAddOnManager->AddAditionalFunctionalityToEngine(*m_pEngine);
    }
}
