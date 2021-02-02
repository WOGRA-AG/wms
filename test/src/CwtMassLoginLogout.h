#ifndef CWTLOGINLOGOUTTEST_H
#define CWTLOGINLOGOUTTEST_H

#include <QtTest>
#include <QObject>

#include "CwtTestBase.h"

class CdmClass;
class CdmObjectContainer;

class CwtLoginLogout: public CwtTestBase
{
   Q_OBJECT
public:
    CwtLoginLogout();
    virtual ~CwtLoginLogout(){}

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void LoginAdmin();
    void Logout();

    void LoginUnknowUser();
    void LoginWrongPassword();
    void MassLoginLogout();
};

#endif // CWTLOGINLOGOUTTEST_H
