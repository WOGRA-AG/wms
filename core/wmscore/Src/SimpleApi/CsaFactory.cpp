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
#include <QCoreApplication>
#include <QScriptEngine>
#include <QScriptValue>

// own Includes
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmModelElement.h"
#include "CdmLocatedElement.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassMethod.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmMember.h"
#include "CdmValueContainerRef.h"
#include "CdmValue.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmValueObjectRef.h"
#include "CdmExecutor.h"
#include "IdmExecutorEngine.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CsaLocatedElement.h"
#include "CsaClass.h"
#include "CsaMember.h"
#include "CsaValue.h"
#include "CsaResultObject.h"
#include "CsaUser.h"
#include "CsaUserGroup.h"
#include "CsaQuery.h"
#include "CsaModelElement.h"
#include "CsaManager.h"
#include "CsaClassManager.h"
#include "CsaContainerManager.h"
#include "CsaScheme.h"
#include "CsaFunction.h"
#include "CsaFactory.h"

CsaFactory::CsaFactory()
    : QObject(nullptr),
      m_rpEngine(nullptr),
      m_pScheme(nullptr),
      m_pClassManager(nullptr),
      m_pContainerManager(nullptr),
      m_pManager(nullptr)

{

}

CsaFactory::CsaFactory(IdmExecutorEngine* p_pEngine)
    : QObject(nullptr),
      m_rpEngine(p_pEngine),
      m_pScheme(nullptr),
      m_pClassManager(nullptr),
      m_pContainerManager(nullptr),
      m_pManager(nullptr)
{

}

CsaFactory::~CsaFactory()
{
    collectGarbage();
}

CsaLocatedElement *CsaFactory::createThisScriptObject(CdmObject *p_pElement)
{
    CsaLocatedElement* pThis = nullptr;
    if (m_rpEngine)
    {
        pThis = createScriptObjectInternal(p_pElement, true);
        m_rpEngine->SetThis(static_cast<CsaObject*>(pThis));
    }

    return pThis;
}

void CsaFactory::createFormulaScriptObject(CdmObject *p_pCdmObject)
{
   if (CHKPTR(p_pCdmObject))
   {
       QMap<long, CdmMember*> qmValues;
       CdmClass* pClass = p_pCdmObject->GetClass();

       if (pClass)
       {
          pClass->GetMemberMap(qmValues);
       }

       QMap<long, CdmMember*>::iterator qmIt = qmValues.begin();
       QMap<long, CdmMember*>::iterator qmItEnd = qmValues.end();

       for (; qmIt != qmItEnd; ++qmIt)
       {
          CdmMember* pMember = qmIt.value();
          CdmValue* pCdmValue = nullptr;

          if (pMember)
          {
             pCdmValue = p_pCdmObject->GetValue(pMember->GetKeyname());

             if (pCdmValue)
             {
                m_rpEngine->SetProperty(pCdmValue);
             }
             else
             {
                 ERR("Value to Member " + pMember->GetKeyname() + " not found! can not add it to script engine!")
             }
          }
        }
    }
}

CsaResultObject* CsaFactory::createResultObject()
{
    return new CsaResultObject(this);
}


CsaLocatedElement* CsaFactory::createScriptObject(CdmLocatedElement* p_pElement)
{
    if (p_pElement)
    {
        return createScriptObjectInternal(p_pElement, false);
    }

    return nullptr;
}

CsaLocatedElement* CsaFactory::createScriptObjectInternal(CdmLocatedElement* p_pElement, bool p_bThis)
{
    CsaLocatedElement* pElement = nullptr;

    if (CHKPTR(p_pElement))
    {
        bool bNew = false;

        if (m_CollectorMap.contains(p_pElement->GetUriInternal()))
        {
            pElement = m_CollectorMap[p_pElement->GetUriInternal()];
        }
        else
        {
            bNew = true;

            if (p_pElement->IsClass())
            {
                pElement = new CsaClass(static_cast<CdmClass*>(p_pElement));
            }
            else if (p_pElement->IsContainer())
            {
                pElement = new CsaObjectContainer(static_cast<CdmObjectContainer*>(p_pElement));
            }
            else if (p_pElement->IsMember())
            {
                pElement = new CsaMember(static_cast<CdmMember*>(p_pElement));
            }
            else if (p_pElement->IsObject())
            {
                pElement = new CsaObject(static_cast<CdmObject*>(p_pElement), this, p_bThis);
            }
            else if (p_pElement->IsValue())
            {
                pElement = new CsaValue(static_cast<CdmValue*>(p_pElement));
            }
            else if (p_pElement->IsUser())
            {
                pElement = new CsaUser(static_cast<CumUser*>(p_pElement));
            }
            else if (p_pElement->IsUserGroup())
            {
                pElement = new CsaUserGroup(static_cast<CumUserGroup*>(p_pElement));
            }
            else if (p_pElement->IsMethod())
            {
                pElement = new CsaFunction(dynamic_cast<CdmClassMethod*>(p_pElement));
            }
            else if (p_pElement->IsScheme())
            {
                pElement = getScheme();
                bNew = false;
            }
            else if (p_pElement->IsContainerManager())
            {
                pElement = getContainerManager();
                bNew = false;
            }
            else if (p_pElement->IsClassManager())
            {
                pElement = getClassManager();
                bNew = false;
            }
            else if (p_pElement->IsDataProvider())
            {
                pElement = getManager();
                bNew = false;
            }

            if (CHKPTR(pElement))
            {
                pElement->setFactory(this);
            }
        }

        if (CHKPTR(pElement) && bNew)
        {
            m_CollectorMap.insert(p_pElement->GetUriInternal(), pElement);
        }
    }

    return pElement;
}
	

