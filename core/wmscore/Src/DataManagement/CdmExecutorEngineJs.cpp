
// System and Qt Includes
#include <QJSEngine>
#include <QJSValue>

// Own Includes
#include "CsaFactory.h"
#include "CsaResultObject.h"
#include "CsaObject.h"
#include "CdmObject.h"
#include "CsaModelElement.h"
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorAddOnManager.h"
#include "CdmValue.h"
#include "CdmExecutorEngineJs.h"

CdmExecutorEngineJs::CdmExecutorEngineJs(CsaFactory* p_pFactory)
    : m_rpFactory(p_pFactory)
{
    SetupEngine();
}

CdmExecutorEngineJs::~CdmExecutorEngineJs()
{
    DELPTR(m_pEngine);
}

QVariant CdmExecutorEngineJs::Evaluate(QString p_qstrCode, QString qstrName)
{
    CsaResultObject* pResult = m_rpFactory->createResultObject();
    m_pEngine->globalObject().setProperty("resultObject", m_pEngine->toScriptValue(pResult));
    QJSValue qjsValue = m_pEngine->evaluate(p_qstrCode, qstrName);
    QVariant qvResult = qjsValue.toVariant();
    pResult->setResult(qvResult);
    return qvResult;
}

QVariant CdmExecutorEngineJs::Call(QString p_qstrName)
{
    return Call(p_qstrName, QVariantList());
}

QVariant CdmExecutorEngineJs::Call(QString p_qstrName, QVariantList p_qvlArguments)
{
    QJSValue qjsResult;
    QJSValue qjsValue = m_pEngine->globalObject().property(p_qstrName);

    if (!qjsValue.isNull())
    {
        if (p_qvlArguments.isEmpty())
        {
            qjsResult = qjsValue.call();
        }
        else
        {
            QJSValueList qjsArgs;

            for (int iPos = 0; iPos < p_qvlArguments.count(); ++iPos)
            {
                QVariant qvArg = p_qvlArguments[iPos];
                qjsArgs.append(m_pEngine->toScriptValue(qvArg));
            }

            qjsResult = qjsValue.call(qjsArgs);
        }
    }
    else
    {
        ERR(p_qstrName + " not found for calling");
    }

    return qjsResult.toVariant();
}

void CdmExecutorEngineJs::SetProperty(QString p_qstrName, QVariant p_qvProperty)
{
    m_pEngine->globalObject().setProperty(p_qstrName, m_pEngine->toScriptValue(p_qvProperty));
}

