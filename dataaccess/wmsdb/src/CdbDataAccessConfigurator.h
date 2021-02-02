#ifndef CODBCDATAACCESSCONFIGURATOR_H
#define CODBCDATAACCESSCONFIGURATOR_H

// System and QT Includes
#include <QObject>
#include <QSettings>

// Own Includes

// Forwards
class QQmlApplicationEngine;
class QQuickWindow;

class CdbDataAccessConfigurator : public QObject
{
   Q_OBJECT

private:
    QString m_qstrApplicationName;
    QSettings* m_pSettings;
    QQmlApplicationEngine* m_pEngine;
    void getMapInitValues(QVariantMap& qMap, QVariantMap& qValues);
    QQuickWindow *CreateView();
public:
    CdbDataAccessConfigurator(QString p_qstrApplicationName);
    virtual ~CdbDataAccessConfigurator();
    void OpenConfigurator();
public slots:
    QString getServer();
    void setServer(QString p_qstrServer);
    QVariant getSettingsValue(QString p_qstrKey);
    void setSettingsValue(QString p_qstrKey, QVariant p_qValue);
    QString getDriver();
    int getDriverIndex();
    void setDriver(QString p_qstrDriver);
    QString getDatabase();
    void setDatabase(QString p_qstrDatabase);
    void setConnectOptions(QString p_qstrConnectOptions);
    QString getConnectOptions();
    int getPort();
    void setPort(int p_iPort);
    QString getUser();
    void setUser(QString p_qstrUser);
    QString getPassword();
    void setPassword(QString p_qstrPassword);
    bool testDatabaseConnection(QString p_qstrHost,
                                QString p_qstrDatabase,
                                int p_iPort,
                                QString p_qstrDriver,
                                QString p_qstrUsername,
                                QString p_qstrPassword,
                                QString p_qstrConfig);

    QStringList getDrivers();
	QVariantMap getValueMap();
	void setValueMap(QVariantMap& p_rqMap);
};

#endif
