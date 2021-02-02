#ifndef CwmsLDAPFASSADE_H
#define CwmsLDAPFASSADE_H
#ifndef WMS_NO_LDAP
#include <QString>
#include <QMap>
#include <QtPlugin>

#include "basetools.h"

class BASETOOLS_API CwmsLdapFassade
{
public:
    virtual ~CwmsLdapFassade() {}
    virtual QString checkPasswordwLdap(QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, int perma) = 0;
    virtual QString ldap_lookup_with_filter(QList<QString>& listQ, QList<QPair<QString,QString> >& listA, QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, QString filter) = 0;

};

#define CwmsLdapFassade_iid "com.wogra.CwmsLdapFassade"
Q_DECLARE_INTERFACE(CwmsLdapFassade, CwmsLdapFassade_iid)

#endif // WMS_NO_LDAP
#endif // CwmsLDAPFASSADE_H
