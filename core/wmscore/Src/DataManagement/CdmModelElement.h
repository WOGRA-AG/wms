#ifndef CDMBASE_H
#define CDMBASE_H


// System and QT Includes
#include <QDateTime>
#include <QVariant>

// own Includes
#include "datamanager.h"
#include "CdmClassManager.h"


// forwards
class QString;
class QDateTime;
class QDomElement;
class CdmDataProvider;
class CdmSettings;
class CdmLogging;

class CdmContainerManager;
class IdmDataAccess;


// enumerations
enum EdmStringDisplayType
{
    edmStringDisplayTypeFormatted,  // formatted (HTML) display
    edmStringDisplayTypeUnFormatted,// unformatted (plain text) display
    edmStringDisplayTypeDirectory,  // for strings with directory dialog
    edmStringDisplayTypeFile,       // for strings with file choice dialog
    edmStringDisplayTypeEncrypted,  // Hidden Passwords
    edmStringDisplayTypeLink,       // Web links
    edmStringDisplayTypeJson,       // Json Content --> can be used for chardocs
    edmStringDisplayTypeXml,        // XML Content --> can be used for chardocs
};

/*
 * The values types in WMS
 */
enum EdmValueType
{
    eDmValueNone              = 0,
    eDmValueBool              = 1,
    eDmValueInt               = 2,
    eDmValueLong              = 3,
    eDmValueFloat             = 4,
    eDmValueDouble            = 5,
    eDmValueString            = 6,
    eDmValueDate              = 7,
    eDmValueTime              = 8,
    eDmValueDateTime          = 9,
    eDmValueObjectRef         = 10,
    eDmValueContainerRef      = 11,
    eDmValueCounter           = 12,
    eDmValueBinaryDocument    = 13,
    eDmValueCharacterDocument = 14,
    eDmValueListInt           = 15,
    eDmValueListDouble        = 16,
    eDmValueListString        = 17,
    eDmValueDictStringInt     = 18,
    eDmValueDictStringString  = 19,
    eDmValueDictStringDouble  = 20,
    eDmValueDictIntInt        = 21,
    eDmValueDictIntString     = 22,
    eDmValueDictIntDouble     = 23,
    eDmValueListObjects       = 24,
    eDmValueObjectTree        = 25,
    eDmValueFormula           = 26,
    eDmValueUser              = 27,
    eDmValueEnum              = 28,
    eDmValueUserGroup         = 29,
    eDmValueArray             = 30,// no wms type will be used for function parameter
    eDmValueGeoPos            = 31, // not yet implemented
    eDmValueDimDouble         = 32, // not yet implemented
    eDmValueURI               = 33,// not yet implemented
    eDmValueQObject           = 34,// no wms type will be used for function parameter or return type
};


enum EdmChangeFlag
{
    edmChangeFlagNone = 0,
    edmChangeFlagKeyname = 1,
    edmChangeFlagType = 2,
    edmChangeFlagUniqueProperty = 4,
    edmChangeFlagAbstract = 8,
    edmChangeFlagPersistent = 16,
    eDmChangeFlagBaseClass = 32,
};


/*
 * The base class for the most datamanager class
 * except manager classes
 */
class WMSMANAGER_API CdmModelElement : public CdmModelElementBase
{
    Q_OBJECT

    friend class IdmDataAccess;
    friend class CdmDataAccessHelper;
    friend class CdmClass;
    friend class CdmObjectContainer;
    friend class CdmContainerManager;
    friend class CdmClassManager;
    
private:    
    /*
     * The Id of the Base object it will be used for referencing
     */
    QAtomicInteger<qint64> m_lId;

    /*
     * The User Id of the latest person who modified this object
     */
    QAtomicInteger<qint64>        m_lModifierId;

    /*
     * The User Id of the creator of this object
     */
    QAtomicInteger<qint64>        m_lCreatorId;

    /*
     * The Object keyname
     */
    QString     m_qstrKeyname;

    /*
     * The object caption
     */
    QString     m_qstrCaption;

    /*
     * The timestamp of the lastchange
     */
    QDateTime   m_qdtLastChange;

    /*
     * Shows if this object is modified
     */
    QAtomicInteger<bool>        m_bModified;

    /*
     * Shows if this object is valid
     */
    QAtomicInteger<bool>        m_bValid;

    /*
     * Shows if the user wants to delete this object
     */
    QAtomicInteger<bool>        m_bDeleted;

    /*
     * Show if this object was created at the moment
     */
    QAtomicInteger<bool>        m_bNew;

    /*
     * if the keyname has changed here you will find the old one
     */
    QString m_qstrOriginalKeyname;


public:
    CdmModelElement(QDomElement& p_rqDomElement);
    CdmModelElement(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, QString p_qstrCaption = "");
    CdmModelElement( QVariant p_qvVariant);
    virtual ~CdmModelElement();
    QDateTime GetLastChange() const;
    void SetLastChange(QDateTime& p_qdDateTime);
    virtual void SetModified();
    qint64 GetCreatorId() const;
    void SetModifierId(qint64 p_lUserId);
    void SetCreatorId(qint64 p_lUserId);
    virtual void ResetNewModified();
    static qint64 ChangeDateToLong(const QDate p_qdDate);
    static QDate ChangeLongToDate(qint64 p_lDate);
    static double ChangeTimeToDouble(QTime p_qtTime);
    static QTime ChangeDoubleToTime(double p_dTime);
    double ChangeDateTimeToDouble(QDateTime p_qdtDateTime) const;
    static QDateTime ChangeDoubleToDateTime(double p_dDateTime);
    void GetLastChange(double& p_dLastChange) const;
    void SetLastChange(double p_dLastChanged);
    static QString ChangeBoolToString(bool p_bValue);
    static bool ChangeStringToBool(QString p_qstrBool);
    virtual QVariant GetVariant() const;
    static QString GetDisplayTypeAsString(EdmStringDisplayType p_eType);
    static bool CheckKeyname(QString p_qstrKeyname);
    QString GenerateKeyname() const;
    CdmModelElement();
    QString GetOriginalKeyname() const;
    virtual bool IsModelElement() const;
    QString GetUriInternal() const;

public slots:
    virtual QString GetKeyname() const;
    virtual bool IsValid() const;
    virtual bool IsDeleted() const;
    qint64 GetModifierId() const;
    bool IsNew() const;
    qint64 GetId() const;
    virtual bool IsModified() const;
    void SetCaption(QString p_qstrCaption);
    virtual QString GetCaption() const;
    virtual QString GetInfo() const;
    virtual QString GetUri() const;

protected:
    void SetInvalid();
    void SetValid();
    virtual void SetDeleted();
    virtual void SetKeyname(QString p_qstrKeyname);
    virtual void SetNew();
    void XmlExportBase(QDomElement& p_rqdeBase) const;
    void XmlImportBase(QDomElement& p_rqDomElement);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    QString GetUriType() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    bool HasUserDeleteAccess();

private:
    void SetId(qint64 p_lId);

};

#endif
