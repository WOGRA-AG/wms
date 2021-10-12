
// WMS Includes
#include "CdmObjectContainer.h"

#include "CdbCommandLoadObjects.h"
#include "CdbCommandRefreshComtainer.h"

CdbCommandRefreshComtainer::CdbCommandRefreshComtainer(CdmObjectContainer* p_pContainer, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer)
{
}

CdbCommandRefreshComtainer::~CdbCommandRefreshComtainer()
{
}

bool CdbCommandRefreshComtainer::CheckValid()
{
    return CHKPTR(m_rpContainer);
}

int CdbCommandRefreshComtainer::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   QDateTime qdtLastChange;
   QList<qint64> qvlObjects;

   // query for reading new id
   qstrQuery = QString("Select ObjectId from WMS_DM_OBJECT where ObjectListId = %1").arg(m_rpContainer->GetId());

   // loading objectid's
   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         do
         {
            qvlObjects.append(cQSqlQuery.value(0).toInt());
         }
         while(cQSqlQuery.next());
      }
      else
      {
         INFO("No Object found in this ObjectList!!");
      }
   }

   // loading Objectlist data
   qstrQuery = QString("Select ol.LastChange, ol.ModifierId, ol.Caption, ol.Comment from WMS_DM_OBJECTLIST ol, "
                       "WMS_CLASS cl where ol.Keyname = '%1' and ol.ClassId = cl.ClassId and cl.DataBaseId "
                       "= %2")
                        .arg(CwmsUtilities::MaskStringForChanges(m_rpContainer->GetKeyname()))
                        .arg(m_rpContainer->GetSchemeId());

   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {

      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         qdtLastChange           = cQSqlQuery.value(0).toDateTime();
        qint64 lLastModifierId    = cQSqlQuery.value(1).toInt();
         QString qstrCaption     = cQSqlQuery.value(2).toString();
         QString qstrComment     = cQSqlQuery.value(3).toString();

         lRet = EC(eDmTrue);
         m_rpContainer->SetModifierId(lLastModifierId);
         m_rpContainer->SetCaption(qstrCaption);
         m_rpContainer->SetComment(qstrComment);
      }
      else
      {
         lRet = EC(eDmObjectListNotFound);
      }
   }

   if (lRet == CdmLogging::eDmTrue)
   {
      m_rpContainer->ClearContainerLocal();
      CdbCommandLoadObjects command(m_rpContainer, qvlObjects, GetDataAccess());
      lRet = command.Run();
      m_rpContainer->ResetNewModified();
      m_rpContainer->SetLastChange(qdtLastChange);
   }

   return lRet;

}
