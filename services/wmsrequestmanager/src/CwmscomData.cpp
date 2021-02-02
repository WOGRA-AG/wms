/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmscomData.cpp
 ** Started Implementation: 2012/04/01
 ** Description:
 **
 ** The Data Object which contains the request data and finally the result.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QStringList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "IwmsParser.h"
#include "IwmsSerializer.h"
#include "wmsdefines.h"

// Basetools Includes
#include "CwmsErrorCollectorSession.h"

// own Includes

#include "CwmscomController.h"
#include "CwmscomHandler.h"
#include "CwmscomDataResult.h"
#include "CwmscomData.h"

/** +-=---------------------------------------------------------Mo 9. Apr 11:41:10 2012-----------*
 * @method  CwmscomData::CwmscomData                         // public                            *
 * @return                                                   //                                   *
 * @param   QString p_qstrSource                             //                                   *
 * @param   CwmscomHandler* p_pHandler                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:41:10 2012-----------*/
CwmscomData::CwmscomData(CwsHttpRequest* p_pRequest,  CwsHttpResponse* p_pResponse, CwmscomHandler* p_pHandler)
: CwmsDataExchange(p_pRequest, p_pResponse, p_pHandler),
  m_pResult(nullptr),
  m_bLoggingActive(true)
{
    m_pErrorCollector = new CwmsErrorCollectorSession(GetSession());
    m_pErrorCollector->SetSeverity(GetLogSeverity());
    CdmLogging::AddAdaptor(m_pErrorCollector);
}

/** +-=---------------------------------------------------------So 1. Apr 12:16:10 2012-----------*
 * @method  CwmscomData::~CwmscomData                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmscomData                                                   *
 *----------------last changed: --------------------------------So 1. Apr 12:16:10 2012-----------*/
CwmscomData::~CwmscomData()
{
   DELPTR(m_pResult);
}


/** +-=---------------------------------------------------------So 1. Apr 10:32:10 2012-----------*
 * @method  CwmscomData::SetResult                           // public                            *
 * @return  void                                             //                                   *
 * @param   CwmscomDataResult* p_pResult                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:32:10 2012-----------*/
void CwmscomData::SetResult(CwmscomDataResult* p_pResult)
{
   m_pResult = p_pResult;
}

bool CwmscomData::IsLoggingActive()
{
    return m_bLoggingActive;
}

void CwmscomData::DeactivateLogging()
{
    m_bLoggingActive = false;

    if (m_pErrorCollector)
    {
        CdmLogging::RemoveAdaptor(m_pErrorCollector);
        DELPTR(m_pErrorCollector);
    }
}

/** +-=---------------------------------------------------------So 1. Apr 10:33:11 2012-----------*
 * @method  CwmscomData::GetResult                           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 10:33:11 2012-----------*/
QString CwmscomData::GetResult()
{
   QString qstrResult;

   if (m_pResult)
   {
      QVariantMap& qmResult = m_pResult->GetResultMap();
      if (!qmResult.isEmpty())
      {
          if (m_bLoggingActive)
          {
            qmResult.insert(WMS_LOG, m_pErrorCollector->ToJson());
            CdmLogging::RemoveAdaptor(m_pErrorCollector);
            DELPTR(m_pErrorCollector);
          }

          if (m_rpHandler)
          {
             IwmsSerializer* pSerializer = m_rpHandler->GetSerializer();

             if (pSerializer)
             {
                qstrResult = QString::fromUtf8(pSerializer->serialize(qmResult));
             }
          }
      }
   }

   return qstrResult;
}

/** +-=---------------------------------------------------------So 1. Apr 11:23:31 2012-----------*
 * @method  CwmscomData::GetControllerName                   // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:23:31 2012-----------*/
QString CwmscomData::GetControllerName()
{
   return m_qmMembers.value("Controller").toString();
}

/** +-=---------------------------------------------------------So 1. Apr 11:23:45 2012-----------*
 * @method  CwmscomData::GetResource                         // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 11:23:45 2012-----------*/
QString CwmscomData::GetResource()
{
   return m_qmMembers.value("Resource").toString();
}

/** +-=---------------------------------------------------------Di 3. Apr 13:57:43 2012-----------*
 * @method  CwmscomData::GetSession                          // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 13:57:43 2012-----------*/
int CwmscomData::GetSession()
{
    QString qstrSession = "SessionId";
   return m_qmMembers.value(qstrSession).toInt();
}

int CwmscomData::GetLogSeverity()
{
    int iRet = eDmError | eDmFatal;

    if (HasValue("LogSeverity"))
    {
        m_qmMembers.value("LogSeverity").toInt();
    }

    return iRet;
}

/** +-=---------------------------------------------------------Mo 9. Jul 12:12:05 2012-----------*
 * @method  CwmscomData::GetStatusCode                       // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Jul 12:12:05 2012-----------*/
EwmsHttpStatusCode CwmscomData::GetStatusCode()
{
   EwmsHttpStatusCode eCode = eWmsHttpStatusCodeOk;

   if (m_pResult)
   {
      eCode = m_pResult->GetReturnCode();
   }

   return eCode;
}
