
// WMSCORE Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmSessionManager.h"

// Own Includes
#include "CftlHelper.h"
#include "CftlDialect.h"
#include "CftlInterface.h"
#include "CftlContainerTableInsert.h"

CftlContainerTableInsert::CftlContainerTableInsert(CdmObject* p_pObject, CftlDialect* p_ppDialect)
    : CftlContainerTableBase(p_ppDialect),
      m_rpObject(p_pObject),
      m_lObjectId(-1)

{
}

CftlContainerTableInsert::~CftlContainerTableInsert()
{
}

long CftlContainerTableInsert::Execute(CftlInterface *p_pInterface)
{
    long lRet = CdmLogging::eDmOk;
    if (CheckValid() && CHKPTR(p_pInterface))
    {
        const CdmClass* pClass = m_rpObject->GetClass();

        if (CHKPTR(pClass))
        {
            QString qstrTableName = pClass->GetConfigItem(FTL_CLASS_TABLE_NAME).toString();
            BuildFieldValuesForInsert(pClass, p_pInterface);
            QString qstrQuery = "insert into " + qstrTableName + " (" +m_qstrFields + ") values(" + m_qstrFieldPlaceholders + ")";
            QSqlQuery query(p_pInterface->GetSqlDatabase());
            query.prepare(qstrQuery);

            QMapIterator<QString, QVariant> qmIt(m_qvmFieldValues);

            while (qmIt.hasNext())
            {
                qmIt.next();
                query.bindValue(qmIt.key(), qmIt.value());
            }

            lRet = p_pInterface->ExecuteQuery(query);

            if (SUCCESSFULL(lRet))
            {
                ReadCreatedObjectId(p_pInterface, qstrTableName);
            }
        }
    }

    return lRet;
}

void CftlContainerTableInsert::ReadCreatedObjectId(CftlInterface *p_pInterface, QString p_qstrClassTableName)
{
    QSqlQuery query(p_pInterface->GetSqlDatabase());
    query.prepare("select " FTL_OBJECT_ID_FIELD_NAME " from " + p_qstrClassTableName + " where " FTL_CREATOR_ID " = :" FTL_CREATOR_ID " and " FTL_CREATED " = :" FTL_CREATED);
    query.bindValue(":" FTL_CREATOR_ID, m_qvmFieldValues[":" FTL_CREATOR_ID]);
    query.bindValue(":" FTL_CREATED, m_qvmFieldValues[":" FTL_CREATED]);

    if (SUCCESSFULL(p_pInterface->ExecuteQuery(query)))
    {
        if (query.first())
        {
            m_lObjectId = query.value(FTL_OBJECT_ID_FIELD_NAME).toInt();
        }
    }
}

void CftlContainerTableInsert::BuildFieldValuesForInsert(const CdmClass* p_pClass, CftlInterface *p_pInterface)
{
    QMap<long, CdmMember*> qmMembers;
    p_pClass->GetMemberMap(qmMembers);

    QMapIterator<long, CdmMember*> qmIt(qmMembers);
    bool bFirst = true;

    while (qmIt.hasNext())
    {
        qmIt.next();

        if (!bFirst)
        {
            m_qstrFieldPlaceholders += ", ";
            m_qstrFields += ", ";
        }
        else
        {
            bFirst = false;
        }

        CdmMember* pMember = qmIt.value();

        if (CHKPTR(pMember) && pMember->IsPersistent())
        {
            QString qstrMajorFieldName = pMember->GetConfigItem(FTL_MEMBER_FIELD_NAME).toString();

            switch (pMember->GetValueType())
            {
            case eDmValueBinaryDocument:
            {
                QString qstrFieldName = qstrMajorFieldName + FTL_BIN_DOC_FILENAME_SUFFIX;
                m_qstrFields += qstrFieldName;
                QString qstrPlaceholder = ":" +qstrFieldName;
                m_qstrFieldPlaceholders += qstrPlaceholder;

                qstrFieldName = qstrMajorFieldName + FTL_BIN_DOC_CONTENT_SUFFIX;
                m_qstrFields += ", " + qstrFieldName;
                qstrPlaceholder = ", :" +qstrFieldName;
                m_qstrFieldPlaceholders += qstrPlaceholder;
                break;
            }
            case eDmValueObjectRef:
            {
                QString qstrFieldName = qstrMajorFieldName + FTL_OBJECT_REF_CONTAINER_SUFFIX;
                m_qstrFields += qstrFieldName;
                QString qstrPlaceholder = ":" +qstrFieldName;
                m_qstrFieldPlaceholders += qstrPlaceholder;

                qstrFieldName = qstrMajorFieldName + FTL_OBJECT_REF_OBJECT_SUFFIX;
                m_qstrFields += qstrFieldName;
                qstrPlaceholder = ":" +qstrFieldName;
                m_qstrFieldPlaceholders += qstrPlaceholder;

                break;
            }
            default:
                QString qstrFieldName = qstrMajorFieldName;
                m_qstrFields += qstrFieldName;
                QString qstrPlaceholder = ":" +qstrFieldName;
                m_qstrFieldPlaceholders += qstrPlaceholder;
                break;
            }

            CftlHelper::FillFieldValues(":" + qstrMajorFieldName, pMember, m_rpObject, m_qvmFieldValues, p_pInterface);
        }
    }

    AddObjectProperties(FTL_CREATOR_ID, (int)CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    AddObjectProperties(FTL_MODIFIER_ID, (int)CdmSessionManager::GetSessionManager()->GetCurrentUserId());
    AddObjectProperties(FTL_LAST_MODIFIED, QDateTime::currentDateTime());
    AddObjectProperties(FTL_CREATED, QDateTime::currentDateTime());
    AddObjectProperties(FTL_CONTAINER_ID_FIELD_NAME, (int)m_rpObject->GetObjectContainerId());
    AddObjectProperties(FTL_OBJECT_CAPTION_FIELD_NAME, m_rpObject->GetCaption());

}

void CftlContainerTableInsert::AddObjectProperties(QString p_qstrFieldName, QVariant p_qvValue)
{
    m_qstrFieldPlaceholders += ", :" + p_qstrFieldName;
    m_qstrFields += ", " + p_qstrFieldName;
    m_qvmFieldValues.insert(":" + p_qstrFieldName, p_qvValue);
}

long CftlContainerTableInsert::GetCreatedObjectId()
{
    return m_lObjectId;
}

QStringList CftlContainerTableInsert::GenerateSqls()
{
    // in this class execute is overridden to be able to use prepared sql statements
    QStringList list;
    return list;
}

bool CftlContainerTableInsert::IsValid()
{
    return (m_rpObject != nullptr);
}
