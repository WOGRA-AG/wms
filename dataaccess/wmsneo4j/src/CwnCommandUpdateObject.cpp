// System and Qt Includes
#include <QFileInfo>

// WMS includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmValue.h"
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
#include "CwnJournal.h"
#include "CwnCommandUpdateBinaryDocument.h"
#include "CwnCommandDeleteObject.h"
#include "CwnCommandCheckObjectLocked.h"
#include "CwnHelper.h"
#include "CwnCommandUpdateObject.h"

#include "CwnCommandStdHeader.h"

CwnCommandUpdateObject::CwnCommandUpdateObject(qint64 p_lSessionId, CdmObject* p_pObject, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lSessionId(p_lSessionId),
      m_rpObject(p_pObject)
{

}

CwnCommandUpdateObject::~CwnCommandUpdateObject()
{

}

bool CwnCommandUpdateObject::CheckValid()
{
    return (m_lSessionId > 0 && CHKPTR(m_rpObject));
}

int CwnCommandUpdateObject::Execute()
{

   qint64 lRet = CdmLogging::eDmObjectAccessError;
    CwnCommandCheckObjectLocked command(m_rpObject->GetId(), m_lSessionId, GetDataAccess());

    if(!SUCCESSFULL(command.Run())) // is not locked
    {
        if((m_rpObject->IsNew() || m_rpObject->IsModified()) && !m_rpObject->IsDeleted() && m_rpObject->IsValid())
        {
            QMap<QString,CdmValue*> qmValues;
            m_rpObject->GetValueMap(qmValues);

            CwnJournal* pJournal = GetDataAccess()->GetJournal();
            if(pJournal)
            {
                pJournal->ObjectModified(m_rpObject);
            }

            QMap<QString, CdmValue*>::iterator qmIt = qmValues.begin();
            QMap<QString, CdmValue*>::iterator qmItEnd = qmValues.end();

            payload += startJsonWCommand(createQueryForUpdateObjects());

            qmIt = qmValues.begin();
            int iCounter = 0;

            for(; qmIt != qmItEnd; ++qmIt)
            {
               CdmValue* pCdmValue = qmIt.value();
               ++iCounter;

               if(CHKPTR(pCdmValue))
               {
                  InsertOrUpdateValue(pCdmValue);
               }
               else
               {
                  lRet = EC(eDmInvalidPtr);
                  break;
               }
            }

            payload += endJsonCommand();

            //qDebug() << payload;
            queryCausedError = payload;
            ConnectAndExecute(openTransaction,payload,nullptr,nullptr);
            QVariant Ret;
            interpretAnswer(Ret);
            lRet = Ret.toInt();
        }
        else if(m_rpObject->IsDeleted() || !m_rpObject->IsValid())
        {

            CwnCommandDeleteObject command(m_rpObject->GetId(), m_lSessionId, GetDataAccess());
            lRet = command.Run();

            if(lRet > 0)
            {
                CdmDataAccessHelper::DeleteObject(m_rpObject);
            }
            else
            {
                ERR("DeleteObject failed!");
            }
        }
    }
    else
    {
        lRet = EC(eDmObjectDeathLock);
        ERR("Cannot update object because it is locked.");
    }

    return static_cast<int>(lRet);
}

void CwnCommandUpdateObject::InsertOrUpdateValue(CdmValue* p_pValue)
{

    if(m_rpObject->IsNew() || p_pValue->IsNew())
    {
       INFO("New Object the Insert method will be called!!");
       InsertValue(p_pValue);
    }
    else if(p_pValue->IsModified())
    {
       INFO("Modified Object the Update method will be called!!");
       UpdateValue(p_pValue);

    }
    else
    {
       EC(eDmOk);
       INFO("Value is not new and not modified must no be updated or inserted Value Id: " + QString::number(p_pValue->GetId()));
    }

}


void CwnCommandUpdateObject::InsertValue(CdmValue* p_pValue)
{
   if(CHKPTR(p_pValue))
   {
      editValues.enqueue(p_pValue);
      EdmValueType eDmValue = p_pValue->GetValueType();

      switch(eDmValue)
      {
      case eDmValueBool:
         InsertBool(dynamic_cast<CdmValueBool*>(p_pValue));
         break;
      case eDmValueInt:
         InsertInt(dynamic_cast<CdmValueInt*>(p_pValue), eDmValueInt);
         break;
      case eDmValueLong:
         InsertLong(dynamic_cast<CdmValueLong*>(p_pValue));
         break;
      case eDmValueFloat:
         InsertFloat(dynamic_cast<CdmValueFloat*>(p_pValue));
         break;
      case eDmValueDouble:
         InsertDouble(dynamic_cast<CdmValueDouble*>(p_pValue));
         break;
      case eDmValueString:
         InsertString(dynamic_cast<CdmValueString*>(p_pValue));
         break;
      case eDmValueDate:
         InsertDate(dynamic_cast<CdmValueDate*>(p_pValue));
         break;
      case eDmValueTime:
         InsertTime(dynamic_cast<CdmValueTime*>(p_pValue));
         break;
      case eDmValueDateTime:
         InsertDateTime(dynamic_cast<CdmValueDateTime*>(p_pValue));
         break;
      case eDmValueObjectRef:
         InsertObjectRef(dynamic_cast<CdmValueObjectRef*>(p_pValue));
         break;
      case eDmValueContainerRef:
         InsertContainerRef(dynamic_cast<CdmValueContainerRef*>(p_pValue));
         break;
      case eDmValueCounter:
         InsertCounter(dynamic_cast<CdmValueCounter*>(p_pValue));
         break;
      case eDmValueBinaryDocument:
         InsertBinaryDocument(dynamic_cast<CdmValueBinaryDocument*>(p_pValue));
         break;
     // Chardocs and derived documents from chardoc as xml
     case eDmValueCharacterDocument:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue), eDmValueCharacterDocument);
         break;
      case eDmValueListInt:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueListInt);
         break;
      case eDmValueListDouble:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueListDouble);
         break;
      case eDmValueListString:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueListString);
         break;
      case eDmValueDictStringInt:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictStringInt);
         break;
      case eDmValueDictStringString:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictStringString);
         break;
      case eDmValueDictStringDouble:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictStringDouble);
         break;
      case eDmValueDictIntInt:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictIntInt);
         break;
      case eDmValueDictIntString:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictIntString);
         break;
      case eDmValueDictIntDouble:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueDictIntDouble);
         break;
      case eDmValueListObjects:
         InsertCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),eDmValueListObjects);
         break;
      case eDmValueUser:
         InsertInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueUser);
         break;
      case eDmValueUserGroup:
         InsertInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueUserGroup);
         break;
      case eDmValueEnum:
         InsertInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueEnum);
         break;
      case eDmValueFormula:
         EC(eDmOk);
         break;
      default:
         EC(eDmUnknownValueError);
         ERR("Invalid Value for writing to object list!!!");
         break;
      }
   }
   else
   {
      EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateValue(CdmValue* p_pValue)
{
   if(CHKPTR(p_pValue))
   {
      editValues.enqueue(p_pValue);
      EdmValueType eDmValue = p_pValue->GetValueType();
      QString qstrQuery;

      switch ( eDmValue )
      {
      case eDmValueBool:
         UpdateBool(dynamic_cast<CdmValueBool*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueInt:
         UpdateInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueInt,qstrQuery,false);
         break;
      case eDmValueLong:
         UpdateLong(dynamic_cast<CdmValueLong*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueFloat:
         UpdateFloat(dynamic_cast<CdmValueFloat*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueDouble:
         UpdateDouble(dynamic_cast<CdmValueDouble*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueString:
         UpdateString(dynamic_cast<CdmValueString*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueDate:
         UpdateDate(dynamic_cast<CdmValueDate*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueTime:
         UpdateTime(dynamic_cast<CdmValueTime*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueDateTime:
         UpdateDateTime(dynamic_cast<CdmValueDateTime*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueObjectRef:
         UpdateObjectRef(dynamic_cast<CdmValueObjectRef*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueContainerRef:
         UpdateContainerRef(dynamic_cast<CdmValueContainerRef*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueCounter:
         UpdateCounter(dynamic_cast<CdmValueCounter*>(p_pValue),qstrQuery,false);
         break;
      case eDmValueBinaryDocument:
         UpdateBinaryDocument(dynamic_cast<CdmValueBinaryDocument*>(p_pValue),qstrQuery,false);
         //CwnCommandUpdateBinaryDocument command((CdmValueBinaryDocument*)p_pValue, GetDataAccess());
         //lRet = command.Run();
         break;
      // Chardocs and derived documents from chardoc as xml
      case eDmValueCharacterDocument:
      case eDmValueListInt:
      case eDmValueListDouble:
      case eDmValueListString:
      case eDmValueDictStringInt:
      case eDmValueDictStringString:
      case eDmValueDictStringDouble:
      case eDmValueDictIntInt:
      case eDmValueDictIntString:
      case eDmValueDictIntDouble:
      case eDmValueListObjects:
          UpdateCharacterDocument(dynamic_cast<CdmValueCharacterDocument*>(p_pValue),qstrQuery,false);
          break;
      case eDmValueUser:
         UpdateInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueUser,qstrQuery,false);
         break;
      case eDmValueUserGroup:
         UpdateInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueUserGroup,qstrQuery,false);
         break;
      case eDmValueEnum:
         UpdateInt(dynamic_cast<CdmValueInt*>(p_pValue),eDmValueEnum,qstrQuery,false);
         break;
      case eDmValueFormula:
         EC(eDmOk);
         break;
      default:
         EC(eDmUnknownValueError);
         ERR("Invalid Value for writing to object list!!!");
         break;
      }
   }
   else
   {
      EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::InsertValue(CdmValue* p_pValue,
                                         EdmValueType p_eType,
                                         QString& qstrQuery)
{
    if( CHKPTR(p_pValue))
    {
        QString label = getLabel(p_eType);

        qstrQuery = QString("MATCH (o:WMS_DM_OBJECT) WHERE id(o)=%1 MATCH (m:WMS_CLASS_MEMBER) WHERE id(m)=%2"
                          " CREATE (o)-[:Object_value]->(v:WMS_VALUE:"+label+")<-[:member_to_value]-(m) WITH v ")
                           .arg(m_rpObject->GetId())
                           .arg(p_pValue->GetMemberId());
        if(p_pValue->GetCreatorId()!=0)
          qstrQuery += QString("MATCH (uc:User) WHERE id(uc)=%1 CREATE (uc)-[:ValueCreator]->(v) WITH v ")
                        .arg(p_pValue->GetCreatorId());
        if(p_pValue->GetModifierId()!=0)
          qstrQuery += QString("MATCH (um:User) WHERE id(um)=%1 CREATE (um)-[:ValueModifier]->(v) WITH v ")
                        .arg(p_pValue->GetModifierId());

        qstrQuery += QString("SET v += { type:%1, LastChange:%2 } WITH v ")
            .arg(p_eType)
            .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()));

    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::UpdateValueTable(CdmValue* p_pValue, QString &qstrQuery)
{
    if(CHKPTR(p_pValue))
    {
        // query for reading new id
        qstrQuery = QString("MATCH (o:WMS_DM_OBJECT)-[k:Object_value]->(v:WMS_VALUE)<-[l:member_to_value]-(m:WMS_CLASS_MEMBER) WHERE id(v)=%1 AND id(o)=%2 AND id(m)=%3 SET v.LastChange=%4 WITH o,v,m ")
                        .arg(p_pValue->GetId())
                        .arg(m_rpObject->GetId())
                        .arg(p_pValue->GetMemberId())
                        .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()));

        qstrQuery += QString("OPTIONAL MATCH ()-[a:ValueModifier]-(v) DELETE a WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[b:ValueCreator]-(v) DELETE b WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[c:userValue]-(v) DELETE c WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[d:userGroupValue]-(v) DELETE d WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[e:objectRefValue]-(v) DELETE e WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[f:objectListRefValue]-(v) DELETE f WITH v ");
        qstrQuery += QString("OPTIONAL MATCH ()-[g:enumValue]-(v) DELETE g WITH v ");

        if(p_pValue->GetModifierId()!=0)
          qstrQuery += QString("MATCH (um:User) WHERE id(um)=%1 CREATE (um)-[:ValueModifier]->(v) WITH v ")
                  .arg(p_pValue->GetModifierId());
        if(p_pValue->GetCreatorId()!=0)
          qstrQuery += QString("MATCH (uc:User) WHERE id(uc)=%1 CREATE (uc)-[:ValueCreator]->(v) WITH v ")
                        .arg(p_pValue->GetCreatorId());
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}


void CwnCommandUpdateObject::InsertBool(CdmValueBool* p_pCdmBool)
{
    if(CHKPTR(p_pCdmBool))
    {
        QString qstrQuery;
        InsertValue(p_pCdmBool, eDmValueBool,qstrQuery);
        UpdateBool(p_pCdmBool,qstrQuery,true);
    }
}

void CwnCommandUpdateObject::UpdateBool(CdmValueBool* p_pCdmBool, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmBool))
    {
        if(!insert){
            UpdateValueTable(p_pCdmBool, qstrQuery);
            createValueJournal(p_pCdmBool);
        }

        qstrQuery += QString("SET v.val=\'%1\' REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmBool->GetValue());

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertInt(CdmValueInt* p_pCdmInt, EdmValueType  p_eType)
{
    if(CHKPTR(p_pCdmInt))
    {
        QString qstrQuery;
        InsertValue(p_pCdmInt, p_eType,qstrQuery);
        UpdateInt(p_pCdmInt,p_eType,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateInt(CdmValueInt* p_pCdmInt, EdmValueType p_eType, QString& qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmInt))
    {
        if(!insert){
            UpdateValueTable(p_pCdmInt, qstrQuery);
            createValueJournal(p_pCdmInt);
        }

        switch(p_eType){
        case eDmValueInt:
            qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmInt->GetValue());
            break;
        case eDmValueUser:
            qstrQuery += QString("MATCH (uv:User) WHERE id(uv)=%1 CREATE (v)-[:userValue]->(uv) REMOVE v.val, v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmInt->GetValue());
            break;
        case eDmValueUserGroup:
            qstrQuery += QString("MATCH (uvg:Group) WHERE id(uvg)=%1 CREATE (v)-[:userGroupValue]->(uvg) REMOVE v.val, v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmInt->GetValue());
            break;
        case eDmValueEnum:
            qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmInt->GetValue());
            break;
        default:
            ERR("Wrong type for an update Integer");
            break;
        }
        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertLong(CdmValueLong* p_pCdmLong)
{
    if(CHKPTR(p_pCdmLong))
    {
        QString qstrQuery;
        InsertValue(p_pCdmLong, eDmValueLong,qstrQuery);
        UpdateLong(p_pCdmLong,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateLong(CdmValueLong* p_pCdmLong, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmLong))
    {
        if(!insert){
            UpdateValueTable(p_pCdmLong, qstrQuery);
            createValueJournal(p_pCdmLong);
        }

        qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmLong->GetValue());

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertFloat(CdmValueFloat* p_pCdmFloat)
{
    if(CHKPTR(p_pCdmFloat))
    {
        QString qstrQuery;
        InsertValue(p_pCdmFloat, eDmValueFloat,qstrQuery);
        UpdateFloat(p_pCdmFloat,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateFloat(CdmValueFloat* p_pCdmFloat, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmFloat))
    {
        if(!insert){
            UpdateValueTable(p_pCdmFloat, qstrQuery);
            createValueJournal(p_pCdmFloat);
        }

        qstrQuery += QString("SET v.val=toFloat(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(QString::number(p_pCdmFloat->GetValue(),'f',7));

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertDouble(CdmValueDouble* p_pCdmDouble)
{
    if(CHKPTR(p_pCdmDouble))
    {
        QString qstrQuery;
        InsertValue(p_pCdmDouble, eDmValueDouble,qstrQuery);
        UpdateDouble(p_pCdmDouble,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateDouble(CdmValueDouble* p_pCdmDouble, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmDouble))
    {
        if(!insert){
            UpdateValueTable(p_pCdmDouble, qstrQuery);
            createValueJournal(p_pCdmDouble);
        }

        qstrQuery += QString("SET v.val=toFloat(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(QString::number(p_pCdmDouble->GetValue(),'f',16));

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertString(CdmValueString* p_pCdmString)
{
    if(CHKPTR(p_pCdmString))
    {
        QString qstrQuery;
        InsertValue(p_pCdmString, eDmValueString,qstrQuery);
        UpdateString(p_pCdmString,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateString(CdmValueString* p_pCdmString, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmString))
    {
        if(!insert){
            UpdateValueTable(p_pCdmString, qstrQuery);
            createValueJournal(p_pCdmString);
        }

        qstrQuery += QString("SET v.val=\'%1\' REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(CwnHelper::MaskStringForChanges(p_pCdmString->GetValue()));

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertDate(CdmValueDate* p_pCdmDate)
{
    if(CHKPTR(p_pCdmDate))
    {
        QString qstrQuery;
        InsertValue(p_pCdmDate, eDmValueDate,qstrQuery);
        UpdateDate(p_pCdmDate,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateDate(CdmValueDate* p_pCdmDate, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmDate))
    {
        if(!insert)
        {
            UpdateValueTable(p_pCdmDate, qstrQuery);
            createValueJournal(p_pCdmDate);
        }

        qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmDate->GetValue().toJulianDay());
        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertTime(CdmValueTime* p_pCdmTime)
{
    if(CHKPTR(p_pCdmTime))
    {
        QString qstrQuery;
        InsertValue(p_pCdmTime, eDmValueTime,qstrQuery);
        UpdateTime(p_pCdmTime,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateTime(CdmValueTime* p_pCdmTime, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmTime))
    {
        if(!insert)
        {
            UpdateValueTable(p_pCdmTime, qstrQuery);
            createValueJournal(p_pCdmTime);
        }

        QTime qTime = p_pCdmTime->GetValue();

        if (!qTime.isValid())
        {
           qTime = QTime::currentTime();
        }

        qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(QTime(0,0).secsTo(qTime));

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertDateTime(CdmValueDateTime* p_pCdmDateTime)
{
    if(CHKPTR(p_pCdmDateTime))
    {
        QString qstrQuery;
        InsertValue(p_pCdmDateTime, eDmValueDateTime,qstrQuery);
        UpdateDateTime(p_pCdmDateTime,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateDateTime(CdmValueDateTime* p_pCdmDateTime, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmDateTime))
    {
        if(!insert){
            UpdateValueTable(p_pCdmDateTime, qstrQuery);
            createValueJournal(p_pCdmDateTime);
        }


        qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmDateTime->GetValue().toTime_t());

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertObjectRef(CdmValueObjectRef* p_pCdmObjectRef)
{
    if(CHKPTR(p_pCdmObjectRef))
    {
        QString qstrQuery;
        InsertValue(p_pCdmObjectRef, eDmValueObjectRef,qstrQuery);
        UpdateObjectRef(p_pCdmObjectRef,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateObjectRef(CdmValueObjectRef* p_pCdmObjectRef, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmObjectRef))
    {
        if(!insert){
            UpdateValueTable(p_pCdmObjectRef, qstrQuery);
            createValueJournal(p_pCdmObjectRef);
        }


        qstrQuery += QString("MATCH (or:WMS_DM_OBJECT) WHERE id(or)=%1 CREATE (v)-[:objectRefValue]->(or) REMOVE v.val, v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmObjectRef->GetValue());

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertContainerRef(CdmValueContainerRef* p_pContainerRef)
{
    if(CHKPTR(p_pContainerRef))
    {
        QString qstrQuery;
        InsertValue(p_pContainerRef, eDmValueContainerRef,qstrQuery);
        UpdateContainerRef(p_pContainerRef,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateContainerRef(CdmValueContainerRef* p_pContainerRef, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pContainerRef))
    {
        if(!insert){
            UpdateValueTable(p_pContainerRef, qstrQuery);
            createValueJournal(p_pContainerRef);
        }


        qstrQuery += QString("MATCH (olr:WMS_DM_OBJECTLIST) WHERE id(olr)=%1 CREATE (v)-[:objectListRefValue]->(olr) REMOVE v.val, v.filetype, v.filename RETURN id(v), v.type").arg(p_pContainerRef->GetValue());

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }

}

void CwnCommandUpdateObject::createValueJournal(CdmValue *p_pValue)
{
    CwnJournal* pJournal = GetDataAccess()->GetJournal();

    if(pJournal)
    {
        pJournal->ValueModified(p_pValue);
    }

}

void CwnCommandUpdateObject::InsertCounter(CdmValueCounter* p_pCdmCounter)
{
    if(CHKPTR(p_pCdmCounter))
    {
        QString qstrQuery;
        InsertValue(p_pCdmCounter,eDmValueCounter,qstrQuery);
        UpdateCounter(p_pCdmCounter,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateCounter(CdmValueCounter* p_pCdmCounter, QString &qstrQuery, bool insert)
{
    if(CHKPTR(p_pCdmCounter))
    {
        if(!insert){
            UpdateValueTable(p_pCdmCounter, qstrQuery);
            createValueJournal(p_pCdmCounter);
        }


        qstrQuery += QString("SET v.val=toInt(\'%1\') REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(p_pCdmCounter->GetValue());

        counterValueList.append(p_pCdmCounter);
        counterAdded +=true;
        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}


void CwnCommandUpdateObject::GetCounterValue()
{
   for(int i=0; i<counterValueList.count();i++)
   {
       CdmValueCounter* temp = counterValueList.at(i);

       if (CHKPTR(temp))
       {
          const CdmObject* pCdmObject = temp->GetObject();

          if (CHKPTR(pCdmObject))
          {
            qint64 lObjectListId = pCdmObject->GetObjectContainerId();

             ((CdmValueLong*)temp)->SetValue(GetCounterValue(lObjectListId,temp->GetId(),temp->GetKeyname()));
          }
       }
   }
}


qint64 CwnCommandUpdateObject::GetCounterValue(qint64 p_lObjectListId,
                                            qint64 p_lValueId,
                                             QString p_qstrKeyname)
{
  qint64 lRet = CdmLogging::eDmObjectAccessError;
   QString qstrQuery;


   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:WMS_VALUE:COUNTER)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' RETURN max(v.val)+1")
                       .arg(p_lObjectListId)
                       .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname));

   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswerForCounter(Ret);
  qint64 lValue = Ret.toInt();
   lRet = Ret.toInt();

   QTime qtCurrent = QTime::currentTime();
   int iTimeStamp = qtCurrent.msec() * qtCurrent.second() * qtCurrent.minute() * qtCurrent.hour();

   qstrQuery = QString("MATCH (v) WHERE id(v:WMS_VALUE:COUNTER)=%3  SET v.val=%1, v.timestamp = %2 RETURN 1")
                          .arg(lValue)
                          .arg(iTimeStamp)
                          .arg(p_lValueId);

   payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   interpretAnswerForCounter(Ret);
   lRet = Ret.toInt();

   if(lRet> 0)
   {
        lRet = MakeCounterValueUnique(static_cast<int>(lValue),
                                       static_cast<int>(iTimeStamp),
                                       p_qstrKeyname,
                                       static_cast<int>(p_lObjectListId),
                                       static_cast<int>(p_lValueId));
   }
   return lRet;
}


int CwnCommandUpdateObject::MakeCounterValueUnique(int p_iCounter,
                                              int p_iTimeStamp,
                                              QString p_qstrKeyname,
                                              int p_lObjectId,
                                              int p_iValueId)
{
   int iRet = CdmLogging::eDmUnknownClassAccessError;
   QString qstrQuery;
   int iSuccess = 0;

   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:WMS_VALUE:COUNTER)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' AND v.val=%3 "
                       "RETURN COUNT(v)")
                   .arg(p_lObjectId)
                   .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname))
                   .arg(p_iCounter);


   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswerForCounter(Ret);

   iSuccess = Ret.toInt();

   if(iSuccess > 0)
   {
     qint64 lValue = iSuccess;
      if (lValue == 1)
      {
        iRet = p_iCounter;
      }
      else if (lValue > 1)
      {
        iRet = IncreaseCounterValue(p_iCounter,
                                    p_iTimeStamp,
                                    p_qstrKeyname,
                                    p_lObjectId,
                                    p_iValueId);
      }
   }
   return iRet;
}


int CwnCommandUpdateObject::IncreaseCounterValue(int p_iCounter,
                                            int p_iTimeStamp,
                                            QString p_qstrKeyname,
                                            int p_lObjectId,
                                            int p_iValueId)
{
   int iRet = p_iCounter;

   if (CheckIncreaseCounterNeeded(p_iCounter,
                                  p_iTimeStamp,
                                  p_qstrKeyname,
                                  p_lObjectId,
                                  p_iValueId))
   {
      iRet = GetCounterValue(p_lObjectId, p_iValueId, p_qstrKeyname);
   }

   return iRet;
}

bool CwnCommandUpdateObject::CheckIncreaseCounterNeeded(int p_iCounter,
                                                   int p_iTimeStamp,
                                                   QString p_qstrKeyname,
                                                   int p_lObjectId,
                                                   int)
{
   bool bRet = false;
   QString qstrQuery;
   int iSuccess = 0;


   qstrQuery = QString("MATCH (m:WMS_CLASS_MEMBER)-[:member_to_value]->(v:WMS_VALUE:COUNTER)<-[:Object_value]-(:WMS_DM_OBJECT)<-[:hasObjects]-(ol:WMS_DM_OBJECTLIST) "
                       "WHERE id(ol)=%1 AND m.Keyname=\'%2\' AND v.val = %3 "
                       "RETURN min(v.timestamp)")
      .arg(p_lObjectId)
      .arg(CwnHelper::MaskStringForChanges(p_qstrKeyname))
      .arg(p_iCounter);

   QString payload = createJson(qstrQuery);
   queryCausedError = payload;
   ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
   QVariant Ret;
   interpretAnswerForCounter(Ret);

   iSuccess = Ret.toInt();

   if(iSuccess > 0)
   {
     qint64 lValue = iSuccess;

      if (lValue != p_iTimeStamp)
      {
        bRet = true;
      }
   }

   return bRet;
}

void CwnCommandUpdateObject::InsertBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument)
{

    if(CHKPTR(p_pCdmBinaryDocument))
    {
        QString qstrQuery;
        InsertValue(p_pCdmBinaryDocument, eDmValueBinaryDocument,qstrQuery);
        UpdateBinaryDocument(p_pCdmBinaryDocument,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

QString CwnCommandUpdateObject::ShortFilename(QString p_qstrFilename)
{
   QString qstrFilename;

   if (p_qstrFilename.length() > 32)
   {
      QFileInfo qfInfo(p_qstrFilename);
      QString qstrSuffix = qfInfo.completeSuffix();
      qstrFilename = qfInfo.baseName();
      qstrFilename = qstrFilename.left(31 - qstrSuffix.length());
      qstrFilename += "." + qstrSuffix;
   }
   else
   {
      qstrFilename = p_qstrFilename;
   }

   return qstrFilename;
}

void CwnCommandUpdateObject::UpdateBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, QString &qstrQuery, bool insert)
{
    QString qcstrBase64 = p_pCdmBinaryDocument->GetBase64();
    // if string is empty then the bindoc was deleted.

    QString qstrFilename = ShortFilename(p_pCdmBinaryDocument->GetFilename());
    QString qstrFileType = p_pCdmBinaryDocument->GetFileType();
    qstrFileType = qstrFileType.replace("'", "");

    if(CHKPTR(p_pCdmBinaryDocument))
    {
        if(!insert)
            UpdateValueTable(p_pCdmBinaryDocument, qstrQuery);


        qstrQuery += QString("SET v.filetype=\'%1\', v.filename=\'%2\', v.val=\'%3\' RETURN id(v), v.type").arg(qstrFileType).arg(qstrFilename.mid(0, 32)).arg(qcstrBase64);

        payload += addJsonCommand(qstrQuery);
    }
    else
    {
        EC(eDmInvalidPtr);
    }
}

void CwnCommandUpdateObject::InsertCharacterDocument(CdmValueCharacterDocument* p_pCdmCharacterDocument,
                                                     EdmValueType p_eType)
{
    if(CHKPTR(p_pCdmCharacterDocument))
    {
        QString qstrQuery;
        InsertValue(p_pCdmCharacterDocument, p_eType,qstrQuery);
        UpdateCharacterDocument(p_pCdmCharacterDocument,qstrQuery,true);
   }
   else
   {
        EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::UpdateCharacterDocument(CdmValueCharacterDocument* p_pCdmCharacterDocument,
                                              QString &qstrQuery, bool insert)
{
   if(CHKPTR(p_pCdmCharacterDocument))
   {
       if(!insert)
           UpdateValueTable(p_pCdmCharacterDocument, qstrQuery);

       QString qstrValue = p_pCdmCharacterDocument->GetValue();
       qstrQuery += QString("SET v.val=\'%1\' REMOVE v.filetype, v.filename RETURN id(v), v.type").arg(CwnHelper::base64_encode(qstrValue));

       payload += addJsonCommand(qstrQuery);
   }
   else
   {
       EC(eDmInvalidPtr);
   }
}

void CwnCommandUpdateObject::interpretAnswerForCounter(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=0;
    }
    else
    {

        const QVariantList* dataList=CwnCommandBase::getDataListPtr();

        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

            Ret = list->at(0);
        }
        else
            Ret=0;
    }
    this->answer = nullptr;
}

void CwnCommandUpdateObject::interpretAnswer(QVariant &Ret)
{
    //qDebug() << location;
    //qDebug() << answer;
    bool bRet = false;

    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());
    this->answer=nullptr;

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=EC(eDmInvalidSelectStatement);
    }
    else
    {
        const QVariantList* results = static_cast<const QVariantList*>(this->qResult->find("results")->data());
        QVariantList::ConstIterator it;

        for (it=results->begin(); it!=results->end(); ++it)
        {
            const QVariantMap* data = static_cast<const QVariantMap*>(it->data());
            const QVariantList* dataList = static_cast<const QVariantList*>(data->find("data")->data());

            // Wurde überhaupt etwas zurückgegeben?
            if(dataList->count() >0)
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
                const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                if(list->at(0).toInt()>0)
                {
                    if(list->count()>1)
                        CdmDataAccessHelper::SetId(this->editValues.dequeue(), list->at(0).toInt());
                    bRet = true;
                }
                else
                    bRet = false;
            }

            if(!bRet)
            {

                ConnectAndExecute(rollbackTransaction,nullptr,this->location,nullptr);
                Ret = -1;
                ERR("Something did go wrong with updateing a object");
                break;
            }
        }

        if(bRet)
        {
            Ret=1;
            ConnectAndExecute(commitTransaction,nullptr,this->location,nullptr);
            if(counterAdded){
                GetCounterValue();
                counterAdded=false;
            }
            m_rpObject->ResetNewModified();
        }
    }
}

QString CwnCommandUpdateObject::createQueryForUpdateObjects()
{
    QString qstrQuery;
    // first step update object itselves

    qstrQuery = QString("MATCH (w:WMS_DM_OBJECT) WHERE id(w)=%1 MATCH (w)<-[h:hasObjects]-(c) "
                        "OPTIONAL MATCH (w)<-[oc:ObjectCreator]-(:User) OPTIONAL MATCH (w)<-[om:ObjectModifier]-(:User) "
                        "OPTIONAL MATCH (w)<-[po:ParentObject]-(o:WMS_DM_OBJECT) OPTIONAL MATCH (w)<-[sc:sessionCreated]-(:Session) "
                        "DELETE h,oc,om,po,sc WITH w MATCH (nc:WMS_DM_OBJECTLIST) WHERE id(nc)=%2 CREATE (nc)-[:hasObjects]->(w) WITH w ")
                      .arg(m_rpObject->GetId())
                      .arg(m_rpObject->GetObjectContainerId());
    if(m_rpObject->GetCreatorId() !=0)
        qstrQuery += QString("MATCH (uc:User) WHERE id(uc)=%1 CREATE (uc)-[:ObjectCreator]->(w) WITH w ")
                      .arg(m_rpObject->GetCreatorId());
    if(m_rpObject->GetModifierId() !=0)
        qstrQuery += QString("MATCH (um:User) WHERE id(um)="+QString::number(m_rpObject->GetModifierId())+" CREATE (um)-[:ObjectModifier]->(w) WITH w ");
    if(m_rpObject->GetParentId() !=0)
        qstrQuery += QString("MATCH (op:WMS_DM_OBJECT) WHERE id(op)=%1 CREATE (op)-[:ParentObject]->(w) ")
                    .arg(m_rpObject->GetParentId());

    qstrQuery += QString("SET w += { Keyname:\'%1\', LastChange:%2, Caption:\'%3\', Config:\'%4\' } RETURN id(w) ")
          .arg(CwnHelper::MaskStringForChanges(m_rpObject->GetKeyname().right(250)))
          .arg(CwnHelper::ChangeDateToString(QDateTime::currentDateTime()))
          .arg(CwnHelper::MaskStringForChanges(m_rpObject->GetCaption().left(45)))
          .arg(CwnHelper::base64_encode(m_rpObject->GetConfig()));

    return qstrQuery;

}

QString CwnCommandUpdateObject::getLabel(EdmValueType p_eBaseType)
{
    QString label;
    switch(p_eBaseType)
    {
    case eDmValueBool:
        label="BOOLEAN";
    break;
    case eDmValueInt:
        label="INTEGER";
    break;
    case eDmValueLong:
        label="qint64";
    break;
    case eDmValueFloat:
        label="FLOAT";
    break;
    case eDmValueDouble:
        label="DOUBLE";
    break;
    case eDmValueString:
        label="STRING";
    break;
    case eDmValueDate:
        label="DATE";
    break;
    case eDmValueTime:
        label="TIME";
    break;
    case eDmValueDateTime:
        label="DATETIME";
    break;
    case eDmValueObjectRef:
        label="OBJECTREF";
    break;
    case eDmValueContainerRef:
        label="OBJECTLISTREF";
    break;
    case eDmValueBinaryDocument:
        label="BINDOC";
    break;
    case eDmValueCharacterDocument:
    case eDmValueDictIntInt:
    case eDmValueDictIntDouble:
    case eDmValueDictIntString:
    case eDmValueDictStringInt:
    case eDmValueDictStringDouble:
    case eDmValueDictStringString:
    case eDmValueListInt:
    case eDmValueListDouble:
    case eDmValueListObjects:
    case eDmValueListString:
        label="CHARDOC";
    break;
    case eDmValueUser:
        label="USER";
    break;
    case eDmValueUserGroup:
        label="USERGROUP";
    break;
    case eDmValueEnum:
        label="ENUM";
    break;
    case eDmValueFormula:
        label="FORMULA";
    break;
    case eDmValueCounter:
        label="COUNTER";
    break;
    }

    return label;
}

