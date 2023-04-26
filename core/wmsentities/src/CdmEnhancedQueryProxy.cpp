// System and QT Includes
#include <QTimer>
#include <QApplication>
#include <CwmsTimeMeassurement.h>

// WMS Manager Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQueryBuilder.h"
#include "CdmEnhancedQueryProxy.h"

CdmEnhancedQueryProxy::CdmEnhancedQueryProxy()
: CdmQueryModel(),
  m_bOrderbyModeAsc(true)
{
}

CdmEnhancedQueryProxy::~CdmEnhancedQueryProxy()
{
}

void CdmEnhancedQueryProxy::ValueChanged()
{
    UpdateSlot();
}

void CdmEnhancedQueryProxy::Execute()
{
    CdmQuery* pQuery = CdmQueryModel::GetQuery();

    if (pQuery != nullptr)
    {
        if (m_qstrOrderBy.isEmpty())
        {
            m_qstrOrderBy = pQuery->GetOrderBy();
            m_bOrderbyModeAsc = pQuery->GetOrderMode();
        }

        pQuery->Clear();
    }

    CreateQuery(GetContainer());
    pQuery = CdmQueryModel::GetQuery();

    if (pQuery != nullptr)
    {
        pQuery->SetContainer(GetContainer());
        pQuery->SetOrderBy(m_qstrOrderBy, m_bOrderbyModeAsc);
        QString qstrWql = CdmQueryBuilder::BuildString(pQuery);
        CdmQueryModel::Execute();
    }
}

void CdmEnhancedQueryProxy::sort(int p_iColumn, Qt::SortOrder p_eSortOrder)
{
    if (CHKPTR(m_pCdmQuery))
    {
        m_qstrOrderBy.clear();

        if (!m_pCdmQuery->IsValid())
        {
            CreateQuery(GetContainer());
        }

        QString qstrColKeyname(m_pCdmQuery->GetKeynameAt(p_iColumn));

        if (!qstrColKeyname.isEmpty())
        {
            m_qstrOrderBy.append(qstrColKeyname);
        }

        if (p_eSortOrder == Qt::AscendingOrder)
        {
            m_bOrderbyModeAsc = true;
        }
        else
        {
            m_bOrderbyModeAsc = false;
        }

        CdmQueryModel::sort(p_iColumn, p_eSortOrder);
    }
}

QStringList CdmEnhancedQueryProxy::GetOrderBy()
{
    return m_qstrOrderBy;
}

void CdmEnhancedQueryProxy::ClearOrderBy()
{
    m_qstrOrderBy.clear();
}

void CdmEnhancedQueryProxy::AddOrderBy(QString p_qstrOrderBy)
{
    m_qstrOrderBy.append(p_qstrOrderBy);
}

void CdmEnhancedQueryProxy::SetOrderByMode(bool p_bAsc)
{
    m_bOrderbyModeAsc = p_bAsc;
}

bool CdmEnhancedQueryProxy::GetOrderByMode()
{
    return m_bOrderbyModeAsc;
}

void CdmEnhancedQueryProxy::GetDisplaySetV(CdmObjectContainer* p_pContainer, QSet<qint64>& p_rqsResult)
{
   if(CHKPTR(p_pContainer))
   { 
      GetQuery()->Clear();
      GetQuery()->DeleteResultElements();
      CreateQuery(p_pContainer);
      Execute();
      const QList<qint64> qvlResult = GetQuery()->GetResultList();

      QList<qint64>::const_iterator qvlIt = qvlResult.begin();
      QList<qint64>::const_iterator qvlItEnd = qvlResult.end();

      for(; qvlIt != qvlItEnd; ++ qvlIt)
      {
        qint64 lValue = (*qvlIt);
         p_rqsResult.insert(lValue);
      }

      GetQuery()->Clear();
   }
}

void CdmEnhancedQueryProxy::GetDisplaySet(CdmObjectContainer* p_pContainer, QSet<qint64>& p_rqsResult)
{
   GetDisplaySetV(p_pContainer, p_rqsResult);
}

int CdmEnhancedQueryProxy::GetFirstResult(CdmObjectContainer* p_pContainer)
{
   int iRet = 0;
   QList<qint64> qvlResults;
   GetDisplayListV(p_pContainer, qvlResults);

   if (qvlResults.count() == 1)
   {
      iRet = (*qvlResults.begin());
   }
   else if (qvlResults.count() > 1)
   {
      iRet = (*qvlResults.begin());
      WARNING("More then one result found!")
   }

   return iRet;
}

void CdmEnhancedQueryProxy::GetDisplayList(CdmObjectContainer* p_pContainer,
                                           QList<qint64>& p_rqvlResults)
{
   GetDisplayListV(p_pContainer, p_rqvlResults);
}

void CdmEnhancedQueryProxy::GetDisplayListV(CdmObjectContainer* p_pContainer,
                                            QList<qint64>& p_rqvlResults)
{
   if(CHKPTR(p_pContainer))
   { 
      GetQuery()->Clear();
      GetQuery()->DeleteResultElements();
      CreateQuery(p_pContainer);
      Execute();
      const QList<qint64> qvlResult = GetQuery()->GetResultList();

      QList<qint64>::const_iterator qvlIt = qvlResult.begin();
      QList<qint64>::const_iterator qvlItEnd = qvlResult.end();

      for(; qvlIt != qvlItEnd; ++ qvlIt)
      {
        qint64 lValue = (*qvlIt);
         p_rqvlResults.append(lValue);
      }

      GetQuery()->Clear();
   }
}

bool CdmEnhancedQueryProxy::IsInResult(CdmObject* p_pCdmObject)
{
   return IsInResult(p_pCdmObject->GetId(), p_pCdmObject->GetObjectContainer());
}

bool CdmEnhancedQueryProxy::IsInResult(qint64 p_lObjectId, CdmObjectContainer* p_pContainer)
{

   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      QSet<qint64> qsObjects;
      GetDisplaySet(p_pContainer, qsObjects);

      if (qsObjects.contains(p_lObjectId))
      {
         bRet = true;
      }
   }

   return bRet;
}

void CdmEnhancedQueryProxy::ObjectCommitedEvent(qint64)
{
    ValueChanged();
}
