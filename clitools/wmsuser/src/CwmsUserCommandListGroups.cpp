#include "CwmsUserCommandListGroups.h"

CwmsUserCommandListGroups::CwmsUserCommandListGroups()
{
}


QString CwmsUserCommandListGroups::GetCommand()
{
    return "listGroups";
}

bool CwmsUserCommandListGroups::Run(QMap<QString, QString> p_qmArgs)
{
    Q_UNUSED(p_qmArgs);
    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        QList<CumUserGroup*> qllGroups;
        pUserManager->GetUserGroupList(qllGroups);
        QList<CumUserGroup*>::iterator qllIt = qllGroups.begin();
        QList<CumUserGroup*>::iterator qllItEnd = qllGroups.end();
        QString qstrOutput = "Group\r\n";

        for (; qllIt != qllItEnd; ++qllIt)
        {
            CumUserGroup* pGroup = *qllIt;

            if (CHKPTR(pGroup))
            {
                qstrOutput += pGroup->GetGroupName() + "\r\n";
            }
        }

        INFO("Groups:\n" + qstrOutput);
        return true;
    }
    return false;
}
