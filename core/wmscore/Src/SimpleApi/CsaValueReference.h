#ifndef CSAVALUEREFERENCE_H
#define CSAVALUEREFERENCE_H

#include "CsaLocatedElement.h"

class CdmValue;

class CsaValueReference : public CsaLocatedElement
{
    Q_OBJECT

    friend class CsaObject;

private:
    CdmValue* m_rpValue;

private:
    CsaValueReference(CdmValue* p_pRef);
    virtual ~CsaValueReference();

public:
    CdmValue *getInternals();
    virtual QVariant getDetailedVariant();

public slots:
    QVariant get();
    void set(QObject* p_pObject);
    QVariant getValueReference(); // deprecated
    void setValueReference(QObject *p_pObject);// deprecated
    virtual bool isReference();
};

#endif // CSAVALUEREFERENCE_H
