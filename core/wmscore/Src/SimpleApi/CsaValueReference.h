#ifndef CSAVALUEREFERENCE_H
#define CSAVALUEREFERENCE_H

#include "CsaLocatedElement.h"

class CdmValue;

class CsaValueReference : public CsaLocatedElement
{
    Q_OBJECT
private:
    CdmValue* m_rpValue;
public:
    CsaValueReference(CdmValue* p_pRef);
    virtual ~CsaValueReference();

    CdmValue *getInternals();
public slots:
    QVariant get();
    void set(QObject* p_pObject);
    QVariant getValueReference(); // deprecated
    void setValueReference(QObject *p_pObject);// deprecated
    virtual bool isReference();

    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();


};

#endif // CSAVALUEREFERENCE_H
