#ifndef CDMMember_H
#define CDMMember_H

// Sytem and QT Includes
#include <QVariant>
#include <QStringList>


// own Includes
#include "CdmRights.h"
#include "CdmModelElement.h"
#include "CdmConfigManager.h"

// Defines
#define WMS_MEMBER_ORIGINAL_VALUE_TYPE "OriginalValueType"

// forwards
class QVariant;
class CdmClassGroup;


// Enumerations
enum EdmMemberAccess
{
    eDmMemberAccessPublic = 0,
    eDmMemberAccessProtected = 1,
    eDmMemberAccessPrivate = 2
};

// TYpeDefs
typedef QPair<QString, QString> StringPair;

/*
 * This class implements a class member.
 * It is the source for creating value objects.
 */
class WMSMANAGER_API CdmMember : public CdmModelElement, public CdmConfigManager
{
    Q_OBJECT

    friend class CdmClass;
    friend class CdmDataAccessHelper;

private:
    /*
       * The Value Type
       */
    EdmValueType m_eDmValue;
    /*
        * The Value size, is used for strings
        */
    long        m_lSize;
    /*
        * Used for ObjectLists and ObjectListRefs
        */
    long        m_lReference;
    /*
        * Used for Counter Values to set the value on which the counter has to start.
        */
    long        m_lCounterStart;

    /*
        * Is used for referencing the class, the member belongs to
        */
    long        m_lClassId;

    /*
        * This shows if a value of this member must have a value or not
        */
    bool        m_bMust;

    /*
        * The default value
        */
    QVariant   m_qvDefaultValue;

    /*
        * Comment for creating Documentation
        */
    QString     m_qstrComment;

    /*
        * This flag is used for objectlistreference to decide if a new objectlist
        * must be created if a new object is created, or deleted if the object
        * will be deleted.
        */
    bool        m_bOwner;

    /*
        * This flag is used to make sure that a value of this member occurs only once
        */
    bool        m_bUnique;

    /*
        * The access flag of the member
        * public: will be shown in ui and is editable
        * protected: will be shown in the ui but is not editable
        * private: will behidden in the ui
        */
    EdmMemberAccess m_eDmMemberAccess;

    /*
        * The Flag shows if thís member is needed by the system. It is not possible to change
        * members with system flag.
        */
    bool m_bSystem;

    /*
        * The database version when this member was last changed or added
        */
    int m_iVersion;

    /*
       * The rights management for this member
       */
    CdmRights m_cCdmRights;

    /*
       * The group in which this member is
       */
    CdmClassGroup* m_rpCdmGroup;

    /*
       * The Code for validating the member content
       */
    QString m_qstrValidationCode;

    /*
       * The translations for the caption
       */
    QMap<QString, StringPair> m_qmTranslations; // <LanguageId, Translation>

    /*
      * The flag if this member has to be saved in the db or not.
      */
    bool m_bPersistent;

