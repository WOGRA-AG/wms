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
#include <qdatetime.h>

// own Includes
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "IdmDataAccess.h"
#include "CdmLogging.h"
#include "CdmLoggingAdaptor.h"




/** +-=---------------------------------------------------------Mo 2. Jul 21:18:56 2007-----------*
 * @method  CdmErrorAdaptor::AddError                        // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:18:56 2007-----------*/


/** +-=---------------------------------------------------------Mo 2. Jul 21:19:06 2007-----------*
 * @method  CdmErrorAdaptor::AddInfo                         // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:19:06 2007-----------*/


/** +-=---------------------------------------------------------Mo 2. Jul 21:19:19 2007-----------*
 * @method  CdmErrorAdaptor::AddWarning                      // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:19:19 2007-----------*/


/** +-=---------------------------------------------------------Mo 2. Jul 21:19:29 2007-----------*
 * @method  CdmErrorAdaptor::AddFatal                        // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:19:29 2007-----------*/


/** +-=---------------------------------------------------------Mo 2. Jul 19:54:08 2007-----------*
 * @method  CdmErrorAdaptor::AddEvent                        // public                            *
 * @return  void                                             //                                   *
 * @param   EdmErrorSeverity p_eDmErrorSeverity              //                                   *
 * @param   QString p_qstrErrorModule                        //                                   *
 * @param   QString p_qstrEventText                          //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment This method adds a error event in the queue.                                          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 19:54:08 2007-----------*/

CdmLoggingAdaptor::~CdmLoggingAdaptor()
{
    QMap<EdmErrorSeverity,QStringList*>::iterator qmIt = m_qmRelevanceClasses.begin();
    QMap<EdmErrorSeverity,QStringList*>::iterator qmItEnd = m_qmRelevanceClasses.end();

    for (; qmIt != qmItEnd; ++qmIt)
    {
        DELPTR(qmIt.value());
    }

    m_qmRelevanceClasses.clear();
}

void CdmLoggingAdaptor::AddEvent(CdmLogEntry& p_Entry)
{
    if(MatchesPatterns(p_Entry))
    {
       switch (p_Entry.GetErrorSeverity())
       {
          case eDmInfo:
             AddInfo(p_Entry);
             break;
          case eDmWarning:
             AddWarning(p_Entry);
             break;
          case eDmError:
             AddError(p_Entry);
             break;
          case eDmFatal:
             AddFatal(p_Entry);
             break;
          default:
             AddInfo(p_Entry);
             break;
       };
    }
}

bool CdmLoggingAdaptor::MatchesPatterns(CdmLogEntry& p_Entry)
{
    bool bContinue = false;

    if (!m_qmRelevanceClasses.isEmpty() && m_qmRelevanceClasses.contains(p_Entry.GetErrorSeverity()))
    {
        QStringList* pqstrlPatterns = m_qmRelevanceClasses[p_Entry.GetErrorSeverity()];

        if (pqstrlPatterns != nullptr && pqstrlPatterns->count() > 0)
        {
            QString qstrFile = p_Entry.GetErrorModule();

            for (int i = 0; i < pqstrlPatterns->count(); ++i)
            {
                QString qstrPattern = pqstrlPatterns->at(i);
                QRegExp regex(qstrPattern, Qt::CaseInsensitive, QRegExp::Wildcard);

                if (regex.exactMatch(qstrFile))
                {
                    bContinue = true;
                    break;
                }
            }
        }
        else
        {
            bContinue = true;
        }
    }
    else
    {
        bContinue = true;
    }

    return bContinue;
}

/** +-=---------------------------------------------------------Sa 7. Jul 17:44:29 2007-----------*
 * @method  CdmErrorAdaptor::GetDataAccessCallCounter        // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jul 17:44:29 2007-----------*/
int CdmLoggingAdaptor::GetDataAccessCallCounter()
{
   int iRet = 0;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (pCdmManager)
   {
      IdmDataAccess* pIdmDataAccess = pCdmManager->GetDataAccess();
      iRet = pIdmDataAccess->GetInterfaceCallCounter();
   }

   return iRet;
}
//m_qmRelevanceClasses


void CdmLoggingAdaptor::AddLoggingRelevance(EdmErrorSeverity p_eSeverity, QString p_qstrPattern)
{
    QStringList* pqstrlPatterns = nullptr;

    if (m_qmRelevanceClasses.contains(p_eSeverity))
    {
        pqstrlPatterns = m_qmRelevanceClasses[p_eSeverity];

        if (!pqstrlPatterns)
        {
            pqstrlPatterns = new QStringList();
            m_qmRelevanceClasses.insert(p_eSeverity, pqstrlPatterns);
        }
    }
    else
    {
        pqstrlPatterns = new QStringList();
        m_qmRelevanceClasses.insert(p_eSeverity, pqstrlPatterns);
    }

    if (CHKPTR(pqstrlPatterns))
    {
        if (!pqstrlPatterns->contains(p_qstrPattern))
        {
            pqstrlPatterns->append(p_qstrPattern);
        }
    }
}

void CdmLoggingAdaptor::RemoveLoggingRelevance(EdmErrorSeverity p_eSeverity, QString p_qstrPattern)
{
    if (m_qmRelevanceClasses.contains(p_eSeverity))
    {
        QStringList* pqstrlPatterns = m_qmRelevanceClasses[p_eSeverity];

        if (pqstrlPatterns)
        {
            if (pqstrlPatterns->contains(p_qstrPattern))
            {
                pqstrlPatterns->removeAll(p_qstrPattern);
            }
        }
    }
}

/** +-=---------------------------------------------------------Mo 2. Jul 20:08:50 2007-----------*
 * @method  CdmErrorAdaptor::AddErrorCode                    // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   QDateTime p_qdtTimeStamp                         //                                   *
 * @param   int p_iCode                                      //                                   *
 * @comment This method adds an error code to the adaptor.                                        *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 20:08:50 2007-----------*/
