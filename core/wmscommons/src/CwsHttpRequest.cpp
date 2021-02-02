/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwsHttpRequest.cpp
 ** Started Implementation: 2012/04/02
 ** Description:
 **
 ** Implements the class
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QTcpSocket>
#include <QJsonDocument>
#include <QByteArray>
#include <QUrl>
#include <QTextStream>
#include <QHostAddress>

#include <QDateTime>
#include <QCoreApplication>

// own Includes

#include "CwsHttpRequest.h"





CwsHttpRequest::CwsHttpRequest()
    : CwsHttpBase(),m_qstrVersion("1.1")
{

}

CwsHttpRequest::~CwsHttpRequest()
{

}

QString CwsHttpRequest::GenerateRequestString()
{
    if (m_qbaContent.isEmpty())
    {
        m_qbaContent.append(GetMethodAsString().toUtf8());
        m_qbaContent.append(" " + GetPathInfo().toUtf8() + GenerateParameterListString().toUtf8() + " HTTP/"+GetHttpVersion()+"\r\n");

        QString qstrHttpRequest;
        AddHeadersToString(qstrHttpRequest);
        AddCookiesToString(qstrHttpRequest);
        m_qbaContent.append("Host: " + GetHost() + " \r\n");
        qstrHttpRequest += "\r\n";

        if (m_wsMethod !=  eWsGet)
        {

            qstrHttpRequest += GetBody();
        }

        m_qbaContent.append(qstrHttpRequest.toUtf8());
    }

    return m_qbaContent;
}

void CwsHttpRequest::AddCookiesToString(QString& p_qstrRequest)
{
    if(m_qlCookies.count()!=0){
        p_qstrRequest += "Cookie: ";

        for (int iPos = 0; iPos < m_qlCookies.count(); ++iPos)
        {
            if (iPos > 0)
            {
                p_qstrRequest +="; ";
            }

            CwsCookie cookie = m_qlCookies[iPos];
            p_qstrRequest += cookie.getName() + "=" + cookie.getValue();
        }

        p_qstrRequest += "\r\n";
    }
}

void CwsHttpRequest::ParseHeadline(QString p_qstrRequest)
{
    int iPos = p_qstrRequest.indexOf(" ");

    if (iPos > 0)
    {
        QString qstrMethod = p_qstrRequest.left(iPos);
        SetMethod(GetMethodFromString(qstrMethod));

        int iPosParams = p_qstrRequest.indexOf("?");

        if (iPosParams >= 0)
        {
            ParseParameter(p_qstrRequest.mid(iPosParams + 1));
            m_qstrUrl = p_qstrRequest.mid(iPos + 1, iPosParams - iPos - 1);
        }
        else
        {
            int iEndPos = p_qstrRequest.indexOf(" ", iPos + 1);

            if (iEndPos < 0)
            {
                m_qstrUrl = p_qstrRequest.mid(iPos + 1);
            }
            else
            {
                m_qstrUrl = p_qstrRequest.mid(iPos + 1, iEndPos - iPos - 1);
            }
        }
    }
}

void CwsHttpRequest::ParseParameter(QString p_qstrParams)
{
    int iEndPos = p_qstrParams.indexOf(" ", 0);

    if (iEndPos > 0)
    {
        p_qstrParams = p_qstrParams.left(iEndPos);
    }

    QStringList qstrlParams = p_qstrParams.split("&");

    for (int iPos = 0; iPos < qstrlParams.count(); ++iPos)
    {
        QString qstrParamDef = qstrlParams[iPos];

        QStringList qstrlParamKeyValue= qstrParamDef.split("=");

        QString qstrKey = qstrlParamKeyValue[0];
        QString qstrValue;

        if (qstrlParamKeyValue.count() == 2)
        {
            qstrValue = qstrlParamKeyValue[1];
        }

        AddPathVariable(qstrKey, qstrValue);
    }
}



EwsHttpMethod CwsHttpRequest::GetMethod() const
{
    return m_wsMethod;
}

QString CwsHttpRequest::GetHttpVersion() const
{
    return m_qstrVersion;
}

QString CwsHttpRequest::GetHost() const
{
    QString qstrHost;
    int iPosStart = m_qstrUrl.indexOf("://");

    if (iPosStart > 0)
    {
        int iPosEnd = m_qstrUrl.indexOf("/", iPosStart + 3);

        if (iPosEnd >= 0)
        {
            qstrHost = m_qstrUrl.mid(iPosStart + 3, iPosEnd - iPosStart - 3);
        }
    }
    else
    {
        int iPosEnd = m_qstrUrl.indexOf("/");

        if (iPosEnd >= 0)
        {
            qstrHost = m_qstrUrl.left(iPosEnd);
        }
    }

    if (qstrHost.isEmpty())
    {
        qstrHost = GetServer();
    }

    return qstrHost;
}

QString CwsHttpRequest::GetPathInfo() const
{
     int iPos = m_qstrUrl.indexOf("://");

     if (iPos > 0)
     {
         iPos = m_qstrUrl.indexOf("/", iPos + 3);

         if (iPos >= 0)
         {
             return m_qstrUrl.mid(iPos);
         }
     }
     else
     {
         iPos = m_qstrUrl.indexOf("/");

         if (iPos >= 0)
         {
             return m_qstrUrl.mid(iPos);
         }
     }

     return "";
}

