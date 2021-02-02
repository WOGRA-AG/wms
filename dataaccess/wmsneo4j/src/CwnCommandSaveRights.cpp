#include "CwnCommandSaveRights.h"

#include "CwnCommandStdHeader.h"

#include "CdmDataProvider.h"
#include "CumAccessor.h"

CwnCommandSaveRights::CwnCommandSaveRights(CdmRights& p_rCcdmRights, long p_lObjectId, QString p_qstrTableName)
: CwnCommandBase(nullptr),
m_lObjectId(p_lObjectId),
m_prCcdmRights(p_rCcdmRights),
m_pqstrTableName(p_qstrTableName)
{

}

CwnCommandSaveRights::~CwnCommandSaveRights()
{

}

void CwnCommandSaveRights::interpretAnswer(QVariant &Ret)
{
    //CwmsJson json;
    //QString qstrJson(answer);

    //this->qResult = json.parse(qstrJson).toMap();

    //qDebug() << qstrJson;

    //if(CwnCommandBase::checkForErrors(this->qResult.size(),queryCausedError))
    //{
    //    Ret=EC(eDmInvalidSelectStatement);
    //}
    //else
    //{
        Ret = 1;
    //}
}

int CwnCommandSaveRights::Execute()
{
    int iRet = CdmLogging::eDmUnknownUserQueryError;

    QString payload = startJsonWCommand(QString("MATCH (var)-[r:rights]->(u) WHERE id(var)=%1 DELETE r RETURN DISTINCT 1")
               .arg(m_lObjectId));

    QVariantMap qvHash = m_prCcdmRights.GetVariant().toMap();
    QVariantMap::Iterator qvIt = qvHash.begin();
    QVariantMap::Iterator qvItEnd = qvHash.end();

    if (qvHash.count() == 0)
    {
        iRet = EC(eDmOk);
    }

    for (; qvIt != qvItEnd; ++qvIt)
    {
       int iUserBaseId = 0;
       QString qstrInsert;
       QString qstrUri = qvIt.key();
       CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pManager))
       {
           CdmLocatedElement* pElement = pManager->GetUriObject(qstrUri);

           if (pElement)
           {
               if (pElement->IsUser() || pElement->IsUserGroup())
               {
                   iUserBaseId = static_cast<CumAccessor*> (pElement)->GetId();
               }
               else
               {
                   ERR("Wrong URI Type");
               }
           }
           else
           {
               ERR("Unknown Element:" + qstrUri);
               continue;
           }
       }


       qstrInsert = QString("MATCH (var:%3),(var2) WHERE id(var)=%1 AND id(var2)=%2 CREATE (var)-[r:rights]->(var2)"
                             " SET r.rightId=%4, r.type=\'%3\'"
                             " RETURN id(r);")
          .arg(m_lObjectId)
          .arg(iUserBaseId)
          .arg(m_pqstrTableName)
          .arg(qvIt.value().toInt());

       payload += addJsonCommand(qstrInsert);

    }
    payload += endJsonCommand();
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandSaveRights::CheckValid()
{
    bool bRet = true;

    if (false)
    {
        bRet = false;
    }

    return bRet;
}
