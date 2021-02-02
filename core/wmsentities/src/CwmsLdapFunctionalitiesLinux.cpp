#ifndef WMS_NO_LDAP
#define SCOPE LDAP_SCOPE_SUBTREE

#include "CwmsLdapFunctionalitiesLinux.h"
#include "ldap.h"
#include "lber.h"

#include <QByteArray>
#include <QList>
#include <iterator>
#include <string.h>
#include <stdio.h>

#include "CdmSettings.h"


CwmsLdapFunctionalitiesLinux* CwmsLdapFunctionalitiesLinux::m_Instance = 0;

QString CwmsLdapFunctionalitiesLinux::checkPasswordwLdap(QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, int perma){

    LDAP *ld = nullptr;
    int rc;
    int version = LDAP_VERSION3;
    struct berval cred;

    QString HoleServerInfo = "ldap://"+ldap_server+":"+port;

    QString domain;
    int i = 0;
    int j = 0;

    for(i=0;i<=dn.length();i++)
    {
        if(i<dn.length()-2 && dn.data()[i] == 'd' && dn.data()[i+1] == 'c' && dn.data()[i+2] == '=')
        {
            j=i+3;
            while(dn.data()[j] != ',' && dn.data()[j] != '\0')
            {
                domain = domain + dn.data()[j];
                j++;
            }
            if(dn.data()[j] == ',')
                domain = domain + '.';
        }
    }


    QString HoleUser = user_dn+"@"+domain;

    QByteArray ba = HoleServerInfo.toLatin1();
    const char *clserver = ba.data();

    QByteArray ba2 = HoleUser.toLatin1();
    const char *cuserdn = ba2.data();

    QByteArray ba3 = passwd.toLatin1();
    const char *cpasswd = ba3.data();

    /*
    printf("%s\n",clserver);
    printf("%s\n",cuserdn);
    printf("%s\n",(char*)cpasswd);
    printf("%i\n", strlen(cpasswd));
    */

    cred.bv_val = (char*) cpasswd;
    cred.bv_len = strlen(cpasswd);

    struct berval* returned_creds;

    if(ld != nullptr)
    {
        int result = ldap_unbind_ext_s(ld,nullptr,nullptr);

        if (result != 0) {
            return QString::fromLocal8Bit(ldap_err2string(result));
        }
    }

    /* Open LDAP Connection */
    if((rc = ldap_initialize(&ld,clserver)) != LDAP_SUCCESS)
    {

        if(ld != nullptr)
        {
            int result = ldap_unbind_ext_s(ld,nullptr,nullptr);

            if (result != 0) {
                return QString::fromLocal8Bit(ldap_err2string(result));
            }
        }

        return QString::fromLocal8Bit(ldap_err2string(rc));

    }

    if (LDAP_OPT_SUCCESS != (rc=ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version))) {

        if(ld != nullptr)
        {
            int result = ldap_unbind_ext_s(ld,nullptr,nullptr);

            if (result != 0) {
                return QString::fromLocal8Bit(ldap_err2string(result));
            }
        }

        return QString::fromLocal8Bit(ldap_err2string(rc));

    }

    rc = ldap_sasl_bind_s(ld, cuserdn, LDAP_SASL_AUTOMATIC, &cred, nullptr, nullptr, &returned_creds);

    if( rc != LDAP_SUCCESS )
    {
        ber_bvfree(returned_creds);

        if(ld != nullptr)
        {
            int result = ldap_unbind_ext_s(ld,nullptr,nullptr);

            if (result != 0) {
                return QString::fromLocal8Bit(ldap_err2string(result));
            }
        }

        return QString::fromLocal8Bit(ldap_err2string(rc));
    }


    ber_bvfree(returned_creds);
    cpasswd = nullptr;

    if(ld != nullptr)
    {
        int result = ldap_unbind_ext_s(ld,nullptr,nullptr);

        if (result != 0) {
            return QString::fromLocal8Bit(ldap_err2string(result));
        }
    }

    return "Erfolg";
}

