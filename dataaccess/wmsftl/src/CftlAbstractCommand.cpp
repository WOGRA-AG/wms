// WMS Includes
#include "CdmObject.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmSession.h"
#include "CdmClass.h"


// Own Includes
#include "CftlInterface.h"
#include "CftlCommandUpdateSession.h"
#include "CftlCommandFindSession.h"
#include "CftlAbstractCommand.h"



CftlAbstractCommand::CftlAbstractCommand(CftlDataAccess* p_pDataAccess)
    : m_rpDataAccess(p_pDataAccess)
{
}

CftlAbstractCommand::~CftlAbstractCommand()
{

}

int CftlAbstractCommand::Run()
{
    int iRet = Validate();

    if (SUCCESSFULL(iRet))
    {
        if (NeedsSessionCheck())
        {
            iRet = SessionCheck();
        }

        if (SUCCESSFULL(iRet))
        {
            iRet = Execute();
        }
    }

    return iRet;
}

long CftlAbstractCommand::ExecuteQuery(QString p_qstrQuery, QSqlQuery& p_rqsqlQuery)
{
    return m_rpDataAccess->ExecuteQuery(p_qstrQuery,p_rqsqlQuery);
}

long CftlAbstractCommand::ExecuteQuery(QSqlQuery& p_rqsqlQuery)
{
    return m_rpDataAccess->ExecuteQuery(p_rqsqlQuery);
}

CftlDialect *CftlAbstractCommand::GetDialect()
{
    CftlInterface* pInterface = GetInterface();

    if (CHKPTR(pInterface))
    {
        return pInterface->GetDialect();
    }

    return nullptr;
}

CftlInterface *CftlAbstractCommand::GetInterface()
{
    return m_rpDataAccess->GetFtlInterface();
}


bool CftlAbstractCommand::Validate()
{
    return (CHKPTR(m_rpDataAccess) && CheckValid());
}


CftlDataAccess* CftlAbstractCommand::GetDataAccess()
{
    return m_rpDataAccess;
}

const CdmClass* CftlAbstractCommand::GetClassFromContainerId(long p_lId)
{
    CdmDataProvider* pDataProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmContainerManager* pContainerManager = pDataProvider->GetContainerManager();

        if (CHKPTR(pContainerManager))
        {
            CdmObjectContainer* pContainer = pContainerManager->FindEmptyContainerById(p_lId);

            if (CHKPTR(pContainer))
            {
                 return pContainer->GetClass();
            }
        }
    }

    return nullptr;
}

QString CftlAbstractCommand::GetClassTableNameFromObject(const CdmObject* p_pObject)
{
    if (CHKPTR(p_pObject))
    {
        const CdmClass* pClass = p_pObject->GetClass();

        if (CHKPTR(pClass))
        {
            return pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
        }
    }

    return "";
}

QString CftlAbstractCommand::GetClassTableNameFromContainerId(long p_lId)
{
    const CdmClass* pClass = GetClassFromContainerId(p_lId);

    if (CHKPTR(pClass))
    {
        return pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
    }

    return "";
}

QString CftlAbstractCommand::GetClassTableNameFromContainer(const CdmObjectContainer* p_pContainer)
{
    const CdmClass* pClass = p_pContainer->GetClass();

    if (CHKPTR(pClass))
    {
        return pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
    }

    return "";
}

QSqlDatabase CftlAbstractCommand::GetSqlDatabase()
{
    CftlInterface* pInterface = GetInterface();

    if (CHKPTR(pInterface))
    {
        return pInterface->GetSqlDatabase();
    }

    return QSqlDatabase();
}

int CftlAbstractCommand::InsertInAccessorTable(EumUserGroupType p_eType)
{
    int iAccessorId =  0;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    cQSqlQuery.prepare("insert into WMS_UM_ACCESSOR(AccessorType, NewAccessor) values(?, true)");
    cQSqlQuery.addBindValue(p_eType);

    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       cQSqlQuery.prepare("select AccessorId from WMS_UM_ACCESSOR where AccessorType = ? and NewAccessor = true");
       cQSqlQuery.addBindValue(p_eType);

       if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
       {
          cQSqlQuery.first();
          if(cQSqlQuery.isValid())
          {
             iAccessorId = cQSqlQuery.value(0).toInt();
          }

          cQSqlQuery.prepare("update WMS_UM_ACCESSOR set newaccessor = false where AccessorId = ?");
          cQSqlQuery.addBindValue(iAccessorId);

          if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
          {
               INFO("Accessor created")
          }
          else
          {
             iAccessorId = EC(eDmAccessorIdNotFoundInDb);
          }
       }
       else
       {
          iAccessorId = EC(eDmInvalidSelectStatement);
       }
    }
    else
    {
       iAccessorId = EC(eDmInvalidInsertStatement);
    }

    return iAccessorId;
}

bool CftlAbstractCommand::NeedsSessionCheck()
{
    return true;
}

int CftlAbstractCommand::SessionCheck()
{
    long lRet = CdmLogging::eDmUnknownSqlError;
    CftlInterface* pInterface = GetInterface();

    if (CHKPTR(pInterface))
    {
        if (!pInterface->IsTransactionRunning())
        {
            CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

            if (CHKPTR(pSessionManager))
            {
                long iSessionId = pSessionManager->GetCurrentSessionId();
                long iUserId = pSessionManager->GetCurrentUserId();
                CftlCommandFindSession command(iSessionId, iUserId, m_rpDataAccess);
                lRet = command.Run();

                if (SUCCESSFULL(lRet))
                {
                  UpdateSession();
                }
            }
        }
        else
        {
            lRet = EC(eDmOk);
        }
    }

    return lRet;
}

void CftlAbstractCommand::UpdateSession()
{
    long lSessionId = CdmSessionManager::GetSessionManager()->GetCurrentSessionId();
    CdmSession* pSession = CdmSessionManager::GetSessionManager()->FindSessionLocal();

    if (CHKPTR(pSession) && pSession->NeedsUpdate())
    {
        CftlCommandUpdateSession command(lSessionId, GetDataAccess());
        command.Run();
        pSession->SessionUpdated();
    }
}
