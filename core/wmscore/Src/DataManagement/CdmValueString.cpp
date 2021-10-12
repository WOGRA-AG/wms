
// System and QT Includes
#include <QTextDocument>
#include <qstring.h>
#include <qdatetime.h>
#include <qdom.h>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueCharacterDocument.h"
#include "CdmMember.h"
#include "CdmValueString.h"


CdmValueString::CdmValueString( qint64 p_lDatabaseId,
                     qint64 p_lId,
                      QString p_qstrKeyname,
                      CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueString, p_pCdmObject)
{
   // nothing to do
}

CdmValueString::CdmValueString(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValue(p_rqvHash, p_pCdmObject)
{
   m_qstrValue = p_rqvHash[WMS_VALUE].toString();
}

CdmValueString::~CdmValueString(  )
{
   // nothing to do
}

void CdmValueString::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qstrValue = p_rqvHash[WMS_VALUE].toString();
}

void CdmValueString::SetDefaultValue(  const CdmMember* p_pCdmMember )
{
   if(CHKPTR(p_pCdmMember))
   {
      p_pCdmMember->GetDefaultValue(m_qstrValue);
      ValueChanged();
   }
}

void CdmValueString::SetValue(const QString& p_qstrValue)
{
   if(p_qstrValue != m_qstrValue)
   {
      m_qstrValue = p_qstrValue;
      ValueChanged();
   }
   else
   {
      INFO("The new and the old value ar equal, so nothing is to do.");
   }
}

void CdmValueString::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
   SetValue(p_qstrValue);
}

QString CdmValueString::GetValue() const
{
   return m_qstrValue;
}

QString CdmValueString::GetDisplayString() const
{
   QTextDocument qTextDocument;
   qTextDocument.setHtml(m_qstrValue);
   return qTextDocument.toPlainText();
}

QString CdmValueString::GetValueAsString() const
{
   return m_qstrValue;
}

int CdmValueString::FromStringToValue(QString p_qstrValue)
{
   int iRet = CdmLogging::eDmUnknownValueError;
   m_qstrValue = p_qstrValue;
   iRet = EC(eDmOk);
   return iRet;
}

QVariant CdmValueString::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_qstrValue);
   return qmVariant;
}

void CdmValueString::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toString());
}

QVariant CdmValueString::GetValueVariant() const
{
   return QVariant(m_qstrValue);
}

void CdmValueString::SetValueVariant(QVariant& p_rqVariant)
{
   SetValue(p_rqVariant.toString());
}

bool CdmValueString::HasValue() const
{
   return !m_qstrValue.isEmpty();
}

void CdmValueString::Restore(QString p_qstrValue)
{
    SetValue(p_qstrValue);
}
