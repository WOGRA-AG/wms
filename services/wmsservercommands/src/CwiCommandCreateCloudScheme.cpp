// System and Qt Includes
#include <QApplication>

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmPackage.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// Basetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwiCommandCreateCloudScheme.h"


CwiCommandCreateCompanyScheme::CwiCommandCreateCompanyScheme(CwmscomData* p_pData)
    : m_rpData(p_pData),
      m_pScheme(nullptr),
      m_pClass(nullptr),
      m_pContainer(nullptr)
{
    if (CHKPTR(m_rpData))
    {
        CwmsContext::GetContext()->ServerLogin();
        m_pResult = new CwmscomDataResult(p_pData);
    }
}


CwiCommandCreateCompanyScheme::~CwiCommandCreateCompanyScheme()
{
    if (CHKPTR(m_rpData))
    {
        CwmsContext::GetContext()->ServerLogout();
    }
}


void CwiCommandCreateCompanyScheme::Execute()
{
    if (CHKPTR(m_rpData))
    {
        if (ValidateData())
        {
            CreateScheme();
            CreateContainer();
            CreateObject();
        }
    }
    else
    {
        m_pResult->SetMessage("Company Scheme failed. Data Object is empty");
        m_pResult->SetSeverity(eWmscomMessageServerityError);
        m_pResult->SetMessageCode(-5000);
    }
}

void CwiCommandCreateCompanyScheme::CreateObject()
{
    QString qstrCompany = m_rpData->GetValue(COMPANY).toString();
    QString qstrAddress = m_rpData->GetValue(ADDRESS).toString();
    QString qstrPostcode = m_rpData->GetValue(POSTCODE).toString();
    QString qstrCity = m_rpData->GetValue(CITY).toString();
    QString qstrTaxId = m_rpData->GetValue(TAXID).toString();
    QString qstrCountry = m_rpData->GetValue(COUNTRY).toString();

    if (m_pContainer)
    {
        CdmObject* pObject = m_pContainer->CreateNewObject();

        if (CHKPTR(pObject))
        {
            pObject->SetValue(COMPANY, qstrCompany);
            pObject->SetValue(ADDRESS, qstrAddress);
            pObject->SetValue(POSTCODE, qstrPostcode);
            pObject->SetValue(CITY, qstrCity);
            pObject->SetValue(TAXID, qstrTaxId);
            pObject->SetValue(COUNTRY, qstrCountry);
            pObject->Commit();

            m_pResult->SetMessage("Company Scheme created");
            m_pResult->SetSeverity(eWmscomMessageServerityInfo);
            m_pResult->SetMessageCode(EC(eDmOk));
        }
    }
}


bool CwiCommandCreateCompanyScheme::ValidateData()
{
    bool bRet = false;
    QString qstrCompany = m_rpData->GetValue(COMPANY).toString();
    QString qstrAddress = m_rpData->GetValue(ADDRESS).toString();
    QString qstrPostcode = m_rpData->GetValue(POSTCODE).toString();
    QString qstrCity = m_rpData->GetValue(CITY).toString();
    QString qstrTaxId = m_rpData->GetValue(TAXID).toString();
    QString qstrCountry = m_rpData->GetValue(COUNTRY).toString();

    if (qstrCompany.isEmpty() ||
        qstrAddress.isEmpty() ||
        qstrPostcode.isEmpty() ||
        qstrCity.isEmpty() ||
        qstrTaxId.isEmpty() ||
        qstrCountry.isEmpty())
    {
        m_pResult->SetMessage("Company Scheme failed. Missing Data for creating scheme");
        m_pResult->SetSeverity(eWmscomMessageServerityError);
        m_pResult->SetMessageCode(EC(eDmOk));
    }
    else
    {
        bRet = true;
    }

    return bRet;
}


CdmScheme* CwiCommandCreateCompanyScheme::CreateScheme()
{
    QString qstrCompany = m_rpData->GetValue(COMPANY).toString();
    QString qstrSchemeName = qstrCompany.replace(" ", "_");

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        if (SUCCESSFULL(pManager->CreateScheme(qstrSchemeName)))
        {
            m_pScheme = pManager->FindSchemeByName(qstrSchemeName);
            CreateClasses();
            CreateContainer();
        }
        else
        {
            m_pResult->SetMessage("Company Scheme creation failed");
            m_pResult->SetSeverity(eWmscomMessageServerityFatal);
            m_pResult->SetMessageCode(EC(eDmOk));
        }
    }

	return m_pScheme;
}


void CwiCommandCreateCompanyScheme::CreateClasses()
{
    CreateCompanyClass();
    CreateSchemeAdminClass();
    CreateApplicationClass();
}

void CwiCommandCreateCompanyScheme::CreateContainer()
{
    CreateCompanyContainer();
    CreateSchemeAdminContainer();
    CreateApplicationContainer();
}

void CwiCommandCreateCompanyScheme::CreateCompanyContainer()
{
    if (CHKPTR(m_pScheme) && m_pClass)
    {
        CdmContainerManager* pContainerManager = m_pScheme->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            QString qstrContainerName = COMPANY_CONTAINER_NAME;

            if (SUCCESSFULL(pContainerManager->CreateContainer(m_pClass,qstrContainerName)))
            {
                m_pContainer = pContainerManager->FindContainerByKeyname(qstrContainerName);
            }
        }
    }
}

