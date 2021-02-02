#include "CwmsUserCommandRemoveUserFromGroup.h"

CwmsUserCommandRemoveUserFromGroup::CwmsUserCommandRemoveUserFromGroup()
{
}

CwmsUserCommandRemoveUserFromGroup::~CwmsUserCommandRemoveUserFromGroup()
{
}


QString CwmsUserCommandRemoveUserFromGroup::GetCommand()
{
    return "removeUserFromGroup";
}

bool CwmsUserCommandRemoveUserFromGroup::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrGroupName = p_qmArgs[GROUP_NAME];
    QString qstrLogin = p_qmArgs[LOGIN];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->RemoveUserFromGroup(qstrLogin, qstrGroupName)))
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
