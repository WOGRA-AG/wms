#include "CwmsUserCommandDeactivateUser.h"

CwmsUserCommandDeactivateUser::CwmsUserCommandDeactivateUser()
{
}

CwmsUserCommandDeactivateUser::~CwmsUserCommandDeactivateUser()
{
}


QString CwmsUserCommandDeactivateUser::GetCommand()
{
    return "deactivateUser";
}

bool CwmsUserCommandDeactivateUser::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        CumUser* pUser = pUserManager->FindUserByLogin(qstrLogin);

        if (pUser)
        {
            pUser->SetActive(false);
            pUserManager->UpdateUser(pUser);
            INFO("User deactivated!");
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
