#ifndef ISALOCATEDELEMENT_H
#define ISALOCATEDELEMENT_H

//QT includes
#include <QObject>

// own Includes

// Forwards
class CsaFactory;

class IsaLocatedElement
{
public slots:
    virtual QObject* getFactory() = 0;
    virtual QObject* getManager() = 0;
    virtual QObject* getContainerManager() = 0;
    virtual QObject* getClassManager() = 0;
    virtual QObject* getScheme() = 0;
    virtual bool isValue() = 0;
    virtual bool isMember() = 0;
    virtual bool isClass() = 0;
    virtual bool isContainer() = 0;
    virtual bool isObject() = 0;
    virtual bool isModelElement() = 0;
    virtual bool isReference() = 0;
    virtual QString getUri() const = 0;
};

#endif // ISALOCATEDELEMENT_H
