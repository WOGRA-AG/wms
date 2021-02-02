#include <QString>
#include "CwmsJson.h"
#include "CdmConfigManager.h"



CdmConfigManager::CdmConfigManager()
{

}

CdmConfigManager::~CdmConfigManager()
{

}

void CdmConfigManager::SetConfig(QString p_qstrConfig)
{
    CwmsJson json;
    if (p_qstrConfig.isEmpty())
    {
        m_qmConfig.clear();
    }
    else
    {
        m_qmConfig = json.parse(p_qstrConfig).toMap();
    }
}

QString CdmConfigManager::GetConfig() const
{
    CwmsJson json;
    QVariantMap qvm = m_qmConfig;
    qvm.remove(TEMPORARY_DATA);
    return json.serialize(qvm);
}

void CdmConfigManager::SetConfigItem(QString p_qstrKey, QVariant p_qvValue)
{
    m_qmConfig.insert(p_qstrKey, p_qvValue);
}

QVariant CdmConfigManager::GetConfigItem(QString p_qstrKey) const
{
    return m_qmConfig[p_qstrKey];
}

QVariant CdmConfigManager::GetTemporaryData(QString p_qstrKey) const
{
    QVariant qvResult;

    if (m_qmConfig.contains(TEMPORARY_DATA))
    {
        QVariantMap qvm = m_qmConfig[TEMPORARY_DATA].toMap();
        qvResult = qvm[p_qstrKey];
    }

    return qvResult;
}

bool CdmConfigManager::HasTemporaryData(QString p_qstrKey) const
{
    bool bRet =false;


    if (m_qmConfig.contains(TEMPORARY_DATA))
    {
        QVariantMap qvm = m_qmConfig[TEMPORARY_DATA].toMap();
        bRet = qvm.contains(p_qstrKey);
    }

    return bRet;
}

void CdmConfigManager::SetTemporaryData(QString p_qstrKey, QVariant p_qvValue)
{
    QVariantMap qvm;

    if (m_qmConfig.contains(TEMPORARY_DATA))
    {
        qvm = m_qmConfig[TEMPORARY_DATA].toMap();
    }

    qvm.insert(p_qstrKey, p_qvValue);
    m_qmConfig[TEMPORARY_DATA] = qvm;

}
