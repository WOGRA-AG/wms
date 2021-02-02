// System and Qt includes
#include <QCoreApplication>
#include <QFileInfo>
#include <QLibrary>
#include <qmessagebox.h>
#include <QFileInfoList>
#include <QPluginLoader>
#include <QDir>
#include <QSettings>

// WMS Commons Includes
#include "wmsdefines.h"
#include "CwmsSettingsStoreFactory.h"

// WMS includes
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// Data Access Plugins Includes
#ifdef WMS_LINK_DATAACCESS_STATIC
#include "CdbDataAccessPlugin.h"
#include "CslDataAccessPlugin.h"
#include "CwcDataAccessPlugin.h"
#endif

// own Includes
#include "CwmsDataAccessConfiguration.h"

CwmsDataAccessConfiguration::CwmsDataAccessConfiguration()
: CdmDataAccessConfiguration()
{

}

CwmsDataAccessConfiguration::~CwmsDataAccessConfiguration()
{

}

QStringList CwmsDataAccessConfiguration::getDataAccessList()
{
#ifdef WMS_LINK_DATAACCESS_STATIC
    return getStaticDataAccessList();
#else
    return getDynamicDataAccessList();
#endif
}

QString CwmsDataAccessConfiguration::getConfigurationPluginName(QString p_qstrConfig)
{
    QString qstrPlguin;
    QSettings* pSettings = CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings(p_qstrConfig);

    if (CHKPTR(pSettings))
    {
        qstrPlguin = pSettings->value(DATA_ACCESS_PLUGIN_NAME).toString();
        DELPTR(pSettings);
    }

    return qstrPlguin;
}

void CwmsDataAccessConfiguration::setConfigurationPluginName(QString p_qstrConfig, QString p_qstrPlugin)
{
    QSettings* pSettings = CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings(p_qstrConfig);

    if (CHKPTR(pSettings))
    {
        pSettings->setValue(DATA_ACCESS_PLUGIN_NAME, p_qstrPlugin);
        pSettings->setValue(DATA_ACCESS_PLUGIN_FILE, m_qmDataAccessFilenames[p_qstrPlugin]);
        DELPTR(pSettings);
    }
}

void CwmsDataAccessConfiguration::deleteConfiguration(QString p_qstrConfig)
{
    QSettings* pSettings = CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings();

    if (CHKPTR(pSettings))
    {
        pSettings->remove(p_qstrConfig);
        DELPTR(pSettings);
    }
}

QStringList CwmsDataAccessConfiguration::getConfigurationList()
{
    QStringList qstrlConfigs;

    QSettings* pSettings = CwmsSettingsStoreFactory::GenerateDatAccessConfigSettings();

    if (CHKPTR(pSettings))
    {
        qstrlConfigs << pSettings->childGroups();
        DELPTR(pSettings);
    }

    return qstrlConfigs;
}

QStringList CwmsDataAccessConfiguration::getStaticDataAccessList()
{
#ifdef WMS_LINK_DATAACCESS_STATIC
    IwmsDataAccessPlugin* pPlugin = new CdbDataAccessPluginImpl();
    addPlugin(pPlugin, "");

    pPlugin = new CslDataAccessPluginImpl();
    addPlugin(pPlugin, "");

    pPlugin = new CwcDataAccessPluginImpl();
    addPlugin(pPlugin, "");

    // TODO: Add Neo4J Plugin

    // Here you have to add further dataaccesses for static linking

#endif
    return m_qstrlDataAccess;
}

void CwmsDataAccessConfiguration::addPlugin(IwmsDataAccessPlugin* pPlugin, QString p_qstrFilename)
{
	QString qstrName = pPlugin->getName();
	QString qstrVersion = pPlugin->getVersion();
	QString qstrDisplayName = qstrName + " [" + qstrVersion + "]";
    m_qmDataAccess.insert(qstrDisplayName, pPlugin);

    if (!p_qstrFilename.isEmpty())
    {
        m_qmDataAccessFilenames.insert(qstrDisplayName, p_qstrFilename);
    }
    else
    {
        m_qmDataAccessFilenames.insert(qstrDisplayName, qstrDisplayName);
    }
	m_qstrlDataAccess.append(qstrDisplayName);
}

QStringList CwmsDataAccessConfiguration::getDynamicDataAccessList()
{
    QString qstrPluginsPath;
#ifndef Q_OS_IOS
#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + DATAACCESS_PLUGIN_PATH;
#endif

    QDir qPluginsDir(qstrPluginsPath);
    QFileInfoList qlEntries = qPluginsDir.entryInfoList(QDir::Files);

    if (m_qstrlDataAccess.count() == 0)
    {
       for (int iCounter = 0; iCounter < qlEntries.count(); ++iCounter)
       {
          QFileInfo qfInfo = qlEntries[iCounter];

          if (!qfInfo.isSymLink() && QLibrary::isLibrary(qfInfo.absoluteFilePath()))
          {
             QString qstrFile = qfInfo.absoluteFilePath();
             QPluginLoader qLoader(qstrFile);

             if (qLoader.isLoaded() || qLoader.load())
             {
                QObject* pObject = qLoader.instance();
                IwmsDataAccessPlugin* pPlugin = qobject_cast<IwmsDataAccessPlugin*>(pObject);

                if (CHKPTR(pPlugin))
                {
                    addPlugin(pPlugin, qfInfo.fileName());
                }
             }
             else
             {
				 QMessageBox::warning(nullptr, "Fehler beim Laden eines Plugins", qLoader.errorString());
                WARNING(qApp->tr("Fehler beim Laden eines Plugins\n") + qLoader.errorString());
             }
         }
         else
         {
            WARNING("File is a symbolic link and will be ignored. Filename: " + qfInfo.fileName());
         }
       }
    }
#endif
    return m_qstrlDataAccess;
}
