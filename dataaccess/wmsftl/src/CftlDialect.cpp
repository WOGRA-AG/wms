// System and Qt Includes
#include "QDir"

// WMS Commons Includes
#include "CwmsJson.h"

// WMS Core Includes
#include "CdmLogging.h"
#include "CdmMember.h"

#include "CftlDialect.h"

CftlDialect::CftlDialect()
    : m_bDirectAutoIncrement(true),
      m_bLimitSupport(true),
      m_iMaxFieldNameLength(55),
      m_iMaxTableNameLength(55)
{
}

CftlDialect::~CftlDialect()
{

}

void CftlDialect::setDefaultConfig()
{
    m_qstrDirectAutoIncrementKeyWord = "auto_increment";
    m_qstrRenameTable = "alter table " FTL_TABLE_NAME_PLACEHOLDER " rename " FTL_NEW_NAME_PLACEHOLDER;
    m_qstrRenameField = "alter table " FTL_TABLE_NAME_PLACEHOLDER " CHANGE COLUMN " FTL_ORIGINAL_NAME_PLACEHOLDER " " FTL_NEW_NAME_PLACEHOLDER " " FTL_TYPE_PLACEHOLDER;
    m_qstrDropColumn = "drop";
    m_qstrAddColumn = "add column";
    m_bDirectAutoIncrement = true;
    m_qstrKeynameType = "VARCHAR(255)";
    m_qstrLimitKeyname = "limit";
    m_qstrOffsetKeyname = "offset";
    m_bLimitSupport = true;
    m_iMaxFieldNameLength = 55;
    m_iMaxTableNameLength = 55;
    QVariantMap qvm; // Dummy
    AddTypeToMap(qvm, eDmValueBool, "int");
    AddTypeToMap(qvm, eDmValueInt, "int");
    AddTypeToMap(qvm, eDmValueLong, "bigint(20)");
    AddTypeToMap(qvm, eDmValueFloat, "DECIMAL(18,7)");
    AddTypeToMap(qvm, eDmValueDouble, "DOUBLE");
    AddTypeToMap(qvm, eDmValueString, "VARCHAR(1000)");
    AddTypeToMap(qvm, eDmValueDate, "DATE");
    AddTypeToMap(qvm, eDmValueTime, "TIME");
    AddTypeToMap(qvm, eDmValueDateTime, "TIMESTAMP");
    AddTypeToMap(qvm, eDmValueObjectRef, "INT");
    AddTypeToMap(qvm, eDmValueContainerRef, "INT");
    AddTypeToMap(qvm, eDmValueCounter, "INT");
    AddTypeToMap(qvm, eDmValueBinaryDocument, "LONGBLOB");
    AddTypeToMap(qvm, eDmValueCharacterDocument, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueListInt, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueListDouble, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueListString, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictStringInt, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictStringString, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictStringDouble, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictIntInt, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictIntString, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueDictIntDouble, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueListObjects, "LONGTEXT");
    AddTypeToMap(qvm, eDmValueUser, "INT");
    AddTypeToMap(qvm, eDmValueEnum, "INT");
    AddTypeToMap(qvm, eDmValueUserGroup, "INT");
}

