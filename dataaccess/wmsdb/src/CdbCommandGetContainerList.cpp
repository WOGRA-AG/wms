
#include "CdmSessionManager.h"
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"

#include "CdbCommandGetContainerList.h"

CdbCommandGetContainerList::CdbCommandGetContainerList(qint64 p_lSchemeId,qint64 p_lClassId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lSchemeId(p_lSchemeId),
  m_lClassId(p_lClassId)
{
}

CdbCommandGetContainerList::~CdbCommandGetContainerList()
{

}

void CdbCommandGetContainerList::GetResult(QMap<qint64, QString> &p_rqmContainerList)
{
    p_rqmContainerList = m_qmContainer;
}

bool CdbCommandGetContainerList::CheckValid()
{
    // Class Id can be 0
    return (m_lSchemeId > 0 && m_lClassId >= 0 && CHKPTR(GetDataAccess()));
}

int CdbCommandGetContainerList::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;

   if(m_lClassId == 0)
   {
      qstrQuery = QString("Select ol.ObjectListId, ol.Keyname from WMS_DM_OBJECTLIST ol, WMS_CLASS cl where "
                          "cl.DatabaseId =  %1")
                          .arg(m_lSchemeId);
   }
   else
   {
      qstrQuery = QString("Select ol.ObjectListId, ol.Keyname from WMS_DM_OBJECTLIST ol, WMS_CLASS cl where "
                          "cl.ClassId = ol.ClassId and cl.DatabaseId =  %1 and ol.ClassId in %2")
                          .arg(m_lSchemeId)
                          .arg(GetClassListString());
   }

   m_qmContainer.clear();

   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      cQSqlQuery.first();

      if(cQSqlQuery.isValid())
      {
         do
         {
           qint64 lId = cQSqlQuery.value(0).toInt();
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

QString CdbCommandGetContainerList::GetClassListString()
{
    QString qstrClassList;
    QList<qint64> qlClasses = GetClassList();

    if (qlClasses.count() > 0)
    {
        qstrClassList = "(";
        bool bFirst = true;

        for(int iPos = 0; iPos < qlClasses.count(); ++iPos)
        {
            if (!bFirst)
            {
                qstrClassList += ", ";
            }

            bFirst = false;

            qstrClassList += QString::number(qlClasses[iPos]);
        }

        qstrClassList += ")";
    }

    return qstrClassList;
}

QList<qint64> CdbCommandGetContainerList::GetClassList()
{
    QList<qint64> qlClasses;
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pManager))
    {
        CdmClassManager* pClassManager = pManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            qlClasses.append(m_lClassId);
            CdmClass* pClass = pClassManager->FindClassById(m_lClassId);

            if (CHKPTR(pClass))
            {
                qlClasses.append(pClass->GetDerivedClasses());
            }
        }
    }

    return qlClasses;
}
