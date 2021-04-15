// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qlocale.h>
#include <qdom.h>


// own Includes
#include "CwmsUtilities.h"
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueDouble.h"

CdmValueDouble::CdmValueDouble(  long p_lDatabaseId,
                      long p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject )
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueDouble, p_pCdmObject),
  m_dValue(0.0)
{
   // nothing to do
}

CdmValueDouble::CdmValueDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_dValue = p_rqvHash[WMS_VALUE].toDouble();
}

CdmValueDouble::~CdmValueDouble()
{
   // nothing to do
}

void CdmValueDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_dValue = p_rqvHash[WMS_VALUE].toDouble();
}

void CdmValueDouble::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_dValue);
      ValueChanged();
   }
}

void CdmValueDouble::SetValue(double p_dValue)
{
   if(m_dValue != p_dValue)
   {
      m_dValue = p_dValue;
      ValueChanged();
   }
}

void CdmValueDouble::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue.toDouble());
}

double CdmValueDouble::GetValue() const
{
   return m_dValue;
}

int CdmValueDouble::IsEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() == m_dValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmValueDouble::IsSmaller(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() > m_dValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmValueDouble::IsSmallerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() >= m_dValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmValueDouble::IsLarger(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() < m_dValue )
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmValueDouble::IsLargerEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() <= m_dValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

int CdmValueDouble::IsNotEqual(  QVariant* p_pqVariant ) const
{
   int iRet = CdmLogging::eDmUnknownCompareError;

   if(CHKPTR(p_pqVariant))
   {
      if(p_pqVariant->toDouble() != m_dValue)
      {
         iRet = EC(eDmTrue);
      }
      else
      {
         iRet = EC(eDmFalse);
      }
   }
   else
   {
      iRet = EC(eDmInvalidPtr);
   }

   return iRet;
}

QString CdmValueDouble::GetDisplayString() const
{
   QString qstrRet;
   QLocale qlDefault;

   const CdmMember* pMember = GetMember();

   qstrRet = pMember->GetPrefix();

   if (pMember->GetDecimalCountOutput() > 0)
   {
       qstrRet += qlDefault.toString(m_dValue, 'f', pMember->GetDecimalCountOutput());
   }
   else
   {
       qstrRet += qlDefault.toString(m_dValue, 'f', 2);
   }

   qstrRet += pMember->GetSuffix();

   return qstrRet;
}

int CdmValueDouble::FromStringToValue(  QString p_qstrValue )
{
   int iRet = CdmLogging::eDmUnknownValueError;

   QLocale qlDefault;
   bool bSuccess = false;
   m_dValue = qlDefault.toDouble(p_qstrValue, &bSuccess);

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

QVariant CdmValueDouble::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert("Value", m_dValue);
   return qmVariant;
}

void CdmValueDouble::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash["Value"].toDouble());
}

QVariant CdmValueDouble::GetValueVariant() const
{
   return QVariant(m_dValue);
}

QString CdmValueDouble::GetValueAsString() const
{
    QLocale loc;
   return loc.toString(m_dValue);
}

void CdmValueDouble::SetValueVariant(QVariant& p_rqVariant)
{
    if (CwmsUtilities::isNumberValid(p_rqVariant.toDouble()))
    {
        SetValue(p_rqVariant.toDouble());
    }
}

void CdmValueDouble::Restore(QString p_qstrValue)
{
    double dValue = p_qstrValue.toDouble();
    SetValue(dValue);
}
