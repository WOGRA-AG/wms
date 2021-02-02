#include "CwnCommandUpdateScheme.h"
#include "CdmScheme.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandUpdateScheme::CwnCommandUpdateScheme(CdmScheme* p_pScheme, CwnDataAccess *p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
m_rpScheme(p_pScheme)
{

}

CwnCommandUpdateScheme::~CwnCommandUpdateScheme()
{

}

QString CwnCommandUpdateScheme::createQuery()
{

    QString query = QString("MATCH e=(s:Scheme) WHERE s.schemename=\'%1\' AND NOT id(s)=%2 WITH count(e) AS num WHERE num=0 MATCH (q:Scheme) WHERE id(q)=%4 SET q.schemename=\'%5\', q.version=\'%6\' WITH q OPTIONAL MATCH (q)-[r:rights]->(u) DELETE r RETURN q;")
            .arg(m_rpScheme->GetSchemeName())
            .arg(m_rpScheme->GetId())
            .arg(m_rpScheme->GetId())
            .arg(m_rpScheme->GetSchemeName())
            .arg(m_rpScheme->GetVersion());
    return query;

}

void CwnCommandUpdateScheme::interpretAnswer(QVariant &Ret)
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
        Ret=EC(eDmInvalidSelectStatement);

    }
    else
    {
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {
            INFO("Scheme updated.");

            Ret = GetDataAccess()->SaveRights(m_rpScheme->GetRights(),
                                                  m_rpScheme->GetId(),
                                                  "Scheme",
                                                  "DatabaseId");
        }
        else
        {
            Ret = -1;
            ERR("Could not update Scheme!");
        }
    }
}

int CwnCommandUpdateScheme::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandUpdateScheme::CheckValid()
{
    return CHKPTR(m_rpScheme);
}
