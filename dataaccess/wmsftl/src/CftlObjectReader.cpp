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

// Own Includes
#include "CftlObjectReader.h"

qint64 CftlObjectReader::ReadValues(CftlContainerTableSelect& selector, QSqlQuery& cQSqlQuery, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    QMap<qint64, CdmMember*>& qmMembers = selector.GetMemberMap();
    QMapIterator<qint64, CdmMember*> qmIt(qmMembers);
    int iPos = selector.GetValueStartPos();


    while (qmIt.hasNext())
    {
        qmIt.next();
        CdmMember* pMember = qmIt.value();

        switch(pMember->GetValueType())
        {
            case eDmValueBinaryDocument:
            {
                lRet = ReadBinaryDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueBool:
            {
                lRet = ReadBool(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueCharacterDocument:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueListInt:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueListDouble:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueListString:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictStringInt:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictStringString:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictStringDouble:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictIntInt:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictIntString:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDictIntDouble:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueListObjects:
            {
                lRet = ReadCharacterDocument(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
                // End of CharDoc derived types
            case eDmValueCounter:
            {
                lRet = ReadCounter(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDate:
            {
                lRet = ReadDate(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDateTime:
            {
                lRet = ReadDateTime(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueDouble:
            {
                lRet = ReadDouble(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueFloat:
            {
                lRet = ReadFloat(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueInt:
            {
                lRet = ReadInt(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueUser:
            {
                lRet = ReadInt(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueLong:
            {
                lRet = ReadLong(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueObjectRef:
            {
                lRet = ReadObjectRef(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueContainerRef:
            {
                lRet = ReadContainerRef(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueString:
            {
                lRet = ReadString(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueTime:
            {
                lRet = ReadTime(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueUserGroup:
            {
                lRet = ReadInt(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
            case eDmValueEnum:
            {
                lRet = ReadInt(cQSqlQuery, iPos, pMember, p_pObject);
                break;
            }
        default:
            INFO("Not persistent member")
        }
    }

    return lRet;
}

int CftlObjectReader::ReadBinaryDocument(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {

        QString qstrFilename = p_rQuery.value(p_riPos++).toString();
        QFileInfo qFileInfo(qstrFilename);
        QString qstrType = qFileInfo.suffix();
        CdmValueBinaryDocument* pValue = new CdmValueBinaryDocument(p_pObject->GetSchemeId(),
                                                                    p_pMember->GetId(),
                                                                    p_pMember->GetKeyname(),
                                                                    qstrFilename,
                                                                    qstrType,
                                                                    p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        p_riPos++; // must be incremented because bin doc consists of two columns.
        lRet = EC(eDmOk);
    }

    return lRet;
}

void CftlObjectReader::SetMemberDataToValue(CdmValue* p_pValue, const CdmMember* p_pMember)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pMember))
    {
        p_pValue->SetMemberId(p_pMember->GetId());
        p_pValue->SetCaption(p_pMember->GetCaption());
    }
}

void CftlObjectReader::SetObjectDataToValue(CdmValue* p_pValue, CdmObject* p_pObject)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pObject))
    {
        CdmDataAccessHelper::SetCreatorId(p_pValue, p_pObject->GetCreatorId());
        CdmDataAccessHelper::SetModifierId(p_pValue, p_pObject->GetModifierId());
        CdmDataAccessHelper::AddValueToObject(p_pObject, p_pValue);
        QDateTime qdtLastChanged = p_pObject->GetLastChange();
        p_pValue->SetLastChange(qdtLastChanged);
        p_pObject->ResetNewModified();
    }
}

int CftlObjectReader::ReadBool(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        bool bValue = p_rQuery.value(p_riPos++).toBool();

        CdmValueBool* pValue = new CdmValueBool(p_pObject->GetSchemeId(),
                                                  p_pMember->GetId(),
                                                  p_pMember->GetKeyname(),
                                                  p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(bValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadCharacterDocument(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {

        QString qstrCharDoc = p_rQuery.value(p_riPos++).toString();
        CdmValueCharacterDocument* pValue = CreateCharDocValue(p_pMember->GetValueType(),
                                                               p_pObject->GetSchemeId(),
                                                               p_pMember->GetId(),
                                                               p_pMember->GetKeyname(),
                                                               p_pObject);


        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(qstrCharDoc);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadCounter(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
       qint64 lValue = p_rQuery.value(p_riPos++).toInt();

        CdmValueCounter* pValue = new CdmValueCounter(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);


        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->CdmValueLong::SetValue(lValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadDate(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        QDate qdValue = p_rQuery.value(p_riPos++).toDate();

        CdmValueDate* pValue = new CdmValueDate(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(qdValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadDateTime(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        QDateTime qdValue = p_rQuery.value(p_riPos++).toDateTime();

        CdmValueDateTime* pValue = new CdmValueDateTime(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(qdValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadDouble(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        double dValue = p_rQuery.value(p_riPos++).toDouble();

        CdmValueDouble* pValue = new CdmValueDouble(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(dValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadFloat(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        float fValue = p_rQuery.value(p_riPos++).toFloat();

        CdmValueFloat* pValue = new CdmValueFloat(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(fValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadInt(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        QVariant qvValue = p_rQuery.value(p_riPos++);
        int iValue = qvValue.toInt();

        CdmValueInt* pValue = new CdmValueInt(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(iValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadLong(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
       qint64 lValue = p_rQuery.value(p_riPos++).toInt();

        CdmValueLong* pValue = new CdmValueLong(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(lValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadObjectRef(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
       qint64 lContainerId = p_rQuery.value(p_riPos++).toInt();
       qint64 lObjectId = p_rQuery.value(p_riPos++).toInt();
        QString qstrObjectKeyname = p_rQuery.value(p_riPos++).toString();
        QString qstrContainerKeyname = p_rQuery.value(p_riPos++).toString();

        CdmValueObjectRef* pValue = new CdmValueObjectRef(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(lContainerId, lObjectId, qstrObjectKeyname, qstrContainerKeyname);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadContainerRef(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
       qint64 lContainerId = p_rQuery.value(p_riPos++).toInt();
        QString qstrContainerKeyname = p_rQuery.value(p_riPos++).toString();

        CdmValueContainerRef* pValue = new CdmValueContainerRef(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(lContainerId);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadString(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        QString qstrValue = p_rQuery.value(p_riPos++).toString();

        CdmValueString* pValue = new CdmValueString(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(qstrValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

int CftlObjectReader::ReadTime(QSqlQuery& p_rQuery, int& p_riPos, CdmMember* p_pMember, CdmObject* p_pObject)
{
   qint64 lRet = CdmLogging::eDmObjectAccessError;

    if (CHKPTR(p_pMember) && CHKPTR(p_pObject))
    {
        QTime qtValue = p_rQuery.value(p_riPos++).toTime();

        CdmValueTime* pValue = new CdmValueTime(p_pObject->GetSchemeId(),
                                                      p_pMember->GetId(),
                                                      p_pMember->GetKeyname(),
                                                      p_pObject);

        SetMemberDataToValue(pValue, p_pMember);
        SetObjectDataToValue(pValue, p_pObject);
        pValue->SetValue(qtValue);
        lRet = EC(eDmOk);
    }

    return lRet;
}

CdmValueCharacterDocument* CftlObjectReader::CreateCharDocValue(EdmValueType p_eType,
                                                                     qint64 p_lDatabaseId,
                                                                     qint64 p_lId,
                                                                      QString p_qstrKeyname,
                                                                      CdmObject* p_pObjectOwner)
{
    CdmValueCharacterDocument* pDocument = nullptr;


    switch (p_eType)
    {
    case eDmValueCharacterDocument:
        pDocument = new CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueListInt:
        pDocument = new CdmValueListInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueListDouble:
        pDocument = new CdmValueListDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueListString:
        pDocument = new CdmValueListString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictStringInt:
        pDocument = new CdmValueDictStringInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictStringString:
        pDocument = new CdmValueDictStringString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictStringDouble:
        pDocument = new CdmValueDictStringDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictIntInt:
        pDocument = new CdmValueDictIntInt(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictIntString:
        pDocument = new CdmValueDictIntString(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueDictIntDouble:
        pDocument = new CdmValueDictIntDouble(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    case eDmValueListObjects:
        pDocument = new CdmValueListObjects(p_lDatabaseId, p_lId, p_qstrKeyname, p_pObjectOwner);
        break;
    default:
        ERR("Invalid Type");
        break;
    }

    return pDocument;
}
