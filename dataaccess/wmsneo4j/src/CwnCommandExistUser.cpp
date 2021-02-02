#include "CwnCommandExistUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandExistUser::CwnCommandExistUser(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess)
{

}

CwnCommandExistUser::~CwnCommandExistUser()
{

}

void CwnCommandExistUser::setLogin(QString login)
{
    this->login = login;
}

QString CwnCommandExistUser::getLogin()
{
    return login;
}

QString CwnCommandExistUser::createQuery()
{
    QString query = QString("MATCH(n:User {login:\'%1\'}) RETURN n;")
                 .arg(getLogin());
    return query;
}

void CwnCommandExistUser::interpretAnswer(QVariant &Ret)
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
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = EC(eDmFalse);
            INFO("No Users found by login.");
        }
    }
}

int CwnCommandExistUser::Execute()
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

bool CwnCommandExistUser::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}

