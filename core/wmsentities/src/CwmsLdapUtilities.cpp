#ifndef WMS_NO_LDAP
#include "CwmsLdapUtilities.h"
#include "CdmDataProvider.h"
#include "CdmLogging.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include <QDebug>
#include <ctime>
#include <iterator>

CwmsLdapUtilities::CwmsLdapUtilities()
{
}

QString CwmsLdapUtilities::prepareEmailForInsert(QString email){

    QString firstEmail;

    int u = 0;

    for(u=0;u<=email.length();u++)
    {
        if(email.data()[u] != ',' && email.data()[u] != '\0')
        {
                firstEmail += email.data()[u];
        }
    }
    if(u!=0)
        return firstEmail;
    else
    {
        return "";
    }
}

QString CwmsLdapUtilities::setRandomPassword(){

    static const char alphanum[] =
    "0123456789"
    "!@#$%^&*"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;
    srand(time(0));
    QString Str;
    for(unsigned int i = 0; i < 20; ++i)
    {
        Str += alphanum[rand() % stringLength];
    }
    return Str;
}

void CwmsLdapUtilities::IsUserInUserGroupOrAdminGroup(QList<QString> &listQ, QList<QPair<QString,QString> >& listA, QString AdminGruppenName, QString BenutzerGruppenName,bool& adminflag, bool& userflag)
{
    //Falls keine Gruppennamen eingegeben wurden,
    //wird eine Anmeldung nicht gewährt.
    //Ansonsten muss Admin-, bzw. User- Gruppenname mit einer
    //der Strings in listA übereinstimmen.

    QList<QPair<QString,QString> >::iterator iter;

    for (iter = listA.begin(); iter != listA.end(); ++iter)
    {
        if(listQ.at(0) == iter->first) {

            if(iter->second.indexOf(AdminGruppenName)>=0)
            {
                adminflag=true;
            }
            if(iter->second.indexOf(BenutzerGruppenName)>=0)
            {
                userflag=true;
            }
            if(adminflag && userflag)
                break;
        }
    }
}


bool CwmsLdapUtilities::updateUserData(CumUserManager* p_pUserManager,
                                      CumUser* p_pUser,
                                      QList<QString>& listQ,
                                      QList<QPair<QString,QString> >& listA,
                                      bool adminflag)
{
    QList<QPair<QString,QString> >::iterator iterA;

    if (CHKPTR(p_pUserManager) && CHKPTR(p_pUser))
    {
        CwmsLdapUtilities ldUtils;

        if(listA.size()<2)
            return false;

        p_pUser->SetAdministrator(adminflag);
        for (iterA = listA.begin(); iterA != listA.end(); ++iterA)
        {
            if(QString::compare((*iterA).first,listQ.at(1)) == 0)
               p_pUser->SetFirstName((*iterA).second);
            else if(QString::compare((*iterA).first,listQ.at(2)) == 0)
               p_pUser->SetLastName((*iterA).second);
            else if(QString::compare((*iterA).first,listQ.at(3)) == 0)
               p_pUser->SetEmail(ldUtils.prepareEmailForInsert((*iterA).second));
        }

        p_pUser->SetPassword(ldUtils.setRandomPassword());
        p_pUserManager->UpdateUser(p_pUser);
    }

    return true;
}

bool CwmsLdapUtilities::createUserData(CumUserManager* p_pUserManager,
                                      QList<QString>& listQ,
                                      QList<QPair<QString,QString> >& listA,
                                      QString user,
                                      QString appName,
                                      bool adminflag)
{
    Q_UNUSED(appName);
    QList<QPair<QString,QString> >::iterator iterA;

    if (CHKPTR(p_pUserManager))
    {
        CwmsLdapUtilities ldUtils;

        if(listA.size()<2)
            return false;

        QString firstName;
        QString lastName;
        QString email;

        for (iterA = listA.begin(); iterA != listA.end(); ++iterA)
        {
            if(QString::compare((*iterA).first,listQ.at(1)) == 0)
                firstName = (*iterA).second;
            else if(QString::compare((*iterA).first,listQ.at(2)) == 0)
                lastName = (*iterA).second;
            else if(QString::compare((*iterA).first,listQ.at(3)) == 0)
                email = ldUtils.prepareEmailForInsert((*iterA).second);
        }

        CumUser* pUser = new CumUser(p_pUserManager);
        pUser->SetLogin(user);
        pUser->SetPassword(ldUtils.setRandomPassword());
        pUser->SetLastName(lastName);
        pUser->SetFirstName(firstName);
        pUser->SetEmail(email);
        pUser->SetAdministrator(adminflag);
        pUser->SetActive(true);
        pUser->SetSchemeIndependent(true);

        p_pUserManager->CreateUser(pUser);
    }

    return true;
}

#endif
