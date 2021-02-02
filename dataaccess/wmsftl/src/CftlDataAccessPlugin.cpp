
// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CftlDataAccess.h"
#include "CftlDataAccessConfigurator.h"
#include "CftlDataAccessPlugin.h"

CftlDataAccessPluginImpl::CftlDataAccessPluginImpl()
    : m_pConfigurator(nullptr)
{
}

CftlDataAccessPluginImpl::~CftlDataAccessPluginImpl()
{
    DELPTR(m_pConfigurator);
}

IdmDataAccess* CftlDataAccessPluginImpl::getDbAccess(QString p_qstrApplication)
{
    IdmDataAccess* pDataAccess = nullptr;

    if (!m_pConfigurator)
    {
        m_pConfigurator = new CftlDataAccessConfigurator(p_qstrApplication);
    }

    pDataAccess = new CftlDataAccess();
    ((CftlDataAccess*)pDataAccess)->Init(m_pConfigurator);
    return pDataAccess;
}

QString CftlDataAccessPluginImpl::getVersion()
{
    return "1.0.0";
}

QString CftlDataAccessPluginImpl::getName()
{
    return "FTL Database Access";
}

QObject *CftlDataAccessPluginImpl::getConfigurationObject(QString p_qstrApplication)
{
    if (m_pConfigurator)
    {
        DELPTR(m_pConfigurator);
    }

    m_pConfigurator = new CftlDataAccessConfigurator(p_qstrApplication);
    return m_pConfigurator;
}

void CftlDataAccessPluginImpl::openConfigurationEditor(QString p_qstrApplication)
{
    if (!m_pConfigurator)
    {
        m_pConfigurator = new CftlDataAccessConfigurator(p_qstrApplication);
    }

    m_pConfigurator->OpenConfigurator();
}


QString CftlDataAccessPluginImpl::getConfigurationUiName()
{
   return "qrc:/qml/WmsdbDataAccessPlugin.qml";
}

QVariantMap CftlDataAccessPluginImpl::GetConfigurationMap(QString p_qstrApplication)
{
    if (m_pConfigurator)
    {
        DELPTR(m_pConfigurator);
    }

    m_pConfigurator = new CftlDataAccessConfigurator(p_qstrApplication);
    return m_pConfigurator->getValueMap();
}

void CftlDataAccessPluginImpl::SetConfigurationMap(QString p_qstrApplication, QVariantMap& p_rMap)
{
	if (!m_pConfigurator)
	{
		m_pConfigurator = new CftlDataAccessConfigurator(p_qstrApplication);
	}

	return m_pConfigurator->setValueMap(p_rMap);
}
