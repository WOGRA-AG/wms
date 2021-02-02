#include "CwnCommandCheckAuthorisation.h"

#include <QCryptographicHash>
#include "CumUser.h"

#include "CwnCommandStdHeader.h"

CwnCommandCheckAuthorisation::CwnCommandCheckAuthorisation(CwnDataAccess* m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{

}

CwnCommandCheckAuthorisation::~CwnCommandCheckAuthorisation()
{

}

void CwnCommandCheckAuthorisation::setLogin(QString login)
{
    this->login = login;
}

QString CwnCommandCheckAuthorisation::getLogin()
{
    return login;
}

void CwnCommandCheckAuthorisation::setPassw(QString passw)
{
    QString qstrRet = passw;
    QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    this->passw = qstrValue;
}

QString CwnCommandCheckAuthorisation::getPassw()
{
    return passw;
}


QString CwnCommandCheckAuthorisation::createQuery()
{
    QString query = QString("MATCH(n:User) WHERE (n.login = \'%1\' AND n.pass = \'%2\' AND n.active=1) RETURN id(n),n;")
                        .arg(getLogin())
                        .arg(getPassw());

    return query;
}

void CwnCommandCheckAuthorisation::interpretAnswer(QVariant &Ret)
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
        ERR("No Users found by login and password.");
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

int CwnCommandCheckAuthorisation::Execute()
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

bool CwnCommandCheckAuthorisation::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty() || getPassw().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}
