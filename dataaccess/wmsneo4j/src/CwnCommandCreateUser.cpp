#include "CwnCommandCreateUser.h"
#include <QCryptographicHash>
#include <QUuid>

#include "CwnCommandStdHeader.h"

CwnCommandCreateUser::CwnCommandCreateUser(CwnDataAccess *m_rpDataAccess, QString p_qstrIdentKey)
: CwnCommandBase(m_rpDataAccess),
  m_qstrIdentKey(p_qstrIdentKey)
{
    // Start Transaction
}

CwnCommandCreateUser::~CwnCommandCreateUser()
{

}

void CwnCommandCreateUser::setActive(bool active)
{
    this->active = active;
}

void CwnCommandCreateUser::setAdmin(bool admin)
{
    this->admin = admin;
}

void CwnCommandCreateUser::setEmail(QString email)
{
    this->email = email;
}

void CwnCommandCreateUser::setFirstname(QString firstname)
{
    this->firstname = firstname;
}

void CwnCommandCreateUser::setLastname(QString lastname)
{
    this->lastname = lastname;
}

void CwnCommandCreateUser::setLogin(QString login)
{
    this->login = login;
}

void CwnCommandCreateUser::setPass(QString pass)
{
    QString qstrRet = pass;
    QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    this->pass = qstrValue;
}

bool CwnCommandCreateUser::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty() ||
        getPass().isEmpty() ||
        getFirstname().isEmpty() ||
        getLastname().isEmpty() ||
        getEmail().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}

bool CwnCommandCreateUser::getActive()
{
    return active;
}

bool CwnCommandCreateUser::getAdmin()
{
    return admin;
}

QString CwnCommandCreateUser::getEmail()
{
    return email;
}

QString CwnCommandCreateUser::getFirstname()
{
    return firstname;
}

QString CwnCommandCreateUser::getLastname()
{
    return lastname;
}

QString CwnCommandCreateUser::getLogin()
{
    return login;
}

QString CwnCommandCreateUser::getPass()
{
    return pass;
}

QString CwnCommandCreateUser::createQuery()
{
    if(m_qstrIdentKey.isEmpty())
    {
        QUuid tmp;
        m_qstrIdentKey = tmp.createUuid().toString();
    }

    QString query = QString("OPTIONAL MATCH (userEmailExist:User {email: \'%1\'}) WITH userEmailExist WHERE userEmailExist IS nullptr OPTIONAL MATCH (userIdentKeyExist:User {identkey: \'%2\'}) WITH userIdentKeyExist WHERE userIdentKeyExist IS nullptr MERGE (user:User {login : \'%3\'}) ON CREATE SET user={active : \'%4\',admin : \'%5\',email : \'%6\',firstname : \'%7\',lastname : \'%8\',login : \'%9\',pass : \'%10\',identkey : \'%11\'}, user.onCreate = true WITH user, EXISTS(user.onCreate) as onCreate REMOVE user.onCreate RETURN id(user),onCreate;")
                .arg(getEmail())
                .arg(m_qstrIdentKey)
                .arg(getLogin())
                .arg(getActive())
                .arg(getAdmin())
                .arg(getEmail())
                .arg(getFirstname())
                .arg(getLastname())
                .arg(getLogin())
                .arg(getPass())
                .arg(m_qstrIdentKey);

   return query;
}

int CwnCommandCreateUser::Execute()
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

void CwnCommandCreateUser::interpretAnswer(QVariant &Ret)
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
            //qDebug() << rowList[1].toBool();
            if(list->at(1).toBool())
            {
                Ret = list->at(0);
                //qDebug() << rowList[0].toInt();
            }
            else
            {
                Ret = EC(eDmFalse);
                INFO("The login name is already in use, but the e-mail and the identityKey are not used.");
            }
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("Either the identityKey or the e-mail already exists in the Database.");
        }
    }
}
