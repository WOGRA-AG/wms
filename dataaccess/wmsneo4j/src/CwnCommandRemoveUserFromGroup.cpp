#include "CwnCommandRemoveUserFromGroup.h"

// System and QT Includes

#include "CwnCommandStdHeader.h"

CwnCommandRemoveUserFromGroup::CwnCommandRemoveUserFromGroup(CwnDataAccess *m_rpDataAccess) : CwnCommandBase(m_rpDataAccess)
{
    this->groupId = -1;
    this->userId = -1;
}

CwnCommandRemoveUserFromGroup::~CwnCommandRemoveUserFromGroup()
{

}

void CwnCommandRemoveUserFromGroup::setGroupId(qint64 groupId)
{
    this->groupId = groupId;
}

qint64 CwnCommandRemoveUserFromGroup::getGroupId()
{
    return groupId;
}

void CwnCommandRemoveUserFromGroup::setUserId(qint64 userId)
{
    this->userId = userId;
}

qint64 CwnCommandRemoveUserFromGroup::getUserId()
{
    return userId;
}

QString CwnCommandRemoveUserFromGroup::createQuery()
{
    QString query = QString("MATCH (a:User)-[r:memberOf]->(b:Group) WHERE id(a) = %1 AND id(b) = %2 DELETE r RETURN count(r);")
                 .arg(getUserId())
                 .arg(getGroupId());

    return query;
}

void CwnCommandRemoveUserFromGroup::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            if((list->at(0).toInt()>0))
            {
                Ret = 1;
            }
        }
        else{
            EC(eDmFalse);
        }
    }
}

int CwnCommandRemoveUserFromGroup::Execute()
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

bool CwnCommandRemoveUserFromGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupId()<0 ||
        getUserId()<0)
    {
        bRet = false;
    }

    return bRet;

}
