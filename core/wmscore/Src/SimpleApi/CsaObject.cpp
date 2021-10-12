/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <QScriptValue>
#include <QEvent>
#include <QDynamicPropertyChangeEvent>

// WMS COmmons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmRights.h"
#include "CdmExecutor.h"
#include "CdmLogging.h"
#include "CdmExecutorFunction.h"
#include "CdmValueObjectRef.h"
#include "CdmValueListObjects.h"
#include "CdmValueContainerRef.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CwmsJson.h"
#include "CdmValueUser.h"
#include "CumUser.h"
#include "CdmValue.h"
#include "CdmValueBinaryDocument.h"
#include "CsaUser.h"
#include "CsaClass.h"
#include "CsaFunction.h"
#include "CsaValue.h"
#include "CsaObjectContainer.h"
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaValueReference.h"
#include "CdmObjectAdaptor.h"

CsaObject::CsaObject(CdmObject *p_pObject, CsaFactory* p_pFactory, bool p_bThis)
    : CsaModelElement(p_pObject),
      m_bThis(p_bThis)
{
    setFactory(p_pFactory);
    addValuesAsProperties();
    addFunctionsToObject();
    installEventFilter(this);
}

CsaObject::~CsaObject()
{
    QMapIterator<QString, CsaValue*> qmIt(m_qmValues);

    while (qmIt.hasNext())
    {
        qmIt.next();
        CsaValue* pValue = qmIt.value();
        DELPTR(pValue);
    }

    m_qmValues.clear();

    for (int iPos = 0; iPos < m_qlReferences.count(); ++iPos)
    {
        CsaValueReference* pValue = m_qlReferences[iPos];
        DELPTR(pValue);
    }

    m_qlReferences.clear();

    for (int iPos = 0; iPos < m_qlFunctions.count(); ++iPos)
    {
        CsaFunction* pValue = m_qlFunctions[iPos];
        DELPTR(pValue);
    }

    m_qlFunctions.clear();
}

CdmObject *CsaObject::getInternals()
{
    return static_cast<CdmObject*>(getElement());
}

QVariant CsaObject::getValuePrimitive(QString p_qstrKeyname)
{
    if (getInternals())
    {
        return getInternals()->GetVariant(p_qstrKeyname);
    }

    return QVariant();
}


void CsaObject::addValuesAsProperties()
{
    CdmObject* pObject = getInternals();
    if (pObject)
    {
        INFO("Add Object with ID " + QString::number(pObject->GetId()) + " to ScriptEngine.");
        QMap<QString, CdmValue*> qmValues;
        pObject->CheckAllValuesCreated();
        pObject->GetValueMap(qmValues);

        QMap<QString, CdmValue*>::iterator qmIt = qmValues.begin();
        QMap<QString, CdmValue*>::iterator qmItEnd = qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmValue* pCdmValue = qmIt.value();
            INFO("Add Value with ID " + QString::number(pCdmValue->GetId()) + " to ScriptEngine.");

            if (CHKPTR(pCdmValue))
            {
                connect(pCdmValue, SIGNAL(ValueChanged(CdmValue*)), this, SLOT(ValueChangedSlot(CdmValue*)));
                CsaValue* pCsaValue = new CsaValue(pCdmValue, this);
                QString qstrKeyname = qmIt.key();
                m_qmValues.insert(qstrKeyname, pCsaValue);
                QString qstrValueType = pCdmValue->GetMember()->GetValueTypeAsString();
                INFO("CsaValue of Value " + qmIt.key() + " created.");

                if (pCdmValue->GetValueType() != eDmValueObjectRef &&
                        pCdmValue->GetValueType() != eDmValueContainerRef)
                {
                    INFO("Value is a Object or Container Ref, add only the value");
                    INFO("Value " + qstrKeyname + "(" + qstrValueType + ") is of primitive type add it as variant");
                    setProperty(qstrKeyname.toUtf8(), pCsaValue->getValue());
                }
                else // Special case references the object must be read with getValue and set with setValue
                {
                    QVariant qvValueObject;
                    CsaValueReference* pRef = new CsaValueReference(pCdmValue);
                    pRef->setFactory(getFactory());
                    m_qlReferences.append(pRef); // for garbage collection
                    INFO("Value " + qstrKeyname + "(" + qstrValueType + ") is a container or object and will be added is QObject.");
                    qvValueObject.setValue(pRef);
                    setProperty(qstrKeyname.toUtf8(), qvValueObject);
                }
            }
        }
    }
}

