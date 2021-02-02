
// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"



// own includes
#include "CwmsUserCommandActivateUser.h"
#include "CwmsUserCommandDeactivateUser.h"
#include "CwmsUserCommandCreateGroup.h"
#include "CwmsUserCommandCreateUser.h"
#include "CwmsUserCommandAddUserToGroup.h"
#include "CwmsUserCommandDeleteGroup.h"
#include "CwmsUserCommandDeleteUser.h"
#include "CwmsUserCommandRemoveUserFromGroup.h"
#include "CwmsUserCommandRenameGroup.h"
#include "CwmsUserCommandUpdateUser.h"
#include "CwmsUserCommandListGroups.h"
#include "CwmsUserCommandListUsers.h"

#include "CwmsUserHandler.h"

#define CONTAINER_ARG "container"
#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define FILENAME_ARG "filename"
#define CONFIG_ARG "config"
#define MODE_ARG "mode"
#define SCHEME_TECHNICAL_SERVER "Technical_Server"
#define COMMAND "command"

CwmsUserHandler::CwmsUserHandler(QMap<QString,QString> p_qmArguments)
: m_qmArguments(p_qmArguments)
{
}

CwmsUserHandler::~CwmsUserHandler()
{

}

bool CwmsUserHandler::Init()
{
    bool bRet = false;
    QString qstrLogin = m_qmArguments[LOGIN_ARG];
    QString qstrPassword = m_qmArguments[PASSWORD_ARG];
    QString qstrScheme = SCHEME_TECHNICAL_SERVER;

    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    int iSessionId = 0;
    iSessionId = pSessionManager->CreateNewSession(qstrLogin, qstrPassword);

    bRet = (SUCCESSFULL(iSessionId));

    if (bRet)
    {
        CwmsUserCommandAbstract* pCommand = new CwmsUserCommandActivateUser();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandDeactivateUser();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandDeleteUser();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandDeleteGroup();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandCreateGroup();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandCreateUser();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandAddUserToGroup();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandRemoveUserFromGroup();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandRenameGroup();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandUpdateUser();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandListUsers();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
        pCommand = new CwmsUserCommandListGroups();
        m_qmCommands.insert(pCommand->GetCommand(), pCommand);
   }

   return bRet;
}

bool CwmsUserHandler::Run()
{
    bool bRet = Validate();

    if (bRet)
    {
        bRet = Init();

        if (bRet)
        {
            if (m_qmCommands.contains(m_qmArguments[COMMAND]))
            {
                CwmsUserCommandAbstract* pCommand = m_qmCommands[m_qmArguments[COMMAND]];
                pCommand->Run(m_qmArguments);
            }
            else
            {
                ERR("Unknown command or command not given.");
            }
        }

        CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

        if (CHKPTR(pSessionManager))
        {
            pSessionManager->Logout();
        }
    }

    return bRet;
}

bool CwmsUserHandler::Validate()
{
    bool bRet = true;

    if (!m_qmArguments.contains(LOGIN_ARG) || !m_qmArguments.contains(PASSWORD_ARG))
    {
        ERR("You need -login and -password for using this app!");
        bRet = false;
    }

    return bRet;
}

