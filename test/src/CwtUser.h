
#ifndef CWTUSER_H
#define CWTUSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QtTest>
#include <QObject>
#include <QDateTime>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Own Includes
#include "CwtTestBase.h"

// Forwards
class CdmScheme;
class CdmManager;
class CdmClassManager;
class CdmContainerManager;
class CumUserManager;

// TypeDefs



/*
 * This class implements the main test class which starts all tests
 */
class CwtUser : public CwtTestBase
{
    Q_OBJECT
private:
    QTime m_qTimeStartSingleTest;
    QTime m_qTimeStartAllTests;

    CumUser *CreateUser(QString p_qstrIdentitfier, CumUserManager *pUserManager);
public:
    CwtUser();
    virtual ~CwtUser();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void FindAdminUserSlot();
    void CreateFindDeleteUser();
    void CreateFindDeleteUserGroup();

    void init();
    void cleanup();
    void FindUserByLogin();
    void FindUserById();
    void FindUnknownUserByLogin();
    void FindUnknownUserById();
    void FindUnknownUserByEmail();
    void FindUserByEmail();
    void FindUserByIdentityKey();
    void FindUnknownUserByIdentityKey();
    void AddAndRemoveUserToUsergroupByIds();
    void AddAndRemoveUserToUsergroupByNames();
    void LoginInactivatedUser();
    void CreateUserWithoutLogin();
    void CreateUserWithoutEmail();
    void FindUsersUnmanaged();
    void RegisterUser();
    void CreateAndFindUserGroupUnmanaged();
};

#endif // CWTTEST_H
