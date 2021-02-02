/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsDataExchange.cpp
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

// WMS Commons Includes
#include "CwsHttpRequest.h"

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "IwmsParser.h"
#include "IwmsSerializer.h"

// Basetools Includes
#include "CwmsErrorCollectorSession.h"

// own Includes
#include "CwmsDataExchangeConfigurator.h"
#include "CwmsDataExchange.h"

CwmsDataExchange::CwmsDataExchange(CwsHttpRequest * p_pRequest, CwsHttpResponse * p_pResponse, CwmsDataExchangeConfigurator* p_pHandler)
: m_bValid(false),
  m_rpHandler(p_pHandler),
  m_rpRequest(p_pRequest),
  m_rpResponse(p_pResponse)
{
    if (m_rpRequest)
    {
        m_bValid = ParseBody(m_rpRequest->GetBody());
        ParseHeader();
    }
}

CwmsDataExchange::CwmsDataExchange(QString p_qstrSource, CwmsDataExchangeConfigurator* p_pHandler)
: m_bValid(false),
  m_rpHandler(p_pHandler),
  m_rpRequest(nullptr)
{
    if (!p_qstrSource.isEmpty())
    {
        m_bValid = ParseBody(p_qstrSource);
    }
}

CwmsDataExchange::CwmsDataExchange(CwmsDataExchangeConfigurator* p_pHandler)
: m_bValid(true),
  m_rpHandler(p_pHandler)
{
}

/** +-=---------------------------------------------------------So 1. Apr 12:16:10 2012-----------*
 * @method  CwmsDataExchange::~CwmsDataExchange                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsDataExchange                                                   *
 *----------------last changed: --------------------------------So 1. Apr 12:16:10 2012-----------*/
CwmsDataExchange::~CwmsDataExchange()
{
}

/** +-=---------------------------------------------------------So 1. Apr 12:15:22 2012-----------*
 * @method  CwmsDataExchange::IsValid                             // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 1. Apr 12:15:22 2012-----------*/
bool CwmsDataExchange::IsValid()
{
   return m_bValid;
}

CwsHttpRequest* CwmsDataExchange::GetRequest() const
{
    return m_rpRequest;
}

CwsHttpResponse* CwmsDataExchange::GetResponse() const
{
    return m_rpResponse;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:43:33 2012-----------*
 * @method  CwmsDataExchange::HasValue                            // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:43:33 2012-----------*/
bool CwmsDataExchange::HasValue(QString p_qstrValue)
{
   return m_qmMembers.contains(p_qstrValue);
}

/** +-=---------------------------------------------------------Di 3. Apr 13:55:33 2012-----------*
 * @method  CwmsDataExchange::GetValue                            // public                            *
 * @return  QVariant                                         //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 3. Apr 13:55:33 2012-----------*/
QVariant CwmsDataExchange::GetValue(QString p_qstrKey)
{
   QVariant qResult;

   if (!p_qstrKey.contains("."))
   {
      qResult = m_qmMembers[p_qstrKey];
   }
   else
   {
      int iPos = 0;
      QVariantMap qmMap = m_qmMembers;
      bool bError = false;

      do 
      {
         iPos = p_qstrKey.indexOf(".");

         QString qstrKey = p_qstrKey.mid(0, iPos);
         p_qstrKey = p_qstrKey.mid(iPos + 1, p_qstrKey.length() - iPos -1);

         if (qmMap[p_qstrKey].type() == QVariant::Map)
         {
            qmMap = qmMap[p_qstrKey].toMap();
         }
         else
         {
            bError = true;
            // ToDo Error handling
            break;
         }
      } 
      while (iPos >= 0);

      if (!bError)
      {
         qResult = qmMap[p_qstrKey];
      }
   }

   return qResult;
}

void CwmsDataExchange::SetValue(QString p_qstrKey, QVariant p_rValue)
{
    m_qmMembers.insert(p_qstrKey, p_rValue);
}

QVariantMap CwmsDataExchange::GetMembers()
{
    return m_qmMembers;
}

QString CwmsDataExchange::Serialize()
{
    QString qstrContent;

    if (CHKPTR(m_rpHandler))
    {
        IwmsSerializer* pSerializer = m_rpHandler->GetSerializer();

        if (CHKPTR(pSerializer))
        {
            qstrContent = QString::fromUtf8(pSerializer->serialize(m_qmMembers));
        }
    }

    return qstrContent;
}

/** +-=---------------------------------------------------------Mo 9. Apr 11:10:24 2012-----------*
 * @method  CwmsDataExchange::Parse                               // protected, virtual                *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrSource                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 11:10:24 2012-----------*/
bool CwmsDataExchange::ParseBody(QString p_qstrSource)
{
   if (m_rpHandler)
   {
      IwmsParser* pParser = m_rpHandler->GetParser();

      if (pParser)
      {
         m_qmMembers = pParser->parse(p_qstrSource).toMap();
         QString qstrResource = m_qmMembers["Resource"].toString();

         if (qstrResource.startsWith("Get"))
         {
            m_qmMembers.insert("Command", "Get");
            m_qmMembers.insert("Resource", qstrResource.mid(3, qstrResource.length() - 3));
         }
         else if (qstrResource.startsWith("Put"))
         {
            m_qmMembers.insert("Command", "Put");
            m_qmMembers.insert("Resource", qstrResource.mid(3, qstrResource.length() - 3));
         }
         else if (qstrResource.startsWith("Delete"))
         {
            m_qmMembers.insert("Command", "Delete");
            m_qmMembers.insert("Resource", qstrResource.mid(6, qstrResource.length() - 6));
         }
      }
   }   

   return (m_qmMembers.count() > 0);
}

/** +-=---------------------------------------------------------Fr 13. Apr 13:27:00 2012----------*
 * @method  CwmsDataExchange::ParseHeader                         // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrHeader                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Apr 13:27:00 2012----------*/
void CwmsDataExchange::ParseHeader()
{
    if (CHKPTR(m_rpRequest))
    {
        if (!m_qmMembers.contains("Command"))
        {
            m_qmMembers.insert("Command", m_rpRequest->GetMethodAsString());
        }

        QString qstrContext = m_rpRequest->GetContextPath();
        QStringList qstrlContext = qstrContext.split("/", QString::SkipEmptyParts);

        if (qstrlContext.count() > 0)
        {
            m_qmMembers.insert("Controller", qstrlContext[0]);
        }

        if (qstrlContext.count() > 1)
        {
            m_qmMembers.insert("Resource", qstrlContext[1]);
        }

    }



}
