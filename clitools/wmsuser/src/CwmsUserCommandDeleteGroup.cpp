#include "CwmsUserCommandDeleteGroup.h"

CwmsUserCommandDeleteGroup::CwmsUserCommandDeleteGroup()
{
}

CwmsUserCommandDeleteGroup::~CwmsUserCommandDeleteGroup()
{
}

QString CwmsUserCommandDeleteGroup::GetCommand()
{
    return "deleteGroup";
}

bool CwmsUserCommandDeleteGroup::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrGroupName = p_qmArgs[GROUP_NAME];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->DeleteUserGroup(qstrGroupName)))
        {
            INFO("Group deleted!");
            return true;
        }
        else
        {
            ERR("Group deletion failed!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