void CsaObject::addFunctionsToObject()
{
    CdmObject* pObject = getInternals();
    CdmClass* pClass = pObject->GetClass();

    if (CHKPTR(pClass))
    {
        QMap<QString, CdmClassMethod*> qmMethods = pClass->GetAllMethods();
        QMapIterator<QString, CdmClassMethod*> qmIt(qmMethods);

        while (qmIt.hasNext())
        {
            qmIt.next();
            CdmClassMethod* pMethod = qmIt.value();

            if (CHKPTR(pMethod))
            {
                QVariant qvMethod;
                CsaFunction* pFunction = new CsaFunction(this, qmIt.key());
                pFunction->setElement(pMethod);
                pFunction->setFactory(getFactory());
                qvMethod.setValue(pFunction);
                m_qlFunctions.append(pFunction);
                setProperty(qmIt.key().toUtf8(), qvMethod);
            }
        }
    }
}

void CsaObject::ValueChangedSlot(CdmValue* p_pCdmValue)
{
    if(CHKPTR(p_pCdmValue))
    {
        if (m_qmValues.contains(p_pCdmValue->GetKeyname()))
        {
            CsaValue* pValue = m_qmValues[p_pCdmValue->GetKeyname()];

            if (CHKPTR(pValue) && property(p_pCdmValue->GetKeyname().toUtf8()) != pValue->getValue())
            {
                setProperty(p_pCdmValue->GetKeyname().toUtf8(), pValue->getValue());
            }
        }
    }
}


void CsaObject::setValuePrimitive(QString p_qstrKeyname, QVariant p_Value)
{
    if (CHKPTR(getInternals()))
    {
        getInternals()->SetValue(p_qstrKeyname, p_Value);
    }
}

QObject *CsaObject::getValueUser(QString p_qstrKeyname)
{
    QObject* pObject = nullptr;

    if (CHKPTR(getInternals()))
    {
        CdmValue* pValue = getInternals()->GetValue(p_qstrKeyname);

        if (CHKPTR(pValue))
        {
            if (pValue->GetValueType() == eDmValueUser)
            {
                pObject = getFactory()->createScriptObject(((CdmValueUser*)pValue)->GetUser());
            }
        }
    }

    return pObject;
}

QString CsaObject::getValueDisplayString(QString p_qstrKeyname)
{
    QString qstrDisplayString;

    if (CHKPTR(getInternals()))
    {
        CdmValue* pValue = getInternals()->GetValue(p_qstrKeyname);

        if (CHKPTR(pValue))
        {
            qstrDisplayString = pValue->GetDisplayString();
        }
    }

    return qstrDisplayString;
}

void CsaObject::setValueUser(QString p_qstrKeyname, QObject * p_pRef)
{
    if (CHKPTR(getInternals()))
    {
        CdmValue* pValue = getInternals()->GetValue(p_qstrKeyname);
        CsaUser* pElement = dynamic_cast<CsaUser*>(p_pRef);

        if (CHKPTR(pValue))
        {
            if (pValue->GetValueType() == eDmValueUser)
            {
                if (pElement)
                {
                    ((CdmValueUser*)pValue)->SetUser(dynamic_cast<CumUser*>(pElement->getInternals()));
                }
                else
                {
                    ((CdmValueUser*)pValue)->SetUser(nullptr);
                }
            }
        }
    }
}

QObject *CsaObject::getValueReference(QString p_qstrKeyname)
{
    QObject* pObject = nullptr;

    if (CHKPTR(getInternals()))
    {
        CdmValue* pValue = getInternals()->GetValue(p_qstrKeyname);

        if (CHKPTR(pValue))
        {
            if (pValue->GetValueType() == eDmValueObjectRef)
            {
                pObject = getFactory()->createScriptObject(((CdmValueObjectRef*)pValue)->GetObject());
            }
            else if (pValue->GetValueType() == eDmValueContainerRef)
            {
                pObject = getFactory()->createScriptObject(((CdmValueContainerRef*)pValue)->GetContainer());
            }
        }
    }

    return pObject;
}


