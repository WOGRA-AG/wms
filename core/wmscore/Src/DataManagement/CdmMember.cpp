// System and QT Includes
#include <QCoreApplication>
#include <qstring.h>
#include <QTextDocument>
#include <qdatetime.h>
#include <QStringList>
#include <qdom.h>
#include <qvariant.h>

// WMS Commons Includes
#include "CwmsJson.h"

// own Includes
#include "wmsdefines.h"
#include "CdmDataProvider.h"
#include "CdmScheme.h"
#include "CdmSystemVariables.h"
#include "CdmSessionManager.h"
#include "CumUserManager.h"
#include "CdmClass.h"
#include "CumUser.h"
#include "CdmLogging.h"
#include "CdmClassGroup.h"
#include "CdmRights.h"
#include "CdmValueListInt.h"
#include "CdmValueListDouble.h"
#include "CdmValueListString.h"
#include "CdmValueDictIntString.h"
#include "CdmValueDictIntInt.h"
#include "CdmValueDictIntDouble.h"
#include "CdmValueDictStringString.h"
#include "CdmValueDictStringInt.h"
#include "CdmValueDictStringDouble.h"
#include "CdmMember.h"


CdmMember::CdmMember(qint64 p_lDbId,
                     qint64 p_lId,
                     QString p_qstrKeyname,
                     EdmValueType p_eDmValue,
                     bool p_bMust,
                     qint64 p_lSize)
    : CdmModelElement(p_lDbId, p_lId, p_qstrKeyname),
      m_eDmValue(p_eDmValue),
      m_lSize(p_lSize),
      m_lReference(0),
      m_lCounterStart(0),
      m_lClassId(0),
      m_bMust(p_bMust),
      m_bOwner(false),
      m_bUnique(false),
      m_eDmMemberAccess(eDmMemberAccessPublic),
      m_bSystem(true),
      m_iVersion(0),
      m_cCdmRights(this),
      m_rpCdmGroup(nullptr),
      m_bPersistent(true),
      m_bIsTree(true)
{
}

CdmMember::CdmMember(QDomElement& p_rqDomElement)
    : CdmModelElement(p_rqDomElement),
      m_eDmValue(eDmValueNone),
      m_lSize(0),
      m_lReference(0),
      m_lCounterStart(0),
      m_lClassId(0),
      m_bMust(false),
      m_bOwner(false),
      m_bUnique(false),
      m_eDmMemberAccess(eDmMemberAccessPublic),
      m_bSystem(true),
      m_iVersion(0),
      m_cCdmRights(this),
      m_rpCdmGroup(nullptr),
      m_bPersistent(true),
      m_bIsTree(true)
{
    XmlImportMember(p_rqDomElement);
}

CdmMember::CdmMember(QVariantMap& p_qMember,qint64 p_lClassId)
    : CdmModelElement(p_qMember),
      m_eDmValue(eDmValueNone),
      m_lSize(0),
      m_lReference(0),
      m_lCounterStart(0),
      m_lClassId(p_lClassId),
      m_bMust(false),
      m_bOwner(false),
      m_bUnique(false),
      m_eDmMemberAccess(eDmMemberAccessPublic),
      m_bSystem(true),
      m_iVersion(0),
      m_cCdmRights(this),
      m_rpCdmGroup(nullptr),
      m_bPersistent(true),
      m_bIsTree(true)
{
    SetVariant(p_qMember);
}

CdmMember::~CdmMember(  )
{
}

void CdmMember::SetVariant(QVariantMap& p_rqvMember)
{
    CdmModelElement::SetVariant(p_rqvMember);
    m_eDmValue = static_cast<EdmValueType>(p_rqvMember[WMS_VALUETYPE].toInt());
    m_eDmMemberAccess = static_cast<EdmMemberAccess>(p_rqvMember[WMS_ACCESS].toInt());
    m_bSystem = p_rqvMember[WMS_SYSTEMVALUE].toBool();
    m_bOwner = p_rqvMember[WMS_OWNER].toBool();
    m_qvDefaultValue = p_rqvMember[WMS_DEFAULT].toString();
    m_lCounterStart = p_rqvMember[WMS_COUNTERSTART].toInt();
    m_lReference  = p_rqvMember[WMS_REFERENCE].toInt();
    m_lClassId = p_rqvMember[WMS_CLASSID].toInt();
    m_qstrComment = p_rqvMember[WMS_COMMENT].toString();
    m_qstrValidationCode = p_rqvMember[WMS_VALIDATION].toString();
    m_bPersistent = p_rqvMember[WMS_PERSISTENT].toBool();
    m_bMust = p_rqvMember[WMS_MUST].toBool();
    m_bIsTree = p_rqvMember[WMS_TREE].toBool();
    m_lSize = p_rqvMember[WMS_SIZE].toInt();
    SetPrefix(p_rqvMember[WMS_PREFIX].toString());
    SetSuffix(p_rqvMember[WMS_SUFFIX].toString());
    SetDecimalCountInput(p_rqvMember[WMS_DECIMALCOUNTINPUT].toInt());
    SetDecimalCountOutput(p_rqvMember[WMS_DECIMALCOUNTOUTPUT].toInt());

    QVariantMap qmRights = p_rqvMember[WMS_RIGHTS].toMap();
    m_cCdmRights.SetVariant(qmRights);

    QVariantMap qvAnnotations = p_rqvMember[WMS_ANNOTATION].toMap();
    QVariantMap qvTranslations = qvAnnotations[WMS_TRANSLATIONS].toMap();

    QVariantMap::iterator qvIt = qvTranslations.begin();
    QVariantMap::iterator qvItEnd = qvTranslations.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QString iId = qvIt.key();
        QVariantMap qvHash = qvIt.value().toMap();

        QString qstrTranslation = qvHash[WMS_TRANSLATION].toString();
        QString qstrComment = qvHash[WMS_COMMENT].toString();
        StringPair pair(qstrTranslation, qstrComment);
        m_qmTranslations.insert(iId, pair);
    }

    QString qstrCategory = p_rqvMember[WMS_CATEGORY].toString();

    if (!qstrCategory.isEmpty())
    {
        CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            m_rpCdmGroup = pCdmClass->FindGroupByName(qstrCategory);
        }
    }

    SetModified();
}

