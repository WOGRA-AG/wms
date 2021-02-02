/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CdmQueryResultElement.cpp
 ** Started Implementation: 2010/11/10
 ** Description:
 ** 
 ** This class implements the result elements of queries
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes


// Own Includes
#include "CdmLogging.h"
#include "CdmQuery.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQueryResultElement.h"

/** +-=---------------------------------------------------------Do 11. Nov 10:12:43 2010----------*
 * @method  CdmQueryResultElement::CdmQueryResultElement     // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   EdmQueryResultElementMode p_eDmMode              //                                   *
 * @param   CdmQuery* p_pCdmQuery            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Nov 10:12:43 2010----------*/
CdmQueryResultElement::CdmQueryResultElement(QString p_qstrKeyname,
                                             EdmQueryResultElementMode p_eDmMode,
                                             CdmQuery* p_pCdmQuery)
: m_qstrKeyname(p_qstrKeyname),
  m_eDmMode(p_eDmMode),
  m_rpCdmQuery(p_pCdmQuery)
{
}

/** +-=---------------------------------------------------------Di 17. Apr 13:15:28 2012----------*
 * @method  CdmQueryResultElement::CdmQueryResultElement     // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmQuery* p_pQuery                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 17. Apr 13:15:28 2012----------*/
CdmQueryResultElement::CdmQueryResultElement(QVariantMap& p_rqvHash, CdmQuery* p_pQuery)
: m_qstrKeyname(""),
  m_eDmMode(eDmQueryResultElementModeNone),
  m_rpCdmQuery(p_pQuery)
{
   m_qstrKeyname = p_rqvHash["Keyname"].toString();
   m_eDmMode = (EdmQueryResultElementMode)p_rqvHash["ElementMode"].toInt();

   QList<QVariant> qlResults = p_rqvHash["Results"].toList();

   for (int iPos = 0; iPos < qlResults.size(); ++iPos)
   {
      QVariant qValue = qlResults[iPos];
      m_qvResults.append(qValue);
   }
}

/** +-=---------------------------------------------------------Mi 10. Nov 17:00:06 2010----------*
 * @method  CdmQueryResultElement::~CdmQueryResultElement    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmQueryResultElement                                         *
 *----------------last changed: --------------------------------Mi 10. Nov 17:00:06 2010----------*/
CdmQueryResultElement::~CdmQueryResultElement()
{
}

/** +-=---------------------------------------------------------So 10. Feb 10:15:22 2013----------*
 * @method  CdmQueryResultElement::GetVariant                // public, const                     *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:15:22 2013----------*/
QVariant CdmQueryResultElement::GetVariant() const
{
   QVariantMap qvHash;

   qvHash.insert("ElementMode", m_eDmMode);
   qvHash.insert("Keyname", m_qstrKeyname);

   QList<QVariant> qlResults;

   QVector<QVariant>::const_iterator qvIt = m_qvResults.begin();
   QVector<QVariant>::const_iterator qvItEnd = m_qvResults.end();

   for (; qvIt != qvItEnd; ++qvIt)
   {
      QVariant qValue = *qvIt;
      qlResults.append(qValue);
   }

   qvHash.insert("Results", qlResults);

   return qvHash;
}

/** +-=---------------------------------------------------------So 10. Feb 10:15:30 2013----------*
 * @method  CdmQueryResultElement::GetKeyname                // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:15:30 2013----------*/
QString CdmQueryResultElement::GetKeyname() const
{
   return m_qstrKeyname;
}

/** +-=---------------------------------------------------------So 10. Feb 10:15:39 2013----------*
 * @method  CdmQueryResultElement::GetMode                   // public, const, slots              *
 * @return  EdmQueryResultElementMode                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 10:15:39 2013----------*/
EdmQueryResultElementMode CdmQueryResultElement::GetMode() const
{
   return m_eDmMode;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:38:37 2012----------*
 * @method  CdmQueryResultElement::GetResults                // public, slots                     *
 * @return  QVector<QVariant>&                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:38:37 2012----------*/
QVector<QVariant>& CdmQueryResultElement::GetResults()
{
   return m_qvResults;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:39:20 2012----------*
 * @method  CdmQueryResultElement::GetResultCount            // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:39:20 2012----------*/
int CdmQueryResultElement::GetResultCount() const
{
   return m_qvResults.count();
}

/** +-=---------------------------------------------------------Di 20. Nov 11:39:28 2012----------*
 * @method  CdmQueryResultElement::GetResultAt               // public, const, slots              *
 * @return  QVariant                                         //                                   *
 * @param   int p_iPos                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:39:28 2012----------*/
QVariant CdmQueryResultElement::GetResultAt(int p_iPos) const
{
   QVariant qVariant;

   if (m_qvResults.count() > p_iPos)
   {
      qVariant =  m_qvResults[p_iPos];
   }

   return qVariant;
}

/** +-=---------------------------------------------------------Di 20. Nov 11:39:38 2012----------*
 * @method  CdmQueryResultElement::GetValueType              // public, slots                     *
 * @return  EdmValue                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:39:38 2012----------*/
EdmValueType CdmQueryResultElement::GetValueType()
{
   EdmValueType eDmValue = eDmValueNone;

   if (CHKPTR(m_rpCdmQuery))
   {
      CdmObjectContainer* pContainer = m_rpCdmQuery->GetContainer();
      const CdmClass* pCdmClass = nullptr;
      if (pContainer)
      {
         pCdmClass = pContainer->GetClass();
      }
      else
      {
          pCdmClass = m_rpCdmQuery->GetClass();
      }

      if (CHKPTR(pCdmClass))
      {
         const CdmMember* pCdmMember = pCdmClass->FindMember(m_qstrKeyname);

         if (CHKPTR(pCdmMember))
         {
            eDmValue = pCdmMember->GetValueType();
         }
      }
   }
   
   return eDmValue;
}

/** +-=---------------------------------------------------------Fr 12. Nov 08:49:17 2010----------*
 * @method  CdmQueryResultElement::AddResult                 // private                           *
 * @return  void                                             //                                   *
 * @param   QVariant p_qvValue                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 12. Nov 08:49:17 2010----------*/
void CdmQueryResultElement::AddResult(QVariant p_qvValue)
{
   m_qvResults.append(p_qvValue);
}

/** +-=---------------------------------------------------------Di 20. Nov 11:39:57 2012----------*
 * @method  CdmQueryResultElement::ClearResults              // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 11:39:57 2012----------*/
void CdmQueryResultElement::ClearResults()
{
   m_qvResults.clear();
}

QStringList CdmQueryResultElement::GetResultAsStringList(CdmQuery* p_pQuery, int p_iCol, bool p_bTrimmed)
{
    QStringList qstrlResult;

    BODY_TRY
    if (CHKPTR(p_pQuery))
    {
        int iNumResults = p_pQuery->GetResultCount();

        for (int iCounter = 0; iCounter < iNumResults; ++iCounter)
        {
            QString qstrResult = p_pQuery->GetResultAt(p_iCol, iCounter).toString();

            if (p_bTrimmed)
            {
                qstrResult = qstrResult.trimmed();
            }

            qstrlResult.append(qstrResult);
        }
    }
    BODY_CATCH

    return qstrlResult;
}
