#include "CwnCommandGetListOfUsersInList.h"

#include "CumUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandGetListOfUsersInList::CwnCommandGetListOfUsersInList(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->groupId = -1;
}

CwnCommandGetListOfUsersInList::~CwnCommandGetListOfUsersInList()
{

}

QString CwnCommandGetListOfUsersInList::createQuery()
{
    QString query = QString("MATCH (group:Group)<-[:memberOf]-(user:User) WHERE id(group) = %1 RETURN id(user),user;")
            .arg(getGroupId());
    return query;
}

void CwnCommandGetListOfUsersInList::interpretAnswer(QVariant &Ret)
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
               CumUser* user = new CumUser(row->at(0).toInt(), nullptr);

                //qDebug() << rowList;

                const QVariantMap* rowMap = static_cast<const QVariantMap*>(row->at(1).data());

                user->SetActive(rowMap->find("active")->toBool());
                user->SetAdministrator(rowMap->find("admin")->toBool());
                user->SetEmail(rowMap->find("email")->toString());
                user->SetFirstName(rowMap->find("firstname")->toString());
                user->SetLastName(rowMap->find("lastname")->toString());
                user->SetLogin(rowMap->find("login")->toString());
                user->SetPassword(rowMap->find("pass")->toString());

                this->p_qvlUsers.append(user);
            }
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("There are no Users in this Group.");
        }
    }
}

int CwnCommandGetListOfUsersInList::Execute()
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

bool CwnCommandGetListOfUsersInList::CheckValid()
{
    bool bRet = true;

    if (getGroupId()<0)
    {
        bRet = false;
    }

    return bRet;
}

QLinkedList<CumUser*> CwnCommandGetListOfUsersInList::getResult()
{
    return this->p_qvlUsers;
}

void CwnCommandGetListOfUsersInList::setGroupId(long groupId)
{
    this->groupId = groupId;
}

long CwnCommandGetListOfUsersInList::getGroupId()
{
    return this->groupId;
}