void CdmMember::Deploy(QVariantMap& p_rqvMember)
{
    CdmModelElement::Deploy(p_rqvMember);
    m_eDmValue = static_cast<EdmValueType>(p_rqvMember[WMS_VALUETYPE].toInt());
    m_eDmMemberAccess = static_cast<EdmMemberAccess>(p_rqvMember[WMS_ACCESS].toInt());
    m_bSystem = p_rqvMember[WMS_SYSTEMVALUE].toBool();
    m_bOwner = p_rqvMember[WMS_OWNER].toBool();
    m_qvDefaultValue = p_rqvMember[WMS_DEFAULT].toString();
    m_lCounterStart = p_rqvMember[WMS_COUNTERSTART].toInt();
    m_lReference  = p_rqvMember[WMS_REFERENCE].toInt();
    m_qstrComment = p_rqvMember[WMS_COMMENT].toString();
    m_qstrValidationCode = p_rqvMember[WMS_VALIDATION].toString();
    m_bPersistent = p_rqvMember[WMS_PERSISTENT].toBool();
    m_bIsTree = p_rqvMember[WMS_TREE].toBool();
    m_bMust = p_rqvMember[WMS_MUST].toBool();
    m_lSize = p_rqvMember[WMS_SIZE].toInt();
    SetPrefix(p_rqvMember[WMS_PREFIX].toString());
    SetSuffix(p_rqvMember[WMS_SUFFIX].toString());
    SetDecimalCountInput(p_rqvMember[WMS_DECIMALCOUNTINPUT].toInt());
    SetDecimalCountOutput(p_rqvMember[WMS_DECIMALCOUNTOUTPUT].toInt());
    m_bUnique = p_rqvMember[WMS_UNIQUE].toBool();

    if (m_eDmValue == eDmValueObjectRef ||
            m_eDmValue == eDmValueContainerRef)
    {
        QString qstrUri = p_rqvMember[WMS_REFERENCEURI].toString();
        CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

        if (!qstrUri.isEmpty() && CHKPTR(pManager))
        {
            CdmModelElement* pElement = dynamic_cast<CdmModelElement*>(pManager->GetUriObject(qstrUri));

            if (pElement)
            {
                m_lReference = pElement->GetId();
            }
            else // class not yet created so i have to create it.
            {
                CdmClassManager* pClassManager = GetClassManager();

                if (CHKPTR(pClassManager))
                {
                    QString qstrKeyname = p_rqvMember[WMS_REFERENCEKEYNAME].toString();

                    if (!qstrKeyname.isEmpty())
                    {
                        CdmPackage* pPackage = pClassManager->FindPackageByClassUri(qstrUri);
                        CdmClass* pClass = pClassManager->CreateClass(qstrKeyname, pPackage);

                        if (CHKPTR(pClass))
                        {
                            m_lReference = pClass->GetId();
                        }
                    }
                }
            }
        }
    }

    QVariantMap qvAnnotations = p_rqvMember[WMS_ANNOTATION].toMap();
    QVariantMap qvTranslations = qvAnnotations[WMS_TRANSLATIONS].toMap();
    QVariantMap::iterator qvIt = qvTranslations.begin();
    QVariantMap::iterator qvItEnd = qvTranslations.end();

    for (; qvIt != qvItEnd; ++qvIt)
    {
        QString iId = qvIt.key();
        QVariantMap qvHash = qvIt.value().toMap();

        QString qstrTranslation = qvHash[WMS_TRANSLATION].toString();
        QString qstrComment = qvHash[WMS_COMMENT].toString();
        StringPair pair(qstrTranslation, qstrComment);
        m_qmTranslations.insert(iId, pair);
    }

    QString qstrCategory = p_rqvMember[WMS_CATEGORY].toString();

    if (!qstrCategory.isEmpty())
    {
        CdmClass* pCdmClass = GetClass();

        if (CHKPTR(pCdmClass))
        {
            m_rpCdmGroup = pCdmClass->FindGroupByName(qstrCategory);
        }
    }

    SetModified();
}

bool CdmMember::IsMust(  ) const
{
    bool bRet = m_bMust;

    if (m_eDmValue == eDmValueListDouble ||
            m_eDmValue == eDmValueListInt ||
            m_eDmValue == eDmValueListString ||
            m_eDmValue == eDmValueDictIntInt ||
            m_eDmValue == eDmValueDictIntDouble ||
            m_eDmValue == eDmValueDictIntString ||
            m_eDmValue == eDmValueDictStringDouble ||
            m_eDmValue == eDmValueDictStringInt ||
            m_eDmValue == eDmValueDictStringString)
    {
        bRet = false;
    }

    return bRet;
}

void CdmMember::SetMustValue(bool p_bMust)
{
    m_bMust = p_bMust;
    SetModified();
}

void CdmMember::SetSize(qint64 p_lSize)
{
    m_lSize = p_lSize;
    SetModified();
}

qint64 CdmMember::GetSize() const
{
    return m_lSize;
}

EdmValueType CdmMember::GetValueType() const
{
    return m_eDmValue;
}

void CdmMember::SetOwner(bool p_bOwner)
{
    m_bOwner = p_bOwner;
    SetModified();
}

bool CdmMember::IsOwner() const
{
    return m_bOwner;
}

void CdmMember::SetUnique(bool p_bUnique)
{
    m_bUnique = p_bUnique;
    SetModified();
}

bool CdmMember::IsUnique() const
{
    return m_bUnique;
}

void CdmMember::SetValueType(EdmValueType p_eDmValue)
{
    if (p_eDmValue != m_eDmValue)
    {
        SetTemporaryData(WMS_MEMBER_ORIGINAL_VALUE_TYPE, m_eDmValue);
        m_eDmValue = p_eDmValue;
        SetModified();
    }
}

