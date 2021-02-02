
// WMS Includes
#include "CdmPackage.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"

// own Includes
#include "CftlCommandDeletePackage.h"


CftlCommandDeletePackage::CftlCommandDeletePackage(CdmPackage* p_pPackage, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_pPackage(p_pPackage)
{
}

CftlCommandDeletePackage::~CftlCommandDeletePackage()
{
}

bool CftlCommandDeletePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

int CftlCommandDeletePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("delete from WMS_CLASS_PACKAGE where URI = ?");
    cQuery.addBindValue(m_pPackage->GetKeyname());

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
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

void CftlCommandDeletePackage::DeletePackageChildren(QList<CdmPackage*>& p_rqlChildren)
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
