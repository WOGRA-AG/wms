#ifndef CSAFUNCTION_H
#define CSAFUNCTION_H

// System and Qt Includes
#include <QJSValue>
#include <QScriptValue>

// Own Includes
#include "CsaFactory.h"
#include "CsaLocatedElement.h"

class CsaClass;
class CsaObject;
class CdmClassMethod;

class WMSMANAGER_API CsaFunction : public CsaLocatedElement
{
    Q_OBJECT

private:
    CsaClass* m_rpClass;
    CsaObject* m_rpObject;
    QString m_qstrFunctionName;
    void setElement(CsaClass *p_pClass, QString p_qstrFunction);
public:
    CsaFunction(CsaClass* p_pClass, QString p_qstrFunction);
    CsaFunction(CsaObject* p_pObject, QString p_qstrFunction);
    CsaFunction(CdmClassMethod *p_pMethod);
    virtual ~CsaFunction();
    virtual QVariant getDetailedVariant();
    QVariant getRoughVariant();
    QVariant execute(QVariantList qvLParams);
    QString getName();
public slots:
    QVariant execute(QScriptValue p_qArg1 = QScriptValue(), QScriptValue p_qArg2 = QScriptValue(), QScriptValue p_qArg3 = QScriptValue(), QScriptValue p_qArg4 = QScriptValue(), QScriptValue p_qArg5 = QScriptValue(), QScriptValue p_qArg6 = QScriptValue(), QScriptValue p_qArg7 = QScriptValue(), QScriptValue p_qArg8 = QScriptValue(), QScriptValue p_qArg9 = QScriptValue(), QScriptValue p_qArg10 = QScriptValue(), QScriptValue p_qArg11 = QScriptValue(), QScriptValue p_qArg12 = QScriptValue(), QScriptValue p_qArg13 = QScriptValue(), QScriptValue p_qArg14 = QScriptValue(), QScriptValue p_qArg15 = QScriptValue());
    virtual QString getUri() const;
    //QVariant execute(QJSValue p_qlArguments);

public:
    void setElement(CdmClassMethod *p_pMethod);
    virtual CdmLocatedElement *getElement();
    static CdmLocatedElement *getElement(QString p_qstrUri);
    static CsaFunction *getFunctionElement(QString p_qstrUri, CsaFactory &p_rFactory);
    CsaObject *getObject();
};

#endif // CSAFUNCTION_H
