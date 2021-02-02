#include "CwnCommandFindUserGroupByName.h"

#include "CumUserGroup.h"

#include "CwnCommandStdHeader.h"

CwnCommandFindUserGroupByName::CwnCommandFindUserGroupByName(QString m_qstrName, CwnDataAccess* m_rpDataAccess)
    : CwnCommandBase(m_rpDataAccess), m_qstrGroupName(m_qstrName), m_pGroup(nullptr)
{

}

CwnCommandFindUserGroupByName::~CwnCommandFindUserGroupByName()
{

}

QString CwnCommandFindUserGroupByName::createQuery()
{
    QString query = QString("MATCH(n:Group) WHERE n.groupname=\'%1\' RETURN id(n),n.groupname;")
            .arg(m_qstrGroupName);
    return query;
}

void CwnCommandFindUserGroupByName::interpretAnswer(QVariant &Ret)
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

            CumUserGroup *result = new CumUserGroup(list->at(0).toInt(), nullptr);
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

int CwnCommandFindUserGroupByName::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit, payload, nullptr, nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandFindUserGroupByName::CheckValid()
{
    bool bRet = true;

    if(m_qstrGroupName.isEmpty())
    {
        bRet = false;
    }
    return bRet;
}

CumUserGroup* CwnCommandFindUserGroupByName::GetResult()
{
    return m_pGroup;
}
