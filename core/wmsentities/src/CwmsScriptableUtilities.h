#ifndef CWMSSCRIPTABLEUTILITIES_H
#define CWMSSCRIPTABLEUTILITIES_H

#include <QObject>

#include "CwmsScriptableBase.h"

class CwmsScriptableUtilities: public CwmsScriptableBase
{
    Q_OBJECT
public:
    explicit CwmsScriptableUtilities();

signals:

public slots: 
    QString convertFromByteArrayToBase64(QByteArray p_qArray);
    QByteArray convertFromBase64ToByteArray(QString p_qstrBase64);
    QObject *createEmptyModel();
    void deleteModel(QObject *p_pModel);
    QString formatDoubleValueToLocaleString(double p_dValue, int p_iDecimalPlaces);
    QString formatIntValueToLocaleString(int p_iValue);
    QDate getDateFromIsoString(QString p_qstrIsoDate);
    QString formatIsoDateToLocaleDate(QString p_qstrIsoDate);

};

#endif // CWMSSCRIPTABLEUTILITIES_H



