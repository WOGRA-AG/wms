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

// Own Includes
#include "CwmsUtilities.h"
#include "CdbCommandLoadSingleObject.h"

CdbCommandLoadSingleObject::CdbCommandLoadSingleObject(long p_lContainerId, long p_lObjectId, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_lContainerId(p_lContainerId),
  m_lObjectId(p_lObjectId),
  m_rpObject(nullptr)
{
}

CdbCommandLoadSingleObject::CdbCommandLoadSingleObject(long p_lContainerId, QString p_qstrKeyname, CdbDataAccess *p_pDataAccess)
    : CdbAbstractCommand(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_lObjectId(-1),
      m_qstrKeyname(p_qstrKeyname),
      m_rpObject(nullptr){

}

CdbCommandLoadSingleObject::~CdbCommandLoadSingleObject()
{

}

CdmObject *CdbCommandLoadSingleObject::GetResult()
{
    return m_rpObject;
}

bool CdbCommandLoadSingleObject::CheckValid()
{
    return (m_lContainerId > 0 && (m_lObjectId > 0 || !m_qstrKeyname.isEmpty()));
}

QString CdbCommandLoadSingleObject::GenerateDbQuery()
{
    QString qstrQuery;
    // query for finding Object

    if (m_lObjectId >= 0)
    {
    qstrQuery = QString("Select obj.ObjectId, obj.Keyname, obj.LastChange, "
                        "obj.CreatorId, obj.ModifierId, obj.Caption, "
                        "cl.ClassId, cl.DatabaseId, obj.Cache, obj.Parent, obj.config "
                        "from WMS_DM_OBJECT obj, WMS_DM_OBJECTLIST ol, WMS_CLASS cl "
                        "where obj.ObjectId = %1 and obj.ObjectListId = ol.ObjectListId and "
                        "ol.ClassId = cl.ClassId")
                        .arg(m_lObjectId);
    }
    else
    {
        qstrQuery = QString("Select obj.ObjectId, obj.Keyname, obj.LastChange, "
                            "obj.CreatorId, obj.ModifierId, obj.Caption, "
                            "cl.ClassId, cl.DatabaseId, obj.Cache, obj.Parent, obj.config "
                            "from WMS_DM_OBJECT obj, WMS_DM_OBJECTLIST ol, WMS_CLASS cl "
                            "where obj.Keyname = '%1' and obj.ObjectListId = ol.ObjectListId and "
                            "ol.ClassId = cl.ClassId")
                            .arg(m_qstrKeyname);
    }

    return qstrQuery;
}

int CdbCommandLoadSingleObject::Execute()
{
   long lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery = GenerateDbQuery();

   if(m_rpObject)
   {
      ERR("Object must be null");
   }

   // Execute Query
   if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
   {
      cQSqlQuery.first();
      if(cQSqlQuery.isValid())
      {

         long lObjectId       = cQSqlQuery.value(0).toInt();
         QString qstrKeyname  = cQSqlQuery.value(1).toString();
         QDateTime qdtLastChange   = cQSqlQuery.value(2).toDateTime();
         long lCreatorId      = cQSqlQuery.value(3).toInt();
         long lLastModifierId = cQSqlQuery.value(4).toInt();
         QString qstrCaption  = cQSqlQuery.value(5).toString();
         long lClassId        = cQSqlQuery.value(6).toInt();
         long lSchemeId = cQSqlQuery.value(7).toInt();
         QString qstrCache = cQSqlQuery.value(8).toString();
         long lParentId = cQSqlQuery.value(9).toInt();
         QString qstrConfig = cQSqlQuery.value(10).toString();

         m_rpObject = CdmDataAccessHelper::CreateObject(lSchemeId,
                                                        lObjectId,
                                                        lClassId,
                                                        m_lContainerId);

         m_rpObject->SetCaption(qstrCaption);
         m_rpObject->SetParent(lParentId);
         CdmDataAccessHelper::SetKeyname(m_rpObject, qstrKeyname);
         CdmDataAccessHelper::SetCreatorId(m_rpObject, lCreatorId);
         CdmDataAccessHelper::SetModifierId(m_rpObject, lLastModifierId);

         ReadValues();
         CdmDataAccessHelper::SetValid(m_rpObject);
         m_rpObject->SetConfig(qstrConfig);
         m_rpObject->SetLastChange(qdtLastChange);
         m_rpObject->ResetNewModified();

         INFO("Object with Id " + QString::number(lObjectId) + " found");

         lRet = EC(eDmTrue);
      }
      else
      {
         lRet = EC(eDmObjectNotFound);
         INFO("Object not found!");
      }
   }
   else
   {
      lRet = EC(eDmInvalidSelectStatement);
      ERR("Query execution failed!!!");
   }

   return static_cast<int>(lRet);
}

long CdbCommandLoadSingleObject::ReadValues()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;
      // query for reading new id
      qstrQuery = QString("Select BaseType from WMS_VALUE where ObjectId = %1")
                          .arg(m_rpObject->GetId());

      // reads the basetypes of the objectlists
      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         long lRet = CdmLogging::eDmOk;
         QList<long> qvlBaseTypes;
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // finding out which type of values are in this object
            {
               long lBaseType = cQSqlQuery.value(0).toInt();
               qvlBaseTypes.append(lBaseType);
            }
            while(cQSqlQuery.next());
         }


         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcBinDoc))
         {
            lRet = ReadBinaryDocuments();
         }


         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcBool) && lRet > 0)
         {
            lRet = ReadBools();
         }


         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcCharDoc) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcCharDoc);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcListInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcListDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcListString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcDictStringInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcDictStringString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcDictStringDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictIntInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcDictIntInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictIntString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcDictIntString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eODbcDictIntDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eODbcDictIntDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListObjects) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(CdbDataAccess::eOdbcListObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcCounter) && lRet > 0)
         {
            lRet = ReadCounters();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDate) && lRet > 0)
         {
            lRet = ReadDates();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDateTime) && lRet > 0)
         {
            lRet = ReadDateTimes();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDouble) && lRet > 0)
         {
            lRet = ReadDoubles();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcFloat) && lRet > 0)
         {
            lRet = ReadFloats();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcInt) && lRet > 0)
         {
            lRet = ReadInts(CdbDataAccess::eOdbcInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcUser) && lRet > 0)
         {
            lRet = ReadInts(CdbDataAccess::eOdbcUser);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcUserGroup) && lRet > 0)
         {
            lRet = ReadInts(CdbDataAccess::eOdbcUserGroup);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcEnum) && lRet > 0)
         {
            lRet = ReadInts(CdbDataAccess::eOdbcEnum);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcLong) && lRet > 0)
         {
            lRet = ReadLongs();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcObjRef) && lRet > 0)
         {
            lRet = ReadObjectRefs();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcObjListRef) && lRet > 0)
         {
            lRet = ReadObjectListRefs();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcString) && lRet > 0)
         {
            lRet = ReadStrings();
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcTime) && lRet > 0)
         {
            lRet = ReadTimes();
         }
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
         ERR("Execute Query failed!!");
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadBinaryDocuments()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading binary document values for one object
      qstrQuery = QString("select val.ValueId, bd.Type, bd.FileName, val.MemberId, val.LastChange, "
                          "val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption "
                          "from WMS_VALUE_BINARYDOCUMENT bd, WMS_VALUE val, WMS_CLASS_MEMBER mem  "
                          "where bd.BinaryDocumentId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcBinDoc);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QString   qstrType           = cQSqlQuery.value(1).toString();
               QString   qstrFilename       = cQSqlQuery.value(2).toString();
               long      lMemberId          = cQSqlQuery.value(3).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(4).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(5).toInt();
               long      lModifierId        = cQSqlQuery.value(6).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(7).toString();
               QString   qstrCaption        = cQSqlQuery.value(8).toString();

               if (CheckType(lMemberId, eDmValueBinaryDocument))
               {
                   CdmValueBinaryDocument* pCdmBinaryDocument = new CdmValueBinaryDocument(m_rpObject->GetSchemeId(),
                                                                                 lId,
                                                                                 qstrKeyname,
                                                                                 qstrFilename,
                                                                                 qstrType,
                                                                                 m_rpObject);

                   pCdmBinaryDocument->SetMemberId(lMemberId);
                   pCdmBinaryDocument->SetCaption(qstrCaption);
                   CdmDataAccessHelper::SetCreatorId(pCdmBinaryDocument, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmBinaryDocument, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmBinaryDocument);
                   pCdmBinaryDocument->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadBools()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading bool values for one object
      qstrQuery = QString("select val.ValueId, bo.Val, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_BOOL bo, WMS_VALUE val, WMS_CLASS_MEMBER mem  where bo.BoolId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcBool);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // reading each bool
            {
               long     lId                = cQSqlQuery.value(0).toInt();
               bool     bValue             = cQSqlQuery.value(1).toBool();
               long     lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange     = cQSqlQuery.value(3).toDateTime();
               long     lCreatorId         = cQSqlQuery.value(4).toInt();
               long     lModifierId        = cQSqlQuery.value(5).toInt();
               QString  qstrKeyname        = cQSqlQuery.value(6).toString();
               QString  qstrCaption        = cQSqlQuery.value(7).toString();

               if (FindMember(lMemberId))
               {
                   CdmValueBool* pCdmBool = new CdmValueBool(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmBool->SetMemberId(lMemberId);
                   pCdmBool->SetCaption(qstrCaption);
                   pCdmBool->SetValue(bValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmBool, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmBool, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmBool);
                   pCdmBool->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
         ERR("Execute Query failed!!!");
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadCharacterDocuments(CdbDataAccess::EodbcBaseType p_eType)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading new id
      qstrQuery = QString("select dt.ValueId, cd.Val, dt.MemberId, dt.LastChange, dt.CreatorId, "
                          "dt.ModifierId, mem.Keyname, mem.Caption "
                          "from WMS_VALUE_CHARACTERDOCUMENT cd, WMS_VALUE dt, WMS_CLASS_MEMBER mem "
                          "where cd.CharacterDocumentId = dt.Valueid and "
                          "dt.MemberId = mem.MemberId and dt.ObjectId= %1 and dt.BaseType = %2")
                        .arg(m_rpObject->GetId())
                        .arg(p_eType);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QString   qstrValue          = cQSqlQuery.value(1).toString();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               // more than one type is read here checkmember cannot be used
               if (FindMember(lMemberId))
               {
                   CdmValueCharacterDocument* pCdmCharacterDocument = CreateCharDocValue(p_eType,
                                                                                    m_rpObject->GetSchemeId(),
                                                                                    lId,
                                                                                    qstrKeyname);
                   pCdmCharacterDocument->SetMemberId(lMemberId);
                   pCdmCharacterDocument->SetCaption(qstrCaption);
                   pCdmCharacterDocument->SetValue(qstrValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmCharacterDocument, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmCharacterDocument, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmCharacterDocument);
                   pCdmCharacterDocument->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadCounters()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading counter values for one object
      qstrQuery = QString("select val.ValueId, co.Val, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_COUNTER co, WMS_VALUE val, WMS_CLASS_MEMBER mem  where co.CounterId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcCounter);


      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // reading each counter
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               long      lValue             = cQSqlQuery.value(1).toInt();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueCounter))
               {
                   CdmValueCounter* pCdmCounter = new CdmValueCounter(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmCounter->SetMemberId(lMemberId);
                   pCdmCounter->SetCaption(qstrCaption);
                   (dynamic_cast<CdmValueLong*>(pCdmCounter))->SetValue(lValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmCounter, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmCounter, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmCounter);
                   pCdmCounter->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadDates()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading date values for one object
      qstrQuery = QString("select val.ValueId, da.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_DATE da, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where da.DateId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcDate);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QDate     qdValue            = cQSqlQuery.value(1).toDate();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueDate))
               {
                   CdmValueDate* pCdmDate = new CdmValueDate(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmDate->SetMemberId(lMemberId);
                   pCdmDate->SetCaption(qstrCaption);
                   pCdmDate->SetValue(qdValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmDate, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmDate, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmDate);
                   pCdmDate->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }

            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadDateTimes()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading datetime values for one object
      qstrQuery = QString("select val.ValueId, dt.Val, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_DATETIME dt, WMS_VALUE val, WMS_CLASS_MEMBER mem  where dt.DateTimeId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcDateTime);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QDateTime qdtValue           = cQSqlQuery.value(1).toDateTime();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueDateTime))
               {
                   CdmValueDateTime* pCdmDateTime = new CdmValueDateTime(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmDateTime->SetMemberId(lMemberId);
                   pCdmDateTime->SetCaption(qstrCaption);
                   pCdmDateTime->SetValue(qdtValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmDateTime, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmDateTime, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmDateTime);
                   pCdmDateTime->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadDoubles()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, dou.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_DOUBLE dou, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where dou.DoubleId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcDouble);



      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               double    dValue             = cQSqlQuery.value(1).toDouble();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueDouble))
               {
                   CdmValueDouble* pCdmDouble = new CdmValueDouble(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmDouble->SetMemberId(lMemberId);
                   pCdmDouble->SetCaption(qstrCaption);
                   pCdmDouble->SetValue(dValue);
                   pCdmDouble->SetLastChange(qdtLastChange);
                   CdmDataAccessHelper::SetCreatorId(pCdmDouble, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmDouble, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmDouble);
                   pCdmDouble->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadFloats()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, fl.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_FLOAT fl, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where fl.FloatId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcFloat);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // reading each float
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               float     fValue             = cQSqlQuery.value(1).toFloat();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueFloat))
               {
                   CdmValueFloat* pCdmFloat = new CdmValueFloat(m_rpObject->GetSchemeId(), lId,
                                                                qstrKeyname, m_rpObject);
                   pCdmFloat->SetMemberId(lMemberId);
                   pCdmFloat->SetCaption(qstrCaption);
                   pCdmFloat->SetValue(fValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmFloat, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmFloat, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmFloat);
                   pCdmFloat->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadInts(CdbDataAccess::EodbcBaseType  p_eOdbcType)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading int values for one object
      qstrQuery = QString("select val.ValueId, valint.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_INT valint, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where valint.IntId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(p_eOdbcType);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // reading each int
            {
               long     lId                = cQSqlQuery.value(0).toInt();
               int      iValue             = cQSqlQuery.value(1).toInt();
               long     lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange     = cQSqlQuery.value(3).toDateTime();
               long     lCreatorId         = cQSqlQuery.value(4).toInt();
               long     lModifierId        = cQSqlQuery.value(5).toInt();
               QString  qstrKeyname        = cQSqlQuery.value(6).toString();
               QString  qstrCaption        = cQSqlQuery.value(7).toString();

               // more than one type is read here CheckType cannont be used
               if (FindMember(lMemberId))
               {
                   CdmValueInt* pCdmInt = nullptr;

                   if (p_eOdbcType == CdbDataAccess::eOdbcInt)
                   {
                      pCdmInt = new CdmValueInt(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   }
                   else if (p_eOdbcType == CdbDataAccess::eOdbcUser)
                   {
                      pCdmInt = new CdmValueUser(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   }
                   else if (p_eOdbcType == CdbDataAccess::eOdbcUserGroup)
                   {
                      pCdmInt = new CdmValueUserGroup(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   }
                   else if (p_eOdbcType == CdbDataAccess::eOdbcEnum)
                   {
                      pCdmInt = new CdmValueEnum(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   }

                   pCdmInt->SetMemberId(lMemberId);
                   pCdmInt->SetCaption(qstrCaption);
                   pCdmInt->SetValue(iValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmInt, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmInt, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmInt);
                   pCdmInt->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadLongs()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, long1.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_LONG long1, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where long1.LongId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcLong);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // reading each long
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               long      lValue             = cQSqlQuery.value(1).toInt();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();


               if (CheckType(lMemberId, eDmValueLong))
               {
                   CdmValueLong* pCdmLong = new CdmValueLong(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmLong->SetMemberId(lMemberId);
                   pCdmLong->SetCaption(qstrCaption);
                   pCdmLong->SetValue(lValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmLong, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmLong, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmLong);
                   pCdmLong->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }

            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadObjectRefs()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading objectreference values for one object
      qstrQuery = QString("SELECT val.ValueId, oref.ClassId, oref.ObjectListId, oref.ObjectId, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption, obj.Keyname, objlist.Keyname "
                          "FROM WMS_VALUE_OBJECTREFERENCE oref "
                          "INNER JOIN WMS_VALUE val ON oref.ObjectReferenceId = val.ValueId "
                          "INNER JOIN WMS_CLASS_MEMBER mem ON val.MemberId = mem.MemberId "
                          "LEFT JOIN WMS_DM_OBJECT obj ON obj.ObjectId = oref.ObjectId "
                          "LEFT JOIN WMS_DM_OBJECTLIST objlist ON objlist.ObjectListId = oref.ObjectListId "
                          "WHERE val.ObjectId = %1 AND val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcObjRef);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // reading each objectreference
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               long      lObjectListId      = cQSqlQuery.value(2).toInt();
               long      lValue             = cQSqlQuery.value(3).toInt();
               long      lMemberId          = cQSqlQuery.value(4).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(5).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(6).toInt();
               long      lModifierId        = cQSqlQuery.value(7).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(8).toString();
               QString   qstrCaption        = cQSqlQuery.value(9).toString();
               QString   qstrObjectKeyname  = cQSqlQuery.value(10).toString();
               QString   qstrContainerKeyname = cQSqlQuery.value(11).toString();

               if (CheckType(lMemberId, eDmValueObjectRef))
               {
                   CdmValueObjectRef* pCdmObjectRef = new CdmValueObjectRef(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);

                   pCdmObjectRef->SetMemberId(lMemberId);
                   pCdmObjectRef->SetCaption(qstrCaption);
                   pCdmObjectRef->SetValue(lObjectListId, lValue, qstrObjectKeyname, qstrContainerKeyname);
                   CdmDataAccessHelper::SetCreatorId(pCdmObjectRef, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmObjectRef, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmObjectRef);
                   pCdmObjectRef->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadObjectListRefs()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading objectreference values for one object
      qstrQuery = QString("select val.ValueId, olr.classid, olr.ObjectListId, val.MemberId, "
                          "val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption "
                          "from WMS_VALUE_OBJECTLISTREFERENCE olr, WMS_VALUE val, WMS_CLASS_MEMBER mem "
                          "where olr.ObjectListReferenceId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcObjListRef);



      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // reading each objectlistreference
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               long      lValue             = cQSqlQuery.value(2).toInt();
               long      lMemberId          = cQSqlQuery.value(3).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(4).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(5).toInt();
               long      lModifierId        = cQSqlQuery.value(6).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(7).toString();
               QString   qstrCaption        = cQSqlQuery.value(8).toString();

               if (CheckType(lMemberId, eDmValueContainerRef))
               {
                   CdmValueContainerRef* pContainerRef = new CdmValueContainerRef(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pContainerRef->SetMemberId(lMemberId);
                   pContainerRef->SetCaption(qstrCaption);
                   pContainerRef->SetValue(lValue);
                   pContainerRef->ResetNewModified();
                   CdmDataAccessHelper::SetCreatorId(pContainerRef, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pContainerRef, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pContainerRef);
                   pContainerRef->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadStrings()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, str.Val, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_STRING str, WMS_VALUE val, WMS_CLASS_MEMBER mem  where str.StringId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcString);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // reading each string
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QString   qstrValue          = cQSqlQuery.value(1).toString();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueString))
               {
                   CdmValueString* pCdmString = new CdmValueString(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmString->SetMemberId(lMemberId);
                   pCdmString->SetCaption(qstrCaption);
                   pCdmString->SetValue(qstrValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmString, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmString, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmString);
                   pCdmString->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }

            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

long CdbCommandLoadSingleObject::ReadTimes()
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(CHKPTR(m_rpObject))
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading time values for one object
      qstrQuery = QString("select val.ValueId, ti.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption from WMS_VALUE_TIME ti, WMS_VALUE val, "
                          "WMS_CLASS_MEMBER mem  where ti.TimeId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId= %1 and val.BaseType = %2")
                          .arg(m_rpObject->GetId())
                          .arg(CdbDataAccess::eOdbcTime);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {
            do // reading each time value
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QTime     qtValue            = cQSqlQuery.value(1).toTime();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();

               if (CheckType(lMemberId, eDmValueTime))
               {
                   CdmValueTime* pCdmTime = new CdmValueTime(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
                   pCdmTime->SetMemberId(lMemberId);
                   pCdmTime->SetCaption(qstrCaption);
                   pCdmTime->SetValue(qtValue);
                   CdmDataAccessHelper::SetCreatorId(pCdmTime, lCreatorId);
                   CdmDataAccessHelper::SetModifierId(pCdmTime, lModifierId);
                   CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmTime);
                   pCdmTime->SetLastChange(qdtLastChange);
                   m_rpObject->ResetNewModified();
               }
            }
            while(cQSqlQuery.next());
         }

         lRet = EC(eDmOk);
      }
      else
      {
         lRet = EC(eDmInvalidSelectStatement);
      }
   }
   else
   {
      lRet = EC(eDmInvalidPtr);
   }

   return lRet;
}

const CdmMember* CdbCommandLoadSingleObject::FindMember(long p_lId)
{
    CdmClass* pClass = m_rpObject->GetClass();

    if (CHKPTR(pClass))
    {
        return pClass->FindMember(p_lId);
    }

    return nullptr;
}

bool CdbCommandLoadSingleObject::CheckType(long  p_lId, EdmValueType p_eNeeded)
{
    bool bRet = true;
    CdmClass* pClass = m_rpObject->GetClass();

    if (CHKPTR(pClass))
    {
        const CdmMember* pMember = pClass->FindMember(p_lId);

        if (!pMember ||
            pMember->GetValueType() != p_eNeeded)
        {
            if (!pMember)
            {
                WARNING("Try Loading Value of Keyname \"" + QString::number(p_lId) +
                        "\".\n The member does not exist anymore and the Value won't be created.");
            }
            else
            {
                WARNING("Try Loading Value of Keyname \"" + QString::number(p_lId) + "\".\n The expected type \"" +
                        pMember->GetValueTypeAsString() + "\" and the db type is \"" + CdmMember::GetValueTypeAsString(p_eNeeded) +
                        "\".\nValue won't be created.");
            }

            bRet = false;
        }
    }

    return bRet;
}

CdmValueCharacterDocument* CdbCommandLoadSingleObject::CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType,
                                                            long p_lDatabaseId,
                                                            long p_lId,
                                                            QString p_qstrKeyname)
{
   CdmValueCharacterDocument* pDocument = nullptr;

   switch (p_eType)
   {
   case CdbDataAccess::eOdbcCharDoc:
      pDocument = new CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcListInt:
      pDocument = new CdmValueListInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcListDouble:
      pDocument = new CdmValueListDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcListString:
      pDocument = new CdmValueListString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcDictStringInt:
      pDocument = new CdmValueDictStringInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcDictStringString:
      pDocument = new CdmValueDictStringString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcDictStringDouble:
      pDocument = new CdmValueDictStringDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcDictIntInt:
      pDocument = new CdmValueDictIntInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcDictIntString:
      pDocument = new CdmValueDictIntString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eODbcDictIntDouble:
      pDocument = new CdmValueDictIntDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   case CdbDataAccess::eOdbcListObjects:
      pDocument = new CdmValueListObjects(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
      break;
   default:
      ERR("Invalid Type");
      break;
   }

   return pDocument;
}

