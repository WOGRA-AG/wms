// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>
#include <qlocale.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueInt.h"

CdmValueInt::CdmValueInt( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueInt, p_pCdmObject),
  m_iValue(0)
{
   // nothing to do
}

CdmValueInt::CdmValueInt(EdmValueType p_eDmValue,
                        qint64 p_lDatabaseId,
                        qint64 p_lId,
                         QString p_qstrKeyname,
                         CdmObject* p_pCdmObject)
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, p_eDmValue, p_pCdmObject),
  m_iValue(0)
{

   // nothing to do
}

CdmValueInt::CdmValueInt(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_iValue = p_rqvHash[WMS_VALUE].toInt();
}

CdmValueInt::~CdmValueInt(  )
{
   // nothing to do
}

void CdmValueInt::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_iValue = p_rqvHash[WMS_VALUE].toInt();
}

void CdmValueInt::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if ( CHKPTR( p_pCdmMember ) )
   {
      p_pCdmMember->GetDefaultValue(m_iValue);
      ValueChanged();
   }
}

void CdmValueInt::SetValue(int p_iValue)
{
   if (m_iValue != p_iValue && !isnan(p_iValue))
   {
      m_iValue = p_iValue;
      ValueChanged();
   }
}

void CdmValueInt::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toInt());
}

int CdmValueInt::GetValue() const
{
   return m_iValue;
}

QString CdmValueInt::GetDisplayString() const
{
    const CdmMember* pMember = GetMember();

    if (CHKPTR(pMember))
    {
        QString qstrDisplayConfig = pMember->GetDisplayConfig();

        if (!qstrDisplayConfig.isEmpty())
        {
            return QString::asprintf(qstrDisplayConfig.toLatin1(), m_iValue);
        }

        return QString::number(m_iValue);
    }

    // should never happen
    return QString::number(m_iValue);
}

int CdmValueInt::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   m_iValue = qlDefault.toInt(p_qstrValue, &bSuccess);

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

QVariant CdmValueInt::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_iValue);
   return qmVariant;
}

void CdmValueInt::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toInt());
}

QVariant CdmValueInt::GetValueVariant() const
{
   return QVariant(m_iValue);
}

QString CdmValueInt::GetValueAsString() const
{
    QLocale loc;
    return loc.toString(m_iValue);
}

void CdmValueInt::SetValueVariant(QVariant& p_rqVariant)
{
    QString qstrValue = p_rqVariant.toString();
    QLocale qLocale;
    SetValue(qLocale.toInt(qstrValue));
}

void CdmValueInt::Restore(QString p_qstrValue)
{
    int iValue = p_qstrValue.toInt();
    SetValue(iValue);
}
