
#include <QScriptValue>

// WMS Commons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CsaObjectContainer.h"
#include "CdmClassMethod.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmScheme.h"
#include "CsaObject.h"
#include "CsaClass.h"
#include "CsaFunction.h"

CsaFunction::CsaFunction(CsaObject* p_pObject, QString p_qstrFunction)
    : CsaLocatedElement(),
      m_rpClass(nullptr),
      m_rpObject(p_pObject),
      m_qstrFunctionName(p_qstrFunction)
{
    if (CHKPTR(p_pObject))
    {
        CsaClass* pClass = dynamic_cast<CsaClass*> (p_pObject->getClass());

        if (CHKPTR(pClass))
        {
            setElement(pClass, p_qstrFunction);
        }
    }
}

CsaFunction::CsaFunction(CsaClass* p_pClass, QString p_qstrFunction)
    : CsaLocatedElement(),
      m_rpClass(p_pClass),
      m_rpObject(nullptr),
      m_qstrFunctionName(p_qstrFunction)
{
    setElement(p_pClass, p_qstrFunction);
}

CsaFunction::CsaFunction(CdmClassMethod* p_pMethod)
    : m_rpClass(nullptr),
      m_rpObject(nullptr),
      m_qstrFunctionName(p_pMethod->GetMethodName())
{
    setElement(p_pMethod);
}

CsaFunction::~CsaFunction()
{
}

void CsaFunction::setElement(CsaClass* p_pClass, QString p_qstrFunction)
{
    if (CHKPTR(p_pClass))
    {
        CdmClass* pClass = p_pClass->getInternals();

        if (CHKPTR(pClass))
        {
            CdmClassMethod* pMethod = pClass->FindMethod(p_qstrFunction);

            if (CHKPTR(pMethod))
            {
                setElement(pMethod);
            }
        }
    }
}

void CsaFunction::setElement(CdmClassMethod* p_pMethod)
{
    Q_UNUSED(p_pMethod);
    QString qstrUri;

    if (m_rpObject)
    {
        CdmObject* pObject = m_rpObject->getInternals();
        if (CHKPTR(pObject))
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_METHODS, QString::number(pObject->GetObjectContainerId()), QString::number(pObject->GetId()),m_qstrFunctionName);
            CsaLocatedElement::setElement(qstrUri);
        }
    }
    else
    {
        qstrUri = p_pMethod->GetUriInternal();
        CsaLocatedElement::setElement(qstrUri);
    }
}

