#ifndef CWMSSERVERSETTINGS_H
#define CWMSSERVERSETTINGS_H

// System and QT Includes
#include <QSettings>
#include <QString>

// Own Includes
#include "basetools.h"

// Forwards
class QWindow;

// Macros
#define SERVER_APP_NAME "Webserver"

class BASETOOLS_API CwmsServerSettings
{


private:
    QSettings* m_pSettings;
    QString m_qstrEntryPrefix;
    QVariantMap getMapInitValues();

public:
    CwmsServerSettings();
    virtual ~CwmsServerSettings();
    void setValueMap(QVariantMap &p_rqMap);
    QVariantMap getValueMap();
    void setSettingsValue(QString p_qstrKey, QVariant p_qValue);
    QVariant getSettingsValue(QString p_qstrKey);
    void dataSourceClickedSlot();
    QString getLoggingPath();
    bool getLoggingInformation();
    bool getLoggingError();
    bool getLoggingWarning();
    bool getLoggingFatal();
    bool getLoggingActive();
    bool getMaxTrials();
    bool getSsl();
    bool getCompression();
    bool getMultiThreaded();
    int getPort();
    int getConfigMaxThreadCount();
    QString getServerUser();
    QString getServerUserPassword();
};

#endif // // CWMSSERVERSETTINGS_H
