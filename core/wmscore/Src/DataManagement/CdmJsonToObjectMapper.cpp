#include <QDebug>

#include "CwmsUtilities.h"

#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectAdaptor.h"
#include "CdmValueDateTime.h"
#include "CdmValueDate.h"
#include "CdmJsonToObjectMapper.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmScheme.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmValue.h"
#include "CdmValueTime.h"
#include "CwmsJson.h"
#include "CdmValueEnum.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueDictStringString.h"
#include "CdmValueBool.h"
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "wmsdefines.h"

CdmJsonToObjectMapper::CdmJsonToObjectMapper()
{

}

bool CdmJsonToObjectMapper::ConvertJson(CdmObject *object, QString& body) {

    CwmsJson json;
    QVariantMap qvValues = json.parse(body).toMap();
    return ConvertVariantMap(object, qvValues);
}

bool CdmJsonToObjectMapper::ConvertVariantMap(CdmObject *object, QVariantMap& qvValues)
{
    CdmObjectAdaptor adaptor(object);
    QVariantMap::iterator qvmIt = qvValues.begin();
    QVariantMap::iterator qvmItEnd = qvValues.end();

    for (; qvmIt != qvmItEnd; ++qvmIt)
    {
        QString key = qvmIt.key();
        const CdmClass *cls = object->GetClass();
        const CdmMember *pMember = cls->FindMember(key);

        if(!pMember)
        {
            ERR(QString("Member %1 not found in Class %2").arg(key).arg(cls->GetKeyname()));
            continue;
        }

        const EdmValueType dataType = pMember->GetValueType();
        QVariant value = qvmIt.value();

        switch (dataType)
        {
        case eDmValueString:
        case eDmValueListString:
        case eDmValueListInt:
        case eDmValueListDouble:
        case eDmValueDictIntDouble:
        case eDmValueDictIntInt:
        case eDmValueDictIntString:
        case eDmValueDictStringDouble:
        case eDmValueDictStringInt:
        case eDmValueDictStringString:
        case eDmValueUserGroup:
        case eDmValueUser:
        case eDmValueBool:
        case eDmValueDate:
        case eDmValueInt:
        case eDmValueLong:
        case eDmValueFloat:
        case eDmValueCounter:
        case eDmValueTime:
        case eDmValueDateTime:
        case eDmValueEnum:
        case eDmValueCharacterDocument:
        case eDmValueDouble:
        case eDmValueBinaryDocument:
        case eDmValueObjectRef:
        {
            CdmValue *pValue = object->GetValue(key);
            if (CHKPTR(pValue))
            {
                pValue->SetValueVariant(value);
            }
            break;
        }
        case eDmValueContainerRef:
        {
            if(pMember->IsOwner())
            {
                CdmObjectContainer *container = adaptor.GetContainerRefValue(key);
                container->DeleteAllObjects();
                ConvertList(container, value);
            }

            break;
        }
        case eDmValueListObjects:
        {
            QVariantList qvlValues = value.toList();
            QVariantList qvlSelfLinks;
            for(auto qvmObj : qvlValues)
            {
                QVariantMap qvm = qvmObj.toMap();
                qvlSelfLinks.append(GetSelfLink(qvm));
            }

            adaptor.SetListObjectsValues(key, qvlSelfLinks);
            break;
        }
        default:
            ERR(QString("%1 not supported").arg(pMember->GetValueTypeAsString()));
            break;
        }
    }

    return SUCCESSFULL(object->Commit());
}

bool CdmJsonToObjectMapper::ConvertList(CdmObjectContainer *container,QVariant& value)
{

    const QList<QVariant> qvValues = value.toList();
    for(QVariant variant: qvValues) {
        QVariantMap map = variant.toMap();
        CdmObject *object = container->CreateNewObject();
        ConvertVariantMap(object, map);
    }

    return true;
}

QString CdmJsonToObjectMapper::GetSelfLink(QVariantMap& qvmMap)
{
    QVariant qvl = qvmMap[WMS_LINKS];

    if(!qvl.isNull())
    {
        for(auto e : qvl.toList())
        {
            QVariantMap qvmEntry = e.toMap();
            if(!qvmEntry.isEmpty()) {
                QVariant qvRel = qvmEntry[WMS_REL];
                if(!qvRel.isNull() && WMS_SELF == qvRel.toString())
                {
                    return qvmEntry[WMS_HREF].toString();
                }
            }
        }
    }

    return "";
}
