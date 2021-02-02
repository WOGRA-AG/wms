// WMS Includes
#include "CdmPackage.h"

// own Includes
#include "CdbCommandUpdatePackage.h"

CdbCommandUpdatePackage::CdbCommandUpdatePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_pPackage(p_pPackage)

{
}

CdbCommandUpdatePackage::~CdbCommandUpdatePackage()
{
}

bool CdbCommandUpdatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CdbCommandUpdatePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QString qstrSystemPackage = CwmsUtilities::ConvertBoolToString(m_pPackage->IsSystemPackage());
    QSqlQuery cQuery;

    QString qstrSql = QString("update WMS_CLASS_PACKAGE set URI = '%1', System_Package = %2 "
                              "where SchemeId = %3 and URI = '%4'")
            .arg(m_pPackage->GetKeyname())
            .arg(qstrSystemPackage)
            .arg(m_pPackage->GetSchemeId())
            .arg(m_pPackage->GetOriginalPackgeString());

    if (ExecuteQuery(qstrSql, cQuery) > 0)
    {
       INFO("Package updated.");
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
