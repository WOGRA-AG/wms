// System and Qt Includes

// WMSCORE Includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"

// own Includes
#include "CftlDialect.h"
#include "CftlHelper.h"
#include "CftlContainerTableCreate.h"

CftlContainerTableCreate::CftlContainerTableCreate(CdmClass* p_pClass, CftlDialect* p_ppDialect)
    : CftlContainerTableBase(p_ppDialect),
      m_rpClass(p_pClass)
{
}

CftlContainerTableCreate::~CftlContainerTableCreate()
{

}

QStringList CftlContainerTableCreate::GenerateSqls()
{
    QStringList qstrlSqls;
    QString qstrSql;
    QString qstrTableName = CftlHelper::GenerateClassContainerTableName(m_rpClass, GetDialect());

    if (!qstrTableName.isEmpty())
    {
        qstrSql = QString("create table %1 (").arg(qstrTableName);
        qstrSql += FTL_CONTAINER_ID_FIELD_NAME " " + GetDialect()->getType(eDmValueLong) + " not null";

        if (GetDialect()->IsDirectAutoIncrement())
        {
            qstrSql += ", " FTL_OBJECT_ID_FIELD_NAME " " + GetDialect()->getType(eDmValueLong) + " not null " + GetDialect()->GetDirectAutoIncrementKeyword();
        }

        qstrSql += ", " FTL_OBJECT_KEYNAME_FIELD_NAME " " + GetDialect()->getKeynameType();
        qstrSql += ", " FTL_OBJECT_CAPTION_FIELD_NAME " " + GetDialect()->getKeynameType();

        qstrSql += AddMembersToTable();
        qstrSql += AddModificationInfo();
        qstrSql += AddPrimaryKey();

        qstrSql += ")";

        qstrlSqls.append(qstrSql);
        qstrlSqls.append(CreateIndices(qstrTableName));

        if (!GetDialect()->IsDirectAutoIncrement())
        {
            QString qstrSequenceSql = GetDialect()->GetSequenceTemplate();
            qstrSequenceSql = qstrSequenceSql.replace("${NAME}", CftlHelper::GenerateClassContainerSequenceName(m_rpClass));
            qstrlSqls.append(qstrSequenceSql);

            QString qstrTriggerSql = GetDialect()->GetSequenceTriggerTemplate();
            qstrTriggerSql = qstrTriggerSql.replace("${NAME}", CftlHelper::GenerateClassContainerSequenceTriggerName(m_rpClass));
            qstrTriggerSql = qstrTriggerSql.replace("${TABLE}", qstrTableName);
            qstrTriggerSql = qstrTriggerSql.replace("${FIELD}", FTL_OBJECT_ID_FIELD_NAME);
            qstrlSqls.append(qstrTriggerSql);
        }

        m_rpClass->SetConfigItem(FTL_CLASS_TABLE_NAME, qstrTableName);
    }
    else
    {
        FATAL("Tablename creation failed!");
    }


    return qstrlSqls;
}

QString CftlContainerTableCreate::AddModificationInfo()
{
    QString qstrSqlPart;
    qstrSqlPart = ", " FTL_CREATOR_ID " " + GetDialect()->getType(eDmValueInt) + " not null";
    qstrSqlPart += ", " FTL_MODIFIER_ID " " + GetDialect()->getType(eDmValueInt) + " not null";
    qstrSqlPart += ", " FTL_LAST_MODIFIED " " + GetDialect()->getType(eDmValueDateTime) + " not null";
    qstrSqlPart += ", " FTL_CREATED " " + GetDialect()->getType(eDmValueDateTime) + " not null";
    qstrSqlPart += ", " FTL_LOCKED " " + GetDialect()->getType(eDmValueLong);
    qstrSqlPart += ", " FTL_LOCKED_TIMESTAMP " " + GetDialect()->getType(eDmValueDateTime);
    qstrSqlPart += ", " FTL_PARENT " " + GetDialect()->getType(eDmValueInt);
    qstrSqlPart += ", " FTL_CONFIG " " + GetDialect()->getType(eDmValueCharacterDocument);
    qstrSqlPart += ", " FTL_SESSION_ID " " + GetDialect()->getType(eDmValueLong);
    qstrSqlPart += ", ";
    return qstrSqlPart;
}

