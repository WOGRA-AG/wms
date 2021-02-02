#ifndef CWMSSCRIPTABLETIMER_H
#define CWMSSCRIPTABLETIMER_H

// System and Qt Includes
#include <QCache>
#include <QMap>
#include <QPair>


// own Includes
#include "basetools.h"
#include "CwmsScriptableBase.h"


// forwards
class QTimer;
class CsaObject;
class CdmClassMethod;

class BASETOOLS_API CwmsScriptableTimer : public CwmsScriptableBase
{
    Q_OBJECT

private:
    QCache<QString, QTimer> m_qmTimerNameMapping;
    QMap<QTimer*, QPair<QString, QString> > m_qmTimerData;

    QString getRealName(QString p_qstrName);
    void executeStaticFunction(QString p_qstrFunction);
    void executeFunction(QString p_qstrObjectUri, QString p_qstrFunction);
    CdmClassMethod * getMethodObject(QString p_qstrFunction);

private slots:
    void timeout();


public:
    CwmsScriptableTimer();
    virtual ~CwmsScriptableTimer();

public slots:
    QString startTimer(QString p_qstrName, CsaObject* p_pObject, QString p_qstrFunction, int intervall);
    QString startSingleShotTimer(QString p_qstrName, CsaObject* p_pObject, QString p_qstrFunction, int intervall);
    QString startTimer(QString p_qstrName, QString p_qstrFunction, int intervall);
    QString startSingleShotTimer(QString p_qstrName, QString p_qstrFunction, int intervall);
    bool stopTimer(QString p_qstrName);
    bool stopAllTimers();


};

#endif // CWMSSCRIPTABLETIMER_H
