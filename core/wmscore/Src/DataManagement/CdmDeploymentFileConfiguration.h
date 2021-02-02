#ifndef CDMDEPLOYMENTFILECONFIGURATION_H
#define CDMDEPLOYMENTFILECONFIGURATION_H

// System and Qt Includes
#include <QStringList>

enum EdmDeploymentFileMode
{
    eDmDeploymentFileModeApplicationRelevant,
    eDmDeploymentFileModeClasses,
    eDmDeploymentFileModeComplete,
    eDmDeploymentFileModeUserDefined
};


class CdmDeploymentFileConfiguration
{

private:
    EdmDeploymentFileMode m_eDeploymentMode;
    QString m_qstrFilename;
    QStringList m_qstrlClassUris;
    QStringList m_qstrlContainerUris;

public:
    CdmDeploymentFileConfiguration();
    virtual ~CdmDeploymentFileConfiguration();
    EdmDeploymentFileMode GetDeploymentMode() const;
    void SetDeploymentMode(EdmDeploymentFileMode p_eMode);
    QString GetFilename() const;
    void SetFilename(QString p_qstrFilename);
    void AddClassUri(QString p_qstrUri);
    QStringList GetClassUris() const;
    void AddContainerUri(QString p_qstrUri);
    QStringList GetContainerUris() const;
};

#endif // CDMDEPLOYMENTFILECONFIGURATION_H
