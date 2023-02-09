// System and QT Includes
#include <QUuid>
#include <QString>
#include <QDateTime>
#include <qdom.h>
#include <QVariant>

// own Includes
#include "wmsdefines.h"
#include "CdmScheme.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
 #include "CdmSessionManager.h"
#include "CdmModelElement.h"

#include "CumUser.h"

CdmModelElement::CdmModelElement( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, QString p_qstrCaption )
: CdmModelElementBase(p_lDatabaseId),
   m_lId(p_lId),
   m_lModifierId(0),
   m_lCreatorId(0),
   m_qstrKeyname(p_qstrKeyname),
   m_qstrCaption(p_qstrCaption),
   m_bModified(false),
   m_bValid(true),
   m_bDeleted(false),
   m_bNew(false)

{
   if(m_lId < 0 || m_qstrKeyname.isEmpty())
   {
      INFO("ID or Keyname are missing, this object is not valid" );
      m_bValid = false;
   }

   if(m_lSchemeId < 0)
   {
      FATAL("DatabaseId is missing, this object is not valid" );
      m_bValid = false;
   }

   if (m_bValid)
   {
       SetKeyname(p_qstrKeyname);
   }
}

CdmModelElement::CdmModelElement(  QDomElement& p_rqDomElement )
: CdmModelElementBase(-1),
   m_lId(-1),
   m_lModifierId(0),
   m_lCreatorId(0),
   m_bModified(false),
   m_bValid(true),
   m_bDeleted(false),
   m_bNew(false)

{
   XmlImportBase(p_rqDomElement);

   if(m_lId < 0 || m_qstrKeyname.isEmpty())
   {
      FATAL("ID or Keyname are missing, this object is not valid" );
      m_bValid = false;
   }

   if(m_lSchemeId < 0)
   {
      FATAL("DatabaseId is missing, this object is not valid" );
      m_bValid = false;
   }

   m_bNew = true;
}

CdmModelElement::CdmModelElement(QVariant p_qvVariant)
: CdmModelElementBase(-1),
  m_lId(-1),
  m_lModifierId(0),
  m_lCreatorId(0),
  m_bModified(false),
  m_bValid(true),
  m_bDeleted(false),
  m_bNew(true)
{
   QVariantMap qvHash = p_qvVariant.toMap();
   SetVariant(qvHash);

   if (m_bValid)
   {
       SetKeyname(m_qstrKeyname);
   }
}

CdmModelElement::CdmModelElement()
: CdmModelElementBase(-1),
  m_lId(-1),
  m_lModifierId(0),
  m_lCreatorId(0),
  m_bModified(false),
  m_bValid(true),
  m_bDeleted(false),
  m_bNew(false)
{
}

CdmModelElement::~CdmModelElement(  )
{
   // nothing to do
}

void CdmModelElement::SetVariant(QVariantMap& p_rqvHash)
{
   SYNCHRONIZED_WRITE;

   if (p_rqvHash[WMS_ID].toInt() > 0)
   {
        m_lId = p_rqvHash[WMS_ID].toInt();
        SetModified();
   }

   if (m_qstrKeyname != p_rqvHash[WMS_KEYNAME].toString())
   {
        m_qstrKeyname = p_rqvHash[WMS_KEYNAME].toString();
        SetModified();
   }

   if (m_qstrCaption  != p_rqvHash[WMS_CAPTION].toString())
   {
        m_qstrCaption  = p_rqvHash[WMS_CAPTION].toString();
        SetModified();
   }

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
       CdmScheme* pScheme = pManager->GetCurrentScheme();

       if (CHKPTR(pScheme))
       {
        SetSchemeId(pScheme->GetId());
       }
   }
}

void CdmModelElement::Deploy(QVariantMap& p_rqvHash)
{
   SYNCHRONIZED_WRITE;
   if (m_qstrKeyname.isEmpty())
   {
        m_qstrKeyname = p_rqvHash[WMS_KEYNAME].toString();
   }

   m_qstrCaption  = p_rqvHash[WMS_CAPTION].toString();
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      m_lSchemeId = GetSchemeId();
   }
}

void CdmModelElement::SetId(qint64 p_lId)
{
   m_lId = p_lId;
}

qint64 CdmModelElement::GetId() const
{
   return m_lId.load();
}

QString CdmModelElement::GetKeyname() const
{
    SYNCHRONIZED_READ;
   return m_qstrKeyname;
}

