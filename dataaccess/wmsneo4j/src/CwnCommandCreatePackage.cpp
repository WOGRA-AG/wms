// WMS Includes
#include "CdmPackage.h"
#include "CwnCommandCreatePackage.h"

#include "CwnCommandStdHeader.h"


CwnCommandCreatePackage::CwnCommandCreatePackage(CdmPackage* p_pPackage, CwnDataAccess* p_pDataAccess):CwnCommandBase(p_pDataAccess),
    m_pPackage(p_pPackage)
{

}

CwnCommandCreatePackage::~CwnCommandCreatePackage()
{
}

bool CwnCommandCreatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}

QString CwnCommandCreatePackage::createQuery()
{

    QString qstrSystemPackage = CwnHelper::ConvertBoolToString(m_pPackage->IsSystemPackage());
    QStringList pieces = m_pPackage->GetPackageString().split(".");

    //qDebug() << pieces;

    if(pieces.count()>1)
    {

        QString uniquematch = QString("(s:Scheme)-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(pieces[0]);

        for(int i=1;i<pieces.count()-1;i++)
        {
            uniquematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(pieces[i]);
        }
        uniquematch += QString("-[:pkglevel]->(p:Package)");

        QString father = QString("(q:Scheme)");

        for(int j=0;j<pieces.count()-2;j++)
        {
            father += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(pieces[j]);
        }
        father += QString("-[:pkglevel]->(k:Package {URIname:\'%1\'})").arg(pieces[pieces.count()-2]);

        QString query = QString("MATCH e=%1 WHERE id(s)=%2 AND p.URIname=\'%3\' WITH count(e) AS num WHERE num=0 MATCH %4 WHERE id(q)=%5 CREATE (k)-[:pkglevel]->(n:Package {URIname:\'%6\',SystemPackage:\'%7\'}) RETURN n;")
                .arg(uniquematch)
                .arg(m_pPackage->GetSchemeId())
                .arg(pieces[pieces.count()-1])
                .arg(father)
                .arg(m_pPackage->GetSchemeId())
                .arg(pieces[pieces.count()-1])
                .arg(qstrSystemPackage);
        return query;
    }
    else if(pieces.count() == 1)
    {
         QString uniquematch = QString("(s:Scheme)-[:pkglevel]->(p:Package)");
         QString father = QString("(q:Scheme) WHERE id(q)=%1").arg(m_pPackage->GetSchemeId());
         QString query = QString("MATCH e=%1 WHERE id(s)=%2 AND p.URIname=\'%3\' WITH count(e) AS num WHERE num=0 MATCH %4 Create (q)-[:pkglevel]->(n:Package {URIname:\'%5\',SystemPackage:\'%6\'}) RETURN n;")
                 .arg(uniquematch)
                 .arg(m_pPackage->GetSchemeId())
                 .arg(pieces[0])
                 .arg(father)
                 .arg(pieces[0])
                 .arg(qstrSystemPackage);
         return query;
    }
    else if(pieces.count() <1)
    {
        //Not possible
        return QString("42");
    }
    return QString("42");

}

int CwnCommandCreatePackage::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

void CwnCommandCreatePackage::interpretAnswer(QVariant &Ret)
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
        Ret=-1;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            INFO("Package inserted.");
            m_pPackage->ResetNewModified();
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = -1;
            ERR("Packagename ist not unique on this pkglevel");
        }

    }
}