QString CftlContainerTableCreate::AddPrimaryKey()
{
    return QString(" primary key (%1)")
            .arg(FTL_OBJECT_ID_FIELD_NAME);
}

QString CftlContainerTableCreate::AddMembersToTable()
{
    QString qstrSqlPart;
    QMap<qint64, CdmMember*> qmMembers;
    m_rpClass->GetMemberMap(qmMembers);

    QMapIterator<qint64, CdmMember*> qmIt(qmMembers);

    while (qmIt.hasNext())
    {
        qmIt.next();
        qstrSqlPart += AddMember(qmIt.value());
    }

    return qstrSqlPart;
}

QString CftlContainerTableCreate::AddMember(CdmMember* p_pMember)
{
    QString qstrSqlPart;

    if (CHKPTR(p_pMember) && p_pMember->IsPersistent())
    {
        EdmValueType eValue = p_pMember->GetValueType();
        QString qstrFieldName = CftlHelper::GenerateMemberFieldName(p_pMember, GetDialect());
        QString qstrType = GetDialect()->getType(eValue);

        switch (eValue) {
        case eDmValueBinaryDocument:
        {
            QString qstrNameField = qstrFieldName + FTL_BIN_DOC_FILENAME_SUFFIX;
            qstrSqlPart = ", " + qstrNameField + " " + GetDialect()->getType(eDmValueString);
            QString qstrDataField = qstrFieldName + FTL_BIN_DOC_CONTENT_SUFFIX;
            qstrSqlPart += ", " + qstrDataField + " " + qstrType;
            break;
        }
        case eDmValueObjectRef:
        {
            QString qstrContainerRefField = qstrFieldName + FTL_OBJECT_REF_CONTAINER_SUFFIX;
            qstrSqlPart = ", " + qstrContainerRefField + " " + GetDialect()->getType(eDmValueContainerRef);
            QString qstrObjectRefField = qstrFieldName + FTL_OBJECT_REF_OBJECT_SUFFIX;
            qstrSqlPart += ", " + qstrObjectRefField + " " + qstrType;
            break;
        }
        default:
            qstrSqlPart = ", " + qstrFieldName + " " +qstrType;
            break;
        }

        p_pMember->SetConfigItem(FTL_MEMBER_FIELD_NAME, qstrFieldName);
    }

    return qstrSqlPart;
}

QStringList CftlContainerTableCreate::CreateIndices(QString p_qstrTableName)
{
    QStringList qstrlIndices;

    QString qstrIndexTemplate = "create index %1 on %2 (%3)";
    int iIndex = 0;

    QString qstrSql = QString(qstrIndexTemplate)
                        .arg(CftlHelper::GenerateClassContainerIndexNameFromTableName(p_qstrTableName, ++iIndex, GetDialect()))
                        .arg(p_qstrTableName)
                        .arg(FTL_OBJECT_ID_FIELD_NAME);

    qstrlIndices.append(qstrSql);

    qstrSql = QString(qstrIndexTemplate)
                            .arg(CftlHelper::GenerateClassContainerIndexNameFromTableName(p_qstrTableName, ++iIndex, GetDialect()))
                            .arg(p_qstrTableName)
                            .arg(FTL_CONTAINER_ID_FIELD_NAME);

    qstrlIndices.append(qstrSql);

    qstrSql = QString(qstrIndexTemplate)
                            .arg(CftlHelper::GenerateClassContainerIndexNameFromTableName(p_qstrTableName, ++iIndex, GetDialect()))
                            .arg(p_qstrTableName)
                            .arg(FTL_CONTAINER_ID_FIELD_NAME ", " FTL_OBJECT_ID_FIELD_NAME);

    qstrlIndices.append(qstrSql);

    qstrSql = QString(qstrIndexTemplate)
                            .arg(CftlHelper::GenerateClassContainerIndexNameFromTableName(p_qstrTableName, ++iIndex, GetDialect()))
                            .arg(p_qstrTableName)
                            .arg(FTL_OBJECT_KEYNAME_FIELD_NAME);

    qstrlIndices.append(qstrSql);
    return qstrlIndices;
}

bool CftlContainerTableCreate::IsValid()
{
    return (m_rpClass != nullptr);
}
