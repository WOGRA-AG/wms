// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// Own Includes
#include "CwnJournal.h"
#include "CwnCommandDeleteContainer.h"

#include "CwnCommandStdHeader.h"

CwnCommandDeleteContainer::CwnCommandDeleteContainer(long p_lContainerId, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(p_lContainerId)
{
}

CwnCommandDeleteContainer::~CwnCommandDeleteContainer()
{
}

QString CwnCommandDeleteContainer::createQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (ol:WMS_DM_OBJECTLIST) WHERE id(ol)=%1 "
                        "WITH ol "
                        "OPTIONAL MATCH (ol)-[:hasObjects]->(o:WMS_DM_OBJECT) "
                        "WITH ol,o "
                        "OPTIONAL MATCH (o)-[:Object_value]->(v:WMS_VALUE) "
                        "WITH ol,o,v "
                        "DETACH DELETE v,o,ol RETURN DISTINCT 1;").arg(m_lContainerId);
    return qstrQuery;
}

bool CwnCommandDeleteContainer::CheckValid()
{
    return (m_lContainerId > 0);
}

void CwnCommandDeleteContainer::interpretAnswer(QVariant &Ret)
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
            CwnJournal* pJournal = GetDataAccess()->GetJournal();

            if(pJournal)
            {
                long lRet = pJournal->ObjectListDeleted(static_cast<int>(m_lContainerId));

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
            Ret = EC(eDmInvalidDeleteStatement);
            ERR("Command didn't found the container.");
        }
    }
}

int CwnCommandDeleteContainer::Execute()
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
