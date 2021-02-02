#ifndef CWMSINITAPPLICATION_H
#define CWMSINITAPPLICATION_H

// System and QT Includes
#include <QObject>     // reason base class QObject

// own includes
#include "basetools.h" // reason: definition of BASETOOLS_API

// enums

enum EinitState
{
    eInitStateLogging,
    eInitStateLogin,
    eInitStateDbSelection,
    eInitStateApplicationSelection,
    eInitStateApplicationStart,
    eInitStateFinished,
    eInitStateCanceled
};

// classes

class BASETOOLS_API CwmsInitApplication : public QObject
{
    Q_OBJECT

private:
    EinitState m_eState;
protected:
    QString m_qstrApplicationName;
    QString m_qstrVersion;
    QString m_qstrWmsStartApplication;

private:
    void Continue();
public:
    CwmsInitApplication(QString p_qstrApplicationName, QString p_qstrVersion);
    virtual ~CwmsInitApplication();
    void InitApplication();
    QString GetApplication() { return m_qstrApplicationName; }
    QString GetVersion() { return m_qstrVersion; }
    QString GetApplicationAndVersionName() { return GetApplication() + QStringLiteral(" V ") + GetVersion(); }
    void SetApplication(QString p_qstrName) { m_qstrApplicationName = p_qstrName; }
    void SetWmsStartApplication(const QString &qstrWmsStartApplication);
    EinitState GetState() { return m_eState; }
    static void StartMainFunction(QString p_qstrFunction);

protected:
    virtual void Canceled();
    virtual void Finished();
    virtual void ApplicationStart();
    virtual void ApplicationSelection();
    virtual void DbSelection();
    virtual void Login();
    virtual void Logging();

public slots:
    void StateFinished(bool p_bSuccess);
};

#endif // CWMSINITAPPLICATION_H
