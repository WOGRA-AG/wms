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
#include "CwnHelper.h"
#include "CwnCommandLoadObjects.h"

#include "CwnCommandStdHeader.h"

#include <QTime>
#include <QDateTime>
#include <QDate>

CwnCommandLoadObjects::CwnCommandLoadObjects(CdmObjectContainer* p_pContainer, QLinkedList<long> &p_qlObjectIds, CwnDataAccess* p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
  m_rpContainer(p_pContainer),
  m_qvlObjectIds(p_qlObjectIds)
{
}

CwnCommandLoadObjects::~CwnCommandLoadObjects()
{

}

bool CwnCommandLoadObjects::CheckValid()
{
    return (CHKPTR(m_rpContainer) && m_qvlObjectIds.count() > 0)    ;
}

QString CwnCommandLoadObjects::GetLoadAllObjectQuery(){

    QString qstrQuery;
    qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]-(:WMS_DM_OBJECTLIST)-[:hasObjects]->(o:WMS_DM_OBJECT) WHERE id(o) IN %1 "
                        "OPTIONAL MATCH (o)<-[:ObjectCreator]-(uc:User) OPTIONAL MATCH (o)<-[:ObjectModifier]-(um:User) OPTIONAL MATCH (o)-[:Parent]->(op:WMS_DM_OBJECT) WITH o,s,op,uc,um,c "
                        "OPTIONAL MATCH (o)-[:Object_value]->(v)<-[:member_to_value]-(m:WMS_CLASS_MEMBER) "
                        "OPTIONAL MATCH (v)<-[:ValueCreator]-(uc:User) "
                        "OPTIONAL MATCH (v)<-[:ValueModifier]-(um:User) "
                        "OPTIONAL MATCH (v)-[:userValue]->(uv:User) "
                        "OPTIONAL MATCH (v)-[:userGroupValue]->(ugv:Group) "
                        "OPTIONAL MATCH (v)-[:enumValue]->(e:Enum) "
                        "OPTIONAL MATCH (v)-[:objectRefValue]->(ov:WMS_DM_OBJECT)<-[:hasObjects]-(ocv:WMS_DM_OBJECTLIST) "
                        "OPTIONAL MATCH (v)-[:objectListRefValue]->(ocvc:WMS_DM_OBJECTLIST) "
                        "OPTIONAL MATCH (o)-[:Parent]->(op:WMS_DM_OBJECT) "
                        "RETURN id(v), v.type, v.val, v.LastChange, v.filetype, v.filename, id(uc), id(um), id(uv), id(ov), id(ocv), id(ocvc), id(m), m.Keyname, m.Caption, id(o), o.Keyname, o.LastChange, o.Caption, o.Cache, id(op), id(c), id(s), id(ugv), o.Config; ")
                    .arg(qstrObjectInString);

    return qstrQuery;
}

