// System and Qt Includes
#include <QStringList>

// own Includes
#include "wmsServerDefines.h"
#include "CwsHttpBase.h"


CwsHttpBase::CwsHttpBase()
    : m_iHeaderLength(0),
      m_qstrServer("localhost")
{

}

CwsHttpBase::~CwsHttpBase()
{

}

QList<QString> CwsHttpBase::GetHeaderNames() const
{
    return m_qmHeaderInformation.keys();
}

QString CwsHttpBase::GetHeader(QString p_qstrKey) const
{
    return m_qmHeaderInformation[p_qstrKey];
}

int CwsHttpBase::GetIntHeader(QString p_qstrKey) const
{
    return m_qmHeaderInformation[p_qstrKey].toInt();
}

int CwsHttpBase::GetHeaderCount() const
{
    return m_qmHeaderInformation.count();
}

int CwsHttpBase::GetContentLength() const
{
    int iLength = 0;

    if (m_qmHeaderInformation.contains("Content-Length"))
    {
        iLength = GetIntHeader("Content-Length");
    }

    return iLength;
}

QString CwsHttpBase::GetBody() const
{
    return m_qstrBody;
}

bool CwsHttpBase::IsBodyEmpty()
{
    return m_qstrBody.isEmpty();
}

void CwsHttpBase::AddHeader(QString p_qstrKey, QString p_qstrValue)
{
    m_qmHeaderInformation.insert(p_qstrKey, p_qstrValue);
}

void CwsHttpBase::AddCookie(CwsCookie p_Cookie)
{
    m_qlCookies.append(p_Cookie);
}

void CwsHttpBase::SetBody(QString p_qstrBody)
{
    m_qstrBody = p_qstrBody;
}

void CwsHttpBase::AddHeadersToString(QString& p_qstrRequest)
{
    QMap<QString, QString>::iterator qmIt = m_qmHeaderInformation.begin();
    QMap<QString, QString>::iterator qmItEnd = m_qmHeaderInformation.end();

    for (;qmIt != qmItEnd; ++qmIt)
    {
       p_qstrRequest += qmIt.key() + ": " + qmIt.value() + "\r\n";
    }
}

void CwsHttpBase::ParseHeaderContent(QString p_qstrHeader)
{
    m_iHeaderLength = p_qstrHeader.length();
    QStringList qstrlHeaders = p_qstrHeader.split("\r\n");

    for(int iPos = 0; iPos < qstrlHeaders.count(); ++iPos)
    {
        QString qstrLine = qstrlHeaders[iPos];

        if (iPos == 0)
        {
            ParseHeadline(qstrLine);
            continue;
        }

        int pos = qstrLine.indexOf(":");
        if (pos >= 0)
        {
            QString qstrKey = qstrLine.mid(0, pos).trimmed();
            QString qstrValue = qstrLine.mid(pos + 1).trimmed();

            if (qstrKey.toLower() == QString(COOKIE).toLower())
            {
                ParseCookies(qstrValue);
            }
            else
            {
                m_qmHeaderInformation.insert(qstrKey, qstrValue);

                if (qstrKey.toLower() == QString(AUTHORIZATION).toLower())
                {
                    QStringList qstrlAuth = qstrValue.split(" ", Qt::SkipEmptyParts);
                    if (qstrlAuth.count() == 2)
                    {
                        SetAuthType(qstrlAuth[0]);
                        SetAuthValue(qstrlAuth[1]);
                    }
                }
            }
        }
        else
        {
            m_qmHeaderInformation.insert(qstrLine, "");
        }
    }
}

void CwsHttpBase::ParseContent()
{
    QString qstrData = QString::fromUtf8(m_qbaContent);
    int iHeaderEnd = qstrData.indexOf("\r\n\r\n");
    if (iHeaderEnd > 0)
    {
        QString qstrHeader = qstrData.left(iHeaderEnd);
        ParseHeaderContent(qstrHeader);
        QString qstrBody = qstrData.mid(iHeaderEnd + 4);
        SetBody(qstrBody);
    }
    else
    {
        ParseHeadline("");
    }

}

QString CwsHttpBase::GetAuthType() const
{
    return m_qstrAuthType;
}

void CwsHttpBase::SetAuthType(QString p_qstrAuthtype)
{
    m_qstrAuthType = p_qstrAuthtype;
}

QString CwsHttpBase::GetAuthValue() const
{
    return m_qstrAuthValue;
}

void CwsHttpBase::SetAuthValue(QString p_qstrAuthtype)
{
    m_qstrAuthValue = p_qstrAuthtype;
}

int CwsHttpBase::GetDocumentLength() const
{
    int iLength = 0;

    if (m_qmHeaderInformation.contains("Content-Length"))
    {
        iLength = GetIntHeader("Content-Length") + m_iHeaderLength + 2;
    }

    return iLength;
}

void CwsHttpBase::CopyContent(QByteArray& p_rResponse)
{
    m_qbaContent = p_rResponse;
}

QString CwsHttpBase::GetServer() const
{
    return m_qstrServer;
}

void CwsHttpBase::SetServer(QString p_qstrServer)
{
    m_qstrServer = p_qstrServer;
}
