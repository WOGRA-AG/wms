#include "CwnCommandDeleteScheme.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeleteScheme::CwnCommandDeleteScheme(CwnDataAccess *m_rpDataAccess, QString p_qstrKeyname)
    : CwnCommandBase(m_rpDataAccess),
      m_qstrKeyname(p_qstrKeyname)
{
    // Start Transaction
}

CwnCommandDeleteScheme::~CwnCommandDeleteScheme()
{

}

QString CwnCommandDeleteScheme::createQuery()
{
    QString query = QString("MATCH (s:Scheme) WHERE s.schemename=\'%1\' "
                            "WITH s "
                            "OPTIONAL MATCH (s)-[:languages]->(l:WMS_LANGUAGES) "
                            "WITH s,l "
                            "OPTIONAL MATCH (s)-[:hasClass]->(c:Class) "
                            "WITH s,l,c "
                            "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:class_group]->(cg:WMS_CLASS_GROUP) "
                            "WITH s,l,c,cg "
                            "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:Class_Validator]->(cv:WMS_CLASS_VALIDATION) "
                            "WITH s,l,c,cg,cv "
                            "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:Class_Method]->(cmet:WMS_CLASS_METHOD) "
                            "WITH s,l,c,cg,cv,cmet "
                            "OPTIONAL MATCH k=(s)-[:pkglevel *]->(:Package)-[:Pkg_Contains_Class]->(c) "
                            "WITH s,l,c,cg,cv,cmet,k "
                            "OPTIONAL MATCH (s)-[:hasClass]->(c)-[:WMS_Member]->(i:WMS_CLASS_MEMBER) "
                            "WITH s,l,c,cg,cv,cmet,k,i "
                            "OPTIONAL MATCH (c)-[:hasObjectContainer]->(ol:WMS_DM_OBJECTLIST) "
                            "WITH s,l,c,cg,cv,cmet,k,i,ol "
                            "OPTIONAL MATCH (ol)-[:hasObjects]->(o:WMS_DM_OBJECT) "
                            "WITH s,l,c,cg,cv,cmet,k,i,ol,o "
                            "OPTIONAL MATCH (o)-[:Object_value]->(v:WMS_VALUE) "
                            "WITH s,l,c,cg,cv,cmet,k,i,ol,o,v "
                            "DETACH DELETE v,o,ol,i,cmet,cv,cg,k,c,l,s "
                            "RETURN DISTINCT 1")
        .arg(m_qstrKeyname);

    return query;
}

QString CwnCommandDeleteScheme::createQueryForNodesWithNoRelationsships()
{
    QString query = QString("OPTIONAL MATCH (n) "
                            "WHERE NOT((n)--()) AND NOT(n:User) AND NOT(n:Group) AND NOT(n:Scheme) "
                            "DELETE (n) RETURN DISTINCT 1");
    return query;
}

void CwnCommandDeleteScheme::interpretAnswer(QVariant &Ret)
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
            INFO("Schemes deleted.");
            Ret = 1;

        }
        else
        {
            Ret = -1;
            ERR("No Schemes found by keyname or Nodes with no relationsships could not be deleted.");
        }
    }
}


int CwnCommandDeleteScheme::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug() << payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    this->answer=nullptr;

    if(iRet>0)
    {
        payload = createJson(createQueryForNodesWithNoRelationsships());
        queryCausedError = payload;
        ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
        QVariant Ret;
        interpretAnswer(Ret);
        iRet = Ret.toInt();
    }

    return iRet;
}

bool CwnCommandDeleteScheme::CheckValid()
{
    return (!m_qstrKeyname.isEmpty());
}
