#include "CwmsUserCommandRenameGroup.h"

CwmsUserCommandRenameGroup::CwmsUserCommandRenameGroup()
{
}

CwmsUserCommandRenameGroup::~CwmsUserCommandRenameGroup()
{
}


QString CwmsUserCommandRenameGroup::GetCommand()
{
    return "renameGroup";
}

bool CwmsUserCommandRenameGroup::Run(QMap<QString, QString> p_qmArgs)
{
    QString qstrGroupName = p_qmArgs[GROUP_NAME];
    QString qstrNewName = p_qmArgs[NEW_GROUP_NAME];

    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        if (SUCCESSFULL(pUserManager->RemoveUserFromGroup(qstrGroupName, qstrNewName)))
        {
            INFO("Group renamed.");
            return true;
        }
        else
        {
            ERR("Could not rename group!");
        }
    }
    else
    {
        ERR("Usermanager not found!");
    }

    return false;
}