CsaFunction* CsaFunction::getFunctionElement(QString p_qstrUri, CsaFactory& p_rFactory)
{
    CsaFunction* pFunction = nullptr;

    if (!p_qstrUri.isEmpty())
    {
        QString qstrUri = p_qstrUri;
        CdmDataProvider::ReplaceUnnecessaryUriParts(qstrUri);
        QString qstrType;
        QString qstrContainer;
        QString qstrObject;
        QString qstrFunction;
        QStringList qstrlUri = qstrUri.split("/");
        int posStart = 1;

        if (qstrlUri.count() > posStart)
        {
            qstrType = qstrlUri[posStart];
        }

        if (qstrlUri.count() > ++posStart)
        {
            qstrContainer = qstrlUri[posStart];
        }

        if (qstrlUri.count() > ++posStart)
        {
            qstrObject = qstrlUri[posStart];
        }

        if (qstrlUri.count() > ++posStart)
        {
            qstrFunction = qstrlUri[posStart];
        }

        if (!qstrFunction.isEmpty() && qstrFunction != "execute")
        {
            CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CdmScheme* pScheme = pDataProvider->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    QString qstrType = WMS_OBJECT;
                    CdmObject* pObject = dynamic_cast<CdmObject*> (pScheme->GetBaseObject(qstrType, qstrContainer, qstrObject, ""));

                    if (CHKPTR(pObject))
                    {
                        CdmClass* pClass = pObject->GetClass();

                        if (CHKPTR(pClass))
                        {
                            CdmClassMethod* pMethod = pClass->GetMethod(qstrFunction);

                            if (CHKPTR(pMethod))
                            {
                                CsaObject* pCsaObject = dynamic_cast<CsaObject*>(p_rFactory.createScriptObject(pObject));

                                if (CHKPTR(pCsaObject))
                                {
                                    pFunction = pCsaObject->getFunction(qstrFunction);
                                    pFunction->setFactory(&p_rFactory);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            qstrFunction = qstrObject;
            QString qstrClass = qstrContainer;

            CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CdmScheme* pScheme = pDataProvider->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    QString qstrType = WMS_CLASS;
                    QString qstrEmpty;
                    CdmClass* pClass = dynamic_cast<CdmClass*> (pScheme->GetBaseObject(qstrType, qstrClass, qstrEmpty, ""));

                    if (CHKPTR(pClass))
                    {
                        CdmClassMethod* pMethod = pClass->GetMethod(qstrFunction);

                        if (CHKPTR(pMethod))
                        {
                            CsaClass* pCsaClass = dynamic_cast<CsaClass*>(p_rFactory.createScriptObject(pClass));

                            if (CHKPTR(pCsaClass))
                            {
                                pFunction = pCsaClass->getFunction(qstrFunction);
                                pFunction->setFactory(&p_rFactory);
                            }
                        }
                    }
                }
            }
        }
    }

    return pFunction;
}

CdmLocatedElement* CsaFunction::getElement(QString p_qstrUri)
{
    CdmLocatedElement* pElement = nullptr;

    if (!p_qstrUri.isEmpty())
    {
        QString qstrUri = p_qstrUri;
        CdmDataProvider::ReplaceUnnecessaryUriParts(qstrUri);
        QString qstrType;
        QString qstrContainer;
        QString qstrObject;
        QString qstrFunction;
        QStringList qstrlUri = qstrUri.split("/", QString::SkipEmptyParts);
        int posStart = 1;

        if (qstrlUri.count() == 4) // method definition on class
        {
            posStart = 0;
            QString qstrClass;

            if (qstrlUri.count() > posStart)
            {
                qstrType = qstrlUri[posStart];
            }

            ++posStart;

            if (qstrlUri.count() > ++posStart)
            {
                qstrClass = qstrlUri[posStart];
            }

            if (qstrlUri.count() > ++posStart)
            {
                qstrFunction = qstrlUri[posStart];
            }

            CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CdmScheme* pScheme = pDataProvider->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    CdmClassManager* pClassManager = pScheme->GetClassManager();

                    if (CHKPTR(pClassManager))
                    {
                        CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

                        if (CHKPTR(pClass))
                        {
                            pElement = pClass->FindMethod(qstrFunction);
                        }
                    }
                }
            }
        }
        else
        {
            if (qstrlUri.count() > posStart)
            {
                qstrType = qstrlUri[posStart];
            }

            if (qstrlUri.count() > ++posStart)
            {
                qstrContainer = qstrlUri[posStart];
            }

            if (qstrlUri.count() > ++posStart)
            {
                qstrObject = qstrlUri[posStart];
            }

            if (qstrlUri.count() > ++posStart)
            {
                qstrFunction = qstrlUri[posStart];
            }

            if (!qstrFunction.isEmpty())
            {
                CdmDataProvider* pDataProvider = CdmSessionManager::GetDataProvider();

                if (CHKPTR(pDataProvider))
                {
                    CdmScheme* pScheme = pDataProvider->GetCurrentScheme();

                    if (CHKPTR(pScheme))
                    {
                        QString qstrType = WMS_OBJECT;
                        CdmObject* pObject = dynamic_cast<CdmObject*> (pScheme->GetBaseObject(qstrType, qstrContainer, qstrObject, ""));

                        if (CHKPTR(pObject))
                        {
                            CdmClass* pClass = pObject->GetClass();

                            if (CHKPTR(pClass))
                            {
                                pElement = pClass->GetMethod(qstrFunction);
                            }
                        }
                    }
                }
            }
        }

    }

    return pElement;

}

CdmLocatedElement* CsaFunction::getElement()
{
    return getElement(m_qstrUriInternal);
}

QVariant CsaFunction::execute(QVariantList qvLParams)
{
    QVariant qsvResult;
    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();


    if (CHKPTR(pExecutor))
    {
        if (m_rpObject)
        {
            qsvResult = pExecutor->GetFunction()->ExecuteObject(m_qstrFunctionName, m_rpObject->getInternals(), qvLParams);
        }
        else if (m_rpClass)
        {
            CdmClassMethod* pMethod = m_rpClass->getInternals()->FindMethod(m_qstrFunctionName);

            if (CHKPTR(pMethod))
            {
                qsvResult = pExecutor->GetFunction()->ExecuteStatic(pMethod, qvLParams);
            }
        }
        else
        {
            ERR("Can not execute function because class and object pointer are nullptr. Functionname: " + m_qstrFunctionName);
        }
    }

    return qsvResult;
}

QString CsaFunction::getName()
{
    return m_qstrFunctionName;
}

