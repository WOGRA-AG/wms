#ifndef WMS_NO_LDAP
#include "CwmsLdapFunctionalitiesWindows.h"

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QLibrary>

#include <winldap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CdmSettings.h"

CwmsLdapFunctionalitiesWindows* CwmsLdapFunctionalitiesWindows::m_Instance = 0;

QString CwmsLdapFunctionalitiesWindows::checkPasswordwLdap(QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, int perma){

    LDAP *pSession = nullptr;
    ULONG lRtn = LDAP_SUCCESS;
    ULONG version = LDAP_VERSION3;
    ULONG lport = port.toULong();
    Q_UNUSED(perma);

    //PWCHAR pserver = (PWCHAR) malloc(ldap_server.length() * sizeof(WCHAR));
    //ldap_server.toWCharArray(pserver);
    QByteArray aserver = ldap_server.toLocal8Bit();
    PCHAR pserver = aserver.data();

    // Initialize session. LDAP_PORT is the default port, 389.
    pSession = ldap_initA(pserver, lport);
    if (pSession == nullptr)
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));

    // Set the version to 3.0 (default version is 2.0).
    lRtn = ldap_set_option(pSession,LDAP_OPT_PROTOCOL_VERSION,(void*)&version);

    if(lRtn != LDAP_SUCCESS)
    {
        ldap_unbind(pSession);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));;
    }

    //--------------------------------------------------------
    // Connect to the server.
    //--------------------------------------------------------

    lRtn = ldap_connect(pSession, nullptr);

    if(lRtn != LDAP_SUCCESS)
    {
        ldap_unbind(pSession);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    //--------------------------------------------------------
    // Bind with credentials.
    //--------------------------------------------------------

    QString domain;
    int i=0;
    int j=0;
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

    //PCHAR pMyDN = dn.toLocal8Bit().data();
    QByteArray aMyDN = dn.toLocal8Bit();
    PCHAR pMyDN = aMyDN.data();

    //PCHAR puser_dn = user_dn.toLocal8Bit().data();
    QByteArray auser_dn = user_dn.toLocal8Bit();
    PCHAR puser_dn = auser_dn.data();

    //PCHAR ppasswd = passwd.toLocal8Bit().data();
    QByteArray apasswd = passwd.toLocal8Bit();
    PCHAR ppasswd = apasswd.data();

    //PCHAR phostName = help.toLocal8Bit().data();
    QByteArray ahostName = domain.toLocal8Bit();
    PCHAR phostName = ahostName.data();

    SEC_WINNT_AUTH_IDENTITY secIdent;

    secIdent.User = (short unsigned int*) puser_dn;
    secIdent.UserLength = user_dn.length();
    secIdent.Password = (short unsigned int*) ppasswd;
    secIdent.PasswordLength = passwd.length();
    secIdent.Domain = (short unsigned int*) phostName;
    secIdent.DomainLength = domain.length();
    secIdent.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

    // Session Handle, Domain DN, Credential, structure, Auth mode
    lRtn = ldap_bind_sA(pSession,pMyDN,(PCHAR)&secIdent,LDAP_AUTH_NEGOTIATE);
    if(lRtn == LDAP_SUCCESS)
    {
        secIdent.Password = nullptr; // Remove password pointer
        ppasswd = nullptr;         // Remove password pointer
        ldap_unbind(pSession);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }
    else
    {
        ldap_unbind(pSession);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));;
    }

    // Cleanup on error.
    if (lRtn != LDAP_SUCCESS)
        ldap_unbind(pSession);

    return QString::fromLocal8Bit(ldap_err2stringA(lRtn));
}

