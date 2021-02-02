#include "CwnCommandCreateUserGroup.h"

#include "CwnCommandStdHeader.h"

CwnCommandCreateUserGroup::CwnCommandCreateUserGroup(CwnDataAccess *m_rpDataAccess) : CwnCommandBase(m_rpDataAccess)
{

}

CwnCommandCreateUserGroup::~CwnCommandCreateUserGroup()
{

}

void CwnCommandCreateUserGroup::setGroupName(QString groupName)
{
    this->groupName = groupName;
}

QString CwnCommandCreateUserGroup::getGroupName()
{
    return groupName;
}

QString CwnCommandCreateUserGroup::createQuery()
{
    QString query = QString("MERGE (group:Group { groupname : \'%1\'}) ON CREATE SET group={groupname : \'%1\', active: '1'}, group.onCreate = true WITH group, EXISTS(group.onCreate) as onCreate REMOVE group.onCreate RETURN id(group),onCreate;")
                 .arg(getGroupName());
    return query;
}

void CwnCommandCreateUserGroup::interpretAnswer(QVariant &Ret)
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
        const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
        const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());
        //qDebug() << rowList[1].toBool();
        if(list->at(1).toBool())
        {
            Ret = list->at(0);
            //qDebug() << rowList[0].toInt();
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("The group name is already in use.");
        }
    }
}

int CwnCommandCreateUserGroup::Execute()
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

bool CwnCommandCreateUserGroup::CheckValid()
{
    bool bRet = true;

    if (getGroupName().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}