void CsaFactory::collectGarbage()
{
    INFO("Garbage Collector called!")
    QMap<QString, CsaLocatedElement*>::iterator qmItLoc = m_CollectorMap.begin();
    QMap<QString, CsaLocatedElement*>::iterator qmItEndLoc = m_CollectorMap.end();


    for (; qmItLoc != qmItEndLoc; ++qmItLoc)
    {
        CsaLocatedElement* pElement = qmItLoc.value();
        DELPTR(pElement)
    }

    for (int pos = 0; pos < m_qlGarbageColectionObjects.count(); ++pos)
    {
        DELPTR(m_qlGarbageColectionObjects[pos])
    }

    m_qlGarbageColectionObjects.clear();
    m_CollectorMap.clear();
    DELPTR(m_pManager)
    DELPTR(m_pClassManager)
    DELPTR(m_pContainerManager)
    DELPTR(m_pScheme)
    
}

void CsaFactory::addObjectForGarbageCollection(QObject* p_pObject)
{
    m_qlGarbageColectionObjects.append(p_pObject);
}

CsaContainerManager *CsaFactory::getContainerManager()
{
    if (!m_pContainerManager)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();
        m_pContainerManager = new CsaContainerManager(pContainerManager);
        m_pContainerManager->setFactory(this);
    }

    return m_pContainerManager;
}

CsaManager *CsaFactory::getManager()
{
    if (!m_pManager)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
        m_pManager = new CsaManager(pManager);
        m_pManager->setFactory(this);
    }

    return m_pManager;
}

void CsaFactory::throwError(QString p_qstrError)
{
    m_rpEngine->ThrowError(p_qstrError);
}

IdmExecutorEngine *CsaFactory::getEngine()
{
    return m_rpEngine;
}

void CsaFactory::setEngine(IdmExecutorEngine *p_pEngine)
{
    m_rpEngine = p_pEngine;
}


CsaClassManager *CsaFactory::getClassManager()
{
    if (!m_pClassManager)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
        CdmClassManager* pClassManager = pManager->GetClassManager();
        m_pClassManager = new CsaClassManager(pClassManager);
        m_pClassManager->setFactory(this);
    }

    return m_pClassManager;
}


CsaScheme *CsaFactory::getScheme()
{
    if (!m_pScheme)
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
        CdmScheme* pDatabase = pManager->GetCurrentScheme();

        if (pDatabase)
        {
            m_pScheme = new CsaScheme(pDatabase);
            m_pScheme->setFactory(this);
        }
    }

    return m_pScheme;
}

CsaQuery* CsaFactory::createQuery(QString p_qstrWQl)
{
   CsaQuery* pQuery = nullptr;
   CdmQueryEnhanced* pQueryInternal = static_cast<CdmQueryEnhanced*>(CdmQueryBuilder::BuildQuery(p_qstrWQl));

   if (CHKPTR(pQueryInternal))
   {
      pQuery = new CsaQuery();
      pQuery->setQuery(pQueryInternal);
      pQuery->setFactory(this);
   }

   return pQuery;
}

CsaQuery* CsaFactory::createQuery(CdmQuery* p_pQuery)
{
   CsaQuery* pQuery = nullptr;

   if (CHKPTR(p_pQuery))
   {
      pQuery = new CsaQuery();
      pQuery->setFactory(this);
      pQuery->setQuery(p_pQuery);
   }

   return pQuery;
}

CsaObject* CsaFactory::findObjectById(int pOlId, int pId)
{
   CsaObject* pObject = nullptr;
   QObject* pObjObjectContainer = getContainerManager()->findEmptyContainerById(pOlId);
   if(CHKPTR(pObjObjectContainer)){
       CsaObjectContainer* pObjectContainer = static_cast<CsaObjectContainer*> (pObjObjectContainer);
       if (CHKPTR(pObjectContainer)) {
           QObject* pObjObject = pObjectContainer->findObjectById(pId);
           if(CHKPTR(pObjObject)){
             pObject = static_cast<CsaObject*> (pObjObject);
           }
       }
   }
   return pObject;
}

