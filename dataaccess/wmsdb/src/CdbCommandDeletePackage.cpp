
// WMS Includes
#include "CdmPackage.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"

// own Includes
#include "CdbCommandDeletePackage.h"


CdbCommandDeletePackage::CdbCommandDeletePackage(CdmPackage* p_pPackage, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_pPackage(p_pPackage)
{
}

CdbCommandDeletePackage::~CdbCommandDeletePackage()
{
}

bool CdbCommandDeletePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CdbCommandDeletePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery;
    QString qstrSql = QString("delete from WMS_CLASS_PACKAGE where URI = '%1' and SCHEMEID = %2")
            .arg(m_pPackage->GetPackageString())
            .arg(m_pPackage->GetSchemeId());

    if (ExecuteQuery(qstrSql, cQuery) > 0)
    {
       INFO("Package deleted.");
       QList<CdmPackage*> qlChildren;
	   m_pPackage->GetChildren(qlChildren);
       DeletePackageChildren(qlChildren);
       DELPTR(m_pPackage);
       iRet = EC(eDmOk);
    }
    else
    {
       ERR("Could not create package on DB.");
       iRet = CdmLogging::eDmInsertPackageFailed;
    }

    return iRet;
}

void CdbCommandDeletePackage::DeletePackageChildren(QList<CdmPackage*>& p_rqlChildren)
{
    CdmClassManager* pClassManager = CdmSessionManager::GetDataProvider()->GetClassManager();

    if (CHKPTR(pClassManager))
    {
        for (int iPos = 0; iPos < p_rqlChildren.count(); ++iPos)
        {
            CdmPackage* pPackageTemp = p_rqlChildren[iPos];

            if (CHKPTR(pPackageTemp))
            {
                pClassManager->DeletePackage(pPackageTemp);
            }
        }
    }
}
