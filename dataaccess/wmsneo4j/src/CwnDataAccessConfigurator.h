#ifndef CWNDATAACCESSCONFIGURATOR_H
#define CWNDATAACCESSCONFIGURATOR_H

// System and QT Includes
#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariantMap>
#include <QVariant>
#include <QStringList>


// Own Includes

// Forwards
class QQmlApplicationEngine;
class QQuickWindow;

class CwnDataAccessConfigurator : public QObject
{
   Q_OBJECT

private:
    QString m_qstrApplicationName;
    QSettings* m_pSettings;
    QQmlApplicationEngine* m_pEngine;
    void getMapInitValues(QVariantMap& qMap, QVariantMap& qValues);
    QQuickWindow *CreateView();
public:
    CwnDataAccessConfigurator(QString p_qstrApplicationName);
    virtual ~CwnDataAccessConfigurator();
    void OpenConfigurator();
public slots:

    QString getServer();
    void setServer(QString p_qstrServer);

    QVariant getSettingsValue(QString p_qstrKey);
    void setSettingsValue(QString p_qstrKey, QVariant p_qValue);

    int getPort();
    void setPort(int p_iPort);
    QString getUser();
    void setUser(QString p_qstrUser);
    QString getPassword();
    void setPassword(QString p_qstrPassword);


    QVariantMap getValueMap();
    void setValueMap(QVariantMap& p_rqMap);
};
#endif
