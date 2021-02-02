#include "CwmsUserCommandAddUserToGroup.h"

CwmsUserCommandAddUserToGroup::CwmsUserCommandAddUserToGroup()
{
}

CwmsUserCommandAddUserToGroup::~CwmsUserCommandAddUserToGroup()
{
}

QString CwmsUserCommandAddUserToGroup::GetCommand()
{
    return "addUserToGroup";
}

bool CwmsUserCommandAddUserToGroup::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrGroupName = p_qmArgs[GROUP_NAME];
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->AddUserToUserGroup(qstrLogin, qstrGroupName)))
        {
            INFO("User added to group.");
            return true;
        }
        else
        {
            ERR("User could not be added to group!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