void CftlDialect::Init(QString p_qstrFilename)
{
    QString qstrContent;
    bool bStoreDefault = false;

    if (p_qstrFilename.isEmpty())
    {
        p_qstrFilename = QDir::homePath() + "/default.dialect";
    }

    QFile qFile(p_qstrFilename);

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream qts(&qFile);
        qstrContent = qts.readAll();
    }
    else
    {
        ERR("Could not oopen dialect file for reading. " + p_qstrFilename);
        bStoreDefault = true;
    }

    if (!qstrContent.isEmpty())
    {
        CwmsJson json;
        QVariantMap qvm = json.parse(qstrContent).toMap();

        if (qvm.count() > 0)
        {
            AddTypeToMap(qvm, eDmValueBool, "int");
            AddTypeToMap(qvm, eDmValueInt, "int");
            AddTypeToMap(qvm, eDmValueLong, "bigint(20)");
            AddTypeToMap(qvm, eDmValueFloat, "DECIMAL(18,7)");
            AddTypeToMap(qvm, eDmValueDouble, "DOUBLE");
            AddTypeToMap(qvm, eDmValueString, "VARCHAR(1000)");
            AddTypeToMap(qvm, eDmValueDate, "DATE");
            AddTypeToMap(qvm, eDmValueTime, "TIME");
            AddTypeToMap(qvm, eDmValueDateTime, "TIMESTAMP");
            AddTypeToMap(qvm, eDmValueObjectRef, "INT");
            AddTypeToMap(qvm, eDmValueContainerRef, "INT");
            AddTypeToMap(qvm, eDmValueCounter, "INT");
            AddTypeToMap(qvm, eDmValueBinaryDocument, "LONGBLOB");
            AddTypeToMap(qvm, eDmValueCharacterDocument, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueListInt, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueListDouble, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueListString, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictStringInt, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictStringString, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictStringDouble, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictIntInt, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictIntString, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueDictIntDouble, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueListObjects, "LONGTEXT");
            AddTypeToMap(qvm, eDmValueUser, "INT");
            AddTypeToMap(qvm, eDmValueEnum, "INT");
            AddTypeToMap(qvm, eDmValueUserGroup, "INT");

            if (qvm.contains(FTL_AUTO_INCREMENT_MODE))
            {
                m_bDirectAutoIncrement = qvm[FTL_AUTO_INCREMENT_MODE].toBool();
            }
            else
            {
                m_bDirectAutoIncrement = true;
            }

            if (qvm.contains(FTL_AUTO_INCREMENT_KEYWORD))
            {
                m_qstrDirectAutoIncrementKeyWord = qvm[FTL_AUTO_INCREMENT_KEYWORD].toString();
            }
            else
            {
                m_qstrDirectAutoIncrementKeyWord = "auto_increment";
            }

            if (qvm.contains(FTL_ADD_COLUMN))
            {
                m_qstrAddColumn = qvm[FTL_ADD_COLUMN].toString();
            }
            else
            {
                m_qstrAddColumn = "add column";
            }

            if (qvm.contains(FTL_DROP_COLUMN))
            {
                m_qstrDropColumn = qvm[FTL_DROP_COLUMN].toString();
            }
            else
            {
                m_qstrDropColumn = "drop";
            }

            if (qvm.contains(FTL_RENAME_FIELD))
            {
                m_qstrRenameField = qvm[FTL_RENAME_FIELD].toString();
            }
            else
            {
                m_qstrRenameField = "alter table " FTL_TABLE_NAME_PLACEHOLDER " CHANGE COLUMN " FTL_ORIGINAL_NAME_PLACEHOLDER " " FTL_NEW_NAME_PLACEHOLDER " " FTL_TYPE_PLACEHOLDER;
            }


            if (qvm.contains(FTL_RENAME_TABLE))
            {
                m_qstrRenameTable = qvm[FTL_RENAME_TABLE].toString();
            }
            else
            {
                m_qstrRenameTable = "alter table " FTL_TABLE_NAME_PLACEHOLDER " rename " FTL_NEW_NAME_PLACEHOLDER;
            }

            if (qvm.contains(FTL_KEYNAME_TYPE))
            {
                m_qstrKeynameType = qvm[FTL_KEYNAME_TYPE].toString();
            }
            else
            {
                m_qstrKeynameType = "VARCHAR(255)";
            }

            if (qvm.contains(FTL_SUPPORT_LIMIT))
            {
                m_bLimitSupport = qvm[FTL_SUPPORT_LIMIT].toBool();
            }
            else
            {
                m_bLimitSupport = true;
            }

            if (qvm.contains(FTL_KEYNAME_LIMT))
            {
                m_qstrLimitKeyname = qvm[FTL_KEYNAME_LIMT].toString();
            }
            else
            {
                if (m_bLimitSupport)
                {
                    m_qstrLimitKeyname = "limit";
                }
            }

            if (qvm.contains(FTL_KEYNAME_OFFSET))
            {
                m_qstrOffsetKeyname = qvm[FTL_KEYNAME_OFFSET].toString();
            }
            else
            {
                if (m_bLimitSupport)
                {
                    m_qstrOffsetKeyname = "offset";
                }
            }

            if (qvm.contains(FTL_MAX_FIELD_NAME_LENGTH))
            {
                m_iMaxFieldNameLength = qvm[FTL_MAX_FIELD_NAME_LENGTH].toInt();
            }

            if (qvm.contains(FTL_MAX_TABLE_NAME_LENGTH))
            {
                m_iMaxTableNameLength = qvm[FTL_MAX_TABLE_NAME_LENGTH].toInt();
            }


            m_qstrGenerateSequenceCommand = qvm[FTL_SEQUENCE_COMMAND].toString();
            m_qstrGenerateTriggerCommand =  qvm[FTL_TRIGGER_COMMAND].toString();
        }
    }
    else
    {
         setDefaultConfig();
    }

    if (bStoreDefault)
    {
        StoreDialect(p_qstrFilename);
    }
}

