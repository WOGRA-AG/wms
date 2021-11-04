// System and Qt Includes
#include <QFileInfo>

// WMS includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
#include "CdmLogging.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmValueListObjects.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CdmValueEnum.h"
#include "CdmDataAccessHelper.h"

// own Includes
#include "CdbJournal.h"
#include "CdbCommandUpdateBinaryDocument.h"
#include "CdbCommandDeleteObject.h"
#include "CdbCommandCheckObjectLocked.h"
#include "CdbCommandUpdateObject.h"
#include "CdbCommandGetCounterValue.h"

CdbCommandUpdateObject::CdbCommandUpdateObject(qint64 p_lSessionId, CdmObject* p_pObject, CdbDataAccess* p_pDataAccess)
    : CdbAbstractCommandTransactional(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_rpObject(p_pObject)
{
}

CdbCommandUpdateObject::~CdbCommandUpdateObject()
{

}

bool CdbCommandUpdateObject::CheckValid()
{
    return (m_lSessionId > 0 && CHKPTR(m_rpObject));
}

int CdbCommandUpdateObject::Execute()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   CdbCommandCheckObjectLocked command(m_rpObject->GetId(), m_lSessionId, GetDataAccess());

   if (!SUCCESSFULL(command.Run())) // is not locked
   {
      if ((m_rpObject->IsNew() || m_rpObject->IsModified()) && !m_rpObject->IsDeleted() && m_rpObject->IsValid())
      {
         lRet = UpdateNewOrModifiedObject();

         if (lRet < 0)
         {
            ERR("UpdateNewOrModifiedObject failed!")
         }
      }
      else if(m_rpObject->IsDeleted() || !m_rpObject->IsValid())
      {
          CdbCommandDeleteObject command(m_rpObject->GetId(), m_lSessionId, GetDataAccess());
          lRet = command.Run();

         if (lRet > 0)
         {
            CdmDataAccessHelper::DeleteObject(m_rpObject);
         }
         else
         {
            ERR("DeleteObject failed!")
         }
      }
      else
      {
         // is not new deleted or modified
         // so nothing is to do
         lRet = EC(eDmOk);
      }
   }
   else
   {
      lRet = EC(eDmObjectDeathLock);
      ERR("Cannot update object because it is locked.")
   }

   BODY_CATCH
   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateNewOrModifiedObject()
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
  QSqlQuery cQSqlQuery;
  QString qstrQuery;
  int iParentId = m_rpObject->GetParentId();
  // first step update object itselves
  qstrQuery = QString("Update WMS_DM_OBJECT set ObjectListId = %1, Keyname = '%2', LastChange = %3, "
                      "CreatorId = %4, ModifierId = %5, Caption = '%6', "
                      "TempSessionId = 0, Parent = %7, config = '%8' where ObjectId = %9")
                    .arg(m_rpObject->GetObjectContainerId())
                    .arg(CwmsUtilities::MaskStringForChanges(m_rpObject->GetKeyname().right(250)))
                    .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                    .arg(m_rpObject->GetCreatorId())
                    .arg(m_rpObject->GetModifierId())
                    .arg(CwmsUtilities::MaskStringForChanges(m_rpObject->GetCaption().left(45)))
                    .arg(iParentId)
                    .arg(CwmsUtilities::MaskStringForChanges(m_rpObject->GetConfig()))
                    .arg(m_rpObject->GetId());


  if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
  {
     // second step insert or update Values
     QMap<QString, CdmValue*> qmValues;
     m_rpObject->GetValueMap(qmValues);

     if (m_rpObject->IsNew())
     {
        CdbJournal* pJournal = GetDataAccess()->GetJournal();

        if (pJournal)
        {
           lRet = pJournal->ObjectModified(m_rpObject);
        }
     }
     else
     {
        lRet = EC(eDmOk);
     }

     QMap<QString, CdmValue*>::iterator qmIt = qmValues.begin();
     QMap<QString, CdmValue*>::iterator qmItEnd = qmValues.end();
     int iCounter = 0;

     for(; qmIt != qmItEnd; ++qmIt)
     {
        CdmValue* pCdmValue = qmIt.value();
        ++iCounter;

        if(CHKPTR(pCdmValue))
        {
           if (!SUCCESSFULL(InsertOrUpdateValue(pCdmValue)))
           {
                break;
           }
        }
        else
        {
           lRet = EC(eDmInvalidPtr);
           break;
        }
     }

     // for the case the object update was successfull
     // and this object has no members
     if(lRet > 0)
     {
        lRet = EC(eDmOk);
        m_rpObject->ResetNewModified();
     }
  }
  else
  {
     lRet = EC(eDmInvalidUpdateStatement);
     ERR("Update query failed!!!");
  }


   return lRet;
}