void CsaObject::setValueReference(QString p_qstrKeyname, QObject * p_pRef)
{
    CdmObject* pObject = getInternals();

    if (CHKPTR(pObject))
    {
        CdmValue* pValue = pObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pValue))
        {
            if (pValue->GetValueType() == eDmValueObjectRef)
            {
                CsaObject* pObject = dynamic_cast<CsaObject*>(p_pRef);

                if (pObject)
                {
                    ((CdmValueObjectRef*)pValue)->SetValue(static_cast<CdmObject*>(pObject->getInternals()));
                }
                else
                {
                    ((CdmValueObjectRef*)pValue)->SetValue(static_cast<CdmObject*>(nullptr));
                }

            }
            else if (pValue->GetValueType() == eDmValueContainerRef)
            {
                CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(p_pRef);

                if (pContainer)
                {
                    ((CdmValueContainerRef*)pValue)->SetValue(static_cast<CdmObjectContainer*>(pContainer->getInternals()));
                }
                else
                {
                    ((CdmValueContainerRef*)pValue)->SetValue(static_cast<CdmObjectContainer*>(nullptr));
                }
            }
        }
    }
}

QObject *CsaObject::getContainer()
{
    if (CHKPTR(getInternals()))
    {
        return getFactory()->createScriptObject(getInternals()->GetObjectContainer());
    }
    else
    {
        return nullptr;
    }
}

int CsaObject::commit()
{
    int iRet = CdmLogging::eDmInvalidObjectPtr;
    CdmObject* pObject = getInternals();

    if (CHKPTR(pObject))
    {
        iRet = getInternals()->Commit();
    }

    return iRet;
}

void CsaObject::refreshObject()
{
    CdmObject* pObject = getInternals();

    if (CHKPTR(pObject))
    {
        pObject->Refresh();

        if ( pObject->IsDeleted())
        {
            // What to do here?
        }
    }
}

QString CsaObject::getValueString(QString p_qstrKeyname) const
{
    QString qstrString;
    CdmObject* pCdmObject = (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, qstrString);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return qstrString;
}


QTime CsaObject::getValueTime(QString p_qstrKeyname) const
{
    QTime qtTime;
    CdmObject* pCdmObject = (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, qtTime);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return qtTime;
}

QDate CsaObject::getValueDate(QString p_qstrKeyname) const
{
    QDate qdDate;
    CdmObject* pCdmObject = (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, qdDate);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return qdDate;
}

QDateTime CsaObject::getValueDateTime(QString p_qstrKeyname) const
{
    QDateTime qdDateTime;
    CdmObject* pCdmObject = (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, qdDateTime);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return qdDateTime;
}

float CsaObject::getValueFloat(QString p_qstrKeyname) const
{
    float fRet = 0.0f;
    CdmObject* pCdmObject =  (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, fRet);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return fRet;
}

bool CsaObject::getValueBool(QString p_qstrKeyname) const
{
    bool bRet = false;
    CdmObject* pCdmObject =  (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, bRet);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return bRet;
}

int CsaObject::getValueInt(QString p_qstrKeyname) const
{
    int iRet = 0;
    CdmObject* pCdmObject =  (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, iRet);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return iRet;
}

qint64 CsaObject::getValueLong(QString p_qstrKeyname) const
{
   qint64 lRet = 0;
    CdmObject* pCdmObject =  (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueLong ||
                    pCdmValue->GetValueType() == eDmValueCounter)
            {
                lRet = ((CdmValueLong*)pCdmValue)->GetValue();
            }
        }
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return lRet;
}

double CsaObject::getValueDouble(QString p_qstrKeyname) const
{
    double dRet = 0.0;
    CdmObject* pCdmObject = (const_cast<CsaObject*>(this))->getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->GetValue(p_qstrKeyname, dRet);
    }
    else
    {
        ERR ("Object is nullptr.");
    }

    return dRet;
}