QString CwsHttpRequest::GetPathVariable(QString p_qstrKey) const
{
    QString qstrVariable = m_qmPathVariables[p_qstrKey.toLower()];
    qstrVariable = QUrl::fromPercentEncoding(qstrVariable.toLocal8Bit());

    if (qstrVariable.startsWith("\"") && qstrVariable.endsWith("\""))
    {
        qstrVariable = qstrVariable.mid(1, qstrVariable.length() - 2);
    }

    return qstrVariable;
}

bool CwsHttpRequest::HasPathVariable(QString p_qstrKey) const
{
    return m_qmPathVariables.contains(p_qstrKey.toLower());
}

int CwsHttpRequest::GetPathVariableCount() const
{
    return m_qmPathVariables.count();
}

QStringList CwsHttpRequest::GetPathVariableNames() const
{
    return m_qmPathVariables.keys();
}

QMap<QString,QString>& CwsHttpRequest::GetPathVariableMap()
{
    return m_qmPathVariables;
}


QString CwsHttpRequest::GetContextPath() const
{
    int iPos = m_qstrUrl.lastIndexOf("?");

    if (iPos >= 0)
    {
        return m_qstrUrl.mid(iPos + 1);
    }
    else
    {
        return m_qstrUrl;
    }

    return "";
}

void CwsHttpRequest::AddPathVariable(QString p_qstrKey, QString p_qstrValue)
{
    m_qmPathVariables.insert(p_qstrKey.toLower(), p_qstrValue);
}

void CwsHttpRequest::SetMethod(EwsHttpMethod p_eMthod)
{
    m_wsMethod = p_eMthod;
}

bool CwsHttpRequest::IsSSLRequest() const
{
    return GetProtocol().toLower().startsWith("https") || m_qstrUrl.contains(":443/");
}


QString CwsHttpRequest::GetProtocol() const
{
    QString qstrProtocol;
    int iPos = m_qstrUrl.indexOf("://");

    if (iPos > 0)
    {
        qstrProtocol = m_qstrUrl.left(iPos);
    }

    return qstrProtocol;
}

void CwsHttpRequest::SetUrl(QString p_qstrUrl)
{
    m_qstrUrl = p_qstrUrl;
}



void CwsHttpRequest::SetHttpVersion(QString p_qstrVersion)
{
    m_qstrVersion = p_qstrVersion;
}

QString CwsHttpRequest::GetMethodAsString() const
{
    QString qstrHttpRequest;

    switch (m_wsMethod)
    {
        case eWsGet:
            qstrHttpRequest += "GET";
        break;
        case eWsDelete:
            qstrHttpRequest += "DELETE";
            break;
        case eWsPost:
            qstrHttpRequest += "POST";
            break;
        case eWsPut:
            qstrHttpRequest += "PUT";
            break;
        case eWsTrace:
            qstrHttpRequest += "TRACE";
            break;
        case eWsConnect:
            qstrHttpRequest += "CONNECT";
            break;
        default:
            qstrHttpRequest += "GET";
    }

    return qstrHttpRequest;
}

 void CwsHttpRequest::SetMethod(QString p_qstrMethod)
 {
     m_wsMethod = GetMethodFromString(p_qstrMethod);
 }

EwsHttpMethod CwsHttpRequest::GetMethodFromString(QString p_qstrMethod) const
{
    if(p_qstrMethod.toUpper() == HTTP_GET)
    {
        return eWsGet;
    }
    else if (p_qstrMethod.toUpper() == HTTP_PUT)
    {
        return eWsPut;
    }
    else if (p_qstrMethod.toUpper() == HTTP_DELETE)
    {
        return eWsDelete;
    }
    else if (p_qstrMethod.toUpper() == HTTP_POST)
    {
        return eWsPost;
    }
    else if (p_qstrMethod.toUpper() == HTTP_TRACE)
    {
       return eWsTrace;
    }
    else if (p_qstrMethod.toUpper() == HTTP_CONNECT)
    {
        return eWsConnect;
    }
    else if (p_qstrMethod.toUpper() == HTTP_OPTIONS)
    {
        return eWsOptions;
    }

    return eWsGet;
}

QString CwsHttpRequest::GenerateParameterListString()
{
    QString qstrParams;

    if (!m_qmPathVariables.isEmpty())
    {
        qstrParams = "?";
        QMap<QString, QString>::iterator qmIt = m_qmPathVariables.begin();
        QMap<QString, QString>::iterator qmItEnd = m_qmPathVariables.end();
        bool bFirst = true;

        for (;qmIt != qmItEnd; ++qmIt)
        {
            if (!bFirst)
            {
                qstrParams +="&";
            }
            else
            {
                bFirst = false;
            }

            qstrParams += qmIt.key() + "=" + qmIt.value() + "\r\n";
        }
    }

    return qstrParams;
}

void CwsHttpRequest::ParseCookies(QString p_qstrCookies)
{
    QStringList qstrlCookies = p_qstrCookies.split(";");

    for(int iPos = 0; iPos < qstrlCookies.count(); ++iPos)
    {
        QString qstrCookie = qstrlCookies[iPos];
        QStringList qstrlKeyValue = qstrCookie.split("=");

        if (qstrlKeyValue.count() == 2)
        {
            CwsCookie cookie;
            cookie.setName(qstrlKeyValue[0].simplified());
            cookie.setValue(qstrlKeyValue[1].simplified());
            m_qlCookies.append(cookie);
        }
    }
}
