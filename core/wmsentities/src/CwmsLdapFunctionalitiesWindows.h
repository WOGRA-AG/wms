#ifndef CwmsLDAPFUNCTIONALITIESWINDOWS_H
#define CwmsLDAPFUNCTIONALITIESWINDOWS_H
#ifndef WMS_NO_LDAP
#include <QString>
#include "CwmsLdapFassade.h"

#include <windows.h>
#include <winldap.h>
#include <winber.h>
#include <rpc.h>
#include <rpcdce.h>
#include "basetools.h"

class BASETOOLS_API CwmsLdapFunctionalitiesWindows : public QObject,public CwmsLdapFassade
{
    Q_OBJECT
    Q_INTERFACES(CwmsLdapFassade)

public:
    static CwmsLdapFunctionalitiesWindows* instance()
    {
        if (!m_Instance)
        {
            if (!m_Instance)
                m_Instance = new CwmsLdapFunctionalitiesWindows;
        }

        return m_Instance;
    }

    static void drop()
    {
        delete m_Instance;
        m_Instance = 0;
    }

    virtual QString checkPasswordwLdap(QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, int perma);
    virtual QString ldap_lookup_with_filter(QList<QString>& listQ, QList<QPair<QString,QString> >& listA, QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, QString filter);

private:

    CwmsLdapFunctionalitiesWindows() {}
    virtual ~CwmsLdapFunctionalitiesWindows() {}
    CwmsLdapFunctionalitiesWindows(const CwmsLdapFunctionalitiesWindows &); // hide copy constructor
    CwmsLdapFunctionalitiesWindows& operator=(const CwmsLdapFunctionalitiesWindows &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident
   static CwmsLdapFunctionalitiesWindows* m_Instance;

};

#endif // WMS_NO_LDAP
#endif // CwmsLDAPFUNCTIONALITIESWINDOWS_H
