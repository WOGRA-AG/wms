#ifndef CWMSSCRIPTABLESTATIC_H
#define CWMSSCRIPTABLESTATIC_H

// System and Qt includes
#include <QObject>
#include <QScriptable>
#include <QScriptValue>
#include <QJSValue>
#include <QVariant>

// own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

class BASETOOLS_API CwmsScriptableStatic: public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptableStatic();
    virtual ~CwmsScriptableStatic();

public slots:
    QVariant call(QString p_qstrClass, QString p_qstrMethod, QScriptValue p_qArg1 = QScriptValue(), QScriptValue p_qArg2 = QScriptValue(), QScriptValue p_qArg3 = QScriptValue(), QScriptValue p_qArg4 = QScriptValue(), QScriptValue p_qArg5 = QScriptValue(), QScriptValue p_qArg6 = QScriptValue(), QScriptValue p_qArg7 = QScriptValue(), QScriptValue p_qArg8 = QScriptValue(), QScriptValue p_qArg9 = QScriptValue(), QScriptValue p_qArg10 = QScriptValue(), QScriptValue p_qArg11 = QScriptValue(), QScriptValue p_qArg12 = QScriptValue(), QScriptValue p_qArg13 = QScriptValue(), QScriptValue p_qArg14 = QScriptValue(), QScriptValue p_qArg15 = QScriptValue());
    QVariant call(QString p_qstrClass, QString p_qstrFunction, QJSValue p_qlArguments);
    //QVariant call(QString p_qstrClass, QString p_qstrFunction);
};

#endif // CWMSSCRIPTABLESTATIC_H
