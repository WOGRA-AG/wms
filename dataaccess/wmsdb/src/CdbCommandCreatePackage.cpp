
// System and Qt Includes

// WMS Includes
#include "CdmPackage.h"

// own Includes
#include "CdbCommandCreatePackage.h"

CdbCommandCreatePackage::CdbCommandCreatePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_pPackage(p_pPackage)
{
}

CdbCommandCreatePackage::~CdbCommandCreatePackage()
{
}

bool CdbCommandCreatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CdbCommandCreatePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    QString qstrSystemPackage = CwmsUtilities::ConvertBoolToString(m_pPackage->IsSystemPackage());
    QSqlQuery cQuery;

    QString qstrSql = QString("insert into WMS_CLASS_PACKAGE (URI, System_Package, SchemeId) "
                              "values('%1', %2, %3)")
                            .arg(m_pPackage->GetPackageString())
                            .arg(qstrSystemPackage)
                            .arg(m_pPackage->GetSchemeId());

    if (ExecuteQuery(qstrSql, cQuery) > 0)
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
