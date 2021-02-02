#include "CwnCommandCheckAuthorisationAdmin.h"

#include <QCryptographicHash>
#include "CumUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandCheckAuthorisationAdmin::CwnCommandCheckAuthorisationAdmin(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{
    this->admin = true;
}

CwnCommandCheckAuthorisationAdmin::~CwnCommandCheckAuthorisationAdmin()
{

}

void CwnCommandCheckAuthorisationAdmin::setLogin(QString login)
{
    this->login = login;
}

QString CwnCommandCheckAuthorisationAdmin::getLogin()
{
    return login;
}

void CwnCommandCheckAuthorisationAdmin::setPassw(QString passw)
{
    QString qstrRet = passw;
    QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    this->passw = qstrValue;
}

QString CwnCommandCheckAuthorisationAdmin::getPassw()
{
    return passw;
}

bool CwnCommandCheckAuthorisationAdmin::getAdmin()
{
    return admin;
}

QString CwnCommandCheckAuthorisationAdmin::createQuery()
{
    QString query = QString("MATCH(n:User) WHERE (n.login = \'%1\' AND n.pass = \'%2\' AND n.admin = \'%3\' AND n.active=1) RETURN id(n),n;")
                        .arg(getLogin())
                        .arg(getPassw())
                        .arg(getAdmin());

    return query;
}

void CwnCommandCheckAuthorisationAdmin::interpretAnswer(QVariant &Ret)
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
        ERR("No Users found by login and password and admin flag.");
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            Ret = 1;
        }
        else
        {
            Ret = EC(eDmFalse);
        }
    }
}

int CwnCommandCheckAuthorisationAdmin::Execute()
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

bool CwnCommandCheckAuthorisationAdmin::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty() || getPassw().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}
