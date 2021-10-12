#include "CwnCommandUpdateUser.h"
#include <QCryptographicHash>

#include "CwnCommandStdHeader.h"

CwnCommandUpdateUser::CwnCommandUpdateUser(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->userid = -1;
    this->active = false;
    this->admin = false;
}

CwnCommandUpdateUser::~CwnCommandUpdateUser()
{

}

void CwnCommandUpdateUser::setUserId(qint64 userid)
{
    this->userid = userid;
}


void CwnCommandUpdateUser::setFirstname(QString name)
{
    this->firstname = name;
}

void CwnCommandUpdateUser::setLastname(QString Surname)
{
    this->lastname = Surname;
}

void CwnCommandUpdateUser::setLogin(QString login)
{
    this->login = login;
}

void CwnCommandUpdateUser::setPassw(QString passw, bool p_bEncrypted)
{
    QString qstrRet = passw;

    if(p_bEncrypted)
    {
        this->passw = passw;
    }
    else{

        QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
        QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
        this->passw = qstrValue;
    }
}

void CwnCommandUpdateUser::setEmail(QString email)
{
    this->email = email;
}

void CwnCommandUpdateUser::setAdmin(bool admin)
{
    this->admin = admin;
}

void CwnCommandUpdateUser::setActive(bool active)
{
    this->active = active;
}

bool CwnCommandUpdateUser::getActive()
{
    return active;
}

bool CwnCommandUpdateUser::getAdmin()
{
    return admin;
}

QString CwnCommandUpdateUser::getEmail()
{
    return email;
}

QString CwnCommandUpdateUser::getPassw()
{
    return passw;
}

QString CwnCommandUpdateUser::getFirstname()
{
    return firstname;
}

QString CwnCommandUpdateUser::getLastname()
{
    return lastname;
}

qint64 CwnCommandUpdateUser::getUserId()
{
    return userid;
}

QString CwnCommandUpdateUser::getLogin()
{
    return login;
}

QString CwnCommandUpdateUser::createQuery()
{
    QString query = QString("MATCH (user:User) WHERE id(user) = %1 OPTIONAL MATCH (userLoginExist:User) WHERE userLoginExist.login = \'%2\' AND NOT(id(userLoginExist) = %3) OPTIONAL MATCH (userEmailExist:User) WHERE userEmailExist.email = \'%4\' AND NOT(id(userEmailExist) = %5) WITH user, userLoginExist, userEmailExist WHERE userLoginExist IS nullptr AND userEmailExist IS nullptr SET user.login = \'%6\', user.email = \'%7\', user.firstname= \'%8\', user.lastname = \'%9\', user.active = \'%10\', user.admin = \'%11\', user.pass = \'%12\' RETURN user, userLoginExist, userEmailExist;")
                 .arg(getUserId())
                 .arg(getLogin())
                 .arg(getUserId())
                 .arg(getEmail())
                 .arg(getUserId())
                 .arg(getLogin())
                 .arg(getEmail())
                 .arg(getFirstname())
                 .arg(getLastname())
                 .arg(getActive())
                 .arg(getAdmin())
                 .arg(getPassw());
    return query;
}

void CwnCommandUpdateUser::interpretAnswer(QVariant &Ret)
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
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {
            //qDebug() << rowMap;
            Ret = 1;
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("Could not update User. The login name or email already exist.");
        }
    }
}

int CwnCommandUpdateUser::Execute()
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

bool CwnCommandUpdateUser::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty() ||
        getPassw().isEmpty() ||
        getFirstname().isEmpty() ||
        getLastname().isEmpty() ||
        getEmail().isEmpty() ||
        getUserId()<0)
    {
        bRet = false;
    }

    return bRet;
}
