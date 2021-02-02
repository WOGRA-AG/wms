#include "CwnCommandFindUserByEmail.h"

#include "CumUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandFindUserByEmail::CwnCommandFindUserByEmail(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{

}

CwnCommandFindUserByEmail::~CwnCommandFindUserByEmail()
{

}

void CwnCommandFindUserByEmail::setEmail(QString email)
{
    this->email = email;
}

QString CwnCommandFindUserByEmail::getEmail()
{
    return email;
}

QString CwnCommandFindUserByEmail::createQuery()
{
    QString query = QString("MATCH(n:User) WHERE n.email = \'%1\' RETURN id(n),n;")
                        .arg(getEmail());

    return query;
}

void CwnCommandFindUserByEmail::interpretAnswer(QVariant &Ret)
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

            result = new CumUser(list->at(0).toInt(), nullptr);
            const QVariantMap* rowMap = static_cast<const QVariantMap*>(list->at(1).data());

            result->SetActive(rowMap->find("active")->toBool());
            result->SetAdministrator(rowMap->find("admin")->toBool());
            result->SetEmail(rowMap->find("email")->toString());
            result->SetLastName(rowMap->find("lastname")->toString());
            result->SetFirstName(rowMap->find("firstname")->toString());
            result->SetLogin(rowMap->find("login")->toString());
            result->SetPassword(rowMap->find("pass")->toString());
            result->SetEncrypted(true);
            result->SetIdentityKey(rowMap->find("identkey")->toString());
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No User found by email.");
        }
    }
}

int CwnCommandFindUserByEmail::Execute()
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

bool CwnCommandFindUserByEmail::CheckValid()
{
    bool bRet = true;

    if (getEmail().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}

CumUser* CwnCommandFindUserByEmail::getResult()
{
    return result;
}
