#include "CwnCommandFindUser.h"

#include <QCryptographicHash>
#include "CumUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandFindUser::CwnCommandFindUser(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess),result(nullptr)
{
    this->userid = -1;
    this->decider = -1;
}

CwnCommandFindUser::~CwnCommandFindUser()
{

}

void CwnCommandFindUser::setLogin(QString login)
{
    this->login = login;
}

QString CwnCommandFindUser::getLogin()
{
    return login;
}

void CwnCommandFindUser::setPassw(QString passw)
{
    QString qstrRet = passw;
    QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    this->passw = qstrValue;
}

QString CwnCommandFindUser::getPassw()
{
    return passw;
}

void CwnCommandFindUser::setUserId(long userid)
{
    this->userid = userid;
}

long CwnCommandFindUser::getUserId()
{
    return userid;
}

void CwnCommandFindUser::setDecider(int decider)
{
    this->decider = decider;
}

int CwnCommandFindUser::getDecider()
{
    return decider;
}

void CwnCommandFindUser::setUserEmail(QString useremail)
{
    this->useremail = useremail;
}

QString CwnCommandFindUser::getUserEmail()
{
    return useremail;
}

void CwnCommandFindUser::setUserIdentKey(QString useridentkey)
{
    this->useridentkey = useridentkey;
}

QString CwnCommandFindUser::getUserIdentKey()
{
    return useridentkey;
}


QString CwnCommandFindUser::createQuery()
{
    QString query;

    if(getDecider() == 0)
    {
        query = QString("MATCH(n:User) WHERE n.login = \'%1\' AND n.pass = \'%2\' RETURN id(n),n;")
                        .arg(getLogin())
                        .arg(getPassw());
    }
    else if(getDecider() == 1)
    {
        query = QString("MATCH(n:User) WHERE id(n) = %1 RETURN id(n),n;")
                        .arg(getUserId());
    }
    else if(getDecider() == 2)
    {
        query = QString("MATCH(n:User) WHERE n.email = \'%1\' RETURN id(n),n;")
                        .arg(getUserEmail());
    }
    else if(getDecider() == 3)
    {
        query = QString("MATCH(n:User) WHERE n.identkey = \'%1\' RETURN id(n),n;")
            .arg(getUserIdentKey());
    }
    return query;
}

void CwnCommandFindUser::interpretAnswer(QVariant &Ret)
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
            INFO("No Users found by login and password or by ID.");
        }
    }
}

int CwnCommandFindUser::Execute()
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

bool CwnCommandFindUser::CheckValid()
{
    bool bRet = true;

    if (getDecider()<0
            || (getDecider() == 0 && (getLogin().isEmpty() || getPassw().isEmpty()))
            || (getDecider() == 1 && getUserId()<0)
            || getDecider()>1)
    {
        bRet = false;
    }

    return bRet;
}

CumUser* CwnCommandFindUser::getResult()
{
    return result;
}
