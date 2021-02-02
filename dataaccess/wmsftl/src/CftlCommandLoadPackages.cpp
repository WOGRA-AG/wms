// WMS Includes
#include "CdmClassManager.h"
#include "CdmPackage.h"

// own Includes
#include "CftlCommandLoadPackages.h"

CftlCommandLoadPackages::CftlCommandLoadPackages(CdmClassManager* p_pClassManager, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpClassManager(p_pClassManager)

{
}

CftlCommandLoadPackages::~CftlCommandLoadPackages()
{

}

bool CftlCommandLoadPackages::CheckValid()
{
    return CHKPTR(m_rpClassManager);
}


int CftlCommandLoadPackages::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQuery(GetSqlDatabase());
    cQuery.prepare("select URI, System_Package from WMS_CLASS_PACKAGE where SchemeId = ?");
    cQuery.addBindValue((int)m_rpClassManager->GetSchemeId());

    QList<CdmPackage*> qlUnresolvedPackages;

    if (SUCCESSFULL(ExecuteQuery(cQuery)))
    {
       cQuery.first();

       while(cQuery.isValid())
       {
           QString qstrKeyname = cQuery.value(0).toString();
           bool bSystemFlag = cQuery.value(1).toBool();

           CdmPackage* pPackage = CdmDataAccessHelper::CreatePackage(m_rpClassManager->GetSchemeId(), qstrKeyname);
           pPackage->SetSystemPackage(bSystemFlag);
           qlUnresolvedPackages.append(pPackage);
           cQuery.next();
       }

       ResolvePackages(qlUnresolvedPackages);
	   iRet = CdmLogging::eDmOk;
    }

    return iRet;
}

void CftlCommandLoadPackages::ResolvePackages(QList<CdmPackage*>& p_rqlUnresolvedPackages)
{
    for (int iPos = 0; iPos < p_rqlUnresolvedPackages.count(); ++iPos)
    {
        CdmPackage* pPackage = p_rqlUnresolvedPackages[iPos];

        if (CHKPTR(pPackage))
        {
            if(pPackage->GetKeyname().contains(".") && !pPackage->GetParent())
            {
                INFO("Resolve Package");
				if (!ResolvePackage(pPackage, p_rqlUnresolvedPackages))
				{
					CdmDataAccessHelper::AddPackageToClassManager(m_rpClassManager, pPackage);
				}
            }
            else if(pPackage->GetKeyname().contains(".") == false)
            {
                INFO("Add Package to ClassManager");
                CdmDataAccessHelper::AddPackageToClassManager(m_rpClassManager, pPackage);
            }
            else
            {
                ERR("Invalid Package Name");
            }
        }
    }
}

bool CftlCommandLoadPackages::ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages)
{
	bool bRet = false;

    if (CHKPTR(p_pPackage))
    {
		QString qstrOriginalKeyname = p_pPackage->GetKeyname();
		int iLastDot = qstrOriginalKeyname.lastIndexOf(".");

        if (iLastDot > 0)
        {
            QString qstrParentPackageKeyname = p_pPackage->GetKeyname().mid(0, iLastDot);
            INFO("Parent Package Name: " + qstrParentPackageKeyname);

            for (int iPos = 0; iPos < p_rqlUnresolvedPackages.count(); ++iPos)
            {
                CdmPackage* pPackage = p_rqlUnresolvedPackages[iPos];

                if (CHKPTR(pPackage) && pPackage->GetKeyname() == qstrParentPackageKeyname)
                {
                    INFO("Parent Package found. Keyname: " + pPackage->GetKeyname());
                    p_pPackage->SetParent(pPackage);
					CdmDataAccessHelper::SetKeyname(p_pPackage, qstrOriginalKeyname.mid(iLastDot + 1, qstrOriginalKeyname.length() - iLastDot - 1));
					
					pPackage->AddChild(p_pPackage);
					p_pPackage->ResetNewModified();
                    break;
                }
            }

            if (p_pPackage->GetParent())
            {
				bRet = true;
            }
			else
			{
				WARNING("No Parent Package found");
			}
        }
        else
        {
            ERR("Invalid Package Keyname or unresolvable");
        }
    }

	return bRet;
}
