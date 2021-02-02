/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and Qt Includes

// WMS Commons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmQueryEnhanced.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaObject.h"
#include "CsaModelElement.h"
#include "CsaObjectContainer.h"
#include "CsaFactory.h"
#include "CsaQuery.h"


CsaQuery::CsaQuery()
: m_pQuery(nullptr)
{
   m_pQuery = new CdmQueryEnhanced(this);
   m_pQuery->setParent(this);
}

CsaQuery::~CsaQuery()
{
   DELPTR(m_pQuery);
}

CdmQuery* CsaQuery::getInternals()
{
   return m_pQuery;
}

bool CsaQuery::containsGrouping()
{
   return m_pQuery->ContainsGrouping();
}

CsaObject* CsaQuery::getObjectAt(int p_iIndex)
{
   CsaObject* pObject = nullptr;
   CdmObject* pObjectInternal = m_pQuery->GetObjectAt(p_iIndex);

   if (pObjectInternal)
   {
      CsaFactory* pFactory = getFactory();

      if (CHKPTR(pFactory))
      {
         pObject = static_cast<CsaObject*>(pFactory->createScriptObject(pObjectInternal));
      }
   }

   return pObject;
}

long CsaQuery::getObjectIdAt(int p_iIndex)
{
   return m_pQuery->GetObjectIdAt(p_iIndex);
}

QString CsaQuery::getResultAsStringAt(int p_iIndex)
{
   return m_pQuery->GetResultAsStringAt(p_iIndex);
}

QVariant CsaQuery::getResultAt(QModelIndex& p_index)
{
   return m_pQuery->GetResultAt(p_index);
}

QVariant CsaQuery::getResultAt(QString p_qstrKeyname, int p_iPos)
{
   return m_pQuery->GetResultAt(p_qstrKeyname, p_iPos);
}

QVariant CsaQuery::getResultAt(int p_iColumn, int p_iRow)
{
   return m_pQuery->GetResultAt(p_iColumn, p_iRow);
}


int CsaQuery::getRowPosOfObjectInResultTree(long p_lObjectId)
{
   return m_pQuery->GetRowPosOfObjectInResultTree(p_lObjectId);
}

bool CsaQuery::isObjectInResultTree(long p_lObejctId)
{
   return m_pQuery->IsObjectInResultTree(p_lObejctId);
}

void CsaQuery::addGroupByElement(QString p_qstrElement)
{
    m_pQuery->AddGroupByElement(p_qstrElement);
}

CsaObject* CsaQuery::getFirstResultObject()
{
   CsaObject* pObject = nullptr;
   CdmObject* pObjectInternal = m_pQuery->GetObjectAt(0);

   if (pObjectInternal)
   {
      CsaFactory* pFactory = getFactory();

      if (CHKPTR(pFactory))
      {
         pObject = static_cast<CsaObject*>(pFactory->createScriptObject(pObjectInternal));
      }
   }

   return pObject;
}

QString CsaQuery::getSchemeName()
{
   return m_pQuery->GetScheme();
}

int CsaQuery::execute()
{
   return m_pQuery->Execute();
}

void CsaQuery::setContainer(CsaObjectContainer* p_pContainer)
{
   m_pQuery->SetContainer(p_pContainer->getInternals());
}

void CsaQuery::clear()
{
   m_pQuery->Clear();
}

CsaObjectContainer* CsaQuery::getContainer()
{
   CsaObjectContainer* pContainer = nullptr;
   CdmObjectContainer* pContainerInternal = m_pQuery->GetContainer();

   if (pContainerInternal)
   {
      CsaFactory* pFactory = getFactory();

      if (CHKPTR(pFactory))
      {
         pContainer = static_cast<CsaObjectContainer*>(pFactory->createScriptObject(pContainerInternal));
      }
   }

   return pContainer;
}

void CsaQuery::setContainerId(long p_lId, QString p_qstrScheme)
{
   m_pQuery->SetContainerId(p_lId, p_qstrScheme);
}

const QVariantList CsaQuery::getResultList()
{
    QVariantList qvResults;
    QLinkedList<long> qllResults = m_pQuery->GetResultList();
    QLinkedListIterator<long> qllIt(qllResults);

    while (qllIt.hasNext())
    {
        qvResults.append((int)qllIt.next());
    }

    return qvResults;
}

bool CsaQuery::containsResultObject(CsaObject* p_pObject)
{
   bool bRet = false;

   if (CHKPTR(p_pObject))
   {
      bRet = m_pQuery->ContainsResultObject(p_pObject->getInternals()->GetId());
   }

   return bRet;
}

bool CsaQuery::containsResultObject(long p_lObjectId)
{
   return m_pQuery->ContainsResultObject(p_lObjectId);
}

int CsaQuery::getResultCount()
{
   return m_pQuery->GetResultCount();
}

int CsaQuery::getColumnCount()
{
   return m_pQuery->GetColumnCount();
}

QString CsaQuery::getKeynameAt(int p_iSection)
{
   return m_pQuery->GetKeynameAt(p_iSection);
}

QVector<QString> CsaQuery::getResultElements()
{
   return m_pQuery->GetResultElements();
}

void CsaQuery::setQuery(CdmQuery* p_pEnhanced)
{
    m_pQuery = p_pEnhanced;
}

QVariant CsaQuery::getDetailedVariant()
{
    if (m_pQuery->IsEnhancedQuery())
    {
      return dynamic_cast<CdmQueryEnhanced*>(m_pQuery)->GetResultElementsAsVariant();
    }
    else
    {
       return m_pQuery->GetResultsAsVariant().toList();
    }
}
