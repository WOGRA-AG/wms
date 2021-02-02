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

// own includes
#include "CwiCommandFindCompanySchemeByName.h"

CwiCommandFindCompanySchemeByName::CwiCommandFindCompanySchemeByName(CwmscomData *p_pData)
    : m_rpData(p_pData)
{
    if (CHKPTR(m_rpData))
    {
        CwmsContext::GetContext()->ServerLogin();
        m_pResult = new CwmscomDataResult(m_rpData);
    }
}

CwiCommandFindCompanySchemeByName::~CwiCommandFindCompanySchemeByName()
{
     CwmsContext::GetContext()->ServerLogout();
}

void CwiCommandFindCompanySchemeByName::Execute()
{
    QString qstrScheme = m_rpData->GetValue("Company").toString();
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pScheme = pManager->FindSchemeByName(qstrScheme);

        if (CHKPTR(pScheme))
        {
            m_pResult->AddValue("CompanyScheme", pScheme->GetVariant());
            m_pResult->AddValue("isCompany", true);
            m_pResult->SetMessage("Company found");
            m_pResult->SetSeverity(eWmscomMessageServerityInfo);
            m_pResult->SetMessageCode(EC(eDmOk));
        }
        else
        {
            m_pResult->AddValue("isCompany", false);
            m_pResult->SetMessage("Company not found");
            m_pResult->SetSeverity(eWmscomMessageServerityInfo);
            m_pResult->SetMessageCode(EC(eDmOk));
        }
    }

}
