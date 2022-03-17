// System and QT Includes

#include "wmsdefines.h"

// own Includes
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CsaClass.h"
#include "CsaFactory.h"
#include "CsaClassManager.h"


CsaClassManager::CsaClassManager(CdmClassManager* p_pClassManager)
: CsaLocatedElement(),
  m_pClassManager(p_pClassManager)
{
    setElement(p_pClassManager);
}

CsaClassManager::~CsaClassManager()
{

}

QObject* CsaClassManager::findClass(QString p_qstrKeyname)
{
    CdmClass* pClass = getInternals()->FindClassByKeyname(p_qstrKeyname);
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pClass);
}

QVariantList CsaClassManager::getClassList()
{
    QVariantList qlClasses;
    QList<CdmClass*> qllClasses;
    getInternals()->GetClassList(qllClasses);

    QList<CdmClass*>::iterator qllIt = qllClasses.begin();
    QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

    CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

    if (CHKPTR(pFactory))
    {
        for(; qllIt != qllItEnd; ++qllIt)
        {
            CsaLocatedElement* pElement = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(*qllIt);

            if (pElement)
            {
                qlClasses.append(QVariant::fromValue(pElement));
            }
        }
    }


    return qlClasses;
}

bool CsaClassManager::existClass(QString p_qstrKeyname)
{
    return getInternals()->ExistClass(p_qstrKeyname);
}

CdmClassManager *CsaClassManager::getInternals()
{
    return m_pClassManager;
}



QVariant CsaClassManager::getDetailedVariant()
{
    QVariantMap qvm;
    CdmClassManager* pClassManager = getInternals();

    if (CHKPTR(pClassManager))
    {
        QList<CdmClass*> qllClasses;
        pClassManager->GetClassList(qllClasses);
        QList<CdmClass*>::iterator qllIt = qllClasses.begin();
        QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

        CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());
        QVariantList qvlClasses;

        if (CHKPTR(pFactory))
        {
            for(; qllIt != qllItEnd; ++qllIt)
            {
                CsaClass* pElement = dynamic_cast<CsaClass*> (dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(*qllIt));

                if (pElement)
                {
                    qvlClasses.append(pElement->getRoughVariant());
                }
            }
        }

        qvm.insert(WMS_CLASSMANAGER, qvlClasses);
    }

    return qvm;
}