    /*
       *
       */
    bool m_bIsTree;

private:
    CdmMember(long p_lDbId,
              long p_lId,
              QString p_qstrKeyname,
              EdmValueType p_eDmValue,
              bool p_bMust,
              long p_lSize);
    CdmMember(QDomElement& p_rqDomElement);
    CdmMember(QVariantMap& p_qMember, long p_lClassId);
    virtual ~CdmMember();

public:
    bool IsMust() const;
    void SetDefaultValue(const QString p_qstDefault );
    void SetDefaultValue(const bool p_bDefault );
    void SetDefaultValue(const int p_iDefault );
    void SetDefaultValue(const long p_lDefault );
    void SetDefaultValue(const double p_dDefault );
    void SetDefaultValue(const float p_fDefault );
    void SetDefaultValue(const QDate p_qdDefault );
    void SetDefaultValue(const QDateTime p_qdtDefault );
    void SetDefaultValue(const QTime p_qtDefault );
    void GetDefaultValue(QTime& p_qtDefault) const;
    void GetDefaultValue(QDateTime& p_qdtDefault) const;
    void GetDefaultValue(QDate& p_qdDefault) const;
    void GetDefaultValue(float& p_fDefault) const;
    void GetDefaultValue(long& p_lDefault) const;
    void GetDefaultValue(int& p_iDefault) const;
    void GetDefaultValue(QString& p_qstDefault) const;
    void GetDefaultValue(bool& p_bDefault) const;
    void GetDefaultValue(double& p_dDefault) const;
    QVariant GetDefaultValue() const;
    void SetValueType(EdmValueType p_eDmValue);
    void SetMustValue(bool p_bMust);
    void SetSize(long p_lSize );
    void SetDefaultValue(const QVariant p_qvValue );
    void SetClassId(long p_lClassId );
    void SetComment(QString p_qstrComment );
    void SetTimeDefaultValue(const double p_dDefault );
    void GetTimeDefaultValue(double& p_dDefault ) const;
    void SetDateTimeDefaultValue(const double p_dDefault );
    void GetDateTimeDefaultValue(double& p_dDefault) const;
    void SetDateDefaultValue(const long p_lDefault );
    void GetDateDefaultValue(long& p_lDefault ) const;
    void SetClassReference(long p_lReference );
    void SetCounterStart(long p_lCounterStart );
    void XmlExport(QDomElement& p_rqdeClassMembers) const;
    void XmlImport(QDomElement& p_rqdeClassMembers );
    void XmlImportMember(QDomElement& p_rqdeClassMembers );
    void SetOwner(bool p_bOwner );
    void SetUnique(bool p_bUnique );
    void SetClassReference(QString p_qstrClassName);
    void SetSystemFlag( bool p_bSystem);
    void SetMemberAccess(EdmMemberAccess p_eDmMemberAccess);
    virtual QVariant GetVariant() const;
    void SetVariant(QVariantMap& p_rqvMember);
    void SetVersion(int p_iVersion);
    void SetGroup(CdmClassGroup* p_pCdmGroup);
    void SetValidationCode(QString p_qstrCode);
    QMap<QString, StringPair>& GetTranslations();
    QString GetTranslation(QString p_iLanguageId) const;
    void SetTranslation(QString p_qstrLanguage, QString p_qstrTranslation, QString p_qstrComment);
    QString GetTranslationComment(QString p_iLanguageId) const;
    void DeleteTranslation(QString p_iId);
    static QString GetValueTypeAsString(EdmValueType p_eValue);
    bool IsPersistent() const;
    void SetPersistent(bool p_bPersistent);
    QString GetEmfType() const;
    void Deploy(QVariantMap& p_rqvMember);
    void SetTree(bool p_bTree);
    bool IsTree() const;
    void SetKeyname(QString p_qstrKeyname);
    void SetPrefix(QString p_qstrPrefix);
    QString GetPrefix() const;
    void SetSuffix(QString p_qstrSuffix);
    QString GetSuffix() const;
    void SetDecimalCountInput(int p_iDecimalCount);
    int GetDecimalCountOutput() const;
    void SetDecimalCountOutput(int p_iDecimalCount);
    int GetDecimalCountInput() const;
    QString GetAccessModeAsString() const;
    QString GetUriInternal() const;
    QString GetEnabledCheck() const;
    QString GetRenderedCheck() const;
    void SetEnabledCheck(QString p_qstrRendered);
    void SetRenderedCheck(QString p_qstrRendered);
    void SetClassReference(CdmClass *p_pClass);
    long GetSize() const;
    EdmValueType GetValueType() const;
    long GetClassId() const;
    QString GetComment() const;
    QString GenerateDocument();
    QString GetValueTypeAsString() const;
    long GetClassReference() const;
    long GetCounterStart() const;
    bool IsOwner() const;
    bool IsUnique() const;
    bool IsSystemMember() const;
    EdmMemberAccess GetAccessMode() const;
    bool IsNumber() const;
    bool IsDisplayMember() const;
    QString ConvertValueToDisplayString(QVariant p_qvValue) const;
    QVariant GetMemberAlignment() const;
    int GetVersion() const;
    const CdmClassGroup* GetGroup() const;
    QString GetGroupName() const;
    bool CheckWriteAccess() const;
    bool CheckReadAccess() const;
    CdmRights& GetRights();
    bool HasValidation() const;
    QString GetValidationCode() const;
    QString GetValidationCodeBase64() const;
    bool IsList() const;
    bool IsMap() const;
    virtual QString GetCaption() const;
    QStringList GetSelectionList() const;
    virtual bool IsMember() const;
    virtual QString GetUri() const;
    bool IsValidationType() const;
    CdmClass* GetClass() const;
    static bool IsExportType(EdmValueType p_eType);
    void SetDisplayConfig(QString p_qstrPrefix);
    QString GetDisplayConfig() const;
    CdmClass *GetClassReferencePtr() const;
};
#endif
