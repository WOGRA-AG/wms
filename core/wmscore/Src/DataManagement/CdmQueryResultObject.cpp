/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmQueryResultObject.cpp
 ** Started Implementation: 2012/10/14
 ** Description:
 **
 ** implements the result object of an query
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Commons Includes
#include "wmsdefines.h"

// own Includes
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmClass.h"
#include "CdmQuery.h"
#include "CdmLogging.h"
#include "CdmQueryResultObject.h"


/** +-=---------------------------------------------------------Mo 15. Okt 08:44:50 2012----------*
 * @method  CdmQueryResultObject::CdmQueryResultObject       // public                            *
 * @return                                                   //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   CdmQueryResultObject* p_pParent                  //                                   *
 * @param   CdmQuery* p_pQuery                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 15. Okt 08:44:50 2012----------*/
CdmQueryResultObject::CdmQueryResultObject(qint64 p_lObjectId,
                                          qint64 p_lContainerId,
                                           CdmQueryResultObject* p_pParent,
                                           CdmQuery* p_pQuery)
: m_rpCdmQuery(p_pQuery),
  m_lObjectId(p_lObjectId),
  m_lContainerId(p_lContainerId),
  m_pParent(p_pParent),
  m_iRow(-1)
{
    if (m_pParent)
    {
        m_iRow = m_pParent->GetRowCount();
        m_pParent->AddChildren(this);
    }
}

/** +-=---------------------------------------------------------So 14. Okt 14:38:50 2012----------*
 * @method  CdmQueryResultObject::~CdmQueryResultObject      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmQueryResultObject                                          *
 *----------------last changed: --------------------------------So 14. Okt 14:38:50 2012----------*/
CdmQueryResultObject::~CdmQueryResultObject()
{
    ClearResults();
}

/** +-=---------------------------------------------------------So 10. Feb 10:16:30 2013----------*
 * @method  CdmQueryResultObject::GetRow                     // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:16:30 2013----------*/
