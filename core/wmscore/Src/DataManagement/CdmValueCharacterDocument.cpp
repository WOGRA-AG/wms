// System and QT Includes
#include <QTextDocument>
#include <qstring.h>
#include <qdom.h>
#include <QVariant>

// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueString.h"
#include "CdmMember.h"
#include "CdmValueCharacterDocument.h"


CdmValueCharacterDocument::CdmValueCharacterDocument(  long p_lDatabaseId,
                                            long p_lId,
                                            QString p_qstrKeyname,
                                            CdmObject* p_pCdmObject )
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname,eDmValueCharacterDocument, p_pCdmObject)
{
   // nothing to do
}

CdmValueCharacterDocument::CdmValueCharacterDocument(long p_lDatabaseId,
                                           long p_lId,
                                           QString p_qstrKeyname,
                                           EdmValueType p_edmValue,
                                           CdmObject* p_pCdmObject)
   : CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, p_edmValue, p_pCdmObject)
{
   // nothing to do
}

CdmValueCharacterDocument::CdmValueCharacterDocument(QVariantMap& p_rqHash,
                                                     CdmObject* p_pCdmObject)
   : CdmValue(p_rqHash, p_pCdmObject)
{
   m_qstrDocument = p_rqHash[WMS_VALUE].toString();
}

CdmValueCharacterDocument::~CdmValueCharacterDocument(  )
{
   // nothing to do
}

void CdmValueCharacterDocument::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   m_qstrDocument = p_rqvHash[WMS_VALUE].toString();
}

void CdmValueCharacterDocument::SetValue(QString p_qstrDocument)
{
   if ( m_qstrDocument != p_qstrDocument)
   {
      m_qstrDocument = p_qstrDocument;
      ValueChanged();
   }
}

void CdmValueCharacterDocument::SetValue(QString p_qstrValue, QString p_qstrValue2)
{
    Q_UNUSED(p_qstrValue2);
    SetValue(p_qstrValue);
}


QString CdmValueCharacterDocument::GetValue() const
{
   return m_qstrDocument;
}


void CdmValueCharacterDocument::SetDefaultValue(const CdmMember* )
{
   // there are no default values for this Value it must be ignored
}


QString CdmValueCharacterDocument::GetDisplayString() const
{
   QTextDocument qTextDocument;
   qTextDocument.setHtml(m_qstrDocument);
   return qTextDocument.toPlainText();
}

int CdmValueCharacterDocument::FromStringToValue(  QString p_qstrValue )
{
   int iRet = CdmLogging::eDmUnknownValueError;

   m_qstrDocument = p_qstrValue;

   // this is allways successfull
   iRet = EC(eDmOk);

   return iRet;
}

QVariant CdmValueCharacterDocument::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   return qmVariant;
}

void CdmValueCharacterDocument::SetVariant(QVariantMap& p_rqvHash)
{
   SetValue(p_rqvHash[WMS_VALUE].toString());
}

QString CdmValueCharacterDocument::GetValueAsString() const
{
   return m_qstrDocument;
}

QVariant CdmValueCharacterDocument::GetValueVariant() const
{
   return QVariant(m_qstrDocument);
}

void CdmValueCharacterDocument::SetValueVariant(QVariant& p_rqVariant)
{
  SetValue(p_rqVariant.toString());
}

void CdmValueCharacterDocument::Restore(QString p_qstrValue)
{
    SetValue(p_qstrValue);
}
