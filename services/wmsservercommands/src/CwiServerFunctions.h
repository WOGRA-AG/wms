#ifndef CWISERVERFUNCTIONS_H
#define CWISERVERFUNCTIONS_H

//WMSCOM Inlcudes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"


class WMSINTERFACE_API CwiServerFunctions : public CwmscomResourceBase
{
public:
    CwiServerFunctions(CwmscomController* p_pController);
    virtual ~CwiServerFunctions();
    void executeDescription(CwmscomData *p_pData);
    QString GetResourceDescription();
    QString getVersion();
protected:
    void ExecuteGet(CwmscomData *p_pData);
    void ExecutePut(CwmscomData *p_pData);
    void ExecuteDelete(CwmscomData *p_pData);
private:
    void RegisterCompany(CwmscomData *p_pData);
    void DeleteCompanyRegistration(CwmscomData *p_pData);
    void FindCompanySchemeByName(CwmscomData *p_pData);
    void InstallAppScheme(CwmscomData *p_pData);
};

#endif // CWISERVERFUNCTIONS_H
