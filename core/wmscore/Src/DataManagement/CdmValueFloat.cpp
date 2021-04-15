// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qlocale.h>
#include <qdom.h>


// own Includes
#include "CwmsUtilities.h"
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueFloat.h"

CdmValueFloat::CdmValueFloat(  long p_lDatabaseId,
                    long p_lId,
                    QString p_qstrKeyname,
                    CdmObject* p_pCdmObject )
   : CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueFloat, p_pCdmObject),
  m_fValue(0.0f)
{
   // nothing to do
}

CdmValueFloat::CdmValueFloat(QVariantMap& p_rqHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqHash, p_pCdmObject)
{
   m_fValue = p_rqHash[WMS_VALUE].toFloat();
}

CdmValueFloat::~CdmValueFloat(  )
{
   // nothing to do
}

void CdmValueFloat::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_fValue = p_rqvHash[WMS_VALUE].toFloat();
}

void CdmValueFloat::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if ( CHKPTR( p_pCdmMember ) )
   {
      p_pCdmMember->GetDefaultValue(m_fValue);
      ValueChanged();
   }
}

void CdmValueFloat::SetValue(float p_fValue)
{
   if (m_fValue != p_fValue)
   {
      m_fValue = p_fValue;
      ValueChanged();
   }
}

void CdmValueFloat::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toDouble());
}

float CdmValueFloat::GetValue() const
{
   return m_fValue;
}

QString CdmValueFloat::GetDisplayString() const
{
   QLocale qlDefault;
   return qlDefault.toString(m_fValue, 'f', 2);
}

int CdmValueFloat::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   float fValue = qlDefault.toFloat(p_qstrValue, &bSuccess);

   // this is allways successfull
   if(bSuccess)
   {
       SetValue(fValue);
      iRet = EC(eDmOk);
   }
   else
   {
      iRet = EC(eDmValueConversionError);
   }

   return iRet;
}

QVariant CdmValueFloat::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   double dValue = m_fValue;
   qmVariant.insert(WMS_VALUE, dValue);
   return qmVariant;
}

void CdmValueFloat::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toFloat());
}

QString CdmValueFloat::GetValueAsString() const
{
   QLocale loc;
   return loc.toString(m_fValue);
}


QVariant CdmValueFloat::GetValueVariant() const
{
   return QVariant(m_fValue);
}

void CdmValueFloat::SetValueVariant(QVariant& p_rqVariant)
{
    bool bSuccess = false;
    float fValue = p_rqVariant.toFloat(&bSuccess);

    if (bSuccess && CwmsUtilities::isNumberValid(fValue))
    {
        SetValue(fValue);
    }
    else if (CwmsUtilities::isNumberValid(fValue))
    {
        FromStringToValue(p_rqVariant.toString());
    }
}


void CdmValueFloat::Restore(QString p_qstrValue)
{
    double dValue = p_qstrValue.toDouble();
    SetValue(dValue);
}
