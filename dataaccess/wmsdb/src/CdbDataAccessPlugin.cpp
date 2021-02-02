
// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CdbDataAccess.h"
#include "CdbDataAccessConfigurator.h"
#include "CdbDataAccessPlugin.h"

CdbDataAccessPluginImpl::CdbDataAccessPluginImpl()
    : m_pConfigurator(nullptr)
{
}

CdbDataAccessPluginImpl::~CdbDataAccessPluginImpl()
{
    DELPTR(m_pConfigurator);
}

IdmDataAccess* CdbDataAccessPluginImpl::getDbAccess(QString p_qstrApplication)
{
    IdmDataAccess* pDataAccess = nullptr;

    if (!m_pConfigurator)
    {
        m_pConfigurator = new CdbDataAccessConfigurator(p_qstrApplication);
    }

    pDataAccess = new CdbDataAccess();
    ((CdbDataAccess*)pDataAccess)->Init(m_pConfigurator);
    return pDataAccess;
}

QString CdbDataAccessPluginImpl::getVersion()
{
    return "2.1.5";
}

QString CdbDataAccessPluginImpl::getName()
{
    return "Relational Database Access";
}

QObject *CdbDataAccessPluginImpl::getConfigurationObject(QString p_qstrApplication)
{
    if (!m_pConfigurator)
    {
        m_pConfigurator = new CdbDataAccessConfigurator(p_qstrApplication);
    }

    return m_pConfigurator;
}

void CdbDataAccessPluginImpl::openConfigurationEditor(QString p_qstrApplication)
{
    if (!m_pConfigurator)
    {
        m_pConfigurator = new CdbDataAccessConfigurator(p_qstrApplication);
    }

    m_pConfigurator->OpenConfigurator();
}


QString CdbDataAccessPluginImpl::getConfigurationUiName()
{
   return "qrc:/qml/WmsdbDataAccessPlugin.qml";
}

QVariantMap CdbDataAccessPluginImpl::GetConfigurationMap(QString p_qstrApplication)
{
    if (m_pConfigurator)
    {
        DELPTR(m_pConfigurator);
    }

    m_pConfigurator = new CdbDataAccessConfigurator(p_qstrApplication);
    return m_pConfigurator->getValueMap();
}

void CdbDataAccessPluginImpl::SetConfigurationMap(QString p_qstrApplication, QVariantMap& p_rMap)
{
    if (m_pConfigurator)
	{
        DELPTR(m_pConfigurator);
	}

    m_pConfigurator = new CdbDataAccessConfigurator(p_qstrApplication);
	return m_pConfigurator->setValueMap(p_rMap);
}
