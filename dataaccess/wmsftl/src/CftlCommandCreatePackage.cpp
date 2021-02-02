
// System and Qt Includes

// WMS Includes
#include "CdmPackage.h"

// own Includes
#include "CftlCommandCreatePackage.h"

CftlCommandCreatePackage::CftlCommandCreatePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_pPackage(p_pPackage)
{
}

CftlCommandCreatePackage::~CftlCommandCreatePackage()
{
}

bool CftlCommandCreatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CftlCommandCreatePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownSqlError;
    QSqlQuery cQuery(GetSqlDatabase());

    cQuery.prepare("insert into WMS_CLASS_PACKAGE (URI, System_Package, SchemeId) "
                              "values(?, ?, ?)");
    cQuery.addBindValue(m_pPackage->GetPackageString());
    cQuery.addBindValue(m_pPackage->IsSystemPackage());
    cQuery.addBindValue((int)m_pPackage->GetSchemeId());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
       INFO("Package inserted.");
       m_pPackage->ResetNewModified();
       iRet = EC(eDmOk);
    }
    else
    {
       ERR("Could not create package on DB.");
       iRet = CdmLogging::eDmInsertPackageFailed;
    }

    return iRet;
}
