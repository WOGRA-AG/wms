/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmEnhancedQueryProxy.cpp
 ** Started Implementation: 2010/11/11
 ** Description:
 **
 ** This class implements the proxy for tableviews of enhanced queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QTimer>
#include <QApplication>
#include <CwmsTimeMeassurement.h>

// WMS Manager Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmObject.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmContainerAdaptor.h"
#include "CdmQueryEnhanced.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmQueryBuilder.h"
#include "CdmMember.h"
#include "CdmEnhancedQueryProxy.h"



/** +-=---------------------------------------------------------Di 3. Apr 13:19:56 2012-----------*
 * @method  CdmEnhancedQueryProxy::CdmEnhancedQueryProxy     // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 13:19:56 2012-----------*/
CdmEnhancedQueryProxy::CdmEnhancedQueryProxy()
: CdmQueryModel(),
  m_bOrderbyModeAsc(true)
{
}

/** +-=---------------------------------------------------------Di 3. Apr 13:20:09 2012-----------*
 * @method  CdmEnhancedQueryProxy::~CdmEnhancedQueryProxy    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmEnhancedQueryProxy                                        *
 *----------------last changed: --------------------------------Di 3. Apr 13:20:09 2012-----------*/
CdmEnhancedQueryProxy::~CdmEnhancedQueryProxy()
{
}

/** +-=---------------------------------------------------------Di 3. Apr 13:20:14 2012-----------*
 * @method  CdmEnhancedQueryProxy::ValueChanged              // protected, virtual                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 13:20:14 2012-----------*/
void CdmEnhancedQueryProxy::ValueChanged()
{
    UpdateSlot();
}

/** +-=---------------------------------------------------------Di 20. Nov 09:42:48 2012----------*
 * @method  CdmEnhancedQueryProxy::Execute                   // public, virtual, slots            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:42:48 2012----------*/
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
        QString qstrWql = CdmQueryBuilder::BuildString(pQuery);
        pQuery->SetContainer(GetContainer());
        pQuery->SetOrderBy(m_qstrOrderBy, m_bOrderbyModeAsc);
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

/** +-=---------------------------------------------------------Di 20. Nov 09:43:27 2012----------*
 * @method  CdmEnhancedQueryProxy::GetQuery                  // public, slots                     *
 * @return  CdmQueryEnhanced*                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:43:27 2012----------*/
CdmQuery* CdmEnhancedQueryProxy::GetQuery()
{
    return CdmQueryModel::GetQuery();
}

