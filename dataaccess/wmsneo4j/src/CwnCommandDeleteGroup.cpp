#include "CwnCommandDeleteGroup.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeleteGroup::CwnCommandDeleteGroup(CwnDataAccess *m_rpDataAccess) : CwnCommandBase(m_rpDataAccess)
{
    this->groupId = -1;
}

CwnCommandDeleteGroup::~CwnCommandDeleteGroup()
{

}

void CwnCommandDeleteGroup::setGroupId(long groupId)
{
    this->groupId = groupId;
}

long CwnCommandDeleteGroup::getGroupId()
{
    return groupId;
}

QString CwnCommandDeleteGroup::createQuery()
{
    QString query = QString("MATCH(n:Group) WHERE id(n)=%1 OPTIONAL MATCH (n)<-[:userGroupValue]-(v) DETACH DELETE v,n RETURN 1;")
                 .arg(getGroupId());
    return query;
}

void CwnCommandDeleteGroup::interpretAnswer(QVariant &Ret)
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
        Ret = -1014;
        ERR("No Groups found by Id");
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            Ret = 1;
        }
        else
        {
            Ret = -1014;
            ERR("No Groups found by Id");
        }
    }
}

int CwnCommandDeleteGroup::Execute()
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

bool CwnCommandDeleteGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupId()<0)
    {
        bRet = false;
    }

    return bRet;
}
