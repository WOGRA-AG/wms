#ifndef CWMSLOGGERCONSOLE_H
#define CWMSLOGGERCONSOLE_H

// System and Qt Includes
#include <QTextStream>

// WMS Includes
#include "CdmLogEntry.h"
#include "CdmLoggingAdaptor.h"

// own Includes
#include "basetools.h"

class BASETOOLS_API CwmsLoggerConsole : public CdmLoggingAdaptor
{
private:
      QString m_qstrOutputFormat;
      QTextStream m_stream;
public:
    CwmsLoggerConsole(QString p_qstrApplicationName, QString p_qstrVersion);
    virtual ~CwmsLoggerConsole();
    virtual void AddError(CdmLogEntry& p_eEntry);
    virtual void AddInfo(CdmLogEntry& p_eEntry);
    virtual void AddWarning(CdmLogEntry& p_eEntry);
    virtual void AddFatal(CdmLogEntry& p_eEntry);
    virtual void AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode);
    QString GetOutputFormat() const;
    void SetOutputFormat(const QString &qstrOutputFormat);

};

#endif // CWMSLOGGERCONSOLE_H
