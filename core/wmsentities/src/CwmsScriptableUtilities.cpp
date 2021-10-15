#include <QByteArray>

#include "CwmsScriptableModel.h"
#include "CwmsScriptableUtilities.h"


CwmsScriptableUtilities::CwmsScriptableUtilities()
{
}


QString CwmsScriptableUtilities::convertFromByteArrayToBase64(QByteArray p_qArray)
{
  return p_qArray.toBase64();
}


QByteArray CwmsScriptableUtilities::convertFromBase64ToByteArray(QString p_qstrBase64)
{
    return QByteArray::fromBase64(p_qstrBase64.toUtf8());
}

QObject* CwmsScriptableUtilities::createEmptyModel()
{
    return new CwmsScriptableModel();
}

void CwmsScriptableUtilities::deleteModel(QObject* p_pModel)
{
    if (p_pModel->objectName() == "Model")
    {
        DELPTR(p_pModel);
    }
    else
    {
        CdmMessageManager::critical("Pointer Löschung nicht erlaubt","In dieser Funktion dürfen nur Models gelöscht werden");
    }
}

QString CwmsScriptableUtilities::formatDoubleValueToLocaleString(double p_dValue, int p_iDecimalPlaces)
{
    QLocale loc;
    return loc.toString(p_dValue, 'f', p_iDecimalPlaces);
}

QString CwmsScriptableUtilities::formatIntValueToLocaleString(int p_iValue)
{
    QLocale loc;
    return loc.toString(p_iValue);
}

QDate CwmsScriptableUtilities::getDateFromIsoString(QString p_qstrIsoDate)
{
    return QDate::fromString(p_qstrIsoDate, Qt::ISODate);
}

QString CwmsScriptableUtilities::formatIsoDateToLocaleDate(QString p_qstrIsoDate)
{
    QDate qdDate = getDateFromIsoString(p_qstrIsoDate);
    QLocale loc;
    return qdDate.toString("dd.MM.yyyy");
}

QString CwmsScriptableUtilities::fromDateToIsoString(QDate p_qdDate)
{
    return p_qdDate.toString(Qt::ISODate);
}
