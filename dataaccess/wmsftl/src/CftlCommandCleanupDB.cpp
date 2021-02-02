#include "CftlCommandCleanupDB.h"

CftlCommandCleanupDB::CftlCommandCleanupDB(CftlDataAccess* p_pDataAccess)
: CftlAbstractTransactionalCommand(p_pDataAccess)
{
}


CftlCommandCleanupDB::~CftlCommandCleanupDB()
{

}

bool CftlCommandCleanupDB::CheckValid()
{
    return true;
}

int CftlCommandCleanupDB::Execute()
{
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    long lRet = EC(eDmOk);

    qstrQuery =
            QString("delete from WMS_CLASS "
                    "where SchemeId not in(select SchemeId from WMS_SCHEME)");

    if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
    {
       lRet = CdmLogging::eDmInvalidDeleteStatement;
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_MEMBER "
                       "where ClassId not in(select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_METHOD "
                       "where ClassId not in(select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_VALIDATION "
                       "where ClassId not in(select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
         lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_BASECLASS "
                       "where ClassId not in(select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }


    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_GROUP "
                       "where ClassId not in(select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
         lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_GROUP_RIGHTS "
                       "where GroupId not in(select id from WMS_CLASS_GROUP)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_GROUP_TRANSLATION "
                       "where GroupId not in(select id from WMS_CLASS_GROUP)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_METHOD_RIGHTS "
                       "where MethodId not in(select id from WMS_CLASS_METHOD)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_MEMBER_TRANSLATION "
                       "where MemberId not in(select memberid from WMS_CLASS_MEMBER)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_CLASS_MEMBER_RIGHTS "
                       "where MemberId not in(select memberid from WMS_CLASS_MEMBER)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_DM_CONTAINER "
                       "where ClassId not in (select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    return lRet;
}
