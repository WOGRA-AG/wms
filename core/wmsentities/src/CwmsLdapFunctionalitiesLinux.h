#ifndef CwmsLDAPFUNCTIONALITIESLINUX_H
#define CwmsLDAPFUNCTIONALITIESLINUX_H
#ifndef WMS_NO_LDAP

#include <QString>
#include "CwmsLdapFassade.h"
#include "basetools.h"

class BASETOOLS_API CwmsLdapFunctionalitiesLinux : public QObject,public CwmsLdapFassade
{
    Q_OBJECT
    Q_INTERFACES(CwmsLdapFassade)

public:
    static CwmsLdapFunctionalitiesLinux* instance()
    {
        if (!m_Instance)
        {
            if (!m_Instance)
                m_Instance = new CwmsLdapFunctionalitiesLinux;
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

    CwmsLdapFunctionalitiesLinux() {}
    virtual ~CwmsLdapFunctionalitiesLinux() {}
    CwmsLdapFunctionalitiesLinux(const CwmsLdapFunctionalitiesLinux &); // hide copy constructor
    CwmsLdapFunctionalitiesLinux& operator=(const CwmsLdapFunctionalitiesLinux &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident
   static CwmsLdapFunctionalitiesLinux* m_Instance;

};

#endif // WMS_NO_LDAP
#endif // CwmsLDAPFUNCTIONALITIESLINUX_H
