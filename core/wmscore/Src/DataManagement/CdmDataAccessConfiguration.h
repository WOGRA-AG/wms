#ifndef CDMQMLDATAACCESSCONFIGURATION_H
#define CDMQMLDATAACCESSCONFIGURATION_H

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QStringListModel>

// WMS Includes
#include "IwmsDataAccessPlugin.h"

// own Includes
#include "datamanager.h"
#include "CdmSettings.h"


// is abstract because we cannot have dependencies to dataaccess plugins in
// wms. See CwmsDataAccessConfiguration in basetools
class WMSMANAGER_API CdmDataAccessConfiguration : public QObject
{
    Q_OBJECT

    static QSettings *GetDataAccessSettings();
    QSettings *GetSettings();

protected:
    QMap<QString, IwmsDataAccessPlugin*> m_qmDataAccess;
    QMap<QString, QString> m_qmDataAccessFilenames;
    QStringList m_qstrlDataAccess;

public:

    CdmDataAccessConfiguration();
    ~CdmDataAccessConfiguration();
    QObject *getDataAccessConfiguration(QString p_qstrDataAccess);
    IwmsDataAccessPlugin *getDataAccessPlugin(QString p_qstrDataAccess);
    static IdmDataAccess *EstablishConnection();
    static QString GetCurrentDataAccessPluginName();
    static QString ReadConfigName();
    void SetConfigName(QString p_qstrConfig);
    static QString ReadConfigFile();
public slots:
    int getCurrentDataAccessConfigurationIndex();
    virtual QStringList getDataAccessList() = 0;
    void openDataAccessConfiguration(QString p_qstrDataAccess);
    QString getCurrentDataAccessConfiguration();
    void setDataAccessConfiguration(QString p_qstrDataAccess);
    QString getDataAccessConfigurationFilename(QString p_qstrDataAccess);
};

#endif 