void CdmMember::SetDefaultValue(const bool p_bDefault)
{
    m_qvDefaultValue = p_bDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const QString p_qstDefault)
{
    m_qvDefaultValue = p_qstDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const int p_iDefault)
{
    m_qvDefaultValue = p_iDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const qint64 p_lDefault)
{
    m_qvDefaultValue = p_lDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const double p_dDefault)
{
    m_qvDefaultValue = p_dDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const float p_fDefault)
{
    m_qvDefaultValue = p_fDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const QDate p_qdDefault)
{
    m_qvDefaultValue = p_qdDefault;
    SetModified();
}

void CdmMember::SetDateDefaultValue(const qint64 p_lDefault)
{
    m_qvDefaultValue = ChangeLongToDate(p_lDefault);
    SetModified();
}

void CdmMember::SetDateTimeDefaultValue(const double p_dDefault)
{
    m_qvDefaultValue = p_dDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const QDateTime p_qdtDefault)
{
    m_qvDefaultValue = p_qdtDefault;
    SetModified();
}

void CdmMember::SetDefaultValue(const QTime p_qtDefault)
{
    m_qvDefaultValue = p_qtDefault;
    SetModified();
}

void CdmMember::SetTimeDefaultValue(const double p_dDefault)
{
    m_qvDefaultValue = ChangeDoubleToTime(p_dDefault);
    SetModified();
}

void CdmMember::SetDefaultValue(const QVariant p_qvValue)
{
    m_qvDefaultValue = p_qvValue;
    SetModified();
}

void CdmMember::GetDefaultValue(bool& p_bDefault) const
{

    p_bDefault = m_qvDefaultValue.toBool();
}

void CdmMember::GetDefaultValue(QString& p_qstDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_qstDefault = qstrValue;
}

void CdmMember::GetDefaultValue(int& p_iDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_iDefault = qstrValue.toInt();
}

void CdmMember::GetDefaultValue(qint64& p_lDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_lDefault = qstrValue.toInt();
}

void CdmMember::GetDefaultValue(double& p_dDefault) const
{
    p_dDefault = m_qvDefaultValue.toDouble();
}

void CdmMember::GetDefaultValue(float& p_fDefault) const
{
    p_fDefault = m_qvDefaultValue.toDouble();
}

void CdmMember::GetDefaultValue(QDate& p_qdDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_qdDefault = QDate::fromString(qstrValue, Qt::ISODate);
}

void CdmMember::GetDateDefaultValue(qint64& p_lDefault) const
{
    p_lDefault = ChangeDateToLong(m_qvDefaultValue.toDate());
}

void CdmMember::GetDefaultValue(QDateTime& p_qdtDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_qdtDefault = QDateTime::fromString(qstrValue, Qt::ISODate);
    qstrValue = p_qdtDefault.toString();
}

void CdmMember::GetDateTimeDefaultValue(double& p_dDefault) const
{
    p_dDefault = ChangeDateTimeToDouble(m_qvDefaultValue.toDateTime());
}

void CdmMember::GetDefaultValue(QTime& p_qtDefault) const
{
    QString qstrValue = m_qvDefaultValue.toString();

    if (CdmSystemVariables::IsSystemValue(qstrValue))
    {
        qstrValue = CdmSystemVariables::GetValueAsString(qstrValue);
    }

    p_qtDefault = QTime::fromString(qstrValue, Qt::ISODate);
}

void CdmMember::GetTimeDefaultValue(double& p_dDefault) const
{
    p_dDefault = ChangeTimeToDouble(m_qvDefaultValue.toTime());
}

QVariant CdmMember::GetDefaultValue() const
{
    return m_qvDefaultValue;
}

void CdmMember::SetClassId(qint64 p_lClassId)
{
    m_lClassId = p_lClassId;
    SetModified();
}

qint64 CdmMember::GetClassId() const
{
    return m_lClassId;
}

CdmClass* CdmMember::GetClass() const
{
    CdmClass* pCdmClass = nullptr;
    CdmClassManager* pClassManager = GetClassManager();

    if (CHKPTR(pClassManager))
    {
        pCdmClass = pClassManager->FindClassById(m_lClassId);
    }

    return pCdmClass;
}

bool CdmMember::IsExportType(EdmValueType p_eType)
{
    if (p_eType == eDmValueListObjects &&
            p_eType == eDmValueContainerRef)
    {
        return false;
    }

    return true;
}

void CdmMember::SetComment(QString p_qstrComment)
{
    m_qstrComment = p_qstrComment;
    SetModified();
}

QString CdmMember::GetComment() const
{
    QString qstrRet = m_qstrComment;
    CdmScheme* pCdmDatabase = GetScheme();

    if (CHKPTR(pCdmDatabase))
    {
        QString qstrLanguage = pCdmDatabase->GetCurrentLanguageName();

        if (!qstrLanguage.isEmpty())
        {
            qstrRet = GetTranslationComment(qstrLanguage);
        }
    }

    return qstrRet;
}

void CdmMember::SetClassReference(qint64 p_lReference)
{
    m_lReference = p_lReference;
    SetModified();
}

void CdmMember::SetClassReference(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        SetClassReference(p_pClass->GetId());
    }
}
CdmClass* CdmMember::GetClassReferencePtr() const
{
    if (m_lReference > 0)
    {
        CdmClassManager* pCdmClassManager = GetClassManager();
        if(CHKPTR(pCdmClassManager))
        {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(m_lReference);

            if(CHKPTR(pCdmClass))
            {
                return pCdmClass;
            }
        }
    }

    return nullptr;
}

qint64 CdmMember::GetClassReference() const
{
    return m_lReference;
}

void CdmMember::SetCounterStart(qint64 p_lCounterStart)
{
    m_lCounterStart = p_lCounterStart;
    SetModified();
}

qint64 CdmMember::GetCounterStart() const
{
    return m_lCounterStart;
}

void CdmMember::SetClassReference(QString p_qstrClassName)
{
    CdmClass* pCdmClassReference = nullptr;

    CdmClassManager* pCdmClassManager = GetClassManager();

    if (CHKPTR(pCdmClassManager))
    {
        pCdmClassReference = pCdmClassManager->FindClassByKeyname(p_qstrClassName);

        if(pCdmClassReference)
        {
            SetClassReference(pCdmClassReference->GetId());
        }
        else
        {
            ERR("Class " + p_qstrClassName + " does not exist!");
        }
    }
}

