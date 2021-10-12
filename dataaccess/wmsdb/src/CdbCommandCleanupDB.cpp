#include "CdbCommandCleanupDB.h"

CdbCommandCleanupDB::CdbCommandCleanupDB(CdbDataAccess* p_pDataAccess)
: CdbAbstractCommandTransactional(p_pDataAccess)
{
}


CdbCommandCleanupDB::~CdbCommandCleanupDB()
{

}

bool CdbCommandCleanupDB::CheckValid()
{
    return true;
}

int CdbCommandCleanupDB::Execute()
{
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
   qint64 lRet = EC(eDmOk);

    qstrQuery =
            QString("delete from WMS_CLASS "
                    "where DataBaseId not in(select databaseid from WMS_DATABASE)");

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
               QString("delete from WMS_DM_OBJECTLIST "
                       "where ClassId not in (select classid from WMS_CLASS)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

    if (SUCCESSFULL(lRet))
    {
       qstrQuery =
               QString("delete from WMS_DM_OBJECT "
                       "where ObjectlistId not in(select objectlistid from WMS_DM_OBJECTLIST)");

       if(ExecuteQuery(qstrQuery, cQSqlQuery) <= 0)
       {
          lRet = CdmLogging::eDmInvalidDeleteStatement;
       }
    }

	return lRet;
}
