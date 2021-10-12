#ifndef CWMSQMLAPPLICATIONMODULE_H
#define CWMSQMLAPPLICATIONMODULE_H

// System and Qt Includes


// Basetools Incldues
#include "CwmsApplicationModule.h"

// own Includes
#include "wmsqml_global.h"

// forwards

class CsaObject;
class CsaObjectContainer;

class WMSQML_EXPORT CwmsQmlApplicationModule : public QObject
{
    Q_OBJECT

private:
   CwmsApplicationModule m_Module;

public:
    CwmsQmlApplicationModule();
    virtual ~CwmsQmlApplicationModule();
    static void registerToQml();

public slots:
    void setObject(CsaObject* p_pObject);
    CsaObject* getUserInterface();
    CsaObject* getObjectModule();
    CsaObjectContainer* getContainerModule();
    QString getName();
   qint64 getId();
};

#endif // CWMSQMLAPPLICATIONMODULE_H
