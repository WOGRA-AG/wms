// WMSCORE Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmValue.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CftlHelper.h"
#include "CftlDialect.h"
#include "CftlInterface.h"
#include "CftlContainerTableUpdate.h"

CftlContainerTableUpdate::CftlContainerTableUpdate(CdmObject* p_Object, CftlDialect* p_ppDialect)
    : CftlContainerTableBase(p_ppDialect),
      m_rpObject(p_Object)
{

}

CftlContainerTableUpdate::~CftlContainerTableUpdate()
{

}

qint64 CftlContainerTableUpdate::Execute(CftlInterface *p_pInterface)
{
   qint64 lRet = CdmLogging::eDmOk;

    if (CheckValid() && CHKPTR(p_pInterface))
    {
        const CdmClass* pClass = m_rpObject->GetClass();

        if (CHKPTR(pClass))
        {
            QString qstrTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
            BuildFieldValuesForUpdate(p_pInterface);
            QString qstrSql = QString("update %1 set %2 where %3")
                    .arg(qstrTableName)
                    .arg(m_qstrSetArea)
                    .arg(BuildWhereCondition());
            QSqlQuery query(p_pInterface->GetSqlDatabase());
            query.prepare(qstrSql);

            QMapIterator<QString, QVariant> qmIt(m_qvValueBindings);

            while (qmIt.hasNext())
            {
                qmIt.next();
                query.bindValue(qmIt.key(), qmIt.value());
            }

            lRet = p_pInterface->ExecuteQuery(query);

            if (SUCCESSFULL(lRet))
            {
                INFO("Object successfully updated");
            }
        }
    }

    return lRet;
}

void CftlContainerTableUpdate::BuildFieldValuesForUpdate(CftlInterface* p_pInterface)
{
    QMap<QString, CdmValue*> qmValues;
    m_rpObject->GetValueMap(qmValues);

    QMapIterator<QString, CdmValue*> qmIt(qmValues);
    bool bFirst = true;

    while (qmIt.hasNext())
    {
        qmIt.next();
        CdmValue* pValue = qmIt.value();

        if (CHKPTR(pValue) &&
            (pValue->IsModified() || pValue->IsNew()) &&
            pValue->GetValueType() != eDmValueFormula &&
            pValue->GetMember()->IsPersistent())
        {
            if (!bFirst)
            {
                m_qstrSetArea += ", ";
            }
            else
            {
                bFirst = false;
            }

            AddUpdateValue(pValue, p_pInterface);
        }
    }

    AddModifierFields();
}

void CftlContainerTableUpdate::AddModifierFields()
{
    if (!m_qvValueBindings.isEmpty())
    {
        m_qstrSetArea += ", ";
    }

    m_qstrSetArea += FTL_LAST_MODIFIED  " = :" FTL_LAST_MODIFIED;
    m_qvValueBindings.insert(":" FTL_LAST_MODIFIED, QDateTime::currentDateTime());

    m_qstrSetArea += ", ";
    m_qstrSetArea += FTL_MODIFIER_ID  " = :" FTL_MODIFIER_ID;
    m_qvValueBindings.insert(":" FTL_MODIFIER_ID, CdmSessionManager::GetSessionManager()->GetCurrentUserId());

    m_qstrSetArea += ", ";
    m_qstrSetArea += FTL_OBJECT_KEYNAME_FIELD_NAME  " = :" FTL_OBJECT_KEYNAME_FIELD_NAME;
    m_qvValueBindings.insert(":" FTL_OBJECT_KEYNAME_FIELD_NAME, m_rpObject->GetKeyname());

    m_qstrSetArea += ", ";
    m_qstrSetArea += FTL_OBJECT_CAPTION_FIELD_NAME  " = :" FTL_OBJECT_CAPTION_FIELD_NAME;
    m_qvValueBindings.insert(":" FTL_OBJECT_CAPTION_FIELD_NAME, m_rpObject->GetCaption());

    CdmObject* pParent = m_rpObject->GetParent();

    if (pParent != nullptr)
    {
        m_qstrSetArea += ", ";
        m_qstrSetArea += FTL_PARENT  " = :" FTL_PARENT;
        m_qvValueBindings.insert(":" FTL_PARENT,pParent->GetId());
    }

}

void CftlContainerTableUpdate::AddUpdateValue(CdmValue* p_pValue, CftlInterface* p_pInterface)
{
    if (CHKPTR(p_pValue))
    {
        const CdmMember* pMember = p_pValue->GetMember();

        if (CHKPTR(pMember) && pMember->IsPersistent())
        {
            QString qstrMajorFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();

            switch (pMember->GetValueType())
            {
            case eDmValueBinaryDocument:
            {
                QString qstrFieldName = qstrMajorFieldName + FTL_BIN_DOC_FILENAME_SUFFIX;
                m_qstrSetArea += qstrFieldName + " = " + ":" + qstrFieldName + ", ";

                qstrFieldName = qstrMajorFieldName + FTL_BIN_DOC_CONTENT_SUFFIX;
                m_qstrSetArea += qstrFieldName + " = " + ":" + qstrFieldName;
                break;
            }
            case eDmValueObjectRef:
            {
                QString qstrFieldName = qstrMajorFieldName + FTL_OBJECT_REF_CONTAINER_SUFFIX;
                m_qstrSetArea += qstrFieldName + " = "+  ":" + qstrFieldName + ", ";

                qstrFieldName = qstrMajorFieldName + FTL_OBJECT_REF_OBJECT_SUFFIX;
                m_qstrSetArea += qstrFieldName + " = "+  ":" + qstrFieldName;

                break;
            }
            default:
                QString qstrFieldName = qstrMajorFieldName;
                m_qstrSetArea += qstrFieldName + " = "+  ":" +qstrFieldName;
                break;
            }

            CftlHelper::FillFieldValues(":" + qstrMajorFieldName, pMember, m_rpObject, m_qvValueBindings, p_pInterface);
        }
    }
}

QString CftlContainerTableUpdate::BuildWhereCondition()
{
    QString qstrRet;

    qstrRet = FTL_OBJECT_ID_FIELD_NAME " = :" FTL_OBJECT_ID_FIELD_NAME;
    m_qvValueBindings.insert(":" FTL_OBJECT_ID_FIELD_NAME, m_rpObject->GetId());
    return qstrRet;
}

QStringList CftlContainerTableUpdate::GenerateSqls()
{
    QStringList list;
    return list;
}

bool CftlContainerTableUpdate::IsValid()
{
    return (m_rpObject != nullptr);
}
