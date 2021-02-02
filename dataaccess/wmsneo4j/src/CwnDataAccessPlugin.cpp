// WMS Includes
#include "CdmLogging.h"

// Own Includes

#include <QVariant>
#include "CwnDataAccess.h"
#include "CwnDataAccessPlugin.h"
#include "CwnDataAccessConfigurator.h"

CwnDataAccessPlugin::CwnDataAccessPlugin()
: m_pConfigurator(nullptr)
{
}

CwnDataAccessPlugin::~CwnDataAccessPlugin()
{
    DELPTR(m_pConfigurator);
}

IdmDataAccess* CwnDataAccessPlugin::getDbAccess(QString p_qstrApplication)
{
    IdmDataAccess* pDataAccess = nullptr;

    if (!m_pConfigurator)
    {
        m_pConfigurator = new CwnDataAccessConfigurator(p_qstrApplication);
    }

    pDataAccess = new CwnDataAccess();
    dynamic_cast<CwnDataAccess*>(pDataAccess)->Init(m_pConfigurator);
    return pDataAccess;

    //return new CwnDataAccess();
}

QString CwnDataAccessPlugin::getVersion()
{
    return "0.95";
}

QString CwnDataAccessPlugin::getName()
{
    return "Neo4j Database Access";
}

QObject *CwnDataAccessPlugin::getConfigurationObject(QString p_qstrApplication)
{
    if (!m_pConfigurator)
    {
        m_pConfigurator = new CwnDataAccessConfigurator(p_qstrApplication);
    }

    return m_pConfigurator;
}

void CwnDataAccessPlugin::openConfigurationEditor(QString p_qstrApplication)
{
    if (!m_pConfigurator)
    {
        m_pConfigurator = new CwnDataAccessConfigurator(p_qstrApplication);
    }

    m_pConfigurator->OpenConfigurator();
}

QString CwnDataAccessPlugin::getConfigurationUiName()
{
   return "qrc:/qml/WmsdbDataAccessPlugin.qml";
}

QVariantMap CwnDataAccessPlugin::GetConfigurationMap(QString p_qstrApplication)
{
    if (m_pConfigurator)
    {
        DELPTR(m_pConfigurator);
    }

    m_pConfigurator = new CwnDataAccessConfigurator(p_qstrApplication);
    return m_pConfigurator->getValueMap();
}

void CwnDataAccessPlugin::SetConfigurationMap(QString p_qstrApplication, QVariantMap &p_rMap)
{
    if (m_pConfigurator)
    {
        DELPTR(m_pConfigurator);
    }

    m_pConfigurator = new CwnDataAccessConfigurator(p_qstrApplication);
    return m_pConfigurator->setValueMap(p_rMap);
}
