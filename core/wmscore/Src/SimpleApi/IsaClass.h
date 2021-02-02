#ifndef ISACLASS_H
#define ISACLASS_H

//Qt includes
#include <QObject>
#include <QVariant>
#include <QString>

//forwards
class CsaClass;

class IsaClass
{
public slots:
        virtual QObject *findMember(QString p_qstrKeyname) = 0;
        virtual QVariantList getMembers() = 0;
        virtual QVariantList getBaseClasses() = 0;
        virtual bool isTypeOf(QObject* p_pClass) = 0;
        virtual bool isImmutable() = 0;
        virtual QObject *getSingletonObject() = 0;
};

#endif // ISACLASS_H
