#include "CwmsUserCommandCreateUser.h"

CwmsUserCommandCreateUser::CwmsUserCommandCreateUser()
{
}

CwmsUserCommandCreateUser::~CwmsUserCommandCreateUser()
{
}

QString CwmsUserCommandCreateUser::GetCommand()
{
    return "createUser";
}

bool CwmsUserCommandCreateUser::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrLogin = p_qmArgs[LOGIN];
    QString qstrPassword = p_qmArgs[PASSWORD];
    QString qstrFirstName = p_qmArgs[FIRSTNAME];
    QString qstrLastName = p_qmArgs[LASTNAME];
    QString qstrEmail = p_qmArgs[MAIL];
    QString qstrAdmin = p_qmArgs[ADMIN];
    QString qstrScheme = p_qmArgs[SCHEME];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        CumUser* pUser = new CumUser(pUserManager);
        pUser->SetLogin(qstrLogin);
        pUser->SetPassword(qstrPassword);
        pUser->SetFirstName(qstrFirstName);
        pUser->SetLastName(qstrLastName);
        pUser->SetEmail(qstrEmail);
        pUser->SetAdministrator(qstrAdmin == "true");

        if (!qstrScheme.isEmpty())
        {
            pUser->AddSchemeUri(qstrScheme);
            pUser->SetSchemeIndependent(false);
        }
        else
        {
            pUser->SetSchemeIndependent(true);
        }

        if(SUCCESSFULL(pUserManager->CreateUser(pUser)))
        {
            INFO("User created.");
            return true;
        }
        else
        {
            ERR("Could not create user!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