QVariant CsaFunction::execute(QScriptValue p_qArg1, QScriptValue p_qArg2, QScriptValue p_qArg3, QScriptValue p_qArg4, QScriptValue p_qArg5, QScriptValue p_qArg6, QScriptValue p_qArg7, QScriptValue p_qArg8, QScriptValue p_qArg9, QScriptValue p_qArg10, QScriptValue p_qArg11, QScriptValue p_qArg12, QScriptValue p_qArg13, QScriptValue p_qArg14, QScriptValue p_qArg15)
{
    QVariantList qlArguments;
    if (p_qArg1.isValid())
    {
        qlArguments.append(p_qArg1.toVariant());
    }

    if (p_qArg2.isValid())
    {
        qlArguments.append(p_qArg2.toVariant());
    }

    if (p_qArg3.isValid())
    {
        qlArguments.append(p_qArg3.toVariant());
    }

    if (p_qArg4.isValid())
    {
        qlArguments.append(p_qArg4.toVariant());
    }

    if (p_qArg5.isValid())
    {
        qlArguments.append(p_qArg5.toVariant());
    }

    if (p_qArg6.isValid())
    {
        qlArguments.append(p_qArg6.toVariant());
    }

    if (p_qArg7.isValid())
    {
        qlArguments.append(p_qArg7.toVariant());
    }

    if (p_qArg8.isValid())
    {
        qlArguments.append(p_qArg8.toVariant());
    }

    if (p_qArg9.isValid())
    {
        qlArguments.append(p_qArg9.toVariant());
    }

    if (p_qArg10.isValid())
    {
        qlArguments.append(p_qArg10.toVariant());
    }

    if (p_qArg11.isValid())
    {
        qlArguments.append(p_qArg11.toVariant());
    }

    if (p_qArg12.isValid())
    {
        qlArguments.append(p_qArg12.toVariant());
    }

    if (p_qArg13.isValid())
    {
        qlArguments.append(p_qArg13.toVariant());
    }

    if (p_qArg14.isValid())
    {
        qlArguments.append(p_qArg14.toVariant());
    }

    if (p_qArg15.isValid())
    {
        qlArguments.append(p_qArg15.toVariant());
    }

    return execute(qlArguments);
}

QString CsaFunction::getUri() const
{
    QString qstrUri;

    if (m_rpObject)
    {
        CdmObject* pObject = m_rpObject->getInternals();
        if (CHKPTR(pObject))
        {
            qstrUri = CdmLocatedElement::CreateUri(WMS_METHODS, pObject->GetObjectContainerKeyname(), pObject->GetKeyname(),m_qstrFunctionName);
        }
    }
    else if (m_rpClass)
    {
        qstrUri = CdmLocatedElement::CreateUri(WMS_METHODS, m_rpClass->getKeyname(),m_qstrFunctionName);
    }
    else
    {
        qstrUri = CsaLocatedElement::getUri();
    }

    return qstrUri;
}
/*
QVariant CsaFunction::execute(QJSValue p_qlArguments)
{
    QVariant qsvResult;

    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
    {
        QVariantList qlArguments;
        if (p_qlArguments.isArray())
        {
            int size = p_qlArguments.property("length").toInt();

            for (int pos = 0; pos < size; ++pos)
            {
                QJSValue qsvArgument = p_qlArguments.property(pos);
                qlArguments.append(qsvArgument.toVariant());
            }
        }
        else if (!p_qlArguments.isNull())
        {
            qlArguments.append(p_qlArguments.toVariant());
        }

        if (m_rpObject)
        {
            qsvResult = pExecutor->GetFunction()->ExecuteObject(m_qstrFunctionName, m_rpObject->getInternals(), qlArguments);
        }
        else if (m_rpClass)
        {
            CdmClassMethod* pMethod = m_rpClass->getInternals()->FindMethod(m_qstrFunctionName);

            if (CHKPTR(pMethod))
            {
                qsvResult = pExecutor->GetFunction()->ExecuteStatic(pMethod, qlArguments);
            }
        }
        else
        {
            ERR("Can not execute function because class and object pointer are nullptr. Functionname: " + m_qstrFunctionName);
        }
    }

    return qsvResult;
}
*/

QVariant CsaFunction::getRoughVariant()
{
    QVariantMap qvm;
    CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (getElement());
    qvm.insert(WMS_NAME, m_qstrFunctionName);

    if (CHKPTR(pMethod))
    {
        qvm.insert(WMS_REFERENCEURI, getUri());
        qvm.insert(WMS_ACCESS, pMethod->GetAccessModeAsString());
        qvm.insert(WMS_RETURNTYPE, CdmMember::GetValueTypeAsString(pMethod->GetReturnType()));
        qvm.insert(WMS_STATIC, pMethod->IsStatic());
    }

    return qvm;
}

QVariant CsaFunction::getDetailedVariant()
{
    QVariantMap qvm = getRoughVariant().toMap();
    CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (getElement());

    if (CHKPTR(pMethod))
    {
        qvm.insert(WMS_PARAMETERS, pMethod->GetParametersAsStringForFunction());
        qvm.insert(WMS_CAPTION, pMethod->GetCaption());
        qvm.insert(WMS_COMMENT, pMethod->GetComment());
        qvm.insert(WMS_VERSION, pMethod->GetVersion());
    }

    return qvm;
}

CsaObject* CsaFunction::getObject()
{
    return m_rpObject;
}
