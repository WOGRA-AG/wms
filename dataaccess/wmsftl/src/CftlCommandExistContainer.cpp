// System and Qt Includes
#include <QSqlQuery>

// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"

// Own Includes
#include "CftlCommandExistContainer.h"

CftlCommandExistContainer::CftlCommandExistContainer(QString p_qstrContainer, CftlDataAccess* p_pDataAccess)
    : CftlAbstractCommand(p_pDataAccess),
      m_qstrContainerKeyname(p_qstrContainer)
{
}

CftlCommandExistContainer::~CftlCommandExistContainer()
{
}

bool CftlCommandExistContainer::CheckValid()
{
    return (!m_qstrContainerKeyname.isEmpty() && CHKPTR(GetDataAccess()));
}

int CftlCommandExistContainer::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    CdmDataProvider* pProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pProvider))
    {
        CdmScheme* pScheme = pProvider->GetCurrentScheme();

        if (CHKPTR(pScheme))
        {
            long lSchemeId = pScheme->GetId();
            QSqlQuery cQSqlQuery(GetSqlDatabase());

            cQSqlQuery.prepare("Select ContainerId from WMS_DM_CONTAINER cont "
                               "inner join WMS_CLASS cl on cl.ClassId = cont.ClassId "
                               "inner join WMS_SCHEME sc on sc.SchemeId = cl.SChemeId "
                               "where cont.Keyname = ? and sc.SchemeId = ?");
            cQSqlQuery.addBindValue(m_qstrContainerKeyname);
            cQSqlQuery.addBindValue((int)lSchemeId);

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
