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
#include "CwnCommandLoadSingleObject.h"

#include "CwnCommandStdHeader.h"

CwnCommandLoadSingleObject::CwnCommandLoadSingleObject(long p_lContainerId, long p_lObjectId, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_lObjectId(p_lObjectId),
      m_rpObject(nullptr)
{
}

CwnCommandLoadSingleObject::CwnCommandLoadSingleObject(long p_lContainerId, QString p_qstrKeyname, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_lContainerId(p_lContainerId),
      m_lObjectId(-1),
      m_qstrKeyname(p_qstrKeyname),
      m_rpObject(nullptr)
{
}

CwnCommandLoadSingleObject::~CwnCommandLoadSingleObject()
{

}

CdmObject *CwnCommandLoadSingleObject::GetResult()
{
    return m_rpObject;
}

bool CwnCommandLoadSingleObject::CheckValid()
{
    return ((m_lContainerId > 0 && m_lObjectId > 0) || !m_qstrKeyname.isEmpty());
}

QString CwnCommandLoadSingleObject::GetLoadAllObjectQuery(){

    QString qstrQuery;

    if (m_lObjectId > 0)
    {
        qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]-(:WMS_DM_OBJECTLIST)-[:hasObjects]->(o:WMS_DM_OBJECT) WHERE id(o)=%1 "
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
                .arg(m_lObjectId);
    }
    else
    {
        qstrQuery = QString("MATCH (s:Scheme)-[:hasClass]->(c:Class)-[:hasObjectContainer]-(:WMS_DM_OBJECTLIST)-[:hasObjects]->(o:WMS_DM_OBJECT) WHERE o.Keyname=\'%1\' "
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
                .arg(m_qstrKeyname);
    }
    return qstrQuery;
}

bool CwnCommandLoadSingleObject::interpretAnswerForLoadObjects(const QVariantList* list)
{
    bool bRet=true;

    if(m_rpObject)
    {
        ERR("Object must be null");
    }

    long lObjectId       = list->at(15).toInt();
    QString qstrKeyname  = list->at(16).toString();
    QDateTime qdLastChange = list->at(17).toDateTime();
    //long lCreatorId      = (list->at(6).isNull())?0:list->at(6).toInt();
    //long lLastModifierId = (list->at(7).isNull())?0:list->at(7).toInt();
    QString qstrCaption  = list->at(18).toString();
    long lClassId        = list->at(21).toInt();
    long lDataBaseId     = list->at(22).toInt();
    //QString qstrCache    = list->at(126).toString();
    long lParent     = (list->at(20).isNull())?0:list->at(20).toInt();
    QString qstrConfig = (list->at(24).isNull())?"":CwnHelper::base64_decode(list->at(24).toString());

    m_rpObject = CdmDataAccessHelper::CreateObject(lDataBaseId,
                                                   lObjectId,
                                                   lClassId,
                                                   m_lContainerId);

    m_rpObject->SetCaption(qstrCaption);
    m_rpObject->SetParent(lParent);
    CdmDataAccessHelper::SetKeyname(m_rpObject, qstrKeyname);
    //CdmDataAccessHelper::SetCreatorId(m_rpObject, lCreatorId);
    //CdmDataAccessHelper::SetModifierId(m_rpObject, lLastModifierId);

    CdmDataAccessHelper::SetValid(m_rpObject);
    m_rpObject->SetLastChange(qdLastChange);
    m_rpObject->SetConfig(qstrConfig);
    m_rpObject->ResetNewModified();

    INFO("Object with Id " + QString::number(m_lObjectId) + " found");

    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForBools(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    bool      bValue             = list->at(2).toBool();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForBinDoc(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QString   qstrType           = list->at(4).toString();
    QString   qstrFilename       = list->at(5).toString();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //if (CheckType(pCdmObject, qstrKeyname, eDmValueBinaryDocument))
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


    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForCharDoc(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QString   qstrValue          = CwnHelper::base64_decode(list->at(2).toString());
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    // more than one type is read here
    //if (CheckType(pCdmObject, qstrKeyname, eDmValueCharacterDocument))
    {
        CdmValueCharacterDocument* pCdmCharacterDocument = CreateCharDocValue(
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


    m_eType=eDmValueNone;
    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForCounters(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(2).toInt();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();



    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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


    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForDates(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDate     qdValue            = QDate::fromJulianDay(list->at(2).toInt());
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();


    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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


    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForDateTimes(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QDateTime qdtValue           = QDateTime::fromTime_t(static_cast<time_t>(list->at(2).toInt()));

    if (qdtValue.date() >= QDate(2037,12,31))
    {
        qdtValue = QDateTime();
    }
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForTimes(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QTime n(0,0);
    QTime     qtValue            = n.addSecs(list->at(2).toInt());
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForDoubles(const QVariantList* list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    double    dValue             = list->at(2).toDouble();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForFloats(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    float     fValue             = list->at(2).toFloat();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();



    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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


    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForInts(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    int       iValue             = 0;
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
    {
        CdmValueInt* pCdmInt = nullptr;

        if (m_eType == eDmValueInt)
        {
            pCdmInt = new CdmValueInt(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
            iValue = list->at(2).toInt();
        }
        else if (m_eType == eDmValueUser)
        {
            pCdmInt = new CdmValueUser(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
            iValue = list->at(8).toInt();
        }
        else if (m_eType == eDmValueUserGroup)
        {
            pCdmInt = new CdmValueUserGroup(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
            iValue = list->at(23).toInt();
        }
        else if (m_eType == eDmValueEnum)
        {
            pCdmInt = new CdmValueEnum(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);
            iValue = list->at(2).toInt();
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

    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForLongs(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(2).toInt();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();


    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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


    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForObjectRefs(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(9).toInt();
    long      lObjectListId      = list->at(10).toInt();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();
    // TODO Read Object and COntainer Keynames


    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
    {
        CdmValueObjectRef* pCdmObjectRef = new CdmValueObjectRef(m_rpObject->GetSchemeId(), lId, qstrKeyname, m_rpObject);

        pCdmObjectRef->SetMemberId(lMemberId);
        pCdmObjectRef->SetCaption(qstrCaption);
        // TODO Read Object and COntainer Keynames
        pCdmObjectRef->SetValue(lObjectListId, lValue, "", "");
        CdmDataAccessHelper::SetCreatorId(pCdmObjectRef, lCreatorId);
        CdmDataAccessHelper::SetModifierId(pCdmObjectRef, lModifierId);
        CdmDataAccessHelper::AddValueToObject(m_rpObject, pCdmObjectRef);
        pCdmObjectRef->SetLastChange(qdtLastChange);
        m_rpObject->ResetNewModified();
    }


    return bRet;
}

bool CwnCommandLoadSingleObject::interpretAnswerForObjectListRefs(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    long      lValue             = list->at(11).toInt();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();


    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;

}

bool CwnCommandLoadSingleObject::interpretAnswerForStrings(const QVariantList *list)
{
    bool bRet=true;

    long      lId                = list->at(0).toInt();
    QString   qstrValue          = list->at(2).toString();
    long      lMemberId          = list->at(12).toInt();
    QDateTime qdtLastChange      = list->at(3).toDateTime();
    long      lCreatorId         = (list->at(6).isNull())?0:list->at(6).toInt();
    long      lModifierId        = (list->at(7).isNull())?0:list->at(7).toInt();
    QString   qstrKeyname        = list->at(13).toString();
    QString   qstrCaption        = list->at(18).toString();

    //  if (CheckType(pCdmObject, qstrKeyname, eDmValueBool))
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

    return bRet;

}

void CwnCommandLoadSingleObject::interpretAnswer(QVariant &Ret)
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

int CwnCommandLoadSingleObject::Execute()
{
    long lRet = CdmLogging::eDmObjectAccessError;
    QString qstrQuery;

    qstrQuery = GetLoadAllObjectQuery();
    QString payload = createJson(qstrQuery);
    //qDebug() << payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    lRet = Ret.toInt();


    return static_cast<int>(lRet);
}

CdmValueCharacterDocument* CwnCommandLoadSingleObject::CreateCharDocValue(
        long p_lDatabaseId,
        long p_lId,
        QString p_qstrKeyname)
{
    CdmValueCharacterDocument* pDocument = nullptr;


    switch (m_eType)
    {
    case eDmValueCharacterDocument:
        pDocument = new CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueListInt:
        pDocument = new CdmValueListInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueListDouble:
        pDocument = new CdmValueListDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueListString:
        pDocument = new CdmValueListString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictStringInt:
        pDocument = new CdmValueDictStringInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictStringString:
        pDocument = new CdmValueDictStringString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictStringDouble:
        pDocument = new CdmValueDictStringDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictIntInt:
        pDocument = new CdmValueDictIntInt(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictIntString:
        pDocument = new CdmValueDictIntString(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueDictIntDouble:
        pDocument = new CdmValueDictIntDouble(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    case eDmValueListObjects:
        pDocument = new CdmValueListObjects(p_lDatabaseId, p_lId, p_qstrKeyname, m_rpObject);
        break;
    default:
        ERR("Invalid Type");
        break;
    }

    return pDocument;
}