void CsaObject::setValueString(QString p_qstrKeyname, QString p_qstrValue)
{

    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_qstrValue);
    }
}


void CsaObject::setValueDate(QString p_qstrKeyname, QDate p_qdDate)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_qdDate);
    }
}

void CsaObject::setValueDateTime(QString p_qstrKeyname, QDateTime p_qdtDateTime)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_qdtDateTime);
    }
}

void CsaObject::setValueTime(QString p_qqstrkeyname, QTime p_qtTime)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qqstrkeyname, p_qtTime);
    }
}

void CsaObject::setValueFloat(QString p_qstrKeyname, float p_fValue)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_fValue);
    }
}

void CsaObject::setValueDouble(QString p_qstrKeyname, double p_dValue)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_dValue);
    }
}


void CsaObject::setValueInt(QString p_qstrKeyname, int p_iValue)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_iValue);
    }
}

void CsaObject::setValueLong(QString p_qstrKeyname,qint64 p_lValue)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_lValue);
    }
}

void CsaObject::setValueBool(QString p_qstrKeyname, bool p_bValue)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        pCdmObject->SetValue(p_qstrKeyname, p_bValue);
    }
}

void CsaObject::addValueListObjectItem(QString p_qstrKeyname, QObject *p_qObject)
{
    CdmObject* pCdmObject = getInternals();

    if (CHKPTR(p_qObject) && CHKPTR(pCdmObject))
    {
        CsaObject* pValue = static_cast<CsaObject*>(p_qObject);
        CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueListObjects)
            {
                ((CdmValueListObjects*)pCdmValue)->AddValue(pValue->getInternals());
            }
        }
    }
}

void CsaObject::removeValueListObjectItem(QString p_qstrKeyname, QObject *p_qObject)
{
    CdmObject* pCdmObject = getInternals();

    if (CHKPTR(p_qObject) && CHKPTR(pCdmObject))
    {
        CsaObject* pValue = static_cast<CsaObject*>(p_qObject);
        CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pCdmValue))
        {
            if (pCdmValue->GetValueType() == eDmValueListObjects)
            {
                ((CdmValueListObjects*)pCdmValue)->RemoveValue(pValue->getInternals());
            }
        }
    }
}

void CsaObject::setValueBinaryDocument(QString p_qstrKeyname, QString p_qstrFilename, QString p_qstrFiletype, QString p_qstrBase64)
{
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        CdmValue* pValue = pCdmObject->GetValue(p_qstrKeyname);

        if (CHKPTR(pValue) && pValue->GetValueType() == eDmValueBinaryDocument)
        {
            CdmValueBinaryDocument* pBinDoc = static_cast<CdmValueBinaryDocument*>(pValue);
            pBinDoc->SetBase64(p_qstrFilename, p_qstrFiletype, p_qstrBase64);
        }
    }
}


QString CsaObject::getJson()
{
    QString qstrJson;
    QVariant qVariant = getDetailedVariant();
    bool success = true;
    CwmsJson cJson;
    qstrJson = cJson.serialize(qVariant, success);
    return qstrJson;
}

QVariantMap CsaObject::getObjectGraphVariant(bool p_bFollowNonOwnerObjectlist, bool p_bFollowNonOwnerObject, QStringList p_qstrExcludedKeynames, int p_iMaxDepth, int p_iMaxObjects)
{
    QVariantMap qVariant;
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        CdmObjectAdaptor cCdmObjectAdaptor(pCdmObject);
        qVariant = cCdmObjectAdaptor.GetVariantGraph(p_bFollowNonOwnerObjectlist, p_bFollowNonOwnerObject, p_qstrExcludedKeynames, p_iMaxDepth, p_iMaxObjects);
    }

    return qVariant;
}

