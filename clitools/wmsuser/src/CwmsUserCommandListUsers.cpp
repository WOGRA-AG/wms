#include "CwmsUserCommandListUsers.h"

CwmsUserCommandListUsers::CwmsUserCommandListUsers()
{
}


QString CwmsUserCommandListUsers::GetCommand()
{
    return "listUsers";
}

bool CwmsUserCommandListUsers::Run(QMap<QString, QString> p_qmArgs)
{
    Q_UNUSED(p_qmArgs);
    CumUserManager* pUserManager = GetUserManager();

    if (CHKPTR(pUserManager))
    {
        QLinkedList<CumUser*> qllUsers;
        pUserManager->GetUserListUnmanaged(qllUsers);
        QLinkedList<CumUser*>::iterator qllIt = qllUsers.begin();
        QLinkedList<CumUser*>::iterator qllItEnd = qllUsers.end();
        QString qstrOutput = "login;Lastname;Firstname;E-Mail;ID;Active;Admin\r\n";

        for (; qllIt != qllItEnd; ++qllIt)
        {
            CumUser* pUser = *qllIt;

            if (CHKPTR(pUser))
            {
                qstrOutput += pUser->GetLogin() + ";" + pUser->GetLastName() + ";" +
                        pUser->GetFirstName() + ";" + pUser->GetEmail() + ";" + QString::number(pUser->GetId()) +
                        ";" + QString::number(pUser->IsActive()) + ";"+ QString::number(pUser->IsAdministrator()) + "\r\n";
            }
        }

        INFO("Users:\n" + qstrOutput);
        return true;
    }
    return false;
}
