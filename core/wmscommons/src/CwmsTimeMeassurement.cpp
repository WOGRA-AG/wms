#include <QDebug>

#include "CwmsTimeMeassurement.h"


QMap<QString,CwmsTimeMeassurement*> CwmsTimeMeassurement::m_qmMeassurements;

CwmsTimeMeassurement::CwmsTimeMeassurement(bool p_bPrintResult, QString p_qstrName)
: m_iTaskCounter(0),
  m_iElapsed(0),
  m_bPrintResult(p_bPrintResult),
  m_qstrMeassurementName(p_qstrName)
{
    start();
}

CwmsTimeMeassurement::CwmsTimeMeassurement(bool p_bPrintResult)
    : m_iTaskCounter(0),
      m_iElapsed(0),
      m_bPrintResult(p_bPrintResult),
      m_qstrMeassurementName("")
{
    start();
}

CwmsTimeMeassurement::~CwmsTimeMeassurement()
{
    finished();
    printResulttoDebugOutput();
}

void CwmsTimeMeassurement::printResulttoDebugOutput()
{
    if (m_bPrintResult && m_iElapsed > 0)
    {
        QString qstrTimestamp = QDateTime::currentDateTime().toString();
        qDebug() << m_qstrMeassurementName << " " << qstrTimestamp << (" Timerecorder result:\n" + getTimeRecorderResult());
    }
}

void CwmsTimeMeassurement::start()
{
    m_iTaskCounter = 0;
    m_iElapsed = 0;
    m_qmTimeRecorder.clear();
    m_qTime.start();
}

void CwmsTimeMeassurement::finishedTask(QString p_qstrTaskName)
{
    int iElapsed = m_qTime.elapsed();
    m_iElapsed += iElapsed;
    m_qmTimeRecorder.insert(QString("%1").arg(++m_iTaskCounter, 2) + " - " + p_qstrTaskName, iElapsed);
    m_qTime.start();
}

void CwmsTimeMeassurement::finished()
{
    int iElapsed = m_qTime.elapsed();
    m_iElapsed += iElapsed;
    m_qmTimeRecorder.insert(QString("%1").arg(++m_iTaskCounter, 2) + " - Finished Operation Complete Duration", m_iElapsed);
}

QString CwmsTimeMeassurement::getTimeRecorderResult()
{
    QString qstrResult;
    QMapIterator<QString,int> qmIt(m_qmTimeRecorder);

    while (qmIt.hasNext())
    {
        qmIt.next();
        qstrResult += "Task: " + qmIt.key() + " Duration: " + QString::number(qmIt.value()) + " mSecs";

        if (qmIt.hasNext())
        {
            qstrResult += "\n";
        }
    }

    return qstrResult;
}

int CwmsTimeMeassurement::GetCompleteDuration() const
{
    return m_iElapsed;
}

void CwmsTimeMeassurement::StartNewMeassurement(QString p_qstrName)
{
    m_qmMeassurements.insert(p_qstrName, new CwmsTimeMeassurement(true, p_qstrName));
}

void CwmsTimeMeassurement::FinishTask(QString p_qstrName, QString p_qstrTask)
{
    if (m_qmMeassurements.contains(p_qstrName))
    {
        CwmsTimeMeassurement* pMeassurement = m_qmMeassurements[p_qstrName];
        pMeassurement->finishedTask(p_qstrTask);
    }
}

QString CwmsTimeMeassurement::EndMeassurement(QString p_qstrName)
{
    QString qstrResult;

    if (m_qmMeassurements.contains(p_qstrName))
    {
        CwmsTimeMeassurement* pMeassurement = m_qmMeassurements[p_qstrName];
        pMeassurement->finished();
        qstrResult = pMeassurement->getTimeRecorderResult();
        m_qmMeassurements.remove(p_qstrName);
        delete pMeassurement;
    }

    return qstrResult;
}
