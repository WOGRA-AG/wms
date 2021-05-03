#include "CwnCommandGetUserList.h"

#include "CumUser.h"

#include "CwnCommandStdHeader.h"
#include "CwnHelper.h"


CwnCommandGetUserList::CwnCommandGetUserList(QString p_qstrUserLoginNameEmail, CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess),m_qstrUserLoginNameEmail(p_qstrUserLoginNameEmail),m_specialSearch(true)
{

}

CwnCommandGetUserList::CwnCommandGetUserList(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess),m_specialSearch(false)
{

}


CwnCommandGetUserList::~CwnCommandGetUserList()
{

}

QString CwnCommandGetUserList::createQuery()
{
    QString query = QString("MATCH (n:User) RETURN id(n),n;");
    return query;
}

QString CwnCommandGetUserList::createSearchQuery()
{

    QString query = QString("MATCH (n:User) WHERE n.email =~\'(?i).*%1.*\' OR n.login =~\'(?i).*%1.*\' OR n.firstname =~\'(?i).*%1.*\' OR n.lastname =~\'(?i).*%1.*\' RETURN DISTINCT id(n), n")
                        .arg(CwnHelper::MaskStringForChanges(m_qstrUserLoginNameEmail.toLower()));
    return query;
}

void CwnCommandGetUserList::interpretAnswer(QVariant &Ret)
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
            INFO("There are no Users in the Database.");
        }
    }
}

int CwnCommandGetUserList::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = (m_specialSearch)?createJson(createSearchQuery()):createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandGetUserList::CheckValid()
{
    bool bRet = true;

    if (/* DISABLES CODE */ (false))
    {
        bRet = false;
    }

    return bRet;
}

QList<CumUser*> CwnCommandGetUserList::getResult()
{
    return this->p_qvlUsers;
}