QString CdmMember::GenerateDocument()
{
    QString qstrDocument;
    qstrDocument += "<tr>";
    qstrDocument += "<td>" + GetKeyname() + "</td>";
    qstrDocument += "<td>" + GetValueTypeAsString() + "</td>";
    qstrDocument += "<td>" + GetComment() + "</td>";
    qstrDocument += "<td>";
    qstrDocument += m_qvDefaultValue.toString();
    qstrDocument += "</td>";
    qstrDocument += "<td>";

    if (m_lReference > 0)
    {
        CdmClass* pCdmClass = GetClassReferencePtr();

        if(CHKPTR(pCdmClass))
        {
            qstrDocument += pCdmClass->GetKeyname();
        }
    }

    qstrDocument += "</td>";
    qstrDocument += "</tr>";
    return qstrDocument;
}

QString CdmMember::GetValueTypeAsString() const
{
    return GetValueTypeAsString(m_eDmValue);
}

QString CdmMember::GetValueTypeAsString(EdmValueType p_eValue)
{
    QString qstrValue;

    switch(p_eValue)
    {
    case eDmValueBool:
        qstrValue = tr("bool");
        break;
    case eDmValueInt:
        qstrValue = tr("int");
        break;
    case eDmValueLong:
        qstrValue = tr("qint64");
        break;
    case eDmValueFloat:
        qstrValue = tr("float");
        break;
    case eDmValueDouble:
        qstrValue = tr("double");
        break;
    case eDmValueString:
        qstrValue = tr("string");
        break;
    case eDmValueDate:
        qstrValue = tr("date");
        break;
    case eDmValueTime:
        qstrValue = tr("time");
        break;
    case eDmValueDateTime:
        qstrValue = tr("timestamp");
        break;
    case eDmValueObjectRef:
        qstrValue = tr("object reference");
        break;
    case eDmValueContainerRef:
        qstrValue = tr("container reference");
        break;
    case eDmValueCounter:
        qstrValue = tr("counter");
        break;
    case eDmValueBinaryDocument:
        qstrValue = tr("binray document");
        break;
    case eDmValueCharacterDocument:
        qstrValue = tr("text document");
        break;
    case eDmValueListDouble:
        qstrValue = tr("list<double>");
        break;
    case eDmValueListObjects:
        qstrValue = tr("list<object reference>");
        break;
    case eDmValueListInt:
        qstrValue = tr("list<qint64>");
        break;
    case eDmValueListString:
        qstrValue = tr("list<string>");
        break;
    case eDmValueDictIntInt:
        qstrValue = tr("map<qint64,qint64>");
        break;
    case eDmValueDictIntDouble:
        qstrValue = tr("map<qint64,double>");
        break;
    case eDmValueDictIntString:
        qstrValue = tr("map<qint64,string>");
        break;
    case eDmValueDictStringDouble:
        qstrValue = tr("map<string,double>");
        break;
    case eDmValueDictStringInt:
        qstrValue = tr("map<string,qint64>");
        break;
    case eDmValueDictStringString:
        qstrValue = tr("map<string,string>");
        break;
    case eDmValueUserGroup:
        qstrValue = tr("user group");
        break;
    case eDmValueUser:
        qstrValue = tr("user");
        break;
    case eDmValueEnum:
        qstrValue = tr("enum");
        break;
    case eDmValueFormula:
        qstrValue = tr("formula");
        break;
    case eDmValueArray:
        qstrValue = tr("array");
        break;
    default:
        qstrValue = tr("invalid");
    };

    return qstrValue;
}

bool CdmMember::IsDisplayMember() const
{
    bool bRet = false;

    if (IsPersistent())
    {
        switch(m_eDmValue)
        {
        case eDmValueBool:
        case eDmValueInt:
        case eDmValueLong:
        case eDmValueFloat:
        case eDmValueDouble:
        case eDmValueString:
        case eDmValueDate:
        case eDmValueTime:
        case eDmValueDateTime:
        case eDmValueCounter:
        case eDmValueUser:
        case eDmValueEnum:
            bRet = true;
            break;
        default:
            bRet = false;
        };
    }

    return bRet;
}

bool CdmMember::IsNumber() const
{
    bool bRet = false;

    switch(m_eDmValue)
    {
    case eDmValueInt:
    case eDmValueLong:
    case eDmValueFloat:
    case eDmValueDouble:
    case eDmValueCounter:
        bRet = true;
        break;
    default:
        bRet = false;
        break;
    };

    return bRet;
}

bool CdmMember::IsList() const
{
    bool bRet = false;

    switch(m_eDmValue)
    {
    case eDmValueListString:
    case eDmValueListInt:
    case eDmValueListDouble:
    case eDmValueListObjects:
        bRet = true;
        break;
    default:
        bRet = false;
        break;
    };

    return bRet;
}

bool CdmMember::IsMap() const
{
    bool bRet = false;

    switch(m_eDmValue)
    {
    case eDmValueDictIntDouble:
    case eDmValueDictIntInt:
    case eDmValueDictIntString:
    case eDmValueDictStringDouble:
    case eDmValueDictStringInt:
    case eDmValueDictStringString:
        bRet = true;
        break;
    default:
        bRet = false;
        break;
    };

    return bRet;
}

bool CdmMember::IsSystemMember() const
{
    return m_bSystem;
}

void CdmMember::SetSystemFlag(bool p_bSystem)
{
    m_bSystem = p_bSystem;
    SetModified();
}

EdmMemberAccess CdmMember::GetAccessMode() const
{
    return m_eDmMemberAccess;
}

QString CdmMember::GetAccessModeAsString() const
{
    switch (m_eDmMemberAccess)
    {
    case eDmMemberAccessPrivate:
        return WMS_ACCESS_PRIVATE;
        break;
    case eDmMemberAccessProtected:
        return WMS_ACCESS_PROTECTED;
        break;
    case eDmMemberAccessPublic:
        return WMS_ACCESS_PUBLIC;
        break;
    default:
        return "Unknown";
    }
}