QVariant CsaObject::getDetailedVariant()
{
    QVariantMap qVariantMap;
    CdmObject* pCdmObject = getInternals();

    if(CHKPTR(pCdmObject))
    {
        QVariantMap qVariantMapValues;

        QMap<QString, CsaValue*>::iterator qmIt = m_qmValues.begin();
        QMap<QString, CsaValue*>::iterator qmItEnd = m_qmValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CsaValue* pValue = qmIt.value();

            if (CHKPTR(pValue) && pValue->hasCurrentUserReadAccess())
            {
                qVariantMapValues.insert(qmIt.key(), pValue->getRoughVariant());
            }
        }

        QVariantList qvlMethods;

        for (int iPos = 0; iPos < m_qlFunctions.count(); ++iPos)
        {
           CsaFunction* pFunction = m_qlFunctions[iPos];

           if (CHKPTR(pFunction))
           {
              CdmClassMethod* pMethod = dynamic_cast<CdmClassMethod*> (pFunction->getElement());

              if (CHKPTR(pMethod) &&
                  pMethod->GetAccess() ==  eDmMemberAccessPublic &&
                  pMethod->GetRights().HasCurrentUserWriteAccess())
              {
                 if (CHKPTR(pFunction))
                 {
                    qvlMethods.append(pFunction->getRoughVariant());
                 }
              }
           }
        }

        const CdmClass* pClass = pCdmObject->GetClass();

        if (CHKPTR(pClass))
        {
           CsaClass* pCsaClass = dynamic_cast<CsaClass*> (getFactory()->createScriptObject(const_cast<CdmClass*>(pClass)));

           if (CHKPTR(pCsaClass))
           {
              qVariantMap.insert(WMS_CLASS, pCsaClass->getRoughVariant());
           }
        }

        qVariantMap.insert(WMS_METHODS, qvlMethods);
        qVariantMap.insert(WMS_VALUES, qVariantMapValues);
        qVariantMap.insert(WMS_ID, static_cast<int>(pCdmObject->GetId()));
        qVariantMap.insert(WMS_CONTAINER, static_cast<int>(pCdmObject->GetObjectContainerId()));
        qVariantMap.insert(WMS_KEYNAME, pCdmObject->GetKeyname());
        qVariantMap.insert(WMS_URI, pCdmObject->GetUri());
        qVariantMap.insert(WMS_TYPE, WMS_OBJECT);
    }
    return qVariantMap;
}

QList<CsaFunction*>& CsaObject::getFunctions()
{
   return m_qlFunctions;
}

CsaFunction *CsaObject::getFunction(QString qstrName)
{
   for (int iPos = 0; iPos < m_qlFunctions.count(); ++iPos)
   {
      CsaFunction* pFunction = m_qlFunctions[iPos];

      if (pFunction->getName() == qstrName)
      {
         return pFunction;
      }
   }

   return nullptr;
}

void CsaObject::deleteObjectOnDb()
{
    CdmObject* pObject = getInternals();

    if (CHKPTR(pObject))
    {
        pObject->SetDeleted();
        pObject->Commit();
    }
}

void CsaObject::setDeleted()
{
    DEPRECATED
    deleteObjectOnDb();
}

bool CsaObject::isDeleted()
{
    DEPRECATED
    return getInternals()->IsDeleted();
}

bool CsaObject::isModified()
{
    return getInternals()->IsModified();
}

bool CsaObject::hasCurrentUserReadAccess()
{
    CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(getContainer());

    if (CHKPTR(pContainer))
    {
        return pContainer->hasCurrentUserReadAccess();
    }

    return false;
}

bool CsaObject::hasCurrentUserWriteAccess()
{
    CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(getContainer());

    if (CHKPTR(pContainer))
    {
        return pContainer->hasCurrentUserReadAccess();
    }

    return false;
}

QVariant CsaObject::execute(QString p_qstrMethod, QScriptValue p_qArg1, QScriptValue p_qArg2, QScriptValue p_qArg3, QScriptValue p_qArg4, QScriptValue p_qArg5, QScriptValue p_qArg6, QScriptValue p_qArg7, QScriptValue p_qArg8, QScriptValue p_qArg9, QScriptValue p_qArg10, QScriptValue p_qArg11, QScriptValue p_qArg12, QScriptValue p_qArg13, QScriptValue p_qArg14, QScriptValue p_qArg15)
{
    QVariant qsvResult;

    CdmExecutor* pExecutor = CdmExecutor::GetExecutor();

    if (CHKPTR(pExecutor))
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

        qsvResult = pExecutor->GetFunction()->ExecuteObject(p_qstrMethod, getInternals(), qlArguments);
    }

    return qsvResult;
}

