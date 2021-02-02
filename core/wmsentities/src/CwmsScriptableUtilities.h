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
};

#endif // CWMSSCRIPTABLEUTILITIES_H
