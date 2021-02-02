#include "CdmLogging.h"
#include "CumAccessor.h"

#include "CdbCommandCreateUserGroup.h"


CdbCommandCreateUserGroup::CdbCommandCreateUserGroup(QString p_qstrGroupName, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_qstrNewName(p_qstrGroupName)
{
}

CdbCommandCreateUserGroup::~CdbCommandCreateUserGroup()
{
}

int CdbCommandCreateUserGroup::Execute()
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    int iAccessorId = InsertInAccessorTable();

    if(SUCCESSFULL(iAccessorId))
    {
       lRet = InsertInGroupTable(iAccessorId);
    }

    return lRet;
}

int CdbCommandCreateUserGroup::InsertInGroupTable(int p_iAccessorId)
{
    long lRet = CdmLogging::eDmUnknownUserQueryError;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;

   qstrQuery = QString("insert into WMS_UM_GROUP (GroupId, Name) values(%1, '%2')")
      .arg(p_iAccessorId)
      .arg(CwmsUtilities::MaskStringForChanges(m_qstrNewName));

   if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      lRet = p_iAccessorId;
   }
   else
   {
      lRet = EC(CdmLogging::eDmInvalidInsertStatement);
      ERR("Insert Usergroup failed!!!");
   }

   return lRet;
}

int CdbCommandCreateUserGroup::InsertInAccessorTable()
{
    int iAccessorId =  0;
    QSqlQuery cQSqlQuery;
    QString qstrQuery;
    qstrQuery = QString("insert into WMS_UM_ACCESSOR(AccessorType, NewAccessor) values(%1, true)")
                 .arg(eUmUserGroupTypeUser);

    if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
    {
       qstrQuery = QString("select AccessorId from WMS_UM_ACCESSOR "
                           "where AccessorType = %1 and NewAccessor = true")
                     .arg(eUmUserGroupTypeUser);

       if(ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
       {
          cQSqlQuery.first();
          if(cQSqlQuery.isValid())
          {
             iAccessorId = cQSqlQuery.value(0).toInt();
          }

          qstrQuery = QString("update WMS_UM_ACCESSOR set newaccessor = false "
                              "where AccessorId = %1")
                                .arg(iAccessorId);

          if(SUCCESSFULL(ExecuteQuery(qstrQuery, cQSqlQuery)))
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


bool CdbCommandCreateUserGroup::CheckValid()
{
    return !m_qstrNewName.isEmpty();
}
