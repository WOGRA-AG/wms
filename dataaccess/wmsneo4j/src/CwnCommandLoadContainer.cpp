// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CwnCommandLoadObjects.h"
#include "CwnCommandLoadContainer.h"
#include "CwnHelper.h"
#include "CdmScheme.h"

#include "CwnCommandStdHeader.h"


CwnCommandLoadContainer::CwnCommandLoadContainer(qint64 p_lContainerId, bool p_bLoadObjects, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(0),
      m_rpContainer(nullptr)
{
}

CwnCommandLoadContainer::CwnCommandLoadContainer(qint64 p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(0),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(p_lSchemeId),
      m_qstrKeyname(p_qstrKeyname),
      m_rpContainer(nullptr)
{
}

CwnCommandLoadContainer::~CwnCommandLoadContainer()
{

}

bool CwnCommandLoadContainer::CheckValid()
{
    return (m_lContainerId > 0 || (m_lSchemeId > 0 && !m_qstrKeyname.isEmpty()));
}

CdmObjectContainer* CwnCommandLoadContainer::GetResult()
{
    return m_rpContainer;
}

bool CwnCommandLoadContainer::interpretAnswerForRights(const QVariantList *dataList)
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

            int iRight = (row->at(1).isValid())?row->at(1).toInt():0;
           qint64 lAccessorId = (row->at(2).isValid())?row->at(2).toInt():0;
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

bool CwnCommandLoadContainer::interpretAnswerForObjects(const QVariantList *dataList)
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

            if(row->at(1).isValid())
                qvlObjects.append(row->at(1).toLongLong());
        }
    }
    else
    {
        INFO("No objects found for this container!!!");
    }

    CwnCommandLoadObjects command(m_rpContainer, qvlObjects, GetDataAccess());
    command.Run();

    return true;
}
bool CwnCommandLoadContainer::interpretAnswerForContainerLoad(const QVariantList* dataList)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    QDateTime qdtLastChange;

    if(dataList == nullptr)
        return true;

    if(dataList->count()>0)
    {
        const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
        const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

       qint64 lClassId           = list->at(0).toInt();
        m_lContainerId          = list->at(1).toInt();
        QString qstrKeyname     = list->at(2).toString();
        qdtLastChange           = list->at(3).toDateTime();
       qint64 lLastModifierId    = (list->at(4).isNull())?0:list->at(4).toInt();
        QString qstrCaption     = list->at(5).toString();
        QString qstrComment     = list->at(6).toString();
       qint64 lDatabaseId        = list->at(7).toInt();
        bool bTree              = list->at(8).toBool();
        QString qstrTempConfig  = list->at(9).toString();
        QString qstrConfig      = CwnHelper::base64_decode(qstrTempConfig);

        m_rpContainer = CdmDataAccessHelper::CreateObjectContainer(lDatabaseId, m_lContainerId, qstrKeyname, lClassId);
        m_rpContainer->SetTree(bTree);
        m_rpContainer->SetCaption(qstrCaption);
        m_rpContainer->SetComment(qstrComment);
        m_rpContainer->SetConfig(qstrConfig);
        CdmDataAccessHelper::SetModifierId(m_rpContainer, lLastModifierId);

        INFO("Container Basedata successfull loaded!!!");
        lRet= true;
    }
    else
    {
        lRet = false;
        if (m_lContainerId > 0)
        {
            INFO("Container with the Id " + QString::number(m_lContainerId) + " not found");
        }
        else
        {
            INFO("Container with the Keyname \"" + m_qstrKeyname + "\" not found");
        }
    }

    return lRet;
}

QString CwnCommandLoadContainer::GetRightsQuery()
{
    QString qstrQuery;

    if (m_lContainerId > 0)
    {
        qstrQuery = QString("MATCH (con:WMS_DM_OBJECTLIST) WHERE id(con)=%1 "
                            "OPTIONAL MATCH (con)-[r:rights]->(u) "
                            "RETURN id(con), r.rightId, id(u)")
                    .arg(m_lContainerId);
    }
    else
    {
        qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]->(con:WMS_DM_OBJECTLIST) WHERE id(s)=%1 AND con.Keyname='%2' "
                            "OPTIONAL MATCH (con)-[r:rights]->(u) "
                            "RETURN id(con), r.rightId, id(u)")
                    .arg(m_lSchemeId)
                    .arg(CwnHelper::MaskStringForChanges(m_qstrKeyname));
    }
    return qstrQuery;
}

