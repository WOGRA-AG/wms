// WMS Includes
#include "CdmLogging.h"
#include "CdmClass.h"

// Own Includes
#include "CwnJournal.h"
#include "CwnCommandDeleteClass.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeleteClass::CwnCommandDeleteClass(long p_lClassId, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lClassId(p_lClassId)
{
}

CwnCommandDeleteClass::~CwnCommandDeleteClass()
{
}

QString CwnCommandDeleteClass::createQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (c:Class) WHERE id(c)=%1 "
                        "OPTIONAL MATCH (c)-[:class_group]->(cg:WMS_CLASS_GROUP) "
                        "WITH c,cg "
                        "OPTIONAL MATCH (c)-[:Class_Validator]->(cv:WMS_CLASS_VALIDATION) "
                        "WITH c,cg,cv "
                        "OPTIONAL MATCH (c)-[:Class_Method]->(cmet:WMS_CLASS_METHOD) "
                        "WITH c,cg,cv,cmet "
                        "OPTIONAL MATCH (c)-[:hasObjectContainer]->(ol) "
                        "WITH c,cg,cv,cmet,ol "
                        "OPTIONAL MATCH (ol)-[:hasObjects]->(o:WMS_DM_OBJECT) "
                        "WITH c,cg,cv,cmet,ol,o "
                        "OPTIONAL MATCH (o)-[:Object_value]->(v:WMS_VALUE) "
                        "WITH c,cg,cv,cmet,ol,o,v "
                        "DETACH DELETE v,o,ol,cmet,cv,cg,c "
                        "RETURN DISTINCT 1;").arg(m_lClassId);

    return qstrQuery;
}

bool CwnCommandDeleteClass::CheckValid()
{
    return (m_lClassId > 0);
}

void CwnCommandDeleteClass::interpretAnswer(QVariant &Ret)
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
            Ret=1;
        }
        else
        {
            Ret = EC(eDmInvalidDeleteStatement);
            ERR("The query execution failed!");
        }
    }
}

int CwnCommandDeleteClass::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug()<<payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}
