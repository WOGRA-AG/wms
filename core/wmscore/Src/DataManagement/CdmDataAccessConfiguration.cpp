// System and QT Includes
#include <QSettings>
#include <QVariant>
#include <QPluginLoader>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QStringList>

// WMSCommons Incldues
#include "wmsdefines.h"
#include "CwmsSettingsStoreFactory.h"

// WMS Manager Includes
#include "CdmSettings.h"
#include "CdmLogging.h"
#include "CdmSessionManager.h"
#include "CdmGlobalContext.h"
#include "CdmDataAccessConfiguration.h"

CdmDataAccessConfiguration::CdmDataAccessConfiguration()
{
}

CdmDataAccessConfiguration::~CdmDataAccessConfiguration()
{
}

QStringList CdmDataAccessConfiguration::getDataAccessList()
{
#ifndef Q_OS_IOS
    QString qstrPluginsPath;

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

          if (!qfInfo.isSymLink())
          {
             QString qstrFile = qfInfo.absoluteFilePath();
			 QPluginLoader qLoader(qstrFile);

             if (qLoader.load())
             {
                QObject* pObject = qLoader.instance();
                IwmsDataAccessPlugin* pPlugin = qobject_cast<IwmsDataAccessPlugin*>(pObject);

                if (CHKPTR(pPlugin))
                {
					QString qstrName = pPlugin->getName();
                    QString qstrVersion = pPlugin->getVersion();
                    QString qstrDisplayName = qstrName + " [" + qstrVersion + "]";
                    m_qmDataAccess.insert(qstrDisplayName, pPlugin);
                    m_qmDataAccessFilenames.insert(qstrDisplayName, qfInfo.fileName());
                    m_qstrlDataAccess.append(qstrDisplayName);
                }
                else
                {
                    DELPTR(pObject);
                }
             }
             else
             {
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

int CdmDataAccessConfiguration::getCurrentDataAccessConfigurationIndex()
{
   QString qstrDataAccess = getCurrentDataAccessConfiguration();
   QMap<QString, QString>::iterator qmIt = m_qmDataAccessFilenames.begin();
   QMap<QString, QString>::iterator qmItEnd = m_qmDataAccessFilenames.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
	   if (qmIt.value() == qstrDataAccess)
	   {
		   qstrDataAccess = qmIt.key();
		   break;
	   }
   }

   return getDataAccessList().indexOf(qstrDataAccess);
}


QString CdmDataAccessConfiguration::getCurrentDataAccessConfiguration()
{
    return GetCurrentDataAccessPluginName();
}

void CdmDataAccessConfiguration::setDataAccessConfiguration(QString p_qstrDataAccess)
{
    QSettings* pSettings = GetDataAccessSettings();

    if (CHKPTR(pSettings))
    {
        if (m_qmDataAccessFilenames.contains(p_qstrDataAccess))
        {
           pSettings->setValue(DATA_ACCESS_PLUGIN, m_qmDataAccessFilenames[p_qstrDataAccess]);
        }

        DELPTR(pSettings);
    }
}

void CdmDataAccessConfiguration::openDataAccessConfiguration(QString p_qstrDataAccess)
{
    IwmsDataAccessPlugin* pPlugin = m_qmDataAccess[p_qstrDataAccess];

    if (CHKPTR(pPlugin))
    {
        QSettings* pSettings = GetSettings();

        if (CHKPTR(pSettings))
        {
            QString qstrConfigName = pSettings->value(DATA_ACCESS_CONFIG).toString();
            pPlugin->openConfigurationEditor(qstrConfigName);
            DELPTR(pSettings);
        }
    }
}

QObject* CdmDataAccessConfiguration::getDataAccessConfiguration(QString p_qstrDataAccess)
{
    QObject* pConfig = nullptr;
    IwmsDataAccessPlugin* pPlugin = m_qmDataAccess[p_qstrDataAccess];

    if (CHKPTR(pPlugin))
    {
        QSettings* pSettings = GetSettings();

        if (CHKPTR(pSettings))
        {
            QString qstrConfigName = pSettings->value(DATA_ACCESS_CONFIG).toString();
            pConfig = pPlugin->getConfigurationObject(qstrConfigName);
            DELPTR(pSettings);
        }
    }

    return pConfig;
}

IwmsDataAccessPlugin* CdmDataAccessConfiguration::getDataAccessPlugin(QString p_qstrDataAccess)
{
    return m_qmDataAccess[p_qstrDataAccess];
}

QString CdmDataAccessConfiguration::getDataAccessConfigurationFilename(QString p_qstrDataAccess)
{
   QString qstrFilename;

   IwmsDataAccessPlugin* pPlugin = m_qmDataAccess[p_qstrDataAccess];

   if (CHKPTR(pPlugin))
   {
      qstrFilename = pPlugin->getConfigurationUiName();
   }

   return qstrFilename;
}

IdmDataAccess* CdmDataAccessConfiguration::EstablishConnection()
{
    IdmDataAccess* pDataAccess = nullptr;

#ifndef Q_OS_IOS
    QString qstrPluginFilename = ReadConfigFile();
    QString qstrPluginsPath;

#ifdef Q_OS_ANDROID
    qstrPluginsPath = qApp->applicationDirPath();
#else
    qstrPluginsPath = qApp->applicationDirPath() + DATAACCESS_PLUGIN_PATH;
#endif

    qstrPluginFilename = qstrPluginsPath + "/" + qstrPluginFilename;
    QPluginLoader qLoader(qstrPluginFilename);

    if (qLoader.load())
    {
       QObject* pObject = qLoader.instance();
       IwmsDataAccessPlugin* pPlugin = qobject_cast<IwmsDataAccessPlugin*>(pObject);

        if (CHKPTR(pPlugin))
        {
            QString qstrName = pPlugin->getName();
            QString qstrVersion = pPlugin->getVersion();
            QString qstrDisplayName = qstrName + " [" + qstrVersion + "]";

            INFO("Plugin found:" + qstrDisplayName);

            pDataAccess = pPlugin->getDbAccess(ReadConfigName());
        }
        else
        {
            ERR("Error while loading Plugin. This is not a valid Data Access Plugin\n" + qLoader.errorString());
        }
    }
    else
    {
       ERR("Error while loading Plugin. This is not a valid Plugin. " + qLoader.errorString());
    }
#endif
   return pDataAccess;
}

QString CdmDataAccessConfiguration::ReadConfigName()
{
    QString qstrConfigName;

    if (CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetMode() == eDmSettingsModeClient)
    {
        qstrConfigName = CwmsSettingsStoreFactory::ReadDataAccessConfigName(eWmsSettingsConfigTypeClient);
    }
    else
    {
        qstrConfigName = CwmsSettingsStoreFactory::ReadDataAccessConfigName(eWmsSettingsConfigTypeServer);
    }

    return qstrConfigName;
}

QString CdmDataAccessConfiguration::ReadConfigFile()
{
    QString qstrConfigName;

    if (CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetMode() == eDmSettingsModeClient)
    {
        qstrConfigName = CwmsSettingsStoreFactory::ReadDataAccessConfigFile(eWmsSettingsConfigTypeClient);
    }
    else
    {
        qstrConfigName = CwmsSettingsStoreFactory::ReadDataAccessConfigFile(eWmsSettingsConfigTypeServer);
    }

    return qstrConfigName;
}

void CdmDataAccessConfiguration::SetConfigName(QString p_qstrConfig)
{
    if (CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetMode() == eDmSettingsModeClient)
    {
        CwmsSettingsStoreFactory::SetDataAccessConfigName(eWmsSettingsConfigTypeClient, p_qstrConfig);
    }
    else
    {
        CwmsSettingsStoreFactory::SetDataAccessConfigName(eWmsSettingsConfigTypeServer, p_qstrConfig);
    }
}

QSettings* CdmDataAccessConfiguration::GetDataAccessSettings()
{
    QSettings* pSettings = nullptr;

    if (CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetMode() == eDmSettingsModeClient)
    {
        pSettings = CwmsSettingsStoreFactory::GenerateClientDataAccessSettings();
    }
    else
    {
        pSettings = CwmsSettingsStoreFactory::GenerateServerDataAccessSettings();
    }

    return pSettings;
}


QSettings* CdmDataAccessConfiguration::GetSettings()
{
    QSettings* pSettings = nullptr;

    if (CdmSessionManager::GetSessionManager()->GetGlobalContext()->GetMode() == eDmSettingsModeClient)
    {
        pSettings = CwmsSettingsStoreFactory::GenerateClientSettings();
    }
    else
    {
        pSettings = CwmsSettingsStoreFactory::GenerateServerSettings();
    }

    return pSettings;
}

QString CdmDataAccessConfiguration::GetCurrentDataAccessPluginName()
{
    QString qstrConfig;
    QSettings* pSettings = GetDataAccessSettings();

    if (CHKPTR(pSettings))
    {
        qstrConfig = pSettings->value(DATA_ACCESS_PLUGIN_NAME).toString();

        if (qstrConfig.isEmpty())
        {
           QString qstrKeysFound = pSettings->allKeys().join("\n");
           QString qstrGroup = pSettings->group();
           QString qstrScope;

           if (pSettings->scope() == QSettings::SystemScope)
           {
               qstrScope = "System";
           }
           else
           {
               qstrScope = "User";
           }

           QString qstrMessage = "Key not found. Keyname: DataAccessPlugin Group: " + qstrGroup + " Scope: " + qstrScope + " Keys found:\n" + qstrKeysFound + "\n";
           ERR(qstrMessage);
           qstrConfig = "Local File Database Access";
        }

        DELPTR(pSettings);
    }

    return qstrConfig;
}

