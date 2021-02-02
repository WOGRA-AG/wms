#ifndef CWMSTIMEMEASSUREMENT_H
#define CWMSTIMEMEASSUREMENT_H

#include <QMap>
#include <QTime>

// Own Includes
#include "wmscommons.h"

class WMSCOMMONS_API CwmsTimeMeassurement
{
private:
    QTime m_qTime;
    QMap<QString,int> m_qmTimeRecorder;
    int m_iTaskCounter;
    int m_iElapsed;
    bool m_bPrintResult;
    QString m_qstrMeassurementName;
    static QMap<QString,CwmsTimeMeassurement*> m_qmMeassurements;

public:
    CwmsTimeMeassurement(bool p_bPrintResult, QString p_qstrName);
    CwmsTimeMeassurement(bool p_bPrintResult);
    virtual ~CwmsTimeMeassurement();
    void finishedTask(QString p_qstrTaskName);
    void finished();
    QString getTimeRecorderResult();

    // Use this only in single threaded environments
    static void StartNewMeassurement(QString p_qstrName);
    static void FinishTask(QString p_qstrName, QString p_qstrTask);
    static QString EndMeassurement(QString p_qstrName);
    int GetCompleteDuration() const;
    void start();
    void printResulttoDebugOutput();
};

#endif // CWMSTIMEMEASSUREMENT_H