bool CwnCommandLoadObjects::interpretAnswerForLoadObjects(const QVariantList* list)
{
    bool bRet=true;
    CdmObject* pCdmObject = nullptr;

    long lCreatorId      = (list->at(6).isNull())?0:list->at(6).toInt();
    long lLastModifierId = (list->at(7).isNull())?0:list->at(7).toInt();
    long lObjectId       = list->at(15).toInt();
    QString qstrKeyname  = list->at(16).toString();
    QDateTime qdLastChange = list->at(17).toDateTime();
    QString qstrCaption  = list->at(18).toString();
    long lClassId        = list->at(21).toInt();
    long lDataBaseId     = list->at(22).toInt();
    //QString qstrCache    = list->at(126).toString();
    long lParent     = (list->at(20).isNull())?0:list->at(20).toInt();
    QString qstrConfig = (list->at(24).isNull())?"":CwnHelper::base64_decode(list->at(24).toString());

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
    pCdmObject->SetConfig(qstrConfig);
    INFO("Object still has Id " + QString::number(pCdmObject->GetId()));
    CdmDataAccessHelper::AddObjectToObjectList(pCdmObject, m_rpContainer);
    INFO("Object still has Id " + QString::number(pCdmObject->GetId()));
    pCdmObject->ResetNewModified();
    qmLastChange.insert(pCdmObject, qdLastChange);
    qmObjects.insert(pCdmObject->GetId(), pCdmObject);

    INFO("Object with Id " + QString::number(pCdmObject->GetId()) + " creation finished");

    return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForBools(const QVariantList* list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    bool      bValue             = list->at(2).toBool();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();

    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
     return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForBinDoc(const QVariantList* list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    QString   qstrType           = list->at(4).toString();
    QString   qstrFilename       = list->at(5).toString();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if (pCdmObject)
    {
     if (pCdmObject->GetId() != lObjectId)
     {
        if (qmObjects.contains(lObjectId))
        {
           pCdmObject = qmObjects[lObjectId];
        }
        else
        {
           pCdmObject = nullptr;
        }
     }
    }
    else
    {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
        }
        else
        {
            pCdmObject = nullptr;
        }
    }

    if (CHKPTR(pCdmObject))
    {
      //if (CheckType(pCdmObject, qstrKeyname, eDmValueBinaryDocument))
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

    return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForCharDoc(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QString   qstrValue          = CwnHelper::base64_decode(list->at(2).toString());
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if (pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
    }
    else
    {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
            CdmValueCharacterDocument* pCdmCharacterDocument = CreateCharDocValue(
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

    m_eType=eDmValueNone;
    return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForCounters(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(2).toLongLong();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
             CdmValueCounter* pCdmCounter = new CdmValueCounter(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
             pCdmCounter->SetMemberId(lMemberId);
             pCdmCounter->SetCaption(qstrCaption);
             (dynamic_cast<CdmValueLong*>(pCdmCounter))->SetValue(lValue);
             CdmDataAccessHelper::SetCreatorId(pCdmCounter, lCreatorId);
             CdmDataAccessHelper::SetModifierId(pCdmCounter, lModifierId);
             CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmCounter);
             pCdmCounter->SetLastChange(qdtLastChange);
             pCdmObject->ResetNewModified();
         }
     }

    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForDates(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDate     qdValue            = QDate::fromJulianDay(list->at(2).toInt());
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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


    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForDateTimes(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDateTime qdtValue           = QDateTime::fromTime_t(static_cast<time_t>(list->at(2).toInt()));

    if (qdtValue.date() >= QDate(2037,12,31))
    {
       qdtValue = QDateTime();
    }
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
    return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForTimes(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;
    QTime n(0,0);

    long      lId                = list->at(0).toInt();

    QTime     qtValue            = n.addSecs(list->at(2).toInt());
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
    return bRet;
}

bool CwnCommandLoadObjects::interpretAnswerForDoubles(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    double    dValue             = list->at(2).toDouble();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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


    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForFloats(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    float     fValue             = list->at(2).toFloat();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();

    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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

    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForInts(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    int       iValue;
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
                 CdmValueInt* pCdmInt = nullptr;

                 if (m_eType == eDmValueInt || m_eType == eDmValueEnum)
                 {
                    pCdmInt = new CdmValueInt(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                    iValue = list->at(2).toInt();
                 }
                 else if (m_eType == eDmValueUser)
                 {
                    pCdmInt = new CdmValueUser(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                    iValue = list->at(8).toInt();
                 }
                 else if (m_eType == eDmValueUserGroup)
                 {
                    pCdmInt = new CdmValueUserGroup(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
                    iValue = list->at(23).toInt();
                 }
                 else
                 {
                     //Error should not happen
                     iValue=0;
                     return 0;
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
    m_eType=eDmValueNone;
    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForLongs(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(2).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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

    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForObjectRefs(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lValue             = list->at(9).toInt();
    long      lObjectListId      = list->at(10).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();
    // TODO add Keyname for object and container


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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
             CdmValueObjectRef* pCdmObjectRef = new CdmValueObjectRef(pCdmObject->GetSchemeId(), lId, qstrKeyname, pCdmObject);
             pCdmObjectRef->SetMemberId(lMemberId);
             pCdmObjectRef->SetCaption(qstrCaption);
             // TODO add Keyname for object and container
             pCdmObjectRef->SetValue(lObjectListId, lValue, "", "");
             CdmDataAccessHelper::SetCreatorId(pCdmObjectRef, lCreatorId);
             CdmDataAccessHelper::SetModifierId(pCdmObjectRef, lModifierId);
             CdmDataAccessHelper::AddValueToObject(pCdmObject, pCdmObjectRef);
             pCdmObjectRef->SetLastChange(qdtLastChange);
             pCdmObject->ResetNewModified();
         }
     }


    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForObjectListRefs(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lValue             = list->at(11).toInt();
    long      lMemberId          = list->at(12).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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

    return bRet;

}

bool CwnCommandLoadObjects::interpretAnswerForStrings(const QVariantList *list)
{
    CdmObject* pCdmObject = nullptr;
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QString   qstrValue          = list->at(2).toString();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    long      lMemberId          = list->at(12).toInt();
    long      lObjectId          = list->at(15).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();


    if(pCdmObject)
    {
        if (pCdmObject->GetId() != lObjectId)
        {
            if (qmObjects.contains(lObjectId))
            {
                pCdmObject = qmObjects[lObjectId];
            }
            else
            {
                pCdmObject = nullptr;
            }
        }
     }
     else
     {
        if (qmObjects.contains(lObjectId))
        {
            pCdmObject = qmObjects[lObjectId];
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


    return bRet;

}

void CwnCommandLoadObjects::interpretAnswer(QVariant &Ret)
{
    //qDebug() << answer;
    bool bRet = true;

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
        const QVariantList* dataListCon = CwnCommandBase::getDataListPtr();

        if(dataListCon->count()>0)
        {
            QList<int> objectList;

            QList<QVariant>::ConstIterator it;
            for(it=dataListCon->begin();it!=dataListCon->end();it++) // loading each class
            {
                const QVariantMap* rowTemp = static_cast<const QVariantMap*>(it->data());
                const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());

                if(list->count()>0){

                    if(!objectList.contains(list->at(15).toInt()))
                    {
                        objectList.append(list->at(15).toInt());
                        bRet = bRet && interpretAnswerForLoadObjects(list);
                    }

                    switch(list->at(1).toInt()){
                        case eDmValueBool:
                            bRet = bRet && interpretAnswerForBools(list);
                            break;
                        case eDmValueBinaryDocument:
                            bRet = bRet && interpretAnswerForBinDoc(list);
                            break;
                        case eDmValueCharacterDocument:
                            m_eType=eDmValueCharacterDocument;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueListInt:
                            m_eType=eDmValueListInt;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueListDouble:
                            m_eType=eDmValueListDouble;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueListString:
                            m_eType=eDmValueListString;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictStringInt:
                            m_eType=eDmValueDictStringInt;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictStringString:
                            m_eType=eDmValueDictStringString;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictStringDouble:
                            m_eType=eDmValueDictStringDouble;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictIntString:
                            m_eType=eDmValueDictIntString;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictIntInt:
                            m_eType=eDmValueDictIntInt;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueDictIntDouble:
                            m_eType=eDmValueDictIntDouble;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueListObjects:
                            m_eType=eDmValueListObjects;
                            bRet = bRet && interpretAnswerForCharDoc(list);
                            break;
                        case eDmValueCounter:
                            bRet = bRet && interpretAnswerForCounters(list);
                            break;
                        case eDmValueDate:
                            bRet = bRet && interpretAnswerForDates(list);
                            break;
                        case eDmValueDateTime:
                            bRet = bRet && interpretAnswerForDateTimes(list);
                            break;
                        case eDmValueDouble:
                            bRet = bRet && interpretAnswerForDoubles(list);
                            break;
                        case eDmValueFloat:
                            bRet = bRet && interpretAnswerForFloats(list);
                            break;
                        case eDmValueInt:
                            m_eType=eDmValueInt;
                            bRet = bRet && interpretAnswerForInts(list);
                            break;
                        case eDmValueUser:
                            m_eType=eDmValueUser;
                            bRet = bRet && interpretAnswerForInts(list);
                            break;
                        case eDmValueUserGroup:
                            m_eType=eDmValueUserGroup;
                            bRet = bRet && interpretAnswerForInts(list);
                            break;
                        case eDmValueEnum:
                            m_eType=eDmValueEnum;
                            bRet = bRet && interpretAnswerForInts(list);
                            break;
                        case eDmValueLong:
                            bRet = bRet && interpretAnswerForLongs(list);
                            break;
                        case eDmValueObjectRef:
                            bRet = bRet && interpretAnswerForObjectRefs(list);
                            break;
                        case eDmValueContainerRef:
                            bRet = bRet && interpretAnswerForObjectListRefs(list);
                            break;
                        case eDmValueString:
                            bRet = bRet && interpretAnswerForStrings(list);
                            break;
                        case eDmValueTime:
                            bRet = bRet && interpretAnswerForTimes(list);
                            break;
                        }
                }
            }
        }
        else
            INFO("Container has no objects.");

        if(bRet)
        {
            Ret=1;
        }
        else
        {
            Ret=-1;
            ERR("Could not load a value or an object.");

        }
    }
}

int CwnCommandLoadObjects::Execute()
{
   long lRet = CdmLogging::eDmObjectAccessError;
   QString qstrQuery;

   if (m_qvlObjectIds.count() > 0)
   {
      qstrObjectInString = GetDataAccess()->GenerateInString(m_qvlObjectIds);

      qstrQuery = GetLoadAllObjectQuery();

      QString payload = createJson(qstrQuery);
      //ERR(payload);
      queryCausedError = payload;
      ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
      QVariant Ret;
      interpretAnswer(Ret);
      lRet = Ret.toInt();

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

   return lRet;
}

CdmValueCharacterDocument* CwnCommandLoadObjects::CreateCharDocValue(
                                                            long p_lDatabaseId,
                                                            long p_lId,
                                                            QString p_qstrKeyname,
                                                            CdmObject* p_pCdmObjectOwner)
{
   CdmValueCharacterDocument* pDocument = nullptr;


   switch (m_eType)
   {
   case eDmValueCharacterDocument:
      pDocument = new CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueListInt:
      pDocument = new CdmValueListInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueListDouble:
      pDocument = new CdmValueListDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueListString:
      pDocument = new CdmValueListString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictStringInt:
      pDocument = new CdmValueDictStringInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictStringString:
      pDocument = new CdmValueDictStringString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictStringDouble:
      pDocument = new CdmValueDictStringDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictIntInt:
      pDocument = new CdmValueDictIntInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictIntString:
      pDocument = new CdmValueDictIntString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueDictIntDouble:
      pDocument = new CdmValueDictIntDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   case eDmValueListObjects:
      pDocument = new CdmValueListObjects(p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObjectOwner);
      break;
   default:
      ERR("Invalid Type");
      break;
   }

   return pDocument;
}


