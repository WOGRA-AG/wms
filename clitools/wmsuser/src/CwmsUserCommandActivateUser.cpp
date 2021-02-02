#include "CwmsUserCommandActivateUser.h"

CwmsUserCommandActivateUser::CwmsUserCommandActivateUser()
{
}


QString CwmsUserCommandActivateUser::GetCommand()
{
    return "activateUser";
}

bool CwmsUserCommandActivateUser::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        CumUser* pUser = pUserManager->FindUserByLogin(qstrLogin);

        if (pUser)
        {
            pUser->SetActive(true);
            pUserManager->UpdateUser(pUser);
            INFO("User activated!");
            return true;
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
