// WMS Includes
#include "CdmObjectContainer.h"
#include "CdmDataAccessHelper.h"

// Own Includes
#include "CdbCommandLoadObjects.h"
#include "CdbCommandLoadContainer.h"

CdbCommandLoadContainer::CdbCommandLoadContainer(long p_lContainerId, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(0),
      m_rpContainer(nullptr)
{
}

CdbCommandLoadContainer::CdbCommandLoadContainer(long p_lSchemeId, QString p_qstrKeyname, bool p_bLoadObjects, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lContainerId(0),
      m_bLoadObjects(p_bLoadObjects),
      m_lSchemeId(p_lSchemeId),
      m_qstrKeyname(p_qstrKeyname),
      m_rpContainer(nullptr)
{
}


CdbCommandLoadContainer::~CdbCommandLoadContainer()
{

}

bool CdbCommandLoadContainer::CheckValid()
{
    return (m_lContainerId > 0 || (m_lSchemeId > 0 && !m_qstrKeyname.isEmpty()));
}

CdmObjectContainer* CdbCommandLoadContainer::GetResult()
{
    return m_rpContainer;
}


QString CdbCommandLoadContainer::GetObjectQuery()
{
    QString qstrQuery;

    if (m_lContainerId > 0)
    {
        qstrQuery = QString("Select ObjectId from WMS_DM_OBJECT where ObjectListId = %1").arg(m_lContainerId);
    }
    else
    {
        qstrQuery = QString("Select ObjectId from WMS_DM_OBJECT obj, WMS_DM_OBJECTLIST ol, "
                            "WMS_CLASS cl where obj.ObjectListId = ol.ObjectListId and "
                            "cl.ClassId = ol.ClassId and cl.DatabaseId = %1 and ol.Keyname = '%2'")
                .arg(m_lSchemeId)
                .arg(CwmsUtilities::MaskStringForChanges(m_qstrKeyname));
    }

    return qstrQuery;
}

QString CdbCommandLoadContainer::GetContainerQuery()
{
    QString qstrQuery;

    if (m_lContainerId > 0)
    {
        qstrQuery = QString("Select cl.ClassId, ol.ObjectListId, ol.Keyname, ol.LastChange, "
                            "ol.CreatorId, ol.ModifierId, ol.Caption, ol.Comment, cl.DatabaseId, ol.Tree, ol.Config "
                            "from WMS_DM_OBJECTLIST ol, WMS_CLASS cl where ol.ObjectListId = %1 "
                            "and ol.ClassId = cl.ClassId")
                            .arg(m_lContainerId);
    }
    else
    {
        qstrQuery = QString("Select cl.ClassId, ol.ObjectListId, ol.Keyname, ol.LastChange, "
                            "ol.CreatorId, ol.ModifierId, ol.Caption, ol.Comment, cl.DatabaseId, "
                            "ol.Tree, ol.Config from WMS_DM_OBJECTLIST ol, WMS_CLASS cl where ol.Keyname = '%1' "
                            "and ol.ClassId = cl.ClassId and cl.DataBaseId = %2")
                        .arg(CwmsUtilities::MaskStringForChanges(m_qstrKeyname))
                        .arg(m_lSchemeId);
    }

    return qstrQuery;
}

int CdbCommandLoadContainer::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    QDateTime qdtLastChange;
    QSqlQuery cQSqlQuery;

    if (m_rpContainer)
    {
        CdmDataAccessHelper::DeleteObjectContainer(m_rpContainer);
    }

    // Creating the Objectlist
    QString qstrQuery = GetContainerQuery();

    if (GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
        cQSqlQuery.first();

        if (cQSqlQuery.isValid())
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
            QString qstrConfig     = cQSqlQuery.value(10).toString();

            m_rpContainer =CdmDataAccessHelper::CreateObjectContainer(lDatabaseId, m_lContainerId, qstrKeyname, lClassId);
            m_rpContainer->SetTree(bTree);
            m_rpContainer->SetCaption(qstrCaption);
            m_rpContainer->SetComment(qstrComment);
            m_rpContainer->SetConfig(qstrConfig);
            CdmDataAccessHelper::SetCreatorId(m_rpContainer, lCreatorId);
            CdmDataAccessHelper::SetModifierId(m_rpContainer, lLastModifierId);

            INFO("Container Basedata successfull loaded!!!")
            lRet = LoadObjectListRights();
        }
        else
        {
            lRet = EC(eDmObjectListNotFound);

            if (m_lContainerId > 0)
            {
                INFO("Container with the Id " + QString::number(m_lContainerId) + " not found")
            }
            else
            {
                INFO("Container with the Keyname \"" + m_qstrKeyname + "\" not found")
            }
        }
    }
    else
    {
        lRet = EC(eDmInvalidSelectStatement);
    }

    if (m_rpContainer)
    {
        LoadObjects();
        m_rpContainer->ResetNewModified();
        m_rpContainer->SetLastChange(qdtLastChange);
    }

    return static_cast<int>(lRet);
}

void CdbCommandLoadContainer::LoadObjects()
{
    if (m_bLoadObjects)
    {
        QList<long> qvlObjects;
        QSqlQuery cQSqlQuery;
        QString qstrQuery = GetObjectQuery();

        if (GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
        {
            cQSqlQuery.first();

            if (cQSqlQuery.isValid())
            {
                do
                {
                    qvlObjects.append(cQSqlQuery.value(0).toInt());
                }
                while(cQSqlQuery.next());
            }
            else
            {
                INFO("No Object found in this ObjectList!!")
            }
        }

        CdbCommandLoadObjects command(m_rpContainer, qvlObjects, GetDataAccess());
        command.Run();
    }
}

long CdbCommandLoadContainer::LoadObjectListRights()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpContainer))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;
      // query for reading new id
      qstrQuery = QString("select AccessorId, AccessRight from WMS_DM_ACCESSORRIGHT where ObjectListId = %1")
                          .arg(m_rpContainer->GetId());

      lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

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

