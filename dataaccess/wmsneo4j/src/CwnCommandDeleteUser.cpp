#include "CwnCommandDeleteUser.h"

#include "CwnCommandStdHeader.h"


CwnCommandDeleteUser::CwnCommandDeleteUser(CwnDataAccess *m_rpDataAccess)
: CwnCommandBase(m_rpDataAccess),
  m_iUserId(-1)
{
    // Start Transaction
}

CwnCommandDeleteUser::CwnCommandDeleteUser(long p_lUserId, CwnDataAccess* p_pDataAccess)
    :CwnCommandBase(p_pDataAccess),
      m_iUserId(p_lUserId)
{
}

CwnCommandDeleteUser::~CwnCommandDeleteUser()
{

}

void CwnCommandDeleteUser::setLogin(QString login)
{
    this->login = login;
}

QString CwnCommandDeleteUser::getLogin()
{
    return login;
}

QString CwnCommandDeleteUser::createQuery()
{
    QString query;

    if(m_iUserId>=0)
    {
        query = QString("MATCH(n:User) WHERE id(n)=%1 OPTIONAL MATCH (n)<-[:SessionConnectionToUser]-(m:Session) OPTIONAL MATCH (n)<-[:userValue]-(v) DETACH DELETE m,n,v RETURN DISTINCT 1;")
        //QString query = QString("MATCH(n:User {login:\'%1\'}) SET n.active='0' RETURN id(n);")
            .arg(m_iUserId);
    }
    else
    {
        query = QString("MATCH(n:User {login:\'%1\'}) OPTIONAL MATCH (n)<-[:SessionConnectionToUser]-(m:Session) OPTIONAL MATCH (n)<-[:userValue]-(v) DETACH DELETE m,n,v RETURN DISTINCT 1;")
        //QString query = QString("MATCH(n:User {login:\'%1\'}) SET n.active='0' RETURN id(n);")
            .arg(getLogin());
    }


    return query;
}

void CwnCommandDeleteUser::interpretAnswer(QVariant &Ret)
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
        Ret = -1014;
        ERR("No Users found by given name.");
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
            Ret = -1014;
            ERR("No Users found by given name.");
        }
    }
}

int CwnCommandDeleteUser::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug()<<payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandDeleteUser::CheckValid()
{
    bool bRet = true;

    if (getLogin().isEmpty())
    {
        bRet = false;
    }

    return bRet;
}

