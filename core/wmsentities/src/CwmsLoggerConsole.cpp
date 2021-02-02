#include "CwmsLoggerConsole.h"

CwmsLoggerConsole::CwmsLoggerConsole(QString p_qstrApplicationName, QString p_qstrVersion)
    : CdmLoggingAdaptor(),
      m_qstrOutputFormat("%1 %2: %3 %4 %5"),
      m_stream(stdout, QIODevice::WriteOnly)
{
    if (p_qstrApplicationName.isEmpty())
    {
       p_qstrApplicationName = "WMS Client Or Server";
    }

    if (p_qstrVersion.isEmpty())
    {
       p_qstrVersion = "Unknown Version";
    }

    m_stream << p_qstrApplicationName + " " + p_qstrVersion + " started." << endl;
    m_stream.flush();
    }

CwmsLoggerConsole::~CwmsLoggerConsole()
{

}

void CwmsLoggerConsole::AddError(CdmLogEntry &p_eEntry)
{
    QString qstrMessage;
    qstrMessage = QString(m_qstrOutputFormat)
            .arg(p_eEntry.GetTimestamp().toString())
            .arg(p_eEntry.GetSeverityAsString())
            .arg(p_eEntry.GetErrorModule())
            .arg(p_eEntry.GetLine())
            .arg(p_eEntry.GetEventText());
    m_stream << qstrMessage << endl;
    m_stream.flush();
}

void CwmsLoggerConsole::AddInfo(CdmLogEntry &p_eEntry)
{
    QString qstrMessage;
    qstrMessage = QString(m_qstrOutputFormat)
            .arg(p_eEntry.GetTimestamp().toString())
            .arg(p_eEntry.GetSeverityAsString())
            .arg(p_eEntry.GetErrorModule())
            .arg(p_eEntry.GetLine())
            .arg(p_eEntry.GetEventText());
    m_stream << qstrMessage << endl;
    m_stream.flush();
}

void CwmsLoggerConsole::AddWarning(CdmLogEntry &p_eEntry)
{
    QString qstrMessage;
    qstrMessage = QString(m_qstrOutputFormat)
            .arg(p_eEntry.GetTimestamp().toString())
            .arg(p_eEntry.GetSeverityAsString())
            .arg(p_eEntry.GetErrorModule())
            .arg(p_eEntry.GetLine())
            .arg(p_eEntry.GetEventText());
    m_stream << qstrMessage << endl;
    m_stream.flush();
}

void CwmsLoggerConsole::AddFatal(CdmLogEntry &p_eEntry)
{
    QString qstrMessage;
    qstrMessage = QString(m_qstrOutputFormat)
            .arg(p_eEntry.GetTimestamp().toString())
            .arg(p_eEntry.GetSeverityAsString())
            .arg(p_eEntry.GetErrorModule())
            .arg(p_eEntry.GetLine())
            .arg(p_eEntry.GetEventText());
    m_stream << qstrMessage << endl;
    m_stream.flush();
}

void CwmsLoggerConsole::AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)
{
    Q_UNUSED(p_qdtTimeStamp);
    Q_UNUSED(p_iCode);
}

QString CwmsLoggerConsole::GetOutputFormat() const
{
    return m_qstrOutputFormat;
}

void CwmsLoggerConsole::SetOutputFormat(const QString &qstrOutputFormat)
{
    m_qstrOutputFormat = qstrOutputFormat;
}
