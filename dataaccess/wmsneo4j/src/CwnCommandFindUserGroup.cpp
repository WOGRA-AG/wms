#include "CwnCommandFindUserGroup.h"

#include "CumUserGroup.h"

#include "CwnCommandStdHeader.h"


CwnCommandFindUserGroup::CwnCommandFindUserGroup(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->groupid = -1;
}

CwnCommandFindUserGroup::~CwnCommandFindUserGroup()
{

}

void CwnCommandFindUserGroup::setGroupid(long groupid)
{
    this->groupid = groupid;
}

long CwnCommandFindUserGroup::getGroupid()
{
    return groupid;
}

QString CwnCommandFindUserGroup::createQuery()
{
    QString query = QString("MATCH(n:Group) WHERE id(n)=%1 RETURN id(n),n.groupname;")
                 .arg(getGroupid());
    return query;
}

void CwnCommandFindUserGroup::interpretAnswer(QVariant &Ret)
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
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            result = new CumUserGroup(list->at(0).toInt(), nullptr);
            result->SetGroupName(list->at(1).toString());
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No groups found by Groupname.");
        }
    }
}

int CwnCommandFindUserGroup::Execute()
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

bool CwnCommandFindUserGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupid()<0)
    {
        bRet = false;
    }

    return bRet;
}

CumUserGroup* CwnCommandFindUserGroup::getResult()
{
    return result;
}

