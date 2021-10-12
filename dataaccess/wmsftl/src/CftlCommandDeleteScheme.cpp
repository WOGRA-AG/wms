
// WMS Core Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmScheme.h"

// Own Includes
#include "CftlCommandCleanupDB.h"
#include "CftlContainerTableDrop.h"
#include "CftlCommandDeleteScheme.h"

CftlCommandDeleteScheme::CftlCommandDeleteScheme(QString p_qstrSchemeName, CftlDataAccess* p_pDataAccess)
    : CftlAbstractTransactionalCommand(p_pDataAccess),
      m_qstrSchemeName(p_qstrSchemeName)
{
}


CftlCommandDeleteScheme::~CftlCommandDeleteScheme()
{

}

bool CftlCommandDeleteScheme::CheckValid()
{
    return (!m_qstrSchemeName.isEmpty());
}

int CftlCommandDeleteScheme::Execute()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());


   qint64 lId = GetSchemeId();

    lRet = DropClassTables(lId);

    if (SUCCESSFULL(lRet))
    {
        cQSqlQuery.prepare("delete from WMS_SCHEME where SchemeName = ?");
        cQSqlQuery.addBindValue(m_qstrSchemeName);

        if(SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
        {
           lRet = GetDataAccess()->DeleteRights(lId, "WMS_SCHEME_RIGHTS", "SchemeId");
        }

        DeleteLanguages(lId);

        CftlCommandCleanupDB command(GetDataAccess());

        if (!SUCCESSFULL(command.Run()))
        {
           lRet = CdmLogging::eDmInvalidDeleteStatement;
        }
    }

    return lRet;
}

void CftlCommandDeleteScheme::DeleteLanguages(qint64 p_lSchemeId)
{
    QSqlQuery cQSqlQuery(GetSqlDatabase());
    cQSqlQuery.prepare("delete from WMS_LANGUAGE where SchemeId = ?");
    cQSqlQuery.addBindValue(p_lSchemeId);

    if(!SUCCESSFULL(ExecuteQuery(cQSqlQuery)))
    {
        ERR("Failed deleting Languages to Scheme!");
    }
}

int CftlCommandDeleteScheme::DropClassTables(qint64 p_lSchemeId)
{
    int iRet =  CdmLogging::eDmOk;
    if (p_lSchemeId > 0)
    {
        CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

        if (CHKPTR(pSessionManager))
        {
            CdmDataProvider* pDataProvider = pSessionManager->GetDataProvider();

            if (CHKPTR(pDataProvider))
            {
                CdmScheme* pScheme = pDataProvider->FindSchemeById(p_lSchemeId);

                if (CHKPTR(pScheme))
                {
                    CdmClassManager* pClassManager = pScheme->GetClassManager();


                    if (CHKPTR(pClassManager))
                    {
                        QList<CdmClass*> qllClasses;
                        pClassManager->GetClassList(qllClasses);
                        QList<CdmClass*>::iterator qllIt = qllClasses.begin();
                        QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

                        for (; qllIt != qllItEnd; ++qllIt)
                        {
                            CdmClass* pClass = *qllIt;

                            if (CHKPTR(pClass))
                            {
                                CftlContainerTableDrop drop(pClass, GetDialect());
                                iRet = drop.Execute(GetInterface());
                            }
                        }
                    }
                }

            }
        }
    }

    return iRet;
}

qint64 CftlCommandDeleteScheme::GetSchemeId()
{
   qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
    QSqlQuery cQSqlQuery(GetSqlDatabase());


    cQSqlQuery.prepare("Select SchemeId from WMS_SCHEME where SchemeName = ?");
    cQSqlQuery.addBindValue(m_qstrSchemeName);

    if(ExecuteQuery(cQSqlQuery) > 0)
    {
        cQSqlQuery.first();

        if(cQSqlQuery.isValid())
        {
            lRet = cQSqlQuery.value(0).toInt();
        }
        else
        {
            lRet = EC(eDmFalse);
        }
    }
    else
    {
        lRet = EC(eDmInvalidSelectStatement);
    }

   return lRet;
}