void CdmMember::SetMemberAccess(EdmMemberAccess p_eDmMemberAccess)
{
    m_eDmMemberAccess = p_eDmMemberAccess;
    SetModified();
}

int CdmMember::GetVersion() const
{
    return m_iVersion;
}

void CdmMember::SetVersion(int p_iVersion)
{
    if (m_iVersion != p_iVersion)
    {
        m_iVersion = p_iVersion;
        SetModified();
    }
}

void CdmMember::SetGroup(CdmClassGroup* p_pCdmGroup)
{
    if (m_rpCdmGroup != p_pCdmGroup)
    {
        m_rpCdmGroup = p_pCdmGroup;
        SetModified();
    }
}

const CdmClassGroup* CdmMember::GetGroup() const
{
    return m_rpCdmGroup;
}

QString CdmMember::GetGroupName() const
{
    QString qstrRet;

    if (m_rpCdmGroup)
    {
        qstrRet = m_rpCdmGroup->GetName();
    }

    return qstrRet;
}

QVariant CdmMember::GetMemberAlignment() const
{

    QVariant qVariant = int(Qt::AlignLeft | Qt::AlignVCenter);

    if (GetValueType() == eDmValueInt ||
            GetValueType() == eDmValueFloat ||
            GetValueType() == eDmValueDouble ||
            GetValueType() == eDmValueCounter)
    {
        qVariant = int(Qt::AlignRight | Qt::AlignVCenter);
    }

    return qVariant;
}

QString CdmMember::ConvertValueToDisplayString(QVariant p_qvValue) const
{
    QString qstrRet;

    switch (GetValueType())
    {
    case eDmValueBool:

        if (p_qvValue.toInt() == 0)
        {
            qstrRet = qApp->tr("Nein");
        }
        else
        {
            qstrRet = qApp->tr("Ja");
        }

        break;
    case eDmValueInt:
        qstrRet = GetPrefix();

        if (!GetDisplayConfig().isEmpty())
        {
            qstrRet = QString::asprintf(GetDisplayConfig().toLatin1(), p_qvValue.toInt());
        }
        else
        {
            qstrRet += p_qvValue.toString();
        }

        qstrRet += GetSuffix();
        break;
    case eDmValueFloat:
    case eDmValueDouble:
    {
        qstrRet = GetPrefix();
        QLocale qlDefault;

        if (GetDecimalCountOutput() > 0)
        {
            qstrRet += qlDefault.toString(p_qvValue.toDouble(), 'f', GetDecimalCountOutput());
        }
        else
        {
            qstrRet += qlDefault.toString(p_qvValue.toDouble(), 'f', 2);
        }

        qstrRet += GetSuffix();
        break;
    }
    case eDmValueString:
    case eDmValueCharacterDocument:
    {
        QTextDocument qtext;
        qtext.setHtml(p_qvValue.toString());
        qstrRet = qtext.toPlainText();
        break;
    }
    case eDmValueDate:
    {
        QDate qDate = p_qvValue.toDate();

        if (qDate.isValid() && qDate < QDate(2200,12,31))
        {
            qstrRet = p_qvValue.toDate().toString(Qt::LocalDate);
        }
        else
        {
            qstrRet = "-";
        }

        break;
    }
    case eDmValueDateTime:
        qstrRet = p_qvValue.toDateTime().toString(Qt::LocalDate);
        break;
    case eDmValueTime:
        qstrRet = p_qvValue.toTime().toString(Qt::LocalDate);
        break;
    case eDmValueUser:
    {
        CumUser* pCumUser = nullptr;
        int iId = p_qvValue.toInt();

        if (iId > 0)
        {
            CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

            if (CHKPTR(pCdmManager))
            {
                CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

                if (CHKPTR(pCumUserManager))
                {
                    pCumUser = pCumUserManager->FindUserById(iId);
                    if (pCumUser)
                    {
                        qstrRet = pCumUser->GetLastName() + " " + pCumUser->GetFirstName();
                    }
                    else
                    {
                        qstrRet = "Unknown User";
                    }

                }
            }
        }

    }
        break;
    case eDmValueEnum:
    {
        QString qstrCode = GetValidationCode();
        QStringList qstrlSelection = qstrCode.split(",");

        int iPos = p_qvValue.toInt();

        if (iPos >= 0 && iPos < qstrlSelection.count())
        {
            qstrRet = qstrlSelection[p_qvValue.toInt()];
        }
    }
        break;
    case eDmValueListString:
    {
        QString qstrDocument = p_qvValue.toString();
        QList<QString> qllValues;
        CdmValueListString::DeserializeXmlToStringList(qstrDocument, qllValues);

        for (auto qllIt = qllValues.begin(); qllIt != qllValues.end();++qllIt)
        {
            qstrRet += *qllIt + " ";
        }
    }
        break;
    case eDmValueListDouble:
    {
        QString qstrDocument = p_qvValue.toString();
        QList<double> qllValues;
        CdmValueListDouble::DeserializeXmlToDoubleList(qstrDocument, qllValues);
        QLocale loc;

        for (auto qllIt = qllValues.begin(); qllIt != qllValues.end();++qllIt)
        {
            qstrRet += loc.toString(*qllIt, 'f', GetDecimalCountOutput()) + " ";
        }
    }
        break;
    case eDmValueListInt:
    {
        QString qstrDocument = p_qvValue.toString();
        QList<int> qllValues;
        CdmValueListInt::DeserializeXmlToIntList(qstrDocument, qllValues);
        QLocale loc;

        for (auto qllIt = qllValues.begin(); qllIt != qllValues.end();++qllIt)
        {
            qstrRet += loc.toString(*qllIt) + " ";
        }
    }
        break;
    case eDmValueDictIntInt:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<int,int> qmValues;
        CdmValueDictIntInt::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + loc.toString(qmIt.key()) + "-" + loc.toString(qmIt.value()) +"] ";
        }
    }
        break;
    case eDmValueDictIntDouble:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<int,double> qmValues;
        CdmValueDictIntDouble::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + loc.toString(qmIt.key()) + "-" + loc.toString(qmIt.value(), 'f') +"] ";
        }
    }
        break;
    case eDmValueDictIntString:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<int,QString> qmValues;
        CdmValueDictIntString::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + loc.toString(qmIt.key()) + "-" + qmIt.value() + "] ";
        }
    }
        break;
    case eDmValueDictStringDouble:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<QString, double> qmValues;
        CdmValueDictStringDouble::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + qmIt.key() + "-" + loc.toString(qmIt.value(), 'f') + "] ";
        }
    }
        break;
    case eDmValueDictStringInt:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<QString, int> qmValues;
        CdmValueDictStringInt::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + qmIt.key() + "-" + loc.toString(qmIt.value()) + "] ";
        }
    }
        break;
    case eDmValueDictStringString:
    {
        QString qstrDocument = p_qvValue.toString();
        QMap<QString, QString> qmValues;
        CdmValueDictStringString::DeserializeXmlToMap(qstrDocument, qmValues);
        QLocale loc;

        for (auto qmIt = qmValues.begin(); qmIt != qmValues.end();++qmIt)
        {
            qstrRet += "[" + qmIt.key() + "-" + qmIt.value() + "] ";
        }
    }
        break;
    default:
        qstrRet = p_qvValue.toString();
    }

    return qstrRet;
}

