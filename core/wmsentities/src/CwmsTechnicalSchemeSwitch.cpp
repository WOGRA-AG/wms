
// WMS Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"


// own Includes
#include "CwmsContext.h"
#include "CwmsTechnicalSchemeSwitch.h"

CwmsTechnicalSchemeSwitch::CwmsTechnicalSchemeSwitch()
{
    SwitchToTechnicalScheme();
}

CwmsTechnicalSchemeSwitch::~CwmsTechnicalSchemeSwitch()
{
    SwitchBackToOriginalScheme();
}

bool CwmsTechnicalSchemeSwitch::SwitchToTechnicalScheme()
{
    bool bRet = false;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pCurrentScheme = pManager->GetCurrentScheme();

        if (pCurrentScheme)
        {
            m_qstrOrignalScheme = pCurrentScheme->GetSchemeName();

            if (m_qstrOrignalScheme == WMS_TECHNICAL_SERVER)
            {
                INFO("TechnicalScheme already current. Nothing to do");
                return true;
            }
        }
        else
        {
            m_qstrOrignalScheme = "";
        }


        INFO("Open Technical Scheme");
        QString qstrScheme = WMS_TECHNICAL_SERVER;
        if (pManager->ExistScheme(qstrScheme))
        {
           if(pManager->FindSchemeByName(qstrScheme))
           {
               INFO("Switched to TechnicalScheme");
               CwmsServerSchemeManager cServerSchemeManager;
               cServerSchemeManager.CheckServerScheme();
               bRet = true;
           }
        }
        else
        {
            // create the scheme
            CwmsServerSchemeManager cServerSchemeManager;
            cServerSchemeManager.CheckServerScheme();
            if(pManager->FindSchemeByName(qstrScheme))
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

bool CwmsTechnicalSchemeSwitch::SwitchBackToOriginalScheme()
{
    if (m_qstrOrignalScheme == WMS_TECHNICAL_SERVER)
    {
        INFO("Stay in TechnicalScheme. Nothing to do");
        return true;
    }

    if(!m_qstrOrignalScheme.isEmpty())
    {
        if (CwmsContext::GetContext()->GetContextType() != eWmsApplicationContextServer)
        {
            INFO("Remove TechnicalScheme locally");
            RemoveTechnicalSchemeLocally();
        }

        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            INFO("Switching back to " + m_qstrOrignalScheme);
            return (pManager->FindSchemeByName(m_qstrOrignalScheme) != nullptr);
        }
    }
    else
    {
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (CHKPTR(pManager))
        {
            pManager->SetCurrentScheme(nullptr);
        }
    }

    return false;
}

bool CwmsTechnicalSchemeSwitch::RemoveTechnicalSchemeLocally()
{
    bool bRet = false;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
     QString qstrScheme = WMS_TECHNICAL_SERVER;

    if (CHKPTR(pManager))
    {
        pManager->RemoveLocalScheme(qstrScheme);
        bRet = true;
    }

    return bRet;
}
