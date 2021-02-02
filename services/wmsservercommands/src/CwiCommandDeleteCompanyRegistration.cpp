// System and Qt Includes
#include <QMap>

// WMS Includes
#include "CdmLogging.h"
#include "CdmRights.h"
#include "CdmDataProvider.h"
#include "CumUserManager.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

// WMS Basetools Includes
#include "CwmsCloudServices.h"
#include "CwmsContext.h"

// Own Includes
#include "CwiCommandDeleteCompanyRegistration.h"

CwiCommandDeleteCompanyRegistration::CwiCommandDeleteCompanyRegistration(CwmscomData* p_pData)
    : m_rpData(p_pData)
{
    if (CHKPTR(m_rpData))
    {
        CwmsContext::GetContext()->ServerLogin();
        m_pResult = new CwmscomDataResult(m_rpData);
    }
}

CwiCommandDeleteCompanyRegistration::~CwiCommandDeleteCompanyRegistration()
{
    CwmsContext::GetContext()->ServerLogout();
}

void CwiCommandDeleteCompanyRegistration::Execute()
{
    QString qstrScheme = m_rpData->GetValue("Company").toString();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pScheme = pManager->FindSchemeByName(qstrScheme);

        if (CHKPTR(pScheme))
        {
            // First delete all Company Users
            DeleteSchemeUsers(pScheme);
            // Second delete the scheme
            pManager->RemoveScheme(pScheme->GetId());
            // third logout
            CdmSessionManager::Logout();

            m_pResult->SetMessage("Scheme deleted. Users deleted, Logout accomplished.");
            m_pResult->SetSeverity(eWmscomMessageServerityInfo);
            m_pResult->SetMessageCode(EC(eDmOk));
        }
        else
        {
            m_pResult->SetMessage("Scheme not found");
            m_pResult->SetSeverity(eWmscomMessageServerityError);
            m_pResult->SetMessageCode(-5000);
            ERR("Scheme not found.");
        }
    }
    else
    {
        m_pResult->SetMessage("Invalid Session");
        m_pResult->SetSeverity(eWmscomMessageServerityFatal);
        m_pResult->SetMessageCode(-5000);
        ERR("No session established!");
    }
}

bool CwiCommandDeleteCompanyRegistration::Validate()
{
    bool bRet = false;

    CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

    if (CHKPTR(pSessionManager))
    {
        const CumUser* pUser = pSessionManager->GetCurrentUser();

        if (CHKPTR(pUser))
        {
            CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pManager))
            {
                CdmScheme* pScheme = pManager->GetCurrentScheme();

                if (CHKPTR(pScheme))
                {
                    if (CwmsCloudServices::IsUserSchemeAdmin(pUser, pScheme))
                    {
                        bRet = true;
                    }
                    else
                    {
                        m_pResult->SetMessage("No privileges to delete Scheme");
                        m_pResult->SetSeverity(eWmscomMessageServerityError);
                        m_pResult->SetMessageCode(-5000);
                    }
                }
            }
        }
    }


    return bRet;
}

void CwiCommandDeleteCompanyRegistration::DeleteSchemeUsers(CdmScheme* p_pScheme)
{
    if (CHKPTR(p_pScheme))
    {
        CdmRights& cRights = p_pScheme->GetRights();

        QMap<int, EdmRight> qmRights = cRights.GetRights();

        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        CumUserManager* pUserManager = pManager->GetUserManager();

        if (CHKPTR(pUserManager))
        {
            QMap<int, EdmRight>::iterator qmIt = qmRights.begin();
            QMap<int, EdmRight>::iterator qmItEnd = qmRights.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                int iUserBaseId = qmIt.key();
                pUserManager->DeleteUser(iUserBaseId);
            }
        }
    }
}