void CdmMember::XmlExport(QDomElement& p_rqdeClassMembers) const
{
    QDomDocument qddDocument = p_rqdeClassMembers.ownerDocument();
    QDomElement qdeRoot = qddDocument.createElement(WMS_MEMBER);
    p_rqdeClassMembers.appendChild(qdeRoot);

    XmlExportBase(qdeRoot);

    qdeRoot.setAttribute(WMS_MUST, ChangeBoolToString(m_bMust));
    qdeRoot.setAttribute(WMS_VALUETYPE, QString::number(m_eDmValue));
    qdeRoot.setAttribute(WMS_CLASSID, QString::number(m_lClassId));
    qdeRoot.setAttribute(WMS_COUNTERSTART, QString::number(m_lCounterStart));
    qdeRoot.setAttribute(WMS_REFERENCE, QString::number(m_lReference));
    qdeRoot.setAttribute(WMS_SIZE, QString::number(m_lSize));
    qdeRoot.setAttribute(WMS_COMMENT, m_qstrComment);
    qdeRoot.setAttribute(WMS_DEFAULT, m_qvDefaultValue.toString());
}

void CdmMember::XmlImportMember(QDomElement& p_rqdeClassMembers)
{
    m_bMust         = ChangeStringToBool(p_rqdeClassMembers.attribute(WMS_MUST,          ""));
    m_eDmValue      = EdmValueType(p_rqdeClassMembers.attribute(WMS_VALUETYPE,               "").toInt());
    m_lClassId      = p_rqdeClassMembers.attribute(WMS_CLASSID,                          "").toInt();
    m_lCounterStart = p_rqdeClassMembers.attribute(WMS_COUNTERSTART,                     "").toInt();
    m_lReference    = p_rqdeClassMembers.attribute(WMS_REFERENCE,                        "").toInt();
    m_lSize         = p_rqdeClassMembers.attribute(WMS_SIZE,                             "").toInt();
    m_qstrComment   = p_rqdeClassMembers.attribute(WMS_COMMENT,                          "");
    m_qvDefaultValue = p_rqdeClassMembers.attribute(WMS_DEFAULT, "");
}

void CdmMember::XmlImport(  QDomElement& p_rqdeClassMembers )
{
    XmlImportBase(p_rqdeClassMembers);
    XmlImportMember(p_rqdeClassMembers);
}

QVariant CdmMember::GetVariant() const
{
    QVariantMap qmVariant = CdmModelElement::GetVariant().toMap();
    qmVariant.insert(WMS_CAPTION, GetCaption());
    qmVariant.insert(WMS_VALUETYPE, m_eDmValue);
    qmVariant.insert(WMS_VALUETYPENAME, GetEmfType());
    qmVariant.insert(WMS_ACCESS, m_eDmMemberAccess);
    qmVariant.insert(WMS_SYSTEMVALUE, m_bSystem);
    qmVariant.insert(WMS_OWNER, m_bOwner);
    qmVariant.insert(WMS_VALIDATION, m_qstrValidationCode);
    qmVariant.insert(WMS_DEFAULT, m_qvDefaultValue.toString());
    qmVariant.insert(WMS_COUNTERSTART, m_lCounterStart);
    qmVariant.insert(WMS_CLASSID, m_lClassId);
    qmVariant.insert(WMS_COMMENT, GetComment());
    qmVariant.insert(WMS_PERSISTENT, m_bPersistent);
    qmVariant.insert(WMS_MUST, m_bMust);
    qmVariant.insert(WMS_TREE, m_bIsTree);
    qmVariant.insert(WMS_PREFIX, GetPrefix());
    qmVariant.insert(WMS_SUFFIX, GetSuffix());
    qmVariant.insert(WMS_DECIMALCOUNTINPUT, GetDecimalCountInput());
    qmVariant.insert(WMS_DECIMALCOUNTOUTPUT, GetDecimalCountOutput());
    qmVariant.insert(WMS_UNIQUE, m_bUnique);
    qmVariant.insert(WMS_RIGHTS, m_cCdmRights.GetVariant());
    QVariant qvVariant(m_lReference);
    qmVariant.insert(WMS_REFERENCE, qvVariant);

    if (m_lReference > 0 && (m_eDmValue == eDmValueContainerRef || m_eDmValue == eDmValueObjectRef))
    {
        CdmClass* pClass = GetClassReferencePtr();

        if (pClass)
        {
            qmVariant.insert(WMS_REFERENCEURI, pClass->GetUriInternal());
            qmVariant.insert(WMS_REFERENCEKEYNAME, pClass->GetKeyname());
        }
    }

    if (m_rpCdmGroup)
    {
        qmVariant.insert(WMS_CATEGORY, m_rpCdmGroup->GetName());
    }

    QVariantMap qvAnnotations;

    QMap<QString, StringPair>::const_iterator qmIt = m_qmTranslations.begin();
    QMap<QString, StringPair>::const_iterator qmItEnd = m_qmTranslations.end();
    QVariantMap qmTranslations;

    for (; qmIt != qmItEnd; ++qmIt)
    {
        QString iId = qmIt.key();
        StringPair pair = qmIt.value();
        QVariantMap qvTranslation;
        qvTranslation.insert(WMS_TRANSLATION, pair.first);
        qvTranslation.insert(WMS_COMMENT, pair.second);
        qmTranslations.insert(iId, qvTranslation);
    }

    qvAnnotations.insert(WMS_TRANSLATION, qmTranslations);
    qmVariant.insert(WMS_ANNOTATION, qvAnnotations);
    return qmVariant;
}

