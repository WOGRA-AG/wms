#ifndef CFTLDIALECT_H
#define CFTLDIALECT_H

#include "CdmModelElement.h"

#define FTL_CONTAINER_ID_FIELD_NAME "ContainerId"
#define FTL_OBJECT_ID_FIELD_NAME "ObjectId"
#define FTL_OBJECT_KEYNAME_FIELD_NAME "Keyname"
#define FTL_OBJECT_CAPTION_FIELD_NAME "Caption"
#define FTL_AUTO_INCREMENT_KEYWORD "AutoIncrementKeyword"
#define FTL_AUTO_INCREMENT_MODE "AutoIncrementMode"
#define FTL_SEQUENCE_COMMAND "SequenceCommand"
#define FTL_TRIGGER_COMMAND "TriggerCommand"
#define FTL_CREATOR_ID "CreatorId"
#define FTL_MODIFIER_ID "ModifierId"
#define FTL_LAST_MODIFIED "LastModified"
#define FTL_CREATED "Created"
#define FTL_LOCKED "Locked"
#define FTL_LOCKED_TIMESTAMP "Locked_Timestamp"
#define FTL_PARENT "Parent"
#define FTL_CONFIG "Config"
#define FTL_SESSION_ID "SessionId"
#define FTL_ADD_COLUMN "AddColumn"
#define FTL_DROP_COLUMN "DropColumn"
#define FTL_RENAME_FIELD "RenameField"
#define FTL_RENAME_TABLE "RenameTable"
#define FTL_KEYNAME_TYPE "KeynameType"
#define FTL_KEYNAME_LIMT "KeynameLimit"
#define FTL_KEYNAME_OFFSET "KeynameOffset"
#define FTL_SUPPORT_LIMIT "SupportLimit"
#define FTL_MAX_FIELD_NAME_LENGTH "MaxFieldNameLength"
#define FTL_MAX_TABLE_NAME_LENGTH "MaxTableNameLength"
#define FTL_MEMBER_PLACEHOLDER "<MEMBERS>"

#define FTL_TABLE_NAME_PLACEHOLDER "${TABLE}"
#define FTL_ORIGINAL_NAME_PLACEHOLDER "${OLDNAME}"
#define FTL_NEW_NAME_PLACEHOLDER "${NAME}"
#define FTL_TYPE_PLACEHOLDER "${TYPE}"

class CftlDialect
{

private:
    QMap<EdmValueType, QString> m_qmTypeMapping;
    bool m_bDirectAutoIncrement;
    bool m_bLimitSupport;
    QString m_qstrDirectAutoIncrementKeyWord;
    QString m_qstrGenerateSequenceCommand;
    QString m_qstrGenerateTriggerCommand;
    QString m_qstrAddColumn;
    QString m_qstrDropColumn;
    QString m_qstrRenameField;
    QString m_qstrRenameTable;
    QString m_qstrKeynameType;
    QString m_qstrLimitKeyname;
    QString m_qstrOffsetKeyname;
    int m_iMaxFieldNameLength;
    int m_iMaxTableNameLength;

    void AddTypeToMap(QVariantMap &p_rqMap, EdmValueType p_eValue, QString p_qstrDefault);
    void setDefaultConfig();

public:
    CftlDialect();
    ~CftlDialect();
    void Init(QString p_qstrFilename);
    QString getType(EdmValueType p_eValue) const;
    void StoreDialect(QString p_qstrFilename);
    bool IsDirectAutoIncrement();
    QString GetDirectAutoIncrementKeyword();
    QString GetSequenceTemplate();
    QString GetSequenceTriggerTemplate();
    QString GetAddColumnString();
    QString GetDropColumnString();
    QString GetRenameFieldTemplate();
    QString GetRenameTableTemplate();
    QString getKeynameType();
    QString GetLimitKeyname();
    QString GetOffsetKeyname();
    bool IsSupportingLimit();
    int GetMaxTableNameLength();
    int GetMaxFieldNameLength();
};

#endif // CFTLDIALECT_H
