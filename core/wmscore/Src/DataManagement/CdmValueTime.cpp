// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueTime.h"


CdmValueTime::CdmValueTime(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueTime, p_pCdmObject)
{
    m_qtValue = QTime::currentTime();
}

CdmValueTime::CdmValueTime(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qtValue = p_rqvHash[WMS_VALUE].toTime();
}

CdmValueTime::~CdmValueTime(  )
{
}

void CdmValueTime::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qtValue = p_rqvHash[WMS_VALUE].toTime();
}

void CdmValueTime::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qtValue);
      ValueChanged();
   }
}

void CdmValueTime::SetValue(const QTime& p_rqtTime)
{
   if(p_rqtTime != m_qtValue)
   {
      m_qtValue = p_rqtTime;
      ValueChanged();
   }
   else
   {
      INFO("Old and New Value are equal no changes will be done.");
   }
}

void CdmValueTime::SetValue(double p_dTime)
{
   m_qtValue = ChangeDoubleToTime(p_dTime);
}

void CdmValueTime::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(QTime::fromString(p_qstrValue));
}

QTime CdmValueTime::GetValue() const
{
   return m_qtValue;
}

void CdmValueTime::GetValue(double& p_dTime) const
{
   p_dTime = ChangeTimeToDouble(m_qtValue);
}

QString CdmValueTime::GetValueAsString() const
{

   return m_qtValue.toString(Qt::ISODate);
}

QString CdmValueTime::GetDisplayString() const
{
   QString qstrRet;

   if (m_qtValue.isValid())
   {
      qstrRet = m_qtValue.toString(Qt::SystemLocaleShortDate);
   }
   else
   {
      qstrRet = "-";
   }

   return qstrRet;
}

QVariant CdmValueTime::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_qtValue);
   return qmVariant;
}

void CdmValueTime::SetVariant(QVariantMap& p_rqvHash)
{
   QString qstrTime = p_rqvHash[WMS_VALUE].toString();
   QTime qtTime = p_rqvHash[WMS_VALUE].toTime();

   if (!qtTime.isValid())
   {
      QDateTime qdtDateTime = p_rqvHash[WMS_VALUE].toDateTime();

      if (qdtDateTime.isValid())
      {
         qtTime = qdtDateTime.time();
      }
      else
      {
         qtTime = QTime(0,0,0,0);
      }
      
   }

   SetValue(qtTime);
}

QVariant CdmValueTime::GetValueVariant() const
{
   return QVariant(m_qtValue);
}

void CdmValueTime::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toTime());
}

void CdmValueTime::Restore(QString p_qstrValue)
{
    QLocale loc;
    QTime qTime = loc.toTime(p_qstrValue, QLocale::ShortFormat);

    if (qTime.isValid())
    {
        SetValue(qTime);
    }
    else
    {
        ERR("Convert value string to time failed. ValueString: " + p_qstrValue);
    }
}
