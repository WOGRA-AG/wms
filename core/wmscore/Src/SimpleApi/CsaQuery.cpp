// System and Qt Includes

// own Includes
#include "CdmQuery.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaObject.h"
#include "CsaClass.h"
#include "CsaObjectContainer.h"
#include "CsaFactory.h"
#include "CsaQuery.h"


CsaQuery::CsaQuery()
: m_pQuery(nullptr)
{
   m_pQuery = new CdmQuery(this);
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

QObject *CsaQuery::getObjectAt(int p_iIndex)
{
   CsaObject* pObject = nullptr;
   CdmObject* pObjectInternal = m_pQuery->GetObjectAt(p_iIndex);

   if (pObjectInternal)
   {
      CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

      if (CHKPTR(pFactory))
      {
         pObject = static_cast<CsaObject*>(pFactory->createScriptObject(pObjectInternal));
      }
   }

   return pObject;
}

qint64 CsaQuery::getObjectIdAt(int p_iIndex)
{
   return m_pQuery->GetObjectIdAt(p_iIndex);
}

QString CsaQuery::getResultAsStringAt(int p_iIndex)
{
   return m_pQuery->GetResultAsStringAt(p_iIndex);
}

QString CsaQuery::getResultAsDisplayStringAt(int p_iColumn, int p_iRow)
{
   return m_pQuery->GetResultAsDisplayStringAt(p_iColumn, p_iRow);
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


int CsaQuery::getRowPosOfObjectInResultTree(qint64 p_lObjectId)
{
   return m_pQuery->GetRowPosOfObjectInResultTree(p_lObjectId);
}

bool CsaQuery::isObjectInResultTree(qint64 p_lObejctId)
{
   return m_pQuery->IsObjectInResultTree(p_lObejctId);
}

void CsaQuery::addGroupByElement(QString p_qstrElement)
{
    m_pQuery->AddGroupByElement(p_qstrElement);
}

QObject* CsaQuery::getFirstResultObject()
{
   CsaObject* pObject = nullptr;
   CdmObject* pObjectInternal = m_pQuery->GetObjectAt(0);

   if (pObjectInternal)
   {
      CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

      if (CHKPTR(pFactory))
      {
         pObject = static_cast<CsaObject*>(pFactory->createScriptObject(pObjectInternal));
      }
   }

   return pObject;
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

QObject *CsaQuery::getContainer()
{
   CsaObjectContainer* pContainer = nullptr;
   CdmObjectContainer* pContainerInternal = m_pQuery->GetContainer();

   if (pContainerInternal)
   {
      CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

      if (CHKPTR(pFactory))
      {
         pContainer = static_cast<CsaObjectContainer*>(pFactory->createScriptObject(pContainerInternal));
      }
   }

   return pContainer;
}

QObject *CsaQuery::getClass()
{
    CsaClass* pClass = nullptr;

    CdmClass* pClassInternal = const_cast<CdmClass*>(m_pQuery->GetClass());
    CsaFactory* pFactory = dynamic_cast<CsaFactory*> (getFactory());

    if (pClassInternal)
    {
        pClass = static_cast<CsaClass*>(pFactory->createScriptObject(pClassInternal));
    }


    return pClass;
}

void CsaQuery::setContainerId(qint64 p_lId)
{
   m_pQuery->SetContainerId(p_lId);
}

const QVariantList CsaQuery::getResultList()
{
    QVariantList qvResults;
    QList<qint64> qllResults = m_pQuery->GetResultList();
    QListIterator<qint64> qllIt(qllResults);

    while (qllIt.hasNext())
    {
        qvResults.append(qllIt.next());
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

bool CsaQuery::containsResultObject(qint64 p_lObjectId)
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

QString CsaQuery::getCaptionAt(int p_iSection)
{
   QString qstrKeyname = m_pQuery->GetKeynameAt(p_iSection);
   CdmClass* pClass = const_cast<CdmClass*>(m_pQuery->GetClass());

   if (CHKPTR(pClass) && !qstrKeyname.isEmpty())
   {
       const CdmMember *pMember = pClass->FindMember(qstrKeyname);

       if (CHKPTR(pMember))
       {
           return pMember->GetCaption();
       }
   }

   return "";
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
    if (m_pQuery->HasResultElements())
    {
      return m_pQuery->GetResultElementsAsVariant();
    }
    else
    {
       return m_pQuery->GetResultsAsVariant().toList();
    }
}
