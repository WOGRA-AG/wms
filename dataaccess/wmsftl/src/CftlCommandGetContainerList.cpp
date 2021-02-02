#include "CftlCommandGetContainerList.h"

CftlCommandGetContainerList::CftlCommandGetContainerList(long p_lSchemeId, long p_lClassId, CftlDataAccess* p_pDataAccess)
: CftlAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_lClassId(p_lClassId)
{
}

CftlCommandGetContainerList::~CftlCommandGetContainerList()
{

}

void CftlCommandGetContainerList::GetResult(QMap<long, QString> &p_rqmContainerList)
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
   long lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery(GetSqlDatabase());
   QString qstrQuery;

   if(m_lClassId == 0)
   {
       cQSqlQuery.prepare("Select ol.ContainerId, ol.Keyname from WMS_DM_CONTAINER ol, WMS_CLASS cl where "
                          "cl.ClassId = ol.ClassId and cl.SchemeId =  ?");
       cQSqlQuery.addBindValue((int)m_lSchemeId);
   }
   else
   {
      cQSqlQuery.prepare("Select ol.ContainerId, ol.Keyname from WMS_DM_CONTAINER ol, WMS_CLASS cl where "
                          "cl.ClassId = ol.ClassId and cl.SchemeId =  ? and ol.ClassId = ?");
      cQSqlQuery.addBindValue((int)m_lSchemeId);
      cQSqlQuery.addBindValue((int)m_lClassId);
   }

   m_qmContainer.clear();

   if(SUCCESSFULL(GetDataAccess()->ExecuteQuery(cQSqlQuery)))
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
         do
         {
            long lId = cQSqlQuery.value(0).toInt();
            QString qstrKeyname = cQSqlQuery.value(1).toString();
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