int CdmQueryResultObject::GetRow() const
{
   return m_iRow;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:40:53 2012----------*
 * @method  CdmQueryResultObject::ClearResults               // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:40:53 2012----------*/
void CdmQueryResultObject::ClearResults()
{
   m_qmResultValues.clear();
   QMapIterator<qint64, CdmQueryResultObject*> qmIt(m_qmChildrenByObject);

   while (qmIt.hasNext())
   {
      qmIt.next();
      CdmQueryResultObject* p = qmIt.value();
      DELPTR(p);
   }

   m_qmChildrenByObject.clear();
   m_qmChildrenByRow.clear();
}

/** +-=---------------------------------------------------------Di 20. Nov 11:41:01 2012----------*
 * @method  CdmQueryResultObject::AddChildren                // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmQueryResultObject* p_pChild                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:41:01 2012----------*/
void CdmQueryResultObject::AddChildren(CdmQueryResultObject* p_pChild)
{
    if (CHKPTR(p_pChild))
    {
        int iRows = GetRowCount();
        m_qmChildrenByObject.insert(p_pChild->GetObjectId(), p_pChild);
        m_qmChildrenByRow.insert(iRows, p_pChild);
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 11:41:10 2012----------*
 * @method  CdmQueryResultObject::GetParent                  // public, slots                     *
 * @return  CdmQueryResultObject*                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:41:10 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::GetParent()
{
   return m_pParent;
}


/** +-=---------------------------------------------------------Di 20. Nov 11:41:17 2012----------*
 * @method  CdmQueryResultObject::GetObjectParentId          // public, slots                     *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:41:17 2012----------*/
qint64 CdmQueryResultObject::GetObjectParentId()
{
   return CdmQueryResultObject::GetObjectParentId(m_lObjectId, m_lContainerId, m_rpCdmQuery);
}

/** +-=---------------------------------------------------------Di 20. Nov 11:41:42 2012----------*
 * @method  CdmQueryResultObject::GetResultAt                // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   int p_iPos                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:41:42 2012----------*/
QVariant CdmQueryResultObject::GetResultAt(int p_iPos)
{
   QVariant qvResult;

   try
   {
      if (m_qmResultValues.contains(p_iPos))
      {
         qvResult = m_qmResultValues[p_iPos];
      }
      else if (p_iPos == 0)
      {
          qvResult = QString ("ObjectId %1 ContainerId %2").arg(m_lObjectId).arg(m_lContainerId);
      }
   }
   catch(...)
   {
      ERR("Something went wrong here");
      qvResult = QVariant();
   }

   return qvResult;
}

QString CdmQueryResultObject::GetResultAsString()
{
    QString qstrResult;
    const CdmClass* pClass = m_rpCdmQuery->GetClass();

    if (CHKPTR(pClass))
    {
        QMap<int, QVariant>::iterator qmIt = m_qmResultValues.begin();
        QMap<int, QVariant>::iterator qmItEnd = m_qmResultValues.end();
        QLocale qLocale;

        for (; qmIt != qmItEnd; ++qmIt)
        {
            QString qstrCaption;
            QString qstrResultValue;
            QVariant qvResult = qmIt.value().toString();
            CdmQueryResultElement* pElement = m_rpCdmQuery->GetResultElement(qmIt.key());

            if (CHKPTR(pElement))
            {
                QString qstrKeyname = pElement->GetKeyname();

                const CdmMember* pMember = pClass->FindMember(qstrKeyname);

                if (CHKPTR(pMember))
                {
                    qstrCaption = pMember->GetCaption();
                    qstrResultValue = pMember->ConvertValueToDisplayString(qvResult);
                }
            }

            qstrResult += "<b>" + qstrCaption + ":</b> " + qstrResultValue + "<br />";
        }
    }


    return qstrResult;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:41:52 2012----------*
 * @method  CdmQueryResultObject::AddResult                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @param   QVariant qvResult                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:41:52 2012----------*/
void CdmQueryResultObject::AddResult(int p_iColumn, QVariant qvResult)
{
   m_qmResultValues.insert(p_iColumn, qvResult);
}

/** +-=---------------------------------------------------------Di 20. Nov 11:42:02 2012----------*
 * @method  CdmQueryResultObject::GetChild                   // public, slots                     *
 * @return  CdmQueryResultObject*                            //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:42:02 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::GetChild(qint64 p_lObjectId)
{
   CdmQueryResultObject* pRet = nullptr;

   if (m_qmChildrenByObject.contains(p_lObjectId))
   {
       pRet = m_qmChildrenByObject[p_lObjectId];
   }
   else
   {
       CdmObjectContainer* pContainer = m_rpCdmQuery->GetContainer();

       if (pContainer && pContainer->IsTree())
       {
           QMapIterator<qint64, CdmQueryResultObject*> qmIt(m_qmChildrenByObject);

           while (qmIt.hasNext())
           {
               qmIt.next();
               CdmQueryResultObject* p = qmIt.value();
               p = p->GetChild(p_lObjectId);

               if (p != nullptr)
               {
                   pRet = p;
                   break;
               }
           }
       }
   }

   return pRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:42:13 2012----------*
 * @method  CdmQueryResultObject::GetChildAtRow              // public, slots                     *
 * @return  CdmQueryResultObject*                            //                                   *
 * @param   int p_iRow                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:42:13 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::GetChildAtRow(int p_iRow)
{
   CdmQueryResultObject* pRet = nullptr;

   if (m_qmChildrenByRow.contains(p_iRow))
   {
      pRet = m_qmChildrenByRow[p_iRow];
   }
   
   return pRet;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:42:40 2012----------*
 * @method  CdmQueryResultObject::GetChildAtRow              // public, slots                     *
 * @return  CdmQueryResultObject*                            //                                   *
 * @param   int p_iRow                                       //                                   *
 * @param   int p_lParentId                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:42:40 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::GetChildAtRow(int p_iRow, int p_lParentId)
{
   CdmQueryResultObject* pResult = nullptr;
   CdmQueryResultObject* pParent = GetChild(p_lParentId);

   if (pParent)
   {
      pResult = pParent->GetChildAtRow(p_iRow);
   }
  

   return pResult;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:42:51 2012----------*
 * @method  CdmQueryResultObject::GetResult                  // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   int p_iRow                                       //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:42:51 2012----------*/
QVariant CdmQueryResultObject::GetResult(int p_iRow, int p_iColumn)
{
   QVariant qvResult;

   CdmQueryResultObject* pResult = GetChildAtRow(p_iRow);

   if (pResult)
   {
      qvResult = pResult->GetResultAt(p_iColumn);
   }

   return qvResult;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:43:01 2012----------*
 * @method  CdmQueryResultObject::GetResult                  // public, slots                     *
 * @return  QVariant                                         //                                   *
 * @param   int p_iRow                                       //                                   *
 * @param   int p_iColumn                                    //                                   *
 * @param  qint64 p_lParentId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:43:01 2012----------*/
QVariant CdmQueryResultObject::GetResult(int p_iRow, int p_iColumn,qint64 p_lParentId)
{
   QVariant qvRet;

   CdmQueryResultObject* pResult = GetChild(p_lParentId);

   if (pResult)
   {
      qvRet = pResult->GetResult(p_iRow, p_iColumn);
   }
   else
   {
      qvRet = GetResult(p_iRow, p_iColumn);
   }

   return qvRet;
}

/** +-=---------------------------------------------------------So 10. Feb 10:17:07 2013----------*
 * @method  CdmQueryResultObject::GetRowCount                // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:17:07 2013----------*/
int CdmQueryResultObject::GetRowCount() const
{
   return m_qmChildrenByObject.count();
}

/** +-=---------------------------------------------------------So 10. Feb 10:17:28 2013----------*
 * @method  CdmQueryResultObject::GetColumnCount             // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:17:28 2013----------*/
int CdmQueryResultObject::GetColumnCount() const
{
   return m_qmResultValues.count();
}

/** +-=---------------------------------------------------------So 10. Feb 10:17:36 2013----------*
 * @method  CdmQueryResultObject::GetObjectId                // public, const, slots              *
 * @return qint64                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:17:36 2013----------*/
qint64 CdmQueryResultObject::GetObjectId() const
{
   return m_lObjectId;
}

qint64 CdmQueryResultObject::GetContainerId() const
{
   return m_lContainerId;
}

qint64 CdmQueryResultObject::SetContainerId(qint64 p_lContainerId)
{
   return m_lContainerId = p_lContainerId;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:44:24 2012----------*
 * @method  CdmQueryResultObject::GetChildList               // public, slots                     *
 * @return  QList<CdmObject*>                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:44:24 2012----------*/
QList<CdmObject*> CdmQueryResultObject::GetChildList()
{
   QList<CdmObject*> qlChilds;
   CdmObjectContainer* pContainer = m_rpCdmQuery->GetContainer();

   if (CHKPTR(pContainer))
   {
       QMapIterator<qint64, CdmQueryResultObject*> qmIt(m_qmChildrenByObject);

       while (qmIt.hasNext())
       {
           qmIt.next();
           CdmQueryResultObject* pChild = qmIt.value();

           if (pChild)
           {
              qint64 lObjectId = pChild->GetObjectId();

               CdmObject* pCdmObject = pContainer->FindObjectById(lObjectId);

               if (CHKPTR(pCdmObject))
               {
                   qlChilds.append(pCdmObject);
               }
           }
       }
   }

   return qlChilds;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:44:43 2012----------*
 * @method  CdmQueryResultObject::GetObject                  // public, slots                     *
 * @return  CdmObject*                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:44:43 2012----------*/
CdmObject* CdmQueryResultObject::GetObject()
{
   CdmObject* pObject = nullptr;

   if (m_lObjectId > 0 && m_lContainerId > 0)
   {
      CdmObjectContainer* pContainer = m_rpCdmQuery->GetContainer();

      if (!pContainer)
      {
          CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

          if (CHKPTR(pManager))
          {
              CdmContainerManager* pContainerManager = pManager->GetContainerManager();

              if (CHKPTR(pContainerManager))
              {
                  pContainer = pContainerManager->FindContainerById(m_lContainerId);
              }
          }
      }

      if (CHKPTR(pContainer))
      {
          pObject = pContainer->FindObjectById(m_lObjectId);
      }
   }

   return pObject;
}

/** +-=---------------------------------------------------------Mo 15. Okt 08:47:25 2012----------*
 * @method  CdmQueryResultObject::CreateResultObject         // public, static                    *
 * @return  CdmQueryResultObject*                            //                                   *
 * @param   CdmQuery* p_pQuery                       //                                   *
 * @param   CdmQueryResultObject* p_pRoot                    //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param  qint64 p_lParentId                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 15. Okt 08:47:25 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::CreateResultObject(CdmQuery* p_pQuery,
                                                               CdmQueryResultObject* p_pRoot,
                                                              qint64 p_lObjectId,
                                                              qint64 p_lContainerId,
                                                              qint64 p_lParentId)
{
   CdmQueryResultObject* pRet = nullptr;
   CdmQueryResultObject* pParent = nullptr;

   if (p_lParentId > 0 && p_lParentId != p_lObjectId)
   {
      pParent = p_pRoot->GetChild(p_lParentId);

      if (!pParent)
      {
         pParent = CreateResultObject(p_pQuery, 
                                      p_pRoot, 
                                      p_lParentId, 
                                      p_lContainerId,
                                      GetObjectParentId(p_lParentId, p_lContainerId,  p_pQuery));
      }
   }
   else
   {
      if (p_lObjectId == p_lParentId)
      {
         WARNING("Parent and Object are equals!!!");
      }

      pParent = p_pRoot;
   }

   if (CHKPTR(pParent))
   {
      pRet = new CdmQueryResultObject(p_lObjectId, p_lContainerId, pParent, p_pQuery);
   }
   
   return pRet;
}

/** +-=---------------------------------------------------------Mo 15. Okt 10:17:00 2012----------*
 * @method  CdmQueryResultObject::FindOrCreateResultObject   // public, static                    *
 * @return  CdmQueryResultObject*                            //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   CdmQueryResultObject* p_pRoot                    //                                   *
 * @param   CdmQuery* p_pQuery                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 15. Okt 10:17:00 2012----------*/
CdmQueryResultObject* CdmQueryResultObject::FindOrCreateResultObject(qint64 p_lObjectId,
                                                                    qint64 p_lContainerId,
                                                                     CdmQueryResultObject* p_pRoot,
                                                                     CdmQuery* p_pQuery)
{
   CdmQueryResultObject* pResult = nullptr;

   if (CHKPTR(p_pRoot) && CHKPTR(p_pQuery))
   {
      pResult = p_pRoot->GetChild(p_lObjectId);

      if (!pResult)
      {
         pResult = CreateResultObject(p_pQuery,
                                      p_pRoot,
                                      p_lObjectId,
                                      p_lContainerId,
                                      GetObjectParentId(p_lObjectId, p_lContainerId,  p_pQuery));
      }
   }

   return pResult;
}

/** +-=---------------------------------------------------------Mo 15. Okt 10:17:38 2012----------*
 * @method  CdmQueryResultObject::GetObjectParentId          // private, static                   *
 * @return qint64                                             //                                   *
 * @param  qint64 p_lObjectId                                 //                                   *
 * @param   CdmQuery* p_pQuery                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 15. Okt 10:17:38 2012----------*/
qint64 CdmQueryResultObject::GetObjectParentId(qint64 p_lObjectId,qint64 p_lContainerId, CdmQuery* p_pQuery)
{
   qint64 lRet = -1;

    if (CHKPTR(p_pQuery))
    {
        CdmObjectContainer* pContainer = nullptr;
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            CdmContainerManager* pContainerManager = pManager->GetContainerManager();

            if (CHKPTR(pContainerManager) && p_lContainerId > 0)
            {
                pContainer = pContainerManager->FindEmptyContainerById(p_lContainerId);
            }
        }

        if (!pContainer)
        {
             pContainer = p_pQuery->GetContainer();
        }

        if (pContainer && pContainer->IsTree() && p_lObjectId >= 0)
        {
            CdmObject* pCdmObject = pContainer->FindObjectById(p_lObjectId);

            if (CHKPTR(pCdmObject))
            {
                lRet = pCdmObject->GetParentId();
            }
        }
    }

   return lRet;
}

/** +-=---------------------------------------------------------Di 12. Feb 11:02:03 2013----------*
 * @method  CdmQueryResultObject::GetVariant                 // public                            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 12. Feb 11:02:03 2013----------*/
QVariant CdmQueryResultObject::GetVariant()
{
   QVariantMap qvHash;
   qvHash["ObjectId"] = m_lObjectId;
   qvHash["ObjectListId"] = m_lContainerId;
   qvHash["Row"] = m_iRow;

   QMap<int, QVariant>::iterator qmIt = m_qmResultValues.begin();
   QMap<int, QVariant>::iterator qmItEnd = m_qmResultValues.end();

   QVariantMap qvResults;

   for (; qmIt != qmItEnd; ++qmIt)
   {
      qvResults[QString::number(qmIt.key())] = qmIt.value();
   }

   qvHash["Results"] = qvResults;

   QVariantList qvChildren;

   QMapIterator<qint64, CdmQueryResultObject*> qmItChildren(m_qmChildrenByObject);

   while (qmItChildren.hasNext())
   {
       qmItChildren.next();
       CdmQueryResultObject* pResult = qmItChildren.value();

      if (CHKPTR(pResult))
      {
         qvChildren.append(pResult->GetVariant());
      }
   }

   qvHash["Children"] = qvChildren;
   return qvHash;
}

QVariant CdmQueryResultObject::GetResultAsVariant()
{
   QMap<int, QVariant>::iterator qmIt = m_qmResultValues.begin();
   QMap<int, QVariant>::iterator qmItEnd = m_qmResultValues.end();

   QVariantMap qmResults;
   QVector<QString> qvResultElements = m_rpCdmQuery->GetResultElements();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      QString qstrResultElement = qvResultElements[qmIt.key()];
      qmResults[qstrResultElement] = qmIt.value();
   }

   QVariantList qvlLinks;
   QVariantMap qvmLink;
   qvmLink.insert(WMS_OBJECT, CdmLocatedElement::CreateUri(WMS_OBJECT, QString::number(m_lContainerId), QString::number(m_lObjectId)));
   qvlLinks.append(qvmLink);
   qmResults.insert(WMS_LINKS, qvmLink);

   if (GetRowCount() > 0)
   {
      QVariantList qvlChildren;

      for (int iPos = 0; iPos < GetRowCount(); ++iPos)
      {
         CdmQueryResultObject* pResult = GetChildAtRow(iPos);

         if (CHKPTR(pResult))
         {
            qvlChildren.append(pResult->GetResultAsVariant());
         }
      }

      qmResults[WMS_CHILDREN] = qvlChildren;
   }


   return qmResults;
}

/** +-=---------------------------------------------------------Di 12. Feb 11:06:32 2013----------*
 * @method  CdmQueryResultObject::SetVariant                 // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 12. Feb 11:06:32 2013----------*/
void CdmQueryResultObject::SetVariant(QVariantMap& p_rqvHash)
{
   m_lObjectId = p_rqvHash["ObjectId"].toInt();
   m_lContainerId = p_rqvHash["ObjectListId"].toInt();
   m_iRow = p_rqvHash["Row"].toInt();

   QVariantMap qvResults = p_rqvHash["Results"].toMap();

   QVariantMap::iterator qvIt = qvResults.begin();
   QVariantMap::iterator qvItEnd = qvResults.end();

   for (; qvIt != qvItEnd; ++qvIt)
   {
      m_qmResultValues.insert(qvIt.key().toInt(), qvIt.value());
   }

   QVariantList qvChildren = p_rqvHash["Children"].toList();

   for (int iCounter = 0; iCounter < qvChildren.count(); ++iCounter)
   {
      QVariantMap qvHash = qvChildren[iCounter].toMap();
      CdmQueryResultObject* pResult = new CdmQueryResultObject(0, 0, this, m_rpCdmQuery);
      pResult->SetVariant(qvHash);
   }
}
