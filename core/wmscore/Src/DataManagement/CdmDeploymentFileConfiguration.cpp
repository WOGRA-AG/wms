#include "CdmDeploymentFileConfiguration.h"

CdmDeploymentFileConfiguration::CdmDeploymentFileConfiguration()
{

}

CdmDeploymentFileConfiguration::~CdmDeploymentFileConfiguration()
{

}

EdmDeploymentFileMode CdmDeploymentFileConfiguration::GetDeploymentMode() const
{
    return m_eDeploymentMode;
}

void CdmDeploymentFileConfiguration::SetDeploymentMode(EdmDeploymentFileMode p_eMode)
{
    m_eDeploymentMode = p_eMode;
}

QString CdmDeploymentFileConfiguration::GetFilename() const
{
    return m_qstrFilename;
}

void CdmDeploymentFileConfiguration::SetFilename(QString p_qstrFilename)
{
    m_qstrFilename = p_qstrFilename;
}

void CdmDeploymentFileConfiguration::AddClassUri(QString p_qstrUri)
{
    if (!m_qstrlClassUris.contains(p_qstrUri))
    {
        m_qstrlClassUris.append(p_qstrUri);
    }
}

QStringList CdmDeploymentFileConfiguration::GetClassUris() const
{
    return m_qstrlClassUris;
}

void CdmDeploymentFileConfiguration::AddContainerUri(QString p_qstrUri)
{
    if (!m_qstrlContainerUris.contains(p_qstrUri))
    {
        m_qstrlContainerUris.append(p_qstrUri);
    }
}

QStringList CdmDeploymentFileConfiguration::GetContainerUris() const
{
    return m_qstrlContainerUris;
}
