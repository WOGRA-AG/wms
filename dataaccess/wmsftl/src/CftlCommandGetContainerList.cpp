#include "CftlCommandGetContainerList.h"

CftlCommandGetContainerList::CftlCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_lClassId(p_lClassId)
{
}

CftlCommandGetContainerList::~CftlCommandGetContainerList()
{

}

void CftlCommandGetContainerList::GetResult(QMap<qint64, QString> &p_rqmContainerList)
{
    p_rqmContainerList = m_qmContainer;
}

bool CftlCommandGetContainerList::CheckValid()
{
    // Class Id can be 0
    return (m_lSchemeId > 0 && m_lClassId >= 0 && CHKPTR(GetDataAccess()));
}

int CftlCommandGetContainerList::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   QString qstrQuery;

   if(m_lClassId == 0)
   {
       cQSqlQuery.prepare("Select ol.ContainerId, ol.Keyname, ol.caption from WMS_DM_CONTAINER ol, WMS_CLASS cl where "
                          "cl.ClassId = ol.ClassId and cl.SchemeId =  ?");
       cQSqlQuery.addBindValue(m_lSchemeId);
   }
   else
   {
      cQSqlQuery.prepare("Select ol.ContainerId, ol.Keyname, ol.caption from WMS_DM_CONTAINER ol, WMS_CLASS cl where "
                          "cl.ClassId = ol.ClassId and cl.SchemeId =  ? and ol.ClassId = ?");
      cQSqlQuery.addBindValue(m_lSchemeId);
      cQSqlQuery.addBindValue(m_lClassId);
   }

   m_qmContainer.clear();

   if(SUCCESSFULL(GetDataAccess()->ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
         do
         {
           qint64 lId = cQSqlQuery.value(0).toInt();
            QString qstrKeyname = cQSqlQuery.value(1).toString();
            QString qstrCaption = cQSqlQuery.value(2).toString();

            if (qstrCaption != qstrKeyname)
            {
                qstrKeyname = QString("%1 (%2)").arg(qstrCaption, qstrKeyname);
            }

            m_qmContainer.insert(lId, qstrKeyname);
         }
         while(cQSqlQuery.next());

         lRet = EC(eDmTrue);
      }
      else
      {
         lRet = EC(eDmObjectListNotFound);
         INFO("No ObjectLists found in Database!!");
      }
   }
   else
   {
      lRet = EC(eDmInvalidSelectStatement);
   }

   return lRet;
}
