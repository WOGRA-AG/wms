#include "CwnCommandLoadPackages.h"

#include "CdmPackage.h"

#include "CwnCommandStdHeader.h"


CwnCommandLoadPackages::CwnCommandLoadPackages(CdmClassManager *p_pClassManager, CwnDataAccess *p_pDataAccess, QString schema)
: CwnCommandBase(p_pDataAccess),
m_rpClassManager(p_pClassManager),
schema(schema)
{

}

CwnCommandLoadPackages::~CwnCommandLoadPackages()
{

}

QString CwnCommandLoadPackages::createQuery()
{
    QString query = QString("{ \"order\" : \"depth_first\", \"prune_evaluator\" : { \"name\" : \"none\", \"language\" : \"builtin\"}, \"uniqueness\" : \"node_global\", \"relationships\" : {\"direction\" : \"out\", \"type\" : \"pkglevel\"}}");
    return query;
}

void CwnCommandLoadPackages::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResultList = static_cast<const QVariantList*>(parsedJson.data());

    // NO ERROR CHECK
    //qDebug() << this->qResultList;
    QList<CdmPackage*> qlUnresolvedPackages;
    QList<QVariant>::ConstIterator it;

    for(it=qResultList->begin();it!=qResultList->end();++it)
    {

        const QVariantMap* infoMap = static_cast<const QVariantMap*>(it->data());
        const QVariantList* nodeList = static_cast<const QVariantList*>(infoMap->find("nodes")->data());

        QString keyname;
        bool bSystemFlag = false;

        QList<QVariant>::ConstIterator itr;
        for(itr=nodeList->begin()+1;itr!=nodeList->end();++itr)
        {
            const QVariantMap* SpeInfoMap = static_cast<const QVariantMap*>(itr->data());
            const QVariantMap* dataMap = static_cast<const QVariantMap*>(SpeInfoMap->find("data")->data());


            keyname+=dataMap->find("URIname")->toString();
            if(itr!=nodeList->end()-1)
                keyname+=".";

            bSystemFlag = dataMap->find("SystemPackage")->toBool();
        }
        //qDebug() << keyname;
        //qDebug() << bSystemFlag;
        //qDebug() << "\n\n\n";

        CdmPackage* pPackage = CdmDataAccessHelper::CreatePackage(m_rpClassManager->GetSchemeId(), keyname);
        pPackage->SetSystemPackage(bSystemFlag);
        qlUnresolvedPackages.append(pPackage);

    }

    ResolvePackages(qlUnresolvedPackages);
    Ret = CdmLogging::eDmOk;

}

int CwnCommandLoadPackages::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createQuery();
    //ERR(payload);
    queryCausedError = payload;
    ConnectAndExecute(traverseDepthSearchFullPath,payload,nullptr,QString("%1").arg(m_rpClassManager->GetSchemeId()));
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    //qDebug() << iRet;
    return iRet;
}

bool CwnCommandLoadPackages::CheckValid()
{
    return CHKPTR(m_rpClassManager);
}

void CwnCommandLoadPackages::ResolvePackages(QList<CdmPackage*>& p_rqlUnresolvedPackages)
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

    for (int iPos = 0; iPos < p_rqlUnresolvedPackages.count(); ++iPos)
    {
        CdmPackage* pPackage = p_rqlUnresolvedPackages[iPos];
        QString qstrOriginalKeyname = pPackage->GetKeyname();
        int iLastDot = qstrOriginalKeyname.lastIndexOf(".");

        if (iLastDot > 0)
        {
            CdmDataAccessHelper::SetKeyname(pPackage, qstrOriginalKeyname.mid(iLastDot + 1, qstrOriginalKeyname.length() - iLastDot - 1));
        }
    }
}

bool CwnCommandLoadPackages::ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages)
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
