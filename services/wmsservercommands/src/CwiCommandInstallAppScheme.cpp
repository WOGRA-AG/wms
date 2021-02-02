
#include "wmsdefines.h"

// WMS Manager includes
#include "CdmLogging.h"
#include "CdmScheme.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// WMS Basetools includes
#include "CwmsServerSchemeManager.h"


#include "CwiCommandInstallAppScheme.h"

CwiCommandInstallAppScheme::CwiCommandInstallAppScheme(CwmscomData* p_pData)
: m_rpData(p_pData),
  m_pResult(nullptr)
{
    m_pResult = new CwmscomDataResult(p_pData);
}


CwiCommandInstallAppScheme::~CwiCommandInstallAppScheme()
{

}

void CwiCommandInstallAppScheme::Execute()
{
    if (CHKPTR(m_rpData))
    {
        int iAppSchemeId = m_rpData->GetValue("Id").toInt();

        if (iAppSchemeId > 0)
        {
            QString qstrWdf = GetDeploymentFile(iAppSchemeId);

            if (!qstrWdf.isEmpty())
            {
                InstallDeploymentFile(qstrWdf);
            }
            else
            {
                m_pResult->SetMessage("WDF Content empty");
                m_pResult->SetSeverity(eWmscomMessageServerityFatal);
                m_pResult->SetMessageCode(-5000);
            }
        }
    }
}


QString CwiCommandInstallAppScheme::GetDeploymentFile(int p_iAppSchemeId)
{
    QString qstrWdf;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pOriginalScheme = pManager->GetCurrentScheme();
        QString qstrScheme = WMS_TECHNICAL_SERVER;
        pManager->LoadScheme(qstrScheme);
        CdmContainerManager* pContainerManager = pManager->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer =
                    pContainerManager->FindEmptyContainerByKeyname(APP_STORE_CONTAINER_NAME);

            if (CHKPTR(pContainerManager))
            {
                CdmObject* pObject = pContainer->FindObjectById(p_iAppSchemeId);

                if (CHKPTR(pObject))
                {
                    qstrWdf = pObject->GetDisplayString("WDF");
                }
                else
                {
                    m_pResult->SetMessage("Object not found");
                    m_pResult->SetSeverity(eWmscomMessageServerityFatal);
                    m_pResult->SetMessageCode(-5000);
                }
            }
        }

        if (pOriginalScheme && pOriginalScheme != pManager->GetCurrentScheme())
        {
            pManager->SetCurrentScheme(pOriginalScheme);
        }
    }

    return qstrWdf;
}


void CwiCommandInstallAppScheme::InstallDeploymentFile(QString& p_rqstrWdf)
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmScheme* pScheme = pManager->GetCurrentScheme();

        if (CHKPTR(pScheme))
        {
            if (pScheme->DeployJsonContent(p_rqstrWdf))
            {
                m_pResult->SetMessage("Deployment successfull");
                m_pResult->SetSeverity(eWmscomMessageServerityInfo);
                m_pResult->SetMessageCode(EC(eDmOk));
            }
            else
            {
                m_pResult->SetMessage("Deployment failed. Couldn't fill scheme\n" + p_rqstrWdf);
                m_pResult->SetSeverity(eWmscomMessageServerityFatal);
                m_pResult->SetMessageCode(-5000);
            }
        }
    }
}
