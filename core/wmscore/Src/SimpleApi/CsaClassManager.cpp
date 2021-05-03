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
    return getFactory()->createScriptObject(pClass);
}

QVariantList CsaClassManager::getClassList()
{
    QVariantList qlClasses;
    QList<CdmClass*> qllClasses;
    getInternals()->GetClassList(qllClasses);

    QList<CdmClass*>::iterator qllIt = qllClasses.begin();
    QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

    CsaFactory* pFactory = getFactory();

    if (CHKPTR(pFactory))
    {
        for(; qllIt != qllItEnd; ++qllIt)
        {
            CsaLocatedElement* pElement = getFactory()->createScriptObject(*qllIt);

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

        CsaFactory* pFactory = getFactory();
        QVariantList qvlClasses;

        if (CHKPTR(pFactory))
        {
            for(; qllIt != qllItEnd; ++qllIt)
            {
                CsaClass* pElement = dynamic_cast<CsaClass*> (getFactory()->createScriptObject(*qllIt));

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


