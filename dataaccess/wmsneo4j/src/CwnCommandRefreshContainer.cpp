#include "CwnCommandRefreshContainer.h"

#include "CwnHelper.h"
#include "CwnDataAccess.h"

#include "CwnCommandStdHeader.h"

CwnCommandRefreshContainer::CwnCommandRefreshContainer(CdmObjectContainer* p_pContainer,CwnDataAccess* p_pDataAccess):CwnCommandBase(p_pDataAccess)
,m_rpContainer(p_pContainer)
{
}

CwnCommandRefreshContainer::~CwnCommandRefreshContainer()
{
}

bool CwnCommandRefreshContainer::CheckValid()
{
    return CHKPTR(m_rpContainer);
}

QString CwnCommandRefreshContainer::GetRightsQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (con:WMS_DM_OBJECTLIST) WHERE id(con)=%1 "
                            "OPTIONAL MATCH (con)-[r:rights]->(u) "
                            "RETURN id(con), r.rightId, id(u)")
                    .arg(m_rpContainer->GetId());
    return qstrQuery;
}

QString CwnCommandRefreshContainer::GetObjectQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (o:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) WHERE id(ol)=%1 RETURN id(o)").arg(m_rpContainer->GetId());


    return qstrQuery;
}

QString CwnCommandRefreshContainer::GetContainerQuery()
{
    QString qstrQuery;
    qstrQuery = QString("MATCH (ol:WMS_DM_OBJECTLIST) WHERE id(ol)=%1 WITH ol OPTIONAL MATCH (cru:User)-[:ContainerCreator]->(ol) OPTIONAL MATCH (cmod:User)-[:ContainerModifier]->(ol) RETURN ol.LastChange,id(cmod),ol.Caption,ol.Comment,ol.Config")
                            .arg(m_rpContainer->GetId());

    return qstrQuery;
}

bool CwnCommandRefreshContainer::interpretAnswerForRights(const QVariantList *dataList)
{
    if(dataList == nullptr)
        return true;

    if(dataList->count()>0)
    {
        QList<QVariant>::ConstIterator it;
        for(it=dataList->begin();it!=dataList->end();it++) // loading each class
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
            const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

           qint64 lAccessorId = (row->at(2).isValid())?row->at(2).toInt():0;
            int iRight = (row->at(1).isValid())?row->at(1).toInt():0;
            if(lAccessorId!=0)
                m_rpContainer->AddAccessorRight(lAccessorId, static_cast<EdmRight>(iRight));
        }
    }
    else
    {
        INFO("No rights found for this container!!!");
    }

    return true;

}

bool CwnCommandRefreshContainer::interpretAnswerForObjects(const QVariantList* dataList)
{
    if(dataList == nullptr)
        return true;

    if(dataList->count()>0)
    {
        QList<QVariant>::ConstIterator it;
        for(it=dataList->begin();it!=dataList->end();it++) // loading each class
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
            const QVariantList* row = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            if(!(row->at(1).isNull()))
                qvlObjects.append(row->at(1).toLongLong());
        }
    }
    else
    {
        INFO("No objects found for this container!!!");
    }

    return true;
}

bool CwnCommandRefreshContainer::interpretAnswerForRefreshContainer(const QVariantList *dataList, QVariant &Ret)
{
    QDateTime qdtLastChange;

    if(dataList->count()>0)
    {
        const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
        const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

        qdtLastChange           = list->at(0).toDateTime();
       qint64 lLastModifierId    = (list->at(1).isNull())?0:list->at(1).toInt();
        QString qstrCaption     = list->at(2).toString();
        QString qstrComment     = list->at(3).toString();
        QString qstrConfig      = CwnHelper::base64_decode(list->at(4).toString());

        if (qdtLastChange.secsTo(QDateTime::currentDateTime()) < m_rpContainer->GetLastChange().secsTo(QDateTime::currentDateTime()))
        {
           Ret = EC(eDmTrue);
           m_rpContainer->SetModifierId(lLastModifierId);
           m_rpContainer->SetCaption(qstrCaption);
           m_rpContainer->SetComment(qstrComment);
           m_rpContainer->SetConfig(qstrConfig);
        }
        else
        {
           Ret = EC(eDmFalse);
           return false;
        }
     }
    else
    {
       Ret = EC(eDmObjectListNotFound);
       return false;
    }

    return true;
}

void CwnCommandRefreshContainer::interpretAnswer(QVariant &Ret)
{
    //qDebug() << answer;
    bool bRet = true;

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

        const QVariantList* results = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        const QVariantMap* data = static_cast<const QVariantMap*>(results->at(0).data());
        const QVariantList* dataListCon = static_cast<const QVariantList*>(data->find("data")->data());

        const QVariantList* resultsRights = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        const QVariantMap* dataRights = static_cast<const QVariantMap*>(resultsRights->at(1).data());
        const QVariantList* dataListRights = static_cast<const QVariantList*>(dataRights->find("data")->data());

        const QVariantList* resultsObjects = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        const QVariantMap* dataObjects = static_cast<const QVariantMap*>(resultsObjects->at(2).data());
        const QVariantList* dataListObjects = static_cast<const QVariantList*>(dataObjects->find("data")->data());


        bRet = bRet && interpretAnswerForObjects(dataListObjects);
        bRet = bRet && interpretAnswerForRefreshContainer(dataListCon, Ret);
        bRet = bRet && interpretAnswerForRights(dataListRights);

        if(!bRet)
        {
            Ret=0;
        }

        if(bRet)
        {
            Ret=1;
            //Loaded Container with Objects
        }
    }
}

int CwnCommandRefreshContainer::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;

    // Creating the Objectlist

    payload += startJsonWCommand(GetContainerQuery());
    payload += addJsonCommand(GetRightsQuery());
    payload += addJsonCommand(GetObjectQuery());
    payload += endJsonCommand();
    queryCausedError = payload;

    ConnectAndExecute(commitTransaction,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();

    m_rpContainer->ClearContainerLocal();
    //CwnCommandLoadObjects command(m_rpContainer, qvlObjects, GetDataAccess());
    //lRet = command.Run();
    m_rpContainer->ResetNewModified();
    m_rpContainer->SetLastChange(qdtLastChange);
    return iRet;
}
