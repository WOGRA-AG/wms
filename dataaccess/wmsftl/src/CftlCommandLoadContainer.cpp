
// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CftlCommandLoadObjects.h"
#include "CftlCommandLoadContainer.h"

CftlCommandLoadContainer::CftlCommandLoadContainer(long p_lContainerId, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(0),
      m_rpContainer(nullptr)
{
}

CftlCommandLoadContainer::CftlCommandLoadContainer(long p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_lContainerId(0),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(p_lSchemeId),
      m_qstrKeyname(p_qstrKeyname),
      m_rpContainer(nullptr)
{
}

CftlCommandLoadContainer::~CftlCommandLoadContainer()
{

}

bool CftlCommandLoadContainer::CheckValid()
{
    return (m_lContainerId > 0 || (m_lSchemeId > 0 && !m_qstrKeyname.isEmpty()));
}

CdmObjectContainer* CftlCommandLoadContainer::GetResult()
{
    return m_rpContainer;
}

void CftlCommandLoadContainer::GenerateContainerQuery(QSqlQuery& p_rQuery)
{
    if (m_lContainerId > 0)
    {
        p_rQuery.prepare("Select cl.ClassId, ol.ContainerId, ol.Keyname, ol.LastChange, "
                         "ol.CreatorId, ol.ModifierId, ol.Caption, ol.Comment, cl.SchemeId, ol.Tree "
                         "from WMS_DM_CONTAINER ol, WMS_CLASS cl where ol.ContainerId = ? "
                         "and ol.ClassId = cl.ClassId");
        p_rQuery.addBindValue((int)m_lContainerId);
    }
    else
    {
        p_rQuery.prepare("Select cl.ClassId, ol.ContainerId, ol.Keyname, ol.LastChange, "
                         "ol.CreatorId, ol.ModifierId, ol.Caption, ol.Comment, cl.SchemeId, "
                         "ol.Tree from WMS_DM_CONTAINER ol, WMS_CLASS cl where ol.Keyname = ? "
                         "and ol.ClassId = cl.ClassId and cl.SchemeId = ?");
        p_rQuery.addBindValue(m_qstrKeyname);
        p_rQuery.addBindValue((int)m_lSchemeId);

    }
}

int CftlCommandLoadContainer::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    QDateTime qdtLastChange;
    QLinkedList<long> qvlObjects;
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    QString qstrQuery;

    if(m_rpContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(m_rpContainer);
    }

    // Creating the Objectlist
    GenerateContainerQuery(cQSqlQuery);


    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            long lClassId           = cQSqlQuery.value(0).toInt();
            m_lContainerId          = cQSqlQuery.value(1).toInt();
            QString qstrKeyname     = cQSqlQuery.value(2).toString();
            qdtLastChange           = cQSqlQuery.value(3).toDateTime();
            long lCreatorId         = cQSqlQuery.value(4).toInt();
            long lLastModifierId    = cQSqlQuery.value(5).toInt();
            QString qstrCaption     = cQSqlQuery.value(6).toString();
            QString qstrComment     = cQSqlQuery.value(7).toString();
            long lDatabaseId        = cQSqlQuery.value(8).toInt();
            bool bTree              = cQSqlQuery.value(9).toBool();

            m_rpContainer = CdmDataAccessHelper::CreateObjectContainer(lDatabaseId, m_lContainerId, qstrKeyname, lClassId);
            m_rpContainer->SetTree(bTree);
            m_rpContainer->SetCaption(qstrCaption);
            m_rpContainer->SetComment(qstrComment);
            CdmDataAccessHelper::SetCreatorId(m_rpContainer, lCreatorId);
            CdmDataAccessHelper::SetModifierId(m_rpContainer, lLastModifierId);

            INFO("Container Basedata successfull loaded!!!");
            lRet = LoadContainerRights();
        }
        else
        {
            lRet = EC(eDmObjectListNotFound);
            if (m_lContainerId > 0)
            {
                INFO("Container with the Id " + QString::number(m_lContainerId) + " not found");
            }
            else
            {
                INFO("Container with the Keyname \"" + m_qstrKeyname + "\" not found");
            }
        }
    }
    else
    {
        lRet = EC(eDmInvalidSelectStatement);
    }

    if(m_rpContainer)
    {
        LoadObjects();
        m_rpContainer->ResetNewModified();
        m_rpContainer->SetLastChange(qdtLastChange);
    }
    return lRet;
}

void CftlCommandLoadContainer::LoadObjects()
{
    if (m_bLoadObjects)
    {
        CftlCommandLoadObjects command(m_rpContainer, GetDataAccess());
        command.Run();
    }
}

long CftlCommandLoadContainer::LoadContainerRights()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(m_rpContainer))
    {
        QSqlQuery cQSqlQuery(GetSqlDatabase());
        QString qstrQuery;

        cQSqlQuery.prepare("select AccessorId, AccessRight from WMS_DM_ACCESSORRIGHT where ContainerId = ?");
        cQSqlQuery.addBindValue((int)m_rpContainer->GetId());

        lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

        if (lRet > 0)
        {
            cQSqlQuery.first();

            if(cQSqlQuery.isValid())
            {
                do
                {
                    long lAccessorId = cQSqlQuery.value(0).toInt();
                    int iRight       = cQSqlQuery.value(1).toInt();

                    m_rpContainer->AddAccessorRight(lAccessorId, (EdmRight)iRight);
                }
                while(cQSqlQuery.next());
            }

            lRet = EC(eDmOk);
        }
    }

    return lRet;
}

