
// System and Qt Includes
#include <QUrl>


// WMS COMMONS Includes
#include "CwmsHttpService.h"
#include "CwmsSettingsStoreFactory.h"
#include "CwmsServerSettings.h"


// WMS Includes
#include "CdmLogging.h"
#include "CdmLogfileWriter.h"
#include "CwmsJson.h"
#include "CdmSessionManager.h"
#include "CdmSettings.h"

// Basetools Includes
#include "CwmsContext.h"

// own Includes
#include "CwsCommandStartServer.h"
#include "CwsCommandStopServer.h"
#include "CwsCommandIsRunning.h"
#include "CwsCommandGetOpenSessions.h"
#include "CwsCommandGetServerSettings.h"
#include "CwsCommandLogin.h"
#include "CwsCommandLogout.h"
#include "CwsCommandUpdateServerSettings.h"
#include "CwsCommandGetAppStoreData.h"
#include "CwsCommandAddAppToStore.h"
#include "CwsCommandDeleteAppFromStore.h"

#include "CwsServerCommandHandler.h"


// DEFINES

#define START_SERVER "Start"
#define STOP_SERVER "Stop"
#define GET_OPEN_SESSIONS "GetOpenSessions"
#define GET_STATE "GetState"
#define GET_SERVER_CONFIG "GetServerConfig"
#define UPDATE_SERVER_CONFIG "UpdateServerConfig"
#define LOGIN "Login"
#define LOGOUT "Logout"
#define INSTALL_LOGGING "InstallLogging"
#define GET_APPSTORE_DATA "GetAppstoreData"
#define ADD_APPSTORE_SCHEME "AddAppStoreScheme"
#define DELETE_APPSTORE_SCHEME "DeleteAppStoreScheme"

CwsServerCommandHandler::CwsServerCommandHandler()
    : m_Server(8383, 1, nullptr)
{
    IwmsParser* pParser = new CwmsJson();
    IwmsSerializer* pSerializer = new CwmsJson();
    m_DataExchangeConfigurator.SetParser(pParser);
    m_DataExchangeConfigurator.SetSerializer(pSerializer);
}

CwsServerCommandHandler::~CwsServerCommandHandler()
{
}


int CwsServerCommandHandler::Start(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    if (IsRunning(p_rRequest, p_rResponse) == 0)
    {
        CwsCommandStartServer command(&m_Server);
        iRet = command.Execute(p_rRequest, p_rResponse);
    }
    else
    {
        ERR("Server already runs");
    }

    return iRet;
}



int CwsServerCommandHandler::Stop(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    if (IsRunning(p_rRequest, p_rResponse) > 0)
    {
        CwsCommandStopServer command(&m_Server);
        iRet = command.Execute(p_rRequest, p_rResponse);
    }
    else
    {
        ERR("Server is already stopped");
    }

    return iRet;
}

int CwsServerCommandHandler::IsRunning(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandIsRunning command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::GetOpenSessions(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandGetOpenSessions command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::Login(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandLogin command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::Logout(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandLogout command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::GetAppStoreData(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;

    CwsCommandGetAppStoreData command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::AddAppStoreScheme(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;

    CwsCommandAddAppToStore command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::DeleteAppStoreScheme(CwsRequest &p_rRequest, CwsResponse &p_rResponse)
{
    int iRet = 0;

    CwsCommandDeleteAppFromStore command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::GetServerConfig(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandGetServerSettings command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

int CwsServerCommandHandler::UpdateServerConfig(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    int iRet = 0;

    CwsCommandUpdateServerSettings command(&m_Server);
    iRet = command.Execute(p_rRequest, p_rResponse);

    return iRet;
}

bool CwsServerCommandHandler::HandleRequest(CwsHttpRequest *p_pRequest, CwsHttpResponse *p_pResponse)
{
    CwsRequest cRequest(p_pRequest->GetBody(), &m_DataExchangeConfigurator);
    CwsResponse cResponse(&m_DataExchangeConfigurator);

    QString qstrCommand = cRequest.GetCommand();

    if (cRequest.GetCommand() == START_SERVER)
    {
        Start(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == STOP_SERVER)
    {
        Stop(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == GET_OPEN_SESSIONS)
    {
        GetOpenSessions(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == GET_STATE)
    {
        IsRunning(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == INSTALL_LOGGING)
    {
        InstallLogging(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == GET_SERVER_CONFIG)
    {
        GetServerConfig(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == UPDATE_SERVER_CONFIG)
    {
        UpdateServerConfig(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == LOGIN)
    {
        Login(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == LOGOUT)
    {
        Logout(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == GET_APPSTORE_DATA)
    {
        GetAppStoreData(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == ADD_APPSTORE_SCHEME)
    {
        AddAppStoreScheme(cRequest, cResponse);
    }
    else if (cRequest.GetCommand() == DELETE_APPSTORE_SCHEME)
    {
        DeleteAppStoreScheme(cRequest, cResponse);
    }

    p_pResponse->SetStatusCode(cResponse.GetStatusCode());
    p_pResponse->SetBody(cResponse.Serialize());
    return true;
}

int CwsServerCommandHandler::InstallLogging(CwsRequest& p_rRequest, CwsResponse& p_rResponse)
{
    Q_UNUSED(p_rRequest);
    Q_UNUSED(p_rResponse);
    CwmsServerSettings cSettings;

     if (cSettings.getLoggingActive())
     {
         QString qstrPath = cSettings.getLoggingPath();

         if (!qstrPath.isEmpty())
         {
            int iSeverity = ExtractSeverity(cSettings);
            CdmLogging::CreateLoggingManager();
            QUrl url(qstrPath);
            qstrPath = url.path();
            CdmLogfileWriter* pWriter = new CdmLogfileWriter(qstrPath,
                                                                       "WMS Application Server",
                                                                       "1.0.0");
            CdmLogging::AddAdaptor(pWriter);
            CdmLogging::SetLoggingMode(iSeverity);
         }
     }

    return 0;
}

int CwsServerCommandHandler::ExtractSeverity( CwmsServerSettings &cSettings )
{
   int iSeverity = 0;

   if (cSettings.getLoggingInformation())
   {
      iSeverity = iSeverity | eDmInfo;
   }

   if (cSettings.getLoggingWarning())
   {
      iSeverity = iSeverity | eDmWarning;
   }

   if (cSettings.getLoggingError())
   {
      iSeverity = iSeverity | eDmError;
   }

   if (cSettings.getLoggingFatal())
   {
      iSeverity = iSeverity | eDmFatal;
   }

   return iSeverity;
}
