#ifndef CWICOMMANDINSTALLAPPSCHEME_H
#define CWICOMMANDINSTALLAPPSCHEME_H


// Own Includes
#include "IwiCommand.h"

class CwiCommandInstallAppScheme : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;

    QString GetDeploymentFile(int p_iAppSchemeId);
    void InstallDeploymentFile(QString &p_rqstrWdf);
public:
    CwiCommandInstallAppScheme(CwmscomData* p_pData);
    virtual ~CwiCommandInstallAppScheme();
    virtual void Execute();
};

#endif // CWICOMMANDINSTALLAPPSCHEME_H
