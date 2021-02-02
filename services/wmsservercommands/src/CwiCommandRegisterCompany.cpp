
// System and Qt Includes

// WMS Includes
#include "CdmScheme.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CumUser.h"


// own Includes
#include "CwiCommandRegisterUser.h"
#include "CwiCommandCreateCloudScheme.h"
#include "CwiCommandRegisterCompany.h"

CwiCommandRegisterCompany::CwiCommandRegisterCompany(CwmscomData *p_pData)
    : m_rpData(p_pData)
{
}

CwiCommandRegisterCompany::~CwiCommandRegisterCompany()
{
}

void CwiCommandRegisterCompany::Execute()
{
    if (CHKPTR(m_rpData))
    {
        // create company scheme
        CwiCommandCreateCompanyScheme commandCreateCompanyScheme(m_rpData);
        commandCreateCompanyScheme.Execute();

        CdmScheme* pScheme = commandCreateCompanyScheme.GetScheme();

        if (CHKPTR(pScheme))
        {
            CwiCommandRegisterUser commandRegisterUser(m_rpData);
            commandRegisterUser.Execute();
            CumUser* pUser = commandRegisterUser.GetUser();

            if (CHKPTR(pUser))
            {
                AddUserToScheme(pUser, pScheme);
            }
        }
    }
}

void CwiCommandRegisterCompany::AddUserToScheme(CumUser* p_pUser, CdmScheme* p_pScheme)
{
    if (CHKPTR(p_pUser) && CHKPTR(p_pScheme))
    {
        // now it is only possible that the current user can see the scheme
        CdmRights& rRights = p_pScheme->GetRights();
        rRights.AddRight(p_pUser->GetId(), eDmRightWrite);
        p_pScheme->Commit();

        // now add user as scheme admin
        CdmContainerManager* pContainerManager = p_pScheme->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindContainerByKeyname(SCHEME_ADMIN_CONTAINER_NAME);

            if (CHKPTR(pContainer))
            {
                CdmObject* pObject = pContainer->CreateNewObject();
                pObject->SetValue(SCHEME_ADMIN, p_pUser);
                pObject->Commit();
            }
        }
    }
}
