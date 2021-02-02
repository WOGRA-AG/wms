#ifndef CWICOMMANDCREATECOMAPNYSCHEME_H
#define CWICOMMANDCREATECOMAPNYSCHEME_H

// System and Qt Includes
#include <QString>

// own Includes
#include "IwiCommand.h"

// DEFINES
#define COMPANY "Company"
#define ADDRESS "Address"
#define POSTCODE "Postcode"
#define CITY "City"
#define TAXID "TaxId"
#define COUNTRY "Country"
#define COMPANY_CONTAINER_NAME "OwnerCompany"
#define COMPANY_CLASS_NAME "Scheme_Owner_Company"
#define PACKAGE_NAME "Internal"
#define SCHEME_ADMIN_CLASS_NAME "Scheme_Admin"
#define SCHEME_ADMIN_CONTAINER_NAME "SchemeAdmins"
#define SCHEME_ADMIN "Admin"
#define APPLICATION_CLASS "Installed_Application"
#define APPLICATION_CONTAINER "InstalledApplications"
#define APPLICATION_NAME "ApplicationName"
#define APPLICATION_VERSION "ApplicationVersion"
#define APPLICATION_INSTALL_DATE "InstallationDate"
#define APPLICATION_INSTALL_USER "Installer"


// forwards
class CdmScheme;
class CdmClass;
class CdmObjectContainer;

class CwiCommandCreateCompanyScheme : public IwiCommand
{
private:
    CwmscomData* m_rpData;
    CwmscomDataResult* m_pResult;
    CdmScheme* m_pScheme;
    CdmClass* m_pClass;
    CdmObjectContainer* m_pContainer;

    CdmScheme *CreateScheme();
    void CreateClasses();
    void CreateCompanyClass();
    void CreateCompanyContainer();
    void CreateContainer();
    void CreateSchemeAdminContainer();
    void CreateSchemeAdminClass();
    bool ValidateData();
    void CreateObject();
    void CreateApplicationClass();
    void CreateApplicationContainer();
public:
    CwiCommandCreateCompanyScheme(CwmscomData* p_pData);
    virtual ~CwiCommandCreateCompanyScheme();
    virtual void Execute();
    CdmScheme *GetScheme();
};

#endif // CWICOMMANDCREATECOMAPNYSCHEME_H
