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
#include "CdbCommandLoadObjects.h"

CdbCommandLoadObjects::CdbCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<long>& p_qlObjectIds, CdbDataAccess* p_pDataAccess)
: CdbAbstractCommand(p_pDataAccess),
  m_rpContainer(p_pContainer),
  m_qvlObjectIds(p_qlObjectIds)
{
}

CdbCommandLoadObjects::~CdbCommandLoadObjects()
{

}

bool CdbCommandLoadObjects::CheckValid()
{
    return (CHKPTR(m_rpContainer) && m_qvlObjectIds.count() > 0)    ;
}

int CdbCommandLoadObjects::Execute()
{
   long lRet = CdmLogging::eDmObjectAccessError;
   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   CdmObject* pCdmObject = nullptr;
   QString qstrObjectInString;
   QMap<long, CdmObject*> qmObjects;
   QMap<CdmObject*, QDateTime> qmLastChange;

   if (m_qvlObjectIds.count() > 0)
   {
      qstrObjectInString = GenerateInString(m_qvlObjectIds);

      qstrQuery = QString("Select obj.ObjectId, obj.Keyname, obj.LastChange, "
                          "obj.CreatorId, obj.ModifierId, obj.Caption, "
                          "cl.ClassId, cl.DatabaseId, obj.Cache, obj.Parent, obj.config "
                          "from WMS_DM_OBJECT obj, WMS_DM_OBJECTLIST ol, WMS_CLASS cl "
                          "where obj.ObjectId IN %1 and obj.ObjectListId = ol.ObjectListId and "
                          "ol.ClassId = cl.ClassId order by obj.ObjectId")
                          .arg(qstrObjectInString);

      // Execute Query
      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();

         while (cQSqlQuery.isValid())
         {

            long lObjectId       = cQSqlQuery.value(0).toInt();
            QString qstrKeyname  = cQSqlQuery.value(1).toString();
            QDateTime qdLastChange = cQSqlQuery.value(2).toDateTime();
            long lCreatorId      = cQSqlQuery.value(3).toInt();
            long lLastModifierId = cQSqlQuery.value(4).toInt();
            QString qstrCaption  = cQSqlQuery.value(5).toString();
            long lClassId        = cQSqlQuery.value(6).toInt();
            long lDataBaseId     = cQSqlQuery.value(7).toInt();
            QString qstrCache    = cQSqlQuery.value(8).toString();
            long lParent     = cQSqlQuery.value(9).toInt();
            QString qstrConfig    = cQSqlQuery.value(10).toString();

            pCdmObject = CdmDataAccessHelper::CreateObject(lDataBaseId,
                                       lObjectId,
                                       lClassId,
                                       m_rpContainer->GetId());

            INFO("Object with Id " + QString::number(pCdmObject->GetId()) + " created");

            pCdmObject->SetCaption(qstrCaption);
            pCdmObject->SetParent(lParent);
            CdmDataAccessHelper::SetKeyname(pCdmObject, qstrKeyname);
            CdmDataAccessHelper::SetCreatorId(pCdmObject, lCreatorId);
            CdmDataAccessHelper::SetModifierId(pCdmObject, lLastModifierId);
            CdmDataAccessHelper::SetValid(pCdmObject);
            INFO("Object still has Id " + QString::number(pCdmObject->GetId()));
            CdmDataAccessHelper::AddObjectToObjectList(pCdmObject, m_rpContainer);
            INFO("Object still has Id " + QString::number(pCdmObject->GetId()));
            pCdmObject->SetConfig(qstrConfig);
            pCdmObject->ResetNewModified();
            qmLastChange.insert(pCdmObject, qdLastChange);
            qmObjects.insert(pCdmObject->GetId(), pCdmObject);

            INFO("Object with Id " + QString::number(pCdmObject->GetId()) + " creation finished");

            lRet = EC(eDmTrue);
            cQSqlQuery.next();
         }

         ReadValues(qstrObjectInString, qmObjects);

         QMap<CdmObject*, QDateTime>::iterator qmIt = qmLastChange.begin();
         QMap<CdmObject*, QDateTime>::iterator qmItEnd = qmLastChange.end();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            CdmObject* pCdmObject = qmIt.key();

            if (CHKPTR(pCdmObject))
            {
               pCdmObject->ResetNewModified();
               pCdmObject->SetLastChange(qmIt.value());
            }
         }
      }
   }
   else
   {
      lRet = EC(eDmTrue);
      INFO("ObjectList is Empty");
   }

   return lRet;
}

