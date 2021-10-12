
// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <qvariant.h>
#include <qdom.h>

// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueBool.h"


CdmValueBool::CdmValueBool( qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject* p_pCdmObject )
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueBool, p_pCdmObject),
  m_bValue(false)
{
   // nothing todo here :-)
}

CdmValueBool::CdmValueBool(QVariantMap& p_qVariant, CdmObject* p_pCdmObject)
: CdmValue(p_qVariant, p_pCdmObject)
{
   m_bValue = p_qVariant[WMS_VALUE].toBool();
}

CdmValueBool::~CdmValueBool(  )
{
   // nothing to do here :-)
}

void CdmValueBool::SetVariant(QVariantMap& p_rqvHash)
{
   QVariant qValue = p_rqvHash["Value"];
   SetValue(qValue.toBool());
}

void CdmValueBool::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_bValue = p_rqvHash["Value"].toBool();
}

void CdmValueBool::SetValue(bool p_bValue)
{
   if (p_bValue != m_bValue)
   {
      m_bValue = p_bValue;
      ValueChanged();
   }
}

void CdmValueBool::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    p_qstrValue = p_qstrValue.simplified();
   if (p_qstrValue == "true" || 
       p_qstrValue == "1" || 
       p_qstrValue == tr("Ja"))
   {
      SetValue(true);
   }
   else
   {
      SetValue(false);
   }
}

bool CdmValueBool::GetValue() const
{
   return m_bValue;
}

void CdmValueBool::SetDefaultValue(const CdmMember* p_pCdmMember)
{
   QVariant qvVariant = p_pCdmMember->GetDefaultValue();
   m_bValue = qvVariant.toBool();
   ValueChanged();
}

QString CdmValueBool::GetDisplayString() const
{
   QString qstrRet = tr("Nein");

   if (m_bValue)
   {
      qstrRet = tr("Ja");
   }
   
   return qstrRet;
}

void CdmValueBool::FromStringToValue(QString p_qstrValue)
{
   SetValue(ChangeStringToBool(p_qstrValue));
}

QVariant CdmValueBool::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, m_bValue);
   return qmVariant;
}

QVariant CdmValueBool::GetValueVariant() const
{
   return QVariant(m_bValue);
}

void CdmValueBool::SetValueVariant(QVariant& p_rqVariant)
{
    if (p_rqVariant.canConvert<bool>())
    {
        SetValue(p_rqVariant.toBool());
    }
    else
    {
        FromStringToValue(p_rqVariant.toString());
    }
}

QString CdmValueBool::GetValueAsString() const
{
   QString qstrRet = "true";
   
   if (!m_bValue)
   {
      qstrRet = "false";
   }

   return qstrRet;
}

void CdmValueBool::Restore(QString p_qstrValue)
{
    if (p_qstrValue == "true")
    {
        SetValue(true);
    }
    else if (p_qstrValue == "false")
    {
        SetValue(false);
    }
    else
    {
        ERR("The value is in this state not restoreable state: " + p_qstrValue);
    }
}
