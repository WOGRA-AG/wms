#ifndef WMS_NO_LDAP
#ifndef CwmsLdapUtilities_H
#define CwmsLdapUtilities_H

#include "basetools.h"

#include "CumUserManager.h"
#include "CumUser.h"

#include <QList>
#include <QPair>
#include <QString>

class BASETOOLS_API CwmsLdapUtilities
{

public:
      CwmsLdapUtilities();
      static void IsUserInUserGroupOrAdminGroup(QList<QString> &listQ, QList<QPair<QString,QString> >& listA, QString AdminGruppenName, QString BenutzerGruppenName,bool& adminflag, bool& userflag);
      static bool updateUserData(CumUserManager* p_pUserManager,
                                 CumUser* p_pUser,
                                 QList<QString> &listQ,
                                 QList<QPair<QString,QString> >& listA,
                                 bool adminflag);
      static bool createUserData(CumUserManager* p_pUserManager, QList<QString> &listQ, QList<QPair<QString,QString> >& listA, QString user, QString appName, bool adminflag);
private:
      static CumUserManager * GetUserManager(QString appName, QString user);
      QString prepareEmailForInsert(QString email);
      QString setRandomPassword();
};

#endif // WMS_NO_LDAP
#endif // CwmsLdapUtilities_H
