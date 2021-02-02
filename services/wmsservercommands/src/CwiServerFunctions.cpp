
// Own Includes
#include "CwiCommandRegisterCompany.h"
#include "CwiCommandDeleteCompanyRegistration.h"
#include "CwiServerFunctions.h"
#include "CwiCommandFindCompanySchemeByName.h"
#include "CwiCommandInstallAppScheme.h"

CwiServerFunctions::CwiServerFunctions(CwmscomController* p_pController)
   : CwmscomResourceBase(p_pController, "ServerFunctions", false, false)
{
}

CwiServerFunctions::~CwiServerFunctions()
{

}


void CwiServerFunctions::ExecuteGet(CwmscomData* p_pData)
{
    QString qstrMode;
    if (p_pData->HasValue("Mode"))
    {
       qstrMode = p_pData->GetValue("Mode").toString();
       if (qstrMode ==  "FindCompanySchemeByName")
       {
          FindCompanySchemeByName(p_pData);
       }
    }
}

void CwiServerFunctions::ExecutePut(CwmscomData* p_pData)
{
    QString qstrMode;
    if (p_pData->HasValue("Mode"))
    {
       qstrMode = p_pData->GetValue("Mode").toString();
       if (qstrMode ==  "RegisterCompany")
       {
          RegisterCompany(p_pData);
       }
       else if (qstrMode ==  "DeleteCompanyRegistration")
       {
          DeleteCompanyRegistration(p_pData);
       }
       else if (qstrMode == "InstallAppScheme")
       {
          InstallAppScheme(p_pData);
       }
    }
}

void CwiServerFunctions::ExecuteDelete(CwmscomData* p_pData)
{
    Q_UNUSED(p_pData);
}



void CwiServerFunctions::executeDescription(CwmscomData* p_pData)
{
    Q_UNUSED(p_pData);
}

QString CwiServerFunctions::GetResourceDescription()
{
    return "This resource is for handling special server services";
}

QString CwiServerFunctions::getVersion()
{
    return "0.1.0";
}

void CwiServerFunctions::RegisterCompany(CwmscomData* p_pData)
{
    CwiCommandRegisterCompany command(p_pData);
    command.Execute();
}

void CwiServerFunctions::DeleteCompanyRegistration(CwmscomData* p_pData)
{
    CwiCommandDeleteCompanyRegistration command(p_pData);
    command.Execute();
}

void CwiServerFunctions::FindCompanySchemeByName(CwmscomData* p_pData)
{
    CwiCommandFindCompanySchemeByName command(p_pData);
    command.Execute();
}

void CwiServerFunctions::InstallAppScheme(CwmscomData* p_pData)
{
    CwiCommandInstallAppScheme command(p_pData);
    command.Execute();
}