QString CdmModelElement::GetOriginalKeyname() const
{
    SYNCHRONIZED_READ;
   return m_qstrOriginalKeyname;
}

QDateTime CdmModelElement::GetLastChange(  ) const
{
    SYNCHRONIZED_READ;
   return m_qdtLastChange;
}

void CdmModelElement::GetLastChange(double& p_dLastChange) const
{
    SYNCHRONIZED_READ;
   p_dLastChange = ChangeDateTimeToDouble(m_qdtLastChange);
}

void CdmModelElement::SetLastChange(QDateTime& p_qdDateTime)
{
    SYNCHRONIZED_WRITE;
   m_qdtLastChange = p_qdDateTime;
}

void CdmModelElement::SetLastChange(  double p_dLastChanged )
{
    SYNCHRONIZED_WRITE;
   m_qdtLastChange = ChangeDoubleToDateTime(p_dLastChanged);
}

void CdmModelElement::SetModified()
{
   SYNCHRONIZED_WRITE;
   m_bModified = true;
   m_qdtLastChange = QDateTime::currentDateTime();
   m_lModifierId = GetUserId();
}

bool CdmModelElement::IsValid() const
{
   return m_bValid.load();
}

void CdmModelElement::SetInvalid(  )
{
   m_bValid = false;
}

void CdmModelElement::SetValid(  )
{
   m_bValid = true;
}

void CdmModelElement::SetDeleted()
{
   m_bDeleted = true;
}

bool CdmModelElement::IsDeleted() const
{
   return m_bDeleted;
}

bool CdmModelElement::IsModified() const
{

   return m_bModified;
}

void CdmModelElement::SetCreatorId( qint64 p_lUserId )
{
   m_lCreatorId = p_lUserId;
}

qint64 CdmModelElement::GetCreatorId(  ) const
{
   return m_lCreatorId.load();
}

void CdmModelElement::SetModifierId( qint64 p_lUserId )
{
   m_lModifierId = p_lUserId;
}

qint64 CdmModelElement::GetModifierId() const
{
   return m_lModifierId.load();
}

void CdmModelElement::SetKeyname(QString p_qstrKeyname)
{
    SYNCHRONIZED_WRITE;
   m_qstrOriginalKeyname = m_qstrKeyname;
   m_qstrKeyname =  p_qstrKeyname.simplified();

   m_qstrKeyname = m_qstrKeyname.replace(QRegExp("[^A-Za-z0-9_]"), "_");
   m_qstrKeyname = m_qstrKeyname.replace(":", "_");
   m_qstrKeyname = m_qstrKeyname.replace(".", "_");
   m_qstrKeyname = m_qstrKeyname.replace(" ", "_");

   if (m_qstrKeyname.length() > 100)
   {
       m_qstrKeyname = m_qstrKeyname.right(100);
   }


   if (!CheckKeyname(m_qstrKeyname))
   {
       WARNING("Keyname does not match rules RegEx: [A-Za-z][A-Za-z0-9_]*");
   }
}

void CdmModelElement::SetNew()
{
   m_bNew = true;
   m_lCreatorId = GetUserId();
}

bool CdmModelElement::IsNew() const
{
   return m_bNew;
}

void CdmModelElement::ResetNewModified(  )
{
   m_bNew      = false;
   m_bModified = false;
}

void CdmModelElement::SetCaption(QString p_qstrCaption)
{
    SYNCHRONIZED_WRITE;
   m_qstrCaption = p_qstrCaption;
   SetModified();
}

QString CdmModelElement::GetCaption() const
{
    SYNCHRONIZED_READ;
   QString qstrRet = m_qstrCaption;

   if(qstrRet.isEmpty())
   {
      qstrRet = GetKeyname();
   }

   return qstrRet;
}

qint64 CdmModelElement::ChangeDateToLong(const QDate p_qdDate)
{
  qint64 lRet = 0;

   lRet = QDate(1900,1,1).daysTo(p_qdDate);

   return lRet;
}

QDate CdmModelElement::ChangeLongToDate( qint64 p_lDate )
{
   QDate qdDate(1900,1,1);

   qdDate = qdDate.addDays(p_lDate);

   return qdDate;
}

double CdmModelElement::ChangeTimeToDouble(  QTime p_qtTime )
{
   double dRet =0.0;

   // it starts on msec on and adds a msec afterwards to prevent negative values.
   dRet = (QTime(0,0,0, 1).msecsTo(p_qtTime) + 1) / 8640000;

   return dRet;
}

