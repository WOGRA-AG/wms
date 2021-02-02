#include "CwnCommandDeletePackage.h"

#include "CdmPackage.h"
#include "CdmModelElement.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeletePackage::CwnCommandDeletePackage(CdmPackage* p_pPackage, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_pPackage(p_pPackage)
{
    // Start Transaction
}

CwnCommandDeletePackage::~CwnCommandDeletePackage()
{

}

QString CwnCommandDeletePackage::createQuery()
{
    QStringList pieces = m_pPackage->GetPackageString().split(".");

    if(pieces.count()>1)
    {

        QString uniquematch = QString("(s:Scheme)-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(pieces[0]);

        for(int i=1;i<pieces.count()-2;i++)
        {
            uniquematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(pieces[i]);
        }
        uniquematch += QString("-[l:pkglevel]->(p:Package {URIname:\'%1\'})").arg(pieces[pieces.length()-1]);

        QString query = QString("MATCH %1 WHERE id(s)=%2 AND p.URIname=\'%3\' WITH l,p OPTIONAL MATCH w=(p)-[:pkglevel *]->() WITH l,w,p OPTIONAL MATCH q=(p)-[:pkglevel|:Pkg_Contains_Class *]->() FOREACH(k IN RELATIONSHIPS(q)| DELETE k) DELETE l,p FOREACH(x IN nodes(w)| DELETE x) RETURN 1;")
                .arg(uniquematch)
                .arg(m_pPackage->GetSchemeId())
                .arg(pieces[pieces.count()-1]);
        return query;
    }
    else
    {
         QString uniquematch = QString("(s:Scheme)-[l:pkglevel]->(p:Package)");
         QString query = QString("MATCH %1 WHERE id(s)=%2 AND p.URIname=\'%3\' WITH l,p OPTIONAL MATCH w=(p)-[:pkglevel *]->() WITH l,w,p OPTIONAL MATCH q=(p)-[:pkglevel|:Pkg_Contains_Class *]->() FOREACH(k IN RELATIONSHIPS(q)| DELETE k) DELETE l,p FOREACH(x IN nodes(w)| DELETE x) RETURN 1;")
                 .arg(uniquematch)
                 .arg(m_pPackage->GetSchemeId())
                 .arg(pieces[0]);
         return query;
    }
}

void CwnCommandDeletePackage::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        if(dataList->count()>0)
        {
            INFO("Package deleted.");
            QList<CdmPackage*> qlChildren;
            m_pPackage->GetChildren(qlChildren);
            DeletePackageChildren(qlChildren);
            CdmPackage::RemovePackageFromClasses(m_pPackage);
            DELPTR(m_pPackage);
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = -1014;
            ERR("No Nodes found by keyname.");
        }
    }
}


int CwnCommandDeletePackage::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug() << payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandDeletePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

void CwnCommandDeletePackage::DeletePackageChildren(QList<CdmPackage*>& p_rqlChildren)
{
    for (int iPos = 0; iPos < p_rqlChildren.count(); ++iPos)
    {
        CdmPackage* pPackageTemp = p_rqlChildren[iPos];

        if (CHKPTR(pPackageTemp))
        {
            CdmPackage::RemovePackageFromClasses(pPackageTemp);
            QList<CdmPackage*> qlChildren;
            pPackageTemp->GetChildren(qlChildren);
            DeletePackageChildren(qlChildren);

            DELPTR(pPackageTemp);

        }
    }
}
