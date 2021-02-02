#include "CwnCommandAddUserToGroup.h"

#include "CwnCommandStdHeader.h"

CwnCommandAddUserToGroup::CwnCommandAddUserToGroup(CwnDataAccess* m_rpDataAccess) : CwnCommandBase(m_rpDataAccess)
{
    this->groupId = -1;
    this->userId = -1;
}

CwnCommandAddUserToGroup::~CwnCommandAddUserToGroup()
{

}

void CwnCommandAddUserToGroup::setGroupId(long groupId)
{
    this->groupId = groupId;
}

long CwnCommandAddUserToGroup::getGroupId()
{
    return groupId;
}

void CwnCommandAddUserToGroup::setUserId(long userId)
{
    this->userId = userId;
}

long CwnCommandAddUserToGroup::getUserId()
{
    return userId;
}

QString CwnCommandAddUserToGroup::createQuery()
{
    QString query = QString("MATCH (a:User),(b:Group) WHERE id(a) = %1 AND id(b) = %2 MERGE (a)-[r:memberOf]->(b) RETURN type(r);")
                 .arg(getUserId())
                 .arg(getGroupId());

    queryCausedError = query;
    return query;
}

void CwnCommandAddUserToGroup::interpretAnswer(QVariant &Ret)
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
        ERR("Neither User nor Group found by ids.");
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
            ERR("Neither User nor Group found by ids.");
        }
    }
}

int CwnCommandAddUserToGroup::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = EC(eDmOk);
    return iRet;

}

bool CwnCommandAddUserToGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupId()<0 ||
        getUserId()<0)
    {
        bRet = false;
    }

    return bRet;

}