QString CwmsLdapFunctionalitiesLinux::ldap_lookup_with_filter(QList<QString>& listQ, QList<QPair<QString,QString> >& listA, QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, QString filter){

    //int global_counter = 0;

    QString hostname = "ldap://"+ldap_server+":"+port;

    QByteArray byteArrayHostname = hostname.toLatin1();
    const char *phostname = byteArrayHostname.data();

    QByteArray byteArrayBaseDN = dn.toLatin1();
    const char *pdn = byteArrayBaseDN.data();

    QByteArray byteArrayFilter = filter.toLatin1();
    const char *pfilter = byteArrayFilter.data();

    QByteArray byteArrayPasswd = passwd.toLatin1();
    char *ppasswd = byteArrayPasswd.data();

    LDAP *ld;

    LDAPMessage *msg;
    BerElement *ber = nullptr;
    struct berval **vals;
    LDAPMessage *entry;

    struct berval cred;
    cred.bv_val = (char*) ppasswd;
    cred.bv_len = strlen(ppasswd);

    struct berval* returned_creds;

    LDAPControl **serverctrls;

    char *attr, *idn, *matched_msg = nullptr, *error_msg = nullptr;

    char **referrals;

    int version, i = 0, msgid = 0, rc = 0, parse_rc = 0, finished = 0, result = 0, num_entries = 0, num_refs = 0;
    QList<QString>::iterator iter;

    struct timeval zerotime;

    zerotime.tv_sec = zerotime.tv_usec = 0L;

    QString domain;

    int u = 0;
    int v = 0;

    for(u=0;u<=dn.length();u++)
    {
        if(u<dn.length()-2 && dn.data()[u] == 'd' && dn.data()[u+1] == 'c' && dn.data()[u+2] == '=')
        {
            v=u+3;
            while(dn.data()[v] != ',' && dn.data()[v] != '\0')
            {
                domain = domain + dn.data()[v];
                v++;
            }
            if(dn.data()[v] == ',')
                domain = domain + '.';
        }
    }

    QString userAndDomain = user_dn+"@"+domain;
    QByteArray byteArrayUserAndDomain = userAndDomain.toLatin1();
    const char *puserAndDomain =  byteArrayUserAndDomain.data();


    /* Get a handle to an LDAP connection. */

    if((rc = ldap_initialize(&ld,phostname)) != LDAP_SUCCESS)
    {
        return QString::fromLocal8Bit(ldap_err2string(rc));
    }

    version = LDAP_VERSION3;

    if ( (rc=ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &version )) != LDAP_SUCCESS ) {

        result = ldap_unbind_ext_s(ld,nullptr,nullptr);

        if (result != 0) {
            return QString::fromLocal8Bit(ldap_err2string(result));
        }

        return QString::fromLocal8Bit(ldap_err2string(rc));
    }

    /* Bind to the server. */

    rc = ldap_sasl_bind_s(ld, puserAndDomain, LDAP_SASL_AUTOMATIC, &cred, nullptr, nullptr, &returned_creds);

    if( rc != LDAP_SUCCESS )
    {
        ber_bvfree(returned_creds);
        if(ld != nullptr)
        {
            result = ldap_unbind_ext_s(ld,nullptr,nullptr);
            if (result != 0) {
                return QString::fromLocal8Bit(ldap_err2string(result));
            }
        }
        return QString::fromLocal8Bit(ldap_err2string(rc));
    }

    /* Send the LDAP search request. */

    rc = ldap_search_ext( ld, pdn, SCOPE, pfilter, nullptr, 0, nullptr, nullptr, nullptr, LDAP_NO_LIMIT, &msgid );

    if ( rc != LDAP_SUCCESS ) {

        result = ldap_unbind_ext_s(ld,nullptr,nullptr);
        if (result != 0) {
            return QString::fromLocal8Bit(ldap_err2string(result));
        }

        return QString::fromLocal8Bit(ldap_err2string(rc));
    }

    /* Poll the server for the results of the search operation.
    Passing LDAP_MSG_ONE indicates that you want to receive
    the entries one at a time, as they come in. If the next
    entry that you retrieve is nullptr, there are no more entries. */

    while ( !finished ) {

        rc = ldap_result( ld, msgid, LDAP_MSG_ONE, &zerotime, &msg );

        /* The server can return three types of results back to the client,
        and the return value of ldap_result() indicates the result type:
        LDAP_RES_SEARCH_ENTRY identifies an entry found by the search,
        LDAP_RES_SEARCH_REFERENCE identifies a search reference returned
        by the server, and LDAP_RES_SEARCH_RESULT is the last result
        sent from the server to the client after the operation completes.
        You need to check for each of these types of results. */

        switch ( rc ) {
            case -1:
                /* An error occurred. */
                result = ldap_unbind_ext_s(ld,nullptr,nullptr);
                if (result != 0) {
                    return QString::fromLocal8Bit(ldap_err2string(result));
                }

                return QString::fromLocal8Bit(ldap_err2string(rc));
            break;

            case 0:
                /* The timeout period specified by zerotime was exceeded.
                   This means that the server has still not yet sent the
                   results of the search operation back to your client.
                   Break out of this switch statement, and continue calling
                   ldap_result() to poll for results. */
            break;

            case LDAP_RES_SEARCH_ENTRY:
                /* The server sent one of the entries found by the search
                operation. Print the DN, attributes, and values of the entry. */
                /* Keep track of the number of entries found. */

                num_entries++;

                /* Get and print the DN of the entry. */

                if (( idn = ldap_get_dn( ld, msg )) != nullptr ) {
                    //printf( "dn: %s\n", idn );
                    ldap_memfree( idn );
                }

                for (entry = ldap_first_entry(ld, msg); entry != nullptr; entry = ldap_next_entry(ld, entry)) {
                    for( attr = ldap_first_attribute(ld, entry, &ber); attr != nullptr;attr = ldap_next_attribute(ld, entry, ber))
                    {
                        if ((vals = ldap_get_values_len(ld, entry, attr)) != nullptr)  {
                            for(i = 0; vals[i] != nullptr; i++) {

                                for (iter = listQ.begin(); iter != listQ.end(); ++iter)
                                {

                                    QByteArray byteArrayTemp = (*iter).toLatin1();
                                    char *Temp = byteArrayTemp.data();

                                    if(strcmp(attr, Temp) == 0) {

                                        QPair<QString,QString> temp;
                                        temp.first = QString(QLatin1String(attr));
                                        temp.second = QString(QLatin1String(vals[i]->bv_val));
                                        listA.append(temp);
                                    }
                                }
                            }
                        }
                        ldap_value_free_len(vals);
                    }
                    ldap_memfree(attr);

                }

                  /* clean up */
                  ldap_msgfree(msg);
                  ldap_msgfree(entry);

                  if (ber != nullptr) {
                      ber_free(ber,0);
                  }

            break;

            case LDAP_RES_SEARCH_REFERENCE:
                /* The server sent a search reference encountered during the
                search operation. */
                /* Keep track of the number of search references returned from
                the server. */

                num_refs++;

                /* Parse the result and print the search references.
                Ideally, rather than print them out, you would follow the
                references. */

                parse_rc = ldap_parse_reference( ld, msg, &referrals, nullptr, 1 );
                if ( parse_rc != LDAP_SUCCESS ) {
                    result = ldap_unbind_ext_s(ld,nullptr,nullptr);
                    if (result != 0) {
                        return QString::fromLocal8Bit(ldap_err2string(result));
                    }

                    return QString::fromLocal8Bit(ldap_err2string(parse_rc));
                }

                if ( referrals != nullptr ) {
                    for ( i = 0; referrals[ i ] != nullptr; i++ ) {
                        //printf( "Search reference: %s\n\n", referrals[ i ] );
                    }
                    free( referrals );
                }

            break;

            case LDAP_RES_SEARCH_RESULT:
                /* Parse the final result received from the server. Note the last
                argument is a non-zero value, which indicates that the
                LDAPMessage structure will be freed when done. (No need
                to call ldap_msgfree().) */

                finished = true;

                parse_rc = ldap_parse_result( ld, msg, &rc, &matched_msg, &error_msg, nullptr, &serverctrls, 1 );

                if ( parse_rc != LDAP_SUCCESS ) {
                    result = ldap_unbind_ext_s(ld,nullptr,nullptr);
                    if (result != 0) {
                        return QString::fromLocal8Bit(ldap_err2string(result));
                    }

                    return QString::fromLocal8Bit(ldap_err2string(parse_rc));
                }

                /* Check the results of the LDAP search operation. */

                if ( rc != LDAP_SUCCESS ) {

                    return QString::fromLocal8Bit(ldap_err2string(rc));

                } else {
                    /*
                    printf( "Search completed successfully.\n"
                    "Entries found: %d\n"
                    "Search references returned: %d\n"
                    "Counted to %d while waiting for the search operation.\n",
                    num_entries, num_refs, global_counter );
                    */
                }

            break;

            default:

            break;
        }

        /* Do other work here while waiting for the search operation to complete. */

        if ( !finished ) {

        }
    }

    if(num_entries >1)
    {
        result = ldap_unbind_ext_s(ld,nullptr,nullptr);
        if (result != 0) {
            return QString::fromLocal8Bit(ldap_err2string(result));
        }
        return "Es wurden mehrere Benutzer zur Suchanfrage gefunden. Überprüfen Sie den Suchfilter.";
    }

    /* Disconnect when done. */
    result = ldap_unbind_ext_s(ld,nullptr,nullptr);
    if (result != 0) {
        return QString::fromLocal8Bit(ldap_err2string(result));
    }

    ppasswd = nullptr;

    return "Erfolg";
}


#endif