void CdmEnhancedQueryProxy::CreateQuery(CdmObjectContainer *p_pContainer)
{
    Q_UNUSED(p_pContainer)
    // must be implemented in derived classes
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:48:20 2012-----------*
 * @method  CdmEnhancedQueryProxy::GetDisplaySetV            // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  // the source objectlist             *
 * @param   QSet<long>& p_rqsResult                          // The list of objects or objectlists*
 *                                                           //  which can be used                *
 * @comment This is the abstract method which must be overwritten be the derived class. the       *
 *          gui components which uses proxies uses the list of results for displaying their       *
 *          contents.                                                                             *
 *----------------last changed: --------------------------------Mi 3. Okt 11:48:20 2012-----------*/
void CdmEnhancedQueryProxy::GetDisplaySetV(CdmObjectContainer* p_pContainer, QSet<long>& p_rqsResult)
{
   if(CHKPTR(p_pContainer))
   { 
      GetQuery()->Clear();
      GetQuery()->DeleteResultElements();
      CreateQuery(p_pContainer);
      Execute();
      const QList<long> qvlResult = GetQuery()->GetResultList();

      QList<long>::const_iterator qvlIt = qvlResult.begin();
      QList<long>::const_iterator qvlItEnd = qvlResult.end();

      for(; qvlIt != qvlItEnd; ++ qvlIt)
      {
         long lValue = (*qvlIt);
         p_rqsResult.insert(lValue);
      }

      GetQuery()->Clear();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:43:46 2012----------*
 * @method  CdmEnhancedQueryProxy::GetDisplaySet             // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  // the source objectlist             *
 * @param   QSet<long>& p_rqsResult                          // The list of objects or objectlists*
 *                                                           //  which can be used                *
 * @comment This is the abstract method which must be overwritten be the derived class. the       *
 *          gui components which uses proxies uses the list of results for displaying their       *
 *          contents.                                                                             *
 *----------------last changed: --------------------------------Di 20. Nov 09:43:46 2012----------*/
void CdmEnhancedQueryProxy::GetDisplaySet(CdmObjectContainer* p_pContainer, QSet<long>& p_rqsResult)
{
   GetDisplaySetV(p_pContainer, p_rqsResult);
}


/** +-=---------------------------------------------------------Di 20. Nov 09:43:53 2012----------*
 * @method  CdmEnhancedQueryProxy::GetFirstResult            // public, slots                     *
 * @return  int                                              //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:43:53 2012----------*/
int CdmEnhancedQueryProxy::GetFirstResult(CdmObjectContainer* p_pContainer)
{
   int iRet = 0;
   QList<long> qvlResults;
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

/** +-=---------------------------------------------------------Di 20. Nov 09:44:11 2012----------*
 * @method  CdmEnhancedQueryProxy::GetDisplayList            // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  // the source objectlist             *
 * @param   QList<long>& p_rqvlResults                 // The list of objects or objectlists*
 *                                                           //  which can be used                *
 * @comment This is the abstract method which must be overwritten be the derived class. the       *
 *          gui components which uses proxies uses the list of results for displaying their       *
 *          contents.                                                                             *
 *----------------last changed: --------------------------------Di 20. Nov 09:44:11 2012----------*/
void CdmEnhancedQueryProxy::GetDisplayList(CdmObjectContainer* p_pContainer,
                                           QList<long>& p_rqvlResults)
{

   GetDisplayListV(p_pContainer, p_rqvlResults);
}

/** +-=---------------------------------------------------------Mi 3. Okt 11:49:19 2012-----------*
 * @method  CdmEnhancedQueryProxy::GetDisplayListV           // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  // the source objectlist             *
 * @param   QList<long>& p_rqvlResults                 // The list of objects or objectlists*
 *                                                           //  which can be used                *
 * @comment This is the abstract method which must be overwritten be the derived class. the       *
 *          gui components which uses proxies uses the list of results for displaying their       *
 *          contents.                                                                             *
 *----------------last changed: --------------------------------Mi 3. Okt 11:49:19 2012-----------*/
void CdmEnhancedQueryProxy::GetDisplayListV(CdmObjectContainer* p_pContainer,
                                            QList<long>& p_rqvlResults)
{
   if(CHKPTR(p_pContainer))
   { 
      GetQuery()->Clear();
      GetQuery()->DeleteResultElements();
      CreateQuery(p_pContainer);
      Execute();
      const QList<long> qvlResult = GetQuery()->GetResultList();

      QList<long>::const_iterator qvlIt = qvlResult.begin();
      QList<long>::const_iterator qvlItEnd = qvlResult.end();

      for(; qvlIt != qvlItEnd; ++ qvlIt)
      {
         long lValue = (*qvlIt);
         p_rqvlResults.append(lValue);
      }

      GetQuery()->Clear();
   }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:44:26 2012----------*
 * @method  CdmEnhancedQueryProxy::IsInResult                // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:44:26 2012----------*/
bool CdmEnhancedQueryProxy::IsInResult(CdmObject* p_pCdmObject)
{
   return IsInResult(p_pCdmObject->GetId(), p_pCdmObject->GetObjectContainer());
}

/** +-=---------------------------------------------------------Di 20. Nov 09:44:34 2012----------*
 * @method  CdmEnhancedQueryProxy::IsInResult                // public, slots                     *
 * @return  bool                                             //                                   *
 * @param   long p_lObjectId                                 //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:44:34 2012----------*/
bool CdmEnhancedQueryProxy::IsInResult(long p_lObjectId, CdmObjectContainer* p_pContainer)
{

   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      QSet<long> qsObjects;
      GetDisplaySet(p_pContainer, qsObjects);

      if (qsObjects.contains(p_lObjectId))
      {
         bRet = true;
      }
   }

   return bRet;
}

void CdmEnhancedQueryProxy::ObjectCommitedEvent(long )
{
    ValueChanged();
}

/** +-=---------------------------------------------------------Mi 3. Okt 10:56:29 2012-----------*
 * @method  CdmEnhancedQueryProxy::UpdateSignal              // public, signals                   *
 * @return  void                                             //                                   *
 * @comment This signal will be emitted when the gui element needs an update.                     *
 *----------------last changed: --------------------------------Mi 3. Okt 10:56:29 2012-----------*/