QVariant CsaObject::execute(QString p_qstrFunctionName, QJSValue p_qlArguments)
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

        qsvResult = pExecutor->GetFunction()->ExecuteObject(p_qstrFunctionName, getInternals(), qlArguments);
    }

    return qsvResult;
}


bool CsaObject::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::DynamicPropertyChange)
    {
        QDynamicPropertyChangeEvent *const myEvent = static_cast<QDynamicPropertyChangeEvent *>(event);

        if(myEvent)
        {
            QString qstrKeyname(myEvent->propertyName());
            updateValue(qstrKeyname);
        }

        myEvent->setAccepted(true);
    }

    return QObject::eventFilter(obj, event);
}

bool CsaObject::updateValue(QString p_qstrKeyname)
{
    bool bRet = false;
    QVariant qvValue = property(p_qstrKeyname.toUtf8());
    CsaValue* pValue = dynamic_cast<CsaValue*> (findValue(p_qstrKeyname));

    if (pValue && qvValue.isValid())
    {
        pValue->setValue(qvValue);
        bRet = true;
    }

    return bRet;
}

QObject* CsaObject::findValue(QString p_qstrKeyname)
{
    CsaValue* pValue = nullptr;

    if (m_qmValues.contains(p_qstrKeyname))
    {
        pValue = m_qmValues[p_qstrKeyname];
    }

    return pValue;
}

bool CsaObject::hasOwner()
{
    return getInternals()->HasOwner();
}

bool CsaObject::hasOwner(QString qstrObjectKeyname)
{
    Q_UNUSED(qstrObjectKeyname);
    ERR("Not needed here.");
    return false;
}

QObject *CsaObject::getOwner()
{
    return static_cast<CsaObject*> (getFactory()->createScriptObject(getInternals()->GetOwner()));
}

QObject *CsaObject::getOwner(QString qstrObjectKeyname)
{
    Q_UNUSED(qstrObjectKeyname);
    ERR("Not needed here.");
    return nullptr;
}

bool CsaObject::isImmutable()
{
    return getInternals()->IsReadOnly();
}

void CsaObject::setImmutable(bool p_bImmutable)
{
    getInternals()->SetImmutable(p_bImmutable);
}

QObject *CsaObject::getClass()
{
    CsaLocatedElement* pClass = nullptr;
    CsaFactory* pFactory = getFactory();

    if (CHKPTR(pFactory))
    {
        pClass = pFactory->createScriptObject(getInternals()->GetClass());
    }

    return pClass;
}


void CsaObject::setFactory(CsaFactory* p_pFactory)
{
    CsaLocatedElement::setFactory(p_pFactory);

    QMap<QString, CsaValue*>::iterator qmIt = m_qmValues.begin();
    QMap<QString, CsaValue*>::iterator qmItEnd = m_qmValues.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        qmIt.value()->setFactory(p_pFactory);
    }
}

void CsaObject::updateValues(QVariantMap& p_qvm)
{
   CdmObject* pCdmObject = getInternals();

   if(CHKPTR(pCdmObject))
   {
      if (p_qvm.contains(WMS_VALUES))
      {
         QVariantMap qvValues = p_qvm[WMS_VALUES].toMap();

         QVariantMap::iterator qvmIt = qvValues.begin();
         QVariantMap::iterator qvmItEnd = qvValues.end();

         for (; qvmIt != qvmItEnd; ++qvmIt)
         {
             if (m_qmValues.contains(qvmIt.key()))
             {
                CsaValue* pValue = m_qmValues[qvmIt.key()];
                if (CHKPTR(pValue))
                {
                    if (pValue->hasCurrentUserWriteAccess())
                    {
                        QVariantMap qvmValue = qvmIt.value().toMap();
                        pCdmObject->SetValue(qvmIt.key(), qvmValue[WMS_VALUE]);
                    }
                    else
                    {
                        ERR("Insufficient privileges to edit value " + qvmIt.key());
                    }
                }
             }
         }
      }
   }
}
