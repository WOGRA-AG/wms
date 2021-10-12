
// WMS Includes
#include "CdmObjectContainer.h"

#include "CftlCommandLoadObjects.h"
#include "CftlCommandRefreshComtainer.h"

CftlCommandRefreshComtainer::CftlCommandRefreshComtainer(CdmObjectContainer* p_pContainer, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_rpContainer(p_pContainer)
{
}

CftlCommandRefreshComtainer::~CftlCommandRefreshComtainer()
{
}

bool CftlCommandRefreshComtainer::CheckValid()
{
    return CHKPTR(m_rpContainer);
}

int CftlCommandRefreshComtainer::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   QDateTime qdtLastChange;

   // loading container data
   cQSqlQuery.prepare("Select ol.LastChange, ol.ModifierId, ol.Caption, ol.Comment from WMS_DM_CONTAINER ol, "
                       "WMS_CLASS cl where ol.Keyname = ? and ol.ClassId = cl.ClassId and cl.SchemeId = ?");
   cQSqlQuery.addBindValue(m_rpContainer->GetKeyname());
   cQSqlQuery.addBindValue(m_rpContainer->GetSchemeId());

   if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {
         qdtLastChange           = cQSqlQuery.value(0).toDateTime();
        qint64 lLastModifierId    = cQSqlQuery.value(1).toInt();
         QString qstrCaption     = cQSqlQuery.value(2).toString();
         QString qstrComment     = cQSqlQuery.value(3).toString();

         if (qdtLastChange.secsTo(QDateTime::currentDateTime()) < m_rpContainer->GetLastChange().secsTo(QDateTime::currentDateTime()))
         {
            lRet = EC(eDmTrue);
            m_rpContainer->SetModifierId(lLastModifierId);
            m_rpContainer->SetCaption(qstrCaption);
            m_rpContainer->SetComment(qstrComment);
         }
         else
         {
            lRet = EC(eDmFalse);
         }
      }
      else
      {
         lRet = EC(eDmObjectListNotFound);
      }
   }

   if (lRet == CdmLogging::eDmTrue)
   {
      m_rpContainer->ClearContainerLocal();
      CftlCommandLoadObjects command(m_rpContainer, GetDataAccess());
      lRet = command.Run();
      m_rpContainer->ResetNewModified();
      m_rpContainer->SetLastChange(qdtLastChange);
   }

   return lRet;
}