CsaObjectContainer* CsaFactory::convertContainer(CdmObjectContainer* p_pContainer, CsaFactory* p_pFactory)
{
    CsaObjectContainer* pContainer = nullptr;

    if (p_pContainer)
    {
        if (CHKPTR(p_pFactory))
        {
            pContainer = static_cast<CsaObjectContainer*>(p_pFactory->createScriptObject(p_pContainer));
        }
    }

    return pContainer;
}

CsaObject* CsaFactory::convertObject(CdmObject* p_pObject, CsaFactory* p_pFactory)
{
    CsaObject* pObject = nullptr;

    if (p_pObject)
    {
        if (CHKPTR(p_pFactory))
        {
            pObject = static_cast<CsaObject*>(p_pFactory->createScriptObject(p_pObject));
        }
    }

    return pObject;
}

QVariant CsaFactory::convertToResultVariantForSubMethodCalls(const QVariant& p_rQVariant)
{
    QVariant p_pQVariantResult;
    if(p_rQVariant.canConvert(QMetaType::QVariantList)){
        QVariantList qvl = p_rQVariant.toList();
        for(int i=0; i<qvl.length(); i++){
            qvl[i] = convertToResultVariant(qvl[i]);
        }
        p_pQVariantResult = qvl;
    }else if(p_rQVariant.canConvert(QMetaType::QVariantMap)){
        QVariantMap qvm = p_rQVariant.toMap();
        QMapIterator<QString, QVariant> i(qvm);
        while (i.hasNext()) {
            i.next();
            QVariant converted = convertToResultVariant(i.value());
            qvm.insert(i.key(), converted);
        }
        p_pQVariantResult = qvm;
    } else {
        p_pQVariantResult = p_rQVariant;
    }
    return p_pQVariantResult;
}

QVariant CsaFactory::convertToResultVariant(const QVariant& p_rQVariant)
{
    QVariant p_pQVariantResult;
    if(p_rQVariant.canConvert(QMetaType::QVariantList)){
        QVariantList qvl = p_rQVariant.toList();
        for(int i=0; i<qvl.length(); i++){
            qvl[i] = convertToResultVariant(qvl[i]);
        }
        p_pQVariantResult = qvl;
    }else if(p_rQVariant.canConvert(QMetaType::QVariantMap)){
        QVariantMap qvm = p_rQVariant.toMap();
        QMapIterator<QString, QVariant> i(qvm);
        while (i.hasNext()) {
            i.next();
            QVariant converted = convertToResultVariant(i.value());
            qvm.insert(i.key(), converted);
        }
        p_pQVariantResult = qvm;
    }else if (p_rQVariant.canConvert(QMetaType::QObjectStar)){
        QObject* qObj = qvariant_cast<QObject*>(p_rQVariant);
        try
        {
            CsaLocatedElement* csaLocatedElement = dynamic_cast<CsaLocatedElement*> (qObj);
            if(CHKPTR(csaLocatedElement) && !csaLocatedElement->getUri().isEmpty())
            {
                if(csaLocatedElement->isContainer())
                {
                    CsaObjectContainer* pConatiner = static_cast<CsaObjectContainer*> (csaLocatedElement);
                    p_pQVariantResult = pConatiner->getDetailedVariant();
                }
                else if(csaLocatedElement->isObject())
                {
                    CsaObject* pConatiner = static_cast<CsaObject*> (csaLocatedElement);
                    p_pQVariantResult = pConatiner->getDetailedVariant();
                }
                else
                {
                    CdmLocatedElement* pLocatedElement = csaLocatedElement->getElement();
                    if(CHKPTR(pLocatedElement))
                    {
                        p_pQVariantResult = pLocatedElement->GetVariant();
                    }
                }
            }
            else
            {
                p_pQVariantResult = p_rQVariant;
            }
        }
        catch(...)
        {
            p_pQVariantResult = p_rQVariant;
        }
    }else if(p_rQVariant.type() == QVariant::DateTime) {
        QDateTime qvdt = p_rQVariant.toDateTime();
        p_pQVariantResult = qvdt.toUTC();
    }else {
        p_pQVariantResult = p_rQVariant;
    }
    return p_pQVariantResult;
}



CsaFactory* CsaFactory::getCurrentFunctionFactory()
{
   CsaFactory* pFactory = nullptr;
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmExecutor* pExecutor = pManager->GetExecutor();
      if (CHKPTR(pExecutor))
      {
         CdmExecutorFunction* pFunction = pExecutor->GetFunction();

         if (CHKPTR(pFunction))
         {
            pFactory = pFunction->GetFactory();
         }
      }
   }

   return pFactory;
}


QStringList CsaFactory::getArguments()
{
    return qApp->arguments();
}
