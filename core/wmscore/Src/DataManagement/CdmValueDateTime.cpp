// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueDateTime.h"


CdmValueDateTime::CdmValueDateTime( qint64 p_lDatabaseId,
                         qint64 p_lId,
                          QString p_qstrKeyname,
                          CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueDateTime, p_pCdmObject)
{
   m_qdtValue = QDateTime::currentDateTime();
}

CdmValueDateTime::CdmValueDateTime(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qdtValue = p_rqvHash[WMS_VALUE].toDateTime();
}

void CdmValueDateTime::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qdtValue = p_rqvHash[WMS_VALUE].toDateTime();
}

CdmValueDateTime::~CdmValueDateTime(  )
{
   // Nothing to do
}

void CdmValueDateTime::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qdtValue);
      ValueChanged();
   }
}

void CdmValueDateTime::SetValue(  double p_dValue )
{
   m_qdtValue = ChangeDoubleToDateTime(p_dValue);
}

void CdmValueDateTime::SetValue(const QDateTime& p_rqdtDateTime)
{
   if(m_qdtValue != p_rqdtDateTime)
   {
      m_qdtValue = p_rqdtDateTime;
      ValueChanged();
   }
}

void CdmValueDateTime::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    p_qstrValue = p_qstrValue.simplified();
    QDateTime qDateTime = QDateTime::fromString(p_qstrValue, "yyyy-MM-dd hh:mm:ss");
    if (qDateTime.isValid())
    {
		SetValue(qDateTime);
    }
}

QDateTime CdmValueDateTime::GetValue() const
{
   QString qstr = m_qdtValue.toString();
   return m_qdtValue;
}

void CdmValueDateTime::GetValue(double& p_dDateTime) const
{
   p_dDateTime = ChangeDateTimeToDouble(m_qdtValue);
}

QString CdmValueDateTime::GetDisplayString() const
{
   QString qstrRet;

   if (m_qdtValue.isValid() && m_qdtValue.date() < QDate(5000,12,31))
   {
      qstrRet = m_qdtValue.toString(Qt::SystemLocaleShortDate);
   }
   else
   {
      qstrRet = "-";
   }

   return qstrRet;
}

QVariant CdmValueDateTime::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert("Value", m_qdtValue);
   return qmVariant;
}

void CdmValueDateTime::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toDateTime());
}

QString CdmValueDateTime::GetValueAsString() const
{
   return m_qdtValue.toString(Qt::ISODate);
}

QVariant CdmValueDateTime::GetValueVariant() const
{
   return QVariant(m_qdtValue);
}

void CdmValueDateTime::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toDateTime());
}

void CdmValueDateTime::Restore(QString p_qstrValue)
{
    QLocale loc;
    QDateTime qdDate = QDateTime::fromString(p_qstrValue, Qt::ISODate);

    if (qdDate.isValid())
    {
        SetValue(qdDate);
    }
    else
    {
        ERR("Could not convert value string to datetime. Value String: " + p_qstrValue);
    }
}
