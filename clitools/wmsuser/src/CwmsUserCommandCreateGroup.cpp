#include "CwmsUserCommandCreateGroup.h"

CwmsUserCommandCreateGroup::CwmsUserCommandCreateGroup()
{
}

CwmsUserCommandCreateGroup::~CwmsUserCommandCreateGroup()
{
}

QString CwmsUserCommandCreateGroup::GetCommand()
{
    return "createGroup";
}

bool CwmsUserCommandCreateGroup::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrGroup = p_qmArgs[GROUP_NAME];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->CreateUserGroup(qstrGroup)))
        {
            INFO("Group created.");
            return true;
        }
        else
        {
            ERR("Could not create group");
        }
    }
    else
    {
        ERR("UserManager not found!");
    }

    return false;
}