qint64 CdbCommandUpdateObject::InsertOrUpdateValue(CdmValue* p_pValue)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;;
    if(m_rpObject->IsNew() || p_pValue->IsNew())
    {
       INFO("New Object the Insert method will be called!!");
       lRet = InsertValue(p_pValue);

       if(lRet < 0)
       {
          ERR("Insert Value failed!!!");
       }
    }
    else if(p_pValue->IsModified())
    {
       INFO("Modified Object the Update method will be called!!");
       lRet = UpdateValue(p_pValue);

       if(lRet < 0)
       {
          ERR("Update Value failed!!!");
       }
    }
    else
    {
       lRet = EC(eDmOk);
       INFO("Value is not new and not modified must no be updated or inserted Value Id: " + QString::number(p_pValue->GetId()));
    }

    return lRet;
}

qint64 CdbCommandUpdateObject::InsertValue(CdmValue* p_pValue)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pValue))
   {
      EdmValueType eDmValue = p_pValue->GetValueType();

      switch(eDmValue)
      {
      case eDmValueBool:
         lRet = InsertBool((CdmValueBool*)p_pValue);
         break;
      case eDmValueInt:
         lRet = InsertInt((CdmValueInt*)p_pValue, CdbDataAccess::eOdbcInt);
         break;
      case eDmValueLong:
         lRet = InsertLong((CdmValueLong*)p_pValue);
         break;
      case eDmValueFloat:
         lRet = InsertFloat((CdmValueFloat*)p_pValue);
         break;
      case eDmValueDouble:
         lRet = InsertDouble((CdmValueDouble*)p_pValue);
         break;
      case eDmValueString:
         lRet = InsertString((CdmValueString*)p_pValue);
         break;
      case eDmValueDate:
         lRet = InsertDate((CdmValueDate*)p_pValue);
         break;
      case eDmValueTime:
         lRet = InsertTime((CdmValueTime*)p_pValue);
         break;
      case eDmValueDateTime:
         lRet = InsertDateTime((CdmValueDateTime*)p_pValue);
         break;
      case eDmValueObjectRef:
         lRet = InsertObjectRef((CdmValueObjectRef*)p_pValue);
         break;
      case eDmValueContainerRef:
         lRet = InsertContainerRef((CdmValueContainerRef*)p_pValue);
         break;
      case eDmValueCounter:
         lRet = InsertCounter((CdmValueCounter*)p_pValue);
         break;
      case eDmValueBinaryDocument:
         lRet = InsertBinaryDocument((CdmValueBinaryDocument*)p_pValue);

         if (lRet > 0)
         {
            CdbCommandUpdateBinaryDocument command((CdmValueBinaryDocument*)p_pValue, GetDataAccess());
            lRet = command.Run();
         }

         break;
     // Chardocs and derived documents from chardoc as xml
     case eDmValueCharacterDocument:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcCharDoc);
         break;
      case eDmValueListInt:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListInt);
         break;
      case eDmValueListDouble:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListDouble);
         break;
      case eDmValueListString:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListString);
         break;
      case eDmValueDictStringInt:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringInt);
         break;
      case eDmValueDictStringString:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringString);
         break;
      case eDmValueDictStringDouble:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringDouble);
         break;
      case eDmValueDictIntInt:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictIntInt);
         break;
      case eDmValueDictIntString:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictIntString);
         break;
      case eDmValueDictIntDouble:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eODbcDictIntDouble);
         break;
      case eDmValueListObjects:
         lRet = InsertCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                         CdbDataAccess::eOdbcListObjects);
         break;
      case eDmValueUser:
         lRet = InsertInt((CdmValueInt*)p_pValue,
                          CdbDataAccess::eOdbcUser);
         break;
      case eDmValueUserGroup:
         lRet = InsertInt((CdmValueInt*)p_pValue,
                           CdbDataAccess::eOdbcUserGroup);
         break;
      case eDmValueEnum:
         lRet = InsertInt((CdmValueInt*)p_pValue,
                           CdbDataAccess::eOdbcEnum);
         break;
      case eDmValueFormula:
         lRet = EC(eDmOk);
         break;
      default:
         lRet = EC(eDmUnknownValueError);
         ERR("Invalid Value for writing to object list!!!");
         break;
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   if (lRet < 0)
   {
       ERR("Failed to store Value. Keyname: " + p_pValue->GetKeyname() + " Errorcode:" + QString::number(lRet));
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateValue(CdmValue* p_pValue)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pValue))
   {
      EdmValueType eDmValue = p_pValue->GetValueType();

      switch ( eDmValue )
      {
      case eDmValueBool:
         lRet = UpdateBool((CdmValueBool*)p_pValue);
         break;
      case eDmValueInt:
         lRet = UpdateInt((CdmValueInt*)p_pValue);
         break;
      case eDmValueLong:
         lRet = UpdateLong((CdmValueLong*)p_pValue);
         break;
      case eDmValueFloat:
         lRet = UpdateFloat((CdmValueFloat*)p_pValue);
         break;
      case eDmValueDouble:
         lRet = UpdateDouble((CdmValueDouble*)p_pValue);
         break;
      case eDmValueString:
         lRet = UpdateString((CdmValueString*)p_pValue);
         break;
      case eDmValueDate:
         lRet = UpdateDate((CdmValueDate*)p_pValue);
         break;
      case eDmValueTime:
         lRet = UpdateTime((CdmValueTime*)p_pValue);
         break;
      case eDmValueDateTime:
         lRet = UpdateDateTime((CdmValueDateTime*)p_pValue);
         break;
      case eDmValueObjectRef:
         lRet = UpdateObjectRef((CdmValueObjectRef*)p_pValue);
         break;
      case eDmValueContainerRef:
         lRet = UpdateContainerRef((CdmValueContainerRef*)p_pValue);
         break;
      case eDmValueCounter:
         lRet = UpdateCounter((CdmValueCounter*)p_pValue);
         break;
      case eDmValueBinaryDocument:
         lRet = UpdateBinaryDocument((CdmValueBinaryDocument*)p_pValue);

         if (lRet > 0)
         {
            CdbCommandUpdateBinaryDocument command((CdmValueBinaryDocument*)p_pValue, GetDataAccess());
            lRet = command.Run();
         }

         break;
      // Chardocs and derived documents from chardoc as xml
     case eDmValueCharacterDocument:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcCharDoc);
         break;
      case eDmValueListInt:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListInt);
         break;
      case eDmValueListDouble:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListDouble);
         break;
      case eDmValueListString:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListString);
         break;
      case eDmValueDictStringInt:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringInt);
         break;
      case eDmValueDictStringString:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringString);
         break;
      case eDmValueDictStringDouble:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictStringDouble);
         break;
      case eDmValueDictIntInt:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictIntInt);
         break;
      case eDmValueDictIntString:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcDictIntString);
         break;
      case eDmValueDictIntDouble:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eODbcDictIntDouble);
         break;
      case eDmValueListObjects:
         lRet = UpdateCharacterDocument((CdmValueCharacterDocument*)p_pValue,
                                        CdbDataAccess::eOdbcListObjects);
         break;
      case eDmValueUser:
         lRet = UpdateInt((CdmValueInt*)p_pValue);
         break;
      case eDmValueUserGroup:
         lRet = UpdateInt((CdmValueInt*)p_pValue);
         break;
      case eDmValueEnum:
         lRet = UpdateInt((CdmValueInt*)p_pValue);
         break;
      case eDmValueFormula:
         lRet = EC(eDmOk);
         break;
      default:
         lRet = EC(eDmUnknownValueError);
         ERR("Invalid Value for writing to object list!!!");
         break;
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   if (lRet < 0)
   {
       ERR("Failed to store Value. Keyname: " + p_pValue->GetKeyname() + " Errorcode:" + QString::number(lRet));
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertValue(CdmValue* p_pValue,
                                           CdbDataAccess::EodbcBaseType p_eOdbcBaseType)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if( CHKPTR(p_pValue))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      qstrQuery = QString("delete from WMS_VALUE where MemberId = %1 and ObjectId = %2")
                     .arg(p_pValue->GetMemberId())
                     .arg(m_rpObject->GetId());

      lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

      if(lRet > 0)
      {

         // query for reading new id
         qstrQuery = QString("Insert into WMS_VALUE (MemberId, BaseType, ObjectId, ContainerId, LastChange, CreatorId, ModifierId)"
                           "values(%1, %2, %3, %4, %5, %6, %7)")
                           .arg(p_pValue->GetMemberId())
                           .arg(p_eOdbcBaseType)
                           .arg(m_rpObject->GetId())
                            .arg(m_rpObject->GetObjectContainerId())
                           .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                           .arg(p_pValue->GetCreatorId())
                           .arg(p_pValue->GetModifierId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet > 0)
         {
            qstrQuery = QString("select max(ValueId) from WMS_VALUE where MemberId = %1 and ObjectId = %2 and BaseType = %3")
                                .arg(p_pValue->GetMemberId())
                                .arg(m_rpObject->GetId())
                                .arg(p_eOdbcBaseType);

            lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

            if(lRet > 0)
            {
               cQSqlQuery.first();
               if(cQSqlQuery.isValid())
               {
                 qint64 lValueId = cQSqlQuery.value(0).toInt();
                  CdmDataAccessHelper::SetId(p_pValue, lValueId);

                  CdbJournal* pJournal = GetDataAccess()->GetJournal();

                  if (pJournal)
                  {
                     pJournal->ValueModified(p_pValue);
                  }
               }
               else
               {
                  lRet = EC(eDmNoNewIdCreated);
                  ERR("Inserted object not found or more than one object found!!");
               }
            }
            else
            {
               lRet = EC(eDmNoNewIdCreated);
               ERR("Inserted object not found!!");
            }
         }
         else
         {
            lRet = EC(eDmInsertvalueBaseDataFailed);
            ERR("Error occured while writing base data for Value");
         }
      }
      else
      {
         lRet = EC(eDmInsertvalueBaseDataFailed);
         ERR("Error occured while deleting base data for Value");
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateValueTable(CdmValue* p_pValue)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pValue))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;
      // query for reading new id
      qstrQuery = QString("update WMS_VALUE set LastChange = %1, ModifierId = %2"
                          " where ValueId = %3")
                          .arg(CwmsUtilities::ChangeDateToString(QDateTime::currentDateTime()))
                          .arg(p_pValue->GetModifierId())
                          .arg(p_pValue->GetId());

      lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

      if(lRet < 0)
      {
         lRet = EC(eDmInvalidUpdateStatement);
         ERR("Value Update not possible!!");
      }
      else
      {
         CdbJournal* pJournal = GetDataAccess()->GetJournal();

         if (pJournal)
         {
            pJournal->ValueModified(p_pValue);
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertBool(CdmValueBool* p_pCdmBool)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmBool))
   {
      lRet = InsertValue(p_pCdmBool, CdbDataAccess::eOdbcBool);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         if(p_pCdmBool->GetValue())
         {
            qstrQuery = QString("Insert into WMS_VALUE_BOOL (BoolId, Val) values(%1, true)")
                             .arg(p_pCdmBool->GetId());
         }
         else
         {
            qstrQuery = QString("Insert into WMS_VALUE_BOOL (BoolId, Val) values(%1, false)")
                           .arg(p_pCdmBool->GetId());

         }

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Bool!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateBool(CdmValueBool* p_pCdmBool)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmBool))
   {
      lRet = UpdateValueTable(p_pCdmBool);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         if(p_pCdmBool->GetValue())
         {
            qstrQuery = QString("update WMS_VALUE_BOOL set Val = true where BoolId = %1")
                              .arg(p_pCdmBool->GetId());
         }
         else
         {
            qstrQuery = QString("update WMS_VALUE_BOOL set Val = false where BoolId = %1")
                              .arg(p_pCdmBool->GetId());
         }

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Bool!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertInt(CdmValueInt* p_pCdmInt, CdbDataAccess::EodbcBaseType  p_eOdbcType)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmInt))
   {
      lRet = InsertValue(p_pCdmInt, p_eOdbcType);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_INT (IntId, Val) values(%1, %2)")
                           .arg(p_pCdmInt->GetId())
                           .arg(p_pCdmInt->GetValue());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Int!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateInt(CdmValueInt* p_pCdmInt)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmInt))
   {
      lRet = UpdateValueTable(p_pCdmInt);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_INT set Val = %1 where IntId = %2")
                             .arg(p_pCdmInt->GetValue())
                             .arg(p_pCdmInt->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Int!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertLong(CdmValueLong* p_pCdmLong)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmLong))
   {
      lRet = InsertValue(p_pCdmLong, CdbDataAccess::eOdbcLong);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_LONG (LongId, Val) values(%1, %2)")
                           .arg(p_pCdmLong->GetId())
                           .arg(p_pCdmLong->GetValue());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for qint64!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateLong(CdmValueLong* p_pCdmLong)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmLong))
   {
      lRet = UpdateValueTable(p_pCdmLong);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_LONG set Val = %1 where LongId = %2")
                           .arg(p_pCdmLong->GetValue())
                           .arg(p_pCdmLong->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for qint64!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertFloat(CdmValueFloat* p_pCdmFloat)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmFloat))
   {
      lRet = InsertValue(p_pCdmFloat, CdbDataAccess::eOdbcFloat);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_FLOAT (FloatId, Val) values(%1, %2)")
                           .arg(p_pCdmFloat->GetId())
                           .arg(p_pCdmFloat->GetValue(), 0, 'f', 7);

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Float!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateFloat(CdmValueFloat* p_pCdmFloat)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmFloat))
   {
      lRet = UpdateValueTable(p_pCdmFloat);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_FLOAT set Val = %1 where FloatId = %2")
                           .arg(p_pCdmFloat->GetValue(), 0, 'f', 7)
                           .arg(p_pCdmFloat->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Float!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertDouble(CdmValueDouble* p_pCdmDouble)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDouble))
   {
      lRet = InsertValue(p_pCdmDouble, CdbDataAccess::eOdbcDouble);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_DOUBLE (DoubleId, Val) values(%1, %2)")
                           .arg(p_pCdmDouble->GetId())
                           .arg(p_pCdmDouble->GetValue(), 0, 'f', 16);

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Double!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateDouble(CdmValueDouble* p_pCdmDouble)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDouble))
   {
      lRet = UpdateValueTable(p_pCdmDouble);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_DOUBLE set Val = %1 where DoubleId = %2")
                           .arg(p_pCdmDouble->GetValue(), 0, 'f', 16)
                           .arg(p_pCdmDouble->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Double!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertString(CdmValueString* p_pCdmString)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmString))
   {
      lRet = InsertValue(p_pCdmString, CdbDataAccess::eOdbcString);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());

         QString qstrValue = p_pCdmString->GetValue();

         cQSqlQuery.prepare("insert into WMS_VALUE_STRING (StringId, Val) values(:id, :val)");
         cQSqlQuery.bindValue(":val", qstrValue);
         cQSqlQuery.bindValue(":id", p_pCdmString->GetId());

         lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for String!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateString(CdmValueString* p_pCdmString)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmString))
   {
      lRet = UpdateValueTable(p_pCdmString);
      if(lRet > 0)
      {
         QString qstrValue = p_pCdmString->GetValue().mid(0,1000);
         QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());


         cQSqlQuery.prepare("update WMS_VALUE_STRING set Val = :val where StringId = :id");
         cQSqlQuery.bindValue(":val", qstrValue);
         cQSqlQuery.bindValue(":id", p_pCdmString->GetId());



         lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for String!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertDate(CdmValueDate* p_pCdmDate)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDate))
   {
      lRet = InsertValue(p_pCdmDate, CdbDataAccess::eOdbcDate);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_DATE (DateId, Val) values(%1, %2)")
                           .arg(p_pCdmDate->GetId())
                           .arg(CwmsUtilities::ChangeDateToString(p_pCdmDate->GetValue()));

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Date!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateDate(CdmValueDate* p_pCdmDate)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDate))
   {
      lRet = UpdateValueTable(p_pCdmDate);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_DATE set Val = %1 where DateId = %2")
                           .arg(CwmsUtilities::ChangeDateToString(p_pCdmDate->GetValue()))
                           .arg(p_pCdmDate->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Date!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertTime(CdmValueTime* p_pCdmTime)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmTime))
   {
      lRet = InsertValue(p_pCdmTime, CdbDataAccess::eOdbcTime);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         QTime qTime = p_pCdmTime->GetValue();

         if (!qTime.isValid())
         {
            qTime = QTime::currentTime();
         }


         qstrQuery = QString("insert into WMS_VALUE_TIME (TimeId, Val) values(%1, '%2')")
                             .arg(p_pCdmTime->GetId())
                             .arg(qTime.toString(Qt::ISODate));

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Time!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateTime(CdmValueTime* p_pCdmTime)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmTime))
   {
      lRet = UpdateValueTable(p_pCdmTime);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         QTime qTime = p_pCdmTime->GetValue();

         if (!qTime.isValid())
         {
            qTime = QTime(0,0,0,0);
         }

         qstrQuery = QString("update WMS_VALUE_TIME set Val = '%1' where TimeId = %2")
                           .arg(p_pCdmTime->GetValue().toString(Qt::ISODate))
                           .arg(p_pCdmTime->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Time!!");
         }

      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertDateTime(CdmValueDateTime* p_pCdmDateTime)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDateTime))
   {
      lRet = InsertValue(p_pCdmDateTime, CdbDataAccess::eOdbcDateTime);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         QDateTime qdtDateTime = p_pCdmDateTime->GetValue();
         QString qstrValue = CwmsUtilities::ChangeDateToString(qdtDateTime);

         qstrQuery = QString("insert into WMS_VALUE_DATETIME (DateTimeId, Val) values(%1, %2)")
                           .arg(p_pCdmDateTime->GetId())
                           .arg(qstrValue);

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for DateTime!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateDateTime(CdmValueDateTime* p_pCdmDateTime)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmDateTime))
   {
      lRet = UpdateValueTable(p_pCdmDateTime);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         QDateTime qdtDateTime = p_pCdmDateTime->GetValue();
         QString qstrValue = CwmsUtilities::ChangeDateToString(qdtDateTime);

         qstrQuery = QString("update WMS_VALUE_DATETIME set Val = %1 where DateTimeId = %2")
                           .arg(qstrValue)
                           .arg(p_pCdmDateTime->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for DateTime!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertObjectRef(CdmValueObjectRef* p_pCdmObjectRef)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmObjectRef))
   {
      lRet = InsertValue(p_pCdmObjectRef, CdbDataAccess::eOdbcObjRef);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_OBJECTREFERENCE (ObjectReferenceId, ClassId, ObjectListId, ObjectId)"
                             " values(%1, %2, %3, %4)")
                             .arg(p_pCdmObjectRef->GetId())
                             .arg(p_pCdmObjectRef->GetClassId())
                             .arg(p_pCdmObjectRef->GetObjectListId())
                             .arg(p_pCdmObjectRef->GetValue());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Object Reference!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateObjectRef(CdmValueObjectRef* p_pCdmObjectRef)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmObjectRef))
   {
      lRet = UpdateValueTable(p_pCdmObjectRef);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_OBJECTREFERENCE set ClassId = %1, ObjectListId = %2, ObjectId = %3 where ObjectReferenceId = %4")
                             .arg(p_pCdmObjectRef->GetClassId())
                             .arg(p_pCdmObjectRef->GetObjectListId())
                             .arg(p_pCdmObjectRef->GetValue())
                             .arg(p_pCdmObjectRef->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            ERR("Update not possible for Object Reference!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertContainerRef(CdmValueContainerRef* p_pContainerRef)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pContainerRef))
   {
      lRet = InsertValue(p_pContainerRef, CdbDataAccess::eOdbcObjListRef);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("insert into WMS_VALUE_OBJECTLISTREFERENCE (ObjectListReferenceId, ClassId, ObjectListId)"
                             "values(%1, %2, %3)")
                             .arg(p_pContainerRef->GetId())
                             .arg(p_pContainerRef->GetClassId())
                             .arg(p_pContainerRef->GetValue());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for ObjectListReference!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateContainerRef(CdmValueContainerRef* p_pContainerRef)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pContainerRef))
   {
      lRet = UpdateValueTable(p_pContainerRef);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_OBJECTLISTREFERENCE set ClassId = %1, ObjectListId= %2 where ObjectListReferenceId = %3")
                             .arg(p_pContainerRef->GetClassId())
                             .arg(p_pContainerRef->GetValue())
                             .arg(p_pContainerRef->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Object List Reference!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertCounter(CdmValueCounter* p_pCdmCounter)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmCounter))
   {
      lRet = InsertValue(p_pCdmCounter, CdbDataAccess::eOdbcCounter);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;
         GetCounterValue(p_pCdmCounter);

         qstrQuery = QString("insert into WMS_VALUE_COUNTER (CounterId, Val) values(%1, %2)")
                           .arg(p_pCdmCounter->GetId())
                           .arg(p_pCdmCounter->GetValue());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Counter!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

void CdbCommandUpdateObject::GetCounterValue(CdmValueCounter* p_pCdmCounter)
{
    CdbCommandGetCounterValue cCommand(p_pCdmCounter, GetDataAccess());
    cCommand.Run();
}

qint64 CdbCommandUpdateObject::UpdateCounter(CdmValueCounter* p_pCdmCounter)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmCounter))
   {
      lRet = UpdateValueTable(p_pCdmCounter);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         qstrQuery = QString("update WMS_VALUE_COUNTER set Val = %1 where CounterId = %2")
                             .arg(p_pCdmCounter->GetValue())
                             .arg(p_pCdmCounter->GetId());

         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Counter!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmBinaryDocument))
   {
      if(InsertValue(p_pCdmBinaryDocument, CdbDataAccess::eOdbcBinDoc) > 0)
      {
         QSqlQuery cQSqlQuery;
         QString qstrQuery;

         QString qstrFilename = ShortFilename(p_pCdmBinaryDocument->GetFilename());
         QString qstrFileType = p_pCdmBinaryDocument->GetFileType();
         qstrFileType = qstrFileType.replace("'", "");

         qstrQuery = QString("insert into WMS_VALUE_BINARYDOCUMENT (BinaryDocumentId, Type, Filename) values(%1, '%2', '%3')")
                           .arg(p_pCdmBinaryDocument->GetId())
                           .arg(qstrFileType)
                           .arg(qstrFilename.mid(0, 32));


         lRet = GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery);

         if(lRet < 0)
         {
            ERR("Insert not possible for Binary Document!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

QString CdbCommandUpdateObject::ShortFilename(QString p_qstrFilename)
{
   QString qstrFilename;

   BODY_TRY
   if (p_qstrFilename.length() > 32)
   {
      QFileInfo qfInfo(p_qstrFilename);
      QString qstrSuffix = qfInfo.completeSuffix();
      qstrFilename = qfInfo.baseName();
      qstrFilename = qstrFilename.left(31 - qstrSuffix.length());
      qstrFilename += QStringLiteral(".") + qstrSuffix;
   }
   else
   {
      qstrFilename = p_qstrFilename;
   }
   BODY_CATCH

   return qstrFilename;
}

qint64 CdbCommandUpdateObject::UpdateBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   BODY_TRY
   if (CHKPTR(p_pCdmBinaryDocument))
   {
      CdbDataAccess* pCdbDataAccess = GetDataAccess();

      if (CHKPTR(pCdbDataAccess))
      {
          lRet = UpdateValueTable(p_pCdmBinaryDocument);

          if (lRet > 0)
          {
             QSqlQuery cQSqlQuery;
             QString qstrQuery;
             QString qstrFilename = ShortFilename(p_pCdmBinaryDocument->GetFilename());

             qstrQuery = QString("update WMS_VALUE_BINARYDOCUMENT set Type = '%1', Filename = '%2' where BinaryDocumentId = %3")
                                 .arg(p_pCdmBinaryDocument->GetFileType())
                                 .arg(qstrFilename)
                                 .arg(p_pCdmBinaryDocument->GetId());

             lRet = pCdbDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);

             if (lRet < 0)
             {
                lRet = EC(eDmInvalidUpdateStatement);
                ERR("Update not possible for Binary Documents!!")
             }
          }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }
   BODY_CATCH

   return lRet;
}

qint64 CdbCommandUpdateObject::InsertCharacterDocument(CdmValueCharacterDocument* p_pCdmCharacterDocument,
                                                     CdbDataAccess::EodbcBaseType p_eType)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(p_pCdmCharacterDocument))
   {
      lRet = InsertValue(p_pCdmCharacterDocument, p_eType);
      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());
         QString qstrQuery;

         QString qstrValue = p_pCdmCharacterDocument->GetValue();

         cQSqlQuery.prepare("insert into WMS_VALUE_CHARACTERDOCUMENT (CharacterDocumentId, Val) values(:id, :val)");
         cQSqlQuery.bindValue(":val", qstrValue);
         cQSqlQuery.bindValue(":id", p_pCdmCharacterDocument->GetId());

         lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidInsertStatement);
            ERR("Insert not possible for Character Document!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }


   return lRet;
}

qint64 CdbCommandUpdateObject::UpdateCharacterDocument(CdmValueCharacterDocument* p_pCdmCharacterDocument,
                                              CdbDataAccess::EodbcBaseType p_eType)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   Q_UNUSED(p_eType);

   if(CHKPTR(p_pCdmCharacterDocument))
   {
      lRet = UpdateValueTable(p_pCdmCharacterDocument);

      if(lRet > 0)
      {
         QSqlQuery cQSqlQuery(GetDataAccess()->GetDbInterface()->GetSqlDatabase());
         QString qstrQuery;

         QString qstrValue = p_pCdmCharacterDocument->GetValue();

         cQSqlQuery.prepare("update WMS_VALUE_CHARACTERDOCUMENT set Val = :val where CharacterDocumentId = :id");
         cQSqlQuery.bindValue(":val", qstrValue.toLatin1());
         cQSqlQuery.bindValue(":id", p_pCdmCharacterDocument->GetId());

         lRet = GetDataAccess()->ExecuteQuery(cQSqlQuery);

         if(lRet < 0)
         {
            lRet = EC(eDmInvalidUpdateStatement);
            ERR("Update not possible for Character Document!!");
         }
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}
