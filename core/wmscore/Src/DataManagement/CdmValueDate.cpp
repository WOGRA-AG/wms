// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueDate.h"

CdmValueDate::CdmValueDate(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueDate, p_pCdmObject)
{
//   m_qdValue = QDate::currentDate();
}

CdmValueDate::CdmValueDate(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qdValue = p_rqvHash[WMS_VALUE].toDate();
}

CdmValueDate::~CdmValueDate(  )
{
   // nothing todo
}

void CdmValueDate::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qdValue = p_rqvHash[WMS_VALUE].toDate();
}

void CdmValueDate::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qdValue);
      ValueChanged();
   }
}

void CdmValueDate::SetValue(const long p_lDate)
{

   if(m_qdValue != ChangeLongToDate(p_lDate))
   {
      m_qdValue = ChangeLongToDate(p_lDate);
      ValueChanged();
   }
}

void CdmValueDate::SetValue(const QDate& p_rqdDate)
{
   if(m_qdValue != p_rqdDate)
   {
      m_qdValue = p_rqdDate;
      ValueChanged();
   }
}

void CdmValueDate::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
   Q_UNUSED(p_qstrValue2);
   p_qstrValue = p_qstrValue.simplified();
   QDate qDate = QDate::fromString(p_qstrValue, "yyyy-MM-dd");
   if (qDate.isValid())
   {
       SetValue(qDate);
   }
}

QDate CdmValueDate::GetValue() const
{
   return m_qdValue;
}

void CdmValueDate::GetValue(long& p_dValue) const
{
   p_dValue = ChangeDateToLong(m_qdValue);
}

QString CdmValueDate::GetDisplayString() const
{
   QString qstrRet;

   if (m_qdValue.isValid() && m_qdValue < QDate(5000,12,31))
   {
      qstrRet = m_qdValue.toString(Qt::SystemLocaleShortDate);
   }
   else
   {
      qstrRet = "-";
   }

   return qstrRet;
}

QString CdmValueDate::GetValueAsString() const
{
   return m_qdValue.toString(Qt::ISODate);
}

QVariant CdmValueDate::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_qdValue);
   return qmVariant;
}

void CdmValueDate::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toDate());
}

QVariant CdmValueDate::GetValueVariant() const
{

   return QVariant(m_qdValue);
}

void CdmValueDate::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toDate());
}

void CdmValueDate::Restore(QString p_qstrValue)
{
    QLocale loc;
    QDate qdDate = QDate::fromString(p_qstrValue, Qt::ISODate);

    if (qdDate.isValid())
    {
        SetValue(qdDate);
    }
    else
    {
        ERR("Could not convert value string to date. Value String: " + p_qstrValue);
    }
}