void CwiCommandCreateCompanyScheme::CreateCompanyClass()
{
    if (CHKPTR(m_pScheme))
    {
        CdmClassManager* pClassManager = m_pScheme->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmPackage* pPackage = pClassManager->CreatePackage(PACKAGE_NAME);

            if (CHKPTR(pPackage))
            {
                m_pClass = pClassManager->CreateClass(COMPANY_CLASS_NAME);

                if (CHKPTR(m_pClass))
                {
                    m_pClass->SetPackage(pPackage);
                    m_pClass->SetCaption(qApp->tr("Unternehmen"));
                    m_pClass->SetComment(qApp->tr("Unternehmen, dem dieser Scheme besitzt."));


                    CdmMember* pMember = m_pClass->CreateMember(COMPANY, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Unternehmen und Rechtsform"));
                        pMember->SetComment(qApp->tr("Der Name des Unternehmens und seine Rechtsform"));
                    }

                    pMember = m_pClass->CreateMember(ADDRESS, eDmValueString, false, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Straße und Haus Nummer bzw. Postfach"));
                        pMember->SetComment(qApp->tr("Die Anschrift des Unternehmens"));
                    }

                    pMember = m_pClass->CreateMember(POSTCODE, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("PLZ"));
                        pMember->SetComment(qApp->tr("Die PLZ des Unternehmens"));
                    }

                    pMember = m_pClass->CreateMember(CITY, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Ort"));
                        pMember->SetComment(qApp->tr("Der Ort des Unternehmenssitz"));
                    }

                    pMember = m_pClass->CreateMember(COUNTRY, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Land"));
                        pMember->SetComment(qApp->tr("Das Land des Unternehmenssitz"));
                    }

                    pMember = m_pClass->CreateMember(TAXID, eDmValueString, false, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Steuernummer bzw. USt-Id"));
                        pMember->SetComment(qApp->tr("Die Steuernummer oder UST-Id des Unternehmens"));
                    }

                    m_pClass->Commit();
                }
            }
        }
    }
}

void CwiCommandCreateCompanyScheme::CreateSchemeAdminClass()
{
    if (CHKPTR(m_pScheme))
    {
        CdmClassManager* pClassManager = m_pScheme->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmPackage* pPackage = pClassManager->FindPackageByName(PACKAGE_NAME);

            if (CHKPTR(pPackage))
            {
                m_pClass = pClassManager->CreateClass(SCHEME_ADMIN_CLASS_NAME);

                if (CHKPTR(m_pClass))
                {
                    CdmMember* pMember = m_pClass->CreateMember(SCHEME_ADMIN, eDmValueUser, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Scheme Administrator"));
                        pMember->SetComment(qApp->tr("Ein Anwender der Schema Admin ist."));
                    }

                    m_pClass->Commit();
                }
            }
        }
    }
}

void CwiCommandCreateCompanyScheme::CreateSchemeAdminContainer()
{
    if (CHKPTR(m_pScheme))
    {
        CdmClass* pClass = nullptr;

        CdmClassManager* pClassManager = m_pScheme->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            pClass = pClassManager->FindClassByKeyname(SCHEME_ADMIN_CLASS_NAME);
        }

        CdmContainerManager* pContainerManager = m_pScheme->GetContainerManager();

        if (CHKPTR(pContainerManager) && pClass)
        {
            QString qstrContainerName = SCHEME_ADMIN_CONTAINER_NAME;
            pContainerManager->CreateContainer(pClass, qstrContainerName);
        }
    }
}

void CwiCommandCreateCompanyScheme::CreateApplicationClass()
{
    if (CHKPTR(m_pScheme))
    {
        CdmClassManager* pClassManager = m_pScheme->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmPackage* pPackage = pClassManager->FindPackageByName(PACKAGE_NAME);

            if (CHKPTR(pPackage))
            {
                m_pClass = pClassManager->CreateClass(APPLICATION_CLASS);

                if (CHKPTR(m_pClass))
                {
                    CdmMember* pMember = m_pClass->CreateMember(APPLICATION_NAME, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Name"));
                        pMember->SetComment(qApp->tr("Name des installierten Applikationsschemas"));
                        pMember->SetMemberAccess(eDmMemberAccessProtected);
                    }

                    pMember = m_pClass->CreateMember(APPLICATION_VERSION, eDmValueString, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Version"));
                        pMember->SetComment(qApp->tr("Version des installierten Applikationsschemas"));
                        pMember->SetMemberAccess(eDmMemberAccessProtected);
                    }

                    pMember = m_pClass->CreateMember(APPLICATION_INSTALL_DATE, eDmValueDateTime, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Installationszeitpunkt"));
                        pMember->SetComment(qApp->tr("Zeitpunkt der Installationsdurchführung."));
                        pMember->SetMemberAccess(eDmMemberAccessProtected);
                    }

                    pMember = m_pClass->CreateMember(APPLICATION_INSTALL_USER, eDmValueUser, true, 0);

                    if (CHKPTR(pMember))
                    {
                        pMember->SetCaption(qApp->tr("Installierender User"));
                        pMember->SetComment(qApp->tr("User der die Installationdurchgeführt hat."));
                        pMember->SetMemberAccess(eDmMemberAccessProtected);
                    }

                    m_pClass->Commit();
                }
            }
        }
    }
}

void CwiCommandCreateCompanyScheme::CreateApplicationContainer()
{
    if (CHKPTR(m_pScheme))
    {
        CdmClass* pClass = nullptr;

        CdmClassManager* pClassManager = m_pScheme->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            pClass = pClassManager->FindClassByKeyname(APPLICATION_CLASS);
        }

        CdmContainerManager* pContainerManager = m_pScheme->GetContainerManager();

        if (CHKPTR(pContainerManager) && pClass)
        {
            QString qstrContainerName = APPLICATION_CONTAINER;
            pContainerManager->CreateContainer(pClass, qstrContainerName);
        }
    }
}

CdmScheme* CwiCommandCreateCompanyScheme::GetScheme()
{
    return m_pScheme;
}
