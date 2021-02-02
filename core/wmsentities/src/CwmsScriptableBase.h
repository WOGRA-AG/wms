#ifndef CWMSSCRIPTABLEBASE_H
#define CWMSSCRIPTABLEBASE_H

#include <QObject>
#include <QScriptable>

class CsaFactory;

class CwmsScriptableBase : public QObject, protected QScriptable
{
    Q_OBJECT

public:
    CwmsScriptableBase();
    virtual ~CwmsScriptableBase();
public slots:
    void addObjectForGarbageCollection(QObject *p_pObject);
protected:
    CsaFactory* getFactory();
};

#endif // CWMSSCRIPTABLEBASE_H
