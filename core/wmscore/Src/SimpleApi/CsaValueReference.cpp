
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValueObjectRef.h"
#include "CdmValueContainerRef.h"
#include "CsaFactory.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CsaValueReference.h"

CsaValueReference::CsaValueReference(CdmValue* p_pRef)
    : m_rpValue(p_pRef)
{

}

CsaValueReference::~CsaValueReference()
{

}

QVariant CsaValueReference::getValueReference()
{
    return get();
}

QVariant CsaValueReference::get()
{
    QVariant qvValue;
    CdmValue* pCdmValue = getInternals();

    if (CHKPTR(pCdmValue))
    {
       // ToDo dependent on valuetype doing the right
       if (pCdmValue->GetValueType() == eDmValueObjectRef)
       {
           CdmObject* pObject = static_cast<CdmValueObjectRef*>(pCdmValue)->GetObject();

           if (pObject)
           {
               qvValue.setValue(getFactory()->createScriptObject(pObject));
           }
       }
       else if (pCdmValue->GetValueType() == eDmValueContainerRef)
       {
           CdmObjectContainer* pContainer = static_cast<CdmValueContainerRef*>(pCdmValue)->GetContainer();

           if (pContainer)
           {
               qvValue.setValue(getFactory()->createScriptObject(pContainer));
           }
       }
    }

    return qvValue;
}

void CsaValueReference::set(QObject* p_pObject)
{
    CdmValue* pValue = getInternals();

    if (CHKPTR(pValue))
    {
        if (pValue->GetValueType() == eDmValueObjectRef)
        {
            CsaObject* pObject = dynamic_cast<CsaObject*>(p_pObject);

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
           CsaObjectContainer* pContainer = dynamic_cast<CsaObjectContainer*>(p_pObject);

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

bool CsaValueReference::isReference()
{

    return true;
}

void CsaValueReference::setValueReference(QObject* p_pObject)
{
    set(p_pObject);
}

CdmValue* CsaValueReference::getInternals()
{
    return m_rpValue;
}


QVariant CsaValueReference::getDetailedVariant()
{
    QVariantMap qvm;
    qvm.insert("ERROR", "NOT IMPLEMENTED FOR THIS CsaValueReference!");
    return qvm;
}


