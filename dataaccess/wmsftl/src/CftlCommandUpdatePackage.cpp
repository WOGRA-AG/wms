
// WMS Includes
#include "CdmPackage.h"

// own Includes
#include "CftlCommandUpdatePackage.h"

CftlCommandUpdatePackage::CftlCommandUpdatePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_pPackage(p_pPackage)

{
}

CftlCommandUpdatePackage::~CftlCommandUpdatePackage()
{
}

bool CftlCommandUpdatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CftlCommandUpdatePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QString qstrSystemPackage = CwmsUtilities::ConvertBoolToString(m_pPackage->IsSystemPackage());
    QSqlQuery cQuery(GetSqlDatabase());

    cQuery.prepare("update WMS_CLASS_PACKAGE set URI = ?, System_Package = ? where SchemeId = ? and URI = ?");
    cQuery.addBindValue(m_pPackage->GetKeyname());
    cQuery.addBindValue(qstrSystemPackage);
    cQuery.addBindValue(m_pPackage->GetSchemeId());
    cQuery.addBindValue(m_pPackage->GetOriginalPackgeString());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
       INFO("Package updated.");
       m_pPackage->ResetNewModified();
       iRet = EC(eDmOk);
    }
    else
    {
       ERR("Could not update package on DB.");
       iRet = CdmLogging::eDmInsertPackageFailed;
    }

    return iRet;
}
