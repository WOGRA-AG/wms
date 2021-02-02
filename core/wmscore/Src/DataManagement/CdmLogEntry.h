/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMERRORENTRY_H
#define CDMERRORENTRY_H

// System and QT Includes
#include <QDateTime>

// own Includes
#include "datamanager.h"
#include "CdmLogging.h"

class WMSMANAGER_API CdmLogEntry
{
    public:
    EdmErrorSeverity m_eDmErrorSeverity;
    QString m_qstrErrorModule;
    QString m_qstrEventText;
    int m_iLine;
    QDateTime m_qdtTimestamp;
    int m_iSessionId;


    public:
    CdmLogEntry(int p_iSessionId,
                  QDateTime p_qdtTimestamp,
                  EdmErrorSeverity p_eDmErrorSeverity,
                  QString p_qstrErrorModule,
                  QString p_qstrEventText,
                  int p_iLine);

    ~CdmLogEntry();

    EdmErrorSeverity GetErrorSeverity() const;
    QString GetErrorModule() const;
    QString GetEventText() const;
    int GetLine() const;
    QDateTime GetTimestamp() const;
    QString GetSeverityAsString() const;
    int GetSessionId() const;
    QString ToString() const;
    QVariant toJson() const;
};

#endif //