QString CdbCommandLoadObjects::GenerateInString(QList<long>& p_rqvlIds)
{
   QString qstrRet = "(";

   QList<long>::iterator qvlIt = p_rqvlIds.begin();
   QList<long>::iterator qvlItEnd = p_rqvlIds.end();

   while (qvlIt != qvlItEnd)
   {
      QString qstrId = QString::number(*qvlIt);
      qstrRet += qstrId;

      ++ qvlIt;

      if (qvlIt != qvlItEnd)
      {
         qstrRet += ", ";
      }
      else
      {
         qstrRet += ")";
         break;
      }
   }

   return qstrRet;
}

long CdbCommandLoadObjects::ReadValues(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if(p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;
      // query for reading new id
      qstrQuery = QString("Select distinct BaseType from WMS_VALUE where ObjectId IN %1")
                          .arg(p_qstrInString);

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
            lRet = ReadBinaryDocuments(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcBool) && lRet > 0)
         {
            lRet = ReadBools(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcCharDoc) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcCharDoc);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcListInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcListDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcListString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcDictStringInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcDictStringString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictStringDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcDictStringDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictIntInt) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcDictIntInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDictIntString) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcDictIntString);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eODbcDictIntDouble) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eODbcDictIntDouble);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcListObjects) && lRet > 0)
         {
            lRet = ReadCharacterDocuments(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcListObjects);
         }

         // End of CharDoc derived types

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcCounter) && lRet > 0)
         {
            lRet = ReadCounters(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDate) && lRet > 0)
         {
            lRet = ReadDates(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDateTime) && lRet > 0)
         {
            lRet = ReadDateTimes(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcDouble) && lRet > 0)
         {
            lRet = ReadDoubles(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcFloat) && lRet > 0)
         {
            lRet = ReadFloats(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcInt) && lRet > 0)
         {
            lRet = ReadInts(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcInt);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcUser) && lRet > 0)
         {
            lRet = ReadInts(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcUser);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcLong) && lRet > 0)
         {
            lRet = ReadLongs(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcObjRef) && lRet > 0)
         {
            lRet = ReadObjectRefs(p_qstrInString, p_rqmObjects);
         }


         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcObjListRef) && lRet > 0)
         {
            lRet = ReadObjectListRefs(p_qstrInString, p_rqmObjects);
         }


         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcString) && lRet > 0)
         {
            lRet = ReadStrings(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcTime) && lRet > 0)
         {
            lRet = ReadTimes(p_qstrInString, p_rqmObjects);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcUserGroup) && lRet > 0)
         {
            lRet = ReadInts(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcUserGroup);
         }

         if(qvlBaseTypes.contains(CdbDataAccess::eOdbcEnum) && lRet > 0)
         {
            lRet = ReadInts(p_qstrInString, p_rqmObjects, CdbDataAccess::eOdbcEnum);
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

int CdbCommandLoadObjects::ReadBinaryDocuments(QString p_qstrInString,
                                           QMap<long,
                                           CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading binary document values for one object
      qstrQuery = QString("select val.ValueId, bd.Type, bd.FileName, val.MemberId, val.LastChange, "
                          "val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption, val.objectid from "
                          "WMS_VALUE_BINARYDOCUMENT bd, WMS_VALUE val, WMS_CLASS_MEMBER mem  "
                          "where bd.BinaryDocumentId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcBinDoc);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(9).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueBinaryDocument))
                   {
                      CdmValueBinaryDocument* pCdmBinaryDocument = new CdmValueBinaryDocument(pCdmObject->GetSchemeId(),
                                                                                    lId,
                                                                                    qstrKeyname,
                                                                                    qstrFilename,
                                                                                    qstrType,
                                                                                    pCdmObject);

                      pCdmBinaryDocument->SetMemberId(lMemberId);
                      pCdmBinaryDocument->SetCaption(qstrCaption);
                      CdmDataAccessHelper::SetCreatorId(pCdmBinaryDocument, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmBinaryDocument, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmBinaryDocument);
                      pCdmBinaryDocument->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadBools(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading bool values for one object
      qstrQuery = QString("select val.ValueId, bo.Val, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_BOOL bo, WMS_VALUE val, WMS_CLASS_MEMBER mem  where bo.BoolId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcBool);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         cQSqlQuery.first();
         CdmObject* pCdmObject = nullptr;

         if(cQSqlQuery.isValid())
         {
            do // reading each bool
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               bool      bValue             = cQSqlQuery.value(1).toBool();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {


                 //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
                   {
                       CdmValueBool* pCdmBool = new CdmValueBool(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                       pCdmBool->SetMemberId(lMemberId);
                       pCdmBool->SetCaption(qstrCaption);
                       pCdmBool->SetValue(bValue);
                       CdmDataAccessHelper::SetCreatorId(pCdmBool, lCreatorId);
                       CdmDataAccessHelper::SetModifierId(pCdmBool, lModifierId);
                       CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmBool);
                       pCdmBool->SetLastChange(qdtLastChange);
                       pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadCharacterDocuments(QString p_qstrInString,
                                              QMap<long,
                                              CdmObject*>& p_rqmObjects,
                                              CdbDataAccess::EodbcBaseType p_eType)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading new id
      qstrQuery = QString("select dt.ValueId, cd.Val, dt.MemberId, dt.LastChange, dt.CreatorId, "
                          "dt.ModifierId, mem.Keyname, mem.Caption, dt.objectid from WMS_VALUE_CHARACTERDOCUMENT cd, "
                          "WMS_VALUE dt, WMS_CLASS_MEMBER mem where cd.CharacterDocumentId = dt.Valueid and "
                          "dt.MemberId = mem.MemberId and dt.ObjectId IN %1 and dt.BaseType = %2 order by dt.objectid")
                          .arg(p_qstrInString)
                          .arg(p_eType);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   // more than one type is read here
                   //if (CheckType(pCdmObject, qstrKeyname, eDmValueCharacterDocument))
                   {
                      CdmValueCharacterDocument* pCdmCharacterDocument = CreateCharDocValue(p_eType,
                                                                                       pCdmObject->GetSchemeId(),
                                                                                       lId,
                                                                                       qstrKeyname,
                                                                                       pCdmObject);
                      pCdmCharacterDocument->SetMemberId(lMemberId);
                      pCdmCharacterDocument->SetCaption(qstrCaption);
                      pCdmCharacterDocument->SetValue(qstrValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmCharacterDocument, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmCharacterDocument, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmCharacterDocument);
                      pCdmCharacterDocument->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadCounters(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading counter values for one object
      qstrQuery = QString("select val.ValueId, co.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_COUNTER co, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where co.CounterId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcCounter);


      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueCounter))
                   {
                      CdmValueCounter* pCdmCounter = new CdmValueCounter(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmCounter->SetMemberId(lMemberId);
                      pCdmCounter->SetCaption(qstrCaption);
                      ((CdmValueLong*)pCdmCounter)->SetValue(lValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmCounter, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmCounter, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmCounter);
                      pCdmCounter->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadDates(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading date values for one object
      qstrQuery = QString("select val.ValueId, da.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_DATE da, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where da.DateId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcDate);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueDate))
                   {
                      CdmValueDate* pCdmDate = new CdmValueDate(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmDate->SetMemberId(lMemberId);
                      pCdmDate->SetCaption(qstrCaption);
                      pCdmDate->SetValue(qdValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmDate, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmDate, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmDate);
                      pCdmDate->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadDateTimes(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading datetime values for one object
      qstrQuery = QString("select val.ValueId, dt.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_DATETIME dt, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where dt.DateTimeId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcDateTime);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // loading each class
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               QDateTime qdtValue           = cQSqlQuery.value(1).toDateTime();

               if (qdtValue.date() >= QDate(2037,12,31))
               {
                  qdtValue = QDateTime();
               }

               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueDateTime))
                   {
                      CdmValueDateTime* pCdmDateTime = new CdmValueDateTime(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmDateTime->SetMemberId(lMemberId);
                      pCdmDateTime->SetCaption(qstrCaption);
                      pCdmDateTime->SetValue(qdtValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmDateTime, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmDateTime, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmDateTime);
                      pCdmDateTime->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadDoubles(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, dou.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_DOUBLE dou, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where dou.DoubleId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcDouble);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueDouble))
                   {
                      CdmValueDouble* pCdmDouble = new CdmValueDouble(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmDouble->SetMemberId(lMemberId);
                      pCdmDouble->SetCaption(qstrCaption);
                      pCdmDouble->SetValue(dValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmDouble, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmDouble, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmDouble);
                      pCdmDouble->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadFloats(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, fl.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_FLOAT fl, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where fl.FloatId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcFloat);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // reading each float
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               float     fValue             = cQSqlQuery.value(1).toDouble();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueFloat))
                   {
                      CdmValueFloat* pCdmFloat = new CdmValueFloat(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmFloat->SetMemberId(lMemberId);
                      pCdmFloat->SetCaption(qstrCaption);
                      pCdmFloat->SetValue(fValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmFloat, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmFloat, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmFloat);
                      pCdmFloat->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadInts(QString p_qstrInString,
                                QMap<long,
                                CdmObject*>& p_rqmObjects,
                                CdbDataAccess::EodbcBaseType  p_eOdbcType)
{


   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading int values for one object
      qstrQuery = QString("select val.ValueId, valint.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_INT valint, WMS_VALUE val, "
                          "WMS_CLASS_MEMBER mem  where valint.IntId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(p_eOdbcType);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {

            do // reading each int
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               int       iValue             = cQSqlQuery.value(1).toInt();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   // more than one type is read here
                   //if (CheckType(pCdmObject, qstrKeyname, eDmValueInt))
                   {
                       CdmValueInt* pCdmInt = nullptr;

                       if (p_eOdbcType == CdbDataAccess::eOdbcInt)
                       {
                          pCdmInt = new CdmValueInt(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                       }
                       else if (p_eOdbcType == CdbDataAccess::eOdbcUser)
                       {
                          pCdmInt = new CdmValueUser(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                       }
                       else if (p_eOdbcType == CdbDataAccess::eOdbcUserGroup)
                       {
                          pCdmInt = new CdmValueUserGroup(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                       }
                       else if (p_eOdbcType == CdbDataAccess::eOdbcEnum)
                       {
                          pCdmInt = new CdmValueEnum(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                       }

                       pCdmInt->SetMemberId(lMemberId);
                       pCdmInt->SetCaption(qstrCaption);
                       pCdmInt->SetValue(iValue);
                       CdmDataAccessHelper::SetCreatorId(pCdmInt, lCreatorId);
                       CdmDataAccessHelper::SetModifierId(pCdmInt, lModifierId);
                       CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmInt);
                       pCdmInt->SetLastChange(qdtLastChange);
                       pCdmObject->ResetNewModified();

                   }
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

int CdbCommandLoadObjects::ReadLongs(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, lon.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_LONG lon, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where lon.LongId = val.ValueId and "
                          "val.Memberid = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcLong);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueLong))
                   {
                      CdmValueLong* pCdmLong = new CdmValueLong(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmLong->SetMemberId(lMemberId);
                      pCdmLong->SetCaption(qstrCaption);
                      pCdmLong->SetValue(lValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmLong, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmLong, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmLong);
                      pCdmLong->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadObjectRefs(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading objectreference values for one object
      qstrQuery = QString("SELECT val.ValueId, val.ObjectId, oref.ObjectListId, oref.ObjectId, val.MemberId, val.LastChange, val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption, obj.Keyname, objlist.Keyname "
                          "FROM WMS_VALUE_OBJECTREFERENCE oref "
                          "INNER JOIN WMS_VALUE val ON oref.ObjectReferenceId = val.ValueId "
                          "INNER JOIN WMS_CLASS_MEMBER mem ON val.MemberId = mem.MemberId "
                          "LEFT JOIN WMS_DM_OBJECT obj ON obj.ObjectId = oref.ObjectId "
                          "LEFT JOIN WMS_DM_OBJECTLIST objlist ON objlist.ObjectListId = oref.ObjectListId "
                          "WHERE val.ObjectId in %1 AND val.BaseType = %2")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcObjRef);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
         cQSqlQuery.first();
         if(cQSqlQuery.isValid())
         {

            do // reading each objectreference
            {
               long      lId                = cQSqlQuery.value(0).toInt();
               long      lObjectId          = cQSqlQuery.value(1).toInt();
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

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueObjectRef))
                   {
                      CdmValueObjectRef* pCdmObjectRef = new CdmValueObjectRef(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmObjectRef->SetMemberId(lMemberId);
                      pCdmObjectRef->SetCaption(qstrCaption);
                      pCdmObjectRef->SetValue(lObjectListId, lValue, qstrObjectKeyname, qstrContainerKeyname);
                      CdmDataAccessHelper::SetCreatorId(pCdmObjectRef, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmObjectRef, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmObjectRef);
                      pCdmObjectRef->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadObjectListRefs(QString p_qstrInString,
                                          QMap<long,
                                          CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading objectreference values for one object
      qstrQuery = QString("select val.ValueId, olr.classid, olr.ObjectListId, val.MemberId, val.LastChange, "
                          "val.CreatorId, val.ModifierId, mem.Keyname, mem.Caption, val.objectid from "
                          "WMS_VALUE_OBJECTLISTREFERENCE olr, WMS_VALUE val, WMS_CLASS_MEMBER mem  "
                          "where olr.ObjectListReferenceId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcObjListRef);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(9).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueContainerRef))
                   {
                      CdmValueContainerRef* pContainerRef = new CdmValueContainerRef(pCdmObject->GetSchemeId(),
                                                                                 lId,
                                                                                 qstrKeyname,
                                                                                 pCdmObject);
                      pContainerRef->SetMemberId(lMemberId);
                      pContainerRef->SetCaption(qstrCaption);
                      pContainerRef->SetValue(lValue);
                      CdmDataAccessHelper::SetCreatorId(pContainerRef, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pContainerRef, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pContainerRef);
                      pContainerRef->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadStrings(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading long values for one object
      qstrQuery = QString("select val.ValueId, str.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_STRING str, WMS_VALUE val, "
                          "WMS_CLASS_MEMBER mem  where str.StringId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcString);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
         cQSqlQuery.first();

         if(cQSqlQuery.isValid())
         {
            do // reading each string
            {
               long      lId                = cQSqlQuery.value(0).toInt();

               QString   qstrValue            = cQSqlQuery.value(1).toString();
               long      lMemberId          = cQSqlQuery.value(2).toInt();
               QDateTime qdtLastChange      = cQSqlQuery.value(3).toDateTime();
               long      lCreatorId         = cQSqlQuery.value(4).toInt();
               long      lModifierId        = cQSqlQuery.value(5).toInt();
               QString   qstrKeyname        = cQSqlQuery.value(6).toString();
               QString   qstrCaption        = cQSqlQuery.value(7).toString();
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueString))
                   {
                      CdmValueString* pCdmString = new CdmValueString(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmString->SetMemberId(lMemberId);
                      pCdmString->SetCaption(qstrCaption);
                      pCdmString->SetValue(qstrValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmString, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmString, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmString);
                      pCdmString->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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

int CdbCommandLoadObjects::ReadTimes(QString p_qstrInString, QMap<long, CdmObject*>& p_rqmObjects)
{
   long lRet = CdmLogging::eDmObjectAccessError;

   if (p_rqmObjects.count() > 0)
   {
      QSqlQuery cQSqlQuery;
      QString qstrQuery;

      // query for reading time values for one object
      qstrQuery = QString("select val.ValueId, ti.Val, val.MemberId, val.LastChange, val.CreatorId, "
                          "val.ModifierId, mem.Keyname, mem.Caption, val.objectid from WMS_VALUE_TIME ti, "
                          "WMS_VALUE val, WMS_CLASS_MEMBER mem  where ti.TimeId = val.ValueId and "
                          "val.MemberId = mem.MemberId and val.ObjectId IN %1 and val.BaseType = %2 order by val.objectid")
                          .arg(p_qstrInString)
                          .arg(CdbDataAccess::eOdbcTime);

      if(GetDataAccess()->ExecuteQuery(qstrQuery, cQSqlQuery) > 0)
      {
         CdmObject* pCdmObject = nullptr;
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
               long      lObjectId          = cQSqlQuery.value(8).toInt();

               if (pCdmObject)
               {
                  if (pCdmObject->GetId() != lObjectId)
                  {
                     if (p_rqmObjects.contains(lObjectId))
                     {
                        pCdmObject = p_rqmObjects[lObjectId];
                     }
                     else
                     {
                        pCdmObject = nullptr;
                     }
                  }
               }
               else
               {
                  if (p_rqmObjects.contains(lObjectId))
                  {
                     pCdmObject = p_rqmObjects[lObjectId];
                  }
                  else
                  {
                     pCdmObject = nullptr;
                  }
               }

               if (CHKPTR(pCdmObject))
               {
                   if (CheckType(pCdmObject, qstrKeyname, eDmValueTime))
                   {
                      CdmValueTime* pCdmTime = new CdmValueTime(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                      pCdmTime->SetMemberId(lMemberId);
                      pCdmTime->SetCaption(qstrCaption);
                      pCdmTime->SetValue(qtValue);
                      CdmDataAccessHelper::SetCreatorId(pCdmTime, lCreatorId);
                      CdmDataAccessHelper::SetModifierId(pCdmTime, lModifierId);
                      CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmTime);
                      pCdmTime->SetLastChange(qdtLastChange);
                      pCdmObject->ResetNewModified();
                   }
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


bool CdbCommandLoadObjects::CheckType(CdmObject* p_pObject, QString p_qstrKeyname, EdmValueType p_eNeeded)
{
    bool bRet = true;
    CdmClass* pClass = p_pObject->GetClass();

    if (CHKPTR(pClass))
    {
        const CdmMember* pMember = pClass->FindMember(p_qstrKeyname);

        if (!pMember ||
            pMember->GetValueType() != p_eNeeded)
        {
            if (!pMember)
            {
                WARNING("Try Loading Value of Keyname \"" + p_qstrKeyname + "\".\n The member does not exist anymore and the Value won't be created.");
            }
            else
            {
                WARNING("Try Loading Value of Keyname \"" + p_qstrKeyname + "\".\n The expected type \"" + pMember->GetValueTypeAsString() + "\" and the db type is \"" + CdmMember::GetValueTypeAsString(p_eNeeded) + "\".\nValue won't be created.");
            }
             bRet = false;
        }
    }

    return bRet;
}

CdmValueCharacterDocument* CdbCommandLoadObjects::CreateCharDocValue(CdbDataAccess::EodbcBaseType p_eType,
                                                            long p_lDatabaseId,
                                                            long p_lId,
                                                            QString p_qstrKeyname,
                                                            CdmObject* p_pCdmObjectOwner)
{
   CdmValueCharacterDocument* pDocument = nullptr;


   switch (p_eType)
   {
   case CdbDataAccess::eOdbcCharDoc:
      pDocument = new CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcListInt:
      pDocument = new CdmValueListInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcListDouble:
      pDocument = new CdmValueListDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcListString:
      pDocument = new CdmValueListString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcDictStringInt:
      pDocument = new CdmValueDictStringInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcDictStringString:
      pDocument = new CdmValueDictStringString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcDictStringDouble:
      pDocument = new CdmValueDictStringDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcDictIntInt:
      pDocument = new CdmValueDictIntInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcDictIntString:
      pDocument = new CdmValueDictIntString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eODbcDictIntDouble:
      pDocument = new CdmValueDictIntDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case CdbDataAccess::eOdbcListObjects:
      pDocument = new CdmValueListObjects(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   default:
      ERR("Invalid Type");
      break;
   }

   return pDocument;
}

