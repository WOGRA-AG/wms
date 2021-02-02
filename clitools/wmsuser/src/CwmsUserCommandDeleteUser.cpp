#include "CwmsUserCommandDeleteUser.h"

CwmsUserCommandDeleteUser::CwmsUserCommandDeleteUser()
{
}

CwmsUserCommandDeleteUser::~CwmsUserCommandDeleteUser()
{
}


QString CwmsUserCommandDeleteUser::GetCommand()
{
    return "deleteUser";
}

bool CwmsUserCommandDeleteUser::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->DeleteUser(qstrLogin)))
        {
            INFO("User deleted!");
            return true;
        }
        else
        {
            ERR("User deletion failed!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
