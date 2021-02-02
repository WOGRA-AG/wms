
// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

// Basetools Includes
#include "CwmsContext.h"

// own includes
#include "CwmsPluginsCommandActivatePlugin.h"
#include "CwmsPluginsCommandDeactivatePlugin.h"
#include "CwmsPluginsCommandListPlugins.h"
#include "CwmsPluginsHandler.h"

#define ALIAS_APP "WMS_Runtime"
#define CONTAINER_ARG "container"
#define LOGIN_ARG "login"
#define PASSWORD_ARG "password"
#define FILENAME_ARG "filename"
#define CONFIG_ARG "config"
#define MODE_ARG "mode"
#define SCHEME "Technical_Server"
#define COMMAND "command"

CwmsPluginsHandler::CwmsPluginsHandler(QMap<QString,QString> p_qmArguments)
: m_qmArguments(p_qmArguments)
{
}

CwmsPluginsHandler::~CwmsPluginsHandler()
{

}

bool CwmsPluginsHandler::Init()
{
    bool bRet = false;
    QString qstrLogin = m_qmArguments[LOGIN_ARG];
    QString qstrPassword = m_qmArguments[PASSWORD_ARG];
    QString qstrScheme = SCHEME;

    CdmSessionManager* pSessionManager = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);
    int iSessionId = 0;
    iSessionId = pSessionManager->CreateNewSession(qstrLogin, qstrPassword);

    if (SUCCESSFULL(iSessionId))
    {
        // First load scheme
        CdmDataProvider* pManager = pSessionManager->GetDataProvider();

        if (SUCCESSFULL(pManager->LoadScheme(qstrScheme)))
        {
            bRet = true;
        }
    }

    CwmsContext::CreateContext(eWmsApplicationContextServer);

    CwmsPluginsCommandAbstract* pCommand = new CwmsPluginsCommandActivatePlugin();
    m_qmCommands.insert(pCommand->GetCommand(), pCommand);
    pCommand = new CwmsPluginsCommandDeactivatePlugin();
    m_qmCommands.insert(pCommand->GetCommand(), pCommand);
    pCommand = new CwmsPluginsCommandListPlugins();
    m_qmCommands.insert(pCommand->GetCommand(), pCommand);

    return bRet;
}

bool CwmsPluginsHandler::Run()
{
    bool bRet = Validate();

    if (bRet)
    {
        bRet = Init();

        if (bRet)
        {
            if (m_qmCommands.contains(m_qmArguments[COMMAND]))
            {
                CwmsPluginsCommandAbstract* pCommand = m_qmCommands[m_qmArguments[COMMAND]];
                pCommand->Run(m_qmArguments);
            }
            else
            {
                ERR("Unknown command or command not given.");
            }

            CdmSessionManager* pSessionManager = CdmSessionManager::GetSessionManager();

            if (CHKPTR(pSessionManager))
            {
                pSessionManager->Logout();
            }
        }
    }

    return bRet;
}

bool CwmsPluginsHandler::Validate()
{
    bool bRet = true;

    return bRet;
}

