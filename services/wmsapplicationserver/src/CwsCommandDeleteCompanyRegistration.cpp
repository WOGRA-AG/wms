
// System and Qt Includes
#include <Qmap>

// WMS Includes
#include "CdmError.h"
#include "CdmRights.h"
#include "CdmManager.h"
#include "CumUserManager.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

// Own Includes
#include "CwsServer.h"
#include "CwsCommandDeleteCompanyRegistration.h"

CwiCommandDeleteCompanyRegistration::CwiCommandDeleteCompanyRegistration(CwsServer* p_pServer)
    : m_rpCwsServer(p_pServer)
{

}

CwiCommandDeleteCompanyRegistration::~CwiCommandDeleteCompanyRegistration()
{

}

int CwiCommandDeleteCompanyRegistration::Execute(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;

    QString qstrScheme = p_rRequest.GetValue("Scheme").toString();

    CdmManager* pManager = CdmSessionManager::GetManager();

    if (CHKPTR(pManager))
    {
        CdmScheme* pScheme = pManager->FindSchemeByName(qstrScheme);

        if (CHKPTR(pScheme))
        {
            // First delete all Company Users

        }
        else
        {
            ERR("Scheme not found.");
        }
    }
    else
    {
        ERR("No session established!");
    }

    return iRet;
}

void CwiCommandDeleteCompanyRegistration::DeleteSchemeUsers(CdmScheme* p_pScheme)
{
    if (CHKPTR(p_pScheme))
    {
        CdmRights& cRights = p_pScheme->GetRights();

        QMap<int, EdmRight> qmRights = cRights.GetRights();

        CdmManager* pManager = CdmSessionManager::GetManager();

        CumUserManager* pUserManager = pManager->GetUserManager();

        if (CHKPTR(pUserManager))
        {
            QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
            QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                int iUserBaseId = qmIt.key();

                //pUserManager->D
            }
        }


    }
}
