// System and QT Includes
#include <QVariantMap>

// Own Includes
#include "wmsdefines.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmValueEnum.h"
#include "CdmLogging.h"

CdmValueEnum::CdmValueEnum(qint64 p_lDatabaseId,
                          qint64 p_lId,
                           QString p_qstrKeyname,
                           CdmObject* p_pCdmObject)
   : CdmValueInt(eDmValueEnum, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{

   // nothing to do
}

CdmValueEnum::CdmValueEnum(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqvHash, p_pCdmObject)
{

}

CdmValueEnum::~CdmValueEnum()
{

}

QString CdmValueEnum::GetDisplayString() const
{
   QString qstrRet;
  QStringList qstrlSelection = GetSelectionList();

  int iPos = GetValue();
  if (iPos < qstrlSelection.count() && iPos >= 0)
  {
     qstrRet = qstrlSelection[iPos];
     qstrRet = qstrRet.trimmed();
  }

   return qstrRet;
}

QStringList CdmValueEnum::GetSelectionList() const
{
   QStringList qstrlSelection;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      qstrlSelection = pCdmMember->GetSelectionList();
   }

   return qstrlSelection;
}

QVariant CdmValueEnum::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

QVariant CdmValueEnum::GetValueVariant() const
{
   return QVariant(GetDisplayString());
}

void CdmValueEnum::SetValueVariant(QVariant& p_rqVariant)
{
    QStringList selectionList = GetSelectionList();
    int id = selectionList.indexOf(p_rqVariant.toString());

    if (id >= 0)
    {
        SetValue(id);
    }
    else
    {
        ERR("Invalid enum value " + p_rqVariant.toString());
    }
}


void CdmValueEnum::Restore(QString p_qstrValue)
{
    QStringList qstrlSelection = GetSelectionList();

    if (qstrlSelection.contains(p_qstrValue))
    {
        SetValue(qstrlSelection.indexOf(p_qstrValue));
    }
    else
    {
        // ERR enum value does not exist anymore
        ERR("Enum state not found in definition. Enum State: " + p_qstrValue);
    }
}
