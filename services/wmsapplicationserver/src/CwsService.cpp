// System and Qt Includes
#include "stdio.h"
#include <QCoreApplication>

// WMS Includes
#include "CdmLogging.h"
#include "CdmSessionManager.h"

#include "CwmsServerSettings.h"

// Own includes
#include "CwsService.h"

#define PORT_ARG "-port="
#define MAINTENANCE_PORT_ARG "-maintenanceport="

CwsService::CwsService(int argc, char** argv, CwsServerCommandHandler* p_pHandler)
  : m_pHandler(p_pHandler),
  m_iPort(0),
  m_iServicePort(0)
{
   ParsePorts(argc, argv);
}

void CwsService::ParsePorts(int argc, char** argv)
{
    for (int iCounter = 1; iCounter < argc; ++iCounter) // 0 = applicationname
    {
        QString arg = QString(argv[iCounter]);
        INFO("Arg: " + arg);
        if (arg.startsWith(PORT_ARG))
        {
            m_iPort = ReadPort(arg);
        }
        else if (arg.startsWith(MAINTENANCE_PORT_ARG))
        {
            m_iServicePort = ReadPort(arg);
        }
    }

    if (m_iPort == 0)
    {
        m_iPort = 8383;
    }

    if (m_iServicePort == 0)
    {
        m_iServicePort = 8181;
    }
}

int CwsService::ReadPort(QString p_qstrArg)
{
    int iPos = p_qstrArg.indexOf("=");
    if (iPos > 0)
    {
        QString qstrPort = p_qstrArg.mid(iPos + 1, p_qstrArg.length() - iPos - 1);
        return qstrPort.toInt();
    }
    else
    {
        return 0;
    }
}

bool CwsService::isServiceArgument(int argc, char **argv)
{
    ERR("Arg count:" + QString::number(argc));

    bool bReturn = false;
    QStringList args;
    args << "-install";
    args << "-uninstall";
    args << "-exec";
    args << "-start";
    args << "-terminate";
    args << "-pause";
    args << "-resume";
    args << "-version";
    args << "-v";
    args << "-i";
    args << "-u";
    args << "-e";
    args << "-t";
    args << "-p";
    args << "-r";
    args << "-c";
    args << "-command";
    args << "-h";
    args << "-help";

    for (int iCounter = 1; iCounter < argc; ++iCounter) // 0 = applicationname
    {
        ERR("Arg: " + QString(argv[iCounter]));
        if (args.contains(argv[iCounter]))
        {
            bReturn = true;
            break;
        }
    }

    if (!bReturn && argc == 1) // no arguments means service
    {
        bReturn = true;
    }

    return bReturn;
}

CwsService::~CwsService()
{
}

void CwsService::start()
{
   CwsRequest request;
   request.SetValue("port", m_iPort);
   request.SetValue("maintenancePort", m_iServicePort);
   CwsResponse response;
   m_pHandler->Start(request, response);
}

void CwsService::pause()
{
    CwsRequest cRequest;
    CwsResponse cResponse;
    m_pHandler->Stop(cRequest, cResponse);
}

void CwsService::resume()
{
   start();
}

void CwsService::stop()
{
   pause();
   qApp->quit();
}

int CwsService::GetMaintenancePort()
{
    if (m_iServicePort == 0)
    {
        m_iServicePort = 8181;
    }

    return m_iServicePort;
}