void CdmExecutorEngineJs::SetProperty(CdmValue *p_pValue)
{
    QJSValue qsValue;
    if (CHKPTR(p_pValue))
    {
        if (p_pValue->GetValueType() == eDmValueObjectRef ||
            p_pValue->GetValueType() == eDmValueContainerRef)
        {
           CsaLocatedElement* pElement = m_rpFactory->createScriptObject(p_pValue);
           qsValue = m_pEngine->toScriptValue(pElement);
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

        m_pEngine->globalObject().setProperty(p_pValue->GetKeyname(), qsValue);
    }
}

void CdmExecutorEngineJs::SetProperty(QString p_qstrName, QObject *p_pObject)
{
    m_pEngine->globalObject().setProperty(p_qstrName, m_pEngine->toScriptValue(p_pObject));
}

QVariant CdmExecutorEngineJs::GetProperty(QString p_qstrName)
{
    return m_pEngine->globalObject().property(p_qstrName).toVariant();
}

void CdmExecutorEngineJs::SetThis(CsaObject *p_pThis)
{
    QJSValue qjsThis = m_pEngine->toScriptValue(p_pThis);
    m_pEngine->globalObject().setProperty("currentObject",  qjsThis);
    m_pEngine->globalObject().setProperty("me",  qjsThis);
}

void CdmExecutorEngineJs::SetThis(CdmObject *p_pThis)
{
    SetThis(static_cast<CsaObject*>(m_rpFactory->createThisScriptObject(p_pThis)));
}

QJSValue CdmExecutorEngineJs::GenerateScriptValue(CdmValue* p_pValue)
{
    QJSValue qsValue;

    if (CHKPTR(p_pValue))
    {
        if (p_pValue->GetValueType() == eDmValueObjectRef ||
            p_pValue->GetValueType() == eDmValueContainerRef)
        {
           CsaLocatedElement* pElement = m_rpFactory->createScriptObject(p_pValue);
           qsValue = m_pEngine->toScriptValue(pElement);
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
                    qsValue = QJSValue(qvValue.toBool());
                    break;
                case eDmValueCharacterDocument:
                    qsValue = QJSValue(qvValue.toString());
                    break;
                case eDmValueDate:
                {
                    QDateTime qdateTime;
                    qdateTime.setDate(qvValue.toDate());
                    qsValue = m_pEngine->toScriptValue(qdateTime);
                    break;
                }
                case eDmValueDateTime:
                    qsValue = m_pEngine->toScriptValue(qvValue.toDateTime());
                    break;
                case eDmValueDouble:
                    qsValue = QJSValue(qvValue.toDouble());
                    break;
                case eDmValueEnum:
                    qsValue = QJSValue(qvValue.toInt());
                    break;
                case eDmValueFloat:
                    qsValue = QJSValue(qvValue.toDouble());
                    break;
                case eDmValueInt:
                    qsValue = QJSValue(qvValue.toInt());
                    break;
                case eDmValueLong:
                    qsValue = QJSValue(qvValue.toInt());
                    break;
                case eDmValueString:
                    qsValue = QJSValue(qvValue.toString());
                    break;
                case eDmValueTime:
                    {
                        QDateTime qdateTime;
                        qdateTime.setTime(qvValue.toTime());
                        qsValue = m_pEngine->toScriptValue(qdateTime);
                    }
                    break;
                case eDmValueFormula:
                    qsValue = QJSValue(m_pEngine->toScriptValue(qvValue));
                    break;
                default:
                    qsValue = QJSValue(m_pEngine->toScriptValue(qvValue));
                    WARNING("Invalid type for script engine");
            }
        }
    }

    return qsValue;
}

void CdmExecutorEngineJs::ThrowError(QString p_qstrError)
{
    // At the moment not supported by QJSEngine
    ERR(p_qstrError);
}

void CdmExecutorEngineJs::PushContext()
{
    // At the moment not supported by QJSEngine
}

void CdmExecutorEngineJs::PopContext()
{
    // At the moment not supported by QJSEngine
}

void CdmExecutorEngineJs::SetValueToScript(CdmValue *p_pValue)
{
    if (CHKPTR(p_pValue))
    {
        m_pEngine->globalObject().setProperty("value", GenerateScriptValue(p_pValue));
    }
}

bool CdmExecutorEngineJs::HasUncaughtExceptions()
{
    // ToDo
    return false;
}

void CdmExecutorEngineJs::StartDebugger()
{

}

void CdmExecutorEngineJs::EndDebugger()
{

}

bool CdmExecutorEngineJs::SupportsDebugger()
{
    return false;
}

bool CdmExecutorEngineJs::SyntaxCheck(QString p_qstrCode)
{
    Q_UNUSED(p_qstrCode);
    // Not supported by QJSEngine
    return true;
}

void CdmExecutorEngineJs::InstallTranslatorFunctions()
{
    // TODO
}

CsaResultObject *CdmExecutorEngineJs::GetResultObject()
{
    QVariant qvResult = GetProperty("resultObject");
    return qvResult.value<CsaResultObject*>();
}

void CdmExecutorEngineJs::AddMethodProxy(CdmClassMethod *p_pMethod)
{
    Q_UNUSED(p_pMethod);
}

void CdmExecutorEngineJs::Reset()
{
    DELPTR(m_pEngine);
    SetupEngine();
}

void CdmExecutorEngineJs::SetupEngine()
{
    m_pEngine = new QJSEngine();
    m_pEngine->globalObject().setProperty(QString("wmsFactory"), m_pEngine->toScriptValue(m_rpFactory));
    CdmExecutorAddOnManager* pAddOnManager = CdmExecutor::GetExecutor()->GetAddOnManager();

    if (CHKPTR(pAddOnManager))
    {
       pAddOnManager->AddAditionalFunctionalityToEngine(*m_pEngine);
    }

}