QString CwnCommandLoadContainer::GetObjectQuery()
{
    QString qstrQuery;
    if (m_bLoadObjects)
    {
        if (m_lContainerId > 0)
        {
            qstrQuery = QString("MATCH (con:WMS_DM_OBJECTLIST) WHERE id(con)=%1 "
                                "OPTIONAL MATCH (con)-[:hasObjects]->(o:WMS_DM_OBJECT) "
                                "RETURN id(con),id(o)").arg(m_lContainerId);
        }
        else
        {
            qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]->(con:WMS_DM_OBJECTLIST) WHERE id(s)=%1 AND con.Keyname='%2' "
                                "OPTIONAL MATCH (con)-[:hasObjects]->(o:WMS_DM_OBJECT) "
                                "RETURN id(con),id(o)")
                    .arg(m_lSchemeId)
                    .arg(CwnHelper::MaskStringForChanges(m_qstrKeyname));
        }

        return qstrQuery;
    }
    else
    {
        return QString("RETURN 1");
    }

}

QString CwnCommandLoadContainer::GetContainerQuery()
{
    QString qstrQuery;

    if (m_lContainerId > 0)
    {
        qstrQuery = QString("MATCH (c:Class)-[:hasObjectContainer]->(ol:WMS_DM_OBJECTLIST) WHERE id(ol)=%1 WITH c,ol MATCH (s:Scheme)-[:hasClass]->(c) OPTIONAL MATCH (cmod:User)<-[:WMS_CONTAINER_MODIFIED_BY]-(ol) RETURN id(c),id(ol),ol.Keyname,ol.LastChange,id(cmod),ol.Caption,ol.Comment,id(s),ol.Tree,ol.Config")
                            .arg(m_lContainerId);
    }
    else
    {
        qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]->(ol:WMS_DM_OBJECTLIST) WHERE ol.Keyname='%1' AND id(s)=%2 WITH c,ol,s OPTIONAL MATCH (cmod:User)<-[:WMS_CONTAINER_MODIFIED_BY]-(ol) RETURN id(c),id(ol),ol.Keyname,ol.LastChange,id(cmod),ol.Caption,ol.Comment,id(s),ol.Tree,ol.Config")
                        .arg(CwnHelper::MaskStringForChanges(m_qstrKeyname))
                        .arg(m_lSchemeId);
    }

    return qstrQuery;
}


void CwnCommandLoadContainer::interpretAnswer(QVariant &Ret)
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

        const QVariantList* dataListObjects = nullptr;
        if (m_bLoadObjects)
        {
            const QVariantList* resultsObjects = static_cast<const QVariantList*>(this->qResult->find("results")->data());
            const QVariantMap* dataObjects = static_cast<const QVariantMap*>(resultsObjects->at(2).data());
            dataListObjects = static_cast<const QVariantList*>(dataObjects->find("data")->data());
        }

        bRet = bRet && interpretAnswerForContainerLoad(dataListCon);
        bRet = bRet && interpretAnswerForRights(dataListRights);

        if (m_bLoadObjects)
            bRet = bRet && interpretAnswerForObjects(dataListObjects);
        else
            bRet= true && bRet;

        if(!bRet)
        {
            Ret = EC(eDmFalse);
            INFO("No Container found by ContainerKeyname.");
        }
        else
        {
            Ret = EC(eDmTrue);
        }
    }
}

int CwnCommandLoadContainer::Execute()
{
    QDateTime qdtLastChange;

    if(m_rpContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(m_rpContainer);
    }

    int iRet = CdmLogging::eDmUnknownClassAccessError;

    // Creating the Objectlist
    payload += startJsonWCommand(GetContainerQuery());
    payload += addJsonCommand(GetRightsQuery());
    payload += addJsonCommand(GetObjectQuery());
    payload += endJsonCommand();

    //ERR(payload);
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();

    if(m_rpContainer)
    {
        m_rpContainer->ResetNewModified();
        m_rpContainer->SetLastChange(qdtLastChange);
    }

    return iRet;
}

