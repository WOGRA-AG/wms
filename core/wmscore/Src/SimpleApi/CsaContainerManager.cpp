// System and QT Includes
#include <QString>

// WMS Entities Includes
#include "wmsdefines.h"

// own Includes
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CsaFactory.h"
#include "CsaClass.h"
#include "CsaClassManager.h"
#include "CsaObjectContainer.h"
#include "CsaContainerManager.h"

CsaContainerManager::CsaContainerManager(CdmContainerManager* p_pContainerManager)
: CsaLocatedElement(),
  m_pContainerManager(p_pContainerManager)
{
    setElement(p_pContainerManager);
}

CsaContainerManager::~CsaContainerManager()
{
}

QObject* CsaContainerManager::createContainer(CsaClass *p_pClass)
{
    QString qstrKeyname = createNewKeyname();
    return createContainer(qstrKeyname, p_pClass);
}

QObject* CsaContainerManager::findContainerById(int p_iId)
{
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(getInternals()->FindContainerById(p_iId));
}

QObject* CsaContainerManager::findContainerByKeyname(QString p_qstrKeyname)
{
    CdmContainerManager* pContainerManager = getInternals();

    if (CHKPTR(pContainerManager))
    {
        return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(getInternals()->FindContainerByKeyname(p_qstrKeyname));
    }

    return nullptr;
}

QObject* CsaContainerManager::findEmptyContainerById(int p_iId)
{
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(getInternals()->FindEmptyContainerById(p_iId));
}

QObject* CsaContainerManager::findEmptyContainerByKeyname(QString p_qstrKeyname)
{
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(getInternals()->FindEmptyContainerByKeyname(p_qstrKeyname));
}

QObject* CsaContainerManager::createContainer(QString p_qstrClassKeyname)
{
    QString qstrKeyname = createNewKeyname();
    return createContainer(qstrKeyname, p_qstrClassKeyname);
}

QString CsaContainerManager::createNewKeyname()
{
    return "Container" + QString::number(getInternals()->GetUserId()) + "_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmsszzz");
}

QObject* CsaContainerManager::createContainer(QString p_qstrKeyname, QString p_qstrClassKeyname)
{
    QObject * pContainer = nullptr;
    CsaClass* pClass = static_cast<CsaClass*>(static_cast<CsaClassManager*>(getClassManager())->findClass(p_qstrClassKeyname));

    if (CHKPTR(pClass))
    {
        CdmClass* pdmClass = pClass->getInternals();
        if (CHKPTR(pdmClass))
        {
            if(getInternals()->CreateContainer(pdmClass, p_qstrKeyname) > 0)
            {
                CdmObjectContainer* pInternalContainer = getInternals()->FindContainerByKeyname(p_qstrKeyname);
                pContainer = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pInternalContainer);
            }
        }
    }
    else
    {
        QString qstrError = "Class with name " + p_qstrClassKeyname + " not found. Can not create container.";
        dynamic_cast<CsaFactory*> (getFactory())->throwError(qstrError);

    }

    return pContainer;
}

QObject* CsaContainerManager::createContainer(QString p_qstrKeyname, CsaClass *p_pClass)
{
    QObject* pContainer = nullptr;
    CdmClass* pClass = p_pClass->getInternals();

    if (CHKPTR(pClass))
    {
        if (getInternals()->CreateContainer(pClass, p_qstrKeyname) > 0)
        {
            CdmObjectContainer* pInternalContainer = getInternals()->FindContainerByKeyname(p_qstrKeyname);
            pContainer = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pInternalContainer);
        }
    }

    return pContainer;
}

QObject* CsaContainerManager::copyContainer(CsaObjectContainer *p_pContainer, bool p_bComplete)
{
    QObject* pContainer = nullptr;
    CdmObjectContainer* pInternalContainer = getInternals()->CopyContainer(p_pContainer->getInternals(), p_bComplete);

    if (CHKPTR(pInternalContainer))
    {
        pContainer = dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pInternalContainer);
    }

    return pContainer;
}

QVariantList CsaContainerManager::getContainerList(QString p_qstrClassName)
{
    QList<QString> qllContainers = getInternals()->GetContainerList(p_qstrClassName);
    QVariantList qlContainers;

    QList<QString>::iterator qllIt = qllContainers.begin();
    QList<QString>::iterator qllItEnd = qllContainers.end();

    for(; qllIt != qllItEnd; ++qllIt)
    {
        qlContainers.append(*qllIt);
    }

    return qlContainers;
}

QObject* CsaContainerManager::reloadContainerComplete(CsaObjectContainer *p_pContainer)
{
    CdmObjectContainer* pContainer = p_pContainer->getInternals();
    getInternals()->ReloadContainerComplete(pContainer);
    return dynamic_cast<CsaFactory*> (getFactory())->createScriptObject(pContainer);
}

void CsaContainerManager::removeContainerLocal(CsaObjectContainer *p_pContainer)
{
    getInternals()->RemoveContainerLocally(p_pContainer->getKeyname());
}

void CsaContainerManager::deleteContainer(CsaObjectContainer *p_pContainer)
{
    getInternals()->DeleteContainer(p_pContainer->getInternals());
}

CdmContainerManager *CsaContainerManager::getInternals()
{
    return m_pContainerManager;
}


QVariant CsaContainerManager::getDetailedVariant()
{
    QVariantMap qvm;
    qvm.insert(WMS_NAME, WMS_CONTAINERMANAGER);
    return qvm;
}



