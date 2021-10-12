#include "CwnCommandGetUserGroupMemberList.h"

#include "CwnCommandStdHeader.h"


CwnCommandGetUserGroupMemberList::CwnCommandGetUserGroupMemberList(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->userId = -1;
}

CwnCommandGetUserGroupMemberList::~CwnCommandGetUserGroupMemberList()
{

}

QString CwnCommandGetUserGroupMemberList::createQuery()
{
    QString query = QString("MATCH (user:User)-[:memberOf]->(group:Group) WHERE id(user) = %1 RETURN id(group),group.groupname;")
            .arg(getUserId());
    return query;
}

void CwnCommandGetUserGroupMemberList::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();

        if(dataListCon->count()>0)
        {
           QList<QVariant>::ConstIterator it;
           for(it=dataListCon->begin();it!=dataListCon->end();it++) // loading each class
           {
               const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
               const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                CumUserGroup* group = new CumUserGroup(row->at(0).toInt(), nullptr);
                group->SetGroupName(row->at(1).toString());
                this->p_rqvlUserGroups.append(group);
            }
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("User found who has no Group.");
        }
    }
}

int CwnCommandGetUserGroupMemberList::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandGetUserGroupMemberList::CheckValid()
{
    bool bRet = true;

    if (getUserId()<0)
    {
        bRet = false;
    }

    return bRet;
}

QList<CumUserGroup*> CwnCommandGetUserGroupMemberList::getResult()
{
    return this->p_rqvlUserGroups;
}

void CwnCommandGetUserGroupMemberList::setUserId(qint64 userId)
{
    this->userId = userId;
}

qint64 CwnCommandGetUserGroupMemberList::getUserId()
{
    return this->userId;
}