QTime CdmModelElement::ChangeDoubleToTime(  double p_dTime )
{
   QTime qtTime(0,0,0,0);

   double dMsecs = p_dTime * 8640000;
   qtTime = qtTime.addMSecs(dMsecs);

   return qtTime;
}

double CdmModelElement::ChangeDateTimeToDouble(QDateTime p_qdtDateTime) const
{
  qint64 lDate = ChangeDateToLong(p_qdtDateTime.date());
   double dTime = ChangeTimeToDouble(p_qdtDateTime.time());

   return dTime + lDate;
}

QDateTime CdmModelElement::ChangeDoubleToDateTime(  double p_dDateTime )
{
   QDateTime qdtDateTime;

  qint64 lDate = (qint64)p_dDateTime;
   double dTime = lDate - p_dDateTime;
   QDate qdDate = ChangeLongToDate(lDate);
   QTime qtTime = ChangeDoubleToTime(dTime);

   qdtDateTime.setDate(qdDate);
   qdtDateTime.setTime(qtTime);

   return qdtDateTime;
}

QString CdmModelElement::ChangeBoolToString(bool p_bValue)
{
   QString qstrRet = "Unknown";
   if(p_bValue)
   {
      qstrRet = "true";
   }
   else
   {
      qstrRet = "false";
   }

   return qstrRet;
}

bool CdmModelElement::ChangeStringToBool(QString p_qstrBool)
{
   bool bRet = false;

   if(p_qstrBool == "true")
   {
      bRet =  true;
   }

   return bRet;
}

void CdmModelElement::XmlExportBase(QDomElement& p_rqdeBase) const
{
   SYNCHRONIZED_READ;
   p_rqdeBase.setAttribute(WMS_ID, QString::number(m_lId));
   p_rqdeBase.setAttribute(WMS_KEYNAME,    m_qstrKeyname);
   p_rqdeBase.setAttribute(WMS_CAPTION,    m_qstrCaption);
   p_rqdeBase.setAttribute(WMS_LASTCHANGE, m_qdtLastChange.toString());
   p_rqdeBase.setAttribute(WMS_DELETED,    ChangeBoolToString(m_bDeleted));
   p_rqdeBase.setAttribute(WMS_MODIFIED,   ChangeBoolToString(m_bModified));
   p_rqdeBase.setAttribute(WMS_NEW,        ChangeBoolToString(m_bNew));
   p_rqdeBase.setAttribute(WMS_VALID,      ChangeBoolToString(m_bValid));
   p_rqdeBase.setAttribute(WMS_CREATORID,    QString::number(m_lCreatorId));
   p_rqdeBase.setAttribute(WMS_MODIFIERID,   QString::number(m_lModifierId));
   p_rqdeBase.setAttribute(WMS_SCHEME,       QString::number(m_lSchemeId));
   p_rqdeBase.setAttribute(WMS_URI,       GetUriInternal());
}

void CdmModelElement::XmlImportBase(  QDomElement& p_rqDomElement )
{
    SYNCHRONIZED_WRITE;
   m_lId           = p_rqDomElement.attribute(WMS_ID, "-1").toInt();
   m_qstrKeyname   = p_rqDomElement.attribute(WMS_KEYNAME, "");
   m_qstrCaption   = p_rqDomElement.attribute(WMS_CAPTION, "");
   m_qdtLastChange = QDateTime::fromString(p_rqDomElement.attribute(WMS_LASTCHANGE, ""));
   m_bDeleted      = ChangeStringToBool(p_rqDomElement.attribute(WMS_DELETED, ""));
   m_bModified     = ChangeStringToBool(p_rqDomElement.attribute(WMS_MODIFIED, ""));
   m_bNew          = ChangeStringToBool(p_rqDomElement.attribute(WMS_NEW, ""));
   m_bValid        = ChangeStringToBool(p_rqDomElement.attribute(WMS_VALID, ""));
   m_lCreatorId    = p_rqDomElement.attribute(WMS_CREATORID, "-1").toInt();
   m_lModifierId   = p_rqDomElement.attribute(WMS_MODIFIERID, "-1").toInt();
   m_lSchemeId   = p_rqDomElement.attribute(WMS_SCHEME, "").toInt();

   m_bModified = true;
}

