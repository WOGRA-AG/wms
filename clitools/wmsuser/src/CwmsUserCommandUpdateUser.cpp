#include "CwmsUserCommandUpdateUser.h"

CwmsUserCommandUpdateUser::CwmsUserCommandUpdateUser()
{
}

CwmsUserCommandUpdateUser::~CwmsUserCommandUpdateUser()
{
}

QString CwmsUserCommandUpdateUser::GetCommand()
{
    return "updateUser";
}

bool CwmsUserCommandUpdateUser::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        CumUser* pUser = pUserManager->FindUserByLogin(qstrLogin);

        if (pUser)
        {
            if (p_qmArgs.contains(PASSWORD))
            {
                QString qstrValue = p_qmArgs[PASSWORD];
                pUser->SetPassword(qstrValue);
                pUser->SetEncrypted(false);
            }

            if (p_qmArgs.contains(FIRSTNAME))
            {
                QString qstrValue = p_qmArgs[FIRSTNAME];
                pUser->SetFirstName(qstrValue);
            }

            if (p_qmArgs.contains(LASTNAME))
            {
                QString qstrValue = p_qmArgs[LASTNAME];
                pUser->SetLastName(qstrValue);
            }

            if (p_qmArgs.contains(MAIL))
            {
                QString qstrValue = p_qmArgs[MAIL];
                pUser->SetEmail(qstrValue);
            }

            if (p_qmArgs.contains(ADMIN))
            {
                QString qstrValue = p_qmArgs[ADMIN];
                pUser->SetAdministrator(qstrValue.toLower() == "true");
            }

            if(SUCCESSFULL(pUserManager->UpdateUser(pUser)))
            {
                INFO("User updated.");
                return true;
            }
            else
            {
                ERR("Could not update User!")
            }
        }
        else
        {
            ERR("User not found!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