bool CdmMember::CheckWriteAccess() const
{
    return m_cCdmRights.HasCurrentUserWriteAccess();
}

bool CdmMember::CheckReadAccess() const
{
    return m_cCdmRights.HasCurrentUserReadAccess();
}

CdmRights& CdmMember::GetRights()
{
    return m_cCdmRights;
}

bool CdmMember::HasValidation() const
{
    return !m_qstrValidationCode.isEmpty();
}

QString CdmMember::GetValidationCode() const
{
    return m_qstrValidationCode;
}

QString CdmMember::GetValidationCodeBase64() const
{
    QByteArray ba;
    ba.append(m_qstrValidationCode);
    return ba.toBase64();
}

void CdmMember::SetValidationCode(QString p_qstrCode)
{
    if (m_qstrValidationCode != p_qstrCode)
    {
        m_qstrValidationCode = p_qstrCode;
        SetModified();
    }
}

QString CdmMember::GetCaption() const
{
    QString qstrRet;
    CdmScheme* pCdmDatabase = GetScheme();

    if (CHKPTR(pCdmDatabase))
    {
        QString qstrLanguage = pCdmDatabase->GetCurrentLanguageName();

        if (!qstrLanguage.isEmpty())
        {
            qstrRet = GetTranslation(qstrLanguage);
        }
    }

    if (qstrRet.isEmpty())
    {
        qstrRet = CdmModelElement::GetCaption();
    }

    return qstrRet;
}

void CdmMember::SetTranslation(QString p_qstrLanguage,
                               QString p_qstrTranslation,
                               QString p_qstrComment)
{
    CdmScheme* pScheme = GetScheme();

    if (CHKPTR(pScheme))
    {
        if (pScheme->GetLanguageId(p_qstrLanguage) > 0)
        {
            StringPair qPair(p_qstrTranslation, p_qstrComment);
            m_qmTranslations.insert(p_qstrLanguage, qPair);
            SetModified();
        }
        else
        {
            ERR("Language " + p_qstrLanguage + " for translation not found.");
        }
    }
}

QString CdmMember::GetTranslation(QString p_iLanguageId) const
{
    QString qstrRet;

    if (m_qmTranslations.contains(p_iLanguageId))
    {
        StringPair qPair = m_qmTranslations[p_iLanguageId];
        qstrRet = qPair.first;
    }

    return qstrRet;
}

QMap<QString, StringPair>& CdmMember::GetTranslations()
{
    return m_qmTranslations;
}

QStringList CdmMember::GetSelectionList() const
{
//    return GetSelectionMap().keys();
    QStringList qstrlSelection;
    QString qstrCode = GetValidationCode();
    qstrCode = qstrCode.replace(", ", ",");
    qstrlSelection = qstrCode.split(",", QString::SkipEmptyParts);
    return qstrlSelection;
}

QMap<QString, int> CdmMember::GetSelectionMap() const
{
    QStringList qstrlSelection;
    QString qstrCode = GetValidationCode();
    qstrCode = qstrCode.replace(", ", ",");
    qstrlSelection = qstrCode.split(",", QString::SkipEmptyParts);
    QMap<QString,int> qmValueSelection;
    int iValue = 0;

    for(int iPos = 0; iPos < qstrlSelection.count(); ++iPos)
    {
        QString qstrValue = qstrlSelection[iPos];

        if (qstrValue.contains("="))
        {
            QStringList qstrlValue = qstrValue.split("=", QString::SkipEmptyParts);

            if (qstrlValue.count() == 2)
            {
               QString qstrKeyname = qstrlValue[0].simplified();
               iValue = qstrlValue[1].simplified().toInt();
               qmValueSelection.insert(qstrKeyname, iValue);
            }
            else
            {
                ERR("Invalid Enum = definition expected: keyname = value. got: "+ qstrValue);
            }
        }
        else
        {
            qmValueSelection.insert(qstrValue,iValue++);
        }
    }

    return qmValueSelection;
}

QString CdmMember::GetTranslationComment(QString p_iLanguageId) const
{
    QString qstrRet;

    if (m_qmTranslations.contains(p_iLanguageId))
    {
        StringPair qPair = m_qmTranslations[p_iLanguageId];
        qstrRet = qPair.second;
    }

    return qstrRet;
}

void CdmMember::DeleteTranslation(QString p_iId)
{
    m_qmTranslations.remove(p_iId);
    SetModified();
}

bool CdmMember::IsPersistent() const
{
    return m_bPersistent;
}

void CdmMember::SetPersistent(bool p_bPersistent)
{
    m_bPersistent = p_bPersistent;
    SetModified();
}

void CdmMember::SetTree(bool p_bTree)
{
    m_bIsTree = p_bTree;
    SetModified();
}

bool CdmMember::IsTree() const
{
    return m_bIsTree;
}

bool CdmMember::IsMember() const
{

    return true;
}

QString CdmMember::GetUri() const
{
    QString qstrUri;
    const CdmClass* pClass = GetClass();

    if (CHKPTR(pClass))
    {
        qstrUri = CreateUri(WMS_URI_MEMBER, pClass->GetFullQualifiedName(), GetKeyname());
    }

    return qstrUri;
}

QString CdmMember::GetUriInternal() const
{
    QString qstrUri;
    const CdmClass* pClass = GetClass();

    if (CHKPTR(pClass))
    {
        qstrUri = CreateUriPath(WMS_URI_MEMBER, pClass->GetFullQualifiedName(), GetKeyname(), "");
    }

    return qstrUri;
}

