// System and Qt Includes
#include <QSqlQuery>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// Own Includes
#include "CdbJournal.h"
#include "CdbCommandDeleteContainer.h"

CdbCommandDeleteContainer::CdbCommandDeleteContainer(qint64 p_lContainerId, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lContainerId(p_lContainerId)
{
}

CdbCommandDeleteContainer::~CdbCommandDeleteContainer()
{
}

bool CdbCommandDeleteContainer::CheckValid()
{
    return (m_lContainerId > 0);
}

int CdbCommandDeleteContainer::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if(CHKPTR(GetDataAccess()))
    {
       QSqlQuery cQSqlQuery;
       QString qstrQuery;

       qstrQuery = QString("delete from WMS_DM_OBJECTLIST where ObjectListId = %1")
                          .arg(m_lContainerId);

       lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

       if(lRet < 0)
       {
          ERR("Delete Object List failed!!!");
          lRet = EC(eDmInvalidDeleteStatement);
       }
       else
       {
          CdbJournal* pJournal = GetDataAccess()->GetJournal();

          if (pJournal)
          {
             lRet = pJournal->ObjectListDeleted(m_lContainerId);
          }
       }
    }
    else
    {
       lRet = EC(eDmInvalidPtr);
    }

    return lRet;
}


