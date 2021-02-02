// System and Qt Includes
#include <QSqlQuery>
#include <QDate>

// WMS Includes
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes
#include "CdbJournal.h"
#include "CdbCommandCheckObjectLocked.h"
#include "CdbCommandDeleteObject.h"

CdbCommandDeleteObject::CdbCommandDeleteObject(long p_lObjectId, long p_lSessionId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess),
  m_lObjectId(p_lObjectId),
  m_lSessionId(p_lSessionId)
{
}

CdbCommandDeleteObject::~CdbCommandDeleteObject()
{

}

bool CdbCommandDeleteObject::CheckValid()
{
    return (m_lObjectId > 0 && m_lSessionId > 0 && CHKPTR(GetDataAccess()));
}

int CdbCommandDeleteObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(GetDataAccess()))
    {
        CdbCommandCheckObjectLocked checkObjectLocked(m_lObjectId, m_lSessionId, GetDataAccess());

       if(!checkObjectLocked.Run())
       {
          QSqlQuery cQSqlQuery;
          QString qstrQuery;

          qstrQuery = QString("Delete from WMS_DM_OBJECT where ObjectId = %1")
                              .arg(m_lObjectId);

          // Deleting Object itselves
          lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

          if(lRet <= 0)
          {
             lRet = EC(eDmInvalidDeleteStatement);
             ERR("The query execution failed!!");
          }
          else
          {
             CdbJournal* pJournal = GetDataAccess()->GetJournal();

             if (pJournal)
             {
                lRet = pJournal->ObjectDeleted(m_lObjectId);
             }
          }
       }
       else
       {
          lRet = EC(eDmObjectDeathLock);
          ERR("Cannot delete object because it's locked.");
       }
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    return lRet;

}
