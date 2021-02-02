#include <QDebug>

#include "CwsHttpResponse.h"

CwsHttpResponse::CwsHttpResponse()
    : CwsHttpBase(),
      m_eStatusCode(eWmsHttpStatusCodeOk),
      m_qstrContentType("application/json; charset=utf-8"),
      m_qstrAllowOrigin("*"),
      m_qstrConnectionMode("close")
{

}

QByteArray CwsHttpResponse::GenerateResponse()
{
    if (m_qbaContent.isEmpty())
    {
        BuildResponse();
    }

    return m_qbaContent;
}

void CwsHttpResponse::BuildResponse()
{
    QString qstrRepsone;
    GenerateHeadLine(qstrRepsone);
    QByteArray qbBody = GetBody().toUtf8();
    int iContentLength = qbBody.size();
    AddHeader("Date", QDateTime::currentDateTime().toString());
    AddHeader("Server", m_qstrServer);
    AddHeader("Content-Length", QString::number(iContentLength));
    AddHeader("Connection", m_qstrConnectionMode);
    AddHeader("Access-Control-Allow-Origin", m_qstrAllowOrigin);
    AddHeader("Content-Type", m_qstrContentType);
    AddHeadersToString(qstrRepsone);
    AddCookiesToString(qstrRepsone);
    qstrRepsone += "\r\n";

    m_qbaContent.append(qstrRepsone.toUtf8());
    m_qbaContent.append(qbBody + "\r\n");
}

void CwsHttpResponse::SetStatusCode(EwmsHttpStatusCode p_eStatusCode)
{
    m_eStatusCode = p_eStatusCode;
}

EwmsHttpStatusCode CwsHttpResponse::GetStatusCode()
{
    return m_eStatusCode;
}

int CwsHttpResponse::GetStatusCodeValue()
{
    return m_eStatusCode;
}

void CwsHttpResponse::SetContentType(QString p_qstrType)
{
    m_qstrContentType = p_qstrType;
}

QString CwsHttpResponse::GetContentType()
{
    return m_qstrContentType;
}

QString CwsHttpResponse::GetAllowOrigin()
{
    return m_qstrAllowOrigin;
}

void CwsHttpResponse::SetAllowOrigin(QString p_qstrOrigin)
{
    m_qstrAllowOrigin = p_qstrOrigin;
}



QString CwsHttpResponse::GetConnectionMode()
{
    return m_qstrConnectionMode;
}

void CwsHttpResponse::SetConnectionMode(QString p_qstrConnectionMode)
{
    m_qstrConnectionMode = p_qstrConnectionMode;
}

void CwsHttpResponse::GenerateHeadLine(QString &p_qstrRequest)
{
    p_qstrRequest = "HTTP/1.1 " + CwmsHttpService::GetReturnCodeAsString(m_eStatusCode) + "\r\n";
}

void CwsHttpResponse::AddCookiesToString(QString &p_qstrRequest)
{
    for (int iPos = 0; iPos < m_qlCookies.count(); ++iPos)
    {
        CwsCookie cookie = m_qlCookies[iPos];
        p_qstrRequest += cookie.generateCookieString() + "\r\n";
    }
}

void CwsHttpResponse::ParseHeadline(QString p_qstrRequest)
{
    QStringList qstrlHeaderParts = p_qstrRequest.split(" ");
    QString qstrStatusCode;

    if (qstrlHeaderParts.count() >= 3)
    {
        qstrStatusCode = qstrlHeaderParts[1];
    }
    else if (qstrlHeaderParts.count() == 2)
    {
        qstrStatusCode = qstrlHeaderParts[0];
    }

    if (!qstrStatusCode.isEmpty())
    {
        int iStatusCode = qstrStatusCode.toInt();

        if (iStatusCode > 0)
        {
            m_eStatusCode = (EwmsHttpStatusCode) iStatusCode;
        }
        else
        {
            qCritical() << "Unknown Statuscode for Response: " << qstrStatusCode;
            m_eStatusCode = eWmsHttpStatusCodeNotFound;
        }
    }
    else
    {
        qCritical() << "No Status code found in header: " << p_qstrRequest;
        m_eStatusCode = eWmsHttpStatusCodeNotFound;
    }
}


void CwsHttpResponse::ParseCookies(QString p_qstrCookies)
{
    QStringList qstrlCookies = p_qstrCookies.split(";");
    CwsCookie cookie;

    for(int iPos = 0; iPos < qstrlCookies.count(); ++iPos)
    {
        QString qstrCookie = qstrlCookies[iPos];
        QStringList qstrlKeyValue = qstrCookie.split("=");

        if (qstrlKeyValue.count() == 2)
        {
            cookie.setPair(qstrlKeyValue[0].simplified(), qstrlKeyValue[1].simplified());
        }
        else if (qstrlKeyValue.count() == 1)
        {
            cookie.setPair(qstrlKeyValue[0].simplified(), "");
        }
        else
        {
            qCritical() << "Unknown Parsestring for cookie: " << qstrCookie;
        }
    }

    m_qlCookies.append(cookie);
}