QString CdmMember::GetEmfType() const
{
    QString qstrValue;

    switch(m_eDmValue)
    {
    case eDmValueBool:
        qstrValue = WMS_EMF_TYPE_BOOL;
        break;
    case eDmValueInt:
        qstrValue = WMS_EMF_TYPE_INT;
        break;
    case eDmValueLong:
        qstrValue = WMS_EMF_TYPE_LONG;
        break;
    case eDmValueFloat:
        qstrValue = WMS_EMF_TYPE_FLOAT;
        break;
    case eDmValueDouble:
        qstrValue = WMS_EMF_TYPE_DOUBLE;
        break;
    case eDmValueString:
        qstrValue = WMS_EMF_TYPE_STRING;
        break;
    case eDmValueDate:
        qstrValue = WMS_EMF_TYPE_DATE;
        break;
    case eDmValueTime:
        qstrValue = WMS_EMF_TYPE_TIME;
        break;
    case eDmValueDateTime:
        qstrValue = WMS_EMF_TYPE_DATETIME;
        break;
    case eDmValueObjectRef:
        qstrValue = WMS_EMF_TYPE_OBJECTREF;
        break;
    case eDmValueContainerRef:
    {
        qstrValue = WMS_EMF_TYPE_CONTAINER;
        CdmClass* pClass = GetClassReferencePtr();

        if (pClass)
        {
            qstrValue += "<" + pClass->GetKeyname() +">";
        }
        else
        {
            qstrValue += "<void>";
        }
    }
        break;
    case eDmValueCounter:
        qstrValue = WMS_EMF_TYPE_COUNTER;
        break;
    case eDmValueBinaryDocument:
        qstrValue = WMS_EMF_TYPE_BINARYDOCUMENT;
        break;
    case eDmValueCharacterDocument:
        qstrValue = WMS_EMF_TYPE_CHARACTERDOCUMENT;
        break;
    case eDmValueListDouble:
        qstrValue = WMS_EMF_TYPE_LISTDOUBLES;
        break;
    case eDmValueListInt:
        qstrValue = WMS_EMF_TYPE_LISTINTS;
        break;
    case eDmValueListObjects:
        qstrValue = "EEList<EObject>";
        break;
    case eDmValueListString:
        qstrValue = WMS_EMF_TYPE_LISTSTRINGS;
        break;
    case eDmValueDictIntInt:
        qstrValue = WMS_EMF_TYPE_DICTINTINT;
        break;
    case eDmValueDictIntDouble:
        qstrValue = WMS_EMF_TYPE_DICTINTDOUBLE;
        break;
    case eDmValueDictIntString:
        qstrValue = "EMap<EInt,EString>";
        break;
    case eDmValueDictStringDouble:
        qstrValue = WMS_EMF_TYPE_DICTSTRINGDOUBLE;
        break;
    case eDmValueDictStringInt:
        qstrValue = WMS_EMF_TYPE_DICTSTRINGINT;
        break;
    case eDmValueDictStringString:
        qstrValue = WMS_EMF_TYPE_DICTSTRINGSTRING;
        break;
    case eDmValueUserGroup:
        qstrValue = WMS_EMF_TYPE_USERGROUP;
        break;
    case eDmValueUser:
        qstrValue = WMS_EMF_TYPE_USER;
        break;
    case eDmValueEnum:
        qstrValue = WMS_EMF_TYPE_ENUM;
        break;
    case eDmValueFormula:
        qstrValue = WMS_EMF_TYPE_FORMULA;
        break;
    default:
        qstrValue = "WMS_EMF_TYPE_UNKNOWN";
    };

    return qstrValue;
}

bool CdmMember::IsValidationType() const
{
    bool bRet = false;

    switch (m_eDmValue)
    {
    case eDmValueBool:
    case eDmValueInt:
    case eDmValueLong:
    case eDmValueFloat:
    case eDmValueDouble:
    case eDmValueString:
    case eDmValueCharacterDocument:
    case eDmValueDate:
    case eDmValueDateTime:
    case eDmValueTime:
        bRet = true;
        break;
    default:
        break;
    }

    return bRet;
}

void CdmMember::SetKeyname(QString p_qstrKeyname)
{
    CdmModelElement::SetKeyname(p_qstrKeyname);
    SetModified();
}

void CdmMember::SetPrefix(QString p_qstrPrefix)
{
    SetConfigItem("prefix", p_qstrPrefix);
    SetModified();
}

QString CdmMember::GetPrefix() const
{
    return GetConfigItem("prefix").toString();
}

void CdmMember::SetDisplayConfig(QString p_qstrPrefix)
{
    SetConfigItem("displayConfig", p_qstrPrefix);
    SetModified();
}

QString CdmMember::GetDisplayConfig() const
{
    return GetConfigItem("displayConfig").toString();
}

void CdmMember::SetSuffix(QString p_qstrSuffix)
{
    SetConfigItem("suffix", p_qstrSuffix);
    SetModified();
}

QString CdmMember::GetSuffix() const
{
    return GetConfigItem("suffix").toString();
}

void CdmMember::SetDecimalCountInput(int p_iDecimalCount)
{
    SetConfigItem("decimalCountInput", p_iDecimalCount);
    SetModified();
}

int CdmMember::GetDecimalCountOutput() const
{
    return GetConfigItem("decimalCountInput").toInt();
}

void CdmMember::SetDecimalCountOutput(int p_iDecimalCount)
{
    SetConfigItem("decimalCountOutput", p_iDecimalCount);
    SetModified();
}

int CdmMember::GetDecimalCountInput() const
{
    return GetConfigItem("decimalCountOutput").toInt();
}

void CdmMember::SetRenderedCheck(QString p_qstrRendered)
{
    SetConfigItem("rendered", p_qstrRendered);
    SetModified();
}

void CdmMember::SetEnabledCheck(QString p_qstrRendered)
{
    SetConfigItem("enabled", p_qstrRendered);
    SetModified();
}

QString CdmMember::GetRenderedCheck() const
{
    return GetConfigItem("rendered").toString();
}

QString CdmMember::GetEnabledCheck() const
{
    return GetConfigItem("enabled").toString();
}
