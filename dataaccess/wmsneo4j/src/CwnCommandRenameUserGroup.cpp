#include "CwnCommandRenameUserGroup.h"
#include "CdmSessionManager.h"
#include "CumUser.h"

#include "CwnCommandStdHeader.h"

CwnCommandRenameUserGroup::CwnCommandRenameUserGroup(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->groupid = -1;
}

CwnCommandRenameUserGroup::~CwnCommandRenameUserGroup()
{

}

void CwnCommandRenameUserGroup::setGroupId(long groupid)
{
    this->groupid = groupid;
}


void CwnCommandRenameUserGroup::setGroupname(QString groupname)
{
    this->groupname = groupname;
}

QString CwnCommandRenameUserGroup::getGroupname()
{
    return groupname;
}

long CwnCommandRenameUserGroup::getGroupId()
{
    return groupid;
}

QString CwnCommandRenameUserGroup::createQuery()
{
    QString query = QString("MATCH (group:Group) WHERE id(group) = %1 OPTIONAL MATCH (groupNameExist:Group {groupname: \'%2\'}) WITH group, groupNameExist WHERE groupNameExist IS nullptr SET group.groupname = \'%3\' RETURN group, groupNameExist;")
            .arg(getGroupId())
            .arg(getGroupname())
            .arg(getGroupname());

    return query;
}

void CwnCommandRenameUserGroup::interpretAnswer(QVariant &Ret)
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
            //qDebug() << rowMap;
            Ret = 1;
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("Could not update groupname. The groupname already exist.");
        }
    }
}

int CwnCommandRenameUserGroup::Execute()
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

bool CwnCommandRenameUserGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupname().isEmpty() ||
        getGroupId()<0)
    {
        bRet = false;
    }

    return bRet;
}
