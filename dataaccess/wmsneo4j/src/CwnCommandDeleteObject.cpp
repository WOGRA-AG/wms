// System and Qt Includes
#include <QDate>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes
#include "CwnJournal.h"
#include "CwnCommandCheckObjectLocked.h"
#include "CwnCommandDeleteObject.h"
#include "CwnCommandStdHeader.h"

CwnCommandDeleteObject::CwnCommandDeleteObject(long p_lObjectId, long p_lSessionId, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_lObjectId(p_lObjectId),
  m_lSessionId(p_lSessionId)
{
}

CwnCommandDeleteObject::~CwnCommandDeleteObject()
{

}

QString CwnCommandDeleteObject::createQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (o:WMS_DM_OBJECT) WHERE id(o)=%1 "
                        "OPTIONAL MATCH (o)-[:Object_value]->(v) "
                        "DETACH DELETE v,o RETURN DISTINCT 1;").arg(m_lObjectId);

    return qstrQuery;
}

bool CwnCommandDeleteObject::CheckValid()
{
    return (m_lObjectId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

void CwnCommandDeleteObject::interpretAnswer(QVariant &Ret)
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
           CwnJournal* pJournal = GetDataAccess()->GetJournal();
           if(pJournal)
           {
              long lRet = pJournal->ObjectDeleted(static_cast<int>(m_lObjectId));

              if(lRet>0)
                  Ret=1;
              else{
                  Ret=-1;
                  ERR("Journal could not be updated");
              }
           }
        }
        else
        {
            Ret=-1;
            ERR("Object could not be deleted.");
        }
    }
}

int CwnCommandDeleteObject::Execute()
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
