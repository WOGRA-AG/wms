#ifndef ISAOBJECT_H
#define ISAOBJECT_H

//Qt includes
#include <QVariant>
#include <QObject>
#include <QScriptValue>
#include <QJSValue>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QString>

class CsaValue;

class IsaObject
{
public slots:
    virtual QObject *findValue(QString p_qstrKeyname) = 0;
    virtual QObject* getClass() = 0;
    virtual QVariant getValuePrimitive(QString p_qstrKeyname) = 0;
    virtual QObject* getValueReference(QString p_qstrKeyname) = 0;
    virtual QObject *getValueUser(QString p_qstrKeyname) = 0;
    virtual double getValueDouble(QString p_qstrKeyname) const = 0;
    virtual long getValueLong(QString p_qstrKeyname) const = 0;
    virtual int getValueInt(QString p_qstrKeyname) const = 0;
    virtual bool getValueBool(QString p_qstrKeyname) const = 0;
    virtual float getValueFloat(QString p_qstrKeyname) const = 0;
    virtual QDateTime getValueDateTime(QString p_qstrKeyname) const = 0;
    virtual QDate getValueDate(QString p_qstrKeyname) const = 0;
    virtual QTime getValueTime(QString p_qstrKeyname) const = 0;
    virtual QString getValueString(QString p_qstrKeyname) const = 0;
    virtual QString getJson() = 0;
    virtual QVariant execute(QString p_qstrMethod, QScriptValue p_qArg1 = QScriptValue(), QScriptValue p_qArg2 = QScriptValue(), QScriptValue p_qArg3 = QScriptValue(), QScriptValue p_qArg4 = QScriptValue(), QScriptValue p_qArg5 = QScriptValue(), QScriptValue p_qArg6 = QScriptValue(), QScriptValue p_qArg7 = QScriptValue(), QScriptValue p_qArg8 = QScriptValue(), QScriptValue p_qArg9 = QScriptValue(), QScriptValue p_qArg10 = QScriptValue(), QScriptValue p_qArg11 = QScriptValue(), QScriptValue p_qArg12 = QScriptValue(), QScriptValue p_qArg13 = QScriptValue(), QScriptValue p_qArg14 = QScriptValue(), QScriptValue p_qArg15 = QScriptValue()) = 0;
    virtual QVariant execute(QString p_qstrFunctionName, QJSValue p_qlArguments) = 0;
    virtual QString getValueDisplayString(QString p_qstrKeyname) = 0;
    virtual QObject *getContainer() = 0;
    virtual bool hasOwner() = 0;
    virtual bool hasOwner(QString qstrObjectKeyname) = 0;
    virtual QObject *getOwner() = 0;
    virtual QObject *getOwner(QString qstrObjectKeyname) = 0;
    virtual bool isImmutable() = 0;
};

#endif // ISAOBJECT_H
