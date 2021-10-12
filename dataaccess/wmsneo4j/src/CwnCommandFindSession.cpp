#include "CwnCommandFindSession.h"

#include <QCryptographicHash>

#include "CdmSessionManager.h"
#include "CdmSession.h"

#include "CwnCommandStdHeader.h"

CwnCommandFindSession::CwnCommandFindSession(qint64 p_lSessionId,qint64 p_lUserId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(p_lUserId)
{

}

CwnCommandFindSession::CwnCommandFindSession(qint64 p_lSessionId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSessionId(p_lSessionId),
  m_lUserId(0),
  m_pSession(nullptr)
{

}

CwnCommandFindSession::CwnCommandFindSession(QString p_qstrBaseAuth, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lSessionId(0),
  m_lUserId(0),
  m_qstrBaseAuth(p_qstrBaseAuth),
  m_pSession(nullptr)
{

}

CwnCommandFindSession::~CwnCommandFindSession()
{

}

QString CwnCommandFindSession::createQueryIdAndUser()
{
    return QString("MATCH (s:Session)-[:SessionConnectionToUser]->(u:User) WHERE id(s)=%1 AND id(u)=%2 RETURN s.State,id(s),id(u);")
            .arg(m_lSessionId)
            .arg(m_lUserId);
}

QString CwnCommandFindSession::createQueryById()
{
    return QString("MATCH (s:Session)-[:SessionConnectionToUser]->(u:User) WHERE id(s)=%1 RETURN s.State,id(s),id(u);")
            .arg(m_lSessionId);
}

QString CwnCommandFindSession::createQueryBaseAuth()
{
    return QString("MATCH (s:Session)-[:SessionConnectionToUser]->(u:User) WHERE s.BaseAuth=\'%1\' RETURN s.State,id(s),id(u);")
            .arg(m_qstrBaseAuth);
}

CdmSession *CwnCommandFindSession::GetResult()
{
    return m_pSession;
}


void CwnCommandFindSession::interpretAnswer(QVariant &Ret)
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
        Ret=0;
    }
    else
    {
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            int iRet = list->at(0).toBool();
            if (SUCCESSFULL(iRet))
            {
                int iSessionId = list->at(1).toInt();
                int iUserId = list->at(2).toInt();;

                m_pSession = CdmDataAccessHelper::CreateNewSession(iSessionId, iUserId, GetDataAccess());
            }
            Ret = iRet;
        }
        else
        {
            Ret = -1;
            ERR("No Session found by id or User and id or BaseAuth.");
        }
    }
}

int CwnCommandFindSession::Execute()
{

    int iRet = CdmLogging::eDmUnknownLoginManagerError;
    QString payload;

     if (m_lSessionId > 0 && m_lUserId > 0)
     {
         m_pSession = CdmSessionManager::GetSessionManager()->FindSessionByIdLocal(static_cast<int>(m_lSessionId));

         if (!m_pSession)
         {
            payload = createJson(createQueryIdAndUser());
         }
         else
         {
             iRet = CdmLogging::eDmOk;
             return iRet;
         }
     }
     else if (m_lSessionId > 0)
     {
         m_pSession = CdmSessionManager::GetSessionManager()->FindSessionByIdLocal(static_cast<int>(m_lSessionId));

         if (!m_pSession)
         {
            payload = createJson(createQueryById());
         }
         else
         {
             iRet = CdmLogging::eDmOk;
             return iRet;
         }
     }
     else if (!m_qstrBaseAuth.isEmpty())
     {
        payload = createJson(createQueryBaseAuth());
     }

     queryCausedError = payload;
     ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
     QVariant Ret;
     interpretAnswer(Ret);
     iRet = Ret.toInt();
     return iRet;
}

bool CwnCommandFindSession::CheckValid()
{
    return (m_lSessionId >= 0);
}
