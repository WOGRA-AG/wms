// System and Qt Includes
#include <QSqlQuery>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"

// OWn Includes
#include "CdbCommandExistContainer.h"

CdbCommandExistContainer::CdbCommandExistContainer(QString p_qstrContainer, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_qstrContainerKeyname(p_qstrContainer)
{
}

CdbCommandExistContainer::~CdbCommandExistContainer()
{
}

bool CdbCommandExistContainer::CheckValid()
{
    return (!m_qstrContainerKeyname.isEmpty() && CHKPTR(GetDataAccess()));
}

int CdbCommandExistContainer::Execute()
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;
    CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pProvider))
    {
        CdmScheme* pScheme = pProvider->GetCurrentScheme();

        if (CHKPTR(pScheme))
        {
           qint64 lSchemeId = pScheme->GetId();
            QSqlQuery cQSqlQuery(GetSqlDatabase());

            cQSqlQuery.prepare("Select ContainerId from WMS_DM_CONTAINER cont "
                               "inner join WMS_CLASS cl on cl.ClassId = cont.ClassId "
                               "inner join WMS_DATABASE sc on sc.DatabaseId = cl.SChemeId "
                               "where cont.Keyname = ? and sc.DatabaseId = ?");
            cQSqlQuery.addBindValue(m_qstrContainerKeyname);
            cQSqlQuery.addBindValue(lSchemeId);

            if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
            {
                cQSqlQuery.first();
                if(cQSqlQuery.isValid())
                {
                    INFO("Container with Keyname " + m_qstrContainerKeyname + " found");
                    lRet = EC(eDmTrue);
                }
                else
                {
                    INFO("Container with Keyname " + m_qstrContainerKeyname + " NOT found");
                    lRet = EC(eDmFalse);
                }
            }
            else
            {
                lRet = EC(eDmInvalidSelectStatement);
                ERR("Query Execution failed!!");
            }
        }
    }

    return lRet;
}