QString CwmsLdapFunctionalitiesWindows::ldap_lookup_with_filter(QList<QString>& listQ, QList<QPair<QString,QString> >& listA, QString ldap_server, QString port, QString dn, QString user_dn, QString passwd, QString filter){

    //---------------------------------------------------------
    // Initialize a session. LDAP_PORT is the default port, 389.
    //---------------------------------------------------------
    QByteArray aserver = ldap_server.toLocal8Bit();
    PCHAR hostName = aserver.data();
    ULONG lport = port.toULong();

    LDAP* pLdapConnection = nullptr;

    pLdapConnection = ldap_initA(hostName, lport);

    if (pLdapConnection == nullptr)
    {
        ldap_unbind(pLdapConnection);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    //-------------------------------------------------------
    // Set session options.
    //-------------------------------------------------------
    ULONG version = LDAP_VERSION3;
    ULONG numReturns = 10;
    ULONG lRtn = 0;

    // Set the version to 3.0 (default is 2.0).
    lRtn = ldap_set_option(
                    pLdapConnection,           // Session handle
                    LDAP_OPT_PROTOCOL_VERSION, // Option
                    (void*) &version);         // Option value

    if(lRtn != LDAP_SUCCESS)
    {
        ldap_unbind(pLdapConnection);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    // Set the limit on the number of entries returned to 10.
    lRtn = ldap_set_option(
                    pLdapConnection,       // Session handle
                    LDAP_OPT_SIZELIMIT,    // Option
                    (void*) &numReturns);  // Option value

    if(lRtn != LDAP_SUCCESS)
    {

        ldap_unbind(pLdapConnection);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }


    //--------------------------------------------------------
    // Connect to the server.
    //--------------------------------------------------------

    lRtn = ldap_connect(pLdapConnection, nullptr);

    if(lRtn == LDAP_SUCCESS)
        printf("ldap_connect succeeded \n");
    else
    {
        printf("ldap_connect failed with 0x%lx.\n",lRtn);
        ldap_unbind(pLdapConnection);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }


    //--------------------------------------------------------
    // Bind with credentials.
    //--------------------------------------------------------
    QString domain;
    int i=0;
    int j=0;
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

    //PCHAR pMyDN = dn.toLocal8Bit().data();
    QByteArray aMyDN = dn.toLocal8Bit();
    PCHAR pMyDN = aMyDN.data();

    //PCHAR puser_dn = user_dn.toLocal8Bit().data();
    QByteArray auser_dn = user_dn.toLocal8Bit();
    PCHAR puser_dn = auser_dn.data();

    //PCHAR ppasswd = passwd.toLocal8Bit().data();
    QByteArray apasswd = passwd.toLocal8Bit();
    PCHAR ppasswd = apasswd.data();

    //PCHAR phostName = help.toLocal8Bit().data();
    QByteArray ahostName = domain.toLocal8Bit();
    PCHAR phostName = ahostName.data();

    SEC_WINNT_AUTH_IDENTITY secIdent;

    secIdent.User = (short unsigned int*) puser_dn;
    secIdent.UserLength = user_dn.length();
    secIdent.Password = (short unsigned int*) ppasswd;
    secIdent.PasswordLength = passwd.length();
    secIdent.Domain = (short unsigned int*) phostName;
    secIdent.DomainLength = domain.length();
    secIdent.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

    lRtn = ldap_bind_sA(
                pLdapConnection,      // Session Handle
                pMyDN,                // Domain DN
                (PCHAR)&secIdent,     // Credential structure
                LDAP_AUTH_NEGOTIATE); // Auth mode
    if(lRtn == LDAP_SUCCESS)
    {
        printf("ldap_bind_s succeeded \n");
        secIdent.Password = nullptr; // Remove password pointer
        ppasswd = nullptr;         // Remove password pointer
    }
    else
    {
        printf("ldap_bind_s failed with 0x%lx.\n",lRtn);
        ldap_unbind(pLdapConnection);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    //----------------------------------------------------------
    // Perform a synchronous search of fabrikam.com for
    // all user objects that have a "person" category.
    //----------------------------------------------------------
    ULONG errorCode = LDAP_SUCCESS;
    LDAPMessage* pSearchResult;

    //PCHAR pMyFilter = "(&(objectClass=person)(sAMAccountName=Thomas)(!(objectClass=Computer)))";
    QByteArray aMyFilter = filter.toLocal8Bit();
    PCHAR pMyFilter = aMyFilter.data();

    PCHAR* pMyAttributes = nullptr;

    if(listQ.length() != 0)
    {

        pMyAttributes = new PCHAR[listQ.length()+1];

        for (int l = 0; l < listQ.length(); l++ )
        {
            pMyAttributes[l] = new char[listQ.at(l).length()+1];
            QByteArray tempString = listQ.at(l).toLocal8Bit();
            strcpy(pMyAttributes[l], tempString.data());

        }
        pMyAttributes[listQ.length()] = nullptr;
    }
    else
    {
        return "Es wurden keine Attribute angegeben";
    }
    errorCode = ldap_search_sA(
                    pLdapConnection,    // Session handle
                    pMyDN,              // DN to start search
                    LDAP_SCOPE_SUBTREE, // Scope
                    pMyFilter,          // Filter
                    pMyAttributes,      // Retrieve list of attributes
                    0,                  // Get both attributes and values
                    &pSearchResult);    // [out] Search results

    if (errorCode != LDAP_SUCCESS)
    {
        ldap_unbind_s(pLdapConnection);
        if(pSearchResult != nullptr)
            ldap_msgfree(pSearchResult);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    //----------------------------------------------------------
    // Get the number of entries returned.
    //----------------------------------------------------------
    ULONG numberOfEntries;

    numberOfEntries = ldap_count_entries(
                        pLdapConnection,    // Session handle
                        pSearchResult);     // Search result

    if(numberOfEntries == 0L)
    {
        //printf("ldap_count_entries failed with 0x%0lx \n",errorCode);
        ldap_unbind_s(pLdapConnection);
        if(pSearchResult != nullptr)
            ldap_msgfree(pSearchResult);
        return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
    }

    //----------------------------------------------------------
    // Loop through the search entries, get, and output the
    // requested list of attributes and values.
    //----------------------------------------------------------
    LDAPMessage* pEntry = nullptr;
    ULONG iCnt = 0;
    const char* sMsg;
    BerElement* pBer = nullptr;
    PCHAR pAttribute = nullptr;
    PCHAR* ppValue = nullptr;
    ULONG iValue = 0;

    for( iCnt=0; iCnt < numberOfEntries; iCnt++ )
    {
        // Get the first/next entry.
        if( !iCnt )
            pEntry = ldap_first_entry(pLdapConnection, pSearchResult);
        else
            pEntry = ldap_next_entry(pLdapConnection, pEntry);

        // Output a status message.
        sMsg = (!iCnt ? "ldap_first_entry" : "ldap_next_entry");
        if( pEntry == nullptr )
        {
            printf("%s failed with 0x%0lx \n", sMsg, LdapGetLastError());
            ldap_unbind_s(pLdapConnection);
            ldap_msgfree(pSearchResult);
            return QString::fromLocal8Bit(ldap_err2stringA(LdapGetLastError()));
        }

        // Get the first attribute name.
        pAttribute = ldap_first_attributeA(
                      pLdapConnection,   // Session handle
                      pEntry,            // Current entry
                      &pBer);            // [out] Current BerElement

        // Output the attribute names for the current object
        // and output values.
        while(pAttribute != nullptr)
        {
            // Get the string values.

            ppValue = ldap_get_valuesA(
                          pLdapConnection,  // Session Handle
                          pEntry,           // Current entry
                          pAttribute);      // Current attribute

            // Print status if no values are returned (nullptr ptr)
            if(ppValue == nullptr)
            {
                return "Attribute has no value";
            }

            // Output the attribute values
            else
            {
                iValue = ldap_count_valuesA(ppValue);
                if(!iValue)
                {
                    return "Bad value list";
                }
                else
                {
                    // Output the first attribute value
                    //printf(": %s", *ppValue);
                    QPair<QString,QString> temp;
                    temp.first = QString(QLatin1String(pAttribute));
                    temp.second = QString(QLatin1String(ppValue[0]));
                    listA.append(temp);

                    // Output more values if available
                    ULONG z;
                    for(z=1; z<iValue; z++)
                    {
                        QPair<QString,QString> temp2;
                        temp2.first = QString(QLatin1String(pAttribute));
                        temp2.second = QString(QLatin1String(ppValue[z]));
                        listA.append(temp2);
                    }
                }
            }

            // Free memory.
            if(ppValue != nullptr)
                ldap_value_freeA(ppValue);
            ppValue = nullptr;
            ldap_memfreeA(pAttribute);

            // Get next attribute name.
            pAttribute = ldap_next_attributeA(
                            pLdapConnection,   // Session Handle
                            pEntry,            // Current entry
                            pBer);             // Current BerElement
        }

        if( pBer != nullptr )
            ber_free(pBer,0);
        pBer = nullptr;
    }

    //----------------------------------------------------------
    // Normal cleanup and exit.
    //----------------------------------------------------------
    if(pMyAttributes != nullptr){
        for(int i=0;i<=listQ.length();i++)
            delete[] pMyAttributes[i];
        delete [] pMyAttributes;
    }
    pMyAttributes = nullptr;

    ldap_unbind(pLdapConnection);
    ldap_msgfree(pSearchResult);
    ldap_value_freeA(ppValue);



    return "Erfolg";
}

#endif
