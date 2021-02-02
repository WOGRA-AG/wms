
// WMS Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmClassManager.h"


// Own Includes
#include "CftlContainerTableDrop.h"
#include "CftlCommandDeleteClass.h"

CftlCommandDeleteClass::CftlCommandDeleteClass(long p_lClassId, CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess),
  m_lClassId(p_lClassId)
{
}


CftlCommandDeleteClass::~CftlCommandDeleteClass()
{
}


bool CftlCommandDeleteClass::CheckValid()
{
    return (m_lClassId >0);
}

long CftlCommandDeleteClass::DropClassTable()
{
    long lRet = CdmLogging::eDmUnknownDBQueryError;
    CdmDataProvider* pDataProvider = CdmSessionManager::GetSessionManager()->GetDataProvider();

    if (CHKPTR(pDataProvider))
    {
        CdmClassManager* pClassManager = pDataProvider->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            CdmClass* pClass = pClassManager->FindClassById(m_lClassId);
            if (CHKPTR(pClass))
            {
                CftlContainerTableDrop dropper(pClass, GetDialect());
                lRet = dropper.Execute(GetInterface());
            }
            else
            {
                lRet = CdmLogging::eDmInvalidClassPtr;
            }
        }
    }

    return lRet;
}

int CftlCommandDeleteClass::Execute()
{
    int iRet = CdmLogging::eDmUnknownClassAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());

    // query for reading new id
    cQSqlQuery.prepare("delete from WMS_CLASS where ClassID = ?");
    cQSqlQuery.addBindValue((int)m_lClassId);

    // Deleting class itselves
    if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
       iRet = DropClassTable();
    }
    else
    {
       iRet = EC(eDmInvalidDeleteStatement);
       ERR("The Class could not be deleted (Error in Query)!!!");
    }

    return iRet;
}