QString CdmModelElement::GetInfo() const
{
    SYNCHRONIZED_READ;
   QString qstrRet;

   qstrRet = "Base Informations:\n";
   qstrRet += "ID:           " + QString::number(GetId()) + "\n";
   qstrRet += "Uri:          " + GetUriInternal() + "\n";
   qstrRet += "Keyname:      " + m_qstrKeyname + "\n";
   qstrRet += "Caption:      " + m_qstrCaption + "\n";
   qstrRet += "Scheme:       " + QString::number(GetSchemeId()) + "\n";
   qstrRet += "CreatorId:    " + QString::number(m_lCreatorId) + "\n";
   qstrRet += "Last Changed: " + m_qdtLastChange.toString() + "\n";
   qstrRet += "Valid:        ";

   if (m_bValid.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }

   qstrRet += "New:          ";

   if (m_bNew.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }


   qstrRet += "Modified:     ";

   if (m_bModified.load())
   {
      qstrRet += "Yes\n";
   }
   else
   {
      qstrRet += "No\n";
   }
   
   return qstrRet;
}

QVariant CdmModelElement::GetVariant() const
{
   SYNCHRONIZED_READ;
   QVariantMap qmVariant;

   qmVariant.insert(WMS_ID, m_lId.load());
   qmVariant.insert(WMS_KEYNAME, m_qstrKeyname);
   qmVariant.insert(WMS_DATABASEID, GetSchemeId());
   qmVariant.insert(WMS_CAPTION, m_qstrCaption);
   qmVariant.insert(WMS_URI, GetUriInternal());
   return qmVariant;
}

QString CdmModelElement::GetDisplayTypeAsString(EdmStringDisplayType p_eType)
{
   QString qstrRet;

   switch (p_eType)
   {
      case edmStringDisplayTypeFormatted:   
         qstrRet = tr("Formatiert");
         break;
      case edmStringDisplayTypeUnFormatted:   
         qstrRet = tr("Unformatiert");
         break;
      case edmStringDisplayTypeDirectory:
         qstrRet = tr("Verzeichnis");
         break;
      case edmStringDisplayTypeFile:
         qstrRet = tr("Datei");
         break;
      case edmStringDisplayTypeEncrypted:
         qstrRet = QStringLiteral("Verschlüsselt");
         break;
      case edmStringDisplayTypeLink:
         qstrRet = tr("Link");
         break;
      case edmStringDisplayTypeJson:   
         qstrRet = tr("Json");
         break;
      case edmStringDisplayTypeXml:   
         qstrRet = tr("XML");
         break;
   }

   return qstrRet;
}

QString CdmModelElement::GetUriType() const
{
    QString qstrType;

    if (IsClass())
    {
       qstrType = WMS_URI_CLASS;
    }
    else if (IsObject())
    {
       qstrType = WMS_URI_OBJECT;
    }
    else if (IsContainer())
    {
       qstrType = WMS_URI_CONTAINER;
    }
    else if (IsValue())
    {
       qstrType = WMS_URI_VALUE;
    }
    else if (IsMember())
    {
       qstrType = WMS_URI_MEMBER;
    }
	else if (IsPackage())
	{
		qstrType = WMS_URI_PACKAGE;
	}
    else
    {
       qstrType = WMS_URI_UNKNOWN;
    }

    return qstrType;
}

QString CdmModelElement::GetUri() const
{
   QString qstrType = GetUriType();
   return CreateUri(qstrType, GetKeyname());
}

QString CdmModelElement::GetUriInternal() const
{
    QString qstrType = GetUriType();
    return CreateUriPath(qstrType, GetKeyname(), "", "");
}

QString CdmModelElement::GenerateKeyname() const
{
    SYNCHRONIZED_READ;
    return  m_qstrKeyname + QUuid::createUuid().toString()
            .remove("-")
            .remove("{")
            .remove("}");
}

bool CdmModelElement::CheckKeyname(QString p_qstrKeyname)
{
    bool bSuccess = false;
    QRegExp regex("[A-Za-z][A-Za-z0-9_]*");
    bSuccess = regex.exactMatch(p_qstrKeyname);

    if (!bSuccess)
    {
        WARNING("Keyname check failed. Keyname:  \"" + p_qstrKeyname +"\"");
    }

    return bSuccess;
}

bool CdmModelElement::IsModelElement() const
{
   return true;
}

bool CdmModelElement::HasUserDeleteAccess()
{
    bool bRet = false;

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    CumUser *pCurrentUser = const_cast<CumUser*>(pManager->GetUser());

    if(CHKPTR(pCurrentUser))
    {
        if(pCurrentUser->IsAdministrator())
        {
            bRet = true;
        }
    }

    return bRet;
}
