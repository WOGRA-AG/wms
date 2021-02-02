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
#include <QDateTime>

// own Includes
#include "CdmLogEntry.h"


CdmLogEntry::CdmLogEntry(int p_iSessionId, QDateTime p_qdtTimestamp, EdmErrorSeverity p_eDmErrorSeverity, QString p_qstrErrorModule, QString p_qstrEventText, int p_iLine)
: m_eDmErrorSeverity(p_eDmErrorSeverity),
  m_qstrErrorModule(p_qstrErrorModule),
  m_qstrEventText(p_qstrEventText),
  m_iLine(p_iLine),
  m_qdtTimestamp(p_qdtTimestamp),
  m_iSessionId(p_iSessionId)
{
}

CdmLogEntry::~CdmLogEntry()
{
}

int CdmLogEntry::GetSessionId() const
{
    return m_iSessionId;
}

QString CdmLogEntry::ToString() const
{
    QString qstrOutputFormat = "%1;%2;%3;%4;%5;"; // CSV Format
    QString qstrRet = QString(qstrOutputFormat)
            .arg(GetTimestamp().toString())
            .arg(GetSeverityAsString())
            .arg(GetErrorModule())
            .arg(GetLine())
            .arg(GetEventText());
    return qstrRet;
}

QVariant CdmLogEntry::toJson() const
{
    QVariantMap qvmJson;
    qvmJson.insert("Timestamp", GetTimestamp());
    qvmJson.insert("Module", GetErrorModule() );
    qvmJson.insert("Severity", GetSeverityAsString());
    qvmJson.insert("Message", GetEventText());
    qvmJson.insert("Linenumber", GetLine());
    qvmJson.insert("SessionId", GetSessionId());
    return qvmJson;
}

QDateTime CdmLogEntry::GetTimestamp() const
{
    return m_qdtTimestamp;
}

QString CdmLogEntry::GetSeverityAsString() const
{
    QString qstrSeverity;

    switch(GetErrorSeverity())
    {
    case eDmInfo:
       qstrSeverity += "INFO";
       break;
    case eDmWarning:
       qstrSeverity += "WARNING";
       break;
    case eDmError:
       qstrSeverity += "ERROR";
       break;
    case eDmFatal:
       qstrSeverity += "FATAL";
       break;
    default:
       qstrSeverity += "UNKNOWN";
    }

    return qstrSeverity;
}


EdmErrorSeverity CdmLogEntry::GetErrorSeverity() const
{
    return m_eDmErrorSeverity;
}

QString CdmLogEntry::GetErrorModule() const
{
    return m_qstrErrorModule;
}

QString CdmLogEntry::GetEventText() const
{
    return m_qstrEventText;
}

int CdmLogEntry::GetLine() const
{
    return m_iLine;
}
