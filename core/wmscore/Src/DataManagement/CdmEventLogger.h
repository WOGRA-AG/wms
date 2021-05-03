#ifndef CDMEVENTLOGGER_H
#define CDMEVENTLOGGER_H

// Sytsem and QT Includes
#include <QString>
#include <QList>
#include <QTextStream>
#include <QFile>
#include <QMutex>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// own Includes
#include "datamanager.h"

class WMSMANAGER_API CdmEventLogger : public CwmsSynchronizable
{
private:
    QFile m_logFile;

    static CdmEventLogger* ms_pCdmEventLogger;

    static QString m_qstrOutputFormat;

public:
    CdmEventLogger(QString qstrFileName,
                   QString p_qstrApplicationName,
                   QString p_qstrVersion);
    ~CdmEventLogger();

    static void CreateLoggingManager(QString qstrFileName,
                                     QString p_qstrApplicationName,
                                     QString p_qstrVersion);
    static void DestroyLoggingManager();
    static CdmEventLogger *getEventLogger();

    static void AddLog(QString p_qstrEventTextFirstPart,
                QString p_qstrEventTextSecondPart);

private:
    void WriteToLogFile(QString qstrMessage);
};

#endif // CDMEVENTLOGGER_H