void CftlDialect::AddTypeToMap(QVariantMap& p_rqMap, EdmValueType p_eValue, QString p_qstrDefault)
{
    QString qstrType;

    if (p_rqMap.contains(CdmMember::GetValueTypeAsString(p_eValue)))
    {
        qstrType = p_rqMap[CdmMember::GetValueTypeAsString(p_eValue)].toString();
    }
    else
    {
        qstrType = p_qstrDefault;
    }

    m_qmTypeMapping.insert(p_eValue, qstrType);

}

void CftlDialect::StoreDialect(QString p_qstrFilename)
{
    QString qstrContent;
    QFile qFile(p_qstrFilename);
    QVariantMap qvm;
    QMapIterator<EdmValueType, QString> qmIt(m_qmTypeMapping);

    while (qmIt.hasNext())
    {
        qmIt.next();
        qvm.insert(CdmMember::GetValueTypeAsString(qmIt.key()), qmIt.value());
    }

    qvm[FTL_AUTO_INCREMENT_MODE] = m_bDirectAutoIncrement;
    qvm[FTL_AUTO_INCREMENT_KEYWORD] = m_qstrDirectAutoIncrementKeyWord;
    qvm[FTL_SEQUENCE_COMMAND] = m_qstrGenerateSequenceCommand;
    qvm[FTL_TRIGGER_COMMAND] = m_qstrGenerateTriggerCommand;
    qvm[FTL_ADD_COLUMN] = m_qstrAddColumn;
    qvm[FTL_DROP_COLUMN] = m_qstrDropColumn;
    qvm[FTL_RENAME_FIELD] = m_qstrRenameField;
    qvm[FTL_RENAME_TABLE] = m_qstrRenameTable;

    CwmsJson json;
    qstrContent = json.serialize(qvm);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream qts(&qFile);
        qts << qstrContent;
    }
    else
    {
        ERR("Could not oopen dialect file for writing. " + p_qstrFilename);
    }
}

bool CftlDialect::IsDirectAutoIncrement()
{
    return m_bDirectAutoIncrement;
}

QString CftlDialect::GetDirectAutoIncrementKeyword()
{
    return m_qstrDirectAutoIncrementKeyWord;
}

QString CftlDialect::GetSequenceTemplate()
{
    return m_qstrGenerateSequenceCommand;
}

QString CftlDialect::GetSequenceTriggerTemplate()
{
    return m_qstrGenerateTriggerCommand;
}

QString CftlDialect::GetAddColumnString()
{
    return m_qstrAddColumn;
}

QString CftlDialect::GetDropColumnString()
{
    return m_qstrDropColumn;
}

QString CftlDialect::GetRenameFieldTemplate()
{
    return m_qstrRenameField;
}

QString CftlDialect::GetRenameTableTemplate()
{
    return m_qstrRenameTable;
}

QString CftlDialect::getKeynameType()
{
    return m_qstrKeynameType;
}

QString CftlDialect::GetLimitKeyname()
{
    return m_qstrLimitKeyname;
}

QString CftlDialect::GetOffsetKeyname()
{
    return m_qstrOffsetKeyname;
}

bool CftlDialect::IsSupportingLimit()
{
    return m_bLimitSupport;
}

int CftlDialect::GetMaxTableNameLength()
{
    return m_iMaxTableNameLength;
}

int CftlDialect::GetMaxFieldNameLength()
{
    return m_iMaxFieldNameLength;
}

QString CftlDialect::getType(EdmValueType p_eValue) const
{
    return m_qmTypeMapping[p_eValue];
}
