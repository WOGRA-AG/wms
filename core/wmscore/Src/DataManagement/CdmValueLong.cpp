// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>
#include <qlocale.h>


// own Includes
#include "wmsdefines.h"
#include "CdmObject.h"
#include "CdmLogging.h"
#include "CdmValueLong.h"


CdmValueLong::CdmValueLong(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueLong, p_pCdmObject),
  m_lValue(0)
{
   // nothing to do
}

CdmValueLong::CdmValueLong(  long p_lDatabaseId,
                  long p_lId,
                  QString p_qstrKeyname,
                  EdmValueType p_eDmValue,
                  CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, p_eDmValue, p_pCdmObject),
  m_lValue(0)
{
   // nothing to do
}

CdmValueLong::CdmValueLong(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_lValue = p_rqvHash[WMS_VALUE].toInt();
}

CdmValueLong::~CdmValueLong(  )
{
   // nothing to do
}

void CdmValueLong::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_lValue = p_rqvHash[WMS_VALUE].toInt();
}

void CdmValueLong::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_lValue);
      ValueChanged();
   }
}

void CdmValueLong::SetValue(long p_lValue)
{
   if(p_lValue != m_lValue)
   {
      m_lValue = p_lValue;
      ValueChanged();
   }
}

void CdmValueLong::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toInt());
}

long CdmValueLong::GetValue() const
{
   return m_lValue;
}

QString CdmValueLong::GetDisplayString() const
{
    const CdmMember* pMember = GetMember();

    if (CHKPTR(pMember))
    {
        QString qstrDisplayConfig = pMember->GetDisplayConfig();

        if (!qstrDisplayConfig.isEmpty())
        {
            return QString::asprintf(qstrDisplayConfig.toLatin1(), m_lValue);
        }

        return QString::number(m_lValue);
    }

    // should never happen
    return QString::number(m_lValue);
}

int CdmValueLong::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;
   bool bSuccess = false;
   m_lValue = p_qstrValue.toLong();

   // this is allways successfull
   if(bSuccess)
   {
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmValueConversionError);
   }

   return iRet;
}

QVariant CdmValueLong::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, (int)m_lValue);
   return qmVariant;
}

void CdmValueLong::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toInt());
}

QString CdmValueLong::GetValueAsString() const
{
   return QString::number(m_lValue);
}

QVariant CdmValueLong::GetValueVariant() const
{
   return QVariant((int) m_lValue);
}

void CdmValueLong::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrValue = p_rqVariant.toString();
    QLocale qLocale;
    SetValue(qLocale.toInt(qstrValue));
}

void CdmValueLong::Restore(QString p_qstrValue)
{
    QLocale loc;
    int iValue = loc.toInt(p_qstrValue);
    SetValue(iValue);
}
