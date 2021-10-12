// System and QT Includes
#include <QString>
#include <QDateTime>
#include <QScriptEngine>

// Own Includes
#include "wmsdefines.h"
#include "CdmExecutor.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmValueFormula.h"
#include "CdmValueContainerRef.h"

CdmValueFormula::CdmValueFormula(qint64 p_lDatabaseId,
                                qint64 p_lId,
                                 QString p_qstrKeyname,
                                 CdmObject* p_pCdmObject)
: CdmValue(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueFormula, p_pCdmObject)
{
}


CdmValueFormula::~CdmValueFormula()
{
   // nothing to do
}

void CdmValueFormula::SetDefaultValue(const CdmMember*)
{
   // does nothing
}

QString CdmValueFormula::GetValueAsString() const
{
   QString qstrResult;
   QVariant qScriptValue = Evaluate();

   if (qScriptValue.canConvert(QMetaType::Double))
   {
      QLocale qLocale;
      bool bOk = false;
      qstrResult = qLocale.toString(qScriptValue.toDouble(&bOk));

      if (!bOk)
      {
        qstrResult = qScriptValue.toString();
      }
   }
   else
   {
      qstrResult = qScriptValue.toString();         
   }
   
   return qstrResult;
}

int CdmValueFormula::GetValueAsInt()
{
   int iValue = 0;
   QVariant qScriptValue = Evaluate();
   iValue = qScriptValue.toInt();
   return iValue;
}

double CdmValueFormula::GetValueAsDouble()
{
   double dValue = 0.0;
   QVariant qScriptValue = Evaluate();
   dValue = qScriptValue.toDouble();
   return dValue;
}

QDateTime CdmValueFormula::GetValueAsTimestamp()
{
   QDateTime qdtDateTime;
   QVariant qScriptValue = Evaluate();
   qdtDateTime = qScriptValue.toDateTime();
   return qdtDateTime;
}

QDate CdmValueFormula::GetValueAsDate()
{
   QDate qdDate;
   QVariant qScriptValue = Evaluate();
   qdDate = qScriptValue.toDateTime().date();
   return qdDate;
}

QTime CdmValueFormula::GetValueAsTime()
{
   QTime qtTime;
   QVariant qScriptValue = Evaluate();
   qtTime = qScriptValue.toDateTime().time();
   return qtTime;
}

QVariant CdmValueFormula::Evaluate() const
{
   QVariant qResult;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      QString qstrFormula = pCdmMember->GetValidationCode();
      qResult = CdmExecutor::GetExecutor()->EvaluateFormula(GetObject(), qstrFormula);
   }

   return qResult;
}

QString CdmValueFormula::GetDisplayString() const
{
   return GetValueAsString();
}

int CdmValueFormula::FromStringToValue(QString)
{
   // DOES NOTHING Keeping baseclass work
   int iRet = EC(eDmOk);
   return iRet;
}

void CdmValueFormula::SetValue(QString , QString )
{
   // Does nothing
}

QVariant CdmValueFormula::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValueAsString());
   return qmVariant;
}

void CdmValueFormula::SetVariant(QVariantMap& p_rqvHash)
{
   Q_UNUSED(p_rqvHash);
   // Does nothing
}

QVariant CdmValueFormula::GetValueVariant() const
{
   return QVariant(GetValueAsString());
}

void CdmValueFormula::SetValueVariant(QVariant&)
{
    // Does nothing
}
